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

#define MEM_BROADCAST      (true)
#define MEM_DONT_BROADCAST (false)

#define MEM_LOCKED         (true)
#define MEM_NOT_LOCKED     (false)

struct shared_region {
    enum AS_TYPE as_type;
    asid_t asid;
    struct mp_region region;
    cpumap_t sharing_cpus;
    bool lock;
};

void mem_handle_broadcast_region(uint32_t event, uint64_t data);
bool mem_unmap_range(struct addr_space* as, vaddr_t vaddr, size_t size, bool broadcast);

enum { MEM_INSERT_REGION, MEM_REMOVE_REGION, MEM_UPDATE_REGION };

#define SHARED_REGION_POOL_SIZE_DEFAULT (128)
#ifndef SHARED_REGION_POOL_SIZE
#define SHARED_REGION_POOL_SIZE SHARED_REGION_POOL_SIZE_DEFAULT
#endif
OBJPOOL_ALLOC(shared_region_pool, struct shared_region, SHARED_REGION_POOL_SIZE);

static inline struct mpe* mem_vmpu_get_entry(struct addr_space* as, mpid_t mpid)
{
    if (mpid < VMPU_NUM_ENTRIES) {
        return &as->vmpu.node[mpid];
    }
    return NULL;
}

static int vmpu_node_cmp(node_t* _n1, node_t* _n2)
{
    struct mpe* n1 = (struct mpe*)_n1;
    struct mpe* n2 = (struct mpe*)_n2;

    if (n1->region.base > n2->region.base) {
        return 1;
    } else if (n1->region.base < n2->region.base) {
        return -1;
    } else {
        return 0;
    }
}

static void mem_vmpu_set_entry(struct addr_space* as, mpid_t mpid, struct mp_region* mpr,
    bool locked)
{
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = mpr->base;
    mpe->region.size = mpr->size;
    mpe->region.mem_flags = mpr->mem_flags;
    mpe->region.as_sec = mpr->as_sec;
    mpe->state = MPE_S_VALID;
    mpe->mpid = mpid;
    mpe->lock = locked;

    list_insert_ordered(&as->vmpu.ordered_list, (node_t*)&as->vmpu.node[mpid], vmpu_node_cmp);
}

static void mem_vmpu_clear_entry(struct addr_space* as, mpid_t mpid)
{
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = 0;
    mpe->region.size = 0;
    mpe->region.mem_flags = PTE_INVALID;
    mpe->region.as_sec = SEC_UNKNOWN;
    mpe->state = MPE_S_INVALID;
    mpe->lock = false;
}

static void mem_vmpu_free_entry(struct addr_space* as, mpid_t mpid)
{
    mem_vmpu_clear_entry(as, mpid);
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);
    mpe->state = MPE_S_FREE;

    list_rm(&as->vmpu.ordered_list, (node_t*)&as->vmpu.node[mpid]);
}

static mpid_t mem_vmpu_allocate_entry(struct addr_space* as)
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

static void mem_vmpu_deallocate_entry(struct addr_space* as, mpid_t mpid)
{
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = 0;
    mpe->region.size = 0;
    mpe->region.mem_flags = PTE_INVALID;
    mpe->region.as_sec = SEC_UNKNOWN;
    mpe->state = MPE_S_FREE;
    mpe->lock = false;
}

static mpid_t mem_vmpu_get_entry_by_addr(struct addr_space* as, vaddr_t addr)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < VMPU_NUM_ENTRIES; i++) {
        struct mpe* mpe = mem_vmpu_get_entry(as, i);

        if (mpe->state != MPE_S_VALID) {
            continue;
        }

        vaddr_t limit_addr = mpe->region.base + mpe->region.size;
        if ((addr >= mpe->region.base) && (addr < limit_addr)) {
            mpid = i;
            break;
        }
    }

    return mpid;
}

static void mem_init_boot_regions(void)
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

#ifdef MEM_NON_UNIFIED
    extern uint8_t _data_vma_start;
    vaddr_t data_vma_start = (vaddr_t)&_data_vma_start;
#endif

    struct mp_region mpr;

    bool separate_noload_region = image_load_end != image_noload_start;
    vaddr_t first_region_end = separate_noload_region ? image_load_end : image_end;

    mpr = (struct mp_region){
        .base = image_start,
        .size = (size_t)(first_region_end - image_start),
#ifdef MEM_NON_UNIFIED
        .mem_flags = PTE_HYP_FLAGS_CODE,
#else
        .mem_flags = PTE_HYP_FLAGS,
#endif
        .as_sec = SEC_HYP_IMAGE,
    };
    mem_map(&cpu()->as, &mpr, MEM_DONT_BROADCAST, MEM_LOCKED);

    if (separate_noload_region) {
        mpr = (struct mp_region){
#ifdef MEM_NON_UNIFIED
            .base = data_vma_start,
            .size = (size_t)(image_end - data_vma_start),
#else
            .base = image_noload_start,
            .size = (size_t)image_end - image_noload_start,
#endif
            .mem_flags = PTE_HYP_FLAGS,
            .as_sec = SEC_HYP_IMAGE,
        };
        mem_map(&cpu()->as, &mpr, MEM_DONT_BROADCAST, MEM_LOCKED);
    }

    mpr = (struct mp_region){
        .base = (vaddr_t)cpu(),
        .size = ALIGN(sizeof(struct cpu), PAGE_SIZE),
        .mem_flags = PTE_HYP_FLAGS,
        .as_sec = SEC_HYP_PRIVATE,
    };
    mem_map(&cpu()->as, &mpr, MEM_DONT_BROADCAST, MEM_LOCKED);
}

void mem_prot_init()
{
    mpu_init();
    as_init(&cpu()->as, AS_HYP, 0);
    mem_init_boot_regions();
    if (DEFINED(MMIO_SLAVE_SIDE_PROT) && cpu_is_master()) {
        mem_mmio_init_regions(&cpu()->as);
    }
    mpu_enable();
}

size_t mem_cpu_boot_alloc_size()
{
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

void mem_mmio_init_regions(struct addr_space* as)
{
    for (unsigned long i = 0; i < platform.mmio_region_num; i++) {
        mem_alloc_map_dev(as, as->type == AS_VM ? SEC_VM_ANY : SEC_HYP_GLOBAL,
            platform.mmio_regions[i].base, platform.mmio_regions[i].base,
            NUM_PAGES(platform.mmio_regions[i].size));
    }
}

static unsigned long as_id_alloc(struct addr_space* as)
{
    static spinlock_t as_id_alloc_lock = SPINLOCK_INITVAL;
    static asid_t asid_counter = 1;
    unsigned long ret = 0;

    spin_lock(&as_id_alloc_lock);
    if (as->type != AS_HYP) {
        ret = asid_counter;
        asid_counter++;
    }
    spin_unlock(&as_id_alloc_lock);

    return ret;
}

void as_init(struct addr_space* as, enum AS_TYPE type, colormap_t colors)
{
    UNUSED_ARG(colors);

    as->type = type;
    as->colors = 0;
    as->id = as_id_alloc(as);
    as->lock = SPINLOCK_INITVAL;
    as_arch_init(as);

    list_init(&(as->vmpu.ordered_list));

    for (size_t i = 0; i < VMPU_NUM_ENTRIES; i++) {
        mem_vmpu_free_entry(as, i);
    }
}

static void mem_free_ppages(struct ppages* ppages)
{
    list_foreach (page_pool_list, struct page_pool, pool) {
        spin_lock(&pool->lock);
        if (in_range(ppages->base, pool->base, pool->num_pages * PAGE_SIZE)) {
            size_t index = (ppages->base - pool->base) / PAGE_SIZE;
            bitmap_clear_consecutive(pool->bitmap, index, ppages->num_pages);
        }
        spin_unlock(&pool->lock);
    }
}

static void mem_msg_handler(uint32_t event, uint64_t data)
{
    mem_handle_broadcast_region(event, data);
}
CPU_MSG_HANDLER(mem_msg_handler, MEM_PROT_SYNC)

static cpumap_t mem_section_shared_cpus(struct addr_space* as, as_sec_t section)
{
    cpumap_t cpus = 0;
    if (as->type == AS_HYP) {
        if ((section == SEC_HYP_GLOBAL) || (section == SEC_HYP_IMAGE)) {
            cpus = BIT_MASK(0, PLAT_CPU_NUM);
        } else if (section == SEC_HYP_VM) {
            /**
             * If we don't have a valid vcpu at this point, it means we are creating this region
             * before even having a vm. Therefore, the sharing of the region must be guaranteed by
             * other means (e.g. vmm_vm_install)
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

static void mem_region_broadcast(struct addr_space* as, struct mp_region* mpr, uint32_t op,
    bool locked)
{
    cpumap_t shared_cpus = mem_section_shared_cpus(as, mpr->as_sec);

    if (shared_cpus == 0) {
        return;
    }

    struct shared_region shared_region = {
        .as_type = as->type,
        .asid = as->id,
        .region = *mpr,
        .lock = locked,
    };

    for (cpuid_t cpuid = 0; cpuid < PLAT_CPU_NUM; cpuid++) {
        if ((cpu()->id != cpuid) && bit_get(shared_cpus, cpuid)) {
            struct shared_region* node = objpool_alloc(&shared_region_pool);
            if (node == NULL) {
                ERROR("Failed allocating shared region node");
            }
            *node = shared_region;
            struct cpu_msg msg = { (uint32_t)MEM_PROT_SYNC, op, (uintptr_t)node };
            cpu_send_msg(cpuid, &msg);
        }
    }
}

static bool mem_broadcast(struct addr_space* as, struct mp_region* mpr, bool broadcast)
{
    if (as->type == AS_HYP && mpr->as_sec == SEC_HYP_PRIVATE) {
        return false;
    }

    return broadcast;
}

static bool mem_check_forced_locked(struct mp_region* mpr, bool locked)
{
    if (mpr->as_sec == SEC_HYP_PRIVATE || mpr->as_sec == SEC_HYP_VM ||
        mpr->as_sec == SEC_HYP_IMAGE) {
        return true;
    }

    return locked;
}

static bool mem_vmpu_insert_region(struct addr_space* as, mpid_t mpid, struct mp_region* mpr,
    bool broadcast, bool locked)
{
    bool lock = mem_check_forced_locked(mpr, locked);
    if (mpid == INVALID_MPID) {
        return false;
    }

    if (mpu_map(as, mpr, lock)) {
        mem_vmpu_set_entry(as, mpid, mpr, lock);
        if (mem_broadcast(as, mpr, broadcast)) {
            mem_region_broadcast(as, mpr, MEM_INSERT_REGION, lock);
        }
        return true;
    }

    return false;
}

static bool mem_vmpu_update_region(struct addr_space* as, mpid_t mpid, struct mp_region merge_reg,
    bool broadcast, bool locked)
{
    bool merged = false;

    if (mpu_update(as, &merge_reg)) {
        struct mpe* mpe = mem_vmpu_get_entry(as, mpid);
        mpe->region = merge_reg;
        if (mem_broadcast(as, &mpe->region, broadcast)) {
            mem_region_broadcast(as, &mpe->region, MEM_UPDATE_REGION, locked);
        }
        merged = true;
    }
    return merged;
}

static bool mem_vmpu_remove_region(struct addr_space* as, mpid_t mpid, bool broadcast)
{
    bool removed = false;

    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    if ((mpe != NULL) && (mpe->state == MPE_S_VALID)) {
        bool lock = mpe->lock;
        if (mem_broadcast(as, &mpe->region, broadcast)) {
            mem_region_broadcast(as, &mpe->region, MEM_REMOVE_REGION, lock);
        }
        mpu_unmap(as, &mpe->region);
        mem_vmpu_free_entry(as, mpid);
        removed = true;
    }

    return removed;
}

static void mem_handle_broadcast_insert(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    if (as->type == AS_HYP) {
        mem_map(&cpu()->as, mpr, MEM_DONT_BROADCAST, locked);
    } else {
        mpu_map(as, mpr, locked);
    }
}

static void mem_handle_broadcast_remove(struct addr_space* as, struct mp_region* mpr)
{
    if (as->type == AS_HYP) {
        /*
            We don't use mpu_unmap because that API forces a broadcast.
            During the handle of a broadcast we don't want that, to avoid
            a chain of broadcasts
        */
        mem_unmap_range(&cpu()->as, mpr->base, mpr->size, MEM_DONT_BROADCAST);
    } else {
        mpu_unmap(as, mpr);
    }
}

static bool mem_update(struct addr_space* as, struct mp_region* mpr, bool broadcast, bool locked)
{
    mpid_t update_mpid = INVALID_MPID;
    list_foreach (as->vmpu.ordered_list, struct mpe, cur) {
        if (cur->region.base == mpr->base && cur->region.size != mpr->size) {
            update_mpid = cur->mpid;
            break;
        }
    }
    if (update_mpid != INVALID_MPID) {
        return mem_vmpu_update_region(as, update_mpid, *mpr, broadcast, locked);
    }
    return false;
}

static void mem_handle_broadcast_update(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    if (as->type == AS_HYP) {
        mem_update(&cpu()->as, mpr, MEM_DONT_BROADCAST, locked);
    } else {
        mpu_update(as, mpr);
    }
}

void mem_handle_broadcast_region(uint32_t event, uint64_t data)
{
    struct shared_region* sh_reg = (struct shared_region*)(uintptr_t)data;

    if (sh_reg != NULL) {
        struct addr_space* as;
        if (sh_reg->as_type == AS_HYP) {
            as = &cpu()->as;
        } else {
            struct addr_space* vm_as = &cpu()->vcpu->vm->as;
            if (vm_as->id != sh_reg->asid) {
                ERROR("Received shared region for unknown vm address space.");
            }
            as = vm_as;
        }

        switch (event) {
            case MEM_INSERT_REGION:
                mem_handle_broadcast_insert(as, &sh_reg->region, sh_reg->lock);
                break;
            case MEM_REMOVE_REGION:
                mem_handle_broadcast_remove(as, &sh_reg->region);
                break;
            case MEM_UPDATE_REGION:
                mem_handle_broadcast_update(as, &sh_reg->region, sh_reg->lock);
                break;
            default:
                ERROR("unknown mem broadcast msg");
        }

        objpool_free(&shared_region_pool, sh_reg);
    }
}

static mpid_t mem_vmpu_find_overlapping_region(struct addr_space* as, struct mp_region* region)
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

static void mem_vmpu_coalesce_contiguous(struct addr_space* as, bool broadcast)
{
    while (true) {
        bool merge = false;
        mpid_t cur_mpid = INVALID_MPID;
        mpid_t prev_mpid = INVALID_MPID;
        struct mpe* prev_reg;
        struct mpe* cur_reg;
        list_foreach_tail(as->vmpu.ordered_list, struct mpe, cur, prev)
        {
            if (prev == NULL) {
                continue;
            }
            cur_reg = mem_vmpu_get_entry(as, cur->mpid);
            prev_reg = mem_vmpu_get_entry(as, prev->mpid);

            bool contiguous = prev_reg->region.base + prev_reg->region.size == cur_reg->region.base;
            bool perms_compatible =
                mpu_perms_compatible(prev_reg->region.mem_flags.raw, cur_reg->region.mem_flags.raw);
            bool lock_compatible = !prev_reg->lock && !cur_reg->lock;
            if (contiguous && perms_compatible && lock_compatible) {
                cur_mpid = cur->mpid;
                prev_mpid = prev->mpid;
                merge = true;
                break;
            }
        }

        if (merge) {
            struct mp_region merged_reg = {
                .base = prev_reg->region.base,
                .size = prev_reg->region.size + cur_reg->region.size,
                .mem_flags = cur_reg->region.mem_flags,
            };
            if (mem_vmpu_update_region(as, prev_mpid, merged_reg, broadcast, prev_reg->lock)) {
                mem_vmpu_remove_region(as, cur_mpid, broadcast);
            }
        } else {
            break;
        }
    }
}

bool mem_map(struct addr_space* as, struct mp_region* mpr, bool broadcast, bool locked)
{
    bool mapped = false;
    mpid_t mpid = INVALID_MPID;

    if (mpr->size == 0) {
        return true;
    }

    if ((mpr->size % mpu_granularity()) != 0) {
        ERROR("trying to set mpu region which is not a multiple of "
              "granularity");
    }

    spin_lock(&as->lock);

    if (mem_vmpu_find_overlapping_region(as, mpr) == INVALID_MPID) {
        mpid = mem_vmpu_allocate_entry(as);
        if (mpid != INVALID_MPID) {
            mapped = mem_vmpu_insert_region(as, mpid, mpr, broadcast, locked);
        } else {
            mem_vmpu_deallocate_entry(as, mpid);
        }
    }

    if (mapped && !locked) {
        mem_vmpu_coalesce_contiguous(as, broadcast);
    }

    spin_unlock(&as->lock);

    return mapped;
}

bool mem_unmap_range(struct addr_space* as, vaddr_t vaddr, size_t size, bool broadcast)
{
    spin_lock(&as->lock);

    size_t size_left = size;

    while (size_left > 0) {
        struct mp_region reg;
        reg.base = vaddr;
        reg.size = size;

        mpid_t mpid = mem_vmpu_find_overlapping_region(as, &reg);
        if (mpid == INVALID_MPID) {
            /**
             * FIXME: right now we are ignoring the fact that the range  or parts of it might not
             * be mapped. This is in line to what the MMU mem_unmap function does. We should change
             * this to only go ahead with the unpamming if the full range is indeed mapped.
             */
            break;
        }
        struct mpe* mpe = mem_vmpu_get_entry(as, mpid);
        reg = mpe->region;

        bool locked = mpe->lock;

        vaddr_t limit = vaddr + size;
        vaddr_t r_limit = reg.base + reg.size;
        vaddr_t r_base = reg.base;

        size_t top_size = limit >= r_limit ? 0 : r_limit - limit;
        size_t bottom_size = vaddr <= r_base ? 0 : vaddr - r_base;

        mem_vmpu_remove_region(as, mpid, broadcast);

        if (top_size > 0) {
            struct mp_region top = reg;
            top.base = limit;
            top.size = top_size;
            mpid_t top_mpid = mem_vmpu_allocate_entry(as);
            if (!mem_vmpu_insert_region(as, top_mpid, &top, broadcast, locked)) {
                return false;
            }
        }

        if (bottom_size > 0) {
            struct mp_region bottom = reg;
            bottom.size = bottom_size;
            mpid_t bottom_mpid = mem_vmpu_allocate_entry(as);
            if (!mem_vmpu_insert_region(as, bottom_mpid, &bottom, broadcast, locked)) {
                return false;
            }
        }

        size_t overlap_size = reg.size - top_size - bottom_size;
        size_left -= overlap_size;
    }

    spin_unlock(&as->lock);

    return size_left == 0;
}

void mem_unmap(struct addr_space* as, vaddr_t at, size_t num_pages, bool free_ppages)
{
    if (mem_unmap_range(as, at, num_pages * PAGE_SIZE, MEM_BROADCAST) && free_ppages) {
        struct ppages ppages = mem_ppages_get(at, num_pages);
        mem_free_ppages(&ppages);
    }
}

vaddr_t mem_map_cpy(struct addr_space* ass, struct addr_space* asd, vaddr_t vas, vaddr_t vad,
    size_t num_pages)
{
    UNUSED_ARG(num_pages);

    struct mpe* mpe;
    struct mp_region mpr;
    vaddr_t va_res = INVALID_VA;

    if ((ass != asd) && (vad == INVALID_VA || vad == vas)) {
        // In mpu-based systems, we can only copy mappings between address spaces, as copying a
        // mapping in a single address space would overlap the orignal mapping. Also because only
        // identify mappings are supported, the source va must equal the destination va, or be an
        // invalid va. This still covers the most useful uses cases.

        spin_lock(&ass->lock);
        mpid_t reg_num_src = mem_vmpu_get_entry_by_addr(ass, vas);
        mpe = mem_vmpu_get_entry(ass, reg_num_src);
        mpr = mpe->region;
        spin_unlock(&ass->lock);

        if (num_pages * PAGE_SIZE > mpr.size) {
            va_res = INVALID_VA;
        } else {
            mpr.size = num_pages * PAGE_SIZE;
            bool broadcast = mem_broadcast(asd, &mpr, MEM_BROADCAST);
            if (mem_map(asd, &mpr, broadcast, MEM_NOT_LOCKED)) {
                va_res = vas;
            } else {
                INFO("failed mem map on mem map cpy");
            }
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

vaddr_t mem_alloc_map(struct addr_space* as, as_sec_t section, struct ppages* ppages, vaddr_t at,
    size_t num_pages, mem_flags_t flags)
{
    // TODO: Check if page->base, page->size and vaddr_t at are page_size align?

    struct ppages temp_ppages;

    if (at == INVALID_VA && ppages == NULL) {
        ERROR("Can't map an MPU region because neither the virtual"
              "or phsyical address was specified.");
    }

    if (at != INVALID_VA && ppages != NULL && at != ppages->base) {
        ERROR("Trying to map non identity");
    }

    if (at == INVALID_VA) {
        at = ppages->base;
    } else if (ppages == NULL) {
        temp_ppages = mem_ppages_get(at, num_pages);
        ppages = &temp_ppages;
    }

    struct mp_region mpr = (struct mp_region){
        .base = ppages->base,
        .size = (num_pages * PAGE_SIZE),
        .as_sec = section,
        .mem_flags = flags,
    };

    mem_map(as, &mpr, MEM_BROADCAST, MEM_NOT_LOCKED);

    return at;
}

vaddr_t mem_alloc_map_dev(struct addr_space* as, as_sec_t section, vaddr_t at, paddr_t pa,
    size_t num_pages)
{
    struct ppages temp_page = mem_ppages_get(pa, num_pages);
    return mem_alloc_map(as, section, &temp_page, at, num_pages,
        as->type == AS_HYP ? PTE_HYP_DEV_FLAGS : PTE_VM_DEV_FLAGS);
}
