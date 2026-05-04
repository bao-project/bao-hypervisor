/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 4,

    .region_num = 1,
    .regions = (struct mem_region[]) {
        {
            /*
             * 2 GiB DRAM at 0x0; first 2 MiB reserved for OpenSBI firmware.
             * Adjust .base/.size to match your actual firmware load address.
             */
            .base = 0x200000,
            .size = 0x7FE00000,
        },
    },

    /* .cache = {
        .lvls = 2,
        .min_shared_lvl = 1,

        .type = {
            [0] = SEPARATE,
            [1] = UNIFIED,
        },

        .indexed = {
            [0] = { PIPT, PIPT },
            [1] = { PIPT, PIPT },
        },

        .line_size = {
            [0] = { 64, 64 },
            [1] = { 64, 64 },
        },

        .assoc = {
            [0] = { 4, 4 },
            [1] = { 16, 16 },
        },

        .numset = {
            [0] = { 256, 256 },
            [1] = { 2048, 2048 },
        },
    }, */

    .arch = {
        /* Supervisor-level APLIC (delegates from M-level APLIC at 0xe4400000) */
        .irqc.aia.aplic.base = 0xe4408000,
        /* Supervisor-level IMSIC; riscv,guest-index-bits = <2> → 3 VS-mode files per hart */
        .irqc.aia.imsic.base           = 0xc4100000,
        .irqc.aia.imsic.num_msis       = 63,
        .irqc.aia.imsic.num_guest_files = 3,
    },

};
