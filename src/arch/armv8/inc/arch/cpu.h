/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>
#include <arch/profile/cpu.h>

#define CPU_MAX (8UL)

struct cpu_arch {
    struct cpu_arch_profile profile;
    unsigned long mpidr;
};

unsigned long cpu_id_to_mpidr(cpuid_t id);
void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr);
void cpu_arch_profile_standby(void);
void cpu_arch_profile_powerdown(void);

extern cpuid_t CPU_MASTER;

/**
 * @brief Stop this CPU for good in the WFI low-power state
 * @note Interrupts stay masked in the hypervisor, but a pending interrupt still ends WFI, so the
 *       loop waits again.
 */
static inline _Noreturn void cpu_arch_halt(void)
{
    while (true) {
        __asm__ volatile("wfi" ::: "memory");
    }
}

#endif /* __ARCH_CPU_H__ */
