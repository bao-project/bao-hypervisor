/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <vmm.h>
#include <platform.h>
#include <arch/generic_timer.h>
#include <cpu.h>
#include <fences.h>

static uint32_t timer_freq = 0;

void vmm_arch_profile_init()
{
    if (cpu()->id == CPU_MASTER) {
        /** 
         * Since there is no firmware in cortex-r platforms, we need to
         * initialize the system counter.
         */
        volatile struct generic_timer_cntctrl *timer_ctl;
        timer_ctl = (struct generic_timer_cntctrl* ) mem_alloc_map_dev(
            &cpu()->as, SEC_HYP_PRIVATE,
            platform.arch.generic_timer.base_addr,
            platform.arch.generic_timer.base_addr,
            sizeof(struct generic_timer_cntctrl));

        timer_ctl->CNTCR |= GENERIC_TIMER_CNTCTL_CNTCR_EN;
        fence_ord_write();

        timer_freq = timer_ctl->CNTDIF0;

        mem_unmap(&cpu()->as, (vaddr_t) timer_ctl, 
            sizeof(struct generic_timer_cntctrl), false);
    }

    cpu_sync_barrier(&cpu_glb_sync);

    sysreg_cntfrq_el0_write(timer_freq);
}
