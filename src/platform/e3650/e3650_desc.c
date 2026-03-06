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
        { // IRAM (3MB total, 256KB reserved for Bootloader at start)
            .base = 0x00A40000, 
            .size = 0x002C0000, 
        }
    },



    .console = {
        .base = E3650_UART_BASE, 
    },

    .arch = {
        .gic = {
            .gicd_addr = E3650_GICD_BASE,
            .gicr_addr = E3650_GICR_BASE,
            .maintenance_id = 25,
        },

        .generic_timer = {
            .fixed_freq = 600000000,
        },

        .clusters = {
            .num = 1,
            .core_num =  (size_t[]) { 4 },
        },
    },

};
