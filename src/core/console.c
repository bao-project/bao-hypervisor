/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file console.c
 * @brief This source file implements the Bao Hypervisor's UART-based console. 
 * 
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

/**
 * @brief Initialize the hypervisor console
 * 
 * The master CPU initialize the configured UART device for the hypervisor
 * console and enables it. Other CPUs wait for initialization to complete.
 * 
 * @see cpu_is_master(), mem_alloc_map_dev(), uart_init(), uart_enable()
 * @see platform, PAGE_OFFSET_MASK, NUM_PAGES, cpu_sync_and_clear_msgs()
 * @see fence_sync_write(), cpu(), addr_space, AS_SEC, WARNING()
 */
void console_init(void)
{
    if (cpu_is_master()) {
        if ((platform.console.base & PAGE_OFFSET_MASK) != 0) {
            WARNING("console base must be page aligned");
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

/**
 * @brief Write to the console
 *
 * Writes a buffer of characters to the UART device, converting newlines
 * to carriage-return + newline sequences. Waits for console to be ready.
 *
 * @param buf Pointer to the character buffer to write
 * @param n Number of characters to write from the buffer
 * @see uart_putc(), console_ready, uart
 * 
 */
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
 * @brief Print formatted output to the console
 *
 * Printf-style formatted output function that writes to the console.
 * Thread-safe using a spinlock. Breaks long output into chunks to
 * handle buffer size limitations.
 *
 * @param fmt Printf-style format string
 * @param ... Variable arguments for format string
 * @see vsnprintk(), console_write(), spin_lock(), spin_unlock(), console_bufffer
 * @see PRINTF_BUFFER_LEN, va_start, va_end, va_list, min(), console_lock
 * 
 */
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

/** @}*/
