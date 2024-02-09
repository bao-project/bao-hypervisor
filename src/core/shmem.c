/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <shmem.h>
#include <config.h>

static size_t shmem_table_size;
static struct shmem* shmem_table;

static void shmem_alloc()
{
    for (size_t i = 0; i < shmem_table_size; i++) {
        struct shmem* shmem = &shmem_table[i];
        if (!shmem->place_phys) {
            size_t n_pg = NUM_PAGES(shmem->size);
            struct ppages ppages = mem_alloc_ppages(shmem->colors, n_pg, false);
            if (ppages.num_pages < n_pg) {
                ERROR("failed to allocate shared memory");
            }
            shmem->phys = ppages.base;
        }
    }
}

struct shmem* shmem_get(size_t shmem_id)
{
    if (shmem_id < shmem_table_size) {
        return &shmem_table[shmem_id];
    } else {
        return NULL;
    }
}

void shmem_init()
{
    if (cpu_is_master()) {
        shmem_table_size = config.shmemlist_size;
        shmem_table = config.shmemlist;
        shmem_alloc();

        for (size_t i = 0; i < config.shmemlist_size; i++) {
            config.shmemlist[i].cpu_masters = 0;
        }
    }
}
