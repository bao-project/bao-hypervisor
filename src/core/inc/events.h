/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __EVENTS_H__
#define __EVENTS_H__

#include <arch/events.h>

#define EVENTS_CNTR_MAX_NUM EVENTS_ARCH_CNTR_MAX_NUM

typedef size_t events_event_t;

#define EVENTS_EVENT_INVALID ((events_event_t)~0UL)

static inline ssize_t events_cntr_alloc(void)
{
    return events_arch_cntr_alloc();
}

static inline void events_cntr_free(size_t counter)
{
    events_arch_cntr_free(counter);
}

static inline void events_configure_counter_partition(size_t mem_throt_reserved)
{
    events_arch_configure_counter_partition(mem_throt_reserved);
}

static inline void events_enable(void)
{
    events_arch_enable();
}

static inline void events_disable(void)
{
    events_arch_disable();
}

static inline int events_cntr_enable(size_t counter)
{
    return events_arch_cntr_enable(counter);
}

static inline void events_cntr_disable(size_t counter)
{
    events_arch_cntr_disable(counter);
}

static inline void events_cntr_set(size_t counter, unsigned long value)
{
    events_arch_cntr_set(counter, value);
}

static inline uint64_t events_get_cntr_value(size_t counter)
{
    return events_arch_get_cntr_value(counter);
}

static inline void events_set_evtyper(size_t counter, events_event_t event)
{
    events_arch_set_evtyper(counter, (size_t)event);
}

static inline void events_interrupt_enable(cpuid_t cpu_id)
{
    events_arch_interrupt_enable(cpu_id);
}

static inline void events_interrupt_disable(cpuid_t cpu_id)
{
    events_arch_interrupt_disable(cpu_id);
}

static inline void events_cntr_irq_enable(size_t counter)
{
    events_arch_cntr_irq_enable(counter);
}

static inline void events_cntr_irq_disable(size_t counter)
{
    events_arch_cntr_irq_disable(counter);
}

static inline void events_clear_cntr_ovs(size_t counter)
{
    events_arch_clear_cntr_ovs(counter);
}

static inline void events_cntr_set_irq_callback(irq_handler_t handler, size_t counter)
{
    events_arch_cntr_set_irq_callback(handler, counter);
}

#endif /* __EVENTS_H__ */
