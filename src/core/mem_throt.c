/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <mem_throt.h>
#include <cpu.h>

void mem_throt_period_timer_callback(irqid_t int_id) {
    timer_disable();
    events_cntr_disable(cpu()->mem_throt.counter_id);
    timer_reschedule_interrupt(cpu()->mem_throt.period_counts);
    events_cntr_set(cpu()->mem_throt.counter_id, cpu()->mem_throt.budget);

    console_printk("Timer Callback\n");
    console_printk("Events counter disable: %d\n", cpu()->mem_throt.counter_id);

    if (cpu()->mem_throt.throttled) {
        events_cntr_irq_enable(cpu()->mem_throt.counter_id);
        cpu()->mem_throt.throttled = false;
    }

    events_cntr_enable(cpu()->mem_throt.counter_id);
    timer_enable();
}



void mem_throt_event_overflow_callback(irqid_t int_id) {
    console_printk("Budget overflow callback for CPU %d\n", cpu()->id);
    events_clear_cntr_ovs(cpu()->mem_throt.counter_id);
    events_cntr_disable(cpu()->mem_throt.counter_id);
    events_cntr_irq_disable(cpu()->mem_throt.counter_id);
    cpu()->mem_throt.throttled = true;
    cpu_standby();
}

void mem_throt_timer_init(irq_handler_t handler) {

    timer_define_irq_callback(handler);
    cpu()->mem_throt.period_counts = timer_init(cpu()->mem_throt.period_us);
}


void mem_throt_events_init(events_enum event, unsigned long budget, irq_handler_t handler) {

    if ((cpu()->mem_throt.counter_id = events_cntr_alloc()) == ERROR_NO_MORE_EVENT_COUNTERS) {
        ERROR("No more event counters!");
    }

    events_set_evtyper(cpu()->mem_throt.counter_id, event);
    events_cntr_set(cpu()->mem_throt.counter_id, budget);
    events_cntr_set_irq_callback(handler, cpu()->mem_throt.counter_id);
    events_clear_cntr_ovs(cpu()->mem_throt.counter_id);
    events_interrupt_enable(cpu()->id);
    events_cntr_irq_enable(cpu()->mem_throt.counter_id);
    events_enable();
    events_cntr_enable(cpu()->mem_throt.counter_id);
}

void mem_throt_init(uint64_t budget, uint64_t period_us) {

    cpu()->mem_throt.throttled = false;
    cpu()->mem_throt.budget = budget;
    cpu()->mem_throt.period_us = period_us;

    mem_throt_timer_init(mem_throt_period_timer_callback);
    mem_throt_events_init(bus_access, cpu()->mem_throt.budget, mem_throt_event_overflow_callback);
}
