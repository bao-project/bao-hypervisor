/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __CPU_H__
#define __CPU_H__

#include <bao.h>
#include <arch/cpu.h>

#include <spinlock.h>
#include <mem.h>
#include <list.h>

#define STACK_SIZE (PAGE_SIZE)

#ifndef __ASSEMBLER__

extern uint8_t _cpu_if_base;

typedef struct {
    list_t event_list;

} __attribute__((aligned(PAGE_SIZE))) cpuif_t;

typedef struct vcpu vcpu_t;

typedef struct cpu {
    uint64_t id;
    addr_space_t as;

    vcpu_t* vcpu;

    cpu_arch_t arch;

    uint8_t root_pt[HYP_ROOT_PT_SIZE] __attribute__((aligned(HYP_ROOT_PT_SIZE)));

    uint8_t stack[STACK_SIZE] __attribute__((aligned(PAGE_SIZE)));

    /******************* PUBLIC INTERFACE  **************************/

    cpuif_t interface __attribute__((aligned(PAGE_SIZE)));

} __attribute__((aligned(PAGE_SIZE))) cpu_t;

extern cpu_t cpu;

typedef struct {
    uint32_t handler;
    uint32_t event;
    uint64_t data;
} cpu_msg_t;

void cpu_send_msg(uint64_t cpu, cpu_msg_t* msg);

typedef void (*cpu_msg_handler_t)(uint32_t event, uint64_t data);

#define CPU_MSG_HANDLER(handler, handler_id)                    \
    __attribute__((section(".ipi_cpumsg_handlers"), used))      \
        cpu_msg_handler_t __cpumsg_handler_##handler = handler; \
    __attribute__((section(".ipi_cpumsg_handlers_id"),          \
                   used)) volatile const uint64_t handler_id;

typedef struct {
    spinlock_t lock;
    volatile uint64_t n;
    volatile bool ready;
    volatile uint64_t count;
} cpu_synctoken_t;

extern cpu_synctoken_t cpu_glb_sync;

static inline void cpu_sync_init(cpu_synctoken_t* token, uint64_t n)
{
    token->lock = SPINLOCK_INITVAL;
    token->n = n;
    token->count = 0;
    token->ready = true;
}

static inline void cpu_sync_barrier(cpu_synctoken_t* token)
{
    // TODO: no fence/barrier needed in this function?

    uint64_t next_count = 0;

    while (!token->ready);

    spin_lock(&token->lock);
    token->count++;
    next_count = ALIGN(token->count, token->n);
    spin_unlock(&token->lock);

    while (token->count < next_count);
}

static inline cpuif_t* cpu_if(uint64_t cpu_id)
{
    return ((void*)&_cpu_if_base) +
           (cpu_id * ALIGN(sizeof(cpuif_t), PAGE_SIZE));
}

void cpu_init(uint64_t cpu_id, uint64_t load_addr);
void cpu_send_msg(uint64_t cpu, cpu_msg_t* msg);
bool cpu_get_msg(cpu_msg_t* msg);
void cpu_msg_handler();
void cpu_msg_set_handler(uint64_t id, cpu_msg_handler_t handler);
void cpu_idle();
void cpu_idle_wakeup();

void cpu_arch_init(uint64_t cpu_id, uint64_t load_addr);
void cpu_arch_idle();

#endif /* __ASSEMBLER__ */

#endif /* __CPU_H__ */
