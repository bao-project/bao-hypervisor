/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <console.h>
#include <earlycon.h>

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

#if defined(EARLY_CONSOLE_UART) && defined(MEM_PROT_MPU)
        if (mem_reuse_early_mapping(platform.console.base, ALIGN(sizeof(*uart), PAGE_SIZE))) {
            uart = (void*)platform.console.base;
        } else
#endif
        {
            uart = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
                platform.console.base, NUM_PAGES(sizeof(*uart)));
        }

        fence_sync_write();

        uart_init(uart);
        uart_enable(uart);
    }

    /* Install shared console mappings on every CPU. */
    cpu_sync_and_clear_msgs(&cpu_glb_sync);

    if (cpu_is_master()) {
        __atomic_store_n(&console_ready, true, __ATOMIC_RELEASE);
    }
}

static void console_putchar(char c, bool ready)
{
    UNUSED_ARG(ready);
#ifdef CONFIG_EARLYCON
    if (!ready) {
        earlycon_putchar(c);
        return;
    }
#endif
    uart_putc(uart, (int8_t)c);
}

void console_write(const char* buf, size_t n)
{
    bool ready = __atomic_load_n(&console_ready, __ATOMIC_ACQUIRE);
#ifndef CONFIG_EARLYCON
    while (!ready) {
        ready = __atomic_load_n(&console_ready, __ATOMIC_ACQUIRE);
    }
#endif
    for (size_t i = 0; i < n; i++) {
        if (buf[i] == '\n') {
            console_putchar('\r', ready);
        }
        console_putchar(buf[i], ready);
    }
}

#define PRINTF_BUFFER_LEN (256)
static char console_bufffer[PRINTF_BUFFER_LEN];

__attribute__((format(printf, 1, 2))) void console_printk(const char* fmt, ...)
{
    va_list args;
    size_t chars_writen;
    const char* fmt_it = fmt;

    va_start(args, fmt);
    spin_lock(&console_lock);
    while (*fmt_it != '\0') {
        chars_writen = vsnprintk(console_bufffer, PRINTF_BUFFER_LEN, &fmt_it, &args);
        console_write(console_bufffer, min(PRINTF_BUFFER_LEN, chars_writen));
    }
    spin_unlock(&console_lock);
    va_end(args);
}

static void console_vprintk_unlocked(const char* fmt, va_list* args)
{
#ifndef CONFIG_EARLYCON
    /* Fatal traps must reach halt even before the normal console is ready. */
    if (!__atomic_load_n(&console_ready, __ATOMIC_ACQUIRE)) {
        return;
    }
#endif
    /* Do not overwrite a normal print interrupted while holding the lock. */
    char buf[PRINTF_BUFFER_LEN];
    const char* fmt_it = fmt;
    while (*fmt_it != '\0') {
        size_t chars_written = vsnprintk(buf, PRINTF_BUFFER_LEN, &fmt_it, args);
        console_write(buf, min(PRINTF_BUFFER_LEN, chars_written));
    }
}

__attribute__((format(printf, 1, 2))) void console_printk_unlocked(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    console_vprintk_unlocked(fmt, &args);
    va_end(args);
}

__attribute__((noreturn, format(printf, 1, 2))) void console_panic(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    console_vprintk_unlocked(fmt, &args);
    va_end(args);
    cpu_halt();
}
