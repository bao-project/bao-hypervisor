/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <arch/sysregs.h>
#include <arch/core_impl.h>

cpuid_t CPU_MASTER __attribute__((section(".datanocopy")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    cpu()->arch.mpidr = sysreg_mpidr_el1_read();
    cpu_arch_profile_init(cpuid, load_addr);
    cpu_arch_core_impl_init();
}

unsigned long cpu_id_to_mpidr(cpuid_t id)
{
    return platform_arch_cpuid_to_mpidr(&platform, id);
}

void cpu_arch_standby()
{
    cpu_arch_profile_standby();

    /*
     * In case the profile implementation does not jump to a predefined wake-up point and just
     * returns from the profile, manually rewind stack and jump to standby wake up. Therefore, we
     * should not return after this point.
     */
    __asm__ volatile("mov sp, %0\n\r"
                     "b cpu_standby_wakeup\n\r" ::"r"(&cpu()->stack[STACK_SIZE]));

    ERROR("returned from standby wake up");
}

void cpu_arch_powerdown()
{
    cpu_arch_profile_powerdown();

    /*
     * In case the profile implementation does not jump to a predefined wake-up point and just
     * returns from the profile, manually rewind stack and jump to powerdown wake up. Therefore, we
     * should not return after this point.
     */
    __asm__ volatile("mov sp, %0\n\r"
                     "b cpu_powerdown_wakeup\n\r" ::"r"(&cpu()->stack[STACK_SIZE]));

    ERROR("returned from powerdown wake up");
}
