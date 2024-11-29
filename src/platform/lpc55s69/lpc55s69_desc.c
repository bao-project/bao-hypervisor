/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

irqid_t plat_ints[2048];

struct platform platform = {

    .cpu_num = 1,
    .cpu_master_fixed = true,
    .cpu_master = 0,

    .region_num = 2,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x30000000, //SRAM0+1 (64 + 64 KiB)
            .size = 0x20000,    //128 KiB
            .perms = RX,
        },
        {
            .base = 0x30020000, //SRAM2+3 (64 + 64 KiB)
            .size = 0x20000,    //128 KiB
            .perms = RWX,
        }
    },

    .console = {
        .base = 0x50086000, // USART0
    },

    .arch = {
        .nvic = {
            .int_addr = 0xF4430000,
            .src_addr = 0xF4432000,
            .interrupts = plat_ints,
            .num_interrupts = sizeof(plat_ints)/sizeof(plat_ints[0])
        },
    },

};
