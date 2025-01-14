/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <arch/sysregs.h>
#include <arch/fences.h>
#include <arch/mpu.h>

static inline size_t mpu_num_entries(void)
{
    return (size_t)MPU_TYPE_N_RGN(MPU->type);
}

static void mpu_entry_set(mpid_t mpid, struct mp_region* mpr)
{
    unsigned long lim = mpr->base + mpr->size - 1;

    MPU->rnr = mpid;
    ISB();
    MPU->rbar = (mpr->base & MPU_RBAR_BASE_MSK) | mpr->mem_flags.rbar;
    MPU->rlar = (lim & MPU_RLAR_LIMIT_MSK) | mpr->mem_flags.rlar;
}

static mpid_t mpu_entry_allocate(void)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < (mpid_t)mpu_num_entries(); i++) {
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, i) == 0) {
            bitmap_set(cpu()->arch.mpu_hyp.bitmap, i);
            reg_num = i;
            break;
        }
    }
    return reg_num;
}

bool mpu_add_region(struct mp_region* reg)
{
    bool failed = true;

    if (reg->size > 0) {
        mpid_t mpid = mpu_entry_allocate();

        if (mpid != INVALID_MPID) {
            failed = false;
            mpu_entry_set(mpid, reg);
        }
    }

    return !failed;
}

bool mpu_perms_comptible(uint8_t perms1, uint8_t perms2)
{
    // TODO:ARMV8M - IMPLEMENT on all archs
    // uint8_t perms_mask = SPMPCFG_S_BIT | SPMPCFG_R_BIT | SPMPCFG_W_BIT | SPMPCFG_X_BIT;
    // return (perms1 & perms_mask) == (perms2 & perms_mask);

    return 1;
}

static void mpu_entry_get_region(mpid_t mpid, struct mp_region* mpe)
{
    MPU->rnr = mpid;
    ISB();

    unsigned long rbar = MPU->rbar;
    unsigned long rlar = MPU->rlar;

    mpe->mem_flags.rbar = MPU_RBAR_FLAGS(rbar);
    mpe->mem_flags.rlar = MPU_RLAR_FLAGS(rlar);
    mpe->base = MPU_RBAR_BASE(rbar);
    mpe->size = (MPU_RLAR_LIMIT(rlar) + 1) - mpe->base;
    mpe->as_sec = SEC_UNKNOWN;
}

static mpid_t mpu_entry_get_region_id(struct mp_region* mpe)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < (mpid_t)mpu_num_entries(); i++) {
        struct mp_region mpe_cmp;
        mpu_entry_get_region(i, &mpe_cmp);

        if (mpe_cmp.base == mpe->base && mpe_cmp.size == mpe->size) {
            mpid = i;
            break;
        }
    }

    return mpid;
}

static void mpu_entry_clear(mpid_t mpid)
{
    MPU->rnr = mpid;
    ISB();
    MPU->rbar = 0;
    MPU->rlar = 0;
}

static inline void mpu_entry_free(mpid_t mpid)
{
    mpu_entry_clear(mpid);
    bitmap_clear(cpu()->arch.mpu_hyp.bitmap, mpid);
}

bool mpu_remove_region(struct mp_region* reg)
{
    bool failed = true;

    if (reg->size > 0) {
        mpid_t mpid = mpu_entry_get_region_id(reg);

        if (mpid != INVALID_MPID) {
            failed = false;
            mpu_entry_free(mpid);
        }
    }

    return !failed;
}

static inline bool mpu_entry_valid(mpid_t mpid)
{
    MPU->rnr = mpid;
    ISB();
    return !!(MPU->rlar & MPU_RLAR_EN);
}

static inline bool mpu_entry_locked(mpid_t mpid)
{
    return !!bitmap_get(cpu()->arch.mpu_hyp.locked, mpid);
}

void mpu_disable_background_region(void)
{
    MPU->ctrl &= ~MPU_CTRL_PRIVDEFENA;
    ISB();
}

void mpu_arch_init(void)
{
    bitmap_clear_consecutive(cpu()->arch.mpu_hyp.bitmap, 0, mpu_num_entries());

    for (mpid_t mpid = 0; mpid < (mpid_t)mpu_num_entries(); mpid++) {
        if (mpu_entry_valid(mpid)) {
            bitmap_set(cpu()->arch.mpu_hyp.bitmap, mpid);
            bitmap_set(cpu()->arch.mpu_hyp.locked, mpid);
        }
    }
}

void mpu_arch_enable(void)
{
    MPU->ctrl |= MPU_CTRL_ENABLE;
    /* Enable background region */
    MPU->ctrl &= ~MPU_CTRL_PRIVDEFENA;
    ISB();
}
