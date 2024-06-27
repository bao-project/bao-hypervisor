#ifndef __ARCH_EVENTS_H__
#define __ARCH_EVENTS_H__

#include <arch/pmu.h>

#define EVENTS_ARCH_CNTR_MAX_NUM    PMU_CNTR_MAX_NUM

static inline size_t events_arch_cntr_alloc()
{
    return pmu_cntr_alloc();
}

static inline void events_arch_cntr_free(size_t counter)
{
    pmu_cntr_free(counter);
}

static inline void events_arch_enable(void)
{
    pmu_enable();
}

static inline void events_arch_disable(void)
{
    pmu_disable();
}

static inline int events_arch_cntr_enable(size_t counter)
{
    return pmu_cntr_enable(counter);
}

static inline void events_arch_cntr_disable(size_t counter)
{
    pmu_cntr_disable(counter);
}

static inline void events_arch_cntr_set(size_t counter, unsigned long value)
{
    pmu_cntr_set(counter, value);
}

static inline uint64_t events_arch_get_cntr_value(size_t counter)
{
    return pmu_cntr_get(counter);
}

static inline void events_arch_set_evtyper(size_t counter, size_t event)
{
    pmu_set_evtyper(counter, event);
}

static inline void events_arch_interrupt_enable(uint64_t cpu_id)
{
    pmu_interrupt_enable(cpu_id);
}

static inline void events_arch_interrupt_disable(uint64_t cpu_id)
{
    pmu_interrupt_disable(cpu_id);
}

static inline void events_arch_cntr_irq_enable(size_t counter)
{
    pmu_set_cntr_irq_enable(counter);
}

static inline void events_arch_cntr_irq_disable(size_t counter)
{
    pmu_set_cntr_irq_disable(counter);
}

static inline void events_arch_clear_cntr_ovs(size_t counter)
{
    pmu_clear_cntr_ovs(counter);
}

static inline void events_arch_cntr_set_irq_callback(irq_handler_t handler, size_t counter)
{
    pmu_define_event_cntr_irq_callback(handler, counter);
}

#endif /* __ARCH_EVENTS_H__ */