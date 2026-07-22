/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

/* Agilex5 UART0: DesignWare 8250 (snps,dw-apb-uart) @ 0x10c02000, 32-bit
 * registers (reg-shift=2, reg-io-width=4).
 */
#define UART8250_REG_WIDTH (4)

#include <drivers/8250_uart.h>

#endif /* __PLAT_PLATFORM_H__ */
