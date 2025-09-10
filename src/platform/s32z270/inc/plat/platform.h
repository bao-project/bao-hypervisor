/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <bao.h>
#include <drivers/linflexd_uart.h>

#define UART_CLK_FREQ           48000000U

#define LINFLEXD_9_TX_PIN       150U
#define LINFLEXD_9_RX_PIN       151U

#define UART_TX_PIN             (LINFLEXD_9_TX_PIN)
#define UART_RX_PIN             (LINFLEXD_9_RX_PIN)
#define SIUL2_IMCR_UART9_RX_OFF (466)

void plat_init(void);

#endif
