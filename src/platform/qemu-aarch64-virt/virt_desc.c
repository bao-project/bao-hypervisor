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
    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x40000000,
            .size = 0x100000000 
        }
    },

    .console = {
        .base = 0x9000000
    },

    .arch = {
        .gic = {
            .gicd_addr = 0x08000000,
            .gicc_addr = 0x08010000,
            .gich_addr = 0x08030000,
            .gicv_addr = 0x08040000,
            .gicr_addr = 0x080A0000,
            .maintenance_id = 25
        },
    }

};
