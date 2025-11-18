/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MPU_H__
#define __ARCH_MPU_H__

#include <bao.h>
#include <arch/sysregs.h>
#include <bitmap.h>
#include <mem.h>

struct mpu_arch {
    BITMAP_ALLOC(allocated_entries, MPU_ARCH_MAX_NUM_ENTRIES);
    BITMAP_ALLOC(locked_entries, MPU_ARCH_MAX_NUM_ENTRIES);
    asid_t entry_asid[MPU_ARCH_MAX_NUM_ENTRIES];
};

#endif /* __ARCH_MPU_H__ */
