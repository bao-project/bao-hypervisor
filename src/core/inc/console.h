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
#define CONSOLE_PANIC_BUFFER_LEN (64)
void console_vprintk(char* buf, size_t buf_len, const char* fmt, va_list* args);
__attribute__((format(printf, 1, 2))) void console_printk_unlocked(const char* fmt, ...);

#endif /* __CONSOLE_H__ */
