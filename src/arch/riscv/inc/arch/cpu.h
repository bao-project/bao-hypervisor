/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>

#define CPU_HAS_EXTENSION(EXT) (DEFINED(EXT))

extern cpuid_t CPU_MASTER;

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

/**
 * @brief Stop this CPU for good in the WFI low-power state
 * @note Interrupts stay disabled in the hypervisor, but an interrupt pending and enabled in sie
 *       still ends WFI, and WFI may also complete for no reason, so the loop waits again.
 */
static inline _Noreturn void cpu_arch_halt(void)
{
    while (true) {
        __asm__ volatile("wfi" ::: "memory");
    }
}

#endif /* __ARCH_CPU_H__ */
