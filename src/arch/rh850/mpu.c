/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <arch/mpu.h>
#include <arch/srs.h>

static inline size_t mpu_num_entries(void)
{
    unsigned long mpcfg = get_mpcfg();
    size_t num = (mpcfg & 0x1f) + 1;
    return num;
}

static inline void mpu_lock_entry(mpid_t mpid)
{
    bitmap_set(cpu()->arch.mpu_hyp.locked, mpid);
}

// static inline bool mpu_entry_locked(mpid_t mpid)
// {
//     return !!bitmap_get(cpu()->arch.mpu_hyp.locked, mpid);
// }

static void mpu_entry_set(mpid_t mpid, struct mp_region *mpr)
{
    unsigned long lim = mpr->base + mpr->size - 4;

    set_mpidx(mpid);
    set_mpla(mpr->base);
    set_mpua(lim);
    set_mpat(mpr->mem_flags.raw);
}

static void mpu_entry_clear(mpid_t mpid)
{
    set_mpidx(mpid);
    set_mpla(0);
    set_mpua(0);
    set_mpat(0); /* TODO is disabling enough */
}

static mpid_t mpu_entry_allocate_guest(void)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = (mpid_t)mpu_num_entries(); i > 0; i--) {
        mpid_t idx = i - 1;
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, idx) == 0) {
            bitmap_set(cpu()->arch.mpu_hyp.bitmap, idx);
            reg_num = idx;

            // // Update HBE
            // unsigned long mpcfg = get_mpcfg();

            // // TODO right now hyp entries must be allocated first
            // //
            // // TODO add hyp mpu entry counter to prevent guest mpu entries from
            // // spiling into hyp entries
            // unsigned long hbe = (reg_num + 1) << 8;
            // mpcfg = (mpcfg & ~0x3F00) | hbe;
            // set_mpcfg(mpcfg);
            break;
        }
    }

    return reg_num;
}

static mpid_t mpu_entry_allocate_hyp(void)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = (mpid_t)mpu_num_entries(); i > 0; i--) {
        mpid_t idx = i - 1;
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, idx) == 0) {
            bitmap_set(cpu()->arch.mpu_hyp.bitmap, idx);
            reg_num = idx;

            break;
        }
    }

    return reg_num;
}

bool mpu_add_region(struct addr_space* as, struct mp_region *reg, bool locked)
{
    bool failed = true;

    if (reg->size > 0) {
        mpid_t mpid = 0;
        if (as->type == AS_VM)
        {
            mpid = mpu_entry_allocate_guest();
        }
        else
        {
            mpid = mpu_entry_allocate_hyp();
        }

        if (mpid != INVALID_MPID) {
            failed = false;
            mpu_entry_set(mpid, reg);
            if (locked) {
                mpu_lock_entry(mpid);
            }
        }
    }

    return !failed;
}

/* static inline bool mpu_arch_perms_compatible(mem_flags_t perms1, mem_flags_t perms2) */
/* { */
/*     UNUSED_ARG(perms1); */
/*     UNUSED_ARG(perms2); */

/*     return 1; */
/* } */

static void mpu_entry_get_region(mpid_t mpid, struct mp_region *mpe)
{
    set_mpidx(mpid);

    unsigned long base = get_mpla();
    unsigned long limit = get_mpua();

    mpe->mem_flags.raw = get_mpat();
    mpe->base = base;
    mpe->size = (limit - base) + 4;
    mpe->as_sec = SEC_UNKNOWN;
}

static mpid_t mpu_entry_get_region_id(struct mp_region *mpe)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < (mpid_t)mpu_num_entries(); i++) {
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, i)) {
            struct mp_region mpe_cmp;
            mpu_entry_get_region(i, &mpe_cmp);

            if (mpe_cmp.base == mpe->base && mpe_cmp.size == mpe->size) {
                mpid = i;
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

bool mpu_remove_region(struct mp_region *reg)
{
    bool failed = true;

    if (reg->size > 0)
    {
        mpid_t mpid = mpu_entry_get_region_id(reg);

        if (mpid != INVALID_MPID)
        {
            failed = false;
            mpu_entry_free(mpid);
        }
    }

    return !failed;
}

bool mpu_update_region(struct mp_region *mpr)
{
    bool failed = true;

    for (mpid_t mpid = 0; mpid < (mpid_t)mpu_num_entries(); mpid++)
    {
        if (bitmap_get(cpu()->arch.mpu_hyp.bitmap, mpid) == 0)
        {
            continue;
        }
        struct mp_region mpe_cmp;
        mpu_entry_get_region(mpid, &mpe_cmp);

        if (mpe_cmp.base == mpr->base)
        {
            mpu_entry_set(mpid, mpr);
            failed = false;
            break;
        }
    }

    return !failed;
}

static inline bool mpu_entry_valid(mpid_t mpid)
{
    set_mpidx(mpid);
    unsigned long attr = get_mpat();
    unsigned long valid_bit = (attr & (1 << 7)) >> 7;

    return !!valid_bit;
}

void mpu_arch_init(void)
{
    bitmap_clear_consecutive(cpu()->arch.mpu_hyp.bitmap, 0, mpu_num_entries());

    for (mpid_t mpid = 0; mpid < (mpid_t)mpu_num_entries(); mpid++)
    {
        /* TODO No entry should be valid at this point... */
        if (mpu_entry_valid(mpid))
        {
            bitmap_set(cpu()->arch.mpu_hyp.bitmap, mpid);
            bitmap_set(cpu()->arch.mpu_hyp.locked, mpid);
        }
    }

    unsigned long mpcfg = get_mpcfg();
    // give all entries to the hypervisor
    unsigned long hbe = 0;
    mpcfg = (mpcfg & ~0x3F00UL) | hbe;
    set_mpcfg(mpcfg);

    /* configure SPIDs */
    // we assume MPIDn.SPID = 0 after reset for n = 2 to 7
    set_mpid0(HYP_SPID);
    set_mpid1(VM_SPID);
    set_mpid7(AUX_SPID);
    set_spid(HYP_SPID);
}

void mpu_arch_enable(void)
{
    set_mpm(3); // TODO don't hardcode
}
