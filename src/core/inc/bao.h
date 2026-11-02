/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __BAO_H__
#define __BAO_H__

#include <arch/bao.h>

#ifndef __ASSEMBLER__

#include <types.h>
#include <console.h>
#include <util.h>

#define INFO(...)    console_printk("BAO INFO: " __VA_ARGS__)

#define WARNING(...) console_printk("BAO WARNING: " __VA_ARGS__)

#define ERROR(...)   panic("BAO ERROR: " __VA_ARGS__)

/**
 * Checks an invariant of the hypervisor itself, never a condition that a guest or the
 * configuration can cause. It compiles to nothing unless BAO_ASSERTS is defined (ASSERTS=y, the
 * default in debug builds), but the condition is always parsed, so it must not have side effects.
 */
#define ASSERT(cond)                                                     \
    do {                                                                 \
        if (DEFINED(BAO_ASSERTS) && !(cond)) {                           \
            panic("BAO ASSERT: %s:%d: %s\n", __func__, __LINE__, #cond); \
        }                                                                \
    } while (0)

void init(cpuid_t cpu_id);

/**
 * Reports a fatal condition and halts the calling CPU. The message is written without taking the
 * console lock, which the caller may already hold.
 */
__attribute__((format(printf, 1, 2))) _Noreturn void panic(const char* fmt, ...);

#endif /* __ASSEMBLER__ */

#endif /* __BAO_H__ */
