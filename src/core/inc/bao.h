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

#define ERROR(...)                                 \
    do {                                           \
        console_printk("BAO ERROR: " __VA_ARGS__); \
        cpu_panic();                               \
    } while (0)

/**
 * Checks an invariant of the hypervisor itself, never a condition that a guest or the
 * configuration can cause. It compiles to nothing unless ASSERTS is defined (ASSERTS=y, the default
 * in debug builds), but the condition is always parsed, so it must not have side effects.
 */
#define ASSERT(cond)                                                           \
    do {                                                                       \
        if (DEFINED(ASSERTS) && !(cond)) {                                     \
            ERROR("assertion failed: %s:%d: %s\n", __func__, __LINE__, #cond); \
        }                                                                      \
    } while (0)

void init(cpuid_t cpu_id);

/* Stops the calling CPU after a fatal error. Every ERROR() ends here. Defined in cpu.c. */
_Noreturn void cpu_panic(void);

#endif /* __ASSEMBLER__ */

#endif /* __BAO_H__ */
