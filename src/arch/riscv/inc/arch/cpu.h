/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>

extern cpuid_t CPU_MASTER;

struct cpu_arch {
    unsigned hart_id;
    unsigned plic_cntxt;
};

static inline struct cpu* cpu() {
    return (struct cpu*)BAO_CPU_BASE;
}

#endif /* __ARCH_CPU_H__ */
