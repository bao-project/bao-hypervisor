/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * @file vm.c
 * @brief This source file implements the hypervisor's Virtual Machine creation API.
 */

#include <vm.h>
#include <string.h>
#include <mem.h>
#include <cache.h>
#include <config.h>
#include <shmem.h>
#include <objpool.h>
#include <list.h>

/**
 * @brief Assign the executing CPU as the VM's master CPU and synchronize the rest of the VM's CPUs.
 * To be noted, this is not a master/slave model.
 * The master CPU is a selected CPU that perform exclusive actions during the VM's initialization
 * that shall not be performed concurrently.
 * @param vm Pointer to VM structure to initialize
 * @param vm_config Configuration describing the VM
 * @param vm_id Unique identifier for the VM
 * @see cpu(), cpu, SPINLOCK_INITVAL, cpu_sync_init(), vm_mem_prot_init()
 */
static void vm_master_init(struct vm* vm, const struct vm_config* vm_config, vmid_t vm_id)
{
    vm->master = cpu()->id;
    vm->config = vm_config;
    vm->cpu_num = vm_config->platform.cpu_num;
    vm->id = vm_id;
    vm->lock = SPINLOCK_INITVAL;

    list_init(&vm->emul_mem_list);
    list_init(&vm->emul_reg_list);
    cpu_sync_init(&vm->sync, vm->cpu_num);
}

/**
 * @brief Register current CPU as part of a VM
 * @param vm Pointer to the VM to update
 * @see spin_lock(), spin_unlock(), cpu(), cpu.
 */
static void vm_cpu_init(struct vm* vm)
{
    spin_lock(&vm->lock);
    vm->cpus |= (1UL << cpu()->id);
    spin_unlock(&vm->lock);
}

/**
 * @brief Calculate the Virtual CPU ID of the executing CPU.
 * @param vm Pointer to the VM whose CPU bitmap is used for the calculation
 * @return vcpuid_t The virtual CPU ID of the executing CPU within this VM
 * @see bit_get(), cpu(), cpu, vcpuid_t
 */
static vcpuid_t vm_calc_vcpu_id(struct vm* vm)
{
    vcpuid_t vcpu_id = 0;
    for (size_t i = 0; i < cpu()->id; i++) {
        if (!!bit_get(vm->cpus, i)) {
            vcpu_id++;
        }
    }
    return vcpu_id;
}

/**
 * @brief Configure the virtualized CPU configuration for the executing physical CPU.
 * Sets up the VCPU structure, links it to the VM and physical CPU,
 * and performs architecture-specific initialization and reset.
 * @param vm Pointer to the VM owning this VCPU
 * @param vm_config Configuration describing the VM and entry point
 * @see vm_calc_vcpu_id(), vm_get_vcpu(), vcpu_arch_init(), vcpu_arch_reset(),
 *      cpu(), cpu.
 */
static void vm_vcpu_init(struct vm* vm, const struct vm_config* vm_config)
{
    vcpuid_t vcpu_id = vm_calc_vcpu_id(vm);
    struct vcpu* vcpu = vm_get_vcpu(vm, vcpu_id);

    vcpu->id = vcpu_id;
    vcpu->phys_id = cpu()->id;
    vcpu->vm = vm;
    vcpu->active = true;
    cpu()->vcpu = vcpu;

    vcpu_arch_init(vcpu, vm);
    vcpu_arch_reset(vcpu, vm_config->entry);
}

/**
 * @brief Map a memory region into a VM's address space
 * Maps a memory region described by vm_mem_region into the VM's address
 * space. For physically placed regions, uses the specified physical address;
 * otherwise allocates new physical pages.
 * @param vm Pointer to the VM to map memory into
 * @param reg Memory region descriptor
 * @see mem_ppages_get(), mem_alloc_map(), ERROR(), NUM_PAGES, vm, vm_mem_region,
 *      vaddr_t, SEC_VM_ANY, PTE_VM_FLAGS, ppages.
 */
static void vm_map_mem_region(struct vm* vm, struct vm_mem_region* reg)
{
    size_t n = NUM_PAGES(reg->size);

    struct ppages pa_reg;
    struct ppages* pa_ptr = NULL;
    if (reg->place_phys) {
        pa_reg = mem_ppages_get(reg->phys, n);
        pa_reg.colors = reg->colors;
        pa_ptr = &pa_reg;
    } else {
        pa_ptr = NULL;
    }

    vaddr_t va = mem_alloc_map(&vm->as, SEC_VM_ANY, pa_ptr, (vaddr_t)reg->base, n, PTE_VM_FLAGS);
    if (va != (vaddr_t)reg->base) {
        ERROR("failed to allocate vm's region at 0x%lx\n", reg->base);
    }
}

/**
 * @brief Map a VM's image region in-place
 * Maps a VM's image into its address space, handling the memory regions
 * before and after the image separately. Supports colored memory
 * configurations, by performing recoloring if needed.
 * @param vm Pointer to the VM data structure, for which the memory is mapped.
 * @param vm_config Configuration describing the VM and its image
 * @param reg Memory region descriptor for the image
 * @see mem_alloc_map(), mem_map_reclr(), mem_ppages_get(), NUM_PAGES, PAGE_SIZE,
 *      all_clrs(), vm, vm_config, vm_mem_region, vaddr_t, ppages, SEC_VM_ANY.
 */
static void vm_map_img_rgn_inplace(struct vm* vm, const struct vm_config* vm_config,
    struct vm_mem_region* reg)
{
    vaddr_t img_base = vm_config->image.base_addr;
    size_t img_size = vm_config->image.size;
    /* mem region pages before the img */
    size_t n_before = NUM_PAGES(img_base - reg->base);
    /* pages after the img */
    size_t n_aft = NUM_PAGES((reg->base + reg->size) - (img_base + img_size));
    /* mem region pages for img */
    size_t n_img = NUM_PAGES(img_size);

    /* map img in place */
    struct ppages pa_img = mem_ppages_get(vm_config->image.load_addr, n_img);

    mem_alloc_map(&vm->as, SEC_VM_ANY, NULL, (vaddr_t)reg->base, n_before, PTE_VM_FLAGS);
    if (all_clrs(vm->as.colors)) {
        /* map img in place */
        mem_alloc_map(&vm->as, SEC_VM_ANY, &pa_img, img_base, n_img, PTE_VM_FLAGS);
        /* we are mapping in place, config is already reserved */
    } else {
        /* recolour img */
        mem_map_reclr(&vm->as, img_base, &pa_img, n_img, PTE_VM_FLAGS);
    }
    /* map pages after img */
    mem_alloc_map(&vm->as, SEC_VM_ANY, NULL, img_base + NUM_PAGES(img_size) * PAGE_SIZE, n_aft,
        PTE_VM_FLAGS);
}

/**
 * @brief Install a VM image into its configured memory region.
 * Copy the VM image from its load address to the runtime base address defined in the
 * VM configuration. If the image is already at its runtime address, return immediately.
 * @note If the load region and the runtime region overlap, trigger a fatal error.
 * @param vm Data structure of the VM to be installed.
 * @param reg Region in which the VM is to be installed
 * @see vm, vm_mem_region, paddr_t, range_overlap_range(), ERROR, NUM_PAGES
 *      cpu(), addr_space, mem_alloc_map(), vaddr_t, ppages, mem_map_cpy()
 *      memcpy(), cache_flush_range(), mem_unmap()
 */
static void vm_install_image(struct vm* vm, struct vm_mem_region* reg)
{
    if (reg->place_phys) {
        paddr_t img_base = (paddr_t)vm->config->image.base_addr;
        paddr_t img_load_pa = vm->config->image.load_addr;
        size_t img_sz = vm->config->image.size;

        if (img_base == img_load_pa) {
            // The image is already correctly installed. Our work is done.
            return;
        }

        if (range_overlap_range(img_base, img_sz, img_load_pa, img_sz)) {
            // We impose an image load region cannot overlap its runtime region. This both
            // simplifies the copying procedure as well as avoids limitations of mpu-based memory
            // management which does not allow overlapping mappings on the same address space.
            ERROR("failed installing vm image. Image load region overlaps with"
                  " image runtime region\n");
        }
    }

    size_t img_num_pages = NUM_PAGES(vm->config->image.size);
    struct ppages img_ppages = mem_ppages_get(vm->config->image.load_addr, img_num_pages);
    vaddr_t src_va = mem_alloc_map(&cpu()->as, SEC_HYP_PRIVATE, &img_ppages, INVALID_VA,
        img_num_pages, PTE_HYP_FLAGS);
    vaddr_t dst_va = mem_map_cpy(&vm->as, &cpu()->as, SEC_HYP_PRIVATE, vm->config->image.base_addr,
        INVALID_VA, img_num_pages);
    memcpy((void*)dst_va, (void*)src_va, vm->config->image.size);
    cache_flush_range((vaddr_t)dst_va, vm->config->image.size);
    mem_unmap(&cpu()->as, src_va, img_num_pages, MEM_DONT_FREE_PAGES);
    mem_unmap(&cpu()->as, dst_va, img_num_pages, MEM_DONT_FREE_PAGES);
}

/**
 * @brief Map (and install) a VM image in a specified memory region.
 * If in-place image is configured (i.e. not copied, at a specific physical address),
 * installation is not performed.
 * @param vm virtual machine to be installed
 * @param vm_config VM installation configuration
 * @param reg Memory region in which the VM is mapped and installed.
 * @see vm, vm_config, vm_mem_region, vm_map_img_rgn_inplace(), vm_map_mem_region(),
 *      vm_install_image()
 */
static void vm_map_img_rgn(struct vm* vm, const struct vm_config* vm_config,
    struct vm_mem_region* reg)
{
    if (!reg->place_phys && vm_config->image.inplace) {
        vm_map_img_rgn_inplace(vm, vm_config, reg);
    } else {
        vm_map_mem_region(vm, reg);
        vm_install_image(vm, reg);
    }
}

/**
 * @brief Initialize the memory regions defined in the VM configuration, within its mapped address space.
 * @param vm VM of which the memory regions are mapped.
 * @param vm_config VM configuration describing the platform's memory layout and image location.
 * @see range_in_range(), vm_map_img_rgn(), vm_map_mem_region(), vm_mem_region, 
 *      vm_config, vm
 */
static void vm_init_mem_regions(struct vm* vm, const struct vm_config* vm_config)
{
    for (size_t i = 0; i < vm_config->platform.region_num; i++) {
        struct vm_mem_region* reg = &vm_config->platform.regions[i];
        bool img_is_in_rgn =
            range_in_range(vm_config->image.base_addr, vm_config->image.size, reg->base, reg->size);
        if (img_is_in_rgn) {
            vm_map_img_rgn(vm, vm_config, reg);
        } else {
            vm_map_mem_region(vm, reg);
        }
    }
}

/**
 * @brief Initialize a VM's IPC resources
 * Map the VM's shared memory regions for inter-processor communication.
 * Its data structures are initialized and any configured physical interrupt is 
 * assigned.
 * @note    If the shared memory configuration is not correct (invalid ID),
 *          the IPC will not be mapped. A warning wil be issued but a runtime error
 *          may be encountered when configured or used by the VM.
 * @note    If the configured IPC shared memory's size is larger than the respective
 *          shared memory region, then the mapped IPC shared memory will be truncated
 *          to the size of the memory region. 
 * @param vm VM for which the IPCs are defined
 * @param vm_config The VM configuration.
 * @see vm, vm_config, ipc, shmem, WARNING(), shmem_get(), interrupts_vm_assign(),
 *      spin_lock(), spin_unlock(), cpu(), vm_mem_region, vm_map_mem_region
 */
static void vm_init_ipc(struct vm* vm, const struct vm_config* vm_config)
{
    vm->ipc_num = vm_config->platform.ipc_num;
    vm->ipcs = vm_config->platform.ipcs;
    for (size_t i = 0; i < vm_config->platform.ipc_num; i++) {
        struct ipc* ipc = &vm_config->platform.ipcs[i];
        struct shmem* shmem = shmem_get(ipc->shmem_id);
        if (shmem == NULL) {
            WARNING("Invalid shmem id in configuration. Ignored.\n");
            continue;
        }
        size_t size = ipc->size;
        if (ipc->size > shmem->size) {
            size = shmem->size;
            WARNING("Trying to map region to smaller shared memory. Truncated\n");
        }

        if (DEFINED(PHYS_IRQS_ONLY)) {
            for (size_t j = 0; j < ipc->interrupt_num; j++) {
                if (!interrupts_vm_assign(vm, ipc->interrupts[j])) {
                    ERROR("Failed to assign interrupt id %d\n", ipc->interrupts[j]);
                }
            }
        }

        spin_lock(&shmem->lock);
        shmem->cpu_masters |= (1UL << cpu()->id);
        spin_unlock(&shmem->lock);

        struct vm_mem_region reg = {
            .base = ipc->base,
            .size = size,
            .place_phys = true,
            .phys = shmem->phys,
            .colors = shmem->colors,
        };

        vm_map_mem_region(vm, &reg);
    }
}

/**
 * @brief Initialize device regions and interrupts for a VM.
 * @note    If MMIO slave-side protection is enabled, architecture-specific access
 *          control is applied instead of direct mapping.
 * @note    If IOMMU virtualization is available and a device carries a valid ID,
 *          register it with the IOMMU.
 * @param vm Pointer to the VM to configure.
 * @param vm_config VM configuration describing the platform devices.
 * @see vm_arch_allow_mmio_access(), mem_alloc_map_dev(), interrupts_vm_assign(),
 *      io_vm_init(), io_vm_add_device(), vm_dev_region, vm, vm_config,
 *      INVALID_VA, PAGE_SIZE, ALIGN, ERROR()
 */
static void vm_init_dev(struct vm* vm, const struct vm_config* vm_config)
{
    for (size_t i = 0; i < vm_config->platform.dev_num; i++) {
        struct vm_dev_region* dev = &vm_config->platform.devs[i];

        if (DEFINED(MMIO_SLAVE_SIDE_PROT)) {
            vm_arch_allow_mmio_access(vm, dev);
        } else if (dev->va != INVALID_VA) {
            size_t n = ALIGN(dev->size, PAGE_SIZE) / PAGE_SIZE;
            mem_alloc_map_dev(&vm->as, SEC_VM_ANY, (vaddr_t)dev->va, dev->pa, n);
        }

        for (size_t j = 0; j < dev->interrupt_num; j++) {
            if (!interrupts_vm_assign(vm, dev->interrupts[j])) {
                ERROR("Failed to assign interrupt id %d\n", dev->interrupts[j]);
            }
        }
    }

    if (io_vm_init(vm, vm_config)) {
        for (size_t i = 0; i < vm_config->platform.dev_num; i++) {
            struct vm_dev_region* dev = &vm_config->platform.devs[i];
            if (dev->id) {
                if (!io_vm_add_device(vm, dev->id)) {
                    ERROR("Failed to add device to iommu\n");
                }
            }
        }
    }
}

/**
 * @brief Initialize a single Remote I/O device for a VM's CPU.
 * @note    A warning is issued if the shared memory configured for the remote I/O
 *          device is not sufficient to fit the device memory region's size.
 * @note A fatal error is triggered if the shared memory ID is invalid.
 * @param vm Pointer to the VM to configure.
 * @param remio_dev Pointer to the remote I/O device descriptor.
 * @see shmem_get(), vm_map_mem_region(), vm_emul_add_mem(), remio_mmio_emul_handler(),
 *      spin_lock(), spin_unlock(), cpu(), shmem, remio_dev, vm_mem_region,
 *      WARNING(), ERROR(), REMIO_DEV_FRONTEND, emul_mem
 */
static void vm_init_remio_dev(struct vm* vm, struct remio_dev* remio_dev)
{
    struct shmem* shmem = shmem_get(remio_dev->shmem.shmem_id);
    if (shmem == NULL) {
        ERROR("Invalid shmem id (%d) in the Remote I/O device (%d) configuration\n",
            remio_dev->shmem.shmem_id, remio_dev->bind_key);
    }
    size_t shmem_size = remio_dev->shmem.size;
    if (shmem_size > shmem->size) {
        shmem_size = shmem->size;
        WARNING("Trying to map region to smaller shared memory. Truncated\n");
    }
    spin_lock(&shmem->lock);
    shmem->cpu_masters |= (1UL << cpu()->id);
    spin_unlock(&shmem->lock);

    struct vm_mem_region reg = {
        .base = remio_dev->shmem.base,
        .size = shmem_size,
        .place_phys = true,
        .phys = shmem->phys,
        .colors = shmem->colors,
    };

    vm_map_mem_region(vm, &reg);

    if (remio_dev->type == REMIO_DEV_FRONTEND) {
        struct emul_mem* emu = &remio_dev->emul;
        emu->va_base = remio_dev->va;
        emu->size = remio_dev->size;
        emu->handler = remio_mmio_emul_handler;
        vm_emul_add_mem(vm, emu);
    }
}

/**
 * @brief Initialize all Remote I/O devices configured for a VM.
 * @param vm Pointer to the VM to configure.
 * @param vm_config VM configuration describing the remote I/O devices.
 * @see vm_init_remio_dev(), remio_assign_vm_cpus(), remio_dev, vm_config, vm
 */
static void vm_init_remio(struct vm* vm, const struct vm_config* vm_config)
{
    if (vm_config->platform.remio_dev_num == 0) {
        return;
    }

    vm->remio_dev_num = vm_config->platform.remio_dev_num;
    vm->remio_devs = vm_config->platform.remio_devs;

    for (size_t i = 0; i < vm_config->platform.remio_dev_num; i++) {
        struct remio_dev* remio_dev = &vm_config->platform.remio_devs[i];
        vm_init_remio_dev(vm, remio_dev);
    }
    remio_assign_vm_cpus(vm);
}

/**
 * @brief Initialize a VM from a pre-allocated VM allocation structure.
 * @param vm_alloc Pointer to the allocation structure carrying the VM and VCPU memory.
 * @return struct vm* Pointer to the initialized VM structure.
 * @see vm_allocation, vm
 */
static struct vm* vm_allocation_init(struct vm_allocation* vm_alloc)
{
    struct vm* vm = vm_alloc->vm;
    vm->vcpus = vm_alloc->vcpus;
    return vm;
}

/**
 * @brief Initialize a Virtual Machine
 * Perform complete initialization of a VM including master initialization,
 * CPU registration, VCPU setup, architecture-specific initialization,
 * memory regions, IPC setup, and device setup.
 * @note    All CPUs' executions are synchronized at various stages to ensure
 *          VM state consistency during its initialization.
 * @param vm_alloc VM allocation structure with memory layout
 * @param vm_config Configuration describing the VM
 * @param master true if this CPU is the VM's master
 * @param vm_id Unique identifier for the VM
 * @return struct vm* Pointer to the initialized VM structure
 * @see vm_allocation_init(), vm_master_init(), vm_cpu_init(), vm_vcpu_init(),
 *      vm_arch_init(), vm_init_mem_regions(), vm_init_ipc(), vm_init_dev(),
 *      vm_init_remio(), cpu_sync_barrier(), cpu_sync_and_clear_msgs().
 */
struct vm* vm_init(struct vm_allocation* vm_alloc, struct cpu_synctoken* vm_init_sync,
    const struct vm_config* vm_config, bool master, vmid_t vm_id)
{
    struct vm* vm = vm_allocation_init(vm_alloc);

    /**
     * Before anything else, initialize vm structure.
     */
    if (master) {
        vm_master_init(vm, vm_config, vm_id);
    }

    cpu_sync_barrier(vm_init_sync);

    /*
     *  Initialize each core.
     */
    vm_cpu_init(vm);

    cpu_sync_barrier(&vm->sync);

    /*
     *  Initialize each virtual core.
     */
    vm_vcpu_init(vm, vm_config);

    cpu_sync_barrier(&vm->sync);

    if (master) {
        vm_mem_prot_init(vm, vm_config);
    }

    cpu_sync_barrier(&vm->sync);

    /**
     * Perform architecture dependent initializations. This includes, for example, setting the page
     * table pointer and other virtualization extensions specifics.
     */
    vm_arch_init(vm, vm_config);

    /**
     * Create the VM's address space according to configuration and where its image was loaded.
     */
    if (master) {
        vm_init_mem_regions(vm, vm_config);
        vm_init_dev(vm, vm_config);
        vm_init_ipc(vm, vm_config);
        vm_init_remio(vm, vm_config);
    }

    cpu_sync_and_clear_msgs(&vm->sync);

    return vm;
}

/**
 * @brief Register a memory-mapped emulation handler with a VM.
 * @param vm Pointer to the VM for which the emulator is registered.
 * @param emu Pointer to the emulated memory region descriptor to register.
 * @see list_push(), vm, emul_mem
 */
void vm_emul_add_mem(struct vm* vm, struct emul_mem* emu)
{
    list_push(&vm->emul_mem_list, &emu->node);
}

/**
 * @brief Register a register-level emulation handler with a VM.
 * @param vm Pointer to the VM for which the emulator is registered.
 * @param emu Pointer to the emulated register descriptor.
 * @see list_push(), vm, emul_reg
 */
void vm_emul_add_reg(struct vm* vm, struct emul_reg* emu)
{
    list_push(&vm->emul_reg_list, &emu->node);
}

/**
 * @brief Register a memory-mapped emulation handler with a VM.
 * @param vm Pointer to the VM that may own the memory access emulation handler.
 * @param emu Pointer to the emulated memory region descriptor to register.
 * @see list_push(), vm, emul_mem
 */
emul_handler_t vm_emul_get_mem(struct vm* vm, vaddr_t addr)
{
    emul_handler_t handler = NULL;
    list_foreach (vm->emul_mem_list, struct emul_mem, emu) {
        if (addr >= emu->va_base && (addr < (emu->va_base + emu->size))) {
            handler = emu->handler;
            break;
        }
    }

    return handler;
}

/**
 * @brief Look up the emulation handler for a given memory-mapped address.
 * @param vm Pointer to the VM that may own the register emulation handler.
 * @param addr Guest virtual address to look up.
 * @return emul_handler_t The handler for the matching region, or NULL if none found.
 * @see list_foreach(), vm, emul_mem, emul_handler_t, vaddr_t
 * @note    The handler is identified by an address. the address may not
 *          correspond to an actual address, but a register ID instead.
 */
emul_handler_t vm_emul_get_reg(struct vm* vm, vaddr_t addr)
{
    emul_handler_t handler = NULL;
    list_foreach (vm->emul_reg_list, struct emul_reg, emu) {
        if (emu->addr == addr) {
            handler = emu->handler;
            break;
        }
    }

    return handler;
}

/**
 * @brief Broadcast a message to all CPUs assigned to the calling CPU's VM.
 * @note The callee do not receive the message.
 * @param vm Pointer to the VM whose CPU members receive the message.
 * @param msg Pointer to the message to broadcast.
 * @see cpu_send_msg(), cpu(), vm, cpu_msg
 */
void vm_msg_broadcast(struct vm* vm, struct cpu_msg* msg)
{
    for (size_t i = 0, n = 0; n < vm->cpu_num - 1; i++) {
        if (((1U << i) & vm->cpus) && (i != cpu()->id)) {
            n++;
            cpu_send_msg(i, msg);
        }
    }
}

/**
 * @brief Translate a virtual CPU mask to a physical CPU mask.
 * @param vm Pointer to the hypervisor's private VM data structure, storing the CPUs ID assigned to the VM.
 * @param mask Virtual CPU bitmask to translate.
 * @param len Number of bits in the mask to consider.
 * @return cpumap_t Physical CPU bitmask corresponding to the input virtual mask.
 * @see vm_translate_to_pcpuid(), vm, cpumap_t, cpuid_t, INVALID_CPUID
 */
__attribute__((weak)) cpumap_t vm_translate_to_pcpu_mask(struct vm* vm, cpumap_t mask, size_t len)
{
    cpumap_t pmask = 0;
    cpuid_t shift;
    for (size_t i = 0; i < len; i++) {
        if ((mask & (1ULL << i)) && ((shift = vm_translate_to_pcpuid(vm, i)) != INVALID_CPUID)) {
            pmask |= (1UL << shift);
        }
    }
    return pmask;
}

/**
 * @brief Translate a physical CPU mask to a virtual CPU mask.
 * @param vm Pointer to the hypervisor's private VM data structure, storing the CPUs ID assigned to the VM.
 * @param mask Physical CPU bitmask to translate.
 * @param len Number of bits in the mask to consider.
 * @return cpumap_t Virtual CPU bitmask corresponding to the input physical mask.
 * @see vm_translate_to_vcpuid(), vm, cpumap_t, vcpuid_t, INVALID_CPUID
 */
__attribute__((weak)) cpumap_t vm_translate_to_vcpu_mask(struct vm* vm, cpumap_t mask, size_t len)
{
    cpumap_t pmask = 0;
    vcpuid_t shift;
    for (size_t i = 0; i < len; i++) {
        if ((mask & (1ULL << i)) && ((shift = vm_translate_to_vcpuid(vm, i)) != INVALID_CPUID)) {
            pmask |= (1UL << shift);
        }
    }
    return pmask;
}

/**
 * @brief Start an active virtual CPU
 * If the virtual CPU is power-on and it is active, the ISA-specific
 * entry point is reached (the hypervisor context is left).
 * If the CPU is not active, it is sent into stand-by mode.
 * If the virtual CPU is not powered on, it
 * @param vcpu Pointer to the VCPU to run
 * @see vcpu_arch_is_on(), vcpu, vcpu_arch_entry(), cpu_standby(), cpu_powerdown().
 */
void vcpu_run(struct vcpu* vcpu)
{
    if (vcpu_arch_is_on(vcpu)) {
        if (vcpu->active) {
            vcpu_arch_entry();
        } else {
            cpu_standby();
        }
    } else {
        cpu_powerdown();
    }
}

/**
 * @brief Grant a VM access to a device's MMIO region.
 * @note Not implemented. It is ISA-specific
 * @see ERROR()
 */
__attribute__((weak)) void vm_arch_allow_mmio_access(struct vm* vm, struct vm_dev_region* dev)
{
    UNUSED_ARG(dev);
    UNUSED_ARG(vm);
    ERROR("vm_arch_allow_mmio_access must be implemented by the arch!\n")
    return;
}
