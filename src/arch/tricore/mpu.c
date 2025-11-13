/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include "types.h"
#include <mem.h>
#include <cpu.h>
#include <arch/csfrs.h>
#include <arch/fences.h>

#define CAT_RW_FLAGS(mem_flags) \
    (((unsigned long int)(mem_flags).write << 2) | ((unsigned long int)(mem_flags).read << 1))

static mpid_t mpu_code_entry_allocate(void)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < MPU_CODE_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.code_bitmap, i) == 0) {
            bitmap_set(cpu()->arch.mpu.code_bitmap, i);
            reg_num = i;
            break;
        }
    }
    return reg_num;
}

static void mpu_code_entry_deallocate(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.mpu.code_bitmap, mpid);
}

static mpid_t mpu_data_entry_allocate(void)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < MPU_DATA_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.data_bitmap, i) == 0) {
            bitmap_set(cpu()->arch.mpu.data_bitmap, i);
            reg_num = i;
            break;
        }
    }
    return reg_num;
}

static mpid_t mpu_data_find_region(struct mp_region* mpr)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < MPU_DATA_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.data_bitmap, i)) {
            if (csfr_dpr_l_read(i) == mpr->base && csfr_dpr_u_read(i) == mpr->base + mpr->size) {
                reg_num = i;
                break;
            }
        }
    }
    return reg_num;
}

static mpid_t mpu_code_find_region(struct mp_region* mpr)
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < MPU_CODE_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.code_bitmap, i)) {
            if (csfr_cpr_l_read(i) == mpr->base && csfr_cpr_u_read(i) == mpr->base + mpr->size) {
                reg_num = i;
                break;
            }
        }
    }
    return reg_num;
}

static void mpu_data_entry_deallocate(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.mpu.data_bitmap, mpid);
}

static void mpu_insert_data_entry(struct mp_region* mpr, mpid_t mpid)
{
    unsigned long lower_addr = mpr->base;
    unsigned long upper_addr = mpr->base + mpr->size;
    csfr_dpr_l_write(mpid, lower_addr);
    csfr_dpr_u_write(mpid, upper_addr);
}

static void mpu_insert_code_entry(struct mp_region* mpr, mpid_t mpid)
{
    unsigned long lower_addr = mpr->base;
    unsigned long upper_addr = mpr->base + mpr->size;
    csfr_cpr_l_write(mpid, lower_addr);
    csfr_cpr_u_write(mpid, upper_addr);
}

static void mpu_prs_enable_entry(unsigned long prs, mpid_t mpid, unsigned long perm)
{
    if (perm & PERM_W) {
        set_dpwe_bit(prs, mpid, true);
    }

    if (perm & PERM_R) {
        set_dpre_bit(prs, mpid, true);
    }

    if (perm & PERM_X) {
        set_cpxe_bit(prs, mpid, true);
    }
}

static void mpu_prs_disable_entry(unsigned long prs, mpid_t mpid, unsigned long perm)
{
    if (perm & PERM_W) {
        set_dpwe_bit(prs, mpid, false);
    }

    if (perm & PERM_R) {
        set_dpre_bit(prs, mpid, false);
    }

    if (perm & PERM_X) {
        set_cpxe_bit(prs, mpid, false);
    }
}

bool mpu_map(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    bool entry_added = false;
    unsigned long code_mpid = INVALID_MPID;
    unsigned long data_mpid = INVALID_MPID;
    unsigned long prs = as->id; // as->type ? 1 : 0;
    mpid_t existing_data = mpu_data_find_region(mpr);
    mpid_t existing_code = mpu_code_find_region(mpr);

    if (mpr->size == 0) {
        return false;
    }

    if (mpr->mem_flags.write || mpr->mem_flags.read) {
        if (existing_data != INVALID_MPID) {
            // Should we increment the ref_counter regardless?
            // Shouldn't we evaluate if regions is already enabled for the PRS?
            cpu()->arch.mpu.data_entries[existing_data].ref_counter++;
            mpu_prs_enable_entry(prs, existing_data, CAT_RW_FLAGS(mpr->mem_flags));
            entry_added = true;

            data_mpid = existing_data;

            /* Is there any circumstance where two regions with the same boundaries are
            not linked? */
            if (existing_code != INVALID_MPID && mpr->mem_flags.exec) { // We assume they were
                                                                        // linked beforehand
                cpu()->arch.mpu.code_entries[existing_code].ref_counter++;
                mpu_prs_enable_entry(prs, existing_code, PERM_X);
                return true;
            }
        } else {
            data_mpid = mpu_data_entry_allocate();
            if (data_mpid != INVALID_MPID) {
                mpu_insert_data_entry(mpr, data_mpid);
                if (locked) {
                    bitmap_set(cpu()->arch.mpu.data_locked, data_mpid);
                }
                mpu_prs_enable_entry(prs, data_mpid,
                    (unsigned long int)CAT_RW_FLAGS(mpr->mem_flags));

                entry_added = true;

                cpu()->arch.mpu.data_entries[data_mpid].ref_counter++;
                cpu()->arch.mpu.data_entries[data_mpid].perms |=
                    (unsigned long int)CAT_RW_FLAGS(mpr->mem_flags);
            }
        }
    }

    if (mpr->mem_flags.exec) {
        if (existing_code != INVALID_MPID) {
            cpu()->arch.mpu.code_entries[existing_code].ref_counter++;

            if (entry_added) {
                cpu()->arch.mpu.code_entries[existing_code].link = data_mpid;
                cpu()->arch.mpu.data_entries[data_mpid].link = existing_code;
            }

        } else {
            code_mpid = mpu_code_entry_allocate();
            if (code_mpid != INVALID_MPID) {
                mpu_insert_code_entry(mpr, code_mpid);
                if (locked) {
                    bitmap_set(cpu()->arch.mpu.code_locked, code_mpid);
                }

                mpu_prs_enable_entry(prs, code_mpid, PERM_X);
                cpu()->arch.mpu.code_entries[code_mpid].ref_counter++;
                cpu()->arch.mpu.code_entries[code_mpid].perms |= PERM_X;

                if (entry_added) {
                    cpu()->arch.mpu.code_entries[code_mpid].link = data_mpid;
                    cpu()->arch.mpu.data_entries[data_mpid].link = code_mpid;
                }
            }
        }
    }
    return true;
}

bool mpu_update(struct addr_space* as, struct mp_region* mpr)
{
    UNUSED_ARG(as);

    for (mpid_t i = 0; i < MPU_DATA_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.data_bitmap, i) == 1) {
            if (csfr_dpr_l_read(i) == mpr->base) {
                csfr_dpr_u_write(i, mpr->base + mpr->size);
                break;
            }
        }
    }

    /* Since we iterate both mpus it is not needed to check links, we just update */

    for (mpid_t i = 0; i < MPU_CODE_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.code_bitmap, i) == 1) {
            if (csfr_cpr_l_read(i) == mpr->base) {
                csfr_cpr_u_write(i, mpr->base + mpr->size);
                break;
            }
        }
    }

    return true;
}

bool mpu_unmap(struct addr_space* as, struct mp_region* mpr)
{
    unsigned long prs = as->id;

    for (mpid_t i = 0; i < MPU_CODE_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.code_bitmap, i) == 1) {
            if (csfr_cpr_l_read(i) == mpr->base && csfr_cpr_u_read(i) == mpr->base + mpr->size) {
                if (cpu()->arch.mpu.code_entries[i].ref_counter == 1) {
                    csfr_cpr_u_write(i, 0);
                    csfr_cpr_l_write(i, 0);
                    mpu_code_entry_deallocate(i);
                }

                cpu()->arch.mpu.code_entries[i].ref_counter--;
                mpu_prs_disable_entry(prs, i, PERM_X);

                if (cpu()->arch.mpu.code_entries[i].link != INVALID_MPID) {
                    cpu()->arch.mpu.code_entries[i].link = INVALID_MPID;
                }
                break;
            }
        }
    }

    for (mpid_t i = 0; i < MPU_DATA_MAX_NUM_ENTRIES; i++) {
        if (bitmap_get(cpu()->arch.mpu.data_bitmap, i) == 1) {
            if (csfr_dpr_l_read(i) == mpr->base && csfr_dpr_u_read(i) == mpr->base + mpr->size) {
                if (cpu()->arch.mpu.data_entries[i].ref_counter == 1) {
                    csfr_dpr_u_write(i, 0);
                    csfr_dpr_l_write(i, 0);
                    mpu_data_entry_deallocate(i);
                }

                cpu()->arch.mpu.data_entries[i].ref_counter--;
                mpu_prs_disable_entry(prs, i, PERM_RW);

                if (cpu()->arch.mpu.data_entries[i].link != INVALID_MPID) {
                    cpu()->arch.mpu.data_entries[i].link = INVALID_MPID;
                }
                break;
            }
        }
    }
    return true;
}

void mpu_enable(void)
{
    csfr_corecon_write(2);
}

void mpu_disable(void)
{
    csfr_corecon_write(0);
}

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2)
{
    mem_flags_t p1;
    mem_flags_t p2;

    /* -Wpedantic doesn't allow casts to union types */
    p1.raw = perms1;
    p2.raw = perms2;

    if (p1.exec == p2.exec) {
        return true;
    }

    if ((p1.read || p1.write) && (p2.read || p2.write)) {
        return true;
    }

    return false;
}

void mpu_init(void)
{
    bitmap_clear_consecutive(cpu()->arch.mpu.code_bitmap, 0, MPU_CODE_MAX_NUM_ENTRIES);
    bitmap_clear_consecutive(cpu()->arch.mpu.data_bitmap, 0, MPU_DATA_MAX_NUM_ENTRIES);

    bitmap_clear_consecutive(cpu()->arch.mpu.code_locked, 0, MPU_CODE_MAX_NUM_ENTRIES);
    bitmap_clear_consecutive(cpu()->arch.mpu.data_locked, 0, MPU_DATA_MAX_NUM_ENTRIES);

    for (mpid_t mpid = 0; mpid < MPU_CODE_MAX_NUM_ENTRIES; mpid++) {
        cpu()->arch.mpu.code_entries[mpid].mpid = mpid;
        cpu()->arch.mpu.code_entries[mpid].link = INVALID_MPID;
        cpu()->arch.mpu.code_entries[mpid].perms = 0;
        cpu()->arch.mpu.code_entries[mpid].ref_counter = 0;
    }

    for (mpid_t mpid = 0; mpid < MPU_DATA_MAX_NUM_ENTRIES; mpid++) {
        cpu()->arch.mpu.data_entries[mpid].mpid = mpid;
        cpu()->arch.mpu.data_entries[mpid].link = INVALID_MPID;
        cpu()->arch.mpu.data_entries[mpid].perms = 0;
        cpu()->arch.mpu.data_entries[mpid].ref_counter = 0;
    }
}
