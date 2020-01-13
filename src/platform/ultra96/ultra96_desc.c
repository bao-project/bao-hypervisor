/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <platform.h>

struct platform_desc platform = {
    .cpu_num = 4,
    .region_num = 2,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x00000000,
            .size = 0x100000 
        },
        {
            .base = 0x00100000,
            .size = 0x7FE00000 
        },
    },

    .console = {
        .base = 0xFF010000
    },

    .arch = {
        .gic = {
            .gicd_addr = 0xF9010000,
            .gicc_addr = 0xF902f000,
            .gich_addr = 0xF9040000,
            .gicv_addr = 0xF906f000,
            .maintenance_id = 25
        },

        .generic_timer = {
            .base_addr = 0xFF260000
        }
    }

};