/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/spinlock.h>
#include <bitmap.h>
#include <bit.h>
#include <platform.h>
#include <interrupts.h>
#include <arch/riscv_iommu.h>
#include <string.h>

// Memory-mapped and in-memory structures
// TODO: Add CQ
struct riscv_iommu_hw {
    volatile struct riscv_iommu_regmap *reg_ptr;
    volatile struct ddt_entry *ddt;
    volatile struct fq_entry *fq;
};

struct riscv_iommu_priv {
    struct riscv_iommu_hw hw;

    spinlock_t ddt_lock;
    BITMAP_ALLOC(ddt_bitmap, DDT_N_ENTRIES);
};

struct riscv_iommu_priv rv_iommu;

/**
 * Read and check IOMMU caps
 */
static void rv_iommu_check_features(void)
{
    unsigned long long caps = rv_iommu.hw.reg_ptr->caps;
    unsigned version = bit64_extract(caps,
                            RV_IOMMU_CAPS_VERSION_OFF, RV_IOMMU_CAPS_VERSION_LEN);

    if (version != 0x10) {
        ERROR("RISC-V IOMMU unsupported version: %d", version);
    }

    if (!(caps & RV_IOMMU_CAPS_SV39X4_BIT)) {
        ERROR("RISC-V IOMMU HW does not support Sv39x4");
    }

    if (!(caps & RV_IOMMU_CAPS_MSI_FLAT_BIT)) {
        WARNING("RISC-V IOMMU HW does not support MSI Address Translation (basic-translate mode)");
    }

    unsigned igs = bit64_extract(caps, RV_IOMMU_CAPS_IGS_OFF, RV_IOMMU_CAPS_IGS_LEN);
    if ((!igs)) {
        ERROR("RISC-V IOMMU HW does not support WSI generation");
    }
}

/**
 * RISC-V IOMMU Fault Queue IRQ handler.
 */
void rv_iommu_fq_irq_handler(irqid_t irq_id)
{
    // Read ipsr.fip
    uint32_t ipsr = rv_iommu.hw.reg_ptr->ipsr;

    // Signal error if fip not set
    if (!(ipsr & RV_IOMMU_IPSR_FIP_BIT))
        ERROR("FQ IRQ handler triggered due to non-FQ interrupt");

    // Read fqcsr error bits and report if any is set
    uint32_t fqcsr = rv_iommu.hw.reg_ptr->fqcsr;
    if (fqcsr & (RV_IOMMU_XQCSR_MF_BIT | RV_IOMMU_FQCSR_OF_BIT))
    {
        if (fqcsr & RV_IOMMU_XQCSR_MF_BIT)
        {
            WARNING("RV IOMMU: FQ Memory Fault error!");
            // TODO: MF management
        }

        if (fqcsr & RV_IOMMU_FQCSR_OF_BIT)
        {
            WARNING("RV IOMMU: FQ Full!");
            // TODO: OF Management
        }

        // Clear fqcsr error bits
        rv_iommu.hw.reg_ptr->fqcsr = RV_IOMMU_FQCSR_CLEAR_ERR;
    }

    // Clear ipsr.fip
    rv_iommu.hw.reg_ptr->ipsr = RV_IOMMU_IPSR_FIP_BIT;

    // Check if new records are available. If yes, report all remaining faults.
    uint32_t fqh = rv_iommu.hw.reg_ptr->fqh;
    uint32_t fqt = rv_iommu.hw.reg_ptr->fqt;

    while (fqh != fqt)
    {
        struct fq_entry record = rv_iommu.hw.fq[fqh];
        WARNING("RV IOMMU FQ: CAUSE: %d | DID: %d | iotval: %x | iotval2: %x",
                bit64_extract(record.tags, RV_IOMMU_FQ_CAUSE_OFF, RV_IOMMU_FQ_CAUSE_LEN),
                bit64_extract(record.tags, RV_IOMMU_FQ_DID_OFF, RV_IOMMU_FQ_DID_LEN),
                record.iotval,
                record.iotval2);
        fqh = (fqh + 1) & FQ_INDEX_MASK;
        // TODO: Translation faults management
    }
    
    // Update fqh
    rv_iommu.hw.reg_ptr->fqh = fqh;
}


/**
 * Init and enable RISC-V IOMMU. 
 */
void rv_iommu_init(void)
{
    // Map register IF (4k)
    vaddr_t reg_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.iommu.base,  NUM_PAGES(sizeof(struct riscv_iommu_regmap)));

    rv_iommu.hw.reg_ptr = (struct riscv_iommu_regmap*)reg_ptr;

    // Read and check caps
    rv_iommu_check_features();

    // Set fctl.WSI
    // We will be first using WSI as IOMMU interrupt mechanism. Then MSIs will be included
    rv_iommu.hw.reg_ptr->fctl = RV_IOMMU_FCTL_DEFAULT;

    // Configure interrupt vectors (icvec)
    // We use a different vector for each interrupt source CQ and FQ by now
    rv_iommu.hw.reg_ptr->icvec = RV_IOMMU_ICVEC_DEFAULT;

    // Clear all IP flags (ipsr)
    rv_iommu.hw.reg_ptr->ipsr = RV_IOMMU_IPSR_CLEAR;
    
    // TODO
    // Allocate memory for CQ
    // Configure cqb with queue size and base address. Clear cqt
    // Allocate IRQ for CQ
    // Enable CQ (cqcsr)

    // Allocate memory for FQ (aligned to 4kiB)
    vaddr_t fq_vaddr = (vaddr_t)mem_alloc_page(NUM_PAGES(sizeof(struct fq_entry) * FQ_N_ENTRIES),
                                                SEC_HYP_GLOBAL, true);
    memset((void*)fq_vaddr, 0, sizeof(struct fq_entry) * FQ_N_ENTRIES);
    rv_iommu.hw.fq = (struct fq_entry*)fq_vaddr;

    // Configure fqb with queue size and base address. Clear fqh
    paddr_t fq_paddr;
    mem_translate(&cpu()->as, fq_vaddr, &fq_paddr);
    rv_iommu.hw.reg_ptr->fqb = FQ_LOG2SZ_1 | 
                                ((fq_paddr >> 2) & RV_IOMMU_XQB_PPN_MASK);
    rv_iommu.hw.reg_ptr->fqh = 0;

    // Allocate IRQ for FQ
    //! Ask Martins about the number of PLIC IP registers
    interrupts_reserve(platform.arch.iommu.fq_irq_id, rv_iommu_fq_irq_handler);
    interrupts_cpu_enable(platform.arch.iommu.fq_irq_id, true);

    // Enable FQ (fqcsr)
    rv_iommu.hw.reg_ptr->fqcsr = RV_IOMMU_FQCSR_DEFAULT;
    //! We ignore fqcsr.busy by now...

    // Init DDT bitmap
    rv_iommu.ddt_lock = SPINLOCK_INITVAL;
    bitmap_clear_consecutive(rv_iommu.ddt_bitmap, 0, DDT_N_ENTRIES);

    // Allocate a page of memory (aligned) for the DDT
    vaddr_t ddt_vaddr = (vaddr_t)mem_alloc_page(NUM_PAGES(sizeof(struct ddt_entry) * DDT_N_ENTRIES), 
                                                SEC_HYP_GLOBAL, true);
    // Clear entries
    memset((void*)ddt_vaddr, 0, sizeof(struct ddt_entry) * DDT_N_ENTRIES);
    rv_iommu.hw.ddt = (struct ddt_entry*)ddt_vaddr;

    // Configure ddtp with DDT base address and IOMMU mode
    paddr_t ddt_paddr;
    mem_translate(&cpu()->as, ddt_vaddr, &ddt_paddr);
    rv_iommu.hw.reg_ptr->ddtp = (unsigned long long)platform.arch.iommu.mode | 
                                ((ddt_paddr >> 2) & RV_IOMMU_DDTP_PPN_MASK);
    //! We ignore ddtp.busy by now...
}

/**
 * Set DDT N bit in the DDT bitmap.
 * 
 * @dev_id: device_id to be allocated
 * 
 * @returns true on success, false on error
 */
bool rv_iommu_alloc_did(deviceid_t dev_id)
{
    spin_lock(&rv_iommu.ddt_lock);

    // Check if DC already exists
    if (!bitmap_get(rv_iommu.ddt_bitmap, dev_id))
    {
        bitmap_set(rv_iommu.ddt_bitmap, dev_id);
    }
    else
    {
        spin_unlock(&rv_iommu.ddt_lock);
        return false;   // device_id already exists
    }
    spin_unlock(&rv_iommu.ddt_lock);

    return true;
}

/**
 * Program DDT entry with base address of the root PT, VMID and translation configuration. Enable DC.
 * 
 * @dev_id:     device_id to index DDT
 * @vm:         VM to which the device is being assigned
 * @root_pt:    Base physical address of the root second-stage PT
 */
void rv_iommu_write_ddt(deviceid_t dev_id, struct vm *vm, paddr_t root_pt)
{
    spin_lock(&rv_iommu.ddt_lock);
    if (!bitmap_get(rv_iommu.ddt_bitmap, dev_id))
    {
        ERROR("IOMMU DC %d is not allocated", dev_id);
    }
    else
    {
        // Configure DC
        uint64_t tc = 0;
        tc |= RV_IOMMU_DC_VALID_BIT;
        rv_iommu.hw.ddt[dev_id].tc = tc;

        uint64_t iohgatp = 0;
        iohgatp |= ((root_pt >> 12) & RV_IOMMU_DC_IOHGATP_PPN_MASK);
        iohgatp |= ((vm->id << RV_IOMMU_DC_IOHGATP_GSCID_OFF) 
                        & RV_IOMMU_DC_IOHGATP_GSCID_MASK);
        iohgatp |= RV_IOMMU_IOHGATP_SV39X4;
        
        rv_iommu.hw.ddt[dev_id].iohgatp = iohgatp;

        // TODO:
        // Configure first-stage translation. Second-stage only by now
        // Configure MSI translation
    }
    spin_unlock(&rv_iommu.ddt_lock);
}
