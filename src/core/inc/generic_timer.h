/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __GENERIC_TIMER_H__
#define __GENERIC_TIMER_H__

#include <timer.h>

static inline uint64_t generic_timer_init(uint64_t period)
{
    return timer_init(period);
}

static inline void generic_timer_enable(void)
{
    timer_enable();
}

static inline void generic_timer_disable(void)
{
    timer_disable();
}

static inline void generic_timer_define_irq_callback(irq_handler_t handler)
{
    timer_define_irq_callback(handler);
}

static inline void generic_timer_reschedule_interrupt(uint64_t count)
{
    timer_reschedule_interrupt(count);
}

static inline uint64_t generic_timer_reschedule_interrupt_us(uint64_t period)
{
    return timer_reschedule_interrupt_us(period);
}

#endif /* __GENERIC_TIMER_H__ */
