/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <string.h>
#include <mem.h>
#include <cache.h>
#include <config.h>
#include <shmem.h>
#include <objpool.h>

static void vm_master_init(struct vm* vm, const struct vm_config* vm_config, vmid_t vm_id)
{
    vm->master = cpu()->id;
    vm->config = vm_config;
    vm->cpu_num = vm_config->platform.cpu_num;
    vm->id = vm_id;
    vm->lock = SPINLOCK_INITVAL;

    cpu_sync_init(&vm->sync, vm->cpu_num);

    vm_mem_prot_init(vm, vm_config);
}

static void vm_cpu_init(struct vm* vm)
{
    spin_lock(&vm->lock);
    vm->cpus |= (1UL << cpu()->id);
    vm->as.cpus |= (1UL << cpu()->id);
    spin_unlock(&vm->lock);
}

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
        ERROR("failed to allocate vm's region at 0x%lx", reg->base);
    }
}

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
                  " image runtime region");
        }
    }

    size_t img_num_pages = NUM_PAGES(vm->config->image.size);
    struct ppages img_ppages = mem_ppages_get(vm->config->image.load_addr, img_num_pages);
    vaddr_t src_va = mem_alloc_map(&cpu()->as, SEC_HYP_GLOBAL, &img_ppages, INVALID_VA,
        img_num_pages, PTE_HYP_FLAGS);
    vaddr_t dst_va =
        mem_map_cpy(&vm->as, &cpu()->as, vm->config->image.base_addr, INVALID_VA, img_num_pages);
    memcpy((void*)dst_va, (void*)src_va, vm->config->image.size);
    cache_flush_range((vaddr_t)dst_va, vm->config->image.size);
    mem_unmap(&cpu()->as, src_va, img_num_pages, false);
    mem_unmap(&cpu()->as, dst_va, img_num_pages, false);
}

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

static void vm_init_ipc(struct vm* vm, const struct vm_config* vm_config)
{
    vm->ipc_num = vm_config->platform.ipc_num;
    vm->ipcs = vm_config->platform.ipcs;
    for (size_t i = 0; i < vm_config->platform.ipc_num; i++) {
        struct ipc* ipc = &vm_config->platform.ipcs[i];
        struct shmem* shmem = shmem_get(ipc->shmem_id);
        if (shmem == NULL) {
            WARNING("Invalid shmem id in configuration. Ignored.");
            continue;
        }
        size_t size = ipc->size;
        if (ipc->size > shmem->size) {
            size = shmem->size;
            WARNING("Trying to map region to smaller shared memory. Truncated");
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

static void vm_init_dev(struct vm* vm, const struct vm_config* vm_config)
{
    for (size_t i = 0; i < vm_config->platform.dev_num; i++) {
        struct vm_dev_region* dev = &vm_config->platform.devs[i];

        size_t n = ALIGN(dev->size, PAGE_SIZE) / PAGE_SIZE;

        if (dev->va != INVALID_VA) {
            mem_alloc_map_dev(&vm->as, SEC_VM_ANY, (vaddr_t)dev->va, dev->pa, n);
        }

        for (size_t j = 0; j < dev->interrupt_num; j++) {
            if (!interrupts_vm_assign(vm, dev->interrupts[j])) {
                ERROR("Failed to assign interrupt id %d", dev->interrupts[j]);
            }
        }
    }

    if (io_vm_init(vm, vm_config)) {
        for (size_t i = 0; i < vm_config->platform.dev_num; i++) {
            struct vm_dev_region* dev = &vm_config->platform.devs[i];
            if (dev->id) {
                if (!io_vm_add_device(vm, dev->id)) {
                    ERROR("Failed to add device to iommu");
                }
            }
        }
    }
}

static void vm_init_remio_dev(struct vm* vm, struct remio_dev* remio_dev)
{
    struct shmem* shmem = shmem_get(remio_dev->shmem.shmem_id);
    if (shmem == NULL) {
        ERROR("Invalid shmem id (%d) in the Remote I/O device (%d) configuration",
            remio_dev->shmem.shmem_id, remio_dev->bind_key);
    }
    size_t shmem_size = remio_dev->shmem.size;
    if (shmem_size > shmem->size) {
        shmem_size = shmem->size;
        WARNING("Trying to map region to smaller shared memory. Truncated");
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

static struct vm* vm_allocation_init(struct vm_allocation* vm_alloc)
{
    struct vm* vm = vm_alloc->vm;
    vm->vcpus = vm_alloc->vcpus;
    return vm;
}

struct vm* vm_init(struct vm_allocation* vm_alloc, const struct vm_config* vm_config, bool master,
    vmid_t vm_id)
{
    struct vm* vm = vm_allocation_init(vm_alloc);

    /**
     * Before anything else, initialize vm structure.
     */
    if (master) {
        vm_master_init(vm, vm_config, vm_id);
    }

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

void vm_emul_add_mem(struct vm* vm, struct emul_mem* emu)
{
    list_push(&vm->emul_mem_list, &emu->node);
}

void vm_emul_add_reg(struct vm* vm, struct emul_reg* emu)
{
    list_push(&vm->emul_reg_list, &emu->node);
}

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

void vm_msg_broadcast(struct vm* vm, struct cpu_msg* msg)
{
    for (size_t i = 0, n = 0; n < vm->cpu_num - 1; i++) {
        if (((1U << i) & vm->cpus) && (i != cpu()->id)) {
            n++;
            cpu_send_msg(i, msg);
        }
    }
}

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
