/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/dummy_uart.h>
#include <fences.h>

void uart_init(volatile struct dummy_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_enable(volatile struct dummy_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_putc(volatile struct dummy_uart* uart, int8_t c)
{
    UNUSED_ARG(uart);
    UNUSED_ARG(c);
    return;
}

void uart_puts(volatile struct dummy_uart* uart, int8_t const* str)
{
    UNUSED_ARG(uart);
    UNUSED_ARG(str);
    return;
}
