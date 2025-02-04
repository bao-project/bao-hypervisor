
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MPU_H__
#define __ARCH_MPU_H__

#include <bao.h>
#include <arch/sysregs.h>

void mpu_arch_init(void);
void mpu_arch_enable(void);
bool mpu_add_region(struct mp_region* reg, bool locked);
bool mpu_remove_region(struct mp_region* reg);
bool mpu_update_region(struct mp_region* reg);
bool mpu_arch_perms_compatible(uint8_t perms1, uint8_t perms2);

#endif /* __ARCH_MPU_H__ */
