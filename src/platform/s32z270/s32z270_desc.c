/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 4,
    .cpu_master_fixed = true,
    .cpu_master = 0,
    .region_num = 22,
    .regions =  (struct mem_region[]) {
        {   /* CRAM0 (Code SRAM) - Optimized for low-latency code accesses. */
            .base = 0x32100000,
            .size = 0x100000,   // 1 MiB
            .perms = MEM_RX,
        },
        {   /* DRAM0 (Data SRAM) - Optimized for low-latency data accesses. */
            .base = 0x31780000,
            .size = 0x40000,    // 256 KiB
            .perms = MEM_RWX,
        },
        {   /* ATCM-RTU0-CPU0 */
            .base = 0x30000000,
            .size = 0x10000,    // 64 KiB
            .perms = MEM_RWX,
        },
        {   /* BTCM-RTU0-CPU0 */
            .base = 0x30100000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* CTCM-RTU0-CPU0 */
            .base = 0x30200000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* ATCM-RTU0-CPU1 */
            .base = 0x30400000,
            .size = 0x10000,    // 64 KiB
            .perms = MEM_RWX,
        },
        {   /* BTCM-RTU0-CPU1 */
            .base = 0x30500000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* CTCM-RTU0-CPU1 */
            .base = 0x30600000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* ATCM-RTU0-CPU2 */
            .base = 0x30800000,
            .size = 0x10000,    // 64 KiB
            .perms = MEM_RWX,
        },
        {   /* BTCM-RTU0-CPU2 */
            .base = 0x30900000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* CTCM-RTU0-CPU2 */
            .base = 0x30a00000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* ATCM-RTU0-CPU3 */
            .base = 0x30c00000,
            .size = 0x10000,    // 64 KiB
            .perms = MEM_RWX,
        },
        {   /* BTCM-RTU0-CPU3 */
            .base = 0x30d00000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* CTCM-RTU0-CPU3 */
            .base = 0x30e00000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
        },
        {   /* DRAM1 */
            .base = 0x317C0000,
            .size = 0x40000,    // 256 KiB
            .perms = MEM_RWX,
        },
        {   /* DRAM2 */
            .base = 0x31800000,
            .size = 0x80000,    // 512 KiB
            .perms = MEM_RWX,
        },
        {   /* CRAM1 */
            .base = 0x32200000,
            .size = 0x100000,   // 1 MiB
            .perms = MEM_RX,
        },
        {   /* CRAM2 */
            .base = 0x32300000,
            .size = 0x100000,   // 1 MiB
            .perms = MEM_RX,
        },
        {   /* CRAM3 */
            .base = 0x32400000,
            .size = 0x100000,   // 1 MiB
            .perms = MEM_RX,
        },
        {   /* CRAM4 */
            .base = 0x32500000,
            .size = 0x100000,   // 1 MiB
            .perms = MEM_RX,
        },
        {   /* CRAM5 */
            .base = 0x32600000,
            .size = 0x100000,   // 1 MiB
            .perms = MEM_RX,
        },
        {   /* CRAM6 */
            .base = 0x32700000,
            .size = 0x100000,   // 1 MiB
            .perms = MEM_RX,
        },
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
            /* S32Z270 R52 platform-defined system counter is by default at 8 MHz
            (FXOSC/RTU.GPR.CFG_CNTDV = 40 MHz / 4+1). If the counter divisor is changed, this value
            must be updated accordingly. */
            .fixed_freq = 8000000
        }
    }
};
