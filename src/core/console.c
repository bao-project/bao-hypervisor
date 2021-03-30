
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
#include <spinlock.h>

volatile bao_uart_t uart
    __attribute__((section(".devices"), aligned(PAGE_SIZE)));
bool ready = false;
static spinlock_t print_lock = SPINLOCK_INITVAL;

void console_init()
{
    if((platform.console.base & PAGE_OFFSET_MASK) != 0) {
        WARNING("console base must be page aligned");
    }

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
    spin_lock(&print_lock);
    uart_puts(&uart, str);
    spin_unlock(&print_lock);
}
