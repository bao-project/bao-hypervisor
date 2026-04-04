/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MPU_H__
#define __ARCH_MPU_H__

#include <bao.h>
#include <mem.h>

struct addr_space;
struct mp_region;

void mpu_arch_init(void);
bool mpu_add_region(struct mp_region* reg, bool locked);
bool mpu_remove_region(struct addr_space* as, struct mp_region* mem);
bool mpu_update_region(struct mp_region* reg);
void mpu_arch_enable(void);
void mpu_arch_disable(void);

#endif /* __ARCH_MPU_H__ */
