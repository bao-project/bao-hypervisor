/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <cpu.h>
#include <drivers/renesas_rlin3.h>
#include <plat/port.h>
#include <plat/clock.h>
#include <plat/stbc.h>
#include <plat/pbg.h>

/* Interrupts */
#define PLAT_MAX_INTERRUPTS     768

void custom_platform_init(void);

#endif /* __PLAT_PLATFORM_H__ */
