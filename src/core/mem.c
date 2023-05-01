/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <mem.h>

#include <cpu.h>
#include <platform.h>
#include <cache.h>
#include <string.h>
#include <vm.h>
#include <fences.h>
#include <config.h>

extern uint8_t _image_start, _image_load_end, _image_end, _vm_image_start, 
    _vm_image_end;

struct list page_pool_list;

bool pp_alloc(struct page_pool *pool, size_t num_pages, bool aligned,
                     struct ppages *ppages)
{
    ppages->colors = 0;
    ppages->num_pages = 0;

    bool ok = false;

    if (num_pages == 0) return true;

    spin_lock(&pool->lock);

    /**
     *  If we need a contigous segment aligned to its size, lets start
     * at an already aligned index.
     */
    size_t start = aligned ? pool->base / PAGE_SIZE % num_pages : 0;
    size_t curr = pool->last + ((pool->last + start) % num_pages);

    /**
     * Lets make two searches:
     *  - one starting from the last known free index.
     *  - in case this does not work, start from index 0.
     */
    for (size_t i = 0; i < 2 && !ok; i++) {
        while (pool->free != 0) {
            ssize_t bit =
                bitmap_find_consec(pool->bitmap, pool->size, curr, num_pages, false);

            if (bit < 0) {
                /**
                 * No num_page page sement was found. If this is the first 
                 * iteration set position to 0 to start next search from index 0.
                 */
                size_t next_aligned = 
                    (num_pages - ((pool->base / PAGE_SIZE) % num_pages)) % num_pages;
                curr = aligned ? next_aligned : 0;
                break;
            } else if (aligned && (((bit + start) % num_pages) != 0)) {
                /**
                 *  If we're looking for an aligned segment and the found
                 * contigous segment is not aligned, start the search again
                 * from the last aligned index
                 */
                curr = bit + ((bit + start) % num_pages);
            } else {
                /**
                 * We've found our pages. Fill output argument info, mark
                 * them as allocated, and update page pool bookkeeping.
                 */
                ppages->base = pool->base + (bit * PAGE_SIZE);
                ppages->num_pages = num_pages;
                bitmap_set_consecutive(pool->bitmap, bit, num_pages);
                pool->free -= num_pages;
                pool->last = bit + num_pages;
                ok = true;
                break;
            }
        }
    }
    spin_unlock(&pool->lock);

    return ok;
}

bool mem_are_ppages_reserved_in_pool(struct page_pool *ppool, struct ppages *ppages)
{
    bool reserved = false;
    bool rgn_found = range_in_range(ppages->base, ppages->num_pages * PAGE_SIZE,
                                    ppool->base, ppool->size * PAGE_SIZE);
    if (rgn_found) {
        size_t pageoff = NUM_PAGES(ppages->base - ppool->base);

        // verify these pages arent allocated yet
        bool is_alloced = bitmap_get(ppool->bitmap, pageoff);
        size_t avlbl_contig_pp = bitmap_count_consecutive(
            ppool->bitmap, ppool->size, pageoff, ppages->num_pages);

        if (is_alloced || avlbl_contig_pp < ppages->num_pages) {
            reserved = true;
        }
    }

    return reserved;
}

bool mem_are_ppages_reserved(struct ppages *ppages)
{
    bool reserved = false;
    list_foreach(page_pool_list, struct page_pool, pool)
    {
        bool is_in_rgn = range_in_range(ppages->base, ppages->num_pages * PAGE_SIZE,
                                        pool->base, pool->size * PAGE_SIZE);

        if (is_in_rgn) {
            reserved = mem_are_ppages_reserved_in_pool(pool, ppages);
            break;
        }
    }

    return reserved;
}

bool mem_reserve_ppool_ppages(struct page_pool *pool, struct ppages *ppages)
{
    bool is_in_rgn = range_in_range(ppages->base, ppages->num_pages * PAGE_SIZE,
                                    pool->base, pool->size * PAGE_SIZE);
    if (!is_in_rgn) return true;

    size_t pageoff = NUM_PAGES(ppages->base - pool->base);

    bool was_free = true;
    if (mem_are_ppages_reserved_in_pool(pool, ppages)) {
        was_free = false;
    }

    bitmap_set_consecutive(pool->bitmap, pageoff, ppages->num_pages);
    pool->free -= ppages->num_pages;

    return is_in_rgn && was_free;
}

void *mem_alloc_page(size_t num_pages, enum AS_SEC sec, bool phys_aligned)
{
    vaddr_t vpage = INVALID_VA;
    struct ppages ppages = mem_alloc_ppages(cpu()->as.colors, num_pages, phys_aligned);

    if (ppages.num_pages == num_pages) {
        vpage = mem_alloc_map(&cpu()->as, sec, &ppages, INVALID_VA, num_pages, PTE_HYP_FLAGS);
    }

    return (void*)vpage;
}

bool root_pool_set_up_bitmap(paddr_t load_addr, struct page_pool *root_pool)
{
    size_t image_size = (size_t)(&_image_end - &_image_start);
    size_t vm_image_size = (size_t)(&_vm_image_end - &_vm_image_start);
    size_t cpu_size = platform.cpu_num * mem_cpu_boot_alloc_size();

    size_t bitmap_num_pages = root_pool->size / (8 * PAGE_SIZE) +
                           ((root_pool->size % (8 * PAGE_SIZE) != 0) ? 1 : 0);
    if (root_pool->size <= bitmap_num_pages) return false;
    size_t bitmap_base = load_addr + image_size + vm_image_size + cpu_size;

    struct ppages bitmap_pp = mem_ppages_get(bitmap_base, bitmap_num_pages);
    bitmap_t* root_bitmap = (bitmap_t*) 
        mem_alloc_map(&cpu()->as, SEC_HYP_GLOBAL, &bitmap_pp, INVALID_VA, bitmap_num_pages, PTE_HYP_FLAGS);
    root_pool->bitmap = root_bitmap;
    memset((void*)root_pool->bitmap, 0, bitmap_num_pages * PAGE_SIZE);

    return mem_reserve_ppool_ppages(root_pool, &bitmap_pp);
}

bool pp_root_reserve_hyp_mem(paddr_t load_addr, struct page_pool *root_pool)
{
    size_t image_load_size = (size_t)(&_image_load_end - &_image_start);
    size_t image_noload_size = (size_t)(&_image_end - &_image_load_end);
    size_t vm_image_size = (size_t)(&_vm_image_end - &_vm_image_start);
    size_t cpu_size = platform.cpu_num * mem_cpu_boot_alloc_size();
    paddr_t image_noload_addr = load_addr + image_load_size + vm_image_size;
    paddr_t cpu_base_addr = image_noload_addr + image_noload_size;

    struct ppages images_load_ppages =
        mem_ppages_get(load_addr, NUM_PAGES(image_load_size));
    struct ppages images_noload_ppages =
        mem_ppages_get(image_noload_addr, NUM_PAGES(image_noload_size));
    struct ppages cpu_ppages =
        mem_ppages_get(cpu_base_addr, NUM_PAGES(cpu_size));

    bool image_load_reserved =
        mem_reserve_ppool_ppages(root_pool, &images_load_ppages);
    bool image_noload_reserved =
        mem_reserve_ppool_ppages(root_pool, &images_noload_ppages);
    bool cpu_reserved = mem_reserve_ppool_ppages(root_pool, &cpu_ppages);

    return image_load_reserved && image_noload_reserved && cpu_reserved;
}

static bool pp_root_init(paddr_t load_addr, struct mem_region *root_region)
{
    struct page_pool *root_pool = &root_region->page_pool;
    root_pool->base = ALIGN(root_region->base, PAGE_SIZE);
    root_pool->size =
        root_region->size / PAGE_SIZE; /* TODO: what if not aligned? */
    root_pool->free = root_pool->size;

    if (!root_pool_set_up_bitmap(load_addr, root_pool)) {
        return false;
    }
    if (!pp_root_reserve_hyp_mem(load_addr, root_pool)) {
        return false;
    }

    root_pool->last = 0;
    return true;
}

static void pp_init(struct page_pool *pool, paddr_t base, size_t size)
{
    struct ppages pages;

    if (pool == NULL) return;

    memset((void*)pool, 0, sizeof(struct page_pool));
    pool->base = ALIGN(base, PAGE_SIZE);
    pool->size = NUM_PAGES(size);
    size_t bitmap_size =
        pool->size / (8 * PAGE_SIZE) + !!(pool->size % (8 * PAGE_SIZE) != 0);

    if (size <= bitmap_size) return;

    pages = mem_alloc_ppages(cpu()->as.colors, bitmap_size, false);
    if (pages.num_pages != bitmap_size) return;

    if ((pool->bitmap = (bitmap_t*)mem_alloc_map(&cpu()->as, SEC_HYP_GLOBAL, &pages, 
                                    INVALID_VA, bitmap_size, PTE_HYP_FLAGS)) == NULL)
        return;

    memset((void*)pool->bitmap, 0, bitmap_size * PAGE_SIZE);

    pool->last = 0;
    pool->free = pool->size;
}

bool mem_vm_img_in_phys_rgn(struct vm_config* vm_config) {

    bool img_in_rgn = false;

    for (size_t i = 0; i < vm_config->platform.region_num; i++) {
        if (vm_config->platform.regions[i].place_phys) {
            vaddr_t rgn_base = vm_config->platform.regions[i].phys;
            size_t rgn_size = vm_config->platform.regions[i].size;
            paddr_t img_base = vm_config->image.load_addr;
            size_t img_size = vm_config->image.size;
            if (range_in_range(img_base, img_size, rgn_base, rgn_size)) {
                img_in_rgn = true;
                break;
            }
        }
    }

    return img_in_rgn;
}

bool mem_reserve_physical_memory(struct page_pool *pool)
{
    if (pool == NULL) return false;

    for (size_t i = 0; i < config.vmlist_size; i++) {
        struct vm_config *vm_cfg = &config.vmlist[i];
        size_t n_pg = NUM_PAGES(vm_cfg->image.size);
        struct ppages ppages = mem_ppages_get(vm_cfg->image.load_addr, n_pg);

        // If the vm image is part of a statically allocated region of the same
        // vm, we defer the reservation of this memory to when we reserve the
        // physical region below. Note that this not allow partial overlaps. If the
        // image must be entirely inside a statically allocated region, or
        // completely outside of it. This avoid overcamplicating the reservation
        // logic while still covering all the useful use cases.
        if (mem_vm_img_in_phys_rgn(vm_cfg)) {
            continue;
        }

        if (!mem_reserve_ppool_ppages(pool, &ppages)) {
            return false;
        }
    }

    /* for every vm config */
    for (size_t i = 0; i < config.vmlist_size; i++) {
        struct vm_config *vm_cfg = &config.vmlist[i];
        /* for every mem region */
        for (size_t j = 0; j < vm_cfg->platform.region_num; j++) {
            struct vm_mem_region *reg = &vm_cfg->platform.regions[j];
            if (reg->place_phys) {
                size_t n_pg = NUM_PAGES(reg->size);
                struct ppages ppages = mem_ppages_get(reg->phys, n_pg);
                if (!mem_reserve_ppool_ppages(pool, &ppages)) {
                    return false;
                }
            }
        }
    }

    for (size_t i = 0; i < config.shmemlist_size; i++) {
        struct shmem *shmem = &config.shmemlist[i];
        if(shmem->place_phys) {
            size_t n_pg = NUM_PAGES(shmem->size);
            struct ppages ppages = mem_ppages_get(shmem->phys, n_pg);
            if (!mem_reserve_ppool_ppages(pool, &ppages)) {
                return false;
            }           
            shmem->phys = ppages.base;
        }
    }

    return true;
}

bool mem_create_ppools(struct mem_region *root_mem_region)
{
    for (size_t i = 0; i < platform.region_num; i++) {
        if (&platform.regions[i] != root_mem_region) {
            struct mem_region *reg = &platform.regions[i];
            struct page_pool *pool = &reg->page_pool;
            if (pool != NULL) {
                pp_init(pool, reg->base, reg->size);
                if (!mem_reserve_physical_memory(pool)) {
                    return false;
                }
                list_push(&page_pool_list, &pool->node);
            }
        }
    }

    return true;
}

struct mem_region *mem_find_root_region(paddr_t load_addr)
{
    size_t image_size = (size_t)(&_image_end - &_image_start);

    /* Find the root memory region in which the hypervisor was loaded. */
    struct mem_region *root_mem_region = NULL;
    for (size_t i = 0; i < platform.region_num; i++) {
        struct mem_region *region = &(platform.regions[i]);
        bool is_in_rgn =
            range_in_range(load_addr, image_size, region->base, region->size);
        if (is_in_rgn) {
            root_mem_region = region;
            break;
        }
    }

    return root_mem_region;
}

bool mem_setup_root_pool(paddr_t load_addr,
                         struct mem_region **root_mem_region)
{
    *root_mem_region = mem_find_root_region(load_addr);
    if (*root_mem_region == NULL) {
        return false;
    }

    return pp_root_init(load_addr, *root_mem_region);
}

__attribute__((weak))
void mem_color_hypervisor(const paddr_t load_addr, struct mem_region *root_region) 
{
    WARNING("Trying to color hypervisor, but implementation does not suuport it");
}

__attribute__((weak))
bool mem_map_reclr(struct addr_space *as, vaddr_t va, struct ppages *ppages,
                    size_t num_pages, mem_flags_t flags) {
    ERROR("Trying to recolor section but there is no coloring implementation");
}

__attribute__((weak))
bool pp_alloc_clr(struct page_pool *pool, size_t num_pages, colormap_t colors,
                         struct ppages *ppages)
{
    ERROR("Trying to allocate colored pages but there is no coloring implementation");
}

struct ppages mem_alloc_ppages(colormap_t colors, size_t num_pages, bool aligned)
{
    struct ppages pages = {.num_pages = 0};

    list_foreach(page_pool_list, struct page_pool, pool)
    {
        bool ok = (!all_clrs(colors) && !aligned)
                      ? pp_alloc_clr(pool, num_pages, colors, &pages)
                      : pp_alloc(pool, num_pages, aligned, &pages);
        if (ok) break;
    }

    return pages;
}

void mem_init(paddr_t load_addr)
{      
    mem_prot_init();

    static struct mem_region *root_mem_region = NULL;

    if (cpu()->id == CPU_MASTER) {
        cache_enumerate();

        if (!mem_setup_root_pool(load_addr, &root_mem_region)) {
            ERROR("couldn't not initialize root pool");
        }

        /* Insert root pool in pool list */
        list_init(&page_pool_list);
        list_push(&page_pool_list, &(root_mem_region->page_pool.node));

        config_init(load_addr);

        if (!mem_reserve_physical_memory(&root_mem_region->page_pool)) {
            ERROR("failed reserving memory in root pool");
        }
    }

    cpu_sync_and_clear_msgs(&cpu_glb_sync);

    if (!all_clrs(config.hyp.colors)) {
        mem_color_hypervisor(load_addr, root_mem_region);
    }

    if (cpu()->id == CPU_MASTER) {
        if (!mem_create_ppools(root_mem_region)) {
            ERROR("couldn't create additional page pools");
        }
    }

    /* Wait for master core to initialize memory management */
    cpu_sync_and_clear_msgs(&cpu_glb_sync);
}
