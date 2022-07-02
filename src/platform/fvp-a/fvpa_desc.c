/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
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
