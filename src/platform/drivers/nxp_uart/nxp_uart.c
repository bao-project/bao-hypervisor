/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
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

