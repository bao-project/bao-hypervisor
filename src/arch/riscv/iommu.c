/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/iommu.h>
#include <config.h>
#include <interrupts.h>
#include <string.h>
#include <arch/spinlock.h>

#define FQ_N_ENTRIES               (64)
#define FQ_LOG2SZ_1                (5ULL)
#define FQ_INDEX_MASK              BIT32_MASK(0, FQ_LOG2SZ_1 + 1)

#define RV_IOMMU_SUPPORTED_VERSION (0x10)

// # Memory-mapped Register Interface
//  Capabilities register fields
#define RV_IOMMU_CAPS_VERSION_OFF  (0)
#define RV_IOMMU_CAPS_VERSION_LEN  (8)

#define RV_IOMMU_CAPS_SV39X4_BIT   (0x1ULL << 17)
#define RV_IOMMU_CAPS_MSI_FLAT_BIT (0x1ULL << 22)
#define RV_IOMMU_CAPS_IGS_OFF      (28)
#define RV_IOMMU_CAPS_IGS_LEN      (2)

// Features control register fields
#define RV_IOMMU_FCTL_WSI_BIT      (0x1UL << 1)
#define RV_IOMMU_FCTL_DEFAULT      (RV_IOMMU_FCTL_WSI_BIT)

// Device Directory Table Pointer register
#define RV_IOMMU_DDTP_MODE_OFF     (0ULL)
#define RV_IOMMU_DDTP_MODE_BARE    (1ULL)
#define RV_IOMMU_DDTP_MODE_1LVL    (2ULL)
#define RV_IOMMU_DDTP_MODE_2LVL    (3ULL)
#define RV_IOMMU_DDTP_MODE_3LVL    (4ULL)

#define RV_IOMMU_DDTP_BUSY_BIT     (0x1ULL << 4)

#define RV_IOMMU_DDTP_PPN_OFF      (10)
#define RV_IOMMU_DDTP_PPN_LEN      (44)
#define RV_IOMMU_DDTP_PPN_MASK     BIT64_MASK(RV_IOMMU_DDTP_PPN_OFF, RV_IOMMU_DDTP_PPN_LEN)

// Queue management
#define RV_IOMMU_XQB_PPN_OFF       (10)
#define RV_IOMMU_XQB_PPN_LEN       (44)
#define RV_IOMMU_XQB_PPN_MASK      BIT64_MASK(RV_IOMMU_XQB_PPN_OFF, RV_IOMMU_XQB_PPN_LEN)

#define RV_IOMMU_XQCSR_EN_BIT      (1ULL << 0)
#define RV_IOMMU_XQCSR_IE_BIT      (1ULL << 1)
#define RV_IOMMU_XQCSR_MF_BIT      (1ULL << 8)
#define RV_IOMMU_XQCSR_ON_BIT      (1ULL << 16)
#define RV_IOMMU_XQCSR_BUSY_BIT    (1ULL << 17)

// FQ CSR
#define RV_IOMMU_FQCSR_OF_BIT      (1ULL << 9)
#define RV_IOMMU_FQCSR_DEFAULT \
    (RV_IOMMU_XQCSR_EN_BIT | RV_IOMMU_XQCSR_IE_BIT | RV_IOMMU_XQCSR_MF_BIT | RV_IOMMU_FQCSR_OF_BIT)
#define RV_IOMMU_FQCSR_CLEAR_ERR (RV_IOMMU_XQCSR_MF_BIT | RV_IOMMU_FQCSR_OF_BIT)

// Interrupt pending register
#define RV_IOMMU_IPSR_FIP_BIT    (1UL << 1)
#define RV_IOMMU_IPSR_CLEAR      (0x0FUL)

// Interrupt Vectors
#define RV_IOMMU_ICVEC_CIV_NUM   (0ULL)
#define RV_IOMMU_ICVEC_FIV_NUM   (1ULL)

#define RV_IOMMU_ICVEC_CIV_OFF   (0)
#define RV_IOMMU_ICVEC_FIV_OFF   (4)

#define RV_IOMMU_ICVEC_CIV       (RV_IOMMU_ICVEC_CIV_NUM << RV_IOMMU_ICVEC_CIV_OFF)
#define RV_IOMMU_ICVEC_FIV       (RV_IOMMU_ICVEC_FIV_NUM << RV_IOMMU_ICVEC_FIV_OFF)
#define RV_IOMMU_ICVEC_DEFAULT   (RV_IOMMU_ICVEC_CIV | RV_IOMMU_ICVEC_FIV)

// # RISC-V IOMMU Memory-Mapped Register Interface
struct riscv_iommu_regmap {
    uint64_t caps;
    uint32_t fctl;
    uint8_t __custom1[4];
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
    uint8_t __rsv1[64];
    uint8_t __custom2[72];
    uint64_t icvec;
    struct {
        uint64_t addr;
        uint32_t data;
        uint32_t vctl;
    } __attribute__((__packed__)) msi_cfg_tbl[16];
    uint8_t __rsv2[3072];

} __attribute__((__packed__, __aligned__(PAGE_SIZE)));

// # RISC-V IOMMU Device Directory Table

// device_id masks
#define DDI_2_BASE_OFF              (16)
#define DDI_1_BASE_OFF              (7)
#define DDI_0_BASE_OFF              (0)

#define DDI_2_BASE_LEN              (8)
#define DDI_1_BASE_LEN              (9)
#define DDI_0_BASE_LEN              (7)

#define DDI_2_MASK_BASE             BIT32_MASK(DDI_2_BASE_OFF, DDI_2_BASE_LEN)
#define DDI_1_MASK_BASE             BIT32_MASK(DDI_1_BASE_OFF, DDI_1_BASE_LEN)
#define DDI_0_MASK_BASE             BIT32_MASK(DDI_0_BASE_OFF, DDI_0_BASE_LEN)

// DC fields

// Non-leaf
#define RV_IOMMU_DDT_NL_PPN_OFF     (10)
#define RV_IOMMU_DDT_NL_PPN_LEN     (44)
#define RV_IOMMU_DDT_NL_PPN_MASK    BIT64_MASK(RV_IOMMU_DDT_NL_PPN_OFF, RV_IOMMU_DDT_NL_PPN_LEN)

// Leaf
#define RV_IOMMU_DC_VALID_BIT       (1ULL << 0)
#define RV_IOMMU_DC_DTF_BIT         (1ULL << 4)

#define RV_IOMMU_DC_IOHGATP_PPN_OFF (0)
#define RV_IOMMU_DC_IOHGATP_PPN_LEN (44)
#define RV_IOMMU_DC_IOHGATP_PPN_MASK \
    BIT64_MASK(RV_IOMMU_DC_IOHGATP_PPN_OFF, RV_IOMMU_DC_IOHGATP_PPN_LEN)
#define RV_IOMMU_DC_IOHGATP_GSCID_OFF (44)
#define RV_IOMMU_DC_IOHGATP_GSCID_LEN (16)
#define RV_IOMMU_DC_IOHGATP_GSCID_MASK \
    BIT64_MASK(RV_IOMMU_DC_IOHGATP_GSCID_OFF, RV_IOMMU_DC_IOHGATP_GSCID_LEN)
#define RV_IOMMU_DC_IOHGATP_MODE_OFF (60)
#define RV_IOMMU_DC_IOHGATP_MODE_LEN (4)
#define RV_IOMMU_DC_IOHGATP_MODE_MASK \
    BIT64_MASK(RV_IOMMU_DC_IOHGATP_MODE_OFF, RV_IOMMU_DC_IOHGATP_MODE_LEN)
#define RV_IOMMU_IOHGATP_SV39X4       (8ULL << RV_IOMMU_DC_IOHGATP_MODE_OFF)
#define RV_IOMMU_IOHGATP_BARE         (0ULL << RV_IOMMU_DC_IOHGATP_MODE_OFF)

#define RV_IOMMU_DC_IOHGATP_PSCID_OFF (12)
#define RV_IOMMU_DC_IOHGATP_PSCID_LEN (20)
#define RV_IOMMU_DC_IOHGATP_PSCID_MASK \
    BIT64_MASK(RV_IOMMU_DC_IOHGATP_PSCID_OFF, RV_IOMMU_DC_IOHGATP_PSCID_LEN)

#define RV_IOMMU_DC_FSC_PPN_OFF    (0)
#define RV_IOMMU_DC_FSC_PPN_LEN    (44)
#define RV_IOMMU_DC_FSC_PPN_MASK   BIT64_MASK(RV_IOMMU_DC_FSC_PPN_OFF, RV_IOMMU_DC_FSC_PPN_LEN)
#define RV_IOMMU_DC_FSC_MODE_OFF   (60)
#define RV_IOMMU_DC_FSC_MODE_LEN   (4)
#define RV_IOMMU_DC_FSC_MODE_MASK  BIT64_MASK(RV_IOMMU_DC_FSC_MODE_OFF, RV_IOMMU_DC_FSC_MODE_LEN)

#define RV_IOMMU_DC_MSIPTP_PPN_OFF (0)
#define RV_IOMMU_DC_MSIPTP_PPN_LEN (44)
#define RV_IOMMU_DC_MSIPTP_PPN_MASK \
    BIT64_MASK(RV_IOMMU_DC_MSIPTP_PPN_OFF, RV_IOMMU_DC_MSIPTP_PPN_LEN)
#define RV_IOMMU_DC_MSIPTP_MODE_OFF (60)
#define RV_IOMMU_DC_MSIPTP_MODE_LEN (4)
#define RV_IOMMU_DC_MSIPTP_MODE_MASK \
    BIT64_MASK(RV_IOMMU_DC_MSIPTP_MODE_OFF, RV_IOMMU_DC_MSIPTP_MODE_LEN)

#define RV_IOMMU_DC_MSIMASK_OFF  (0)
#define RV_IOMMU_DC_MSIMASK_LEN  (52)
#define RV_IOMMU_DC_MSIMASK_MASK BIT64_MASK(RV_IOMMU_DC_MSIMASK_OFF, RV_IOMMU_DC_MSIMASK_LEN)

typedef uint64_t* ddt_bitmap_t;

#define DDT_BITMAP_GET(BITMAP, DEV_ID) (BITMAP[DEV_ID / 64] & (1ULL << (DEV_ID % 64)))
#define DDT_BITMAP_SET(BITMAP, DEV_ID) (BITMAP[DEV_ID / 64] |= (1ULL << (DEV_ID % 64)))

// Abstract Device Context Struct
// Each entry may represent 1 or 2 entries, depending on MSI translation support
struct ddt_entry {
    uint64_t dw_1;
    uint64_t dw_2;
    uint64_t dw_3;
    uint64_t dw_4;
    uint64_t dw_5;
    uint64_t dw_6;
    uint64_t dw_7;
    uint64_t dw_8;
} __attribute__((__packed__));

// # Fault Queue
#define RV_IOMMU_FQ_CAUSE_OFF (0)
#define RV_IOMMU_FQ_CAUSE_LEN (12)
#define RV_IOMMU_FQ_PID_OFF   (12)
#define RV_IOMMU_FQ_PID_LEN   (20)
#define RV_IOMMU_FQ_TTYP_OFF  (34)
#define RV_IOMMU_FQ_TTYP_LEN  (6)
#define RV_IOMMU_FQ_DID_OFF   (40)
#define RV_IOMMU_FQ_DID_LEN   (24)

struct fq_entry {
    uint64_t tags;
    uint64_t __rsv;
    uint64_t iotval;
    uint64_t iotval2;
} __attribute__((__packed__));

// # Memory-mapped and in-memory structures
//  TODO: Add CQ
struct riscv_iommu_hw {
    volatile struct riscv_iommu_regmap* reg_ptr;
    volatile uint64_t* vddt_lvl0;
    volatile uint64_t** vddt_lvl1;
    volatile uint64_t*** vddt_lvl2;
    volatile struct fq_entry* fq;
};

// Private data
struct riscv_iommu_priv {
    struct riscv_iommu_hw hw; // HW ptrs

    // DDT
    spinlock_t ddt_lock;
    ddt_bitmap_t ddt_bitmap;

    // Misc
    unsigned long long caps;       // caps register
    uint8_t supported_modes;       // supported IOMMU modes
    unsigned long long iommu_mode; // current IOMMU mode
    bool msi_support;              // MSI translation support flag
};

struct riscv_iommu_priv rv_iommu;

/**************** RISC-V IOMMU specific functions ****************/

/**
 *  Read and check IOMMU caps
 */
static void rv_iommu_check_features(void)
{
    unsigned version =
        bit64_extract(rv_iommu.caps, RV_IOMMU_CAPS_VERSION_OFF, RV_IOMMU_CAPS_VERSION_LEN);

    if (version != RV_IOMMU_SUPPORTED_VERSION) {
        ERROR("RV_IOMMU: Unsupported version: %d", version);
    }

    if (!(rv_iommu.caps & RV_IOMMU_CAPS_SV39X4_BIT)) {
        ERROR("RV IOMMU: Sv39x4 not supported");
    }

    unsigned igs = bit64_extract(rv_iommu.caps, RV_IOMMU_CAPS_IGS_OFF, RV_IOMMU_CAPS_IGS_LEN);
    if (!igs) {
        WARNING("RV IOMMU: WSI generation not supported. MSI generation is currently not supported "
                "by Bao");
    }
}

/**
 *  RISC-V IOMMU Fault Queue IRQ handler.
 */
void rv_iommu_fq_irq_handler(irqid_t irq_id)
{
    UNUSED_ARG(irq_id);

    // Read ipsr.fip
    uint32_t ipsr = rv_iommu.hw.reg_ptr->ipsr;

    // Signal error if fip not set
    if (!(ipsr & RV_IOMMU_IPSR_FIP_BIT)) {
        ERROR("FQ IRQ handler triggered due to non-FQ interrupt");
    }

    // Read fqcsr error bits and report if any is set
    uint32_t fqcsr = rv_iommu.hw.reg_ptr->fqcsr;
    if (fqcsr & (RV_IOMMU_XQCSR_MF_BIT | RV_IOMMU_FQCSR_OF_BIT)) {
        if (fqcsr & RV_IOMMU_XQCSR_MF_BIT) {
            WARNING("RV IOMMU: FQ Memory Fault error!");
            // TODO: MF management
        }

        if (fqcsr & RV_IOMMU_FQCSR_OF_BIT) {
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

    while (fqh != fqt) {
        struct fq_entry record = rv_iommu.hw.fq[fqh];
        WARNING("RV IOMMU FQ: CAUSE: %d | DID: %d | iotval: %x | iotval2: %x",
            bit64_extract(record.tags, RV_IOMMU_FQ_CAUSE_OFF, RV_IOMMU_FQ_CAUSE_LEN),
            bit64_extract(record.tags, RV_IOMMU_FQ_DID_OFF, RV_IOMMU_FQ_DID_LEN), record.iotval,
            record.iotval2);
        fqh = (fqh + 1) & FQ_INDEX_MASK;
        // TODO: Translation faults management
    }

    // Update fqh
    rv_iommu.hw.reg_ptr->fqh = fqh;
}

/**
 *  Allocate one page to store first-level table virtual ptrs
 *  Indexed with DDI[1]
 */
void alloc_2lvl_vptrs(void)
{
    // 2^9 * 8 bytes per non-leaf entry = 4096 bytes (1 page)
    volatile uint64_t** lvl1_vaddr = (volatile uint64_t**)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
    memset((void*)lvl1_vaddr, 0, 0x1000);
    rv_iommu.hw.vddt_lvl1 = lvl1_vaddr;
}

/**
 *  Upgrade the IOMMU mode from 1LVL to 2LVL.
 *  Rearrange DDT and update ddtp
 */
void up_1lvl_to_2lvl(void)
{
    // As the IOMMU is in 1LVL mode, rv_iommu.hw.vddt_lvl0 (and thus the ddtp) register points to a
    // table that may have leaf entries in it (DCs).

    // 1. Allocate a new page to work as the root table
    uint64_t* new_root_vaddr = (uint64_t*)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
    memset((void*)new_root_vaddr, 0, 0x1000);

    // 2. Configure its first entry to point to the physical address of the table pointed by
    // rv_iommu.hw.vddt_lvl0
    paddr_t nl_paddr;
    mem_translate(&cpu()->as, (vaddr_t)rv_iommu.hw.vddt_lvl0, &nl_paddr);
    new_root_vaddr[0] = ((nl_paddr >> 2) & RV_IOMMU_DDT_NL_PPN_MASK) | RV_IOMMU_DC_VALID_BIT;

    // 3. Point rv_iommu.hw.vddt_lvl1[0] to the table pointed by rv_iommu.hw.vddt_lvl0 with the DCs
    // (now lvl1 table)
    rv_iommu.hw.vddt_lvl1[0] = rv_iommu.hw.vddt_lvl0;

    // 4. Point rv_iommu.hw.vddt_lvl0 to the new root table
    rv_iommu.hw.vddt_lvl0 = new_root_vaddr;

    // 5. Update ddtp with the base physical address of the new table pointed by
    // rv_iommu.hw.vddt_lvl0
    rv_iommu.iommu_mode = RV_IOMMU_DDTP_MODE_2LVL;

    paddr_t ddt_paddr;
    mem_translate(&cpu()->as, (vaddr_t)new_root_vaddr, &ddt_paddr);
    rv_iommu.hw.reg_ptr->ddtp = rv_iommu.iommu_mode | ((ddt_paddr >> 2) & RV_IOMMU_DDTP_PPN_MASK);
}

/*
 *  Allocate 512 pages to store second-level table virtual ptrs
 *  Indexed with DDI[2] DDI[1]
 */
void alloc_3lvl_vptrs(void)
{
    // 2^9 * 8 bytes per non-leaf entry = 4096 bytes (1 page)
    volatile uint64_t*** lvl2_vaddr = (volatile uint64_t***)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
    memset((void*)lvl2_vaddr, 0, 0x1000);

    // Allocate one page for each second-level table
    for (size_t i = 0; i < 512; i++) {
        volatile uint64_t** lvl2_vaddr_i =
            (volatile uint64_t**)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
        memset((void*)lvl2_vaddr_i, 0, 0x1000);
        lvl2_vaddr[i] = lvl2_vaddr_i;
    }

    rv_iommu.hw.vddt_lvl2 = lvl2_vaddr;
}

/**
 *  Upgrade the IOMMU mode from 2LVL to 3LVL.
 *  Rearrange DDT and update ddtp
 */
void up_2lvl_to_3lvl(void)
{
    // As the IOMMU is in 2LVL mode, rv_iommu.hw.vddt_lvl0 (and thus the ddtp) register points to
    // 512 tables that may have leaf entries in it (DCs).

    // 1. Allocate a new page to work as the root table
    uint64_t* new_root_vaddr = (uint64_t*)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
    memset((void*)new_root_vaddr, 0, 0x1000);

    // 2. Configure its first entry to point to the physical address of the table pointed by
    // rv_iommu.hw.vddt_lvl0
    paddr_t nl_paddr;
    mem_translate(&cpu()->as, (vaddr_t)rv_iommu.hw.vddt_lvl0, &nl_paddr);
    new_root_vaddr[0] = ((nl_paddr >> 2) & RV_IOMMU_DDT_NL_PPN_MASK) | RV_IOMMU_DC_VALID_BIT;

    // 3. Point rv_iommu.hw.vddt_lvl2[0][0..512-1] to the tables pointed by
    // rv_iommu.hw.vddt_lvl1[0..512-1] with the DCs (now lvl2 tables)
    for (size_t i = 0; i < (0x1000 / 8); i++) {
        rv_iommu.hw.vddt_lvl2[0][i] = rv_iommu.hw.vddt_lvl1[i];
    }

    // 4. Point rv_iommu.hw.vddt_lvl1[0] to the table pointed by rv_iommu.hw.vddt_lvl0 with the
    // non-leaf entries (now lvl1 table)
    rv_iommu.hw.vddt_lvl1[0] = rv_iommu.hw.vddt_lvl0;

    // 5. Point rv_iommu.hw.vddt_lvl0 to the new root table
    rv_iommu.hw.vddt_lvl0 = new_root_vaddr;

    // 6. Update ddtp with the base physical address of the new table pointed by
    // rv_iommu.hw.vddt_lvl0
    rv_iommu.iommu_mode = RV_IOMMU_DDTP_MODE_3LVL;

    paddr_t ddt_paddr;
    mem_translate(&cpu()->as, (vaddr_t)new_root_vaddr, &ddt_paddr);
    rv_iommu.hw.reg_ptr->ddtp = rv_iommu.iommu_mode | ((ddt_paddr >> 2) & RV_IOMMU_DDTP_PPN_MASK);
}

/**
 *  Determine supported IOMMU modes (number of DDT levels)
 *  Allocate memory for leaf and non-leaf DDT tables
 *  Program the IOMMU with the simplest supported mode
 *  Enable IOMMU
 */
void ddt_init(void)
{
    // Lock DDT
    rv_iommu.ddt_lock = SPINLOCK_INITVAL;

    // Determine supported modes (3LVL, 2LVL, 1LVL, BARE)
    uint64_t ddtp_mode = RV_IOMMU_DDTP_MODE_1LVL;
    uint64_t simplest_mode = 0;
    bool first = true;
    rv_iommu.supported_modes = 0;

    for (size_t i = 0; i < RV_IOMMU_DDTP_MODE_3LVL; i++) {
        // Probe ddtp register
        rv_iommu.hw.reg_ptr->ddtp = ddtp_mode;
        uint64_t ddtp_readback = rv_iommu.hw.reg_ptr->ddtp;

        if (ddtp_readback == ddtp_mode) {
            rv_iommu.supported_modes |= (1 << (i + 2));
            if (first) {
                first = false;
                simplest_mode = ddtp_mode; // save simplest mode
            }
        }

        (ddtp_mode)++;
    }

    // 1LVL, 2LVL and 3LVL not supported
    if (!simplest_mode) {
        // Probe ddtp register with Bare mode
        rv_iommu.hw.reg_ptr->ddtp = RV_IOMMU_DDTP_MODE_BARE;
        uint64_t ddtp_readback = rv_iommu.hw.reg_ptr->ddtp;

        if (ddtp_readback == RV_IOMMU_DDTP_MODE_BARE) {
            // No need to populate the DDT if IOMMU is in Bare mode
            WARNING("RV_IOMMU: Only Bare mode supported");
            rv_iommu.iommu_mode = RV_IOMMU_DDTP_MODE_BARE;
            return;
        } else {
            ERROR("RV_IOMMU: No valid IOMMU mode supported");
        }
    }

    // Save IOMMU mode
    rv_iommu.iommu_mode = simplest_mode;

    // Allocate memory for the DDT bitmap
    rv_iommu.ddt_bitmap = (ddt_bitmap_t)mem_alloc_page(512, SEC_HYP_GLOBAL, true);
    memset((void*)rv_iommu.ddt_bitmap, 0, 512 * 0x1000);

    // Simplest supported mode is 3LVL
    if (rv_iommu.iommu_mode >= RV_IOMMU_DDTP_MODE_3LVL) {
        alloc_3lvl_vptrs();
    }

    // Simplest supported mode is 2LVL
    if (rv_iommu.iommu_mode >= RV_IOMMU_DDTP_MODE_2LVL) {
        alloc_2lvl_vptrs();
    }

    vaddr_t ddt_vaddr = 0;

    // Allocate one page for the root table of the DDT
    ddt_vaddr = (vaddr_t)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
    memset((void*)ddt_vaddr, 0, 0x1000);
    rv_iommu.hw.vddt_lvl0 = (uint64_t*)ddt_vaddr;

    // Get physical address of the root table and configure ddtp
    paddr_t ddt_paddr;
    mem_translate(&cpu()->as, ddt_vaddr, &ddt_paddr);
    rv_iommu.hw.reg_ptr->ddtp = rv_iommu.iommu_mode | ((ddt_paddr >> 2) & RV_IOMMU_DDTP_PPN_MASK);
    // TODO: poll ddtp.busy
}

/**
 *  Initialize IOMMU hardware
 */
void rv_iommu_init(void)
{
    // Map register IF (4k)
    vaddr_t reg_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.iommu.base, NUM_PAGES(sizeof(struct riscv_iommu_regmap)));

    rv_iommu.hw.reg_ptr = (struct riscv_iommu_regmap*)reg_ptr;

    // Read caps register
    rv_iommu.caps = rv_iommu.hw.reg_ptr->caps;

    // Check caps
    rv_iommu_check_features();

    // Determine whether the IOMMU supports MSI translation
    rv_iommu.msi_support = ((rv_iommu.caps & RV_IOMMU_CAPS_MSI_FLAT_BIT) != 0);

    // Set fctl.WSI We will be first using WSI as IOMMU interrupt mechanism. Then MSIs will be
    // included
    rv_iommu.hw.reg_ptr->fctl = RV_IOMMU_FCTL_DEFAULT;

    // Configure interrupt vectors (icvec) We use a different vector for each interrupt source CQ
    // and FQ by now
    rv_iommu.hw.reg_ptr->icvec = RV_IOMMU_ICVEC_DEFAULT;

    // Clear all IP flags (ipsr)
    rv_iommu.hw.reg_ptr->ipsr = RV_IOMMU_IPSR_CLEAR;

    // TODO Allocate memory for CQ Configure cqb with queue size and base address. Clear cqt
    // Allocate IRQ for CQ Enable CQ (cqcsr)

    // Allocate memory for FQ (aligned to 4kiB)
    vaddr_t fq_vaddr = (vaddr_t)mem_alloc_page(NUM_PAGES(sizeof(struct fq_entry) * FQ_N_ENTRIES),
        SEC_HYP_GLOBAL, true);
    memset((void*)fq_vaddr, 0, sizeof(struct fq_entry) * FQ_N_ENTRIES);
    rv_iommu.hw.fq = (struct fq_entry*)fq_vaddr;

    // Configure fqb with queue size and base address. Clear fqh
    paddr_t fq_paddr;
    mem_translate(&cpu()->as, fq_vaddr, &fq_paddr);
    rv_iommu.hw.reg_ptr->fqb = FQ_LOG2SZ_1 | ((fq_paddr >> 2) & RV_IOMMU_XQB_PPN_MASK);
    rv_iommu.hw.reg_ptr->fqh = 0;

    // Allocate IRQ for FQ
    if (!interrupts_reserve(platform.arch.iommu.fq_irq_id, rv_iommu_fq_irq_handler)) {
        ERROR("Failed to reserve IOMMU FQ interrupt");
    }

    interrupts_cpu_enable(platform.arch.iommu.fq_irq_id, true);

    // Enable FQ (fqcsr)
    rv_iommu.hw.reg_ptr->fqcsr = RV_IOMMU_FQCSR_DEFAULT;
    // TODO: poll fqcsr.busy

    // Init DDT
    ddt_init();
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
    if (!(DDT_BITMAP_GET(rv_iommu.ddt_bitmap, dev_id))) {
        DDT_BITMAP_SET(rv_iommu.ddt_bitmap, dev_id);
        allocated = true;
    } else {
        allocated = false; // device_id already exists
    }

    spin_unlock(&rv_iommu.ddt_lock);
    return allocated;
}

/**
 *  Program DDT entry with base address of the root PT, VMID and translation configuration. Enable
 *  DC.
 *
 *  @dev_id:     device_id to index DDT
 *  @vm:         VM to which the device is being assigned
 *  @root_pt:    Base physical address of the root second-stage PT
 */
void rv_iommu_write_ddt(deviceid_t dev_id, struct vm* vm, paddr_t root_pt)
{
    spin_lock(&rv_iommu.ddt_lock);
    if (!(DDT_BITMAP_GET(rv_iommu.ddt_bitmap, dev_id))) {
        ERROR("IOMMU DC %d is not allocated", dev_id);
    }

    else {
        // Get DID indexes
        unsigned ddi_2 =
            (dev_id & (DDI_2_MASK_BASE | ((unsigned int)rv_iommu.msi_support << 15))) >>
            (DDI_2_BASE_OFF - (int)rv_iommu.msi_support);
        unsigned ddi_1 = (dev_id & (DDI_1_MASK_BASE >> (unsigned int)rv_iommu.msi_support)) >>
            (DDI_1_BASE_OFF - (int)rv_iommu.msi_support);
        unsigned ddi_0 = (dev_id & (DDI_0_MASK_BASE >> (unsigned int)rv_iommu.msi_support));

        // In bare mode there is no need to populate the DDT
        if (rv_iommu.iommu_mode == RV_IOMMU_DDTP_MODE_BARE) {
            return;
        }

        /*** Check whether we need to scale to a greater mode ***/

        // If the IOMMU is not in 3LVL mode and DDI[2] != 0, we need to scale to 3LVL
        if (ddi_2 && (rv_iommu.iommu_mode < RV_IOMMU_DDTP_MODE_3LVL)) {
            // Check if 3LVL is supported. Otherwise, raise error
            if (rv_iommu.supported_modes & (1 << RV_IOMMU_DDTP_MODE_3LVL)) {
                if (rv_iommu.iommu_mode == RV_IOMMU_DDTP_MODE_1LVL) {
                    // Scale from 1LVL to 2LVL
                    alloc_2lvl_vptrs();
                    up_1lvl_to_2lvl();
                }

                // Scale from 2LVL to 3LVL
                alloc_3lvl_vptrs();
                up_2lvl_to_3lvl();
            }

            else {
                ERROR("RV_IOMMU: Unsupported device_id width");
            }
        }

        // If the IOMMU is in 1LVL mode and DDI[1] != 0, we need to scale to 2LVL
        if (ddi_1 && (rv_iommu.iommu_mode < RV_IOMMU_DDTP_MODE_2LVL)) {
            // Check if 2LVL is supported. Otherwise, raise error
            if (rv_iommu.supported_modes & (1 << RV_IOMMU_DDTP_MODE_2LVL)) {
                // Scale from 1LVL to 2LVL
                alloc_2lvl_vptrs();
                up_1lvl_to_2lvl();
            }

            else {
                ERROR("RV_IOMMU: Unsupported device_id width");
            }
        }

        /*** Write non-leaf entries if needed ***/

        if (rv_iommu.iommu_mode >= RV_IOMMU_DDTP_MODE_2LVL) {
            // Get root index according to the IOMMU mode
            unsigned ddi_root =
                (rv_iommu.iommu_mode == RV_IOMMU_DDTP_MODE_3LVL) ? (ddi_2) : (ddi_1);

            // Allocate first-level table if it does not exist
            if (!rv_iommu.hw.vddt_lvl1[ddi_root]) {
                // Allocate a page of memory to use as the first-level table
                vaddr_t lvl1_vaddr = (vaddr_t)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
                memset((void*)lvl1_vaddr, 0, 0x1000);
                // Save base virtual address
                rv_iommu.hw.vddt_lvl1[ddi_root] = (uint64_t*)lvl1_vaddr;

                // Get physical address of the lvl1 table
                paddr_t lvl1_paddr;
                mem_translate(&cpu()->as, lvl1_vaddr, &lvl1_paddr);

                // Program root table entry with base physical address of the lvl1 table
                rv_iommu.hw.vddt_lvl0[ddi_root] =
                    ((lvl1_paddr >> 2) & RV_IOMMU_DDT_NL_PPN_MASK) | RV_IOMMU_DC_VALID_BIT;
            }

            if (rv_iommu.iommu_mode == RV_IOMMU_DDTP_MODE_3LVL) {
                // Allocate second-level table if it does not exist
                if (!rv_iommu.hw.vddt_lvl2[ddi_2][ddi_1]) {
                    // Allocate a page of memory to use as the second-level table for for DDI[2] and
                    // DDI[1]
                    vaddr_t lvl2_vaddr = (vaddr_t)mem_alloc_page(1, SEC_HYP_GLOBAL, true);
                    memset((void*)lvl2_vaddr, 0, 0x1000);
                    // Save base virtual address
                    rv_iommu.hw.vddt_lvl2[ddi_2][ddi_1] = (uint64_t*)lvl2_vaddr;

                    // Get physical address of the lvl2 table
                    paddr_t lvl2_paddr;
                    mem_translate(&cpu()->as, lvl2_vaddr, &lvl2_paddr);

                    // Program root table entry with base physical address of the lvl1 table
                    rv_iommu.hw.vddt_lvl1[ddi_2][ddi_1] =
                        ((lvl2_paddr >> 2) & RV_IOMMU_DDT_NL_PPN_MASK) | RV_IOMMU_DC_VALID_BIT;
                }
            }
        }

        /*** Write DC ***/

        // Get DC pointer
        struct ddt_entry* dc_ptr = NULL;
        switch (rv_iommu.iommu_mode) {
            case RV_IOMMU_DDTP_MODE_3LVL:
                dc_ptr = (struct ddt_entry*)(rv_iommu.hw.vddt_lvl2[ddi_2][ddi_1]);
                break;
            case RV_IOMMU_DDTP_MODE_2LVL:
                dc_ptr = (struct ddt_entry*)(rv_iommu.hw.vddt_lvl1[ddi_1]);
                break;
            case RV_IOMMU_DDTP_MODE_1LVL:
                dc_ptr = (struct ddt_entry*)rv_iommu.hw.vddt_lvl0;
                break;

            default:
                break;
        }

        // MSI translation supported. DC in extended format
        if (rv_iommu.msi_support) {
            // tc
            uint64_t tc = 0;
            tc |= RV_IOMMU_DC_VALID_BIT;
            dc_ptr[ddi_0].dw_1 = tc;

            // iohgatp
            uint64_t iohgatp = 0;
            iohgatp |= ((root_pt >> 12) & RV_IOMMU_DC_IOHGATP_PPN_MASK);
            iohgatp |= ((vm->id << RV_IOMMU_DC_IOHGATP_GSCID_OFF) & RV_IOMMU_DC_IOHGATP_GSCID_MASK);
            iohgatp |= RV_IOMMU_IOHGATP_SV39X4;
            dc_ptr[ddi_0].dw_2 = iohgatp;

            // Future work: ta, fsc, msiptp, msi_addr_mask, msi_addr_pattern
        }

        // MSI translation not supported: DC in base format
        else {
            // Even DCs occupy the first 32 bytes of each entry
            if (ddi_0 % 2 == 0) {
                // tc
                uint64_t tc = 0;
                tc |= RV_IOMMU_DC_VALID_BIT;
                dc_ptr[ddi_0 / 2].dw_1 = tc;

                // iohgatp
                uint64_t iohgatp = 0;
                iohgatp |= ((root_pt >> 12) & RV_IOMMU_DC_IOHGATP_PPN_MASK);
                iohgatp |=
                    ((vm->id << RV_IOMMU_DC_IOHGATP_GSCID_OFF) & RV_IOMMU_DC_IOHGATP_GSCID_MASK);
                iohgatp |= RV_IOMMU_IOHGATP_SV39X4;
                dc_ptr[ddi_0 / 2].dw_2 = iohgatp;

                // Future work: ta, fsc
            }

            // Odd DCs occupy the second 32 bytes of each entry
            else {
                // tc
                uint64_t tc = 0;
                tc |= RV_IOMMU_DC_VALID_BIT;
                dc_ptr[ddi_0 / 2].dw_5 = tc;

                // iohgatp
                uint64_t iohgatp = 0;
                iohgatp |= ((root_pt >> 12) & RV_IOMMU_DC_IOHGATP_PPN_MASK);
                iohgatp |=
                    ((vm->id << RV_IOMMU_DC_IOHGATP_GSCID_OFF) & RV_IOMMU_DC_IOHGATP_GSCID_MASK);
                iohgatp |= RV_IOMMU_IOHGATP_SV39X4;
                dc_ptr[ddi_0 / 2].dw_6 = iohgatp;

                // Future work: ta, fsc
            }
        }
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
    if (cpu_is_master() && platform.arch.iommu.base) {
        rv_iommu_init();
        return true;
    }

    return false;
}

/**
 * Initialize the DDT entry indexed by device_id for the given VM Configure corresponding DDT entry
 * with root PT base addr, VMID (GSCID) and device config
 *
 * @vm:     VM struct to which the device will be assigned.
 * @dev_id: device_id of the device to be added.
 *
 * @returns true on success, false on error.
 */
static bool iommu_vm_arch_add(struct vm* vm, deviceid_t dev_id)
{
    if (dev_id > 0) {
        // Check if device was already added to a VM
        if (rv_iommu_alloc_did(dev_id)) {
            paddr_t rootpt;
            // Translate root PT base address
            mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &rootpt);
            // Set DDT entry with root PT base address, VMID and configuration
            rv_iommu_write_ddt(dev_id, vm, rootpt);
        } else {
            INFO("RV IOMMU: Cannot add one device ID (%d) twice", dev_id);
            return false;
        }
    } else {
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
inline bool iommu_arch_vm_add_device(struct vm* vm, deviceid_t dev_id)
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
bool iommu_arch_vm_init(struct vm* vm, const struct vm_config* config)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(config);

    // For now there is no data to initialize
    return true;
}
