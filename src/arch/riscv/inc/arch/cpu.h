/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>

#define CPU_HAS_EXTENSION(EXT) (DEFINED(EXT))

extern cpuid_t CPU_MASTER;

/**
 * With a frame pointer, s0 points just above the frame record {caller's s0, ra}, which the
 * prologue stores in the two words below it.
 */
#define ARCH_FRAME_RECORD_OFFSET (2 * REGLEN)
#define ARCH_FRAME_RECORD_ALIGN  (REGLEN)

struct cpu_arch {
#if (IRQC == PLIC)
    unsigned plic_cntxt;
#else
    EMPTY_STRUCT_FIELDS
#endif
};

static inline struct cpu* cpu(void)
{
    return (struct cpu*)BAO_CPU_BASE;
}

#endif /* __ARCH_CPU_H__ */
