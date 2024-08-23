/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>

cpuid_t CPU_MASTER __attribute__((section(".data")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    (void) load_addr;

    if (cpuid == CPU_MASTER) {
        /* sbi_init(); */
        for (size_t coreid = 0; coreid < platform.cpu_num; coreid++) {
            if (coreid == cpuid) {
                continue;
            }
            /* struct sbiret ret = scr_core_start(coreid, load_addr, 0); */
            /* if (ret.error < 0) { */
            /*     WARNING("failed to wake up core %d", coreid); */
            /* } */
        }
    }

    /* Enable virtualization on the CPU */
    /* TODO VCON0 = 1 << 1 (EN) */
}

void cpu_arch_idle(void)
{
    /* __asm volatile("wfi\n\t" ::: "memory"); */
    __asm__ volatile("mov.a %%sp, %[val]\n\r"
                   "j cpu_idle_wakeup\n\r" 
                   ::[val] "d"(&cpu()->stack[STACK_SIZE]));
    ERROR("returned from idle wake up");
}
