/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#define UART8250_REG_WIDTH      (4)
#define UART8250_PAGE_OFFSET    (0x40)

#define CPUx_PROTSTMSE_OFFSET   (0xE0D8)
#define PROTSTMSE_SEL_OFFSET    (8UL)
#define CPUx_ACCENSTMCFG_OFFSET (0xE0E0)

#include <drivers/tricore_uart.h>

void platform_cpu_init(cpuid_t cpuid, paddr_t load_addr);

#endif
