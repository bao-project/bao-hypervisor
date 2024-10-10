/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <mem_throt.h>
#include <cpu.h>
#include <vm.h>


// enum{THROT_CPU_STANDBY, THROT_CPU_WAKEUP};


// static void mem_throt_callback(uint32_t event, uint64_t data);

// CPU_MSG_HANDLER(mem_throt_callback, THROT_IPI_ID)

// static void mem_throt_callback (uint32_t event, uint64_t data) {
//     console_printk("Received IPI with event %lu on core %d\n", event, cpu()->id);
//     switch(event){
//         case THROT_CPU_STANDBY:
//             // console_printk("Suppose to put %d in standby \n", cpu()->id);
//             break;
//         case THROT_CPU_WAKEUP:
//             // console_printk("Suppose to wake up %d \n", cpu()->id);
//             break;
//         default:
//             console_printk("Unknown event %lu\n", event);
//             break;
//         }
//     }

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
    // uint32_t target_cpu_mask = cpu()->vcpu->vm->cpus;  // Assuming this is a bitmask of all CPUs
    
    // Clear the bit for the current CPU to avoid sending IPI to itself
    // target_cpu_mask &= ~(1ull << cpu()->id);  // Exclude the current CPU from the mask
    // Send IPI to each CPU in the target mask using SGI for standby
    // for (int i = 0; i < sizeof(target_cpu_mask) * 8; i++) {
    //     if (target_cpu_mask & (1ull << i)) {            
    //         // Create the cpu_msg structure here
    //         struct cpu_msg msg = {
    //             .event = THROT_CPU_WAKEUP,
    //             .handler = THROT_IPI_ID
    //             };
    //         console_printk("Sending IPI with event %lu, handler %d to cpu %d\n", msg.event, msg.handler, i);
    //         cpu_send_msg(i, &msg);
    //     }
    //  }

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
    //enhace this part
}


void mem_throt_timer_init(irq_handler_t handler) {
    // console_printk("Memory Throttling Timer Init on cpu %d\n", cpu()->id);
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
