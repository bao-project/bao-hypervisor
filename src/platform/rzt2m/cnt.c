/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <cpu.h>
#include <arch/generic_timer.h>
#include <fences.h>

volatile struct generic_timer_cntctrl* cnt;

void rzt2m_cnt_init(void)
{
    /* Map System Counter MMIO */
    vaddr_t cnt_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA,
        platform.arch.generic_timer.base_addr, NUM_PAGES(sizeof(struct generic_timer_cntctrl)));
    if (cnt_ptr == INVALID_VA) {
        ERROR("Maping System Counter MMIO region failed\n");
    }
    cnt = (struct generic_timer_cntctrl*)cnt_ptr;

    cnt->CNTDIF0 = platform.arch.generic_timer.fixed_freq;
    fence_ord_write();

    cnt->CNTCV = 0;
    cnt->CNTCR |= (CNTCR_EN);
    fence_ord_write();

    mem_unmap(&cpu()->as, cnt_ptr, NUM_PAGES(sizeof(struct generic_timer_cntctrl)), true);
}