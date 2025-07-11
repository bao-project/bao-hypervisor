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
    if (cpu_is_master()) {
        unsigned long cur_cntfrq = sysreg_cntfrq_el0_read();
        if (cur_cntfrq != 0UL) {
            timer_freq = (uint32_t)cur_cntfrq;
        } else if (platform.arch.generic_timer.fixed_freq != 0) {
            timer_freq = (uint32_t)platform.arch.generic_timer.fixed_freq;
        } else {
            if (platform.arch.generic_timer.base_addr == 0) {
                ERROR("generic timer base_addr undefined; cannot init system counter");
            }

            volatile struct generic_timer_cntctrl* timer_ctl;
            timer_ctl = (struct generic_timer_cntctrl*)mem_alloc_map_dev(&cpu()->as,
                SEC_HYP_PRIVATE, platform.arch.generic_timer.base_addr,
                platform.arch.generic_timer.base_addr, sizeof(struct generic_timer_cntctrl));

            timer_ctl->CNTCR |= GENERIC_TIMER_CNTCTL_CNTCR_EN;
            fence_ord_write();

            timer_freq = (uint32_t)timer_ctl->CNTDIF0;

            mem_unmap(&cpu()->as, (vaddr_t)timer_ctl, sizeof(struct generic_timer_cntctrl),
                MEM_DONT_FREE_PAGES);
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    /* Program CNTFRQ_EL0 and verify. */
    sysreg_cntfrq_el0_write(timer_freq);
    if (sysreg_cntfrq_el0_read() != (unsigned long)timer_freq) {
        ERROR("failed to program CNTFRQ_EL0 to %u Hz", timer_freq);
    }
}
