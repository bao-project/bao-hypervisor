/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

#define E3650_UART_BASE 0xF8D60000 // UART15 Base

#define E3650_GICD_BASE 0xF4000000 // GIC Distributor
#define E3650_GICR_BASE 0xF4100000 // GIC Redistributor (Core 0)

struct platform platform = {

    .cpu_num = 4,
    .cpu_master_fixed = true,
    .cpu_master = 0,

    .region_num = 1,
    .regions =  (struct mem_region[]) {
        { // Start after 256KB Bootloader reservation
            .base = 0x00A40000, 
          // 3MB - 256KB
            .size = 0x002C0000, 
        }
    },

    .mmio_region_num = 3,
    .mmio_regions = (struct mem_region[]) {
        { // UART15
            .base = E3650_UART_BASE,
            .size = 0x1000, 
        },
        { // GIC Distributor
            .base = E3650_GICD_BASE,
            .size = 0x10000,
        },
        { // GIC Redistributor
            .base = E3650_GICR_BASE,
            .size = 0x20000,
        },
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
            .base_addr = 0xF8C20000, // APB_SYS_CNT_BASE
        },

        .clusters = {
            .num = 1,
            .core_num =  (size_t[]) { 4 },
        },
    },

};
