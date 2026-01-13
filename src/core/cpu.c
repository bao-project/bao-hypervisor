/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file cpu.c
 * @brief This source file contains the implementation of the CPU management.
 * 
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

/**
 * @brief Initialize the calling CPU's state.
 *
 * This function configures the currently executing cpu data structure, initializes
 * architecture-specific CPU state, initializes the CPU interface event list
 * and, if running on the master CPU, initializes the global
 * synchronization token and sets up inter-processor message handler IDs.
 *
 * @param cpu_id Identifier of the CPU to be initialized.
 *
 * @return None.
 *
 * @see cpuid_t, cpu(), cpu_if(), cpu_arch_init(), list_init(), cpu_is_master(),
 * @see cpu_sync_init(), cpu_sync_barrier(), platform, _ipi_cpumsg_handlers_id_start, 
 * @see _ipi_cpumsg_handlers_id_end, ipi_cpumsg_handlers, size_t
 *
 */
void cpu_init(cpuid_t cpu_id)
{
    cpu()->id = cpu_id;
    cpu()->handling_msgs = false;
    cpu()->interface = cpu_if(cpu()->id);

    cpu_arch_init(cpu_id, img_addr);

    list_init(&cpu()->interface->event_list);

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

/**
 * @brief Sends a message from the current CPU to a target CPU.
 *
 * Allocates a message node from the message object pool, copies the
 * message into it and pushes it on the target CPU's event list, then
 * triggers an IPI to wake the target CPU.
 *
 * @param trgtcpu Target CPU identifier.
 * @param msg Pointer to the message to send. The message contents are copied.
 *
 * @return None.
 *
 * @see cpuid_t, cpu_msg, cpu_msg_node, node_t, objpool_alloc(), ERROR(), list_push(),
 * @see cpu_if(), fence_sync_write(), interrupts_cpu_sendipi()
 * 
 */
void cpu_send_msg(cpuid_t trgtcpu, struct cpu_msg* msg)
{
    struct cpu_msg_node* node = objpool_alloc(&msg_pool);
    if (node == NULL) {
        ERROR("cant allocate msg node");
    }
    node->msg = *msg;
    list_push(&cpu_if(trgtcpu)->event_list, (node_t*)node);
    fence_sync_write();
    interrupts_cpu_sendipi(trgtcpu);
}

/**
 * @brief Retrieve the next CPU message from the calling CPU event list.
 *
 * Pops a cpu_msg_node from the current CPU interface event list and copies
 * the contained message to the provided out-parameter. Frees the message
 * node back to the object pool.
 *
 * @param[out] msg Pointer to storage that will receive the popped message.
 * @return true if a message was retrieved and copied; false if the event list was empty.
 *
 * @see list_pop(), objpool_free(), cpu_msg, cpu_msg_node, cpu(), cpuif
 * 
 */
bool cpu_get_msg(struct cpu_msg* msg)
{
    struct cpu_msg_node* node = NULL;
    if ((node = (struct cpu_msg_node*)list_pop(&cpu()->interface->event_list)) != NULL) {
        *msg = node->msg;
        objpool_free(&msg_pool, node);
        return true;
    }
    return false;
}

/**
 * @brief Handle all pending CPU messages for the current CPU.
 *
 * This routine repeatedly fetches messages using cpu_get_msg() and invokes
 * the registered inter-processor message handler (ipi_cpumsg_handlers) for
 * each message. The cpu->handling_msgs flag is used to indicate message
 * processing is in progress.
 *
 * @return None.
 *
 * @see cpu(), cpu_get_msg(), ipi_cpumsg_handlers[], ipi_cpumsg_handler_num
 * @see cpu_msg_handler_t, cpu_msg
 * 
 */
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

/**
 * @brief Put the CPU into a low-power standby state.
 *
 * Calls the architecture-specific standby entry routine.
 * This function is expected not to return; if it does, 
 * a spurious wake-up is reported as an error.
 *
 * @return None.
 *
 * @see cpu_arch_standby(), ERROR()
 * 
 */
void cpu_standby(void)
{
    cpu_arch_standby();

    /**
     * Should not return here. cpu should "wake up" from standby in cpu_standby_wakeup with a
     * rewound stack.
     */
    ERROR("Spurious standby wake up");
}

/**
 * @brief Power down the CPU core.
 *
 * This function calls an architecture-specific power-down routine. The function is
 * not expected to return; if it does, the function logs a spurious wake-up.
 *
 * @return None.
 *
 * @see cpu_arch_powerdown(), ERROR()
 * 
 */
void cpu_powerdown(void)
{
    cpu_arch_powerdown();

    /**
     * Should not return here. cpu should "wake up" from powerdown in cpu_powerdown_wakeup with a
     * rewound stack.
     */
    ERROR("Spurious powerdown wake up");
}

/**
 * @brief Wakeup handler invoked when exiting standby mode.
 *
 * Checks for pending IPIs and handles CPU messages, then resumes the
 * currently assigned vCPU (if any) or re-enters standby state.
 * It is intended to be called with a rewound stack by architecture-specific wakeup code.
 *
 * @return None.
 *
 * @see interrupts_ipi_check(), interrupts_ipi_clear(), cpu_msg_handler(), vcpu_run(),
 * @see cpu_standby(), cpu(), vcpu, cpu
 * 
 */
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

/**
 * @brief Wakeup handler invoked after powerdown exit.
 *
 * Checks for IPIs and handles messages, then resumes 
 * the vCPU if present or re-enters powerdown otherwise.
 *
 * @return None.
 *
 * @see interrupts_ipi_check(), interrupts_ipi_clear(), cpu_msg_handler(), vcpu_run()
 * @see cpu_powerdown(), cpu(), cpu, vcpu
 * 
 */
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
