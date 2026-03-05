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

struct cpu_synctoken cpu_glb_sync = { .ready = false };

extern cpu_msg_handler_t ipi_cpumsg_handlers[];
extern size_t _ipi_cpumsg_handlers_id_start[];
extern size_t _ipi_cpumsg_handlers_id_end[];
static size_t ipi_cpumsg_handler_num;

struct cpuif cpu_interfaces[PLAT_CPU_NUM];

void cpu_init(cpuid_t cpu_id)
{
    cpu()->id = cpu_id;
    cpu()->handling_msgs = false;
    cpu()->interface = cpu_if(cpu()->id);

    cpu_arch_init(cpu_id, img_addr);

    cq_init(cpu()->interface->msgs);

    if (cpu_is_master()) {
        cpu_sync_init(&cpu_glb_sync, platform.cpu_num);

        ipi_cpumsg_handler_num =
            (size_t)(_ipi_cpumsg_handlers_id_end - _ipi_cpumsg_handlers_id_start);
        for (size_t i = 0; i < ipi_cpumsg_handler_num; i++) {
            ((size_t*)_ipi_cpumsg_handlers_id_start)[i] = i;
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);
}

void cpu_send_msg(cpuid_t trgtcpu, struct cpu_msg* msg)
{
    cq_add(cpu_if(trgtcpu)->msgs, *msg);
    fence_sync_write();
    interrupts_cpu_sendipi(trgtcpu);
}

bool cpu_get_msg(struct cpu_msg* msg)
{
    return cq_pop(cpu()->interface->msgs, msg);
}

void cpu_msg_handler(void)
{
    cpu()->handling_msgs = true;
    struct cpu_msg msg;
    while (cpu_get_msg(&msg)) {
        if (msg.handler < ipi_cpumsg_handler_num && ipi_cpumsg_handlers[msg.handler]) {
            ipi_cpumsg_handlers[msg.handler](msg.event, msg.data);
        }
    }
    cpu()->handling_msgs = false;
}

void cpu_standby(void)
{
    cpu_arch_standby();

    /**
     * Should not return here. cpu should "wake up" from standby in cpu_standby_wakeup with a
     * rewinded stack.
     */
    ERROR("Spurious standby wake up");
}

void cpu_powerdown(void)
{
    cpu_arch_powerdown();

    /**
     * Should not return here. cpu should "wake up" from powerdown in cpu_powerdown_wakeup with a
     * rewinded stack.
     */
    ERROR("Spurious powerdown wake up");
}

void cpu_standby_wakeup(void)
{
    if (interrupts_ipi_check()) {
        interrupts_ipi_clear();
        cpu_msg_handler();
    }

    if (cpu()->vcpu != NULL) {
        vcpu_run(cpu()->vcpu);
    } else {
        cpu_standby();
    }
}

void cpu_powerdown_wakeup(void)
{
    if (interrupts_ipi_check()) {
        interrupts_ipi_clear();
        cpu_msg_handler();
    }

    if (cpu()->vcpu != NULL) {
        vcpu_run(cpu()->vcpu);
    } else {
        cpu_powerdown();
    }
}
