/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 4,
    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x40000000,
            .size = 0x100000000 
        }
    },

    .console = {
        .base = 0x9000000
    },

    .arch = {
        .gic = {
            .gicd_addr = 0x08000000,
            .gicc_addr = 0x08010000,
            .gich_addr = 0x08030000,
            .gicv_addr = 0x08040000,
            .gicr_addr = 0x080A0000,
            .maintenance_id = 25
        },
    }

};
