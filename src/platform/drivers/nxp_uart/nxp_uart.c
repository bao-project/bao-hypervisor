/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/nxp_uart.h>

void uart_init(volatile struct lpuart* uart)
{
    uart->global |= LPUART_GLOBAL_RST_BIT;
    uart->global &= ~LPUART_GLOBAL_RST_BIT;

    uart->baud = LPUART_BAUD_80MHZ_115200;
}

void uart_enable(volatile struct lpuart* uart)
{
    uart->ctrl = LPUART_CTRL_TE_BIT;
}

void uart_putc(volatile struct lpuart* uart, int8_t c)
{
    while (!(uart->stat & LPUART_STAT_TDRE_BIT)) { }
    uart->data = (uint32_t)c;
}

#ifdef EARLY_CONSOLE_DRIVER
#include <earlycon.h>

void earlycon_uart_init(void* base)
{
    volatile bao_uart_t* uart = base;
    uart_init(uart);
    uart_enable(uart);
}
#ifdef MEM_PROT_MMU
_Static_assert(sizeof(bao_uart_t) <= PAGE_SIZE, "early UART must fit in its boot mapping");
#endif

void earlycon_uart_putc(void* base, char c)
{
    uart_putc(base, (int8_t)c);
}
#endif
