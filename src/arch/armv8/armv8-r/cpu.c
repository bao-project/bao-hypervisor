/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <arch/gic.h>

// #define MC_ME_PRTN0_PCONF 0x40088100
// #define MC_ME_PRTN0_PUPD 0x40088104
// #define MC_ME_PRTN0_COFB0_CLKEN 0x40088130
// #define MC_ME_PRTN0_STAT 0x40088108
// #define MC_ME_CTL_KEY 0x40088000
// #define MC_ME_CORE0_PCONF 0x40088140
// #define MC_ME_CORE0_PUPD 0x40088144
// #define MC_ME_CORE0_ADDR 0x4008814C
// #define MC_ME_CORE0_STAT 0x40088148

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr)
{
    UNUSED_ARG(cpuid);
    UNUSED_ARG(load_addr);
    // PARTITION1
    // MC_ME.PRTN0_PCONF.R = 1
    // MC_ME.PRTN0_PUPD.R = 1
    // MC_ME.PRTN0_COFB0_CLKEN.R = 0x3FF  ????

    // MC_ME.MC_ME_CTL_KEY.R = 0x00005AF0
    // MC_ME.MC_ME_CTL_KEY.R = 0x0000A50F

    // WAIT FOR  MC_ME.PRTN0_STAT.R == 1

    // MC_ME.MODE_CONF.R = 1

    // CORE 0
    // MC_ME.CORE0_PCONF.R = 1
    // MC_ME.CORE0_ADDR.R = load_addr ?
    // MC_ME.CORE0_PUPD.R = 1

    // MC_ME.MC_ME_CTL_KEY.R = 0x00005AF0
    // MC_ME.MC_ME_CTL_KEY.R = 0x0000A50F

    // WAIT FOR  MC_ME.CORE0_STAT.R == 1

    // REPEAT FOR OTHER CORES
}

void cpu_arch_profile_standby()
{
    __asm__ volatile("wfi");
}

void cpu_arch_profile_powerdown()
{
    __asm__ volatile("wfi");
}
