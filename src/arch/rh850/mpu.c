/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <arch/mpu.h>
#include <srs.h>
#include <arch/fences.h>
#include <bitmap.h>
#include <plat/pbg.h>
#include <arch/vmm.h>

static inline size_t mpu_num_entries(void)
{
    unsigned long nmpue = MPCFG_GET_NMPUE(srs_mpcfg_read());
    unsigned long num = nmpue + 1;
    return num;
}

static void mpu_entry_set(mpid_t mpid, struct mp_region* mpr)
{
    unsigned long lim = mpr->base + mpr->size - 4;

    srs_mpidx_write(mpid & MPIDX_IDX_MASK);
    srs_mpla_write(mpr->base & MPLA_MASK);
    srs_mpua_write(lim & MPUA_MASK);
    srs_mpat_write(mpr->mem_flags.raw);

    synci();
}

static void mpu_entry_clear(mpid_t mpid)
{
    srs_mpidx_write(mpid & MPIDX_IDX_MASK);
    srs_mpla_write(0);
    srs_mpua_write(0);
    srs_mpat_write(0);

    synci();
}

static mpid_t mpu_entry_allocate_hyp(void)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = (mpid_t)mpu_num_entries(); i > 0; i--) {
        /* mpid_t is unsigned so we can't test for negative number.
         * Subtract 1 to get the index */
        mpid_t idx = i - 1;
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, idx) == 0) {
            bitmap_set(cpu()->arch.mpu_hyp.bitmap, idx);
            reg_num = idx;

            break;
        }
    }

    return reg_num;
}

static inline void mpu_set_hbe(unsigned long hbe)
{
    unsigned long mpcfg = srs_mpcfg_read();
    mpcfg = (mpcfg & ~MPCFG_HBE_MASK) | (hbe << MPCFG_HBE_OFF);
    srs_mpcfg_write(mpcfg);
}

static inline void update_hbe(void)
{
    /* Hyp entries are allocated top to bottom. By finding the first
     * entry from 0 to end, we get the last entry used by the hyp. This is
     * then used as the watermark */
    mpid_t mpid =
        (mpid_t)bitmap_find_nth(cpu()->arch.mpu_hyp.bitmap, mpu_num_entries(), 1, 0, BITMAP_SET);
    mpu_set_hbe(mpid);
}

bool mpu_add_region(struct mp_region* reg, bool locked)
{
    bool failed = true;
    UNUSED_ARG(locked);

    if (reg->size > 0) {
        mpid_t mpid = 0;
        mpid = mpu_entry_allocate_hyp();

        if (mpid != INVALID_MPID) {
            failed = false;
            mpu_entry_set(mpid, reg);
        }
        update_hbe();
    }

    return !failed;
}

static void mpu_entry_get_region(mpid_t mpid, struct mp_region* mpe)
{
    srs_mpidx_write(mpid & MPIDX_IDX_MASK);
    syncp();

    unsigned long base = srs_mpla_read();
    unsigned long limit = srs_mpua_read();

    mpe->mem_flags.raw = srs_mpat_read();
    mpe->base = base;
    mpe->size = (limit - base) + 4;
    mpe->as_sec = SEC_UNKNOWN;
}

static mpid_t mpu_entry_get_region_id(struct addr_space* as, struct mp_region* mem)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < (mpid_t)mpu_num_entries(); i++) {
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, i)) {
            struct mp_region mpe_cmp;
            mpu_entry_get_region(i, &mpe_cmp);

            if (mpe_cmp.base == mem->base && mpe_cmp.size == mem->size) {
                if (as->type != AS_HYP) { /* VM */
                    if (mpe_cmp.mem_flags.wmpid6 || mpe_cmp.mem_flags.rmpid6) {
                        mpid = i;
                    }
                } else { /* HYP */
                    if (mpe_cmp.mem_flags.wmpid7 || mpe_cmp.mem_flags.rmpid7) {
                        mpid = i;
                    }
                }
                break;
            }
        }
    }

    return mpid;
}

static inline void mpu_entry_free(mpid_t mpid)
{
    mpu_entry_clear(mpid);
    bitmap_clear(cpu()->arch.mpu_hyp.bitmap, mpid);
}

bool mpu_remove_region(struct addr_space* as, struct mp_region* mem)
{
    bool failed = true;

    if (mem->size > 0) {
        mpid_t mpid = mpu_entry_get_region_id(as, mem);

        if (mpid != INVALID_MPID) {
            failed = false;
            mpu_entry_free(mpid);
            update_hbe();
        }
    }

    return !failed;
}

bool mpu_update_region(struct mp_region* mpr)
{
    bool failed = true;

    for (mpid_t mpid = 0; mpid < (mpid_t)mpu_num_entries(); mpid++) {
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, mpid) == 0) {
            continue;
        }
        struct mp_region mpe_cmp;
        mpu_entry_get_region(mpid, &mpe_cmp);

        if (mpe_cmp.base == mpr->base) {
            mpu_entry_set(mpid, mpr);
            update_hbe();
            failed = false;
            break;
        }
    }

    return !failed;
}

static inline bool mpu_entry_valid(mpid_t mpid)
{
    srs_mpidx_write(mpid & MPIDX_IDX_MASK);
    syncp();

    unsigned long valid_bit = MPAT_GET_E(srs_mpat_read());

    return !!valid_bit;
}

void mpu_arch_init(void)
{
    bitmap_clear_consecutive(cpu()->arch.mpu_hyp.bitmap, 0, mpu_num_entries());

    for (mpid_t mpid = 0; mpid < (mpid_t)mpu_num_entries(); mpid++) {
        /* No entry should be valid at this point */
        if (mpu_entry_valid(mpid)) {
            bitmap_set(cpu()->arch.mpu_hyp.bitmap, mpid);
        }
    }

    /* give no mpu entries to hypervisor, we will allocate them dynamically */
    mpu_set_hbe(mpu_num_entries());

    if (cpu_is_master()) {
        /* Initialize slave side protection.
         * In the future we should figure out how to move this to io_init */
        pbg_init();
    }

    srs_mpid7_write(HYP_SPID);
    srs_spid_write(HYP_SPID);
}

void mpu_arch_enable(void)
{
    srs_mpm_write(MPM_SVP | MPM_MPE);
    synci();
}

void mpu_arch_disable(void)
{
    unsigned long mpm = srs_mpm_read() & ~MPM_MPE;
    srs_mpm_write(mpm);
}
