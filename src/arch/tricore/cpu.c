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
        for (size_t coreid = 0; coreid < platform.cpu_num; coreid++) {
            if (coreid == cpuid) {
                continue;
            }

            apu_enable_access_cpu((struct PROT_ACCESSEN*)(0xF880E060), coreid);
            //*(unsigned long *)(0xF880E078)= 0x90000000;//CPU0_ACCENDLMU0_RGNLA
            //*(unsigned long *)(0xF880E07C)= 0x90100000;

            apu_enable_access_cpu((struct PROT_ACCESSEN*)(0xF880E400), coreid);
            //*(unsigned long *)(0xF880E418)= 0x90000000;//CPU0_ACCENDLMU0_RGNLA
            //*(unsigned long *)(0xF880E41C)= 0x90080000;

            apu_enable_access_cpu((struct PROT_ACCESSEN*)(0xF884E060), coreid);
            //*(unsigned long *)(0xF884E078)= 0x90000000;//CPU1_ACCENDLMU0_RGNLA
            //*(unsigned long *)(0xF884E07C)= 0x90100000;

            apu_enable_access_cpu((struct PROT_ACCESSEN*)(0xF8840000 + 0xE400), coreid);
            //*(unsigned long *)(0xF884E418)= 0x90000000;//CPU1_ACCENDLMU0_RGNLA
            //*(unsigned long *)(0xF884E41C)= 0x90080000;

            csfr_cpu_pc_write(coreid, load_addr);
            csfr_cpu_bootcon_write(coreid, 0);
        }
    }
}

void cpu_arch_idle(void)
{
    /* __asm volatile("wfi\n\t" ::: "memory"); */
    __asm__ volatile("mov.a %%sp, %[val]\n\r"
        //"j cpu_idle_wakeup\n\r"
        ::[val] "d"(&cpu()->stack[STACK_SIZE]));
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
void abort (void)
{
    ERROR("abort() reached!");
}