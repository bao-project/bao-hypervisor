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

#include <vm.h>
#include <string.h>
#include <mem.h>
#include <cache.h>

enum emul_type {EMUL_MEM, EMUL_REG};
struct emul_node {
    node_t node;
    enum emul_type type;
    union {
        emul_mem_t emu_mem;
        emul_reg_t emu_reg;
    };
};

static void vm_master_init(vm_t* vm, const vm_config_t* config, uint64_t vm_id)
{
    vm->master = cpu.id;
    vm->config = config;
    vm->cpu_num = config->platform.cpu_num;
    vm->id = vm_id;

    cpu_sync_init(&vm->sync, vm->cpu_num);

    as_init(&vm->as, AS_VM, vm_id, NULL, config->colors);

    list_init(&vm->emul_list);
    objcache_init(&vm->emul_oc, sizeof(struct emul_node), SEC_HYP_VM, false);
}

void vm_cpu_init(vm_t* vm)
{
    spin_lock(&vm->lock);
    vm->cpus |= (1UL << cpu.id);
    spin_unlock(&vm->lock);
}

void vm_vcpu_init(vm_t* vm, const vm_config_t* config)
{
    size_t n = NUM_PAGES(sizeof(vcpu_t));
    vcpu_t* vcpu = (vcpu_t*)mem_alloc_page(n, SEC_HYP_VM, false);
    if(vcpu == NULL){ ERROR("failed to allocate vcpu"); }
    memset(vcpu, 0, n * PAGE_SIZE);

    cpu.vcpu = vcpu;
    vcpu->phys_id = cpu.id;
    vcpu->vm = vm;

    uint64_t count = 0, offset = 0;
    while (count < vm->cpu_num) {
        if (offset == cpu.id) {
            vcpu->id = count;
            break;
        }
        if ((1UL << offset) & vm->cpus) {
            count++;
        }
        offset++;
    }

    memset(vcpu->stack, 0, sizeof(vcpu->stack));
    vcpu->regs = (struct arch_regs*)(vcpu->stack + sizeof(vcpu->stack) -
                                     sizeof(*vcpu->regs));

    vcpu_arch_init(vcpu, vm);
    vcpu_arch_reset(vcpu, config->entry);

    list_push(&vm->vcpu_list, &vcpu->node);
}

static void vm_copy_img_to_rgn(vm_t* vm, const vm_config_t* config,
                               struct mem_region* reg)
{
    /* map original img address */
    size_t n_img = NUM_PAGES(config->image.size);
    ppages_t src_pa_img = mem_ppages_get(config->image.load_addr, n_img);
    void* src_va = mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL, n_img);
    if (mem_map(&cpu.as, src_va, &src_pa_img, n_img, PTE_HYP_FLAGS)) {
        ERROR("mem_map failed %s", __func__);
    }

    /* map new address */
    uint64_t offset = config->image.base_addr - reg->base;
    uint64_t dst_phys = reg->phys + offset;
    ppages_t dst_pp = mem_ppages_get(dst_phys, n_img);
    void* dst_va = mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL, n_img);
    if (mem_map(&cpu.as, dst_va, &dst_pp, n_img, PTE_HYP_FLAGS)) {
        ERROR("mem_map failed %s", __func__);
    }

    memcpy(dst_va, src_va, n_img * PAGE_SIZE);
    cache_flush_range(dst_va, n_img * PAGE_SIZE);
    /*TODO: unmap */
}

void vm_map_mem_region(vm_t* vm, struct mem_region* reg)
{
    size_t n = NUM_PAGES(reg->size);
    void* va = mem_alloc_vpage(&vm->as, SEC_VM_ANY, (void*)reg->base, n);
    if (va != (void*)reg->base) {
        ERROR("failed to allocate vm's dev address");
    }

    if (reg->place_phys) {
        ppages_t pa_reg = mem_ppages_get(reg->phys, n);
        mem_map(&vm->as, va, &pa_reg, n, PTE_VM_FLAGS);
    } else {
        mem_map(&vm->as, va, NULL, n, PTE_VM_FLAGS);
    }
}

static void vm_map_img_rgn_inplace(vm_t* vm, const vm_config_t* config,
                                   struct mem_region* reg)
{
    /* mem region pages before the img */
    size_t n_before = (config->image.base_addr - reg->base) / PAGE_SIZE;
    /* pages after the img */
    size_t n_aft = ((reg->base + reg->size) -
                    (config->image.base_addr + config->image.size)) /
                   PAGE_SIZE;
    /* mem region pages for img */
    size_t n_img = NUM_PAGES(config->image.size);

    size_t n_total = n_before + n_aft + n_img;

    /* map img in place */
    ppages_t pa_img = mem_ppages_get(config->image.load_addr, n_img);
    void* va = mem_alloc_vpage(&vm->as, SEC_VM_ANY, (void*)reg->base, n_total);

    /* map pages before img */
    mem_map(&vm->as, va, NULL, n_before, PTE_VM_FLAGS);

    if (all_clrs(vm->as.colors)) {
        /* map img in place */
        mem_map(&vm->as, va + n_before * PAGE_SIZE, &pa_img, n_img,
                PTE_VM_FLAGS);
        /* we are mapping in place, config is already reserved */
    } else {
        /* recolour img */
        mem_map_reclr(&vm->as, va + n_before * PAGE_SIZE, &pa_img, n_img,
                      PTE_VM_FLAGS);
        /* TODO: reserve phys mem? */
    }
    /* map pages after img */
    mem_map(&vm->as, va + (n_before + n_img) * PAGE_SIZE, NULL, n_aft,
            PTE_VM_FLAGS);
}

static void vm_map_img_rgn(vm_t* vm, const vm_config_t* config,
                           struct mem_region* reg)
{
    if (reg->place_phys) {
        vm_copy_img_to_rgn(vm, config, reg);
        vm_map_mem_region(vm, reg);
    } else {
        vm_map_img_rgn_inplace(vm, config, reg);
    }
}

static void vm_init_mem_regions(vm_t* vm, const vm_config_t* config)
{
    for (int i = 0; i < config->platform.region_num; i++) {
        struct mem_region* reg = &config->platform.regions[i];
        int img_is_in_rgn = range_in_range(
            config->image.base_addr, config->image.size, reg->base, reg->size);
        if (img_is_in_rgn) {
            vm_map_img_rgn(vm, config, reg);
        } else {
            vm_map_mem_region(vm, reg);
        }
    }
}

static void vm_init_ipc(vm_t* vm, const vm_config_t* config)
{
    vm->ipc_num = config->platform.ipc_num;
    vm->ipcs = config->platform.ipcs;
    for (int i = 0; i < config->platform.ipc_num; i++) {
        ipc_t *ipc = &config->platform.ipcs[i];
        shmem_t *shmem = ipc_get_shmem(ipc->shmem_id);
        if(shmem == NULL) {
            WARNING("Invalid shmem id in configuration. Ignored.");
            continue;
        }
        size_t size = ipc->size;
        if(ipc->size > shmem->size) {
            size = shmem->size;
            WARNING("Trying to map region to smaller shared memory. Truncated");
        }
        struct mem_region reg = {
            .base = ipc->base,
            .size = size,
            .place_phys = true,
            .phys = shmem->phys,
            .colors = shmem->colors
        };

        vm_map_mem_region(vm, &reg);
    }
}

static void vm_init_dev(vm_t* vm, const vm_config_t* config)
{
    for (int i = 0; i < config->platform.dev_num; i++) {
        struct dev_region* dev = &config->platform.devs[i];

        size_t n = ALIGN(dev->size, PAGE_SIZE) / PAGE_SIZE;

        void* va = mem_alloc_vpage(&vm->as, SEC_VM_ANY, (void*)dev->va, n);
        mem_map_dev(&vm->as, va, dev->pa, n);

        for (int j = 0; j < dev->interrupt_num; j++) {
            interrupts_vm_assign(vm, dev->interrupts[j]);
        }
    }

    /* iommu */
    if (iommu_vm_init(vm, config) >= 0) {
        for (int i = 0; i < config->platform.dev_num; i++) {
            struct dev_region* dev = &config->platform.devs[i];
            if (dev->id) {
                if(iommu_vm_add_device(vm, dev->id) < 0){
                    ERROR("Failed to add device to iommu");
                }
            }
        }
    }
      
}

void vm_init(vm_t* vm, const vm_config_t* config, bool master, uint64_t vm_id)
{
    /**
     * Before anything else, initialize vm structure.
     */
    if (master) {
        vm_master_init(vm, config, vm_id);
    }

    /*
     *  Initialize each core.
     */
    vm_cpu_init(vm);

    cpu_sync_barrier(&vm->sync);

    /*
     *  Initialize each virtual core.
     */
    vm_vcpu_init(vm, config);

    cpu_sync_barrier(&vm->sync);

    /**
     * Perform architecture dependent initializations. This includes,
     * for example, setting the page table pointer and other virtualization
     * extensions specifics.
     */
    vm_arch_init(vm, config);

    /**
     * Create the VM's address space according to configuration and where
     * its image was loaded.
     */
    if (master) {
        vm_init_mem_regions(vm, config);
        vm_init_dev(vm, config);
        vm_init_ipc(vm, config);
    }

    cpu_sync_barrier(&vm->sync);
}

vcpu_t* vm_get_vcpu(vm_t* vm, uint64_t vcpuid)
{
    list_foreach(vm->vcpu_list, vcpu_t, vcpu)
    {
        if (vcpu->id == vcpuid) return vcpu;
    }

    return NULL;
}

void vm_emul_add_mem(vm_t* vm, emul_mem_t* emu)
{
    struct emul_node* ptr = objcache_alloc(&vm->emul_oc);
    if (ptr != NULL) {
        ptr->type = EMUL_MEM;
        ptr->emu_mem = *emu;
        list_push(&vm->emul_list, (void*)ptr);
        // TODO: if we plan to grow the VM's PAS dynamically, after
        // inialization,
        // the pages for this emulation region must be reserved in the stage 2
        // page table.
    }
}

void vm_emul_add_reg(vm_t* vm, emul_reg_t* emu)
{
    struct emul_node* ptr = objcache_alloc(&vm->emul_oc);
    if (ptr != NULL) {
        ptr->type = EMUL_REG;
        ptr->emu_reg = *emu;
        list_push(&vm->emul_list, (void*)ptr);
        // TODO: if we plan to grow the VM's PAS dynamically, after
        // inialization,
        // the pages for this emulation region must be reserved in the stage 2
        // page table.
    }

}    

static inline emul_handler_t vm_emul_get(vm_t* vm, enum emul_type type, uint64_t addr)
{
    emul_handler_t handler = NULL;
    list_foreach(vm->emul_list, struct emul_node, node)
    {
        if (node->type == EMUL_MEM) {
            emul_mem_t* emu = &node->emu_mem;
            if (addr >= emu->va_base && (addr < (emu->va_base + emu->size))) {
                handler = emu->handler;
                break;
            }
        } else {
            emul_reg_t *emu = &node->emu_reg;
            if(emu->addr == addr) {
                handler = emu->handler;
                break; 
            }
        }
    }

    return handler;
}

emul_handler_t vm_emul_get_mem(vm_t* vm, uint64_t addr)
{
    return vm_emul_get(vm, EMUL_MEM, addr);
}

emul_handler_t vm_emul_get_reg(vm_t* vm, uint64_t addr)
{
    return vm_emul_get(vm, EMUL_REG, addr);
}

void vm_msg_broadcast(vm_t* vm, cpu_msg_t* msg)
{
    for (int i = 0, n = 0; n < vm->cpu_num - 1; i++) {
        if (((1U << i) & vm->cpus) && (i != cpu.id)) {
            n++;
            cpu_send_msg(i, msg);
        }
    }
}

__attribute__((weak)) uint64_t vm_translate_to_pcpu_mask(vm_t* vm,
                                                         uint64_t mask,
                                                         size_t len)
{
    uint64_t pmask = 0;
    int shift;
    for (int i = 0; i < len; i++) {
        if ((mask & (1ULL << i)) &&
            ((shift = vm_translate_to_pcpuid(vm, i)) >= 0)) {
            pmask |= (1ULL << shift);
        }
    }
    return pmask;
}

__attribute__((weak)) uint64_t vm_translate_to_vcpu_mask(vm_t* vm,
                                                         uint64_t mask,
                                                         size_t len)
{
    uint64_t pmask = 0;
    int shift;
    for (int i = 0; i < len; i++) {
        if ((mask & (1ULL << i)) &&
            ((shift = vm_translate_to_vcpuid(vm, i)) >= 0)) {
            pmask |= (1ULL << shift);
        }
    }
    return pmask;
}

void vcpu_run(vcpu_t* vcpu)
{
    cpu.vcpu->active = true;
    vcpu_arch_run(vcpu);
}
