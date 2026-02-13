/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/smmuv2.h>
#include <arch/spinlock.h>
#include <bitmap.h>
#include <bit.h>
#include <arch/sysregs.h>
#include <platform.h>
#include <cpu.h>
#include <mem.h>

#define SME_MAX_NUM 128
#define CTX_MAX_NUM 128

struct smmu_hw {
    volatile struct smmu_glbl_rs0_hw* glbl_rs0;
    volatile struct smmu_glbl_rs1_hw* glbl_rs1;
    volatile struct smmu_cntxt_hw* cntxt;
};

struct smmu_priv {
    struct smmu_hw hw;

    /* For easier book keeping */
    spinlock_t sme_lock;
    size_t sme_num;
    BITMAP_ALLOC(sme_bitmap, SME_MAX_NUM);
    BITMAP_ALLOC(grp_bitmap, SME_MAX_NUM);

    spinlock_t ctx_lock;
    size_t ctx_num;
    BITMAP_ALLOC(ctxbank_bitmap, CTX_MAX_NUM);
};

struct smmu_priv smmu;

/**
 * Iterate stream match entries.
 *
 * @sme: starting point of the loop cursor
 */
#define smmu_for_each_sme(sme)                                                \
    for (size_t __bit = bitmap_get(smmu.sme_bitmap, sme); sme < smmu.sme_num; \
         __bit = bitmap_get(smmu.sme_bitmap, ++sme))                          \
        if (!__bit)                                                           \
            continue;                                                         \
        else

/**
 * Accessors inline functions.
 */
static inline bool smmu_sme_is_group(size_t sme)
{
    return bitmap_get(smmu.grp_bitmap, sme);
}

static inline size_t smmu_sme_get_ctx(size_t sme)
{
    return S2CR_CBNDX(smmu.hw.glbl_rs0->S2CR[sme]);
}

static inline streamid_t smmu_sme_get_id(size_t sme)
{
    return SMMU_SMR_ID(smmu.hw.glbl_rs0->SMR[sme]);
}

static inline streamid_t smmu_sme_get_mask(size_t sme)
{
    return SMMU_SMR_MASK(smmu.hw.glbl_rs0->SMR[sme]);
}

static void smmu_check_features(void)
{
    unsigned version =
        bit32_extract(smmu.hw.glbl_rs0->IDR7, SMMUV2_IDR7_MAJOR_OFF, SMMUV2_IDR7_MAJOR_LEN);
    if (version != 2) {
        ERROR("smmu unsupported version: %d", version);
    }

    if (!(smmu.hw.glbl_rs0->IDR0 & SMMUV2_IDR0_S2TS_BIT)) {
        ERROR("smmuv2 does not support 2nd stage translation");
    }

    if (!(smmu.hw.glbl_rs0->IDR0 & SMMUV2_IDR0_SMS_BIT)) {
        ERROR("smmuv2 does not support stream match");
    }

    /**
     * TODO: the most common smmuv2 implementation (mmu-500) does not provide ptw coherency. So we
     * must add some mechanism software-managed coherency mechanism for the vms using the smmu
     * according to the result of this feature test.
     */
    if (!(smmu.hw.glbl_rs0->IDR0 & SMMUV2_IDR0_CTTW_BIT)) {
        WARNING("smmuv2 does not support coherent page table walks");
    }

    if (!(smmu.hw.glbl_rs0->IDR0 & SMMUV2_IDR0_BTM_BIT)) {
        ERROR("smmuv2 does not support tlb maintenance broadcast");
    }

    if (!(smmu.hw.glbl_rs0->IDR2 & SMMUV2_IDR2_PTFSv8_4kB_BIT)) {
        ERROR("smmuv2 does not support 4kb page granule");
    }

    size_t pasize = bit32_extract(smmu.hw.glbl_rs0->IDR2, SMMUV2_IDR2_OAS_OFF, SMMUV2_IDR2_OAS_LEN);
    size_t ipasize =
        bit32_extract(smmu.hw.glbl_rs0->IDR2, SMMUV2_IDR2_IAS_OFF, SMMUV2_IDR2_IAS_LEN);

    if (pasize < parange) {
        ERROR("smmuv2 does not support the full available pa range");
    } else if (ipasize < parange) {
        ERROR("smmuv2 does not support the full available ipa range");
    }
}

void smmu_init(void)
{
    /*
     * Alloc pages for global address space.
     *
     * Map the first 4k so we can read all the info we need to further allocate smmu registers.
     */
    vaddr_t smmu_glbl_rs0 = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.smmu.base, NUM_PAGES(sizeof(struct smmu_glbl_rs0_hw)));

    smmu.hw.glbl_rs0 = (struct smmu_glbl_rs0_hw*)smmu_glbl_rs0;

    size_t pg_size = smmu.hw.glbl_rs0->IDR1 & SMMUV2_IDR1_PAGESIZE_BIT ? 0x10000 : 0x1000;
    size_t num_page = 1UL << (bit32_extract(smmu.hw.glbl_rs0->IDR1, SMMUV2_IDR1_NUMPAGEDXB_OFF,
                                  SMMUV2_IDR1_NUMPAGEDXB_LEN) +
                          1);
    size_t ctx_bank_num =
        bit32_extract(smmu.hw.glbl_rs0->IDR1, SMMUV2_IDR1_NUMCB_OFF, SMMUV2_IDR1_NUMCB_LEN);

    vaddr_t smmu_glbl_rs1 = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.smmu.base + pg_size, NUM_PAGES(sizeof(struct smmu_glbl_rs1_hw)));

    vaddr_t smmu_cntxt = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.smmu.base + (num_page * pg_size), NUM_PAGES(pg_size * ctx_bank_num));

    smmu.hw.glbl_rs1 = (struct smmu_glbl_rs1_hw*)smmu_glbl_rs1;
    smmu.hw.cntxt = (struct smmu_cntxt_hw*)smmu_cntxt;

    /* Everything is mapped. Initialize book-keeping data. */

    smmu_check_features();

    smmu.ctx_lock = SPINLOCK_INITVAL;
    smmu.ctx_num = ctx_bank_num;
    bitmap_clear_consecutive(smmu.ctxbank_bitmap, 0, smmu.ctx_num);

    smmu.sme_lock = SPINLOCK_INITVAL;
    smmu.sme_num = smmu.hw.glbl_rs0->IDR0 & SMMUV2_IDR0_MASK;
    bitmap_clear_consecutive(smmu.sme_bitmap, 0, smmu.sme_num);
    bitmap_clear_consecutive(smmu.grp_bitmap, 0, smmu.sme_num);

    /* Clear random reset state. */
    smmu.hw.glbl_rs0->GFSR = smmu.hw.glbl_rs0->GFSR;
    smmu.hw.glbl_rs0->NSGFSR = smmu.hw.glbl_rs0->NSGFSR;

    for (size_t i = 0; i < smmu.sme_num; i++) {
        smmu.hw.glbl_rs0->SMR[i] = 0;
    }

    for (size_t i = 0; i < smmu.ctx_num; i++) {
        smmu.hw.cntxt[i].SCTLR = 0;
        smmu.hw.cntxt[i].FSR = ~0U;
    }

    /* Enable IOMMU. */
    uint32_t cr0 = smmu.hw.glbl_rs0->CR0;
    cr0 = SMMUV2_CR0_CLEAR(cr0);
    cr0 |= SMMUV2_CR0_USFCFG | SMMUV2_CR0_SMCFCFG;
    cr0 &= ~SMMUV2_CR0_CLIENTPD;
    smmu.hw.glbl_rs0->CR0 = cr0;
}

ssize_t smmu_alloc_ctxbnk(void)
{
    spin_lock(&smmu.ctx_lock);
    /* Find a free context bank. */
    ssize_t nth = bitmap_find_nth(smmu.ctxbank_bitmap, smmu.ctx_num, 1, 0, BITMAP_NOT_SET);
    if (nth >= 0) {
        bitmap_set(smmu.ctxbank_bitmap, (size_t)nth);
    }
    spin_unlock(&smmu.ctx_lock);

    return nth;
}

static size_t smmu_cb_ttba_offset(size_t t0sz)
{
    size_t offset = 12;

    if (parange_table[parange] < 44) {
        /* SMMUV2_TCR_SL0_1 */
        if (t0sz >= 21 && t0sz <= 33) {
            offset = 37 - t0sz;
        }
    } else {
        /* SMMUV2_TCR_SL0_0 */
        if (t0sz >= 16 && t0sz <= 24) {
            offset = 28 - t0sz;
        }
    }

    return offset;
}

void smmu_write_ctxbnk(size_t ctx_id, paddr_t root_pt, asid_t vm_id)
{
    spin_lock(&smmu.ctx_lock);
    if (!bitmap_get(smmu.ctxbank_bitmap, ctx_id)) {
        ERROR("smmu ctx %d is already allocated", ctx_id);
    } else {
        /* Set type as stage 2 only. */
        smmu.hw.glbl_rs1->CBAR[ctx_id] = SMMUV2_CBAR_VMID(vm_id);
        smmu.hw.glbl_rs1->CBA2R[ctx_id] = SMMUV2_CBAR_VA64;

        /**
         * This should closely match to the VTCR configuration set up in vmm_arch_init as we're
         * sharing page table between the VM and its smmu context.
         */
        uint32_t tcr = ((parange << SMMUV2_TCR_PS_OFF) & SMMUV2_TCR_PS_MSK);
        size_t t0sz = 64 - parange_table[parange];
        tcr |= SMMUV2_TCR_TG0_4K;
        tcr |= SMMUV2_TCR_ORGN0_WB_RA_WA;
        tcr |= SMMUV2_TCR_IRGN0_WB_RA_WA;
        tcr |= (uint32_t)SMMUV2_TCR_T0SZ(t0sz);
        tcr |= SMMUV2_TCR_SH0_IS;
        tcr |= ((parange_table[parange] < 44) ? SMMUV2_TCR_SL0_1 : SMMUV2_TCR_SL0_0);
        smmu.hw.cntxt[ctx_id].TCR = tcr;
        smmu.hw.cntxt[ctx_id].TTBR0 = root_pt & SMMUV2_CB_TTBA(smmu_cb_ttba_offset(t0sz));

        uint32_t sctlr = smmu.hw.cntxt[ctx_id].SCTLR;
        sctlr = SMMUV2_SCTLR_CLEAR(sctlr);
        sctlr |= SMMUV2_SCTLR_DEFAULT;
        smmu.hw.cntxt[ctx_id].SCTLR |= sctlr;
    }
    spin_unlock(&smmu.ctx_lock);
}

ssize_t smmu_alloc_sme(void)
{
    spin_lock(&smmu.sme_lock);
    /* Find a free sme. */
    ssize_t nth = bitmap_find_nth(smmu.sme_bitmap, smmu.sme_num, 1, 0, BITMAP_NOT_SET);
    if (nth >= 0) {
        bitmap_set(smmu.sme_bitmap, (size_t)nth);
    }
    spin_unlock(&smmu.sme_lock);

    return nth;
}

/*
 * When adding a new stream match entry there are a two different cases:
 *
 *      1. sme is a group;
 *      2. sme is a device.
 *
 * Groups can be merged together if one is found to be inclusive or equal of the other.
 *
 * Devices can be added (i.e. merged into) a group, but not together.
 *
 * This function searches for existing smes that are compatible for merging with the new sme,
 * raising an ERROR when conflicting attributes are found.
 */
bool smmu_compatible_sme_exists(streamid_t mask, streamid_t id, size_t ctx, bool group)
{
    bool included = false;
    size_t sme = 0;

    spin_lock(&smmu.sme_lock);
    smmu_for_each_sme(sme)
    {
        streamid_t sme_mask = smmu_sme_get_mask(sme);
        streamid_t mask_r = mask & sme_mask;
        streamid_t diff_id = (smmu_sme_get_id(sme) ^ id) & ~(mask | sme_mask);

        if (!diff_id) {
            /* Only group-to-group or device-to-group can be merged */
            if (((group || smmu_sme_is_group(sme)) && (mask_r == mask || mask_r == sme_mask)) &&
                ctx == smmu_sme_get_ctx(sme)) {
                /* Compatible entry found.
                 *
                 * If the new entry includes an existing one, there is the possibility that it will
                 * include other existing entries, it is therefore necessary to remove the existing
                 * entry and keep searching.
                 */
                if (mask > sme_mask) {
                    bitmap_clear(smmu.sme_bitmap, sme);
                } else {
                    included = true;
                    break;
                }

            } else {
                ERROR("SMMU sme conflict");
            }
        }
    }
    spin_unlock(&smmu.sme_lock);

    return included;
}

void smmu_write_sme(size_t sme, streamid_t mask, streamid_t id, bool group)
{
    spin_lock(&smmu.sme_lock);
    if (!bitmap_get(smmu.sme_bitmap, sme)) {
        ERROR("smmu: trying to write unallocated sme %d", sme);
    } else {
        smmu.hw.glbl_rs0->SMR[sme] = mask << SMMU_SMR_MASK_OFF;
        smmu.hw.glbl_rs0->SMR[sme] |= id & SMMU_ID_MSK;
        smmu.hw.glbl_rs0->SMR[sme] |= SMMUV2_SMR_VALID;

        if (group) {
            bitmap_set(smmu.grp_bitmap, sme);
        }
    }
    spin_unlock(&smmu.sme_lock);
}

void smmu_write_s2c(size_t sme, size_t ctx_id)
{
    spin_lock(&smmu.sme_lock);
    if (!bitmap_get(smmu.ctxbank_bitmap, ctx_id)) {
        ERROR("smmu: trying to write unallocated s2c %d", ctx_id);
    } else if (!bitmap_get(smmu.sme_bitmap, sme)) {
        ERROR("smmu: trying to bind unallocated sme %d", sme);
    } else {
        /* Initial contex is a translation context. */
        uint32_t s2cr = smmu.hw.glbl_rs0->S2CR[sme];

        s2cr = S2CR_CLEAR(s2cr);
        s2cr |= S2CR_DFLT;
        s2cr |= (uint32_t)(ctx_id & S2CR_CBNDX_MASK);

        smmu.hw.glbl_rs0->S2CR[sme] = s2cr;
    }
    spin_unlock(&smmu.sme_lock);
}
