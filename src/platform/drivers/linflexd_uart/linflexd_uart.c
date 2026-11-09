/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/linflexd_uart.h>
#include <plat/platform.h>

void uart_enable(volatile struct linflexd_uart* uart)
{
    uart->lincr1 &= ~(LINFLEXD_LINCR1_SLEEP | LINFLEXD_LINCR1_INIT);
}

#ifdef EARLY_CONSOLE_DRIVER
static inline void uart_init_common(volatile struct linflexd_uart* uart, bool early)
#else
void uart_init(volatile struct linflexd_uart* uart)
#endif
{
    /* Request init mode */
    uart->lincr1 = (uart->lincr1 & ~(LINFLEXD_LINCR1_SLEEP)) | LINFLEXD_LINCR1_INIT;

    /* Set the baud rate */
    uart->linibrr = UART_CLK_FREQ / (UART_BAUDRATE * LINFLEXD_DEFAULT_OSR);

    /* Setup uart mode with the following configuration
     * word length -> 8 Bits
     * no parity
     * buffer mode
     * 115200
     * Tx mode
     */
    uart->uartcr |= LINFLEXD_UARTCR_WL0;
    uart->uartcr &= ~(LINFLEXD_UARTCR_WL1);
    uart->uartcr &= ~(LINFLEXD_UARTCR_PCE);
    uart->uartcr &= ~(LINFLEXD_UARTCR_TFBM);
    uart->uartcr &= ~(LINFLEXD_UARTCR_RFBM);

    /* Enable TX and RX */
    uart->uartcr |= (LINFLEXD_UARTCR_TXEN | LINFLEXD_UARTCR_RXEN);

#ifdef EARLY_CONSOLE_DRIVER
    if (!early) {
#endif
        uart->linier |= LINFLEXD_LINIER_DRIE;
#ifdef EARLY_CONSOLE_DRIVER
    }
#endif

    /* Sanitize tx empty flag */
    uart->uartsr |= LINFLEXD_UARTSR_DTFTFF;
}

uint32_t uart_getc(volatile struct linflexd_uart* uart)
{
    while (!((uart->lincr1) & LINFLEXD_UARTSR_RMB_MASK))
        ;
    return (uart->bdrm & LINFLEXD_BDRM_DATA4_MASK);
}

void uart_putc(volatile struct linflexd_uart* uart, int8_t c)
{
    uint32_t reg_val;

    do {
        reg_val = (uart->linsr & LINFLEXD_LINSR_LINS_MASK) >> LINFLEXD_LINSR_LINS_SHIFT;
    } while (reg_val == LINFLEXD_LINSR_LINS_DRDT || reg_val == LINFLEXD_LINSR_LINS_HRT);

    uart->bdrl = (uint32_t)c;
}

void uart_puts(volatile struct linflexd_uart* uart, const char* s)
{
    while (*s) {
        uart_putc(uart, (int8_t)*s++);
    }
}

#ifdef EARLY_CONSOLE_DRIVER
void uart_init(volatile struct linflexd_uart* uart)
{
    uart_init_common(uart, false);
}

#include <earlycon.h>

void earlycon_uart_init(void* base)
{
    volatile bao_uart_t* uart = base;
    uart->linier = 0;
    /* Reuse normal setup without its receive-interrupt enable. */
    uart_init_common(uart, true);
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
