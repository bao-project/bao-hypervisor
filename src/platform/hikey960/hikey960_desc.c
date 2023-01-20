/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {
    .cpu_num = 4, /* ONLY SUPORT A53 FOR NOW, cpu_num max is 4 */
    .region_num = 2,

    /* plat memory is: 0-3.5GB; 4-4.5GB */
    .regions =  (struct mem_region[]) {
        {
            /* 0-3.5GB*/
            .base = 0x00000000,
            .size = 0xE0000000,
        },
        {
            /* 8-8.5G from UEFI*/
            .base = 0x200000000,
            .size =  0x20000000,
        },
    },

    .arch = {
        .gic = {
            /* check gic 400 manual */ 
            .gicd_addr = 0xE82B1000,
            .gicc_addr = 0xE82B2000,
            .gich_addr = 0xE82B4000,
            .gicv_addr = 0xE82B6000,
            .maintenance_id = 25
        },

        .generic_timer = {
            .base_addr = 0xFFF08000 /* SYS_CNT */
        },

        .smmu = {
            .base = 0xE8DC0000
        }
    },

    .console = {
        .base = 0xFFF32000 /* UART 6 */
    },
};
