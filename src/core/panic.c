/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <console.h>

_Noreturn void panic(const char* fmt, ...)
{
    char buf[CONSOLE_PANIC_BUFFER_LEN];
    va_list args;

    va_start(args, fmt);
    console_vprintk(buf, CONSOLE_PANIC_BUFFER_LEN, fmt, &args);
    va_end(args);

    console_printk_unlocked("BAO PANIC: cpu%lu halted\n", cpu()->id);

    while (true) { }
}
