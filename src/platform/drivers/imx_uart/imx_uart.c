/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/imx_uart.h>
#include <fences.h>

#define IMX_UART_STAT2_TXDC   (1 << 3)
#define IMX_UART_STAT2_TXFULL (1 << 4)

void uart_init(volatile struct imx_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_enable(volatile struct imx_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_putc(volatile struct imx_uart* uart, int8_t c)
{
    while (uart->ts & IMX_UART_STAT2_TXFULL) { }
    uart->txd = (uint32_t)c;
    while (!(uart->stat2 & IMX_UART_STAT2_TXDC)) { }
}

void uart_puts(volatile struct imx_uart* uart, int8_t const* str)
{
    while (*str) {
        uart_putc(uart, *str++);
    }
}
