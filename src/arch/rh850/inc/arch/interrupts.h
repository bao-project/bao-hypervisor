/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>
#include <platform.h>

#define ARCH_MAX_INTERRUPTS    2048
#define MAX_GUEST_INTERRUPTS   PLAT_MAX_INTERRUPTS
#define MAX_INTERRUPT_LINES    PLAT_MAX_INTERRUPTS
#define MAX_INTERRUPT_HANDLERS PLAT_MAX_INTERRUPTS

#endif /* __ARCH_INTERRUPTS_H__ */
