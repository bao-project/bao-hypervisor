/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __MEM_PROT_H__
#define __MEM_PROT_H__

#include <bao.h>
#include <bitmap.h>
#include <list.h>
#include <arch/mem.h>
#include <arch/spinlock.h>

#define HYP_ASID         0
#define VMPU_NUM_ENTRIES 64

struct mp_region {
    vaddr_t base;
    size_t size;
    mem_flags_t mem_flags;
    as_sec_t as_sec;
};

struct addr_space {
    asid_t id;
    enum AS_TYPE type;
    cpumap_t cpus;
    colormap_t colors;
    struct {
        struct list ordered_list;
        struct mpe {
            node_t node;
            enum { MPE_S_FREE, MPE_S_INVALID, MPE_S_VALID } state;
            bool lock;
            struct mp_region region;
            mpid_t mpid;
        } node[VMPU_NUM_ENTRIES];
    } vmpu;
    spinlock_t lock;
};

void as_init(struct addr_space* as, enum AS_TYPE type, asid_t id, cpumap_t cpus, colormap_t colors);

static inline bool mem_regions_overlap(struct mp_region* reg1, struct mp_region* reg2)
{
    return range_in_range(reg1->base, reg1->size, reg2->base, reg2->size);
}

bool mem_map(struct addr_space* as, struct mp_region* mpr, bool broadcast, bool locked);

/**
 * This functions must be defined for the physical MPU. The abstraction provided by the physical
 * MPU layer is minimal. Besides initialization:
 * i) It must provide the view of a separate physical MPU for each privilege;
 * ii) It must allow the mapping and unmapping of regions on these MPUs,returning a binary return
 * success value.
 */
void mpu_init(void);
void mpu_enable(void);
bool mpu_map(struct addr_space* as, struct mp_region* mem, bool locked);
bool mpu_unmap(struct addr_space* as, struct mp_region* mem);

void mem_vmpu_coalesce_contiguous(struct addr_space* as, bool broadcast, bool locked);
bool mem_update(struct addr_space* as, struct mp_region* mpr, bool broadcast, bool locked);
bool mpu_update(struct addr_space* as, struct mp_region* mpr);

#endif /* __MEM_PROT_H__ */
