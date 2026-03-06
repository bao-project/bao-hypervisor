/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef E3650_UART_H
#define E3650_UART_H

#include <stdint.h>

/* --- Register Bit Definitions --- */

/* MCR0: Module Control Register 0 */
#define MCR0_MODEN         (1u << 0)  /* Module Enable */
#define MCR0_MODRST        (1u << 1)  /* Module Reset */
#define MCR0_DEBUG_SWEN    (1u << 9)  /* Debug Mode Software Enable */
#define MCR0_DEBUG_CTRL    (1u << 10) /* Debug Mode Control */

/* PCR0: Port Control Register 0 */
#define PCR0_TXEN          (1u << 5) /* Transmitter Enable */
#define PCR0_RXEN          (1u << 6) /* Receiver Enable */

/* PCR1: Baud Rate Configuration */
/* Default Baudrate Divider: 83.33MHz / 115200 ~= 723 */
#define UART_BAUDRATE_DIV  (723)

/* PCR8: Filter Control */
#define PCR8_RXSYNCEN      (1u << 17) /* RX Sync Enable */
#define PCR8_RXFILTCTL_VAL (3u << 18) /* RX Filter Control Value (Shifted) */

/* FCR: FIFO Control Register (Shared bits for FCR0/FCR1) */
#define FCR_FIFO_CLR       (1u << 16) /* Clear FIFO */

/* FSR0: FIFO Status Register 0 */
#define FSR0_TX_FULL       (1u << 25) /* TX FIFO Full Flag */

/* --- Register Layout Structure --- */

struct e3650_uart {
    volatile uint32_t mcr0;           /* 0x0 */
    volatile uint32_t prdatainj;      /* 0x4 */
    volatile uint32_t mcr2;           /* 0x8 */
    volatile uint32_t mcr3;           /* 0xC */
    volatile uint32_t mcr4;           /* 0x10 */
    volatile uint32_t reserved1;      /* 0x14 */
    volatile uint32_t msr0;           /* 0x18 */
    volatile uint32_t msr1;           /* 0x1C */
    volatile uint32_t intr0;          /* 0x20 */
    volatile uint32_t reserved2[2];   /* 0x24 ~ 0x28 */
    volatile uint32_t intr3;          /* 0x2C */
    volatile uint32_t inten0;         /* 0x30 */
    volatile uint32_t reserved3[2];   /* 0x34 ~ 0x38 */
    volatile uint32_t inten3;         /* 0x3C */
    volatile uint32_t cmdcsr0;        /* 0x40 */
    volatile uint32_t cmdcsr1;        /* 0x44 */
    volatile uint32_t reserved4[2];   /* 0x48 ~ 0x4C */
    volatile uint32_t fcr0;           /* 0x50 */
    volatile uint32_t fcr1;           /* 0x54 */
    volatile uint32_t reserved5[2];   /* 0x58 ~ 0x5C */
    volatile uint32_t fsr0;           /* 0x60 */
    volatile uint32_t fsr1;           /* 0x64 */
    volatile uint32_t reserved6[2];   /* 0x68 ~ 0x6C */
    volatile uint32_t dmacr;          /* 0x70 */
    volatile uint32_t dmasr;          /* 0x74 */
    volatile uint32_t reserved7[2];   /* 0x78 ~ 0x7C */
    volatile uint32_t pcr0;           /* 0x80 */
    volatile uint32_t pcr1;           /* 0x84 */
    volatile uint32_t pcr2;           /* 0x88 */
    volatile uint32_t pcr3;           /* 0x8C */
    volatile uint32_t pcr4;           /* 0x90 */
    volatile uint32_t pcr5;           /* 0x94 */
    volatile uint32_t pcr6;           /* 0x98 */
    volatile uint32_t pcr7;           /* 0x9C */
    volatile uint32_t pcr8;           /* 0xA0 */
    volatile uint32_t pcr9;           /* 0xA4 */
    volatile uint32_t pcr10;          /* 0xA8 */
    volatile uint32_t pcr11;          /* 0xAC */
    volatile uint32_t pcr12;          /* 0xB0 */
    volatile uint32_t pcr13;          /* 0xB4 */
    volatile uint32_t pcr14;          /* 0xB8 */
    volatile uint32_t pcr15;          /* 0xBC */
    volatile uint32_t reserved8[8];   /* 0xC0 ~ 0xDC */
    volatile uint32_t int_sta;        /* 0xE0 */
    volatile uint32_t int_sta_en;     /* 0xE4 */
    volatile uint32_t int_sig_en;     /* 0xE8 */
    volatile uint32_t reserved9[5];   /* 0xEC ~ 0xFC */
    volatile uint32_t psr0;           /* 0x100 */
    volatile uint32_t psr1;           /* 0x104 */
    volatile uint32_t psr2;           /* 0x108 */
    volatile uint32_t psr3;           /* 0x10C */
    volatile uint32_t psr4;           /* 0x110 */
    volatile uint32_t psr5;           /* 0x114 */
    volatile uint32_t psr6;           /* 0x118 */
    volatile uint32_t psr7;           /* 0x11C */
    volatile uint32_t reserved10[56]; /* 0x120 ~ 0x1FC */
    volatile uint32_t txdr;           /* 0x200 */
    volatile uint32_t reserved11[63]; /* 0x204 ~ 0x2FC */
    volatile uint32_t rxdr;           /* 0x300 */
};

typedef volatile struct e3650_uart bao_uart_t;

void uart_enable(volatile struct e3650_uart* uart);
void uart_init(volatile struct e3650_uart* uart);
void uart_puts(volatile struct e3650_uart* uart, const int8_t* str);
void uart_putc(volatile struct e3650_uart* uart, int8_t c);

#endif /* E3650_UART_H */
