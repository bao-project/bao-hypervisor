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

static mpid_t mpu_find_region(struct mp_region* mpr)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < MPU_ARCH_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.profile.mpu.allocated_entries, i)) {
            sysreg_prselr_el2_write(i);
            ISB();
            unsigned long hw_base = (sysreg_prbar_el2_read() & PRBAR_BASE_MSK);
            unsigned long hw_limit = (sysreg_prlar_el2_read() & PRLAR_LIMIT_MSK);
            unsigned long sw_base = (mpr->base & PRBAR_BASE_MSK);
            unsigned long sw_limit = ((mpr->base + mpr->size - 1) & PRLAR_LIMIT_MSK);
            if ((hw_base == sw_base) && (hw_limit == sw_limit)) {
                reg_num = i;
                break;
            }
        }
    }
    return reg_num;
}

static mpid_t mpu_entry_allocate(void)
{
    mpid_t reg_num = INVALID_MPID;
    reg_num = (mpid_t)bitmap_find_nth(cpu()->arch.profile.mpu.allocated_entries, 
        MPU_ARCH_MAX_NUM_ENTRIES, 1, 0 , false);

    bitmap_set(cpu()->arch.profile.mpu.allocated_entries, reg_num);

    return reg_num;
}

static inline void mpu_entry_deallocate(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.profile.mpu.allocated_entries,mpid);
}

static inline void mpu_entry_lock(mpid_t mpid)
{
    bitmap_set(cpu()->arch.profile.mpu.locked_entries,mpid);
}

static inline void mpu_entry_unlock(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.profile.mpu.locked_entries,mpid);
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

static void mpu_entry_update(mpid_t mpid, struct mp_region* mpr)
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

static inline perms_t mem_vmpu_entry_perms(struct mp_region* mpr)
{
    perms_t perms = PERM_R;
    perms |= !(mpr->mem_flags.prbar & PRBAR_XN) ? PERM_X : 0;
    perms |= !(mpr->mem_flags.prbar & PRBAR_NWR_BIT) ? PERM_W : 0;
    return perms;
}

bool mpu_map(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    mpid_t mpid = INVALID_MPID;
    priv_t priv = mpu_as_priv(as);
    mpid_t existing = mpu_find_region(mpr);

    if (mpr->size == 0) {
        return false;
    }

    if (existing != INVALID_MPID) {
        return false;
    }

    else {
        mpid = mpu_entry_allocate();
        if (mpid != INVALID_MPID) {
            if (locked) {
                mpu_entry_lock(mpid);
            }
            bitmap_set((bitmap_t *)&as->arch.mpu_entry_mask, mpid);
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
    mpid_t mpid = mpu_find_region(mpr);

    if (mpid != INVALID_MPID) {
        mpu_entry_deallocate(mpid);
        mpu_entry_unlock(mpid);
        
        mpu_entry_clear(mpid);
    }

    return true;
}

bool mpu_update(struct addr_space* as, struct mp_region* mpr)
{
    UNUSED_ARG(as);
    unsigned long prbar = 0;
    unsigned long base = 0;
    for (mpid_t i = 0; i < MPU_ARCH_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.profile.mpu.allocated_entries,i)) {
            sysreg_prselr_el2_write(i);
            ISB();
            prbar = sysreg_prbar_el2_read();
            base = PRBAR_BASE(prbar);
            if (base == mpr->base) {
                mpu_entry_update(i, mpr);
                return true;
            }
        }
    }

    return false;
}

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2)
{
    return perms1 == perms2;
}

void mpu_enable(void)
{
    sysreg_sctlr_el2_write(SCTLR_M);
}

void mpu_init()
{
    for (mpid_t mpid = 0; mpid < MPU_ARCH_MAX_NUM_ENTRIES; mpid++) {
        bitmap_clear(cpu()->arch.profile.mpu.allocated_entries,mpid);
        bitmap_clear(cpu()->arch.profile.mpu.locked_entries,mpid);
    }
}
