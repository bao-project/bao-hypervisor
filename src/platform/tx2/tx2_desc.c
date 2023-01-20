/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {
    .cpu_num = 6,
    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x80000000,
            .size = 0x200000000
        },
    },

    .console = {
        .base = 0x03100000
    },

    .arch = {
        .gic = {
            .gicd_addr = 0x03881000,
            .gicc_addr = 0x03882000,
            .gich_addr = 0x03884000,
            .gicv_addr = 0x03886000,
            .maintenance_id = 25
        },

        .clusters = {
            .num = 2,
            .core_num = (size_t[]){ 2, 4 },
        },

        .smmu = {
            .base = 0x12000000,
            .interrupt_id = 187,
            .global_mask = 0x7f80,
        }
    }

};
