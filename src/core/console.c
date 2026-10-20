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

static volatile bao_uart_t* uart;
static bool console_ready = false;
static spinlock_t console_lock = SPINLOCK_INITVAL;

void console_init(void)
{
    if (cpu_is_master()) {
        if ((platform.console.base & PAGE_OFFSET_MASK) != 0) {
            WARNING("console base must be page aligned\n");
        }

        uart = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
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
    while (!console_ready)
        ;
    for (size_t i = 0; i < n; i++) {
        if (buf[i] == '\n') {
            uart_putc(uart, '\r');
        }
        uart_putc(uart, (int8_t)buf[i]);
    }
}

#define PRINTF_BUFFER_LEN (256)
static char console_bufffer[PRINTF_BUFFER_LEN];

/**
 * Formats fmt through buf, buf_len bytes at a time, and writes it out without taking the console
 * lock. Kept out of line on purpose: it is the single copy of the formatting loop shared by the
 * locked printk, the unlocked printk and panic().
 */
__attribute__((noinline)) void console_vprintk(char* buf, size_t buf_len, const char* fmt,
    va_list* args)
{
    const char* fmt_it = fmt;

    while (*fmt_it != '\0') {
        size_t chars_writen = vsnprintk(buf, buf_len, &fmt_it, args);
        console_write(buf, min(buf_len, chars_writen));
    }
}

__attribute__((format(printf, 1, 2))) void console_printk(const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    spin_lock(&console_lock);
    console_vprintk(console_bufffer, PRINTF_BUFFER_LEN, fmt, &args);
    spin_unlock(&console_lock);
    va_end(args);
}

/**
 * Lock-free variant for the panic path: the calling CPU may already hold console_lock, so this
 * formats into a small stack buffer and writes without taking the lock. Its output may interleave
 * with the output of other CPUs.
 */
__attribute__((format(printf, 1, 2))) void console_printk_unlocked(const char* fmt, ...)
{
    char buf[CONSOLE_PANIC_BUFFER_LEN];
    va_list args;

    va_start(args, fmt);
    console_vprintk(buf, CONSOLE_PANIC_BUFFER_LEN, fmt, &args);
    va_end(args);
}
