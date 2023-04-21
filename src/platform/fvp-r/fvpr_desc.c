/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 4,
    .cpu_master_fixed = true,
    .cpu_master = 0,

    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            // DRAM, 0GB-2GB
            .base = 0x00000000,
            .size = 0x80000000
        }
    },

    .console = {
        .base = 0x9C090000  // UART0 (PL011)
    },

    .arch = {
        .gic = {
            .gicd_addr = 0xAF000000,
            .gicc_addr = 0xAC000000,
            .gich_addr = 0xAC010000,
            .gicv_addr = 0xAC02F000,
            .gicr_addr = 0xAF100000,
            .maintenance_id = 25
        },

        .generic_timer = {
            .base_addr = 0xAA430000
        }
    }

};
