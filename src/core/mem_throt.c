/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <cpu.h>
#include <mem_throt.h>
#include <platform.h>
#include <vm.h>

#ifndef PLAT_MEM_THROT_EVENT
#define PLAT_MEM_THROT_EVENT EVENTS_EVENT_INVALID
#endif

static mem_throt_t mem_throt_state[CPU_MAX];

static inline mem_throt_t* mem_throt_get_state(void)
{
    if (cpu()->id >= CPU_MAX) {
        ERROR("Invalid CPU id = %lu\n", cpu()->id);
    }

    return &mem_throt_state[cpu()->id];
}

static inline void mem_throt_rearm_counter(mem_throt_t* state)
{
    events_cntr_set(state->counter_id, state->budget);

    /* Restore PMU IRQ delivery in case low-power transitions clear PMU/GIC enable
     * bits. */
    events_interrupt_enable(cpu()->id);
    events_clear_cntr_ovs(state->counter_id);
    events_cntr_irq_enable(state->counter_id);
    events_cntr_enable(state->counter_id);
}

static inline events_event_t mem_throt_platform_event(void)
{
    events_event_t event = (events_event_t)PLAT_MEM_THROT_EVENT;

    if (event == EVENTS_EVENT_INVALID) {
        ERROR("Missing platform memory throttling event\n");
    }

    return event;
}

static void mem_throt_period_timer_callback(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    mem_throt_t* state = mem_throt_get_state();

    timer_disable();
    events_cntr_disable(state->counter_id);
    mem_throt_rearm_counter(state);
    state->throttled = false;
    timer_reschedule_interrupt(state->period_counts);
    timer_enable();
}

static void mem_throt_event_overflow_callback(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    mem_throt_t* state = mem_throt_get_state();

    events_cntr_disable(state->counter_id);
    events_cntr_irq_disable(state->counter_id);
    state->throttled = true;
}

void interrupts_post_handler(void)
{
    mem_throt_t* state = mem_throt_get_state();

    if (state->initialized && state->throttled) {
        cpu_standby();
    }
}

static void mem_throt_timer_init(irq_handler_t handler)
{
    mem_throt_t* state = mem_throt_get_state();

    timer_define_irq_callback(handler);
    state->period_counts = timer_reschedule_interrupt_us(state->period_us);
    timer_enable();
}

static void mem_throt_events_init(events_event_t event, unsigned long budget, irq_handler_t handler)
{
    mem_throt_t* state = mem_throt_get_state();
    events_enable();

    ssize_t counter = events_cntr_alloc();
    if (counter == ERROR_NO_MORE_EVENT_COUNTERS) {
        ERROR("No more event counters!\n");
    }

    state->counter_id = (size_t)counter;

    events_set_evtyper(state->counter_id, event);
    events_cntr_set(state->counter_id, budget);
    events_cntr_set_irq_callback(handler, state->counter_id);
    events_clear_cntr_ovs(state->counter_id);
    events_interrupt_enable(cpu()->id);
    events_cntr_irq_enable(state->counter_id);
    events_cntr_enable(state->counter_id);
}

void mem_throt_init(unsigned long budget, uint64_t period_us)
{
    mem_throt_t* state = mem_throt_get_state();

    if (period_us == 0U) {
        ERROR("Invalid memory throttling period\n");
    }

    state->throttled = false;
    state->initialized = false;
    state->budget = budget;
    state->period_us = period_us;

    events_configure_counter_partition(1);
    mem_throt_timer_init(mem_throt_period_timer_callback);
    mem_throt_events_init(mem_throt_platform_event(), state->budget,
                          mem_throt_event_overflow_callback);
    state->initialized = true;
}
