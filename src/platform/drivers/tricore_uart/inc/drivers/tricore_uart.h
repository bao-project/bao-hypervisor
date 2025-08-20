/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __UART_TRICORE_H
#define __UART_TRICORE_H

#include <stdint.h>
#include <stdbool.h>
#include <arch/prot.h>

struct asclin0_hw {
    volatile uint8_t RESERVED[0x200];
};

struct rst {
    volatile uint32_t CTRLA;
    volatile uint32_t CTRLB;
    volatile uint32_t STAT;
};

struct asclin_hw {
    volatile uint32_t CLC;
    volatile uint32_t OCS;
    volatile uint32_t ID;
    struct rst RST;
    volatile uint8_t RESERVED[0x20 - 0x14 - 0x4];
    volatile uint32_t PROTE;
    volatile uint32_t PROTSE;
    volatile uint8_t RESERVED1[0x40 - 0x24 - 0x4];
    struct PROT_ACCESSEN ACCEN;
    volatile uint8_t RESERVED2[0x100 - 0x54 - 0x4];
    volatile uint32_t IOCR;
    volatile uint32_t TXFIFOCON;
    volatile uint32_t RXFIFOCON;
    volatile uint32_t BITCON;
    volatile uint32_t FRAMECON;
    volatile uint32_t DATCON;
    volatile uint32_t BRG;
    volatile uint32_t BRD;
    volatile uint32_t LINCON;
    volatile uint32_t LINBTIMER;
    volatile uint32_t LINHTIMER;
    volatile uint32_t FLAGS;
    volatile uint32_t FLAGSSET;
    volatile uint32_t FLAGSCLEAR;
    volatile uint32_t FLAGSENABLE;
    volatile uint32_t CSR;
    volatile uint32_t TXDATA[8];
    volatile uint32_t RXDATA[8];
    volatile uint32_t RXDATAD;
    volatile uint8_t RESERVED3[0x200 - 0x180 - 0x4];
};

typedef struct asclin_hw bao_uart_t;

/** Public Tricore UART interfaces */

bool uart_init(volatile struct asclin_hw* uart);
void uart_enable(volatile struct asclin_hw* uart);
void uart_disable(volatile struct asclin_hw* uart);
bool uart_set_baud_rate(volatile struct asclin_hw* uart, uint32_t baud_rate);
uint32_t uart_getc(volatile struct asclin_hw* uart);
void uart_putc(volatile struct asclin_hw* uart, int8_t c);

#endif /* __UART_TRICORE_H */
