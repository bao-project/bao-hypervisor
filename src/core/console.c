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
#include <printk.h>
#include <util.h>

static volatile bao_uart_t *uart;
static bool console_ready = false;
static spinlock_t console_lock = SPINLOCK_INITVAL;

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

        console_ready = true;
    }

    cpu_sync_and_clear_msgs(&cpu_glb_sync);
}


void console_write(const char* buf, size_t n)
{
    while (!console_ready);
    for (size_t i = 0; i < n; i++) {
        if (buf[i] == '\n') {
            uart_putc(uart, '\r');
        }
        uart_putc(uart, buf[i]);
    }
}

#define PRINTF_BUFFER_LEN   (256)
static char console_bufffer[PRINTF_BUFFER_LEN];

__attribute__((format(printf, 1, 2))) void console_printk(const char* fmt, ...)
{
    va_list args;
    size_t chars_writen;
    const char* fmt_it = fmt;

    va_start(args, fmt);
    spin_lock(&console_lock);
    while (*fmt_it != '\0') {
        chars_writen =
            vsnprintk(console_bufffer, PRINTF_BUFFER_LEN, &fmt_it, &args);
        console_write(console_bufffer, min(PRINTF_BUFFER_LEN, chars_writen));
    }
    spin_unlock(&console_lock);
    va_end(args);
}
