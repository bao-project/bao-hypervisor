/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <srs.h>

cpuid_t CPU_MASTER __attribute__((section(".datanocopy")));

#define SNZCFG_PERIOD (uint8_t)(~0)

static inline uint64_t read_tscount64(void)
{
    uint32_t hi1, lo, hi2;

    do {
        hi1 = srs_tscounth_read();
        lo = srs_tscountl_read();
        hi2 = srs_tscounth_read();
        /* check against overflows */
    } while (hi1 != hi2);

    return ((uint64_t)hi2 << 32) | lo;
}

static void wait_us(unsigned long us)
{
    /* enable counter */
    srs_tsctrl_write(TSCTRL_CEN_SET(srs_tsctrl_read()));
    uint64_t before = 0;
    uint64_t target = us * (PLAT_CLK_CPU / (1000UL * 1000UL));

    before = read_tscount64();
    while ((read_tscount64() - before) < target) { }

    /* disable counter */
    srs_tsctrl_write(TSCTRL_CEN_CLR(srs_tsctrl_read()));
}

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
            /* wait 100us as per the manual */
            wait_us(100);
        }
    }

    /* set xxPSW.EBV */
    srs_eipsw_write(0x8000);
    srs_fepsw_write(0x8000);

    /* Set snooze time */
    srs_snzcfg_write(SNZCFG_PERIOD);
}

static void reset_stack_and_jump(void* stack_base, void (*jmp_target)(void))
{
    __asm__ volatile("mov   %[stack], sp\n\t"
                     "jarl  %[target], lp\n\t" : : [stack] "r"(stack_base), [target] "r"(jmp_target)
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
