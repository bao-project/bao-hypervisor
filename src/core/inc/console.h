/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <bao.h>

void console_init(void);
void console_write(const char* buf, size_t n);
__attribute__((format(printf, 1, 2))) void console_printk(const char* fmt, ...);

/* Fatal diagnostics: uses a local buffer and never waits on the console lock. */
__attribute__((format(printf, 1, 2))) void console_printk_unlocked(const char* fmt, ...);

/* Best-effort unlocked diagnostics followed by a permanent local CPU halt. */
__attribute__((noreturn, format(printf, 1, 2))) void console_panic(const char* fmt, ...);

#endif /* __CONSOLE_H__ */
