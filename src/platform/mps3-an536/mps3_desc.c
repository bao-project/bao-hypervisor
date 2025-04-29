/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 2,
    .cpu_master_fixed = true,
    .cpu_master = 0,

    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            // DRAM, 0GB-2GB
            .base = 0x20000000,
            .size = 0x80000000,
        }
    },

    .console = {
        //.base = 0xE7C00000,  // UART LLPP //MAYBE
        .base = 0xE0205000,  // UART0
    },

    .arch = {
        .gic = {
            //GIC DISTRIBUTOR 0xF0000000
            .gicd_addr = 0xF0000000,
            //.gicc_addr = 0xAC000000,
            //.gich_addr = 0xAC010000,
            //.gicv_addr = 0xAC02F000,
            .gicr_addr = 0xF0100000,
            .maintenance_id = 25,
        },

        .generic_timer = {
            .base_addr = 0xE0101000, //DUAL TIMER ??
        },
    },

};
