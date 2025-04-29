
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

struct mpu_perms {
    perms_t el2;
    perms_t el1;
};

struct mpu_arch {
    unsigned long bitmap;
    unsigned long locked;

    struct mpu_perms entry_perms[MPU_ARCH_MAX_NUM_ENTRIES];
};

// void mpu_arch_init(void);
// void mpu_arch_enable(void);
// bool mpu_add_region(struct mp_region* reg, bool locked);
// bool mpu_remove_region(struct mp_region* reg);
// bool mpu_update_region(struct mp_region* reg);
bool mpu_perms_compatible(uint32_t perms1, uint32_t perms2);

#endif /* __ARCH_MPU_H__ */
