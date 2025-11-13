/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CMSDK_UART_H_
#define __CMSDK_UART_H_

#include <stdint.h>

struct cmsdk_uart_hw {
    volatile uint32_t data;
    volatile uint32_t state;
    volatile uint32_t ctrl;
    volatile uint32_t intstatus;
    volatile uint32_t bauddiv;
} __attribute__((packed));

typedef struct cmsdk_uart_hw bao_uart_t;

void uart_enable(volatile struct cmsdk_uart_hw* ptr_uart);
void uart_init(volatile struct cmsdk_uart_hw* ptr_uart);
void uart_putc(volatile struct cmsdk_uart_hw* ptr_uart, int8_t c);

#endif /* __CMSDK_UART_H_ */
