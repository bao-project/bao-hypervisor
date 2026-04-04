/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#ifndef __ASSEMBLER__
#include <cpu.h>
#include <drivers/renesas_rlin3.h>
#include <plat/port.h>
#include <plat/clock.h>
#include <plat/stbc.h>
#include <plat/pbg.h>
#endif /* __ASSEMBLER__ */

/* Interrupts */
#define PLAT_MAX_INTERRUPTS      768

#define PLAT_INTC1_IHVCFG_OFFSET 0x2F0

#ifndef PLAT_CLK_CPU
#define PLAT_CLK_CPU (400000000UL) // 400 MHz. This value depends on CKDIVMD OPTION BYTE.
#endif

#endif                             /* __PLAT_PLATFORM_H__ */
