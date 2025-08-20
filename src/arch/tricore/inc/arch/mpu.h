/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __MPU_H__
#define __MPU_H__

#include <bao.h>
#include <mem.h>

struct mpu_node {
    mpid_t link;
    mem_flags_t perms;
    unsigned long ref_counter;
};
struct mpu_arch {
    BITMAP_ALLOC(data_bitmap, MPU_DATA_MAX_NUM_ENTRIES);
    BITMAP_ALLOC(code_bitmap, MPU_CODE_MAX_NUM_ENTRIES);

    struct mpu_node data_entries[MPU_DATA_MAX_NUM_ENTRIES];
    struct mpu_node code_entries[MPU_CODE_MAX_NUM_ENTRIES];
};

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2);
bool mpu_update(struct addr_space* as, struct mp_region* mpr);
void mpu_enable(void);
void mpu_disable(void);

#endif //__MPU_H__
