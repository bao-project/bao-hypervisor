/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <drivers/cmsdk_uart.h>

#define CMSDK_UART_STATE_TX_BUF_FULL        (1UL << 0)
#define CMSDK_UART_STATE_TX_BUF_OVERRUN     (1UL << 2)
#define CMSDK_UART_STATE_RX_BUF_OVERRUN     (1UL << 3)
#define CMSDK_UART_CTRL_TXEN                (1UL << 0)
#define CMSDK_UART_INTSTATUS_TX_IRQ         (1UL << 0)
#define CMSDK_UART_INTSTATUS_RX_IRQ         (1UL << 1)
#define CMSDK_UART_INTSTATUS_TX_OVERRUN_IRQ (1UL << 2)
#define CMSDK_UART_INTSTATUS_RX_OVERRUN_IRQ (1UL << 3)

void uart_init(volatile struct cmsdk_uart_hw* ptr_uart)
{
    ptr_uart->state = CMSDK_UART_STATE_TX_BUF_OVERRUN | CMSDK_UART_STATE_RX_BUF_OVERRUN;
    ptr_uart->intstatus = CMSDK_UART_INTSTATUS_TX_IRQ | CMSDK_UART_INTSTATUS_RX_IRQ |
        CMSDK_UART_INTSTATUS_TX_OVERRUN_IRQ | CMSDK_UART_INTSTATUS_RX_OVERRUN_IRQ;
}

void uart_enable(volatile struct cmsdk_uart_hw* ptr_uart)
{
    ptr_uart->ctrl = CMSDK_UART_CTRL_TXEN;
}

void uart_putc(volatile struct cmsdk_uart_hw* ptr_uart, int8_t c)
{
    while (ptr_uart->state & CMSDK_UART_STATE_TX_BUF_FULL) { }
    ptr_uart->data = (uint32_t)c;
}
