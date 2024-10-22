/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __mem_throt_H__
#define __mem_throt_H__

#include <timer.h>
#include <events.h>
#include <bitmap.h>



typedef struct mem_throt_info {
	bool is_initialized;
	bool throttled;			 
	size_t counter_id;
	size_t period_us;
	size_t period_counts;
	size_t budget; 
	int64_t budget_left;
	size_t assign_ratio;
}mem_throt_t;

extern size_t global_num_ticket_hypervisor;

void mem_throt_config(size_t period_us, size_t vm_budget, size_t* cpu_ratio);

void mem_throt_init();

void mem_throt_period_timer_callback(irqid_t);

/* budget is used up. PMU generate an interrupt */
void mem_throt_event_overflow_callback(irqid_t); 
void mem_throt_process_overflow(void);

void mem_throt_timer_init(irq_handler_t hander);
void mem_throt_events_init(events_enum event, unsigned long budget, irq_handler_t handler);
void mem_throt_budget_change(uint64_t budget);

#endif /* __mem_throt_H__ */