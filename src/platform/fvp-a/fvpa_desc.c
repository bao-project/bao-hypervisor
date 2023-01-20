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
            // DRAM, 0GB-2GB
            .base = 0x80000000,
            .size = 0x80000000
        }
    },

    .console = {
        .base = 0x1C090000  // UART0 (PL011)
    },

    .arch = {
        .gic = {
            .gicd_addr = 0x2F000000,
            .gicc_addr = 0x2C000000,
            .gich_addr = 0x2C010000,
            .gicv_addr = 0x2C02F000,
            .gicr_addr = 0x2F100000,
            .maintenance_id = 25
        },
    }

};
