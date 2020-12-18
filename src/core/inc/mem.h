/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __MEM_H__
#define __MEM_H__

#include <bao.h>
#include <arch/mem.h>
#include <page_table.h>
#include <list.h>
#include <spinlock.h>
#include <cache.h>

#ifndef __ASSEMBLER__

enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY };
enum AS_SEC {
    /*--- VM AS SECTIONS -----*/
    SEC_HYP_GLOBAL = 0,
    SEC_HYP_IMAGE,
    SEC_HYP_DEVICE,
    SEC_HYP_PRIVATE,
    SEC_HYP_VM,
    SEC_HYP_ANY, /* must be last */
    /*--- VM AS SECTIONS -----*/
    SEC_VM_ANY = 0, /* must be last */
};

typedef struct {
    page_table_t pt;
    enum AS_TYPE type;
    uint64_t colors;
    uint64_t id;
    spinlock_t lock;
} addr_space_t;

typedef struct {
    uint64_t base;
    size_t size;
    uint64_t colors;
} ppages_t;

struct mem_region {
    uint64_t base;
    size_t size;
    uint64_t colors;
    bool place_phys;
    uint64_t phys;
};

struct dev_region {
    uint64_t pa;
    uint64_t va;
    size_t size;
    size_t interrupt_num;
    uint64_t *interrupts;
    uint32_t id; /* bus master id for iommu effects */
};

typedef struct shmem {
    uint64_t size;
    uint64_t colors;
    bool place_phys;
    uint64_t phys;
    uint64_t cpu_masters;
} shmem_t;

static inline ppages_t mem_ppages_get(uint64_t base, uint64_t size)
{
    return (ppages_t){.colors = 0, .base = base, .size = size};
}

static inline bool all_clrs(uint64_t clrs)
{
    return (clrs == 0) ||
           ((clrs & ((1ULL << COLOR_NUM) - 1)) == ((1ULL << COLOR_NUM) - 1));
}

void mem_init(uint64_t load_addr, uint64_t config_addr);
void as_init(addr_space_t* as, enum AS_TYPE type, uint64_t id, void* root_pt,
             uint64_t colors);
void* mem_alloc_page(size_t n, enum AS_SEC sec, bool phys_aligned);
ppages_t mem_alloc_ppages(uint64_t colors, size_t n, bool aligned);
void* mem_alloc_vpage(addr_space_t* as, enum AS_SEC section, void* at,
                      size_t n);
void mem_free_vpage(addr_space_t* as, void* at, size_t n, bool free_ppages);
int mem_map(addr_space_t* as, void* va, ppages_t* ppages, size_t n,
            uint64_t flags);
int mem_map_reclr(addr_space_t* as, void* va, ppages_t* ppages, size_t n,
                  uint64_t flags);
int mem_map_dev(addr_space_t* as, void* va, uint64_t base, size_t n);

/* Functions implemented in architecture dependent files */

void as_arch_init(addr_space_t* as);
bool mem_translate(addr_space_t* as, void* va, uint64_t* pa);

#endif /* |__ASSEMBLER__ */

#endif /* __MEM_H__ */
