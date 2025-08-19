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
};

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2);

#endif /* __ARCH_MPU_H__ */
