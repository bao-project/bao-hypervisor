/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/smmuv3.h>
#include <arch/spinlock.h>
#include <bitmap.h>
#include <bit.h>
#include <arch/sysregs.h>
#include <platform.h>

// Use a 4kiB page of memory for the ST
// If a (non-embedded) SMMU implementation supports less than 64 STEs,
//      the max number of STEs supported is selected
#define ST_N_ENTRIES     (64)

#define EVENTQ_N_ENTRIES (32)

// Delay to ack register writes
#define ACK_DELAY        (10000)

struct smmuv3_hw {
    volatile struct smmuv3_regmap_p0_hw* regmap_p0;
    volatile struct smmuv3_regmap_p1_hw* regmap_p1;
    volatile struct smmuv3_st_hw* st;
    volatile struct smmuv3_eventq_hw* eventq;
};

struct smmuv3_priv {
    struct smmuv3_hw hw;

    /* For easier book keeping */
    spinlock_t st_lock;
    size_t st_num;
    BITMAP_ALLOC(st_bitmap, ST_N_ENTRIES);
};

struct smmuv3_priv smmuv3;

uint16_t log2(uint32_t n)
{
    uint16_t log_val = -1;

    if (n == 0) {
        return 0;
    }

    while (n) {
        log_val++;
        n >>= 1;
    }

    return log_val;
}

// Check capabilities
static void smmuv3_check_capabilities()
{
    unsigned major_version = 0;
    unsigned tt_format = 0;
    unsigned sid_max_width = 0;
    size_t pa_size = 0;

    // Check major version
    major_version =
        bit32_extract(smmuv3.hw.regmap_p0->AIDR, SMMUV3_AIDR_MAJOR_OFF, SMMUV3_AIDR_MAJOR_LEN);
    if (major_version != 3) {
        ERROR("SMMU unsupported version: %d", major_version);
    }

    // Stage-2 translation support
    if (!(smmuv3.hw.regmap_p0->IDR0 & SMMUV3_IDR0_S2P_BIT)) {
        ERROR("This SMMU implementation does not support Stage-2 translation");
    }

    // Translation Table format (AArch<XX>)
    // TODO: Confirm format of target platform
    tt_format = bit32_extract(smmuv3.hw.regmap_p0->IDR0, SMMUV3_IDR0_TTF_OFF, SMMUV3_IDR0_TTF_LEN);
    if (!(tt_format & (unsigned)0x2)) {
        ERROR("AArch64 not suported by this SMMU implementation");
    }

    // Check coherent access support
    if (!(smmuv3.hw.regmap_p0->IDR0 & SMMUV3_IDR0_COHACC_BIT)) {
        ERROR("This SMMU implementation does not support coherent memory accesses");
    }

    // Check broadcast TLB maintenance support
    if (!(smmuv3.hw.regmap_p0->IDR0 & SMMUV3_IDR0_BTM_BIT)) {
        ERROR("This SMMU implementation does not support broadcast TLB maintenance");
    }

    // VMID support
    if (!(smmuv3.hw.regmap_p0->IDR0 & SMMUV3_IDR0_VMW_BIT)) {
        ERROR("This SMMU implementation does not support VMID matching");
    }

    // 16-bit VMID support
    if (!(smmuv3.hw.regmap_p0->IDR0 & SMMUV3_IDR0_VMID16_BIT)) {
        WARNING("This SMMU implementation only supports VMIDs up to 8bits");
    }

    // Check max width of the streamID
    // At minimum we should have as many STE entries as DMAs attached to the platform
    sid_max_width =
        bit32_extract(smmuv3.hw.regmap_p0->IDR1, SMMUV3_IDR1_SIDSIZE_OFF, SMMUV3_IDR1_SIDSIZE_LEN);
    if ((1 << sid_max_width) < config->platform.dev_num) {
        ERROR("Insufficient STEs for this platform: %d", (1 << sid_max_width));
    }

    pa_size = bit32_extract(smmuv3.hw.regmap_p0->IDR5, SMMUV3_IDR5_OAS_OFF, SMMUV3_IDR5_OAS_LEN);

    if (pa_size < parange) {
        ERROR("This SMMU implementation does not support the full available PA range");
    }

    // Check translation granularity
    if (!(smmuv3.hw.regmap_p0->IDR5 & SMMUV3_IDR5_GRAN4K_BIT)) {
        ERROR("This SMMU implementation does not support 4kiB translation granularity");
    }
}

/**
 * Init and enable ARM SMMUv3.
 */
void smmuv3_init()
{
    unsigned evtq_max_sz = 0;
    unsigned evtq_sz = 0;
    uint8_t ack = 0;

    // # Map register IF
    //  For now, we only map the first 4k of Page 0, as we do not use the remaining registers
    vaddr_t smmuv3_regmap_p0 = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.smmu.base, NUM_PAGES(sizeof(struct smmuv3_regmap_p0_hw)));

    smmuv3.hw.regmap_p0 = (struct smmuv3_regmap_p0_hw*)smmuv3_regmap_p0;

    // Page 1
    vaddr_t smmuv3_regmap_p1 = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.smmu.base, NUM_PAGES(sizeof(struct smmuv3_regmap_p1_hw)));

    smmuv3.hw.regmap_p1 = (struct smmuv3_regmap_p1_hw*)smmuv3_regmap_p1;

    // # Check capabilities
    smmuv3_check_capabilities();

    // # Clear Errors/Interrupts
    smmuv3.hw.regmap_p0->GERROR_N = smmuv3.hw.regmap_p0->GERROR;
    // TODO: Wired-signaled interrupt mechanism is implementation-defined. Check for WSI support and
    // clear IP bits if present.

    // # Configure Fault/Event Queue
    //  Check whether queues are stored internally within the SMMU
    if (smmuv3.hw.regmap_p0->IDR1 & SMMUV3_IDR1_QUEUES_PRESET_BIT) {
        // EVENTQ is stored internally within the SMMU. Base register is fixed
    }

    else {
        // EVENTQ is stored in main memory. We need to allocate and configure base register

        // Check max number of EVTQ entries
        evtq_max_sz = bit32_extract(smmuv3.hw.regmap_p0->IDR1, SMMUV3_IDR1_EVENTQS_OFF,
            SMMUV3_IDR1_EVENTQS_LEN);
        evtq_sz = (evtq_max_sz < EVENTQ_N_ENTRIES) ? (evtq_max_sz) : (EVENTQ_N_ENTRIES);

        // Allocate memory for the EVENTQ
        vaddr_t eventq_vaddr =
            (vaddr_t)mem_alloc_page(NUM_PAGES(sizeof(struct smmuv3_eventq_entry) * evtq_sz),
                SEC_HYP_GLOBAL, true);
        memset((void*)eventq_vaddr, 0, sizeof(struct smmuv3_eventq_entry) * evtq_sz);
        smmuv3.hw.eventq = (struct smmuv3_eventq_entry*)eventq_vaddr;

        // Set EVENTQ size
        uint32_t eventq_base = 0;
        eventq_base |= log2(evtq_sz) & SMMUV3_EVENTQ_BASE_LOG2SZ_MASK;

        // Initialize base pointer
        paddr_t eventq_paddr;
        mem_translate(&cpu()->as, eventq_vaddr, &eventq_paddr);
        eventq_base |=
            ((eventq_paddr << SMMUV3_EVENTQ_BASE_ADDR_OFF) & SMMUV3_EVENTQ_BASE_ADDR_MASK);
        smmuv3.hw.regmap_p0->EVENTQ_BASE = eventq_base;
    }

    // Initialize index registers
    smmuv3.hw.regmap_p1->EVENTQ_PROD = 0;
    smmuv3.hw.regmap_p1->EVENTQ_CONS = 0;

    // Enable EVENTQ and global interrupts
    smmuv3.hw.regmap_p0->IRQ_CTRL = (SMMUV3_IRQCTRL_EVENTQ_BIT | SMMUV3_IRQCTRL_GERROR_BIT);

    // Ensure that interrupts were enabled
    ack = 0;
    for (size_t i = 0; i < ACK_DELAY; i++) {
        if (smmuv3.hw.regmap_p0->IRQ_CTRL_ACK == smmuv3.hw.regmap_p0->IRQ_CTRL) {
            ack = 1;
            break;
        }
    }
    if (!ack) {
        WARNING("Could not enable Global and EVENTQ interrupts");
    }

    // Enable fault queue
    smmuv3.hw.regmap_p0->CR0 |= SMMUV3_CR0_EVENTQEN_BIT;

    // Confirm that the EVENTQ was enabled
    ack = 0;
    for (size_t i = 0; i < ACK_DELAY; i++) {
        if (smmuv3.hw.regmap_p0->CR0_ACK == smmuv3.hw.regmap_p0->CR0) {
            ack = 1;
            break;
        }
    }
    if (!ack) {
        WARNING("Could not enable the EVENTQ");
    }

    // # Issue commands to invalidate all cached configuration and TLB entries
    /*
        Since we do not perform invalidations in Bao, it may not be necessary to perform this step.
        However, invalidation of all non-secure TLB information can be achieved using
       CMD_TLBI_EL2_ALL and CMD_TLBI_NSNH_ALL commands
    */

    // # Configure Stream Table registers
    //  Check whether the Stream Table is stored internally within the SMMU
    if (smmuv3.hw.regmap_p0->IDR1 & SMMUV3_IDR1_TABLES_PRESET_BIT) {
        // Stream Table is embedded within the SMMU. We only need to know the size
        smmuv3.st_num = (1 << bit32_extract(smmuv3.hw.regmap_p0->STRTAB_BASE_CFG,
                             SMMUV3_STRTAB_BASE_CFG_LOG2SZ_OFF, SMMUV3_STRTAB_BASE_CFG_LOG2SZ_LEN));
    }

    else {
        // ST is stored in main memory

        // Check max number of STEs supported
        size_t max_num_ste = (1 << bit32_extract(smmuv3.hw.regmap_p0->IDR1, SMMUV3_IDR1_SIDSIZE_OFF,
                                  SMMUV3_IDR1_SIDSIZE_LEN));
        smmuv3.st_num = (max_num_ste < ST_N_ENTRIES) ? (max_num_ste) : (ST_N_ENTRIES);

        // Allocate a page of memory for the Stream Table
        vaddr_t st_vaddr =
            (vaddr_t)mem_alloc_page(NUM_PAGES(sizeof(struct smmuv3_ste) * smmuv3.st_num),
                SEC_HYP_GLOBAL, true);
        // Clear entries
        memset((void*)st_vaddr, 0, sizeof(struct smmuv3_ste) * smmuv3.st_num);
        smmuv3.hw.st = (struct smmuv3_ste*)st_vaddr;

        // Config STRTAB_BASE with physical base address of the ST in memory
        paddr_t st_paddr;
        mem_translate(&cpu()->as, st_vaddr, &st_paddr);
        smmuv3.hw.regmap_p0->STRTAB_BASE =
            ((st_paddr << SMMUV3_STRTAB_BASE_ADDR_OFF) & SMMUV3_STRTAB_BASE_ADDR_MASK);

        // Config Stream Table format and size
        uint32_t st_config = 0;
        st_config |= log2(smmuv3.st_num) & SMMUV3_STRTAB_BASE_CFG_LOG2SZ_MASK;
        st_config |= SMMUV3_STRTAB_BASE_CFG_FMT_LINEAR & SMMUV3_STRTAB_BASE_CFG_FMT_MASK;
        smmuv3.hw.regmap_p0->STRTAB_BASE_CFG = st_config;
    }

    // Init ST bitmap
    smmuv3.st_lock = SPINLOCK_INITVAL;
    bitmap_clear_consecutive(smmuv3.st_bitmap, 0, smmuv3.st_num);

    // # Configure other relevant registers
    //  We have to determine the reset value of SMMU_GBPA.ABORT
    if (smmuv3.hw.regmap_p0->GBPA & SMMUV3_GBPA_ABORT_BIT) {
        WARNING("SMMU_GBPA.ABORT is clear by default. This allows incoming transactions 
                    to bypass the SMMU before it has been initialized");
    }

    // Enable recording of C_BAD_STREAMID in the EVENTQ
    smmuv3.hw.regmap_p0->CR2 |= SMMUV3_CR2_RECINVSID_BIT;

    // # Enable the SMMU
    smmuv3.hw.regmap_p0->CR0 |= SMMUV3_CR0_SMMUEN_BIT;

    // Confirm that the SMMU was enabled
    ack = 0;
    for (size_t i = 0; i < ACK_DELAY; i++) {
        if (smmuv3.hw.regmap_p0->CR0_ACK == smmuv3.hw.regmap_p0->CR0) {
            ack = 1;
            break;
        }
    }
    if (!ack) {
        ERROR("Could not enable the SMMU");
    }
}

/**
 * Allocate Stream Table Entry in the ST bitmap.
 *
 * @sid: StreamID index to select STE
 *
 * @returns true on success, false on error
 */
bool smmuv3_alloc_ste(streamid_t sid)
{
    bool allocated;
    spin_lock(&smmuv3.st_lock);

    // Check whether the STE is already allocated
    if (!bitmap_get(smmuv3.st_bitmap, sid)) {
        bitmap_set(smmuv3.st_bitmap, sid);
        allocated = true;
    } else {
        allocated = false; // StreamID is already allocated
    }

    spin_unlock(&smmuv3.st_lock);
    return allocated;
}

/**
 * Configure STE with base address of the root PT, VMID and translation configuration. Enable STE.
 *
 * @sid:        StreamID to index ST
 * @vm:         VM to which the device is being assigned
 * @root_pt:    Base physical address of the root second-stage PT
 */
void smmuv3_write_ste(streamid_t sid, struct vm* vm, paddr_t root_pt)
{
    spin_lock(&smmuv3.st_lock);
    if (!bitmap_get(smmuv3.st_bitmap, sid)) {
        ERROR("Trying to configure STE %d, which is not allocated", sid);
    } else {
        // Configure STE
        // Stage-1 context fields
        uint64_t s1_ctx = 0;
        s1_ctx |= SMMUV3_STE_VALID_BIT;
        s1_ctx |= SMMUV3_STE_CONFIG_S2ONLY;
        smmuv3.hw.st[sid].s1_ctx = s1_ctx;

        // Translation control
        uint32_t tc = 0;
        smmuv3.hw.st[sid].tc = tc;

        // Memory attributes
        uint32_t memattr = 0;
        // memattr |= SMMUV3_STE_MTCFG_BIT;         // replace incoming cacheability
        // memattr |= SMMUV3_STE_MEMATTR_IWB_OWB;   // Inner and outer WB cacheable
        // memattr |= SMMUV3_STE_ALLOCCFG_RA_WA;    // Write/Read Allocate, non-transient
        // memattr |= SMMUV3_STE_SHCFG_INNSH;       // Inner shareable
        memattr |= SMMUV3_STE_SHCFG_USEIN; // Use incoming shareability
        smmuv3.hw.st[sid].memattr = memattr;

        // VMID
        uint32_t s2vmid = 0;
        s2vmid |= ((vm->id << SMMUV3_STE_S2VMID_OFF) & SMMUV3_STE_S2VMID_MASK);
        smmuv3.hw.st[sid].s2vmid = s2vmid;

        // Stage-2 config
        uint32_t s2_cfg = 0;
        size_t t0sz = 64 - parange_table[parange]; // {32, 28, 24, 22, 20, 16}
        s2_cfg |= ((t0sz << SMMUV3_STE_S2T0SZ_OFF) & SMMUV3_STE_S2T0SZ_MASK);
        s2_cfg |= |=
            ((parange_table[parange] < 44) ? SMMUV3_STE_S2SL0_LVL1 : SMMUV3_STE_S2SL0_LVL0);
        s2_cfg |= SMMUV3_STE_S2IR0_WB_RA_WA; // Inner region cacheability for stage-2
        s2_cfg |= SMMUV3_STE_S2OR0_WB_RA_WA; // Outer region cacheability for stage-2
        s2_cfg |= SMMUV3_STE_S2SH0_INNSH;    // Shareability for stage-2
        s2_cfg |= ((parange << SMMUV3_STE_S2PS_OFF) & SMMUV3_STE_S2PS_MASK); // PA size
        // TODO: Check target platform format
        s2_cfg |= SMMUV3_STE_S2AA64_BIT; // Stage-2 translation table is AArch64
        s2_cfg |= SMMUV3_STE_S2R_BIT;    // Stage-2 record fault model
        smmuv3.hw.st[sid].s2_cfg = s2_cfg;

        // Stage-2 Translation Table
        uint64_t s2_ttb = 0;
        s2_ttb |= (((root_pt >> 4) << SMMUV3_STE_S2TTB_OFF) & SMMUV3_STE_S2TTB_MASK);
        smmuv3.hw.st[sid].s2_ttb = s2_ttb;

        // Remaining fields are ignored
        smmuv3.hw.st[sid].partid = 0;
        smmuv3.hw.st[sid].sec_cfg = 0;
        smmuv3.hw.st[sid].vms_ptr = 0;
        smmuv3.hw.st[sid].sec_s2ttb = 0;
        smmuv3.hw.st[sid].__res0 = 0;

        // TODO:
        // Stall fault model ?
        // Configure first-stage translation. Second-stage only by now
    }
    spin_unlock(&smmuv3.st_lock);
}
