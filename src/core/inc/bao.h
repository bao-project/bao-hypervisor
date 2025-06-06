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

#define INFO(...)    console_printk("BAO INFO: " __VA_ARGS__);

#define WARNING(...) console_printk("BAO WARNING: " __VA_ARGS__);

#define ERROR(...)                             \
    console_printk("BAO ERROR: " __VA_ARGS__); \
    while (true) { };

void init(cpuid_t cpu_id);

/* The address where the Bao image is loaded in memory */
extern const uintptr_t img_addr;
/* The address where the data section is loaded in memory */
extern const uintptr_t data_addr;

#endif /* __ASSEMBLER__ */

#endif /* __BAO_H__ */
