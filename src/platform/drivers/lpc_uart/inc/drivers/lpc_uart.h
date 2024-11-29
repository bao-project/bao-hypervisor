/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef LPC_UART_H
#define LPC_UART_H

#include <stdint.h>

struct lpc_uart {
    volatile uint32_t cfg;               /* 0x000 */
    volatile uint32_t ctl;               /* 0x004*/
    volatile uint32_t stat;              /* 0x008 */
    volatile uint32_t intenset;          /* 0x00C */
    volatile uint32_t intenclr;          /* 0x010 */
    uint32_t reserved1[3];               /* 0x014 */
    volatile uint32_t brg;               /* 0x020 */
    volatile const uint32_t intstat;     /* 0x024 */
    volatile uint32_t osr;               /* 0x028 */
    volatile uint32_t addr;              /* 0x02C */
    uint32_t reserved2[884];             /* 0x030 */
    volatile uint32_t fifocfg;           /* 0xE00 */
    volatile uint32_t fifostat;          /* 0xE04 */
    volatile uint32_t fifotrig;          /* 0xE08 */
    uint32_t reserved3;                  /* 0xE0C */
    volatile uint32_t fifointenset;      /* 0xE10 */
    volatile uint32_t fifointenclr;      /* 0xE14 */
    volatile const uint32_t fifointstat; /* 0xE18 */
    uint32_t reserved4;                  /* 0xE1C */
    volatile uint32_t fifowr;            /* 0xE20 */
    uint32_t reserved5[3];               /* 0xE24 */
    volatile uint32_t fiford;            /* 0xE30 */
    uint32_t reserved6[3];               /* 0xE34 */
    volatile uint32_t fifordnopop;       /* 0xE40 */
    uint32_t reserved7;                  /* 0xE44 */
    volatile uint32_t fifosize;          /* 0xE48 */
    uint32_t reserved8[108];             /* 0xE4C */
    volatile uint32_t id;                /* 0xFFC */
};

typedef volatile struct lpc_uart bao_uart_t;

void uart_enable(volatile struct lpc_uart* uart);
void uart_init(volatile struct lpc_uart* uart);
void uart_puts(volatile struct lpc_uart* uart, const int8_t* str);
void uart_putc(volatile struct lpc_uart* uart, int8_t str);

#endif /* LPC_UART_H */
