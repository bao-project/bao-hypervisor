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

struct platform platform = {
    .cpu_num = 4,
    .region_num = 2,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x40000000,
            .size = 0xffffffff - 0x40000000, // 3 GiB
        },
        {
            .base = 0x100000000,
            .size = 0x13FFFFFFF-0x100000000, // 1 GiB
        }
    },

    .console = {
        .base = 0x30860000,
    },

    .arch = {

        .clusters =  {
            .num = 1,
            .core_num = (size_t[]) {4}
        },

        .gic = {
	    .gicd_addr = 0x38800000,
	    .gicr_addr = 0x38880000,
	    .gicc_addr = 0x31000000,
	    .gicv_addr = 0x31010000,
	    .gich_addr = 0x31020000,
            .maintenance_id = 25
        },
    }
};
