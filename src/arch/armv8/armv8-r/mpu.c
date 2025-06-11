/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <vm.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

#define NUM_ENTRIES 32
#define BIT(x)      ((unsigned long)(1 << (x)))

struct cpu* CPU_TEMP;

struct MPU_TEMP {
    // regs
    unsigned long HMPUIR;
    unsigned long HPRBAR[NUM_ENTRIES];
    unsigned long HPRENR;
    unsigned long HPRLAR[NUM_ENTRIES];
    unsigned long HPRSELR;
    unsigned long MPUIR;
    unsigned long PRBAR[NUM_ENTRIES];
    unsigned long PRENR;
    unsigned long PRLAR[NUM_ENTRIES];
    unsigned long PRSELR;
    unsigned long VSCTLR;

    unsigned long EL2_EN;
    unsigned long EL1_EN;
    unsigned long EL2_LOCKED;
} mpu_temp;

void mpu_temp_update(void)
{
    mpu_temp.HMPUIR = sysreg_mpuir_el2_read();
    mpu_temp.HPRENR = sysreg_prenr_el2_read();
    for (uint32_t i = 0; i < NUM_ENTRIES; i++) {
        sysreg_prselr_el2_write(i);
        ISB();
        mpu_temp.HPRBAR[i] = sysreg_prbar_el2_read();
        mpu_temp.HPRLAR[i] = sysreg_prlar_el2_read();
    }

    mpu_temp.EL2_EN = cpu()->as.arch.entry_mask;
    mpu_temp.EL1_EN = cpu()->vcpu->vm->as.arch.entry_mask;
    mpu_temp.EL2_LOCKED = cpu()->arch.profile.mpu.locked;
}

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
        if (cpu()->arch.profile.mpu.bitmap & BIT(i)) {
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
    for (mpid_t i = 0; i < MPU_ARCH_MAX_NUM_ENTRIES; i++) {
        if (!(cpu()->arch.profile.mpu.bitmap & BIT(i))) {
            cpu()->arch.profile.mpu.bitmap |= BIT(i);
            reg_num = i;
            break;
        }
    }
    return reg_num;
}

static void mpu_entry_set(mpid_t mpid, struct mp_region* mpr)
{
    unsigned long lim = mpr->base + mpr->size - 1;

    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prbar_el2_write((mpr->base & PRBAR_BASE_MSK) | mpr->mem_flags.prbar);
    sysreg_prlar_el2_write((lim & PRLAR_LIMIT_MSK) | mpr->mem_flags.prlar);
}

static void mpu_entry_update(mpid_t mpid, struct mp_region* mpr)
{
    unsigned long lim = mpr->base + mpr->size - 1;

    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prlar_el2_write(lim & PRLAR_LIMIT_MSK);
}

static bool mpu_entry_clear(mpid_t mpid)
{
    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prlar_el2_write(0);
    sysreg_prbar_el2_write(0);
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
    // check if there is a region with same base and size
    // check if it is a sub region?

    mpid_t mpid = INVALID_MPID;
    priv_t priv = mpu_as_priv(as);
    mpid_t existing = mpu_find_region(mpr);

    mpu_temp_update();
    if (mpr->size == 0) {
        return false;
    }

    if (existing != INVALID_MPID) {
        // What to do when there is region already in the mpu?
        // Check the permissions? Shouldn't those be on the update?
        // el1 vs el2
        return false;
    }

    else {
        mpid = mpu_entry_allocate();
        if (mpid != INVALID_MPID) {
            if (locked) {
                cpu()->arch.profile.mpu.locked |= BIT(mpid);
            }

            perms_t perms;
            perms = mem_vmpu_entry_perms(mpr);
            as->arch.entry_mask |= BIT(mpid);
            if (priv == PRIV_VM) {
                mpr->mem_flags.prlar &= (uint16_t)~PRLAR_EN;
                cpu()->arch.profile.mpu.entry_perms[mpid].el1 = perms; // WRONG?
                cpu()->arch.profile.mpu.entry_perms[mpid].el2 = PERM_NONE;
            } else {
                cpu()->arch.profile.mpu.entry_perms[mpid].el1 = PERM_NONE;
                cpu()->arch.profile.mpu.entry_perms[mpid].el2 = perms;
            }
            mpu_entry_set(mpid, mpr);
        }
    }

    mpu_temp_update();

    return true;
}

bool mpu_unmap(struct addr_space* as, struct mp_region* mpr)
{
    // priv_t priv = mpu_as_priv(as);
    UNUSED_ARG(as);
    mpid_t mpid = mpu_find_region(mpr);
    mpu_temp_update();
    if (mpid != INVALID_MPID) {
        cpu()->arch.profile.mpu.bitmap &= ~BIT(mpid);
        cpu()->arch.profile.mpu.locked &= ~BIT(mpid);
        cpu()->arch.profile.mpu.entry_perms[mpid].el1 = PERM_NONE;
        cpu()->arch.profile.mpu.entry_perms[mpid].el2 = PERM_NONE;
        mpu_entry_clear(mpid);
    }
    mpu_temp_update();
    return true;
}

bool mpu_update(struct addr_space* as, struct mp_region* mpr)
{
    // priv_t priv = mpu_as_priv(as);
    UNUSED_ARG(as);
    mpu_temp_update();
    for (mpid_t i = 0; i < MPU_ARCH_MAX_NUM_ENTRIES; i++) {
        if (cpu()->arch.profile.mpu.bitmap & BIT(i)) {
            if ((sysreg_prbar_el2_read() & PRBAR_BASE_MSK) ==
                mpr->base /*&& !bitmap_get(cpu()->arch.profile.mpu.locked,i)*/) {
                // should we check if the new addresses overlap any region?
                mpu_entry_update(i, mpr);
                break;
            }
        }
    }

    mpu_temp_update();
    return true;
}

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2)
{
    // TODO
    UNUSED_ARG(perms1);
    UNUSED_ARG(perms2);
    return true;
}

void mpu_enable(void) { }

void mpu_init()
{
    CPU_TEMP = cpu();
    cpu()->arch.profile.mpu.bitmap = 0;
    cpu()->arch.profile.mpu.locked = 0;

    for (mpid_t mpid = 0; mpid < MPU_ARCH_MAX_NUM_ENTRIES; mpid++) {
        cpu()->arch.profile.mpu.entry_perms[mpid].el1 = 0;
        cpu()->arch.profile.mpu.entry_perms[mpid].el2 = 0;
    }
}
