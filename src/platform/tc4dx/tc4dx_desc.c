
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <plat/plat_irqs.h>
#include <plat/plat_devs.h>

struct platform platform = {

    .cpu_num = 6,
    .cpu_master_fixed = true,
    .cpu_master = 0,

    .region_num = 23,
    .regions =  (struct mem_region[]) {
        {   // NVM.PFLASH00 - 2Mb
            .base = 0xA0000000,
            .size = 0x400000,
            .perms = MEM_RX,
        },
        {
            // DLMU0
            .base = 0x90000000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // DLMU1
            .base = 0x90080000,
            .size =   0x80000,
            .perms = MEM_RWX,
        },
        {
            // DLMU2
            .base = 0x90100000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // DLMU3
            .base = 0x90180000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // DLMU4
            .base = 0x90200000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // DLMU5
            .base = 0x90280000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU0
            .base = 0x90400000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU1
            .base = 0x90480000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU2
            .base = 0x90500000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU3
            .base = 0x90580000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU4
            .base = 0x90600000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU5
            .base = 0x90680000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU6
            .base = 0x90700000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU7
            .base = 0x90780000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU8
            .base = 0x90800000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // LMU9
            .base = 0x90880000,
            .size = 0x80000,
            .perms = MEM_RWX,
        },
        {
            // CPU0.DSPR, 240Kb
            .base = 0x70000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
        {
            // CPU1.DSPR, 240Kb
            .base = 0x60000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
        {
            // CPU2.DSPR, 240Kb
            .base = 0x50000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
        {
            // CPU3.DSPR, 240Kb
            .base = 0x40000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
        {
            // CPU4.DSPR, 240Kb
            .base = 0x30000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
        {
            // CPU5.DSPR, 240Kb
            .base = 0x20000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
    },
    .mmio_region_num = 1,
    .mmio_regions = (struct mem_region[]) {
        {
            .base = 0xF0000000,
            .size = 0xFFF0000,
        },
    },
    .arch = {
        .ir = {
            .int_addr = 0xF4430000,
            .src_addr = 0xF4432000,
            .GPSR_offset = 0x700,
            .GPSR_size = 0x420,
        },
        .device_num = sizeof(dev_array)/sizeof(struct plat_device),
        .devices = dev_array,
    },

    .console = {
        .base = 0xF46C0000, //ASCLIN0
    },
};
