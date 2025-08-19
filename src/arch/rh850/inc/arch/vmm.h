/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_VMM_H__
#define __ARCH_VMM_H__

#include <bao.h>

void vmm_enable_access_to_vm(void);
void vmm_disable_access_to_vm(void);

#endif /* __ARCH_VMM_H__ */