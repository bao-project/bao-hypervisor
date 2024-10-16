/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <mem_throt.h>
#include <cpu.h>
#include <vm.h>

size_t global_num_ticket_hypervisor;
size_t global_num_ticket_hypervisor_left;
uint8_t counter; //este parece-me estar a mais 


void mem_throt_period_timer_callback(irqid_t int_id) {
    timer_disable();
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    timer_reschedule_interrupt(cpu()->vcpu->vm->mem_throt.period_counts);
    events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->vm->mem_throt.budget * cpu()->vcpu->mem_throt.assign_ratio / 100);

    if (cpu()->vcpu->mem_throt.throttled)  
    {
        events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
        cpu()->vcpu->mem_throt.throttled = false;
    }
    events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    
    if (cpu()->vcpu->vm->master) 
        cpu()->vcpu->vm->mem_throt.budget_left = cpu()->vcpu->vm->mem_throt.budget;
    
    if(++counter == 10)
    {
        global_num_ticket_hypervisor_left = global_num_ticket_hypervisor;
        counter = 0;
    }

    timer_enable();

}

void mem_throt_event_overflow_callback(irqid_t int_id) {

    events_clear_cntr_ovs(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_irq_disable(cpu()->vcpu->vm->mem_throt.counter_id);

    if(cpu()->vcpu->vm->mem_throt.budget_left)
    {
        cpu()->vcpu->vm->mem_throt.budget_left -= (cpu()->vcpu->vm->mem_throt.budget - cpu()->vcpu->vm->mem_throt.budget * cpu()->vcpu->mem_throt.assign_ratio / 100) /cpu()->vcpu->vm->cpu_num;
        mem_throt_budget_change((cpu()->vcpu->vm->mem_throt.budget - (cpu()->vcpu->vm->mem_throt.budget * cpu()->vcpu->mem_throt.assign_ratio / 100)) / cpu()->vcpu->vm->cpu_num);
    }
    else if (global_num_ticket_hypervisor_left)
    {
        global_num_ticket_hypervisor_left--;
        if (1000 - ((cpu()->vcpu->vm->mem_throt.budget - cpu()->vcpu->vm->mem_throt.budget * cpu()->vcpu->mem_throt.assign_ratio) /cpu()->vcpu->vm->cpu_num) > 0)
        cpu()->vcpu->vm->mem_throt.budget_left += 1000 - (cpu()->vcpu->vm->mem_throt.budget - cpu()->vcpu->vm->mem_throt.budget * cpu()->vcpu->mem_throt.assign_ratio) /cpu()->vcpu->vm->cpu_num;
        mem_throt_budget_change((cpu()->vcpu->vm->mem_throt.budget - cpu()->vcpu->vm->mem_throt.budget * cpu()->vcpu->mem_throt.assign_ratio) / cpu()->vcpu->vm->cpu_num);
    }
    else 
    {
        cpu()->vcpu->mem_throt.throttled = true;  
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

inline void mem_throt_budget_change(uint64_t budget) {
    events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->vm->mem_throt.budget);
    events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
}

void mem_throt_config(uint64_t period_us, uint64_t vm_budget, uint64_t* cpu_ratio) {
    static int cpu_max;
    if(vm_budget == 0) return;

    if (cpu()->vcpu->vm->master) 
    {
        cpu()->vcpu->vm->mem_throt.throttled = false;
        cpu()->vcpu->vm->mem_throt.period_us = period_us;
        cpu()->vcpu->vm->mem_throt.budget = vm_budget;
        cpu()->vcpu->vm->mem_throt.budget_left = cpu()->vcpu->vm->mem_throt.budget;
    }

    cpu()->vcpu->mem_throt.assign_ratio = cpu_ratio[cpu()->vcpu->id]; 

    cpu()->vcpu->mem_throt.budget = vm_budget * (cpu()->vcpu->mem_throt.assign_ratio) / 100;

    if(cpu_max += cpu()->vcpu->mem_throt.assign_ratio > 100)
    {
        ERROR("The sum of the ratios is greater than 100");
    }

}

void mem_throt_init() {

    if (cpu()->vcpu->mem_throt.budget == 0) return;

    cpu()->vcpu->vm->mem_throt.budget -= cpu()->vcpu->mem_throt.budget;
    cpu()->vcpu->vm->mem_throt.budget_left = cpu()->vcpu->mem_throt.budget;
    console_printk("%d", cpu()->vcpu->vm->mem_throt.budget_left);
    mem_throt_events_init(bus_access, cpu()->vcpu->mem_throt.budget, mem_throt_event_overflow_callback);

    mem_throt_timer_init(mem_throt_period_timer_callback);
}

void hypervisor_mem_throt_config(size_t num_ticket_hypervisor) {
    global_num_ticket_hypervisor = num_ticket_hypervisor;
}