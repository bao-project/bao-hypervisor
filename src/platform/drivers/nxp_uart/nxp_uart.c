/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <drivers/nxp_uart.h>

void uart_init(volatile struct lpuart *uart){
    uart->global |= LPUART_GLOBAL_RST_BIT;
    uart->global &= ~LPUART_GLOBAL_RST_BIT; 

    uart->baud = LPUART_BAUD_80MHZ_115200;
}

void uart_enable(volatile struct lpuart *uart){
    uart->ctrl = LPUART_CTRL_TE_BIT;
}

void uart_putc(volatile struct lpuart *uart, char c){
    while(!(uart->stat & LPUART_STAT_TDRE_BIT));
    uart->data = c;
}

void uart_puts(volatile struct lpuart *uart, char const* str){
    while (*str) {
        uart_putc(uart, *str++);
    }
}

