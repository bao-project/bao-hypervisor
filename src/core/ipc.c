/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file ipc.c
 * @brief This source file contains the implementation for inter-processor communication (IPC) 
 */

#include <ipc.h>

#include <cpu.h>
#include <vmm.h>
#include <hypercall.h>
#include <config.h>
#include <shmem.h>

enum { IPC_NOTIFY };

union ipc_msg_data {
    struct {
        uint32_t shmem_id;
        uint32_t event_id;
    };
    uint64_t raw;
};

/**
 * @brief Find an IPC object in a VM by its shared memory ID
 *
 * @param vm Pointer to the VM structure to search
 * @param shmem_id ID of the shared memory region to be found.
 * @return struct ipc* Pointer to the found IPC object, or NULL if not found.
 * @see vm, ipc
 * 
 */
static struct ipc* ipc_find_by_shmemid(struct vm* vm, size_t shmem_id)
{
    struct ipc* ipc_obj = NULL;

    for (size_t i = 0; i < vm->ipc_num; i++) {
        if (vm->ipcs[i].shmem_id == shmem_id) {
            ipc_obj = &vm->ipcs[i];
            break;
        }
    }

    return ipc_obj;
}

/**
 * @brief Notify a VM of an IPC event by injecting an interrupt
 *
 * @param shmem_id ID of the shared memory region allocated to the IPC channel
 * @param event_id Event identifier to trigger
 * @see ipc_find_by_shmemid(), cpu(), vcpu_inject_irq(), irqid_t, ipc, vcpu, vm
 * 
 */
static void ipc_notify(size_t shmem_id, size_t event_id)
{
    struct ipc* ipc_obj = ipc_find_by_shmemid(cpu()->vcpu->vm, shmem_id);
    if (ipc_obj != NULL && event_id < ipc_obj->interrupt_num) {
        irqid_t irq_id = ipc_obj->interrupts[event_id];
        vcpu_inject_irq(cpu()->vcpu, irq_id);
    }
}

/**
 * @brief Handle IPC events received via CPU messages
 * @param event Event type (e.g., IPC_NOTIFY)
 * @param data Message data containing shmem_id and event_id
 * @see ipc_notify(), WARNING(), ipc_msg_data, IPC_NOTIFY
 * 
 */
static void ipc_handler(uint32_t event, uint64_t data)
{
    union ipc_msg_data ipc_data = { .raw = data };
    switch (event) {
        case IPC_NOTIFY:
            ipc_notify(ipc_data.shmem_id, ipc_data.event_id);
            break;
        default:
            WARNING("Unknown IPC IPI event");
            break;
    }
}
CPU_MSG_HANDLER(ipc_handler, IPC_CPUMSG_ID)

/**
 * @brief Handle IPC-related hypercalls from VMs
 *
 * Processes IPC hypercalls by sending IPC messages to target CPUs running
 * VMs that share memory regions. Validates the IPC and shared memory IDs
 * before sending notifications.
 *
 * @return long int HC_E_SUCCESS on successful execution.
 * @return long int HC_E_INVAL_ARGS if the arguments are invalid.
 * @see hypercall_get_arg(), shmem_get(), cpu_send_msg(), cpu(), platform 
 * @see vcpu, shmem, ipc_msg_data, IPC_NOTIFY, IPC_CPUMSG_ID, vm, cpumap_t
 * 
 */
long int ipc_hypercall(void)
{
    unsigned long ipc_id = hypercall_get_arg(cpu()->vcpu, 0);
    unsigned long ipc_event = hypercall_get_arg(cpu()->vcpu, 1);

    long int ret = -HC_E_SUCCESS;

    struct shmem* shmem = NULL;
    bool valid_ipc_obj = ipc_id < cpu()->vcpu->vm->ipc_num;
    if (valid_ipc_obj) {
        shmem = shmem_get(cpu()->vcpu->vm->ipcs[ipc_id].shmem_id);
    }
    bool valid_shmem = shmem != NULL;

    if (valid_ipc_obj && valid_shmem) {
        cpumap_t ipc_cpu_masters = shmem->cpu_masters & ~cpu()->vcpu->vm->cpus;

        union ipc_msg_data data = {
            .shmem_id = (uint32_t)cpu()->vcpu->vm->ipcs[ipc_id].shmem_id,
            .event_id = (uint32_t)ipc_event,
        };
        struct cpu_msg msg = { (uint32_t)IPC_CPUMSG_ID, IPC_NOTIFY, data.raw };

        for (size_t i = 0; i < platform.cpu_num; i++) {
            if (ipc_cpu_masters & (1ULL << i)) {
                cpu_send_msg(i, &msg);
            }
        }

    } else {
        ret = -HC_E_INVAL_ARGS;
    }

    return ret;
}
