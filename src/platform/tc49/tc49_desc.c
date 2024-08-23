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
            .size = 0x80000000,
        }
    },

    .arch = {
        .ir = {
            .int_addr = 0xF0030000,
            .src_addr = 0xF0032000,
        },
    },

    .console = {
        .base = 0x9C090000,
    },
};
