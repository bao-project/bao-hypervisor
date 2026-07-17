/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

/* Board DDR map. Capacity is injected as AGX5_MEM_GB via platform-cppflags
 * (-DAGX5_MEM_GB, see platform.mk) and is common across all Agilex5 boards.
 * Capacities > 2 GiB add a second mem_region for the high DDR window.
 */
#define AGX5_GB        (0x40000000ULL)
#define AGX5_LOW_BASE  (0x82000000ULL)
#define AGX5_LOW_RSVD  (AGX5_LOW_BASE - 0x80000000ULL)
#define AGX5_HIGH_BASE (0x880000000ULL)

/* GiB owned by each window for the requested capacity. */
#define AGX5_LOW_GB    ((AGX5_MEM_GB) >= 2 ? 2ULL : (AGX5_MEM_GB))
#define AGX5_HIGH_GB   ((AGX5_MEM_GB) > 2 ? ((AGX5_MEM_GB) - 2ULL) : 0ULL)

struct platform platform = {
    .cpu_num = 4,
    .arch = {
        .clusters = {
            .num = 1,
            .core_num = (size_t[]){ 4 },
        },
        .gic = {
            .gicc_addr = 0x0,
            .gich_addr = 0x0,
            .gicv_addr = 0x0,
            .gicd_addr = 0x1d000000,
            .gicr_addr = 0x1d060000,
            .maintenance_id = 25,
        },
        .generic_timer = {
            .base_addr = 0x10d02000,
        },
    },
    .region_num = (AGX5_MEM_GB > 2) ? 2 : 1,
    .regions = (struct mem_region[]) {
        {
            /* Low window @ 0x82000000, capped at 2 GiB minus the 32 MiB
             * TF-A/stub reservation. For AGX5_MEM_GB=2 this is 0x7e000000.
             */
            .base = AGX5_LOW_BASE,
            .size = (AGX5_LOW_GB * AGX5_GB) - AGX5_LOW_RSVD,
        },
        {
            /* High window @ 0x880000000 = capacity above 2 GiB.
             * Only used when region_num == 2 (AGX5_MEM_GB > 2).
             */
            .base = AGX5_HIGH_BASE,
            .size = AGX5_HIGH_GB * AGX5_GB,
        },
    },
    .console = {
        .base = 0x10c02000,
    },
};
