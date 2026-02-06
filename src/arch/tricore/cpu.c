/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <arch/csfrs.h>
#include <arch/prot.h>

cpuid_t CPU_MASTER __attribute__((section(".data")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    if (cpuid == CPU_MASTER) {
        platform_cpu_init(cpuid, load_addr);
    }
}

void cpu_arch_idle(void)
{
    __asm__ volatile("mov.a %%sp, %[val]\n\r" ::[val] "d"(&cpu()->stack[STACK_SIZE]));
    ERROR("returned from idle wake up");
}

void cpu_arch_powerdown(void)
{
    /* Is this the right instruction?
    should we switch modes in the SMM (system mode management) ?*/
    __asm__ volatile("wait");
}

void cpu_arch_standby(void)
{
    /* Is this the right instruction?
    should we switch modes in the SMM (system mode management) ?*/
    __asm__ volatile("wait");
}

/* The current GCC injects calls to abort() in some places, which
   results in undefined references.
   For this reason we define our own abort() for this architecture. */
void abort(void)
{
    ERROR("abort() reached!");
}
