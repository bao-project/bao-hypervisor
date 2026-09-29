/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <bao.h>
#include <stdarg.h>

void console_init(void);
void console_write(const char* buf, size_t n);
__attribute__((format(printf, 1, 2))) void console_printk(const char* fmt, ...);

/**
 * @brief Print without taking the console lock
 *
 * For a CPU that may already hold the console lock, such as one reporting a fatal error. The
 * output of other CPUs can interleave with it.
 *
 * @param fmt Format string
 * @param args Arguments for fmt, consumed by the call
 */
void console_vprintk_unlocked(const char* fmt, va_list* args);

/**
 * @brief Print without taking the console lock; see console_vprintk_unlocked()
 *
 * @param fmt Format string, followed by its arguments
 */
__attribute__((format(printf, 1, 2))) void console_printk_unlocked(const char* fmt, ...);

#endif /* __CONSOLE_H__ */
