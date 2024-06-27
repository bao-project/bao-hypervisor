/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __ARCH_TIMER_MOD_H__
#define __ARCH_TIMER_MOD_H__

#include <interrupts.h>
#include <platform.h>

uint64_t timer_arch_init(uint64_t period);
void timer_arch_enable();
void timer_arch_disable();

void timer_arch_reschedule_interrupt(uint64_t count);
uint64_t timer_arch_reschedule_interrupt_us(uint64_t period);

static inline void timer_arch_define_irq_callback(irq_handler_t handler)
{
    interrupts_reserve(platform.arch.generic_timer.timer_id, handler);
    interrupts_arch_enable(platform.arch.generic_timer.timer_id, true);
}

#endif /* __ARCH_TIMER_MOD_H__ */
