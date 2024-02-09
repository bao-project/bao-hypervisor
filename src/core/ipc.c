/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
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

static void ipc_notify(size_t shmem_id, size_t event_id)
{
    struct ipc* ipc_obj = ipc_find_by_shmemid(cpu()->vcpu->vm, shmem_id);
    if (ipc_obj != NULL && event_id < ipc_obj->interrupt_num) {
        irqid_t irq_id = ipc_obj->interrupts[event_id];
        vcpu_inject_hw_irq(cpu()->vcpu, irq_id);
    }
}

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

long int ipc_hypercall(unsigned long ipc_id, unsigned long ipc_event, unsigned long arg2)
{
    UNUSED_ARG(arg2);

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
