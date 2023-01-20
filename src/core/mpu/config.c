/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <config.h>

void config_mem_prot_init(paddr_t load_addr) {

    for (size_t i = 0; i < config.vmlist_size; i++){

        for (size_t j = 0; j < config.vmlist[i].platform.region_num; j++) {
            /**
             * On MPU systems all VM regions must be physical regions with 
             * 1-to-1 mapping.
             */
            config.vmlist[i].platform.regions[j].place_phys = true;
            vaddr_t region_base = config.vmlist[i].platform.regions[j].base;
            config.vmlist[i].platform.regions[j].phys = region_base;
        }

        for (size_t j = 0; j < config.vmlist[i].platform.ipc_num; j++) {
            /**
             * In MPU-based systems, the address of the VM's IPC object and
             * the used must follow a 1-1 mapping.
             */
            size_t shmem_id = config.vmlist[i].platform.ipcs[j].shmem_id;
            vaddr_t ipc_base_addr = config.vmlist[i].platform.ipcs[j].base;
            vaddr_t shmem_base_addr = config.shmemlist[shmem_id].base;
            if (ipc_base_addr != shmem_base_addr) {
                ERROR("IPC base addr must be the same as its shmem base addr.");
            }
        }

    }

    for (size_t i = 0; i < config.shmemlist_size; i++){
        /**
         * On MPU systems all shared memory regions must be physical
         * regions with 1-to-1 mapping.
         */
        config.shmemlist[i].place_phys = true;
    }

}
