/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <vm.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

static priv_t mpu_as_priv(struct addr_space* as)
{
    priv_t priv;

    if (as->type == AS_VM) {
        priv = PRIV_VM;
    } else {
        priv = PRIV_HYP;
    }

    return priv;
}

static unsigned long mpu_get_region_base(mpid_t mpid)
{
    unsigned long prbar = 0;

    sysreg_prselr_el2_write(mpid);
    ISB();
    prbar = sysreg_prbar_el2_read();

    return PRBAR_BASE(prbar);
}

static mpid_t mpu_find_region(struct mp_region* mpr, asid_t asid)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < MPU_ARCH_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.profile.mpu.allocated_entries, i)) {
            if (mpu_get_region_base(i) == mpr->base &&
                cpu()->arch.profile.mpu.entry_asid[i] == asid) {
                mpid = i;
                break;
            }
        }
    }
    return mpid;
}

static mpid_t mpu_entry_allocate(asid_t asid)
{
    mpid_t reg_num = INVALID_MPID;
    reg_num = (mpid_t)bitmap_find_nth(cpu()->arch.profile.mpu.allocated_entries,
        MPU_ARCH_MAX_NUM_ENTRIES, 1, 0, false);

    bitmap_set(cpu()->arch.profile.mpu.allocated_entries, reg_num);
    cpu()->arch.profile.mpu.entry_asid[reg_num] = asid;

    return reg_num;
}

static inline void mpu_entry_deallocate(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.profile.mpu.allocated_entries, mpid);
    cpu()->arch.profile.mpu.entry_asid[mpid] = INVALID_ASID;
}

static inline void mpu_entry_lock(mpid_t mpid)
{
    bitmap_set(cpu()->arch.profile.mpu.locked_entries, mpid);
}

static inline void mpu_entry_unlock(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.profile.mpu.locked_entries, mpid);
}

static void mpu_entry_set(mpid_t mpid, struct mp_region* mpr)
{
    unsigned long lim = mpr->base + mpr->size - 1;

    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prbar_el2_write((mpr->base & PRBAR_BASE_MSK) | mpr->mem_flags.prbar);
    sysreg_prlar_el2_write((lim & PRLAR_LIMIT_MSK) | mpr->mem_flags.prlar);
    ISB();
}

static void mpu_entry_update_limit(mpid_t mpid, struct mp_region* mpr)
{
    unsigned long lim = mpr->base + mpr->size - 1;

    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prlar_el2_write((lim & PRLAR_LIMIT_MSK) | mpr->mem_flags.prlar);
    ISB();
}

static bool mpu_entry_clear(mpid_t mpid)
{
    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prlar_el2_write(0);
    sysreg_prbar_el2_write(0);
    ISB();
    return true;
}

bool mpu_map(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    mpid_t mpid = INVALID_MPID;
    priv_t priv = mpu_as_priv(as);

    if (mpr->size == 0) {
        return false;
    }

    /* We don't check if there is an existing region because bao ensure that
    there is only 1 address space active at the same time, and as such, only a
    single set of mpu entries are enabled.
    Furthermore, the same check is done at the vMPU level.
    */

    else {
        mpid = mpu_entry_allocate(as->id);
        if (mpid != INVALID_MPID) {
            if (locked) {
                mpu_entry_lock(mpid);
            }
            bitmap_set((bitmap_t*)&as->arch.mpu_entry_mask, mpid);
            if (priv == PRIV_VM) {
                mpr->mem_flags.prlar &= (uint16_t)~PRLAR_EN;
            }
            mpu_entry_set(mpid, mpr);
        }
    }

    return true;
}

bool mpu_unmap(struct addr_space* as, struct mp_region* mpr)
{
    UNUSED_ARG(as);
    mpid_t mpid = mpu_find_region(mpr, as->id);

    if (mpid != INVALID_MPID) {
        mpu_entry_deallocate(mpid);
        mpu_entry_unlock(mpid);

        mpu_entry_clear(mpid);

        bitmap_clear((bitmap_t*)&as->arch.mpu_entry_mask, mpid);
    }

    return true;
}

bool mpu_update(struct addr_space* as, struct mp_region* mpr)
{
    mpid_t mpid = mpu_find_region(mpr, as->id);

    if (mpid != INVALID_MPID) {
        mpu_entry_update_limit(mpid, mpr);
        return true;
    }

    return false;
}

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2)
{
    return perms1 == perms2;
}

void mpu_enable(void)
{
    unsigned long reg_val;

    reg_val = sysreg_sctlr_el2_read();
    reg_val |= SCTLR_M;
    sysreg_sctlr_el2_write(reg_val);

    ISB();
}

void mpu_init()
{
    for (mpid_t mpid = 0; mpid < MPU_ARCH_MAX_NUM_ENTRIES; mpid++) {
        bitmap_clear(cpu()->arch.profile.mpu.allocated_entries, mpid);
        bitmap_clear(cpu()->arch.profile.mpu.locked_entries, mpid);
        cpu()->arch.profile.mpu.entry_asid[mpid] = INVALID_ASID;
    }
}
