/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <platform.h>
#include <arch/generic_timer.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr) {
    /** 
     * Since there is no firmware in cortex-r platforms, we need to
     * initialize the system counter.
     */
    volatile struct generic_timer_cntctrl *timer_ctl =
        (void*) platform.arch.generic_timer.base_addr;
    timer_ctl->CNTCR |= GENERIC_TIMER_CNTCTL_CNTCR_EN;
    sysreg_cntfrq_el0_write(timer_ctl->CNTDIF0);
}

void cpu_arch_profile_idle() {
    asm volatile("wfi");
}
