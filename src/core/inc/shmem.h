/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef SHMEM_H
#define SHMEM_H

#include <mem.h>

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

void shmem_init(void);
struct shmem* shmem_get(size_t shmem_id);

#endif /* SHMEM_H */
