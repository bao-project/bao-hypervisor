/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/lpc_uart.h>
#include <bao.h>
void uart_init(volatile struct lpc_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_enable(volatile struct lpc_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_putc(volatile struct lpc_uart* uart, int8_t c)
{
    UNUSED_ARG(uart);
    UNUSED_ARG(c);
    return;
}

void uart_puts(volatile struct lpc_uart* uart, int8_t const* str)
{
    UNUSED_ARG(uart);
    UNUSED_ARG(str);
    return;
}
