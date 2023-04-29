/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <vm.h>
#include <bao.h>
#include <fences.h>
#include <platform_defs.h>
#include <objpool.h>
#include <config.h>

struct shared_region {
    enum AS_TYPE as_type;
    asid_t asid;
    struct mp_region region;
    cpumap_t sharing_cpus;
};

void mem_handle_broadcast_region(uint32_t event, uint64_t data);
bool mem_map(struct addr_space *as, struct mp_region *mpr, bool broadcast);
bool mem_unmap_range(struct addr_space *as, vaddr_t vaddr, size_t size, bool broadcast);

enum { MEM_INSERT_REGION, MEM_REMOVE_REGION };

#define SHARED_REGION_POOL_SIZE_DEFAULT (128)
#ifndef SHARED_REGION_POOL_SIZE
#define SHARED_REGION_POOL_SIZE SHARED_REGION_POOL_SIZE_DEFAULT
#endif
OBJPOOL_ALLOC(shared_region_pool, struct shared_region, SHARED_REGION_POOL_SIZE);

static inline struct mpe* mem_vmpu_get_entry(struct addr_space* as, mpid_t mpid)
{
    if (mpid < VMPU_NUM_ENTRIES) {
        return &as->vmpu[mpid];
    }
    return NULL;
}

void mem_vmpu_set_entry(struct addr_space *as, mpid_t mpid, struct mp_region *mpr)
{
    struct mpe *mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = mpr->base;
    mpe->region.size = mpr->size;
    mpe->region.mem_flags = mpr->mem_flags;
    mpe->region.as_sec = mpr->as_sec;
    mpe->state = MPE_S_VALID;
}

void mem_vmpu_clear_entry(struct addr_space *as, mpid_t mpid)
{
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = 0;
    mpe->region.size = 0;
    mpe->region.mem_flags = PTE_INVALID;
    mpe->region.as_sec = SEC_UNKNOWN;
    mpe->state = MPE_S_INVALID;
}

void mem_vmpu_free_entry(struct addr_space *as, mpid_t mpid)
{
    mem_vmpu_clear_entry(as, mpid);
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);
    mpe->state = MPE_S_FREE;
}

mpid_t mem_vmpu_allocate_entry(struct addr_space *as)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < VMPU_NUM_ENTRIES; i++) {
        struct mpe* mpe = mem_vmpu_get_entry(as, i);
        if (mpe->state == MPE_S_FREE) {
            mpid = i;
            mpe->state = MPE_S_INVALID;
            break;
        }
    }

    return mpid;
}

mpid_t mem_vmpu_get_entry_by_addr(struct addr_space* as, vaddr_t addr)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < VMPU_NUM_ENTRIES; i++) {

        struct mpe *mpe =  mem_vmpu_get_entry(as, i);

        if (mpe->state != MPE_S_VALID) {
            continue;
        }

        vaddr_t limit_addr = mpe->region.base + mpe->region.size;
        if((addr >= mpe->region.base) && (addr < limit_addr)) {
                mpid = i;
                break;
         }
    }

    return mpid;
}

static inline priv_t as_priv(struct addr_space *as)
{
    priv_t priv;

    switch (as->type) {
        case AS_HYP:
        /* fallthrough */
        case AS_HYP_CPY:
            priv = PRIV_HYP;
            break;
        case AS_VM:
            priv = PRIV_VM;
            break;
        default:
            priv = PRIV_NONE;
    }

    return priv;
}

static void as_init_boot_regions()
{

    /**
     * Add hypervisor mpu entries set up during boot to the vmpu:
     *  - hypervisor image (loadable and non-loadable)
     *  - private cpu region
    */

    extern uint8_t _image_start, _image_load_end, _image_noload_start, _image_end;
    vaddr_t image_start = (vaddr_t)&_image_start;
    vaddr_t image_load_end = (vaddr_t)&_image_load_end;
    vaddr_t image_noload_start = (vaddr_t)&_image_noload_start;
    vaddr_t image_end = (vaddr_t)&_image_end;

    struct mp_region mpr;
    mpid_t mpid = 0;

    bool separate_noload_region = image_load_end != image_noload_start;
    vaddr_t first_region_end = separate_noload_region ? image_load_end : image_end;

    mpr = (struct mp_region) {
        .base = image_start,
        .size = (size_t) (first_region_end - image_start),
        .mem_flags = PTE_HYP_FLAGS,
        .as_sec = SEC_HYP_IMAGE,
    };
    mem_vmpu_set_entry(&cpu()->as, mpid, &mpr);
    mpid++;

    if (separate_noload_region) {
        mpr = (struct mp_region) {
            .base = image_noload_start,
            .size = (size_t) image_end - image_noload_start,
            .mem_flags = PTE_HYP_FLAGS,
            .as_sec = SEC_HYP_IMAGE,
        };
        mem_vmpu_set_entry(&cpu()->as, mpid, &mpr);
        mpid++;
    }

    mpr = (struct mp_region) {
        .base = (vaddr_t)cpu(),
        .size =  ALIGN(sizeof(struct cpu), PAGE_SIZE),
        .mem_flags = PTE_HYP_FLAGS,
        .as_sec = SEC_HYP_PRIVATE,
    };
    mem_vmpu_set_entry(&cpu()->as, mpid, &mpr);
    mpid++;
}

void mem_prot_init()
{
    mpu_init();
    as_init(&cpu()->as, AS_HYP, HYP_ASID, 0);
    as_init_boot_regions();
}

size_t mem_cpu_boot_alloc_size()
{
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

void as_init(struct addr_space *as, enum AS_TYPE type, asid_t id, colormap_t colors)
{
    as->type = type;
    as->colors = 0;
    as->id = id;
    as_arch_init(as);

    for(size_t i=0; i<VMPU_NUM_ENTRIES; i++) {
        mem_vmpu_free_entry(as, i);
    }
}

static void mem_free_ppages(struct ppages *ppages)
{
    list_foreach(page_pool_list, struct page_pool, pool)
    {
        spin_lock(&pool->lock);
        if (in_range(ppages->base, pool->base, pool->size * PAGE_SIZE)) {
            size_t index = (ppages->base - pool->base) / PAGE_SIZE;
            bitmap_clear_consecutive(pool->bitmap, index, ppages->num_pages);
        }
        spin_unlock(&pool->lock);
    }
}

void mem_msg_handler(uint32_t event, uint64_t data)
{
    mem_handle_broadcast_region(event, data);
}
CPU_MSG_HANDLER(mem_msg_handler, MEM_PROT_SYNC);

static cpumap_t mem_section_shared_cpus(struct addr_space *as, as_sec_t section)
{
    cpumap_t cpus = 0;
    if (as->type == AS_HYP) {
        if ((section == SEC_HYP_GLOBAL) ||  (section == SEC_HYP_IMAGE)) {
            cpus = BIT_MASK(0, PLAT_CPU_NUM);
        } else if (section == SEC_HYP_VM) {
            /**
             * If we don't have a valid vcpu at this point, it means we are
             * creating this region before even having a vm. Therefore, the
             * sharing of the region must be guaranteed by other means (e.g.
             * vmm_vm_install)
             */
            if (cpu()->vcpu != NULL) {
                cpus = cpu()->vcpu->vm->cpus;
            }
        }
    } else {
        cpus = cpu()->vcpu->vm->cpus;
    }

    return cpus;
}

void mem_region_broadcast(struct addr_space *as, struct mp_region *mpr, uint32_t op)
{
    cpumap_t shared_cpus = mem_section_shared_cpus(as, mpr->as_sec);

    if(shared_cpus == 0) {
        return;
    }

    struct shared_region shared_region = {
        .as_type = as->type,
        .asid = as->id,
        .region = *mpr,
    };

    for (cpuid_t cpuid = 0; cpuid < PLAT_CPU_NUM; cpuid++) {
        if ((cpu()->id != cpuid) && bit_get(shared_cpus, cpuid)) {
            struct shared_region *node = objpool_alloc(&shared_region_pool);
            if (node == NULL) {
                ERROR("Failed allocating shared region node");
            }
            *node = shared_region;
            struct cpu_msg msg = {MEM_PROT_SYNC, op, (uintptr_t) node};
            cpu_send_msg(cpuid, &msg);
        }
    }
}

bool mem_vmpu_insert_region(struct addr_space *as, mpid_t mpid,
    struct mp_region *mpr, bool broadcast)
{
    if (mpid == INVALID_MPID) {
        return false;
    }

    if (mpu_map(as_priv(as), mpr)) {
        mem_vmpu_set_entry(as, mpid, mpr);
        if (broadcast) {
            mem_region_broadcast(as, mpr, MEM_INSERT_REGION);
        }
        return true;
    }

    return false;
}

bool mem_vmpu_remove_region(struct addr_space* as, mpid_t mpid, bool broadcast)
{
    bool removed = false;

    struct mpe *mpe = mem_vmpu_get_entry(as, mpid);

    if ((mpe != NULL) && (mpe->state == MPE_S_VALID)) {
        if (broadcast) {
            mem_region_broadcast(as, &mpe->region, MEM_REMOVE_REGION);
        }
        mpu_unmap(as_priv(as), &mpe->region);
        mem_vmpu_free_entry(as, mpid);
        removed = true;
    }

    return removed;
}

void mem_handle_broadcast_insert(struct addr_space *as, struct mp_region *mpr)
{
    if (as->type == AS_HYP) {
        mem_map(&cpu()->as, mpr, false);
    } else {
        mpu_map(as_priv(as), mpr);
    }
}

void mem_handle_broadcast_remove(struct addr_space *as, struct mp_region *mpr)
{
    if (as->type == AS_HYP) {
        mem_unmap_range(&cpu()->as, mpr->base, mpr->size, false);
    } else {
        mpu_unmap(as_priv(as), mpr);
    }
}

void mem_handle_broadcast_region(uint32_t event, uint64_t data)
{
    struct shared_region* sh_reg = (struct shared_region*) (uintptr_t)data;

    if(sh_reg != NULL) {
        struct addr_space *as;
        if (sh_reg->as_type == AS_HYP) {
            as = &cpu()->as;
        } else {
            struct addr_space *vm_as = &cpu()->vcpu->vm->as;
            if (vm_as->id != sh_reg->asid) {
                ERROR("Received shared region for unkown vm address space.");
            }
            as = vm_as;
        }

        switch(event){
            case MEM_INSERT_REGION:
                mem_handle_broadcast_insert(as, &sh_reg->region);
                break;
            case MEM_REMOVE_REGION:
                mem_handle_broadcast_remove(as, &sh_reg->region);
                break;
            default:
                ERROR("unknown mem broadcast msg");
        }

        objpool_free(&shared_region_pool, sh_reg);
    }
}

mpid_t mem_vmpu_find_overlapping_region(struct addr_space *as, 
    struct mp_region *region)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < VMPU_NUM_ENTRIES; i++) {

        struct mpe* mpe = mem_vmpu_get_entry(as, i);

        if (mpe->state != MPE_S_VALID) {
            continue;
        }

        if (mem_regions_overlap(region, &mpe->region)) {
            mpid = i;
            break;
        }

    }

    return mpid;
}

bool mem_map(struct addr_space *as, struct mp_region *mpr, bool broadcast)
{
    bool mapped = false;

    if (mpr->size == 0) {
        return true;
    }

    if ((mpr->size % mpu_granularity()) != 0) {
        ERROR("trying to set mpu region which is not a multiple of granularity");
    }

    spin_lock(&as->lock);
    
    if (mem_vmpu_find_overlapping_region(as, mpr) == INVALID_MPID) {
        // TODO: check if it possible to merge with another region
        mpid_t mpid = mem_vmpu_allocate_entry(as);
        if (mpid != INVALID_MPID) {
            mapped = mem_vmpu_insert_region(as, mpid, mpr, broadcast);
        }

    }

    spin_unlock(&as->lock);

    return mapped;
}

bool mem_unmap_range(struct addr_space *as, vaddr_t vaddr, size_t size, bool broadcast)
{
    spin_lock(&as->lock);

    size_t size_left = size;

    while (size_left > 0) {

        struct mp_region reg = (struct mp_region) {
            reg.base = vaddr,
            reg.size = size,
        };
        mpid_t mpid = mem_vmpu_find_overlapping_region(as, &reg);
        if (mpid == INVALID_MPID) {
            /**
             * FIXME: right now we are ignoring the fact that the range  or
             * parts of it might not be mapped. This is in line to what the MMU
             * mem_unmap function does. We should change this to only go ahead
             * with the unpamming if the full range is indeed mapped.
            */
            break;
        }
        struct mpe *mpe = mem_vmpu_get_entry(as, mpid);
        reg = mpe->region;

        vaddr_t limit = vaddr + size;
        vaddr_t r_limit = reg.base + reg.size;
        vaddr_t r_base = reg.base;

        size_t top_size = limit >= r_limit ? 0 : r_limit - limit;
        size_t bottom_size = vaddr <= r_base ? 0 : vaddr - r_base;

        mem_vmpu_remove_region(as, mpid, true);

        if (top_size > 0) {
            struct mp_region top = reg;
            top.base = limit;
            top.size = top_size;
            mpid_t top_mpid = mem_vmpu_allocate_entry(as);
            mem_vmpu_insert_region(as, top_mpid, &top, true);
        }

        if (bottom_size > 0) {
            struct mp_region bottom = reg;
            bottom.size = bottom_size;
            mpid_t bottom_mpid = mem_vmpu_allocate_entry(as);
            mem_vmpu_insert_region(as, bottom_mpid, &bottom, true);
        }

        size_t overlap_size = reg.size - top_size - bottom_size;
        size_left -= overlap_size;
    }

    spin_unlock(&as->lock);

    return size_left == 0;
}


void mem_unmap(struct addr_space *as, vaddr_t at, size_t num_pages,
    bool free_ppages)
{
    if (mem_unmap_range(as, at, num_pages * PAGE_SIZE, true) && free_ppages) {
        struct ppages ppages = mem_ppages_get(at, num_pages);
        mem_free_ppages(&ppages);
    }
}

vaddr_t mem_map_cpy(struct addr_space *ass, struct addr_space *asd, vaddr_t vas,
                vaddr_t vad, size_t num_pages)
{
    struct mpe *mpe;
    struct mp_region mpr;
    vaddr_t va_res = INVALID_VA;

    if ((ass != asd) && (vad == INVALID_VA || vad == vas)) {
        // In mpu-based systems, we can only copy mappings between address
        // spaces, as copying a mapping in a single address space would overlap
        // the orignal mapping. Also because only identify mappings are
        // supported, the source va must equal the destination va, or be an
        // invalid va. This still covers the most useful uses cases.

        spin_lock(&ass->lock);
        mpid_t reg_num_src = mem_vmpu_get_entry_by_addr(ass, vas);
        mpe = mem_vmpu_get_entry(ass, reg_num_src);
        mpr = mpe->region;
        spin_unlock(&ass->lock);

        if (mem_map(asd, &mpr, true)) {
            va_res = vas;
        } else {
            INFO("failed mem map on mem map cpy");
        }
    } else {
        INFO("failed mem map cpy");
    }

    return va_res;
}

bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa)
{
    if (mem_vmpu_get_entry_by_addr(as, va) != INVALID_MPID) {
        *pa = va;
        return true;
    } else {
        return false;
    }
}

vaddr_t mem_alloc_map(struct addr_space* as, as_sec_t section,
    struct ppages *ppages, vaddr_t at, size_t num_pages, mem_flags_t flags)
{
    // TODO: Check if page->base, page->size and vaddr_t at are page_size align?

    struct ppages temp_ppages;

    if (at == INVALID_VA && ppages == NULL) {
        ERROR ("Can't map an MPU region because neither the virtual"
            "or phsyical address was specified.");
    } 
    
    if (at != INVALID_VA && ppages != NULL && at != ppages->base) {
        ERROR ("Trying to map non identity");
    }
    
    if (at == INVALID_VA) {
        at = ppages->base;
    } else if (ppages == NULL) {
        temp_ppages = mem_ppages_get(at, num_pages);
        ppages = &temp_ppages;
    }

    struct mp_region mpr = (struct mp_region) {
        .base = ppages->base,
        .size = (num_pages * PAGE_SIZE),
        .as_sec = section,
        .mem_flags = flags,
    };

    mem_map(as, &mpr, true);

    return at;
}

vaddr_t mem_alloc_map_dev(struct addr_space* as, as_sec_t section,
                             vaddr_t at, paddr_t pa, size_t num_pages)
{
    struct ppages temp_page = mem_ppages_get(pa, num_pages);
    return mem_alloc_map(as, section, &temp_page, at, num_pages,
                   as->type == AS_HYP ? PTE_HYP_DEV_FLAGS : PTE_VM_DEV_FLAGS);
}


