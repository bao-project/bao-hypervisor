/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <mem_throt.h>
#include <cpu.h>
#include <vm.h>
#include <spinlock.h>

spinlock_t lock;

void mem_throt_period_timer_callback(irqid_t int_id) {
    timer_disable();
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    timer_reschedule_interrupt(cpu()->vcpu->vm->mem_throt.period_counts);
    events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->mem_throt.budget);

    if (cpu()->vcpu->mem_throt.throttled)  
    {
        events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
        cpu()->vcpu->mem_throt.throttled = false;
    }
    events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    
    if (cpu()->vcpu->vm->master) 
        cpu()->vcpu->vm->mem_throt.budget_left = cpu()->vcpu->vm->mem_throt.budget;
    
    timer_enable();

}

void mem_throt_event_overflow_callback(irqid_t int_id) {

    events_clear_cntr_ovs(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_disable(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_irq_disable(cpu()->vcpu->vm->mem_throt.counter_id);

    spin_lock(&lock);
    cpu()->vcpu->vm->mem_throt.budget_left -= (cpu()->vcpu->vm->mem_throt.budget / cpu()->vcpu->vm->cpu_num);
    spin_unlock(&lock);
    
    if(cpu()->vcpu->vm->mem_throt.budget_left >= 0)
    {
        mem_throt_budget_change((cpu()->vcpu->vm->mem_throt.budget / cpu()->vcpu->vm->cpu_num));
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

inline void mem_throt_budget_change(size_t budget) {
    events_cntr_set(cpu()->vcpu->vm->mem_throt.counter_id, cpu()->vcpu->vm->mem_throt.budget);
    events_cntr_enable(cpu()->vcpu->vm->mem_throt.counter_id);
    events_cntr_irq_enable(cpu()->vcpu->vm->mem_throt.counter_id);
}

void mem_throt_config(size_t period_us, size_t vm_budget, size_t* cpu_ratio) {
    if(vm_budget == 0) return;

    if (cpu()->id == cpu()->vcpu->vm->master) 
    {   
        vm_budget = vm_budget / cpu()->vcpu->vm->cpu_num;
        cpu()->vcpu->vm->mem_throt.throttled = false;
        cpu()->vcpu->vm->mem_throt.period_us = period_us;
        cpu()->vcpu->vm->mem_throt.budget = vm_budget * cpu()->vcpu->vm->cpu_num ;
        cpu()->vcpu->vm->mem_throt.budget_left = cpu()->vcpu->vm->mem_throt.budget;
        cpu()->vcpu->vm->mem_throt.is_initialized = true;
    }

    while(cpu()->vcpu->vm->mem_throt.is_initialized != true);

    spin_lock(&lock);

    cpu()->vcpu->mem_throt.assign_ratio = cpu_ratio[cpu()->vcpu->id]; 
    cpu()->vcpu->mem_throt.budget = vm_budget * (cpu()->vcpu->mem_throt.assign_ratio) / 100;
    cpu()->vcpu->vm->mem_throt.budget -= cpu()->vcpu->mem_throt.budget;
    cpu()->vcpu->vm->mem_throt.budget_left -= cpu()->vcpu->mem_throt.budget;
    cpu()->vcpu->vm->mem_throt.assign_ratio += cpu()->vcpu->mem_throt.assign_ratio;
    cpu()->vcpu->vm->mem_throt.counter_id = 1;
    spin_unlock(&lock);


    if(cpu()->vcpu->vm->mem_throt.assign_ratio > 100){
        ERROR("The sum of the ratios is greater than 100");
    }

    
}

void mem_throt_init() {

    if (cpu()->vcpu->mem_throt.budget == 0) return;
    mem_throt_events_init(bus_access, cpu()->vcpu->mem_throt.budget, mem_throt_event_overflow_callback);
    mem_throt_timer_init(mem_throt_period_timer_callback);
}

