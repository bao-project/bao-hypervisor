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

#include <vmm.h>
#include <vm.h>
#include <config.h>
#include <cpu.h>
#include <spinlock.h>
#include <fences.h>
#include <string.h>
#include <ipc.h>

struct config* vm_config_ptr;
volatile static struct vm_assignment {
    spinlock_t lock;
    bool master;
    size_t ncpus;
    cpumap_t cpus;
    struct vm *vm;
    struct vm_install_info vm_install_info;
    bool install_info_ready;
    // pte_t vm_shared_table;
} *vm_assign;

static bool vmm_assign_vcpu(bool *master, vmid_t *vm_id) {
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
            } else if (vm_assign[i].ncpus <
                       config.vmlist[i].platform.cpu_num) {
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
            if (vm_assign[i].ncpus <
                config.vmlist[i].platform.cpu_num) {
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

static struct vm* vmm_alloc_vm(vmid_t vm_id, bool master) {
    vm_assign[vm_id].vm = NULL;
    if (master) {
        vm_assign[vm_id].vm = (struct vm*)
            mem_alloc_page(NUM_PAGES(sizeof(struct vm)), SEC_HYP_VM, false);
        memset(vm_assign[vm_id].vm, 0, sizeof(struct vm));
        vm_assign[vm_id].vm_install_info = 
            vmm_get_vm_install_info(vm_assign[vm_id].vm);
        fence_ord_write();
        vm_assign[vm_id].install_info_ready = true;
    } else {
        while (!vm_assign[vm_id].install_info_ready);
        vmm_vm_install(vm_assign[vm_id].vm, 
            (struct vm_install_info*)&vm_assign[vm_id].vm_install_info);
        fence_sync_write();
    }
    return vm_assign[vm_id].vm;
}

static size_t vmass_npages = 0;

static void vmm_alloc_assign_array() {
    if (cpu()->id == CPU_MASTER) {
        vmass_npages =
            ALIGN(sizeof(struct vm_assignment) * config.vmlist_size,
                  PAGE_SIZE) /
            PAGE_SIZE;
        vm_assign = mem_alloc_page(vmass_npages, SEC_HYP_GLOBAL, false);
        if (vm_assign == NULL) ERROR("cant allocate vm assignemnt pages");
        memset((void*)vm_assign, 0, vmass_npages * PAGE_SIZE);
    }
}

static void vmm_free_assign_array() {
    if (cpu()->id == CPU_MASTER) {
        mem_free_vpage(&cpu()->as, (vaddr_t)vm_assign, vmass_npages, true);
    }
}

void vmm_init()
{       
    vmm_arch_init();
    vmm_io_init();

    vmm_alloc_assign_array();
    cpu_sync_barrier(&cpu_glb_sync);

    bool master = false;
    vmid_t vm_id = -1;
    struct vm_config *vm_config = NULL;
    struct vm* vm = NULL;
    
    bool vm_assigned = vmm_assign_vcpu(&master, &vm_id);
    if (vm_assigned) {
        vm_config = &config.vmlist[vm_id];
        vm = vmm_alloc_vm(vm_id, master);
    }

    cpu_sync_barrier(&cpu_glb_sync);
    vmm_free_assign_array();

    ipc_init(vm_config, master);

    if (vm_assigned) {
        vm_init(vm, vm_config, master, vm_id);
        vcpu_run(cpu()->vcpu);
    } else {
        cpu_idle();
    }
}
