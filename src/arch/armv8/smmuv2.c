/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <arch/smmuv2.h>
#include <arch/spinlock.h>
#include <bitmap.h>
#include <bit.h>
#include <arch/sysregs.h>

#define SME_MAX_NUM 128
#define CTX_MAX_NUM 128

typedef struct {
    volatile smmu_glbl_rs0_t *glbl_rs0;
    volatile smmu_glbl_rs1_t *glbl_rs1;
    volatile smmu_cntxt_t *cntxt;
} smmu_hw;

typedef struct {
    smmu_hw hw;

    /* For easier book keeping */
    spinlock_t sme_lock;
    uint32_t sme_num;
    BITMAP_ALLOC(sme_bitmap, SME_MAX_NUM);
    BITMAP_ALLOC(grp_bitmap, SME_MAX_NUM);

    spinlock_t ctx_lock;
    int32_t ctx_num;
    BITMAP_ALLOC(ctxbank_bitmap, CTX_MAX_NUM);
} smmu_priv_t;

smmu_priv_t smmu;

/**
 * Iterate stream match entries.
 *
 * @sme: starting point of the loop cursor
 */
#define smmu_for_each_sme(sme)                                             \
    for (int __bit = bitmap_get(smmu.sme_bitmap, sme); sme < smmu.sme_num; \
         __bit = bitmap_get(smmu.sme_bitmap, ++sme))                       \
        if (!__bit)                                                        \
            continue;                                                      \
        else

/**
 * Accessors inline functions.
 */
inline bool smmu_sme_is_group(uint32_t sme)
{
    return bitmap_get(smmu.grp_bitmap, sme);
}

inline uint32_t smmu_sme_get_ctx(uint32_t sme)
{
    return S2CR_CBNDX(smmu.hw.glbl_rs0->S2CR[sme]);
}

inline uint16_t smmu_sme_get_id(uint32_t sme)
{
    return SMMU_SMR_ID(smmu.hw.glbl_rs0->SMR[sme]);
}

inline uint16_t smmu_sme_get_mask(uint32_t sme)
{
    return SMMU_SMR_MASK(smmu.hw.glbl_rs0->SMR[sme]);
}

static void smmu_check_features()
{
    int version = bit_extract(smmu.hw.glbl_rs0->IDR7, SMMUV2_IDR7_MAJOR_OFF,
                              SMMUV2_IDR7_MAJOR_LEN);
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
     * TODO: the most common smmuv2 implementation (mmu-500) does not provide
     * ptw coherency. So we must add some mechanism software-managed
     * coherency mechanism for the vms using the smmu according to the
     * result of this feature test.
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

    int pasize = bit_extract(smmu.hw.glbl_rs0->IDR2, SMMUV2_IDR2_OAS_OFF,
                             SMMUV2_IDR2_OAS_LEN);
    int ipasize = bit_extract(smmu.hw.glbl_rs0->IDR2, SMMUV2_IDR2_IAS_OFF,
                              SMMUV2_IDR2_IAS_LEN);
    int parange = 0;
    parange = MRS(ID_AA64MMFR0_EL1);
    parange &= ID_AA64MMFR0_PAR_MSK;

    if (pasize < parange) {
        ERROR("smmuv2 does not support the full available pa range");
    } else if (ipasize < parange) {
        ERROR("smmuv2 does not support the full available ipa range");
    }
}

void smmu_init()
{
    /*
     * Alloc pages for global address space.
     *
     * Map the first 4k so we can read all the info we need to further
     * allocate smmu registers.
     */
    smmu_glbl_rs0_t *smmu_glbl_rs0 = mem_alloc_vpage(
        &cpu.as, SEC_HYP_GLOBAL, NULL, NUM_PAGES(sizeof(smmu_glbl_rs0_t)));
    mem_map_dev(&cpu.as, smmu_glbl_rs0, platform.arch.smmu.base,
                NUM_PAGES(sizeof(smmu_glbl_rs0_t)));

    uint32_t pg_size =
        smmu_glbl_rs0->IDR1 & SMMUV2_IDR1_PAGESIZE_BIT ? 0x10000 : 0x1000;
    uint32_t num_page =
        1ULL << (bit_extract(smmu_glbl_rs0->IDR1, SMMUV2_IDR1_NUMPAGEDXB_OFF,
                             SMMUV2_IDR1_NUMPAGEDXB_LEN) +
                 1);
    int32_t ctx_bank_num = bit_extract(
        smmu_glbl_rs0->IDR1, SMMUV2_IDR1_NUMCB_OFF, SMMUV2_IDR1_NUMCB_LEN);

    smmu_glbl_rs1_t *smmu_glbl_rs1 = mem_alloc_vpage(
        &cpu.as, SEC_HYP_GLOBAL, NULL, NUM_PAGES(sizeof(smmu_glbl_rs1_t)));
    mem_map_dev(&cpu.as, smmu_glbl_rs1, platform.arch.smmu.base + pg_size,
                NUM_PAGES(sizeof(smmu_glbl_rs1_t)));

    smmu_cntxt_t *smmu_cntxt = mem_alloc_vpage(
        &cpu.as, SEC_HYP_GLOBAL, NULL, NUM_PAGES((pg_size * ctx_bank_num)));
    mem_map_dev(&cpu.as, smmu_cntxt,
                platform.arch.smmu.base + (num_page * pg_size),
                NUM_PAGES(pg_size * ctx_bank_num));

    /* Everything is mapped. Initialize book-keeping data. */
    smmu.hw.glbl_rs0 = smmu_glbl_rs0;
    smmu.hw.glbl_rs1 = smmu_glbl_rs1;
    smmu.hw.cntxt = smmu_cntxt;

    smmu_check_features();

    smmu.ctx_lock = SPINLOCK_INITVAL;
    smmu.ctx_num = ctx_bank_num;
    bitmap_clear_consecutive(smmu.ctxbank_bitmap, 0, smmu.ctx_num);

    smmu.sme_lock = SPINLOCK_INITVAL;
    smmu.sme_num = smmu.hw.glbl_rs0->IDR0 & SMMUV2_IDR0_MASK;
    bitmap_clear_consecutive(smmu.sme_bitmap, 0, smmu.sme_num);
    bitmap_clear_consecutive(smmu.grp_bitmap, 0, smmu.sme_num);

    /* Clear random reset state. */
    smmu_glbl_rs0->GFSR = smmu_glbl_rs0->GFSR;
    smmu_glbl_rs0->NSGFSR = smmu_glbl_rs0->NSGFSR;

    for (int i = 0; i < smmu.sme_num; i++) {
        smmu_glbl_rs0->SMR[i] = 0;
    }

    for (int i = 0; i < smmu.ctx_num; i++) {
        smmu_cntxt[i].SCTLR = 0;
        smmu_cntxt[i].FSR = -1;
    }

    /* Enable IOMMU. */
    uint32_t cr0 = smmu.hw.glbl_rs0->CR0;
    cr0 = SMMUV2_CR0_CLEAR(cr0);
    cr0 |= SMMUV2_CR0_USFCFG | SMMUV2_CR0_SMCFCFG;
    cr0 &= ~SMMUV2_CR0_CLIENTPD;
    smmu.hw.glbl_rs0->CR0 = cr0;
}

int smmu_alloc_ctxbnk()
{
    spin_lock(&smmu.ctx_lock);
    /* Find a free context bank. */
    int nth = bitmap_find_nth(smmu.ctxbank_bitmap, smmu.ctx_num, 1, 0, false);
    if (nth >= 0) {
        bitmap_set(smmu.ctxbank_bitmap, nth);
    }
    spin_unlock(&smmu.ctx_lock);

    return nth;
}

static int smmu_cb_ttba_offset(int t0sz)
{
    int offset = 12;

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

void smmu_write_ctxbnk(int32_t ctx_id, void *root_pt, uint32_t vm_id)
{
    spin_lock(&smmu.ctx_lock);
    if (!bitmap_get(smmu.ctxbank_bitmap, ctx_id)) {
        ERROR("smmu ctx %d is already allocated", ctx_id);
    } else {
        /* Set type as stage 2 only. */
        smmu.hw.glbl_rs1->CBAR[ctx_id] = SMMUV2_CBAR_VMID(vm_id);
        smmu.hw.glbl_rs1->CBA2R[ctx_id] = SMMUV2_CBAR_VA64;

        /**
         * This should closely match to the VTCR configuration set up in
         * vmm_arch_init as we're sharing page table between the VM and its
         * smmu context.
         */
        uint32_t tcr = ((parange << SMMUV2_TCR_PS_OFF) & SMMUV2_TCR_PS_MSK);
        int t0sz = 64 - parange_table[parange];
        tcr |= SMMUV2_TCR_TG0_4K;
        tcr |= SMMUV2_TCR_ORGN0_WB_RA_WA;
        tcr |= SMMUV2_TCR_IRGN0_WB_RA_WA;
        tcr |= SMMUV2_TCR_T0SZ(t0sz);
        tcr |= SMMUV2_TCR_SH0_IS;
        tcr |= ((parange_table[parange] < 44) ? SMMUV2_TCR_SL0_1
                                              : SMMUV2_TCR_SL0_0);
        smmu.hw.cntxt[ctx_id].TCR = tcr;
        smmu.hw.cntxt[ctx_id].TTBR0 =
            ((uint64_t)root_pt) & SMMUV2_CB_TTBA(smmu_cb_ttba_offset(t0sz));

        uint32_t sctlr = smmu.hw.cntxt[ctx_id].SCTLR;
        sctlr = SMMUV2_SCTLR_CLEAR(sctlr);
        sctlr |= SMMUV2_SCTLR_DEFAULT;
        smmu.hw.cntxt[ctx_id].SCTLR |= sctlr;
    }
    spin_unlock(&smmu.ctx_lock);
}

int smmu_alloc_sme()
{
    spin_lock(&smmu.sme_lock);
    /* Find a free sme. */
    int nth = bitmap_find_nth(smmu.sme_bitmap, smmu.sme_num, 1, 0, false);
    spin_unlock(&smmu.sme_lock);

    return nth;
}

/*
 * When adding a new stream match entry there are a two different cases:
 *
 *      1. sme is a group;
 *      2. sme is a device.
 *
 * Groups can be merged together if one is found to be inclusive or equal of
 * the other.
 *
 * Devices can be added (i.e. merged into) a group, but not together.
 *
 * This function searches for existing smes that are compatible for merging
 * with the new sme, raising an ERROR when conflicting attributes are found.
 */
bool smmu_compatible_sme_exists(uint16_t mask, uint16_t id, uint32_t ctx,
                                bool group)
{
    bool included = false;
    uint32_t sme = 0;

    spin_lock(&smmu.sme_lock);
    smmu_for_each_sme(sme)
    {
        uint16_t sme_mask = smmu_sme_get_mask(sme);
        uint16_t mask_r = mask & sme_mask;
        uint16_t diff_id = (smmu_sme_get_id(sme) ^ id) & ~(mask | sme_mask);

        if (!diff_id) {
            /* Only group-to-group or device-to-group can be merged */
            if ((group || (smmu_sme_is_group(sme) &&
                (mask_r == mask || mask_r == sme_mask)) ||
                (ctx == smmu_sme_get_ctx(sme)))) {

                /* Compatible entry found.
                 *
                 * If the new entry includes an existing one, there is the
                 * possibility that it will include other existing entries, it
                 * is therefore necessary to remove the existing entry and keep
                 * searching.
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

void smmu_write_sme(uint32_t sme, uint16_t mask, uint16_t id, bool group)
{
    spin_lock(&smmu.sme_lock);
    if (bitmap_get(smmu.sme_bitmap, sme)) {
        ERROR("smmu: trying to write unallocated sme %d", sme);
    } else {
        smmu.hw.glbl_rs0->SMR[sme] = mask << SMMU_SMR_MASK_OFF;
        smmu.hw.glbl_rs0->SMR[sme] |= id & SMMU_ID_MSK;
        smmu.hw.glbl_rs0->SMR[sme] |= SMMUV2_SMR_VALID;
        bitmap_set(smmu.sme_bitmap, sme);

        if (group) {
            bitmap_set(smmu.grp_bitmap, sme);
        }
    }
    spin_unlock(&smmu.sme_lock);
}

void smmu_write_s2c(uint32_t sme, int32_t ctx_id)
{
    spin_lock(&smmu.sme_lock);
    if (!bitmap_get(smmu.sme_bitmap, sme)) {
        ERROR("smmu: trying to write unallocated s2c %d", sme);
    } else {
        /* Initial contex is a translation context. */
        uint32_t s2cr = smmu.hw.glbl_rs0->S2CR[sme];

        s2cr = S2CR_CLEAR(s2cr);
        s2cr |= S2CR_DFLT;
        s2cr |= ctx_id & S2CR_CBNDX_MASK;

        smmu.hw.glbl_rs0->S2CR[sme] = s2cr;
    }
    spin_unlock(&smmu.sme_lock);
}
