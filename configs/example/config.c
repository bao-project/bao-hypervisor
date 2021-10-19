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


#include <config.h>

/**
 * Declare VM images using the VM_IMAGE macro, passing an identifier and the
 * path for the image.
 */
VM_IMAGE(vm1, "/path/to/vm1/binary.bin");
VM_IMAGE(vm2, "/path/to/vm2/binary.bin");

/**
 * The configuration itself is a struct config that MUST be named config.
 */
struct config config = {
    
    /**
     * This macro must be always placed in the config struct, to initialize,
     * configuration independent fields.
     */
    CONFIG_HEADER

    /**
     * This defines an array of shared memory objects that may be associated
     * with inter-partition communication objects in the VM platform definition
     * below using the shared memory object ID, ie, its index in the list.
     */
    .shmemlist_size = 1,
    .shmemlist = (struct shmem[]) {
        [0] = {.size = 0x1000,}
    },

    /**
     * This configuration has 2 VMs.
     */
    .vmlist_size = 2,
    .vmlist = {
        { 
            .image = {
                .base_addr = 0x80000000,
                /** 
                 * Use the  VM_IMAGE_OFFSET and VM_IMAGE_SIZE to initialize
                 * the image fields passing the identifier of the image.
                 */
                .load_addr = VM_IMAGE_OFFSET(vm1),
                .size = VM_IMAGE_SIZE(vm1)
            },

            .entry = 0x80000000,
            .cpu_affinity = 0x3,
            .colors = 0x0F0F0F0F,

            .platform = {

                .cpu_num = 2,
                
                .region_num = 1,
                .regions =  (struct mem_region[]) {
                    {
                        .base = 0x80000000,
                        .size = 0x100000 
                    }
                },

                .dev_num = 1,
                .devs =  (struct dev_region[]) {
                    {   
                        /* UART0 */
                        .pa = 0x1c090000,
                        .va = 0x1c090000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {38} 
                    }
                },

                .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0x80100000,
                        .size = 0x1000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {42}
                    }
                },

                .arch = {
                    .gic = {
                        .gicc_addr = 0x2C000000,
                        .gicd_addr = 0x2F000000
                    }
                }
            },

        },

        {
            .image = {
                .base_addr = 0x00000000,
                .load_addr = VM_IMAGE_OFFSET(vm2),
                .size = VM_IMAGE_SIZE(vm2)
            },

            .entry = 0x0000000,
            .cpu_affinity = 0xC,
            .colors = 0xF0F0F0F0,

            .platform = {
                .cpu_num = 2,
                
                .region_num = 2,
                .regions =  (struct mem_region[]) {
                    {
                        .base = 0x00000000,
                        .size = 0x80000000 
                    }
                    ,
                    {
                        .base = 0x100000000,
                        .size = 0x40000000
                    }
                },

                .dev_num = 1,
                .devs =  (struct dev_region[]) {
                    {   
                        /* UART1 */
                        .pa = 0x1C0B0000,
                        .va = 0x1c090000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {39} 
                    },
                    {
                        /* Timer interrupt */
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {27}
                    }
                },

                .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0x90000000,
                        .size = 0x1000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (uint64_t[]) {112}
                    }
                },

                .arch = {
                    .gic = {
                        .gicc_addr = 0x2C000000,
                        .gicd_addr = 0x2F000000
                    }
                }
            },
        },
    },
};
