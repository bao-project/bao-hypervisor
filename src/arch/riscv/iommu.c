/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/iommu.h>
#include <config.h>
#include <interrupts.h>
#include <string.h>
#include <arch/spinlock.h>
#include <bitmap.h>

// We initially use a 1-LVL DDT with DC in extended format
// N entries = 4kiB / 64 B p/ entry = 64 Entries
#define DDT_N_ENTRIES (64)

#define FQ_N_ENTRIES  (64)
#define FQ_LOG2SZ_1   (5ULL)
#define FQ_INDEX_MASK BIT32_MASK(0, FQ_LOG2SZ_1 + 1)

#define RV_IOMMU_SUPPORTED_VERSION   (0x10)

//# Memory-mapped Register Interface
// Capabilities register fields
#define RV_IOMMU_CAPS_VERSION_OFF    (0)
#define RV_IOMMU_CAPS_VERSION_LEN    (8)

#define RV_IOMMU_CAPS_SV39X4_BIT     (0x1ULL << 17)
#define RV_IOMMU_CAPS_MSI_FLAT_BIT   (0x1ULL << 22)
#define RV_IOMMU_CAPS_IGS_OFF        (28)
#define RV_IOMMU_CAPS_IGS_LEN        (2)

// Features control register fields
#define RV_IOMMU_FCTL_WSI_BIT        (0x1UL << 1)
#define RV_IOMMU_FCTL_DEFAULT        (RV_IOMMU_FCTL_WSI_BIT)

// Device Directory Table Pointer register
#define RV_IOMMU_DDTP_MODE_OFF       (0ULL)
#define RV_IOMMU_DDTP_MODE_BARE      (1ULL)
#define RV_IOMMU_DDTP_MODE_1LVL      (2ULL)
#define RV_IOMMU_DDTP_MODE_2LVL      (3ULL)
#define RV_IOMMU_DDTP_MODE_3LVL      (4ULL)

#define RV_IOMMU_DDTP_BUSY_BIT       (0x1ULL << 4)

#define RV_IOMMU_DDTP_PPN_OFF        (10)
#define RV_IOMMU_DDTP_PPN_LEN        (44)
#define RV_IOMMU_DDTP_PPN_MASK       BIT64_MASK(RV_IOMMU_DDTP_PPN_OFF, RV_IOMMU_DDTP_PPN_LEN)

// Queue management
#define RV_IOMMU_XQB_PPN_OFF         (10)
#define RV_IOMMU_XQB_PPN_LEN         (44)
#define RV_IOMMU_XQB_PPN_MASK        BIT64_MASK(RV_IOMMU_XQB_PPN_OFF, RV_IOMMU_XQB_PPN_LEN)

#define RV_IOMMU_XQCSR_EN_BIT        (1ULL << 0)
#define RV_IOMMU_XQCSR_IE_BIT        (1ULL << 1)
#define RV_IOMMU_XQCSR_MF_BIT        (1ULL << 8)
#define RV_IOMMU_XQCSR_ON_BIT        (1ULL << 16)
#define RV_IOMMU_XQCSR_BUSY_BIT      (1ULL << 17)

// FQ CSR
#define RV_IOMMU_FQCSR_OF_BIT        (1ULL << 9)
#define RV_IOMMU_FQCSR_DEFAULT       (RV_IOMMU_XQCSR_EN_BIT | \
                                         RV_IOMMU_XQCSR_IE_BIT | \
                                         RV_IOMMU_XQCSR_MF_BIT | \
                                         RV_IOMMU_FQCSR_OF_BIT)
#define RV_IOMMU_FQCSR_CLEAR_ERR     (RV_IOMMU_XQCSR_MF_BIT | RV_IOMMU_FQCSR_OF_BIT)

// Interrupt pending register
#define RV_IOMMU_IPSR_FIP_BIT        (1UL << 1)
#define RV_IOMMU_IPSR_CLEAR          (0x0FUL)

// Interrupt Vectors
#define RV_IOMMU_ICVEC_CIV_NUM       (0ULL)
#define RV_IOMMU_ICVEC_FIV_NUM       (1ULL)

#define RV_IOMMU_ICVEC_CIV_OFF       (0)
#define RV_IOMMU_ICVEC_FIV_OFF       (4)

#define RV_IOMMU_ICVEC_CIV           (RV_IOMMU_ICVEC_CIV_NUM << RV_IOMMU_ICVEC_CIV_OFF)
#define RV_IOMMU_ICVEC_FIV           (RV_IOMMU_ICVEC_FIV_NUM << RV_IOMMU_ICVEC_FIV_OFF)
#define RV_IOMMU_ICVEC_DEFAULT       (RV_IOMMU_ICVEC_CIV | RV_IOMMU_ICVEC_FIV)

//# RISC-V IOMMU Memory-Mapped Register Interface
struct riscv_iommu_regmap {
    uint64_t caps;
    uint32_t fctl;
    uint8_t  __custom1[4];
    uint64_t ddtp;
    uint64_t cqb;
    uint32_t cqh;
    uint32_t cqt;
    uint64_t fqb;
    uint32_t fqh;
    uint32_t fqt;
    uint64_t pqb;
    uint32_t pqh;
    uint32_t pqt;
    uint32_t cqcsr;
    uint32_t fqcsr;
    uint32_t pqcsr;
    uint32_t ipsr;
    uint32_t iocntovf;
    uint32_t iocntinh;
    uint64_t iohpmcycles;
    uint64_t iohpmctr[31];
    uint64_t iohpmevt[31];
    uint64_t tr_req_iova;
    uint64_t tr_req_ctl;
    uint64_t tr_response;
    uint8_t  __rsv1[64];
    uint8_t  __custom2[72];
    uint64_t icvec;
    struct {
        uint64_t addr;
        uint32_t data;
        uint32_t vctl;
    } __attribute__((__packed__)) msi_cfg_tbl[16];
    uint8_t  __rsv2[3072];

} __attribute__((__packed__, __aligned__(PAGE_SIZE)));

//# RISC-V IOMMU Device Directory Table
#define RV_IOMMU_DC_VALID_BIT   (1ULL << 0)
#define RV_IOMMU_DC_DTF_BIT     (1ULL << 4)

#define RV_IOMMU_DC_IOHGATP_PPN_OFF     (0)
#define RV_IOMMU_DC_IOHGATP_PPN_LEN     (44)
#define RV_IOMMU_DC_IOHGATP_PPN_MASK    BIT64_MASK(RV_IOMMU_DC_IOHGATP_PPN_OFF, RV_IOMMU_DC_IOHGATP_PPN_LEN)
#define RV_IOMMU_DC_IOHGATP_GSCID_OFF   (44)
#define RV_IOMMU_DC_IOHGATP_GSCID_LEN   (16)
#define RV_IOMMU_DC_IOHGATP_GSCID_MASK  BIT64_MASK(RV_IOMMU_DC_IOHGATP_GSCID_OFF, RV_IOMMU_DC_IOHGATP_GSCID_LEN)
#define RV_IOMMU_DC_IOHGATP_MODE_OFF    (60)
#define RV_IOMMU_DC_IOHGATP_MODE_LEN    (4)
#define RV_IOMMU_DC_IOHGATP_MODE_MASK   BIT64_MASK(RV_IOMMU_DC_IOHGATP_MODE_OFF, RV_IOMMU_DC_IOHGATP_MODE_LEN)
#define RV_IOMMU_IOHGATP_SV39X4         (8ULL << RV_IOMMU_DC_IOHGATP_MODE_OFF)
#define RV_IOMMU_IOHGATP_BARE           (0ULL << RV_IOMMU_DC_IOHGATP_MODE_OFF)

#define RV_IOMMU_DC_IOHGATP_PSCID_OFF   (12)
#define RV_IOMMU_DC_IOHGATP_PSCID_LEN   (20)
#define RV_IOMMU_DC_IOHGATP_PSCID_MASK  BIT64_MASK(RV_IOMMU_DC_IOHGATP_PSCID_OFF, RV_IOMMU_DC_IOHGATP_PSCID_LEN)

#define RV_IOMMU_DC_FSC_PPN_OFF         (0)
#define RV_IOMMU_DC_FSC_PPN_LEN         (44)
#define RV_IOMMU_DC_FSC_PPN_MASK        BIT64_MASK(RV_IOMMU_DC_FSC_PPN_OFF, RV_IOMMU_DC_FSC_PPN_LEN)
#define RV_IOMMU_DC_FSC_MODE_OFF        (60)
#define RV_IOMMU_DC_FSC_MODE_LEN        (4)
#define RV_IOMMU_DC_FSC_MODE_MASK       BIT64_MASK(RV_IOMMU_DC_FSC_MODE_OFF, RV_IOMMU_DC_FSC_MODE_LEN)

#define RV_IOMMU_DC_MSIPTP_PPN_OFF      (0)
#define RV_IOMMU_DC_MSIPTP_PPN_LEN      (44)
#define RV_IOMMU_DC_MSIPTP_PPN_MASK     BIT64_MASK(RV_IOMMU_DC_MSIPTP_PPN_OFF, RV_IOMMU_DC_MSIPTP_PPN_LEN)
#define RV_IOMMU_DC_MSIPTP_MODE_OFF     (60)
#define RV_IOMMU_DC_MSIPTP_MODE_LEN     (4)
#define RV_IOMMU_DC_MSIPTP_MODE_MASK    BIT64_MASK(RV_IOMMU_DC_MSIPTP_MODE_OFF, RV_IOMMU_DC_MSIPTP_MODE_LEN)

#define RV_IOMMU_DC_MSIMASK_OFF         (0)
#define RV_IOMMU_DC_MSIMASK_LEN         (52)
#define RV_IOMMU_DC_MSIMASK_MASK        BIT64_MASK(RV_IOMMU_DC_MSIMASK_OFF, RV_IOMMU_DC_MSIMASK_LEN)

struct ddt_entry {
    uint64_t tc;
    uint64_t iohgatp;
    uint64_t ta;
    uint64_t fsc;
    uint64_t msiptp;
    uint64_t msi_addr_mask;
    uint64_t msi_addr_pattern;
    uint64_t __rsv;
} __attribute__((__packed__));


//# Fault Queue Record
#define RV_IOMMU_FQ_CAUSE_OFF    (0)
#define RV_IOMMU_FQ_CAUSE_LEN    (12)
#define RV_IOMMU_FQ_PID_OFF      (12)
#define RV_IOMMU_FQ_PID_LEN      (20)
#define RV_IOMMU_FQ_TTYP_OFF     (34)
#define RV_IOMMU_FQ_TTYP_LEN     (6)
#define RV_IOMMU_FQ_DID_OFF      (40)
#define RV_IOMMU_FQ_DID_LEN      (24)

struct fq_entry {
    uint64_t tags;
    uint64_t __rsv;
    uint64_t iotval;
    uint64_t iotval2;
} __attribute__((__packed__));

//# Memory-mapped and in-memory structures
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

/**************** RISC-V IOMMU specific functions ****************/

/**
 * Read and check IOMMU caps
 */
static void rv_iommu_check_features(void)
{
    unsigned long long caps = rv_iommu.hw.reg_ptr->caps;
    unsigned version = bit64_extract(caps,
                            RV_IOMMU_CAPS_VERSION_OFF, RV_IOMMU_CAPS_VERSION_LEN);

    if (version != RV_IOMMU_SUPPORTED_VERSION) {
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
    interrupts_reserve(platform.arch.iommu.fq_irq_id, rv_iommu_fq_irq_handler);
    interrupts_cpu_enable(platform.arch.iommu.fq_irq_id, true);

    // Enable FQ (fqcsr)
    rv_iommu.hw.reg_ptr->fqcsr = RV_IOMMU_FQCSR_DEFAULT;
    // TODO: poll fqcsr.busy 

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
    // TODO: poll ddtp.busy
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
    bool allocated;
    spin_lock(&rv_iommu.ddt_lock);

    // Check if DC already exists
    if (!bitmap_get(rv_iommu.ddt_bitmap, dev_id))
    {
        bitmap_set(rv_iommu.ddt_bitmap, dev_id);
        allocated = true;
    }
    else
    {
        allocated = false;   // device_id already exists
    }

    spin_unlock(&rv_iommu.ddt_lock);
    return allocated;
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

/**************** IOMMU IF functions ****************/

/**
 * IOMMU HW Initialization.
 * 
 * @returns true on success, false on error.
 */
bool iommu_arch_init()
{   

    // By checking platform.arch.iommu.base we verify if an IOMMU is present in the platform
    if(cpu()->id == CPU_MASTER && platform.arch.iommu.base){
        rv_iommu_init();
        return true;
    }

    return false;
}

/**
 * Initialize the DDT entry indexed by device_id for the given VM
 * Configure corresponding DDT entry with root PT base addr, VMID (GSCID) and device config
 * 
 * @vm:     VM struct to which the device will be assigned.
 * @dev_id: device_id of the device to be added.
 * 
 * @returns true on success, false on error.
 */
static bool iommu_vm_arch_add(struct vm *vm, deviceid_t dev_id)
{
    if (dev_id > 0)
    {
        // Check if device was already added to a VM
        if(rv_iommu_alloc_did(dev_id))
        {
            paddr_t rootpt;
            // Translate root PT base address
            mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &rootpt);
            // Set DDT entry with root PT base address, VMID and configuration
            rv_iommu_write_ddt(dev_id, vm, rootpt);
        }
        else
        {
            INFO("RV IOMMU: Cannot add one device ID (%d) twice", dev_id);
            return false;
        }
    }
    else
    {
        INFO("RV IOMMU: Invalid device ID: %d", dev_id);
        return false;
    }

    return true;
}

/**
 * Add device to the VM specified.
 * 
 * @vm:     VM struct to which the device will be assigned.
 * @dev_id: device_id of the device to be added.
 * 
 * @returns true on success, false on error.
 */
inline bool iommu_arch_vm_add_device(struct vm *vm, deviceid_t dev_id)
{
    return iommu_vm_arch_add(vm, dev_id);
}

/**
 * Initialize VM-specific, arch-specific IOMMU data.
 * 
 * @vm:     VM under consideration.
 * @config: VM config.
 * 
 * @returns true on success, false on error.
 */
bool iommu_arch_vm_init(struct vm *vm, const struct vm_config *config)
{
    // For now there is no data to initialize
    return true;
}
