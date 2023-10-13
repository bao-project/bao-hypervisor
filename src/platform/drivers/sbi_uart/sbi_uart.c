/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/sbi_uart.h>
#include <arch/sbi.h>

bool uart_init(bao_uart_t* uart)
{
    return true;
}
void uart_enable(bao_uart_t* uart) {}

void uart_putc(bao_uart_t* uart, const char c) {
    sbi_console_putchar(c);
}
