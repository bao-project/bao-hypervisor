/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */


#include <config.h>

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
        [0] = {.base = 0x317FF000,
               .size = 0x1000,}
    },

    /**
     * This configuration has 2 VMs.
     */
    .vmlist_size = 2,
    .vmlist = {
       { 
           //.image = VM_IMAGE_LOADED(0x317C0000, 0x317C0000, 0x14000), // SRAM
           .image = VM_IMAGE_LOADED(0x32200000, 0x32200000, 0x14000),   // CRAM

           .entry = 0x32200000,
           .cpu_affinity = 0b00,

           .platform = {

               .cpu_num = 1,

               .region_num = 1,
               .regions =  (struct vm_mem_region[]) {
                   {
                       .base = 0x32200000,
                       .size = 0x0007FFFF
                   }
               },

               .dev_num = 2,
               .devs =  (struct vm_dev_region[]) {
                   {   
                       /* LINFlexD 9 */
                       .pa = 0x42980000,
                       .va = 0x42980000,
                       .size = 0x10000,
                       .interrupt_num = 1,
                       .interrupts = (irqid_t[]) {253}  
                   },
                   {   
                       /* SIUL2_5 */
                       .pa = 0x42D20000,
                       .va = 0x42D20000,
                       .size = 0xFFFF//0x1800
                   },
                   // {   
                   //     /* MC_CGM_5 */
                   //     .pa = 0x42830000,
                   //     .va = 0x42830000,
                   //     .size = 0x500
                   // }
               },

               .ipc_num = 1,
               .ipcs = (struct ipc[]) {
                   {
                       .base = 0x317FF000,
                       .size = 0x1000,
                       .shmem_id = 0,
                       .interrupt_num = 1,
                       .interrupts = (irqid_t[]) {42}
                   }
               },

               .arch = {
                   .gic = {
                       .gicc_addr = 0x2C000000,
                       .gicd_addr = 0x47800000,
                       .gicr_addr = 0x47900000
                   }
               }
           },

       },

        {
            // .image = VM_IMAGE_LOADED(0x31800000, 0x31800000, 0xe086),
            .image = VM_IMAGE_LOADED(0x32280000, 0x32280000, 0xe086),          // CRAM

            // .entry = 0x31800000,    // Zephyr
            .entry = 0x32280000,    // Zephyr
            .cpu_affinity = 0b10,

            .platform = {
                .cpu_num = 1,
                
                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        // .base = 0x31800000,
                        // .size = 0x80000
                        .base = 0x32280000, //CRAM
                        .size = 0x003FFFFF
                    }
                },

                .dev_num = 3,
                .devs =  (struct vm_dev_region[]) {
                    {   
                        /* LINFlexD 0 */
                        .pa = 0x40170000,
                        .va = 0x40170000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {244}  
                    },
                    {   
                        /* SIUL2_0 */
                        .pa = 0x40520000,
                        .va = 0x40520000,
                        .size = 0x1800
                    },
                    {   
                        /* MC_CGM_0 */
                        .pa = 0x40030000,
                        .va = 0x40030000,
                        .size = 0x500
                    }
                },

                .ipc_num = 1,
                .ipcs = (struct ipc[]) {
                    {
                        .base = 0x317FF000,
                        .size = 0x1000,
                        .shmem_id = 0,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {112}
                    }
                },

                .arch = {
                    .gic = {
                        .gicc_addr = 0x2C000000,
                        .gicd_addr = 0x47800000,
                        .gicr_addr = 0x47900000
                    }
                }
            },
        },
    },
};