/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <ipc.h>

#include <cpu.h>
#include <vmm.h>
#include <hypercall.h>

enum {IPC_NOTIFY};

typedef union {
    struct {
        uint8_t shmem_id;
        uint8_t event_id;
    };
    uint64_t raw;
} ipc_msg_data_t;

static size_t shmem_table_size;
static shmem_t *shmem_table;

shmem_t* ipc_get_shmem(uint64_t shmem_id) {
    if(shmem_id < shmem_table_size) {
        return &shmem_table[shmem_id];
    } else {
        return NULL;
    }
}

static ipc_t* ipc_find_by_shmemid(vm_t* vm, uint64_t shmem_id) {

    ipc_t* ipc_obj = NULL;

    for(int i = 0; i < vm->ipc_num; i++) {
        if(vm->ipcs[i].shmem_id == shmem_id) {
            ipc_obj = &vm->ipcs[i];
            break;
        }
    }

    return ipc_obj;
}

static void ipc_notify(uint64_t shmem_id, uint64_t event_id) {
    ipc_t* ipc_obj = ipc_find_by_shmemid(cpu.vcpu->vm, shmem_id);
    if(ipc_obj != NULL && event_id < ipc_obj->interrupt_num) {
        int irq_id = ipc_obj->interrupts[event_id];
        interrupts_vm_inject(cpu.vcpu->vm, irq_id);
    }
}

static void ipc_handler(uint32_t event, uint64_t data){
    ipc_msg_data_t ipc_data = { .raw = data };
    switch(event){
        case IPC_NOTIFY: 
            ipc_notify(ipc_data.shmem_id, ipc_data.event_id);
        break;
    }
}
CPU_MSG_HANDLER(ipc_handler, IPC_CPUSMG_ID);

int64_t ipc_hypercall(uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
    uint64_t ipc_id = arg0;
    uint64_t ipc_event = arg1;
    int64_t ret = -HC_E_SUCCESS;

    shmem_t *shmem = NULL; 
    bool valid_ipc_obj = ipc_id < cpu.vcpu->vm->ipc_num;
    if(valid_ipc_obj) {
        shmem = ipc_get_shmem(cpu.vcpu->vm->ipcs[ipc_id].shmem_id);
    }
    bool valid_shmem = shmem != NULL;

    if(valid_ipc_obj && valid_shmem) {

        uint64_t ipc_cpu_masters = shmem->cpu_masters & ~cpu.vcpu->vm->cpus;

        ipc_msg_data_t data = {
            .shmem_id = cpu.vcpu->vm->ipcs[ipc_id].shmem_id,
            .event_id = ipc_event,
        };
        cpu_msg_t msg = {IPC_CPUSMG_ID, IPC_NOTIFY, data.raw};

        for (int i = 0; i < platform.cpu_num; i++) {
            if (ipc_cpu_masters & (1ULL << i)) {
                cpu_send_msg(i, &msg);
            }
        }

    } else {
        ret = -HC_E_INVAL_ARGS;
    }

    return ret;
}

static void ipc_alloc_shmem() {
    for (int i = 0; i < shmem_table_size; i++) {
        shmem_t *shmem = &shmem_table[i];
        if(!shmem->place_phys) {
            size_t n_pg = NUM_PAGES(shmem->size);
            ppages_t ppages = mem_alloc_ppages(shmem->colors, n_pg, false);
            if(ppages.size < n_pg) {
                ERROR("failed to allocate shared memory");
            }
            shmem->phys = ppages.base;
        }
    }
}

static void ipc_setup_masters(const vm_config_t* vm_config, bool vm_master) {
    
    static spinlock_t lock = SPINLOCK_INITVAL;

    for(int i = 0; i < vm_config_ptr->shmemlist_size; i++) {
        vm_config_ptr->shmemlist[i].cpu_masters = 0;
    }

    cpu_sync_barrier(&cpu_glb_sync);

    if(vm_master) {
        for(int i = 0; i < vm_config->platform.ipc_num; i++) {
            spin_lock(&lock);
            shmem_t *shmem = ipc_get_shmem(vm_config->platform.ipcs[i].shmem_id);
            if(shmem != NULL) {
                shmem->cpu_masters |= (1ULL << cpu.id);
            }
            spin_unlock(&lock);
        }
    }
}

void ipc_init(const vm_config_t* vm_config, bool vm_master) {

    shmem_table_size = vm_config_ptr->shmemlist_size;
    shmem_table = vm_config_ptr->shmemlist;
    
    if(cpu.id == CPU_MASTER) {
        ipc_alloc_shmem();
    }

    ipc_setup_masters(vm_config, vm_master);

}
