/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VMM_H__
#define __VMM_H__

#include <bao.h>
#include <arch/vmm.h>
#include <vm.h>

void vmm_init(void);
void vmm_arch_init(void);

void vmm_io_init(void);

#endif /* __VMM_H__ */
