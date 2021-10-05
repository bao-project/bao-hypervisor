/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <platform.h>

struct platform_desc platform = {
    .cpu_num = 6,
    .region_num = 2,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x80020000,
            .size = 0x80000000 - 0x20000 // 2 GiB - 128 KiB (reserved for ATF) 
        },
        {
            .base = 0x880000000,
            .size = 0x100000000 // 4 GiB 
        }
    },

    .console = {
        .base = 0x5a060000
    },

    .arch = {

        .clusters =  {
            .num = 2,
            .core_num = (uint8_t[]) {4, 2}
        },

        .gic = {
            .gicd_addr = 0x51a00000,
            .gicr_addr = 0x51b00000,
            .gicc_addr = 0x52000000,
            .gich_addr = 0x52010000,
            .gicv_addr = 0x52020000,
            .maintenance_id = 25
        },

        .smmu = {
            .base = 0x51400000,
            .interrupt_id = 187,
            .global_mask = 0x7fc0,
        },

    }
};
