/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <interrupts.h>
#include <platform.h>
#include <objpool.h>
#include <vm.h>
#include <fences.h>

struct cpu_msg_node {
    node_t node;
    struct cpu_msg msg;
};

#define CPU_MSG_POOL_SIZE_DEFAULT (128)
#ifndef CPU_MSG_POOL_SIZE
#define CPU_MSG_POOL_SIZE CPU_MSG_POOL_SIZE_DEFAULT
#endif

OBJPOOL_ALLOC(msg_pool, struct cpu_msg_node, CPU_MSG_POOL_SIZE);

struct cpu_synctoken cpu_glb_sync = {.ready = false};

extern cpu_msg_handler_t ipi_cpumsg_handlers[];
extern uint8_t _ipi_cpumsg_handlers_size;
extern size_t _ipi_cpumsg_handlers_id_start[];
size_t ipi_cpumsg_handler_num;

struct cpuif cpu_interfaces[PLAT_CPU_NUM];

void cpu_init(cpuid_t cpu_id, paddr_t load_addr)
{
    cpu()->id = cpu_id;
    cpu()->handling_msgs = false;
    cpu()->interface = cpu_if(cpu()->id);

    cpu_arch_init(cpu_id, load_addr);

    list_init(&cpu()->interface->event_list);

    if (cpu()->id == CPU_MASTER) {
        cpu_sync_init(&cpu_glb_sync, platform.cpu_num);

        ipi_cpumsg_handler_num =
            ((size_t)&_ipi_cpumsg_handlers_size) / sizeof(cpu_msg_handler_t);
        for (size_t i = 0; i < ipi_cpumsg_handler_num; i++) {
            ((size_t*)_ipi_cpumsg_handlers_id_start)[i] = i;
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);
}

void cpu_send_msg(cpuid_t trgtcpu, struct cpu_msg *msg)
{
    struct cpu_msg_node *node = objpool_alloc(&msg_pool);
    if (node == NULL) ERROR("cant allocate msg node");
    node->msg = *msg;
    list_push(&cpu_if(trgtcpu)->event_list, (node_t *)node);
    fence_sync_write();
    interrupts_cpu_sendipi(trgtcpu, IPI_CPU_MSG);
}

bool cpu_get_msg(struct cpu_msg *msg)
{
    struct cpu_msg_node *node = NULL;
    if ((node = (struct cpu_msg_node *)list_pop(&cpu()->interface->event_list)) !=
        NULL) {
        *msg = node->msg;
        objpool_free(&msg_pool, node);
        return true;
    }
    return false;
}

void cpu_msg_handler()
{
    cpu()->handling_msgs = true;
    struct cpu_msg msg;
    while (cpu_get_msg(&msg)) {
        if (msg.handler < ipi_cpumsg_handler_num &&
            ipi_cpumsg_handlers[msg.handler]) {
            ipi_cpumsg_handlers[msg.handler](msg.event, msg.data);
        }
    }
    cpu()->handling_msgs = false;
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

    if (cpu()->vcpu != NULL) {
        vcpu_run(cpu()->vcpu);
    } else {
        cpu_idle();
    }
}
