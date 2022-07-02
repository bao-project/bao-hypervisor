/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
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
