/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>
#include <mem.h>
#include <arch/mpu.h>

#define CPU_HAS_EXTENSION(EXT) (DEFINED(EXT))

extern cpuid_t CPU_MASTER;

struct cpu_arch {
    struct mpu_arch mpu;
    unsigned long state;
};

static inline struct cpu* cpu(void)
{
    register unsigned long a8 __asm__("a8");
    return (struct cpu*)a8;
}
void cpu_arch_idle(void);

#endif /* __ARCH_CPU_H__ */
