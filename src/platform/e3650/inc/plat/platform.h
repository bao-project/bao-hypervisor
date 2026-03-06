/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <drivers/e3650_uart.h>

#define E3650_UART_BASE 0xF8D60000 // UART15 Base

#define E3650_GICD_BASE 0xF4000000 // GIC Distributor
#define E3650_GICR_BASE 0xF4100000 // GIC Redistributor (Core 0)

#endif                             /* __PLAT_PLATFORM_H__ */
