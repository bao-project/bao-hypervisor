
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MPU_H__
#define __ARCH_MPU_H__

#include <bao.h>
#include <arch/sysregs.h>

void mpu_arch_init(void);
bool mpu_add_region(struct mp_region* reg);
bool mpu_remove_region(struct mp_region* reg);

#endif /* __ARCH_MPU_H__ */
