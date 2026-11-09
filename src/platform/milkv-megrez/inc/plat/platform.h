/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <plat/cpu_ext.h>

/*
 * The EIC7700X serial ports are Synopsys DesignWare APB UARTs:
 *   reg-io-width = <4>  -> 32-bit register accesses
 *   reg-shift    = <2>  -> registers are 4 bytes apart
 *   (registers start at the page base, so no UART8250_PAGE_OFFSET)
 * Must be defined before including the driver header, which derives
 * uart8250_reg_t from it.
 */
#define UART8250_REG_WIDTH (4)

#include <drivers/8250_uart.h>

#define IPIC_SBI    (1)
#define IPIC_ACLINT (2)

#endif /* __PLAT_PLATFORM_H__ */
