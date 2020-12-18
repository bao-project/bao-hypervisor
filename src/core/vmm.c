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
#include <iommu.h>
#include <spinlock.h>
#include <fences.h>
#include <string.h>
#include <ipc.h>

struct config* vm_config_ptr;

void vmm_init()
{
    if(vm_config_ptr->vmlist_size == 0){
        if(cpu.id == CPU_MASTER)
            INFO("No virtual machines to run.");
        cpu_idle();
    } 
    
    vmm_arch_init();

    volatile static struct vm_assignment {
        spinlock_t lock;
        bool master;
        size_t ncpus;
        uint64_t cpus;
        pte_t vm_shared_table;
    } * vm_assign;

    size_t vmass_npages = 0;
    if (cpu.id == CPU_MASTER) {
        iommu_init();

        vmass_npages =
            ALIGN(sizeof(struct vm_assignment) * vm_config_ptr->vmlist_size,
                  PAGE_SIZE) /
            PAGE_SIZE;
        vm_assign = mem_alloc_page(vmass_npages, SEC_HYP_GLOBAL, false);
        if (vm_assign == NULL) ERROR("cant allocate vm assignemnt pages");
        memset((void*)vm_assign, 0, vmass_npages * PAGE_SIZE);
    }

    cpu_sync_barrier(&cpu_glb_sync);

    bool master = false;
    bool assigned = false;
    size_t vm_id = 0;
    vm_config_t *vm_config = NULL;

    /**
     * Assign cpus according to vm affinity.
     */
    for (int i = 0; i < vm_config_ptr->vmlist_size && !assigned; i++) {
        if (vm_config_ptr->vmlist[i].cpu_affinity & (1UL << cpu.id)) {
            spin_lock(&vm_assign[i].lock);
            if (!vm_assign[i].master) {
                vm_assign[i].master = true;
                vm_assign[i].ncpus++;
                vm_assign[i].cpus |= (1UL << cpu.id);
                master = true;
                assigned = true;
                vm_id = i;
            } else if (vm_assign[i].ncpus <
                       vm_config_ptr->vmlist[i].platform.cpu_num) {
                assigned = true;
                vm_assign[i].ncpus++;
                vm_assign[i].cpus |= (1UL << cpu.id);
                vm_id = i;
            }
            spin_unlock(&vm_assign[i].lock);
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    /**
     * Assign remaining cpus not assigned by affinity.
     */
    if (assigned == false) {
        for (int i = 0; i < vm_config_ptr->vmlist_size && !assigned; i++) {
            spin_lock(&vm_assign[i].lock);
            if (vm_assign[i].ncpus <
                vm_config_ptr->vmlist[i].platform.cpu_num) {
                if (!vm_assign[i].master) {
                    vm_assign[i].master = true;
                    vm_assign[i].ncpus++;
                    master = true;
                    assigned = true;
                    vm_assign[i].cpus |= (1UL << cpu.id);
                    vm_id = i;
                } else {
                    assigned = true;
                    vm_assign[i].ncpus++;
                    vm_assign[i].cpus |= (1UL << cpu.id);
                    vm_id = i;
                }
            }
            spin_unlock(&vm_assign[i].lock);
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    if (assigned) {
        vm_config = &vm_config_ptr->vmlist[vm_id];
        if (master) {
            size_t vm_npages = NUM_PAGES(sizeof(vm_t));
            void* va = mem_alloc_vpage(&cpu.as, SEC_HYP_VM, (void*)BAO_VM_BASE,
                                       vm_npages);
            mem_map(&cpu.as, va, NULL, vm_npages, PTE_HYP_FLAGS);
            memset(va, 0, vm_npages * PAGE_SIZE);
            fence_ord_write();
            vm_assign[vm_id].vm_shared_table =
                *pt_get_pte(&cpu.as.pt, 0, (void*)BAO_VM_BASE);
        } else {
            while (vm_assign[vm_id].vm_shared_table == 0);
            pte_t* pte = pt_get_pte(&cpu.as.pt, 0, (void*)BAO_VM_BASE);
            *pte = vm_assign[vm_id].vm_shared_table;
            fence_sync_write();
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    if (cpu.id == CPU_MASTER) {
        mem_free_vpage(&cpu.as, (void*)vm_assign, vmass_npages, true);
    }

    ipc_init(vm_config, master);

    if (assigned) {
        vm_init((void*)BAO_VM_BASE, vm_config, master, vm_id);
        vcpu_run(cpu.vcpu);
    } else {
        cpu_idle();
    }
}
