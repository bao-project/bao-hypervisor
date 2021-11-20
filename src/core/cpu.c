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

#include <cpu.h>
#include <interrupts.h>
#include <platform.h>
#include <objcache.h>
#include <vm.h>
#include <fences.h>

struct cpu_msg_node {
    node_t node;
    struct cpu_msg msg;
};

struct cpu cpu __attribute__((section(".cpu_private")));

struct cpu_synctoken cpu_glb_sync = {.ready = false};

struct objcache msg_cache;
extern cpu_msg_handler_t _ipi_cpumsg_handlers_start;
extern uint64_t _ipi_cpumsg_handlers_size, _ipi_cpumsg_handlers_id_start;
cpu_msg_handler_t *ipi_cpumsg_handlers;
size_t ipi_cpumsg_handler_num;

void cpu_init(uint64_t cpu_id, paddr_t load_addr)
{
    cpu_arch_init(cpu_id, load_addr);

    cpu.id = cpu_id;
    list_init(&cpu.interface.event_list);

    if (cpu.id == CPU_MASTER) {
        cpu_sync_init(&cpu_glb_sync, platform.cpu_num);
        objcache_init(&msg_cache, sizeof(struct cpu_msg_node), SEC_HYP_GLOBAL,
                      false);

        ipi_cpumsg_handlers = &_ipi_cpumsg_handlers_start;
        ipi_cpumsg_handler_num =
            ((size_t)&_ipi_cpumsg_handlers_size) / sizeof(cpu_msg_handler_t);
        for (size_t i = 0; i < ipi_cpumsg_handler_num; i++) {
            (&_ipi_cpumsg_handlers_id_start)[i] = i;
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);
}

void cpu_send_msg(uint64_t trgtcpu, struct cpu_msg *msg)
{
    struct cpu_msg_node *node = objcache_alloc(&msg_cache);
    if (node == NULL) ERROR("cant allocate msg node");
    node->msg = *msg;
    list_push(&cpu_if(trgtcpu)->event_list, (node_t *)node);
    fence_sync_write();
    interrupts_cpu_sendipi(trgtcpu, IPI_CPU_MSG);
}

bool cpu_get_msg(struct cpu_msg *msg)
{
    struct cpu_msg_node *node = NULL;
    if ((node = (struct cpu_msg_node *)list_pop(&cpu.interface.event_list)) !=
        NULL) {
        *msg = node->msg;
        objcache_free(&msg_cache, node);
        return true;
    }
    return false;
}

void cpu_msg_handler()
{
    struct cpu_msg msg;
    while (cpu_get_msg(&msg)) {
        if (msg.handler < ipi_cpumsg_handler_num &&
            ipi_cpumsg_handlers[msg.handler]) {
            ipi_cpumsg_handlers[msg.handler](msg.event, msg.data);
        }
    }
}

void cpu_idle()
{
    cpu_arch_idle();

    /**
     * Should not return here.
     * cpu should "wake up" from idle in cpu_idle_wakeup
     * with a rewinded stack.
     */
    ERROR("Spurious idle wake up");
}

void cpu_idle_wakeup()
{
    if (interrupts_check(IPI_CPU_MSG)) {
        interrupts_clear(IPI_CPU_MSG);
        cpu_msg_handler();
    }

    if (cpu.vcpu != NULL) {
        vcpu_run(cpu.vcpu);
    } else {
        cpu_idle();
    }
}
