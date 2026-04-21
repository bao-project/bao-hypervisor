/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <config.h>

struct config config = {
    .vmlist_size = 1,
    .vmlist = (struct vm_config[]) {
        {
            //Baremetal VM
            .image = VM_IMAGE_LOADED(0x32200000, 0x32200000, 0x14000),
            .entry = 0x32200000,
            .platform = {
                .cpu_num = 4,
                .region_num = 2,
                .regions =  (struct vm_mem_region[]) {
                    {
                        // CRAM1 (1MiB)
                       .base = 0x32200000,
                       .size = 0x100000
                   },
                   {
                        // DRAM1 (1MiB)
                       .base = 0x317C0000,
                       .size = 0x40000
                   }
                },
                .dev_num = 4,
                .devs =  (struct vm_dev_region[]) {
                    {
                        // LINFlexD_0
                        .pa = 0x40170000,
                        .va = 0x40170000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {244}
                    },
                    {
                        // SIUL2_0
                        .pa = 0x40520000,
                        .va = 0x40520000,
                        .size = 0x10000
                    },
                    {
                        // MC_CGM_0
                        .pa = 0x40030000,
                        .va = 0x40030000,
                        .size = 0x500
                    },
                    {
                        // System Timer
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {27}
                    },
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
    }
};
