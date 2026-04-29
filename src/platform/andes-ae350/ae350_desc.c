/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 1,

    .region_num = 1,
    .regions = (struct mem_region[]) {
        {
            /*
             * 2 GiB DRAM at 0x0; first 2 MiB reserved for OpenSBI firmware.
             * Adjust .base/.size to match your actual firmware load address.
             */
            .base = 0x00200000,
            .size = 0x7FE00000,
        },
    },

    .arch = {
        /* Supervisor-level APLIC (delegates from M-level APLIC at 0xe4400000) */
        .irqc.aia.aplic.base = 0xe4408000,
        /* Supervisor-level IMSIC; riscv,guest-index-bits = <2> → 3 VS-mode files per hart */
        .irqc.aia.imsic.base           = 0xc4100000,
        .irqc.aia.imsic.num_msis       = 63,
        .irqc.aia.imsic.num_guest_files = 3,
    },

};
