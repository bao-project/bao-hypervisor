/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bao.h>
#include <cpu.h>
#include <arch/sbi.h>

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(uint64_t cpuid, uint64_t load_addr)
{
    if (cpuid == CPU_MASTER) {
        sbi_init();
    }
}

void cpu_arch_idle()
{
    asm volatile("wfi\n\t" ::: "memory");
    asm volatile("mv sp, %0\n\r"
                 "j cpu_idle_wakeup\n\r" ::"r"(&cpu.stack[STACK_SIZE]));
}
