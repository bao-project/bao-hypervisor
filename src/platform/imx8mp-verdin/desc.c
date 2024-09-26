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
            .size = 0x80000000, // 2 GiB
        },
    },

    .console = {
        .base = 0x30880000,
    },

    .arch = {
        .gic = {
	    .gicd_addr = 0x38800000,
	    .gicr_addr = 0x38880000,
	    .gicc_addr = 0x31000000,
	    .gicv_addr = 0x31010000,
	    .gich_addr = 0x31020000,
            .maintenance_id = 25
        },
    }
};
