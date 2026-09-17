/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vmm.h>
#include <vm.h>
#include <config.h>
#include <cpu.h>
#include <spinlock.h>
#include <fences.h>
#include <string.h>
#include <shmem.h>

/* The vm structures are statically allocated, one per vm in the configuration */
static struct vm vms[CONFIG_VM_NUM];

static struct vm_assignment {
    spinlock_t lock;
    struct cpu_synctoken root_sync;
    bool master;
    size_t ncpus;
    cpumap_t cpus;
} vm_assign[CONFIG_VM_NUM];

static bool vmm_assign_vcpu(bool* master, vmid_t* vm_id)
{
    bool assigned = false;
    *master = false;
    /* Assign cpus according to vm affinity. */
    for (size_t i = 0; i < config.vmlist_size && !assigned; i++) {
        if (config.vmlist[i].cpu_affinity & (1UL << cpu()->id)) {
            spin_lock(&vm_assign[i].lock);
            if (!vm_assign[i].master) {
                vm_assign[i].master = true;
                vm_assign[i].ncpus++;
                vm_assign[i].cpus |= (1UL << cpu()->id);
                *master = true;
                assigned = true;
                *vm_id = i;
            } else if (vm_assign[i].ncpus < config.vmlist[i].platform.cpu_num) {
                assigned = true;
                vm_assign[i].ncpus++;
                vm_assign[i].cpus |= (1UL << cpu()->id);
                *vm_id = i;
            }
            spin_unlock(&vm_assign[i].lock);
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    /* Assign remaining cpus not assigned by affinity. */
    if (assigned == false) {
        for (size_t i = 0; i < config.vmlist_size && !assigned; i++) {
            spin_lock(&vm_assign[i].lock);
            if (vm_assign[i].ncpus < config.vmlist[i].platform.cpu_num) {
                if (!vm_assign[i].master) {
                    vm_assign[i].master = true;
                    vm_assign[i].ncpus++;
                    *master = true;
                    assigned = true;
                    vm_assign[i].cpus |= (1UL << cpu()->id);
                    *vm_id = i;
                } else {
                    assigned = true;
                    vm_assign[i].ncpus++;
                    vm_assign[i].cpus |= (1UL << cpu()->id);
                    *vm_id = i;
                }
            }
            spin_unlock(&vm_assign[i].lock);
        }
    }

    return assigned;
}

void vmm_init()
{
    vmm_arch_init();
    vmm_io_init();
    shmem_init();
    remio_init();

    if (cpu_is_master()) {
        for (size_t i = 0; i < CONFIG_VM_NUM; i++) {
            vm_assign[i].lock = SPINLOCK_INITVAL;
            cpu_sync_init(&vm_assign[i].root_sync, config.vmlist[i].platform.cpu_num);
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    bool master = false;
    vmid_t vm_id = INVALID_VMID;
    if (vmm_assign_vcpu(&master, &vm_id)) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        struct vm* vm = vm_init(&vms[vm_id], &vm_assign[vm_id].root_sync, vm_config, master, vm_id);
        cpu_sync_barrier(&vm->sync);
        vcpu_run(&cpu()->vcpu);
    } else {
        cpu_powerdown();
    }
}
