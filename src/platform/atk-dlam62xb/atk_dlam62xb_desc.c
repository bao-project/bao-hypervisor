/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {
    .cpu_num = 4,
    .cpu_master_fixed = true,
    .cpu_master = 0,
    .region_num = 1,
    .regions = (struct mem_region[]) {{ .base = 0x80000000, .size = 0x40000000 }},
    .console = { .base = 0x02800000 },
    .arch = {
        .clusters = { .num = 1, .core_num = (size_t[]) {4} },
        .mpidr_table = { .table = (unsigned long[]) {0, 1, 2, 3} },
        .gic = { .gicd_addr = 0x01800000, .gicr_addr = 0x01880000, .maintenance_id = 25 },
    },
};
