/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <arch/sbi.h>
#include <platform.h>

cpuid_t CPU_MASTER __attribute__((section(".data")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    if (cpuid == CPU_MASTER) {
        sbi_init();
        for(size_t hartid = 0; hartid < platform.cpu_num; hartid++){
            if(hartid == cpuid) continue;
            struct sbiret ret = sbi_hart_start(hartid, load_addr, 0);
            if(ret.error < 0) {
                WARNING("failed to wake up hart %d", hartid);
            }
        }
    }
}

void cpu_arch_idle()
{
    asm volatile("wfi\n\t" ::: "memory");
    asm volatile("mv sp, %0\n\r"
                 "j cpu_idle_wakeup\n\r" ::"r"(&cpu()->stack[STACK_SIZE]));
    ERROR("returned from idle wake up");
}
