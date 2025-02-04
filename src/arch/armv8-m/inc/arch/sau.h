
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SAU_H__
#define __ARCH_SAU_H__

#include <bao.h>
#include <arch/sysregs.h>

void sau_arch_init(void);
void sau_arch_enable(void);
bool sau_add_region(struct mp_region* reg, bool locked);
bool sau_remove_region(struct mp_region* reg);
bool sau_update_region(struct mp_region* reg);
bool sau_perms_compatible(uint8_t perms1, uint8_t perms2);

#endif /* __ARCH_SAU_H__ */
