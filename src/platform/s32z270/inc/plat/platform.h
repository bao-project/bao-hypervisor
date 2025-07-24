/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <bao.h>
#include <drivers/linflexd_uart.h>

void plat_cpu_init(cpuid_t cpuid, paddr_t load_addr);

#endif
