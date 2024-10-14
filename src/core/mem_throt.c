/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <mem_throt.h>
#include <cpu.h>
#include <vm.h>

bool is_mem_throt_initialized = false;

void mem_throt_period_timer_callback(irqid_t int_id) {
    timer_disable();
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    timer_reschedule_interrupt(cpu()->vcpu->vm->mem_throt.period_counts);
    events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->mbr_budget);

    if (cpu()->vcpu->vm->mem_throt.throttled) 
    {
        events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
        cpu()->vcpu->vm->mem_throt.throttled = false;
    }
    events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    
    if (cpu()->vcpu->vm->master) 
        cpu()->vcpu->vm->mem_throt.num_tickets_vm_left = cpu()->vcpu->vm->mem_throt.num_tickets_vm;
    cpu()->vcpu->mbr_num_tickets_left = cpu()->vcpu->mbr_num_tickets;

    timer_enable();

}
void mem_throt_event_overflow_callback(irqid_t int_id) {

    events_clear_cntr_ovs(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_irq_disable(cpu()->vcpu->vm->mem_throt.counter_id);

    if(cpu()->vcpu->mbr_num_tickets_left)
    {
        cpu()->vcpu->mbr_num_tickets_left--;
        events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->vm->mem_throt.budget);
        events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
        events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    }
    else if (cpu()->vcpu->vm->mem_throt.num_tickets_vm_left)
    {
        cpu()->vcpu->vm->mem_throt.num_tickets_vm_left--;
        events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->vm->mem_throt.budget);
        events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
        events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
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

void vm_mem_throt_init(uint64_t budget, uint64_t period_us, uint64_t num_tickets_vm) {

    if (cpu()->vcpu->vm->master) 
    {
        cpu()->vcpu->vm->mem_throt.throttled = false;
        cpu()->vcpu->vm->mem_throt.period_us = period_us;
        cpu()->vcpu->vm->mem_throt.num_tickets_vm = num_tickets_vm;
        cpu()->vcpu->vm->mem_throt.num_tickets_vm_left = cpu()->vcpu->vm->mem_throt.num_tickets_vm;
        cpu()->vcpu->vm->mem_throt.budget = budget;
        is_mem_throt_initialized = true;
    }
    while (!is_mem_throt_initialized);
    mem_throt_timer_init(mem_throt_period_timer_callback);
}

void cpu_mem_throt_init(uint64_t budget, uint64_t num_tickets) {
    cpu()->vcpu->mbr_budget = budget/num_tickets;
    cpu()->vcpu->mbr_num_tickets = num_tickets;
    cpu()->vcpu->mbr_num_tickets_left = --num_tickets;
    mem_throt_events_init(bus_access, cpu()->vcpu->mbr_budget, mem_throt_event_overflow_callback);
}
