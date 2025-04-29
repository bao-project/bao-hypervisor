/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef DUMMY_UART_H
#define DUMMY_UART_H

#include <bao.h>
// #include <plat/platform.h>

struct dummy_uart {
    uint32_t dummy_reg; /* 0x0 */
};

typedef volatile struct dummy_uart bao_uart_t;

void uart_enable(volatile struct dummy_uart* uart);
void uart_init(volatile struct dummy_uart* uart);
void uart_puts(volatile struct dummy_uart* uart, const int8_t* str);
void uart_putc(volatile struct dummy_uart* uart, int8_t str);

#endif /* DUMMY_UART_H */
