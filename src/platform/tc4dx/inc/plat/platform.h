/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#define CPUx_PROTSTMSE_OFFSET   (0xE0D8)
#define PROTSTMSE_SEL_OFFSET    (8UL)
#define CPUx_ACCENSTMCFG_OFFSET (0xE0E0)

#define GPSR_SRC_BASE           (0x1460 / 4) /* First GPSR in TC4Dx */
#define GPSR_MAX_NODES          8

#include <drivers/asclin_uart.h>

void platform_cpu_init(cpuid_t cpuid, paddr_t load_addr);

#endif
