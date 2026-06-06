/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 8,

    .region_num = 1,
    .regions = (struct mem_region[]) {
        {
            .base = 0x102000000,
            .size = 0x1fe000000,
        },
    },

    /* K3 UART0: the hypervisor's own console (page-aligned base). */
    .console = {
        .base = 0xd4017000,
    },

    .arch = {
        .irqc.aia.aplic.base = 0xe0804000,
        .irqc.aia.imsic.base = 0xe0400000,
        .irqc.aia.imsic.num_msis = 511,
        .irqc.aia.imsic.num_guest_files = 63,
    },

};
