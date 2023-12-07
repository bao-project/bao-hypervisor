/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <drivers/imx_uart.h>

void uart_init(volatile struct imx_uart *uart){
    return;
}

void uart_enable(volatile struct imx_uart *uart){
    return;
}

void uart_putc(volatile struct imx_uart *uart, char c){
    while((uart->ts & 0b1000000) == 0);
    uart->txd = c;
}

void uart_puts(volatile struct imx_uart *uart, char const* str){
    while (*str) {
        uart_putc(uart, *str++);
    }
}

