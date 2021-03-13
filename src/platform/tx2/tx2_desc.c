/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Gero Schwaericke <gero.schwaericke@tum.de>
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
            .core_num = (uint8_t[]){ 2, 4 },
        },

        .smmu = {
            .base = 0x12000000,
            .interrupt_id = 187,
            .global_mask = 0x7f80,
        }
    }

};
