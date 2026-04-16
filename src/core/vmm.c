/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * @file vmm.c
 * @brief This source file contains the core implementation for VM management.
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

/**
 * @brief Assign the current CPU to a VM as a vCPU
 * @param[out] master Set to true if this CPU becomes a VM's master
 * @param[out] vm_id ID of the VM this CPU is assigned to
 * @return bool true if CPU was assigned to a VM, false otherwise
 * @see config, vmid_t, vm_assignment, cpu(), cpumap_t, vm_allocation, vm_install_info
 *      cpu_sync_barrier(), spin_lock(), spin_unlock().
 */
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

/**
 * @brief Allocate memory for VM and VCPU structures
 * Allocates a contiguous block of memory for the VM structure and its VCPUs,
 * ensuring proper alignment of all fields. The allocation is page-aligned
 * and mapped in the hypervisor's address space.
 * @param[out] vm_alloc Output structure to receive allocation details
 * @param[in] vm_config Configuration describing the VM requirements
 * @return bool true if allocation successful, false otherwise
 * @see mem_alloc_page(), memset(), ALIGN(), PAGE_SIZE, NUM_PAGES(), vcpu, vm
 *      vaddr_t, SEC_HYP_VM, MEM_ALIGN_NOT_REQ, vm_allocation, vm_platform, vm_config
 */
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

    void* allocation = mem_alloc_page(NUM_PAGES(total_size), SEC_HYP_VM, MEM_ALIGN_NOT_REQ);
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

/**
 * @brief Allocate and install VM structures
 * The master CPU allocates VM structures and shares installation info
 * with other CPUs. Non-master CPUs wait for the master to prepare the
 * installation info before proceeding with their own installation.
 * @param vm_id ID of the VM to allocate/install
 * @param master true if this CPU is the VM's master
 * @return struct vm_allocation* Pointer to the VM allocation structure
 * @see vmm_alloc_vm(), vmm_get_vm_install_info(), vmm_vm_install(), config
 *      vm_assignment, fence_ord_read(), fence_ord_write(), ERROR(), vm_allocation
 *      vm_config, config, vm_install_info
 */
static struct vm_allocation* vmm_alloc_install_vm(vmid_t vm_id, bool master)
{
    struct vm_allocation* vm_alloc = &vm_assign[vm_id].vm_alloc;
    struct vm_config* vm_config = &config.vmlist[vm_id];
    if (master) {
        if (!vmm_alloc_vm(vm_alloc, vm_config)) {
            ERROR("Failed to allocate vm internal structures\n");
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

/**
 * @brief Initialize the hypervisor's VM management.
 * @note    This is the last step of the hypervisor initialization.
 *          Once all the CPU have executed this function, they are already
 *          executing within the VM's execution environment.
 * @see vmm_arch_init(), vmm_io_init(), shmem_init(), remio_init(), vmm_assign_vcpu()
 *      vmm_alloc_install_vm(), vm_init(), vcpu_run(), cpu_powerdown(), cpu_sync_barrier()
 *      vm_assignment, spinlock_t, vm_config, config, vm_platform, cpu_synctoken
 *      vmid_t, cpu(), vcpu
 */
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
        struct vm_allocation* vm_alloc = vmm_alloc_install_vm(vm_id, master);
        struct vm_config* vm_config = &config.vmlist[vm_id];
        struct vm* vm = vm_init(vm_alloc, &vm_assign[vm_id].root_sync, vm_config, master, vm_id);
        cpu_sync_barrier(&vm->sync);
        vcpu_run(cpu()->vcpu);
    } else {
        cpu_powerdown();
    }
}
