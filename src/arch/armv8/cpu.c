/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Gero Schwaericke <gero.schwaericke@tum.de>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <arch/sysregs.h>

cpuid_t CPU_MASTER __attribute__((section(".data")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{   
    cpu()->arch.mpidr = sysreg_mpidr_el1_read();
    cpu_arch_profile_init(cpuid, load_addr);
}

unsigned long cpu_id_to_mpidr(cpuid_t id)
{
    return platform_arch_cpuid_to_mpdir(&platform, id);
}

void cpu_arch_idle()
{
    cpu_arch_profile_idle();

    /*
     * In case the profile implementation does not jump to a predefined wake-up
     * point and just returns from the profile, manually rewind stack and jump 
     * to idle wake up. Therefore, we should not return after this point.
     */
    asm volatile(
        "mov sp, %0\n\r"
        "b cpu_idle_wakeup\n\r"
        ::"r"(&cpu()->stack[STACK_SIZE]));

    ERROR("returned from idle wake up");
}
