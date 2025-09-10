/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 4,
    .cpu_master_fixed = true,
    .cpu_master = 0,
    .region_num = 2,
    .regions =  (struct mem_region[]) {
        {
            /* CRAM0 (Code SRAM) - Optimized for low-latency code accesses. Can be used for data,
            but we restrict it to code only. */
            .base = 0x32100000,
            .size = 0x200000,
            .perms = MEM_RX,
        },
        {
            /* DRAM0 (Data RAM) - Optimized for low-latency data accesses. Can be used for code,
            but we restrict it to data only. "plat_mem" build macro must be equal to "non_unified"
            */
            .base = 0x31780000,
            .size = 0x40000,
            .perms = MEM_RWX,
        }
    },

    .console = {
        /* LINFlexD 9 */
        .base = 0x42980000
    },

    .arch = {
        .clusters =  {
            .num = 1,
            .core_num = (size_t[]) {4}
        },

        .gic = {
            .gicd_addr = 0x47800000,
            .gicr_addr = 0x47900000,
            .maintenance_id = 25
        },

        .generic_timer = {
            .base_addr = 0x44820000,
            .fixed_freq = 8000000       // 8 MHz (FXOSC/RTU.GPR.CFG_CNTDV = 40 MHz / 4+1)
        }
    }
};
