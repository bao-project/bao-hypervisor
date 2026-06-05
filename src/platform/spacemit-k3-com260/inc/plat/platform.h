/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

/* K3 UART0: 16550-compatible, 32-bit registers (reg-shift=2, reg-io-width=4),
 * registers start at the page base (no page offset). */
#define UART8250_REG_WIDTH (4)

#include <drivers/8250_uart.h>

/* The X100 harts implement the Sstc extension (per-hart supervisor timer). */
#define CPU_EXT_SSTC 1

#define IPIC_SBI     (1)
#define IPIC_ACLINT  (2)

#endif
