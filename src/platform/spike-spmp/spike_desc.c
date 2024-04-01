/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <platform.h>

struct platform platform = {

    .cpu_num = 2,

    .region_num = 1,
    .regions =  (struct mem_region[]) {
#if (RV32)
        {
            .base = 0x80400000,
            .size = 0x80000000 - 0x400000,
        },
#else
        {
            .base = 0x80200000,
            .size = 0x80000000 - 0x200000,
        },
#endif
    },

    .arch = {
        .irqc.plic.base = 0xc000000,
    },

};
