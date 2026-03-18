/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file shmem.c
 * @brief This source file contains the API implementation for allocating, initializing and finding
 * shared memory regions.
 * 
 */

#include <shmem.h>
#include <config.h>

static size_t shmem_table_size;
static struct shmem* shmem_table;

/**
 * @brief Allocate physical memory for shared memory regions
 * Initialize each shared memory region in the global table.
 * For regions that aren't physically placed, allocates physical pages according
 * to the region's size and color requirements.
 * @see mem_alloc_ppages(), NUM_PAGES(), ERROR(), SPINLOCK_INITVAL, shmem, ppages
 *      MEM_ALIGN_NOT_REQ, colormap_t, ppages
 */
static void shmem_alloc(void)
{
    for (size_t i = 0; i < shmem_table_size; i++) {
        struct shmem* shmem = &shmem_table[i];
        if (!shmem->place_phys) {
            size_t n_pg = NUM_PAGES(shmem->size);
            struct ppages ppages = mem_alloc_ppages(shmem->colors, n_pg, MEM_ALIGN_NOT_REQ);
            if (ppages.num_pages < n_pg) {
                ERROR("failed to allocate shared memory");
            }
            shmem->phys = ppages.base;
        }
    }
}

/**
 * @brief Get a shared memory region by its ID
 * @param shmem_id ID of the shared memory region to retrieve
 * @return struct shmem* Pointer to the shared memory region, or NULL if invalid ID
 * @see shmem_table, shmem
 */
struct shmem* shmem_get(size_t shmem_id)
{
    if (shmem_id < shmem_table_size) {
        return &shmem_table[shmem_id];
    } else {
        return NULL;
    }
}

/**
 * @brief Initialize the shared memory subsystem
 * On the master CPU, initialize the global shared memory table from
 * configuration and allocates physical memory for each region.
 * Also initialize the CPU masters bitmap for each region.
 * @see cpu_is_master(), config, shmem, shmem_alloc(), cpumap_t, SPINLOCK_INITVAL
 */
void shmem_init()
{
    if (cpu_is_master()) {
        shmem_table_size = config.shmemlist_size;
        shmem_table = config.shmemlist;

        for (size_t i = 0; i < config.shmemlist_size; i++) {
            shmem_table[i].lock = SPINLOCK_INITVAL;
            shmem_table[i].cpu_masters = 0;
        }

        shmem_alloc();
    }
}
