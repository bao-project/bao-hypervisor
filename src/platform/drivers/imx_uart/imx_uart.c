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
#include <fences.h>

#define IMX_UART_STAT2_TXDC (1<<3)
#define IMX_UART_STAT2_TXFE (1<<14)
#define IMX_UART_STAT2_TXFULL (1<<4)

void uart_init(volatile struct imx_uart *uart){
    return;
}

void uart_enable(volatile struct imx_uart *uart){
    return;
}

void uart_putc(volatile struct imx_uart *uart, char c){
    while((uart->ts & IMX_UART_STAT2_TXFULL));
    uart->txd = c;
    while (!(uart->stat2 & IMX_UART_STAT2_TXDC));
}

void uart_puts(volatile struct imx_uart *uart, char const* str){
    while (*str) {
        uart_putc(uart, *str++);
    }
}

