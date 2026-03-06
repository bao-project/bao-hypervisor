/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __LINFLEXD_UART_H_
#define __LINFLEXD_UART_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct linflexd_uart {
    uint32_t lincr1;
    uint32_t linier;
    uint32_t linsr;
    uint32_t linesr;
    uint32_t uartcr;
    uint32_t uartsr;
    uint32_t lintcsr;
    uint32_t linocr;
    uint32_t lintocr;
    uint32_t linfbrr;
    uint32_t linibrr;
    uint32_t lincfr;
    uint32_t lincr2;
    uint32_t bidr;
    uint32_t bdrl;
    uint32_t bdrm;
    uint8_t reserved_0[12];
    uint32_t gcr;
    uint32_t uartpto;
    uint32_t uartcto;
    uint32_t dmatxe;
    uint32_t dmarxe;
};

typedef struct linflexd_uart bao_uart_t;

/* For printk */
#define serial_puts(str_buffer)   uart_puts(1, str_buffer)

#define UART_BAUDRATE             (115200U)
#define LINFLEXD_DEFAULT_OSR      (16U)

#define LINFLEXD_LINCR1_INIT      (1U << 0U)
#define LINFLEXD_LINCR1_SLEEP     (1U << 1U)

#define LINFLEXD_UARTCR_WL0       (1U << 1U)
#define LINFLEXD_UARTCR_PCE       (1U << 2U)
#define LINFLEXD_UARTCR_TXEN      (1U << 4U)
#define LINFLEXD_UARTCR_RXEN      (1U << 5U)
#define LINFLEXD_UARTCR_WL1       (1U << 7U)
#define LINFLEXD_UARTCR_TFBM      (1U << 8U)
#define LINFLEXD_UARTCR_RFBM      (1U << 9U)

#define LINFLEXD_UARTSR_DTFTFF    (1U << 1U)
#define LINFLEXD_UARTSR_RMB_MASK  (0x200U)

#define LINFLEXD_LINSR_LINS_MASK  (0xF000U)
#define LINFLEXD_LINSR_LINS_SHIFT (12U)
#define LINFLEXD_LINSR_LINS_DRDT  (0x7U)
#define LINFLEXD_LINSR_LINS_HRT   (0x8U)

#define LINFLEXD_LINIER_DRIE      (1U << 2U)
#define LINFLEXD_BDRM_DATA4_MASK  (0xFFU)

void uart_enable(volatile struct linflexd_uart* uart);
void uart_init(volatile struct linflexd_uart* uart);
uint32_t uart_getc(volatile struct linflexd_uart* uart);
void uart_putc(volatile struct linflexd_uart* uart, int8_t c);
void uart_puts(volatile struct linflexd_uart* uart, const char* s);

#endif /* __LINFLEXD_UART_H_ */
