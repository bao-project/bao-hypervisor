
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SAU_H__
#define __ARCH_SAU_H__

#include <bao.h>
#include <arch/sysregs.h>

void sau_arch_init(void);
bool sau_add_region(struct mp_region* reg);
bool sau_remove_region(struct mp_region* reg);

#endif /* __ARCH_SAU_H__ */
