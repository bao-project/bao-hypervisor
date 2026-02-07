/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/linflexd_uart.h>
#include <platform.h>

void uart_enable(volatile struct linflexd* uart)
{
    /* Request normal mode */
    uart->lincr1 &= ~(LINFLEXD_LINCR1_SLEEP | LINFLEXD_LINCR1_INIT);
}

static void uart_set_baudrate(volatile struct linflexd* uart)
{
    uint32_t ibr;

    /* Compute the value for the integer baudrate */
    ibr = LINFLEXD_9_CLKFREQ / (UART_BAUDRATE * LINFLEXD_9_DFLT_OSR);

    /* Write the computed ibr */
    uart->linibrr = ibr;
}

void uart_init(volatile struct linflexd* uart)
{
    /* Request init mode */
    uart->lincr1 = (uart->lincr1 & ~(LINFLEXD_LINCR1_SLEEP)) | LINFLEXD_LINCR1_INIT;

    /* Setup uart mode with the following configuration
     * word length -> 8 Bits
     * no parity
     * buffer mode
     * 115200
     * Tx mode
     */
    uart->uartcr |= (LINFLEXD_UARTCR_UART | LINFLEXD_UARTCR_WL1 | LINFLEXD_UARTCR_TXEN);

    /* Set the baud rate */
    uart_set_baudrate(uart);

    /* Sanitize tx empty flag */
    uart->uartsr |= LINFLEXD_UARTSR_DTFTFF;
}

void uart_putc(volatile struct linflexd* uart, int8_t c)
{
    uint32_t reg_val;

    do {
        reg_val = (uart->linsr & LINFLEXD_LINSR_LINS_MASK) >> LINFLEXD_LINSR_LINS_SHIFT;
    } while (reg_val == LINFLEXD_LINSR_LINS_DRDT || reg_val == LINFLEXD_LINSR_LINS_HRT);

    uart->bdrl = (uint32_t)c;
}

void uart_puts(volatile struct linflexd* uart, const char* s)
{
    while (*s) {
        uart_putc(uart, (int8_t)*s++);
    }
}
