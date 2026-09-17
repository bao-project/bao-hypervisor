/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_EVENTS_H__
#define __ARCH_EVENTS_H__

#include <arch/pmu.h>

#define EVENTS_ARCH_CNTR_MAX_NUM PMU_CNTR_MAX_NUM

static inline ssize_t events_arch_cntr_alloc(void)
{
    return pmu_cntr_alloc();
}

static inline void events_arch_cntr_free(size_t counter)
{
    pmu_cntr_free(counter);
}

static inline void events_arch_configure_counter_partition(size_t mem_throt_reserved)
{
    pmu_configure_counter_partition(mem_throt_reserved);
}

/* enable events */
static inline void events_arch_enable(void)
{
    pmu_enable();
}

/* disable events */
static inline void events_arch_disable(void)
{
    pmu_disable();
}

/* enable events counter */
static inline int events_arch_cntr_enable(size_t counter)
{
    return pmu_cntr_enable(counter);
}

/* disable events counter */
static inline void events_arch_cntr_disable(size_t counter)
{
    pmu_cntr_disable(counter);
}

/* set event counter value */
static inline void events_arch_cntr_set(size_t counter, unsigned long value)
{
    pmu_cntr_set(counter, value);
}

/* get event counter value */
static inline uint64_t events_arch_get_cntr_value(size_t counter)
{
    return pmu_cntr_get(counter);
}

/* define event to count */
static inline void events_arch_set_evtyper(size_t counter, size_t event)
{
    pmu_set_evtyper(counter, event);
}

/*enable events interrupt*/
static inline void events_arch_interrupt_enable(cpuid_t cpu_id)
{
    pmu_interrupt_enable(cpu_id);
}

/*disable events interrupt*/
static inline void events_arch_interrupt_disable(cpuid_t cpu_id)
{
    pmu_interrupt_disable(cpu_id);
}

/* enable event counter interrupt */
static inline void events_arch_cntr_irq_enable(size_t counter)
{
    pmu_set_cntr_irq_enable(counter);
}

/* disable event counter interrupt */
static inline void events_arch_cntr_irq_disable(size_t counter)
{
    pmu_set_cntr_irq_disable(counter);
}

static inline void events_arch_clear_cntr_ovs(size_t counter)
{
    pmu_clear_cntr_ovs(counter);
}

/* set event counter interrupt callback */
static inline void events_arch_cntr_set_irq_callback(irq_handler_t handler, size_t counter)
{
    pmu_define_event_cntr_irq_callback(handler, counter);
}

#endif /* __ARCH_EVENTS_H__ */
