/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#ifndef __SBI_UART_H__
#define __SBI_UART_H__

#include <bao.h>

typedef volatile uint8_t bao_uart_t;

bool uart_init(bao_uart_t* uart);
void uart_enable(bao_uart_t* uart);
void uart_puts(bao_uart_t* uart,const char *s);

#endif /* __SBI_UART_H__ */
