/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef UART8250_H
#define UART8250_H

#include <bao.h>
#include <plat/platform.h>

#define UART8250_LSR_THRE   (1U << 5)

#ifndef UART8250_REG_WIDTH
     #error "uart8259 reg width " UART8250_REG_WIDTH "not defined"
#endif

#ifndef UART8250_REG_WIDTH
#define UART8250_REG_WIDTH 4
#endif

#if (UART8250_REG_WIDTH == 1)
    typedef uint8_t uart8250_reg_t;
#elif (UART8250_REG_WIDTH == 4)
    typedef uint32_t uart8250_reg_t;
#else 
    #error "uart8250 reg width " UART8250_REG_WIDTH " not supported"
#endif


#ifndef UART8250_PAGE_OFFSET
#define UART8250_PAGE_OFFSET 0
#endif

struct uart8250_hw {
    uint8_t offset[UART8250_PAGE_OFFSET];
    union {
        uart8250_reg_t thr;
        uart8250_reg_t rbr;
        uart8250_reg_t dll;
    };
    union {
        uart8250_reg_t ier;
        uart8250_reg_t dlh;
    };
    union {
        uart8250_reg_t iir;
        uart8250_reg_t fcr;
    };
    uart8250_reg_t lcr;
    uart8250_reg_t mcr;
    uart8250_reg_t lsr;
    uart8250_reg_t msr;
    uart8250_reg_t sr;
};

#define UART8250_LCR_DLAB   (0x1 << 7)
#define UART8250_LCR_8BIT   (0x3 << 0)

#define UART8250_FCR_TX_CLR     (0x1 << 2)
#define UART8250_FCR_RX_CLR     (0x1 << 1)
#define UART8250_FCR_EN         (0x1 << 0)

typedef struct uart8250_hw bao_uart_t;

void uart_enable(volatile struct uart8250_hw *uart);
void uart_init(volatile struct uart8250_hw *uart);
void uart_puts(volatile struct uart8250_hw *uart, const char* str);

#endif /* UART8250_H */
