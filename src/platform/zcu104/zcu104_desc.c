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
    .cpu_num = 4,
    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
           /**
            * The Arm Trusted Firmware shipped in the default Xilinx BOOT.BIN
            * is loaded in a non secure zone, more specifically at the end of
            * the first memory bank. Being in a non-secure zone means that can
            * be easily overwritten.
            *
            * The memory size is therefore shrunk to take this into account and
            * avoid memory corruption.
            *
            * Note that if the ATF is compiled with debug symbols or with a
            * custom SPD service, then it gets loaded at the *beginning* of the
            * first memory bank, in that case the base address should be
            * changed to 0x80000, and the size shrunk accorindgly.
            */
            .base = 0x00080000,
            .size = 0x7FF00000 - 0x16000
        }
    },

    .console = {
        .base = 0xFF000000
    },

    .arch = {
        .gic = {
            .gicd_addr = 0xF9010000,
            .gicc_addr = 0xF902f000,
            .gich_addr = 0xF9040000,
            .gicv_addr = 0xF906f000,
            .maintenance_id = 25
        },

        .smmu = {
            .base = 0xFD800000,
            .interrupt_id = 187
        },

        .generic_timer = {
            .base_addr = 0xFF260000
        }
    }
};
