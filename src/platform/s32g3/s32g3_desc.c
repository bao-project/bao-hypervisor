/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 8,
    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x80000000,
            .size = 0x80000000,
        }
    },

    .console = {
        .base = 0x401c8000,
    },

    .arch = {

        .clusters =  {
            .num = 2,
            .core_num = (size_t[]) {4, 4},
        },

        .gic = {
            .gicd_addr = 0x50800000,
            .gicr_addr = 0x50900000,
            .gicc_addr = 0x50400000,
            .gich_addr = 0x50410000,
            .gicv_addr = 0x50420000,
            .maintenance_id = 25,
        },
    },
};
