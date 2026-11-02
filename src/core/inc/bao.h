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

void init(cpuid_t cpu_id);

/**
 * Reports a fatal condition and halts the calling CPU. The message is written without taking the
 * console lock, which the caller may already hold.
 */
__attribute__((format(printf, 1, 2))) _Noreturn void panic(const char* fmt, ...);

#endif /* __ASSEMBLER__ */

#endif /* __BAO_H__ */
