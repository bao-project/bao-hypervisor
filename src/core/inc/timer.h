/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __TIMER_MOD_H__
#define __TIMER_MOD_H__s

#include <interrupts.h>
#include <arch/timer.h>

static inline uint64_t timer_init(uint64_t period) {
    return timer_arch_init(period);
}

static inline void timer_enable() {
    timer_arch_enable();
}

static inline void timer_disable() {
    timer_arch_disable();
}

static inline void timer_define_irq_callback(irq_handler_t handler) {
    timer_arch_define_irq_callback(handler);
}

static inline void timer_reschedule_interrupt(uint64_t count) {
    timer_arch_reschedule_interrupt(count);
}

static inline uint64_t timer_reschedule_interrupt_us(uint64_t period) {
    return timer_arch_reschedule_interrupt_us(period);
}

#endif /* __TIMER_MOD_H__ */