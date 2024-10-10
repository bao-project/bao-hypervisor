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
	int budget;              
	bool throttled;			 
	int counter_id;
	int period_us;
	int period_counts;
	int vm_ticket_num;
	int vm_ticket_num_left;
}mem_throt_t;


void vm_mem_throt_init(uint64_t budget, uint64_t period_us, uint64_t ticket_num);
void mem_throt_period_timer_callback(irqid_t);

/* budget is used up. PMU generate an interrupt */
void mem_throt_event_overflow_callback(irqid_t); 
void mem_throt_process_overflow(void);

void mem_throt_timer_init(irq_handler_t hander);
void mem_throt_events_init(events_enum event, unsigned long budget, irq_handler_t handler);

#endif /* __mem_throt_H__ */