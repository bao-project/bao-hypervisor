/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stddef.h>

void console_init(void);
void console_printk(const char* fmt, ...);

#endif /* __CONSOLE_H__ */
