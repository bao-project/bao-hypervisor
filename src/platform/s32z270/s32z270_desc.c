/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

/* The TCM hosting each core's cpu structure is that core's S32Z270_CPUn_HOME Kconfig choice */
#define CPU0_ATCM_HOME (CONFIG_S32Z270_CPU0_HOME == 0)
#define CPU0_BTCM_HOME (CONFIG_S32Z270_CPU0_HOME == 1)
#define CPU0_CTCM_HOME (CONFIG_S32Z270_CPU0_HOME == 2)

#define CPU1_ATCM_HOME (CONFIG_S32Z270_CPU1_HOME == 0)
#define CPU1_BTCM_HOME (CONFIG_S32Z270_CPU1_HOME == 1)
#define CPU1_CTCM_HOME (CONFIG_S32Z270_CPU1_HOME == 2)

#define CPU2_ATCM_HOME (CONFIG_S32Z270_CPU2_HOME == 0)
#define CPU2_BTCM_HOME (CONFIG_S32Z270_CPU2_HOME == 1)
#define CPU2_CTCM_HOME (CONFIG_S32Z270_CPU2_HOME == 2)

#define CPU3_ATCM_HOME (CONFIG_S32Z270_CPU3_HOME == 0)
#define CPU3_BTCM_HOME (CONFIG_S32Z270_CPU3_HOME == 1)
#define CPU3_CTCM_HOME (CONFIG_S32Z270_CPU3_HOME == 2)

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
            .cpu_affinity = CORE(0),
            .cpu_home = CPU0_ATCM_HOME,
        },
        {   /* BTCM-RTU0-CPU0 */
            .base = 0x30100000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(0),
            .cpu_home = CPU0_BTCM_HOME,
        },
        {   /* CTCM-RTU0-CPU0 */
            .base = 0x30200000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(0),
            .cpu_home = CPU0_CTCM_HOME,
        },
        {   /* ATCM-RTU0-CPU1 */
            .base = 0x30400000,
            .size = 0x10000,    // 64 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(1),
            .cpu_home = CPU1_ATCM_HOME,
        },
        {   /* BTCM-RTU0-CPU1 */
            .base = 0x30500000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(1),
            .cpu_home = CPU1_BTCM_HOME,
        },
        {   /* CTCM-RTU0-CPU1 */
            .base = 0x30600000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(1),
            .cpu_home = CPU1_CTCM_HOME,
        },
        {   /* ATCM-RTU0-CPU2 */
            .base = 0x30800000,
            .size = 0x10000,    // 64 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(2),
            .cpu_home = CPU2_ATCM_HOME,
        },
        {   /* BTCM-RTU0-CPU2 */
            .base = 0x30900000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(2),
            .cpu_home = CPU2_BTCM_HOME,
        },
        {   /* CTCM-RTU0-CPU2 */
            .base = 0x30a00000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(2),
            .cpu_home = CPU2_CTCM_HOME,
        },
        {   /* ATCM-RTU0-CPU3 */
            .base = 0x30c00000,
            .size = 0x10000,    // 64 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(3),
            .cpu_home = CPU3_ATCM_HOME,
        },
        {   /* BTCM-RTU0-CPU3 */
            .base = 0x30d00000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(3),
            .cpu_home = CPU3_BTCM_HOME,
        },
        {   /* CTCM-RTU0-CPU3 */
            .base = 0x30e00000,
            .size = 0x4000,    // 16 KiB
            .perms = MEM_RWX,
            .cpu_affinity = CORE(3),
            .cpu_home = CPU3_CTCM_HOME,
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

    .mmio_region_num = 1,
    .mmio_regions = (struct mem_region[]) {
        {   /* Peripheral space (AIPS, GIC, generic timer, LINFlexD) */
            .base = 0x40000000,
            .size = 0x10000000,
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
