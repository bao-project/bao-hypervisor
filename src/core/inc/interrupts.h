/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <bao.h>
#include <arch/interrupts.h>

#include <bitmap.h>

struct vm;

typedef void (*irq_handler_t)(irqid_t int_id);

void interrupts_init();
void interrupts_reserve(irqid_t int_id, irq_handler_t handler);

void interrupts_cpu_sendipi(cpuid_t target_cpu, irqid_t ipi_id);
void interrupts_cpu_enable(irqid_t int_id, bool en);

bool interrupts_check(irqid_t int_id);
void interrupts_clear(irqid_t int_id);

enum irq_res { HANDLED_BY_HYP, FORWARD_TO_VM };
enum irq_res interrupts_handle(irqid_t int_id);

void interrupts_vm_assign(struct vm *vm, irqid_t id);
void interrupts_vm_inject(struct vm *vm, irqid_t id);

/* Must be implemented by architecture */

void interrupts_arch_init();
void interrupts_arch_enable(irqid_t int_id, bool en);
bool interrupts_arch_check(irqid_t int_id);
void interrupts_arch_clear(irqid_t int_id);
void interrupts_arch_ipi_send(cpuid_t cpu_target, irqid_t ipi_id);
void interrupts_arch_vm_assign(struct vm *vm, irqid_t id);
void interrupts_arch_vm_inject(struct vm *vm, irqid_t id);
bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t id);

#endif /* __INTERRUPTS_H__ */
