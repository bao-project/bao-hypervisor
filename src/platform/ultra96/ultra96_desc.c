/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {
    .cpu_num = 4,
    .region_num = 2,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x00000000,
            .size = 0x100000 
        },
        {
            .base = 0x00100000,
            .size = 0x7FE00000 
        },
    },

    .console = {
        .base = 0xFF010000
    },

    .arch = {
        .gic = {
            .gicd_addr = 0xF9010000,
            .gicc_addr = 0xF902f000,
            .gich_addr = 0xF9040000,
            .gicv_addr = 0xF906f000,
            .maintenance_id = 25
        },

        .generic_timer = {
            .base_addr = 0xFF260000
        }
    }

};
