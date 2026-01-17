/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <arch/srs.h>

cpuid_t CPU_MASTER __attribute__((section(".datanocopy")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    UNUSED_ARG(load_addr);
    volatile unsigned long* bootcrl = (unsigned long*)platform.arch.bootctrl_addr;

    if (cpuid == CPU_MASTER) {
        for (size_t c = 0; c < platform.cpu_num; c++) {
            if (c == cpuid) {
                continue;
            }

            (*bootcrl) |= (1UL << c);
        }
    }

    /* clear exception registers */
    set_eipc(0x0);
    set_fepc(0x0);
    set_mea(0x0);
    set_mei(0x0);
    set_eiic(0x0);
    set_feic(0x0);

    /* set xxPSW.EBV */
    set_eipsw(0x8000);
    set_fepsw(0x8000);

    /* Set snooze time */
    set_snzcfg(SNZCFG_PERIOD);
}

static void reset_stack_and_jump(void* stack_base, void (*jmp_target)(void))
{
    __asm__ volatile("mov   %[stack], sp\n\t"
                     "st.w  lp, -4[sp]\n\t"
                     "add   -4, sp\n\t"
                     "jarl  %[target], lp\n\t"
                     "ld.w  0[sp], lp\n\t"
                     "add   4, sp\n\t"
                     "jmp   [lp]\n\t" : : [stack] "r"(stack_base), [target] "r"(jmp_target)
                     : "lp", "memory");
}

void cpu_arch_standby()
{
    snooze();
    reset_stack_and_jump(&cpu()->stack[STACK_SIZE], cpu_standby_wakeup);
    ERROR("returned from standby wake up");
}

void cpu_arch_powerdown()
{
    snooze();
    reset_stack_and_jump(&cpu()->stack[STACK_SIZE], cpu_powerdown_wakeup);
    ERROR("returned from powerdown wake up");
}
