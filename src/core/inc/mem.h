/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __MEM_H__
#define __MEM_H__

#include <bao.h>
#include <mem_prot/mem.h>
#include <list.h>
#include <spinlock.h>
#include <cache.h>
#include <bitmap.h>

#ifndef __ASSEMBLER__

struct ppages {
    paddr_t base;
    size_t num_pages;
    colormap_t colors;
};

struct page_pool {
    node_t node;
    paddr_t base;
    size_t size;
    size_t free;
    size_t last;
    bitmap_t* bitmap;
    spinlock_t lock;
};

struct mem_region {
    paddr_t base;
    size_t size;
    struct page_pool page_pool;
};

struct shmem {
    size_t size;
    colormap_t colors;
    bool place_phys;
    union {
        paddr_t base;
        paddr_t phys;
    };
    cpumap_t cpu_masters;
    spinlock_t lock;
};

static inline struct ppages mem_ppages_get(paddr_t base, size_t num_pages)
{
    return (struct ppages){.colors = 0, .base = base, .num_pages = num_pages};
}

static inline bool all_clrs(colormap_t clrs)
{
    colormap_t mask = (((colormap_t)1) << COLOR_NUM) - 1;
    colormap_t masked_colors = clrs & mask;
    return (masked_colors == 0) || (masked_colors == mask);
}

void mem_init(paddr_t load_addr);
void* mem_alloc_page(size_t num_pages, enum AS_SEC sec, bool phys_aligned);
struct ppages mem_alloc_ppages(colormap_t colors, size_t num_pages, bool aligned);
vaddr_t mem_alloc_map(struct addr_space* as, enum AS_SEC section, struct ppages *page, 
                        vaddr_t at, size_t num_pages, mem_flags_t flags);
vaddr_t mem_alloc_map_dev(struct addr_space* as, enum AS_SEC section,
                            vaddr_t at, paddr_t pa, size_t size);
void mem_unmap(struct addr_space* as, vaddr_t at, size_t num_pages,
                    bool free_ppages);
bool mem_map_reclr(struct addr_space* as, vaddr_t va, struct ppages* ppages,
                size_t num_pages, mem_flags_t flags);
vaddr_t mem_map_cpy(struct addr_space *ass, struct addr_space *asd, vaddr_t vas,
                vaddr_t vad, size_t num_pages);
bool pp_alloc(struct page_pool *pool, size_t num_pages, bool aligned,
                     struct ppages *ppages);

void mem_prot_init();
size_t mem_cpu_boot_alloc_size();

/* Functions implemented in architecture dependent files */

void as_arch_init(struct addr_space* as);
bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa);

extern struct list page_pool_list;

#endif /* |__ASSEMBLER__ */

#endif /* __MEM_H__ */
