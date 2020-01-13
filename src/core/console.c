
/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bao.h>
#include <console.h>

#include <platform.h>
#include <cpu.h>
#include <mem.h>
#include <fences.h>

volatile bao_uart_t uart
    __attribute__((section(".devices"), aligned(PAGE_SIZE)));
static bool ready = false;

void console_init()
{
    mem_map_dev(&cpu.as, (void*)&uart, platform.console.base,
                NUM_PAGES(sizeof(uart)));

    fence_sync_write();

    uart_init(&uart);
    uart_enable(&uart);

    ready = true;
}

void console_write(char const* const str)
{
    if (!ready) return;
    uart_puts(&uart, str);
}