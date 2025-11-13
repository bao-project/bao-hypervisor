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
            .base = 0x20000000,
            .size = 0x80000000,
        }
    },

    .console = {
        .base = 0xE0205000,  // UART2
    },

    .arch = {
        .gic = {
            .gicd_addr = 0xF0000000,
            .gicr_addr = 0xF0100000,
            .maintenance_id = 25,
        },
    },

};
