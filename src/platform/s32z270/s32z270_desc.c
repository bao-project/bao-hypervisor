/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 2,
    .region_num = 2,
    .regions =  (struct mem_region[]) {
        {
            // DRAM, 256KB
            //.base = 0x34800000,        // SRAM0
            //.size = 0x40000,
            // CRAM, 1MB
            .base = 0x32100000,     // CRAM0
            .size = 0x200000,
            .perms = RX,
        },
        {
            .base = 0x34800000,     // CRAM0
            .size = 0x40000,
            .perms = RWX,
        }
    },

    .console = {
        .base = 0x42980000          // Linflexd_9
        //.base = 0x40170000          // Linflexd_0
    },

    .arch = {
        .clusters =  {
            .num = 1,
            .core_num = (size_t[]) {2}
        },

        .gic = {
            .gicd_addr = 0x47800000,
            .gicr_addr = 0x47900000,
            .maintenance_id = 25        //TBD
        },

        .generic_timer = {
            .base_addr = 0x44820000     //TBD
        }
    }
};
