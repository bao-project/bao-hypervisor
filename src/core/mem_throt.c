/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <mem_throt.h>
#include <cpu.h>
#include <vm.h>


void mem_throt_period_timer_callback(irqid_t int_id) {

    timer_disable();
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    timer_reschedule_interrupt(cpu()->vcpu->vm->mem_throt.period_counts);
    events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->vm->mem_throt.budget);

    if (cpu()->vcpu->vm->mem_throt.throttled) 
    {
        events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
        cpu()->vcpu->vm->mem_throt.throttled = false;
    }
    events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    
    if (cpu()->vcpu->vm->master) 
        cpu()->vcpu->vm->mem_throt.ticket_num_left = cpu()->vcpu->vm->mem_throt.ticket_num;
    
    timer_enable();

}
void mem_throt_event_overflow_callback(irqid_t int_id) {

    events_clear_cntr_ovs(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_irq_disable(cpu()->vcpu->vm->mem_throt.counter_id);

    if(cpu()->vcpu->vm->mem_throt.ticket_num_left > 0)
    {
        cpu()->vcpu->vm->mem_throt.ticket_num_left--;
        events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->vm->mem_throt.budget);
        events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);

    }
    else
    {
        cpu()->vcpu->vm->mem_throt.throttled = true;  
        cpu_standby();
    }
}


void mem_throt_timer_init(irq_handler_t handler) {
    timer_define_irq_callback(handler);
    cpu()->vcpu->vm->mem_throt.period_counts = timer_init(cpu()->vcpu->vm->mem_throt.period_us);
}


void mem_throt_events_init(events_enum event, unsigned long budget, irq_handler_t handler) {

    if ((cpu()->vcpu->vm->mem_throt.counter_id = events_cntr_alloc()) == ERROR_NO_MORE_EVENT_COUNTERS) {
        ERROR("No more event counters!");
    }

    events_set_evtyper(cpu()->vcpu->vm->mem_throt.counter_id, event);
    events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, budget);
    events_cntr_set_irq_callback(handler, cpu()->vcpu->vm->mem_throt.counter_id);
    events_clear_cntr_ovs(cpu()->vcpu->vm->mem_throt.counter_id);
    events_interrupt_enable(cpu()->id);
    events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    events_enable();
    events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
}

void mem_throt_init(uint64_t budget, uint64_t period_us, uint64_t ticket_num) {

    if (cpu()->vcpu->vm->master) 
    {
        cpu()->vcpu->vm->mem_throt.throttled = false;
        cpu()->vcpu->vm->mem_throt.period_us = period_us;
        cpu()->vcpu->vm->mem_throt.ticket_num = ticket_num - cpu()->vcpu->vm->cpu_num;
        cpu()->vcpu->vm->mem_throt.ticket_num_left = cpu()->vcpu->vm->mem_throt.ticket_num;
        cpu()->vcpu->vm->mem_throt.budget = budget / cpu()->vcpu->vm->mem_throt.ticket_num;
        is_mem_throt_initialized = true;
    }
    while (!is_mem_throt_initialized);
    mem_throt_timer_init(mem_throt_period_timer_callback);
    mem_throt_events_init(bus_access, cpu()->vcpu->vm->mem_throt.budget, mem_throt_event_overflow_callback);
}
