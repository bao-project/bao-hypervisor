/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <types.h>
#include <mem.h>
#include <cpu.h>
#include <arch/csfrs.h>
#include <arch/fences.h>

#define MPU_SET_PERM   true
#define MPU_CLEAR_PERM false

static mpid_t mpu_data_entry_allocate(void)
{
    mpid_t reg_num = INVALID_MPID;
    ssize_t free_mpu_entry = bitmap_find_nth(cpu()->arch.mpu.data_bitmap, MPU_DATA_MAX_NUM_ENTRIES,
        1, 0, BITMAP_NOT_SET);
    if (free_mpu_entry != -1) {
        bitmap_set(cpu()->arch.mpu.data_bitmap, (size_t)free_mpu_entry);
        reg_num = (mpid_t)free_mpu_entry;
    }

    return reg_num;
}

static void mpu_data_entry_deallocate(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.mpu.data_bitmap, mpid);
}

static mpid_t mpu_code_entry_allocate(void)
{
    mpid_t reg_num = INVALID_MPID;
    ssize_t free_mpu_entry = bitmap_find_nth(cpu()->arch.mpu.code_bitmap, MPU_CODE_MAX_NUM_ENTRIES,
        1, 0, BITMAP_NOT_SET);
    if (free_mpu_entry != -1) {
        bitmap_set(cpu()->arch.mpu.code_bitmap, (size_t)free_mpu_entry);
        reg_num = (mpid_t)free_mpu_entry;
    }

    return reg_num;
}

static void mpu_code_entry_deallocate(mpid_t mpid)
{
    bitmap_clear(cpu()->arch.mpu.code_bitmap, mpid);
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

static void mpu_insert_data_entry(struct mp_region* mpr, mpid_t mpid)
{
    unsigned long lower_addr = mpr->base;
    unsigned long upper_addr = mpr->base + mpr->size;
    csfr_dpr_l_write(mpid, lower_addr);
    csfr_dpr_u_write(mpid, upper_addr);
    fence_sync();
}

static void mpu_insert_code_entry(struct mp_region* mpr, mpid_t mpid)
{
    unsigned long lower_addr = mpr->base;
    unsigned long upper_addr = mpr->base + mpr->size;
    csfr_cpr_l_write(mpid, lower_addr);
    csfr_cpr_u_write(mpid, upper_addr);
    fence_sync();
}

static inline void mpu_prs_update_perm(unsigned long prs, mpid_t mpid, mem_flags_t perm, bool val)
{
    if (perm.write) {
        set_dpwe_bit(prs, mpid, val);
    }

    if (perm.read) {
        set_dpre_bit(prs, mpid, val);
    }

    if (perm.exec) {
        set_cpxe_bit(prs, mpid, val);
    }

    fence_sync();
}

static void mpu_prs_set_perm(unsigned long prs, mpid_t mpid, mem_flags_t perm)
{
    mpu_prs_update_perm(prs, mpid, perm, MPU_SET_PERM);
}

static void mpu_prs_clr_perm(unsigned long prs, mpid_t mpid, mem_flags_t perm)
{
    mpu_prs_update_perm(prs, mpid, perm, MPU_CLEAR_PERM);
}

bool mpu_map(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    UNUSED_ARG(locked);
    bool data_entry_set = false;
    mpid_t code_mpid = INVALID_MPID;
    mpid_t data_mpid = INVALID_MPID;
    unsigned long prs = as->id;
    mpid_t existing_data = mpu_data_find_region(mpr);
    mpid_t existing_code = mpu_code_find_region(mpr);

    if (mpr->size == 0) {
        return false;
    }

    if (mpr->mem_flags.write || mpr->mem_flags.read) {
        if (existing_data != INVALID_MPID) {
            cpu()->arch.mpu.data_entries[existing_data].ref_counter++;
            mpu_prs_set_perm(prs, existing_data, mpr->mem_flags);
            data_entry_set = true;

            data_mpid = existing_data;
        } else {
            data_mpid = mpu_data_entry_allocate();
            if (data_mpid != INVALID_MPID) {
                mpu_insert_data_entry(mpr, data_mpid);

                mem_flags_t perms;
                perms.raw = (mpr->mem_flags.raw & PTE_PERM_RW.raw);
                mpu_prs_set_perm(prs, data_mpid, perms);

                data_entry_set = true;

                cpu()->arch.mpu.data_entries[data_mpid].ref_counter++;
                cpu()->arch.mpu.data_entries[data_mpid].perms.raw |= mpr->mem_flags.raw;
            }
        }
    }

    if (mpr->mem_flags.exec) {
        if (existing_code != INVALID_MPID) {
            cpu()->arch.mpu.code_entries[existing_code].ref_counter++;

            if (data_entry_set) {
                cpu()->arch.mpu.code_entries[existing_code].link = data_mpid;
                cpu()->arch.mpu.data_entries[data_mpid].link = existing_code;
            }

        } else {
            code_mpid = mpu_code_entry_allocate();
            if (code_mpid != INVALID_MPID) {
                mpu_insert_code_entry(mpr, code_mpid);

                mpu_prs_set_perm(prs, code_mpid, PTE_PERM_X);
                cpu()->arch.mpu.code_entries[code_mpid].ref_counter++;
                cpu()->arch.mpu.code_entries[code_mpid].perms.raw |= PTE_PERM_X.raw;

                if (data_entry_set) {
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

    fence_sync();
    return true;
}

bool mpu_unmap(struct addr_space* as, struct mp_region* mpr)
{
    unsigned long prs = as->id;
    bool ret = false;

    mpid_t code_entry = mpu_code_find_region(mpr);
    mpid_t data_entry = mpu_data_find_region(mpr);

    if (data_entry != INVALID_MPID) {
        if (cpu()->arch.mpu.data_entries[data_entry].ref_counter == 1) {
            csfr_dpr_u_write(data_entry, 0);
            csfr_dpr_l_write(data_entry, 0);
            mpu_data_entry_deallocate(data_entry);
            fence_sync();
        }

        cpu()->arch.mpu.data_entries[data_entry].ref_counter--;
        mpu_prs_clr_perm(prs, data_entry, PTE_PERM_RW);

        if (cpu()->arch.mpu.data_entries[data_entry].link != INVALID_MPID) {
            cpu()->arch.mpu.data_entries[data_entry].link = INVALID_MPID;
        }

        ret = true;
    }

    if (code_entry != INVALID_MPID) {
        if (cpu()->arch.mpu.code_entries[code_entry].ref_counter == 1) {
            csfr_cpr_u_write(code_entry, 0);
            csfr_cpr_l_write(code_entry, 0);
            mpu_code_entry_deallocate(code_entry);
            fence_sync();
        }

        cpu()->arch.mpu.code_entries[code_entry].ref_counter--;
        mpu_prs_clr_perm(prs, code_entry, PTE_PERM_X);

        if (cpu()->arch.mpu.code_entries[code_entry].link != INVALID_MPID) {
            cpu()->arch.mpu.code_entries[code_entry].link = INVALID_MPID;
        }
        ret = true;
    }

    return ret;
}

void mpu_enable(void)
{
    unsigned long corecon = csfr_corecon_read();
    corecon |= CORECON_PROTEN_MASK;
    csfr_corecon_write(corecon);
    fence_sync();
}

void mpu_disable(void)
{
    unsigned long corecon = csfr_corecon_read();
    corecon &= ~CORECON_PROTEN_MASK;
    csfr_corecon_write(corecon);
    fence_sync();
}

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2)
{
    /* this function is used by mem_vmpu_coalesce_contiguous and needs to return
    true when 2 different regions have compatible permissions to be coalesced.
    In TC4 we have code and data entries, which is translated to:
        Code entries -> exec permissions
        data entries -> read or write permissions
    Therefore, this function returns true if both regions have exec permissions
    or if both regions have a combination of read or write permissions */
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
    bitmap_clear_consecutive(cpu()->arch.mpu.data_bitmap, 0, MPU_DATA_MAX_NUM_ENTRIES);
    bitmap_clear_consecutive(cpu()->arch.mpu.code_bitmap, 0, MPU_CODE_MAX_NUM_ENTRIES);

    for (mpid_t mpid = 0; mpid < MPU_DATA_MAX_NUM_ENTRIES; mpid++) {
        cpu()->arch.mpu.data_entries[mpid].link = INVALID_MPID;
        cpu()->arch.mpu.data_entries[mpid].perms = PTE_PERM_NONE;
        cpu()->arch.mpu.data_entries[mpid].ref_counter = 0;
    }

    for (mpid_t mpid = 0; mpid < MPU_CODE_MAX_NUM_ENTRIES; mpid++) {
        cpu()->arch.mpu.code_entries[mpid].link = INVALID_MPID;
        cpu()->arch.mpu.code_entries[mpid].perms = PTE_PERM_NONE;
        cpu()->arch.mpu.code_entries[mpid].ref_counter = 0;
    }
}
