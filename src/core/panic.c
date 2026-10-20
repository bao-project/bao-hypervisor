/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <console.h>

#ifdef BAO_DEBUG
/* Architectures without a frame-pointer walker report an empty backtrace. */
__attribute__((weak)) size_t cpu_arch_backtrace(uintptr_t fp, uintptr_t* pcs, size_t max_depth)
{
    UNUSED_ARG(fp);
    UNUSED_ARG(pcs);
    UNUSED_ARG(max_depth);
    return 0;
}
#endif

_Noreturn void panic(const char* fmt, ...)
{
    char buf[CONSOLE_PANIC_BUFFER_LEN];
    va_list args;

    va_start(args, fmt);
    console_vprintk(buf, CONSOLE_PANIC_BUFFER_LEN, fmt, &args);
    va_end(args);

    console_printk_unlocked("BAO PANIC: cpu%lu halted\n", cpu()->id);

    if (DEFINED(BAO_DEBUG)) {
        uintptr_t pcs[BACKTRACE_MAX_DEPTH];
        size_t depth =
            cpu_arch_backtrace((uintptr_t)__builtin_frame_address(0), pcs, BACKTRACE_MAX_DEPTH);

        console_printk_unlocked("backtrace:\n");
        for (size_t i = 0; i < depth; i++) {
            console_printk_unlocked("  [<%lx>]\n", (unsigned long)pcs[i]);
        }
    }

    while (true) { }
}
