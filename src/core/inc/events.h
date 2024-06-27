/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __EVENTS_H__
#define __EVENTS_H__

#include <arch/events.h>

#define EVENTS_CNTR_MAX_NUM    EVENTS_ARCH_CNTR_MAX_NUM


typedef enum {
    mem_access = 0,            // Memory access event.
    l2_cache_access,           // L2 cache access event.
    bus_access,                // Bus access event.
    external_mem_request,      // External memory request event.
    l2_cache_refill            // L2 cache refill event.
} events_enum;


static inline size_t events_cntr_alloc() {
    return events_arch_cntr_alloc();
}

static inline void events_cntr_free(size_t counter) {
    events_arch_cntr_free(counter);
}

static inline void events_enable(void) {
    events_arch_enable();
}

static inline void events_disable(void) {
    events_arch_disable();
}

static inline int events_cntr_enable(size_t counter) {
    return events_arch_cntr_enable(counter);
}

static inline void events_cntr_disable(size_t counter) {
    events_arch_cntr_disable(counter);
}

static inline void events_cntr_set(size_t counter, unsigned long value) {
    events_arch_cntr_set(counter, value);
}

static inline uint64_t events_get_cntr_value(size_t counter) {
    return events_arch_get_cntr_value(counter);
}

static inline void events_set_evtyper(size_t counter, events_enum event) {
    events_arch_set_evtyper(counter, event);
}

static inline void events_interrupt_enable(uint64_t cpu_id) {
    events_arch_interrupt_enable(cpu_id);
}

static inline void events_interrupt_disable(uint64_t cpu_id) {
    events_arch_interrupt_disable(cpu_id);
}

static inline void events_cntr_irq_enable(size_t counter) {
    events_arch_cntr_irq_enable(counter);
}

static inline void events_cntr_irq_disable(size_t counter) {
    events_arch_cntr_irq_disable(counter);
}

static inline void events_clear_cntr_ovs(size_t counter) {
    events_arch_clear_cntr_ovs(counter);
}

static inline void events_cntr_set_irq_callback(irq_handler_t handler, size_t counter) {
    events_arch_cntr_set_irq_callback(handler, counter);
}

#endif /* __EVENTS_H__ */