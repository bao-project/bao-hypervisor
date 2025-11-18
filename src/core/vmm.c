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

static struct vm_assignment {
    spinlock_t lock;
    struct cpu_synctoken root_sync;
    bool master;
    size_t ncpus;
    cpumap_t cpus;
    struct vm_allocation vm_alloc;
    struct vm_install_info vm_install_info;
    volatile bool install_info_ready;
} vm_assign[CONFIG_VM_NUM];


static size_t max_vcpu_per_cpu(void) {

    size_t vcpu_num = 0;
    size_t exlusive_cpu_num = 0;

    for (size_t i = 0; i < config.vmlist_size; i++) {
        vcpu_num += config.vmlist[i].platform.cpu_num;
        if (config.vmlist[i].cpu_exclusivity) {
            exlusive_cpu_num += config.vmlist[i].platform.cpu_num;
        }
    }

    size_t shared_cpu_num = platform.cpu_num - exlusive_cpu_num;
    size_t non_exclusive_vcpu_num = vcpu_num - exlusive_cpu_num;
    size_t max_vcpu = (non_exclusive_vcpu_num / shared_cpu_num) +
        ((non_exclusive_vcpu_num % shared_cpu_num) > 0 ? 1 : 0);

    return max_vcpu;
}

static bool vmm_assign_vcpus(void)
{
    size_t max_vcpus = max_vcpu_per_cpu();
    cpumap_t exclusive_cpus = 0;
    size_t cpu_vcpu_count[PLAT_CPU_NUM] = { 0 };

    static const struct {
        bool find_exclusive;
        bool assign_affinity;
    } cpu_search_params[4] = {
        { true, true },
        { true, false },
        { false, true },
        { false, false },
    };

    for (size_t k = 0; k < 4; k++) {

        for (size_t i = 0; i < config.vmlist_size; i++) {

            struct vm_config *vm_config = &config.vmlist[i];
            struct vm_assignment *vm_assignment = &vm_assign[i];
            size_t vm_cpu_num = vm_config->platform.cpu_num;

            if (cpu_search_params[k].find_exclusive && !vm_config->cpu_exclusivity) {
                continue;
            }

            // For each physical cpu try to assign it one of this VM's vcpu
            for (size_t j = 0; (j < PLAT_CPU_NUM) && (vm_assignment->ncpus < vm_cpu_num); j++) {

                // If this cpu was already assigned a vCPU in the same VM, skip it
                if (bit_get(vm_assignment->cpus, j)) {
                    continue;
                }

                // If we are looking for exlucsive cpus and this was already assigned, skip it
                if (cpu_search_params[k].find_exclusive && (cpu_vcpu_count[j] > 0)) {
                    continue;
                }

                // If this cpu was already exclusively assigned, skip it
                if (bit_get(exclusive_cpus, j)) {
                    continue;
                }

                // If this cpu has no affinity to the VM and was already assigned the maximum 
                // number of vcpus allowed, skip it
                if (!cpu_search_params[k].assign_affinity && cpu_vcpu_count[j] >= max_vcpus) {
                    continue;
                }

                if (!cpu_search_params[k].assign_affinity || bit_get(vm_config->cpu_affinity, j)) {
                    vm_assignment->cpus |= 1UL << j;
                    vm_assignment->ncpus += 1;
                    cpu_vcpu_count[j] += 1;
                    if (cpu_search_params[k].find_exclusive) {
                        exclusive_cpus |= 1UL << j;
                    }
                }
            }
        }
    }

    return true;
}

static bool vmm_alloc_vm(struct vm_allocation* vm_alloc, struct vm_config* vm_config)
{
    /**
     * We know that we will allocate a block aligned to the PAGE_SIZE, which is guaranteed to
     * fulfill the alignment of all types. However, to guarantee the alignment of all fields, when
     * we calculate the size of a field in the vm_allocation struct, we must align the previous
     * total size calculated until that point, to the alignment of the type of the next field.
     */

    size_t total_size = sizeof(struct vm);
    size_t vcpus_offset = ALIGN(total_size, _Alignof(struct vcpu));
    total_size = vcpus_offset + (vm_config->platform.cpu_num * sizeof(struct vcpu));
    total_size = ALIGN(total_size, PAGE_SIZE);

    void* allocation = mem_alloc_page(NUM_PAGES(total_size), SEC_HYP_GLOBAL, MEM_ALIGN_NOT_REQ);
    if (allocation == NULL) {
        return false;
    }
    memset((void*)allocation, 0, total_size);

    vm_alloc->base = (vaddr_t)allocation;
    vm_alloc->size = total_size;
    vm_alloc->vm = (struct vm*)vm_alloc->base;
    vm_alloc->vcpus = (struct vcpu*)(vm_alloc->base + vcpus_offset);

    return true;
}

static struct vm_allocation* vmm_alloc_install_vm(vmid_t vm_id, bool master)
{
    struct vm_allocation* vm_alloc = &vm_assign[vm_id].vm_alloc;
    struct vm_config* vm_config = &config.vmlist[vm_id];
    if (master) {
        if (!vmm_alloc_vm(vm_alloc, vm_config)) {
            ERROR("Failed to allocate vm internal structures");
        }
        vm_assign[vm_id].vm_install_info = vmm_get_vm_install_info(vm_alloc);
        fence_ord_write();
        vm_assign[vm_id].install_info_ready = true;
    } else {
        while (!vm_assign[vm_id].install_info_ready) { }
        fence_ord_read();
        vmm_vm_install(&vm_assign[vm_id].vm_install_info);
    }

    return vm_alloc;
}

static bool vmm_get_next_assigned_vm(bool *master, vmid_t *vm_id) {

    bool assigned = false;
    *master = false;

    for (size_t i = 0; i < config.vmlist_size; i++) {
        if (vm_assign[i].cpus & (1UL << cpu()->id)) {

            spin_lock(&vm_assign[i].lock);
            vm_assign[i].cpus &= ~(1UL << cpu()->id);
            if (!vm_assign[i].master) {
                vm_assign[i].master = true;
                *master = true;
            }
            spin_unlock(&vm_assign[i].lock);
    
            *vm_id = i;
            assigned = true;
            break;
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
        vmm_assign_vcpus();
    }

    cpu_sync_barrier(&cpu_glb_sync);

    bool master = false;
    vmid_t vm_id = INVALID_VMID;
    while (vmm_get_next_assigned_vm(&master, &vm_id)) {
        struct vm_allocation* vm_alloc = vmm_alloc_install_vm(vm_id, master);
        struct vm_config* vm_config = &config.vmlist[vm_id];
        vm_init(vm_alloc, &vm_assign[vm_id].root_sync, vm_config, master, vm_id);
    }
}
