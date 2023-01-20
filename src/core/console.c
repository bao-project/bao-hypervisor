/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <console.h>

#include <platform.h>
#include <cpu.h>
#include <mem.h>
#include <fences.h>
#include <spinlock.h>

volatile bao_uart_t *uart;
bool ready = false;
static spinlock_t print_lock = SPINLOCK_INITVAL;

void console_init()
{
    if (cpu()->id == CPU_MASTER) {
        if((platform.console.base & PAGE_OFFSET_MASK) != 0) {
            WARNING("console base must be page aligned");
        }

        uart = (void*) mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
            platform.console.base, NUM_PAGES(sizeof(*uart)));

        fence_sync_write();

        uart_init(uart);
        uart_enable(uart);

        ready = true;
    }

    cpu_sync_and_clear_msgs(&cpu_glb_sync);
}

void console_write(char const* const str)
{
    if (!ready) return;
    spin_lock(&print_lock);
    uart_puts(uart, str);
    spin_unlock(&print_lock);
}
