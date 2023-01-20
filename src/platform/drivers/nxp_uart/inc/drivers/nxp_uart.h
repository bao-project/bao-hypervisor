/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef UART_NXP_H
#define UART_NXP_H

#include <stdint.h>
#include <stdbool.h>

struct lpuart {
    uint32_t verid; 
    uint32_t param;
    uint32_t global;
    uint32_t pincfg;
    uint32_t baud;
    uint32_t stat;
    uint32_t ctrl;
    uint32_t data;
    uint32_t match;
    uint32_t modir;
    uint32_t fifo;
    uint32_t water;
};

#define LPUART_GLOBAL_RST_BIT  (1U << 1)
#define LPUART_BAUD_80MHZ_115200 ((4 << 24) | (1 << 17) | 138)
#define LPUART_CTRL_TE_BIT (1U << 19)
#define LPUART_STAT_TDRE_BIT (1U << 23)

typedef struct lpuart bao_uart_t;

void uart_enable(volatile struct lpuart *uart);
void uart_init(volatile struct lpuart *uart);
void uart_puts(volatile struct lpuart * uart, const char* str);

#endif /* __UART_NXP_H */
