/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <arch/sysregs.h>

cpuid_t CPU_MASTER __attribute__((section(".data")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    UNUSED_ARG(cpuid);
    UNUSED_ARG(load_addr);
}

void cpu_arch_standby()
{
    __asm__ volatile("wfi");
}

void cpu_arch_powerdown()
{
    __asm__ volatile("wfi");
}
