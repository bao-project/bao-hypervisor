/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <platform.h>
#include <arch/gic.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr)
{
    if (cpuid == CPU_MASTER) {
        for (size_t cpu_core_id = 0; cpu_core_id < platform.cpu_num; cpu_core_id++) {
            if (cpu_core_id == cpuid) {
                continue;
            }

            plat_cpu_init(cpu_core_id, load_addr);
        }
    }
}

void cpu_arch_profile_standby()
{
    __asm__ volatile("wfi");
}

void cpu_arch_profile_powerdown()
{
    __asm__ volatile("wfi");
}
