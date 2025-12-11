/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/tricore_uart.h>
#include <arch/prot.h>

#define NUMERATOR   2 * 4
#define DENOMINATOR 0xD9

static inline void uart_enable_clock(volatile struct asclin_hw* uart, uint32_t clk_mode)
{
    uart->CSR = clk_mode;
    while ((uart->CSR) >> 31)
        ;
}

static inline void uart_disable_clock(volatile struct asclin_hw* uart)
{
    uart->CSR = 0;
    while ((uart->CSR) >> 31)
        ;
}

bool uart_init(volatile struct asclin_hw* uart)
{
    // Enable module
    uart->CLC = 0x0;

    uart_disable_clock(uart);

    // set module to initilise mode
    uart->FRAMECON = 0;
    // set prescaler to 1
    uart->BITCON = 1;

    uart_enable_clock(uart, 2);
    uart_disable_clock(uart);

    // Set baudrate to 115200
    uart->BITCON |= 0x880F0000;
    uart->BRG = NUMERATOR << 16 | DENOMINATOR;

    uart_enable_clock(uart, 2);
    uart_disable_clock(uart);

    uart->RXFIFOCON = 1 << 6; // outlet width = 1
    uart->TXFIFOCON = 1 << 6; // inlet width 1
    uart->DATCON = 0x7;
    uart->FRAMECON |= 0x1 << 16 | 1 << 9;

    uart_enable_clock(uart, 2);

    uart->FLAGSENABLE = 0;
    uart->FLAGSCLEAR = 0xFFFFFFFF;

    uart->FLAGSENABLE = 1 << 16 | 1 << 18 | 1 << 26 | 1 << 27 | 1 << 30; // parity error PEE, frame
                                                                         // error, rxfifooverflow,
                                                                         // rxfifounderflow,
                                                                         // txfifooverflow

    // Enable fifo outlet
    uart->TXFIFOCON |= 0x2;
    uart->RXFIFOCON |= 0x2;

    // Flush TxFIFO
    uart->TXFIFOCON |= 1;
    uart->RXFIFOCON |= 1;

    return true;
}

void uart_enable(volatile struct asclin_hw* uart)
{
    UNUSED_ARG(uart);
}

void uart_disable(volatile struct asclin_hw* uart)
{
    UNUSED_ARG(uart);
}

bool uart_set_baud_rate(volatile struct asclin_hw* uart, uint32_t baud_rate)
{
    UNUSED_ARG(uart);
    UNUSED_ARG(baud_rate);
    return true;
}

uint32_t uart_getc(volatile struct asclin_hw* uart)
{
    UNUSED_ARG(uart);
    return 0;
}

void uart_putc(volatile struct asclin_hw* uart, int8_t c)
{
    uart->TXDATA[0] = (uint32_t)c;
    while (!(uart->FLAGS & (1UL << 31)))
        ;
    uart->FLAGSCLEAR = 0xFFFFFFFF;
}
