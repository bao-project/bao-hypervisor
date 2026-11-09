/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/imx_uart.h>
#include <fences.h>

#define IMX_UART_STAT2_TXDC   (1 << 3)
#define IMX_UART_STAT2_TXFULL (1 << 4)

void uart_init(volatile struct imx_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_enable(volatile struct imx_uart* uart)
{
    UNUSED_ARG(uart);
    return;
}

void uart_putc(volatile struct imx_uart* uart, int8_t c)
{
    while (uart->ts & IMX_UART_STAT2_TXFULL) { }
    uart->txd = (uint32_t)c;
    while (!(uart->stat2 & IMX_UART_STAT2_TXDC)) { }
}

void uart_puts(volatile struct imx_uart* uart, int8_t const* str)
{
    while (*str) {
        uart_putc(uart, *str++);
    }
}

#ifdef EARLY_CONSOLE_DRIVER
#include <earlycon.h>

void earlycon_uart_init(void* base)
{
    volatile bao_uart_t* uart = base;
    /* Keep firmware clock, pins and baud rate; mask interrupt/DMA requests. */
    uart->cr1 &= ~((1U << 15) | (1U << 13) | (1U << 12) | (1U << 9) | (1U << 8) |
        (1U << 6) | (1U << 5) | (1U << 3) | (1U << 2));
    uart->cr2 &= ~((1U << 11) | (1U << 4) | (1U << 3));
    uart->cr3 &= ~((1U << 13) | (1U << 12) | (1U << 11) | (1U << 6) | (1U << 5) |
        (1U << 4) | (1U << 3));
    uart->cr4 &= ~((1U << 8) | (1U << 7) | (1U << 6) | (1U << 3) | (1U << 2) |
        (1U << 1) | (1U << 0));
}
#ifdef MEM_PROT_MMU
_Static_assert(sizeof(bao_uart_t) <= PAGE_SIZE, "early UART must fit in its boot mapping");
#endif

void earlycon_uart_putc(void* base, char c)
{
    uart_putc(base, (int8_t)c);
}
#endif
