/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

struct platform platform = {

    .cpu_num = 4,
    .cpu_master_fixed = true,
    .cpu_master = 0,

    .region_num = 11,
    .regions =
        (struct mem_region[]){
            // Code flash (User Areas)
            {
                .base = 0x0,
                .size = 0x1000000,
                .perms = MEM_RX,
            },
            // Code flash (Non-overlay area & User Boot Area 0)
            {
                .base = 0x4000000,
                .size = 0x4010000,
                .perms = MEM_RX,
            },
            // Code flash (User Boot Area 1)
            {
                .base = 0x8400000,
                .size = 0x10000,
                .perms = MEM_RX,
            },
            // Cluster0 RAM
            {
                .base = 0xFE000000,
                .size = 0x80000,
                .perms = MEM_RWX,
            },
            // Cluster1 RAM
            {
                .base = 0xFE100000,
                .size = 0x80000,
                .perms = MEM_RWX,
            },
            // Cluster2 RAM
            {
                .base = 0xFE400000,
                .size = 0x200000,
                .perms = MEM_RWX,
            },
            // Cluster3 RAM (Retention RAM)
            {
                .base = 0xFE800000,
                .size = 0x40000,
                .perms = MEM_RWX,
            },
            // Local RAM (CPU0)
            {
                .base = 0xFDC00000,
                .size = 0x10000,
                .perms = MEM_RWX,
            },
            // Local RAM (CPU1)
            {
                .base = 0xFDA00000,
                .size = 0x10000,
                .perms = MEM_RWX,
            },
            // Local RAM (CPU2)
            {
                .base = 0xFD800000,
                .size = 0x10000,
                .perms = MEM_RWX,
            },
            // Local RAM (CPU3)
            {
                .base = 0xFD600000,
                .size = 0x10000,
                .perms = MEM_RWX,
            }
        },

    .console = {
        .base = 0xFFC7C100, // RLIN35
    },

    .arch = {
        .intc = {
            .intc1_addr = 0xFFFC0000,
            .intc2_addr = 0xFFF80000,
            .intif_addr = 0xFF090000,
            .eint_addr = 0xFFC00000,
            .fenc_addr = 0xFF9A3A00,
            .feinc_addr = {
                0xFF9A3B00,
                0xFF9A3C00,
                0xFF9A3D00,
                0xFF9A3E00,
            },
        },

        .bootctrl_addr = 0xFFFB2000,
        .ipir_addr = 0xFFFB9000
    }
};

/*
    Array of port register values

    Index:  |0 |1 |2 |3 |4 |5  |6  |7  |8  |9  |10 |
    Groups: |G2|G3|G4|G5|G6|G10|G17|G20|G21|G22|G24|
*/
const uint16_t port_reg_val[PLAT_NUM_PORT_CFG_REGS][PLAT_NUM_PORT_GROUPS] = {
    /*|   G2   |   G3   |   G4   |   G5   |   G6   |   G10   |  G17  |   G20  |   G21  |   G22  |
       G24   |*/
    /* P */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0800U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U, 0x0000U },
    /* PM */
    { 0x8CD3U, 0xFFEBU, 0x2A5FU, 0xFFEBU, 0xEE2FU, 0xF39CU, 0xFFDCU, 0xB9A7U, 0xFF1FU, 0xFFE2U,
        0xFFFFU },
    /* PMC */
    { 0x7830U, 0x003CU, 0x1BC0U, 0x0004U, 0x9B40U, 0x3F18U, 0x0000U, 0x66C8U, 0x00E0U, 0x001FU,
        0x0000U },
    /* PFC */
    { 0x0000U, 0x0014U, 0x1B40U, 0x0000U, 0x1340U, 0x2118U, 0x0000U, 0x66C8U, 0x00E0U, 0x001FU,
        0x0000U },
    /* PFCE */
    { 0x7830U, 0x0028U, 0x0800U, 0x0004U, 0x9B40U, 0x1E00U, 0x0000U, 0x0000U, 0x0000U, 0x0013U,
        0x0000U },
    /* PFCAE */
    { 0x0010U, 0x0028U, 0x10C0U, 0x0000U, 0x8000U, 0x2100U, 0x0000U, 0x0000U, 0x00E0U, 0x000CU,
        0x0000U },
    /* PINV */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PIBC */
    { 0x0001U, 0x0040U, 0x2003U, 0x0040U, 0x0020U, 0x0000U, 0x0000U, 0x0100U, 0x0000U, 0x0000U,
        0x0000U },
    /* PBDC */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PIPC */
    { 0x2000U, 0x0000U, 0x0000U, 0x0004U, 0x0000U, 0x0400U, 0x0000U, 0x0008U, 0x00E0U, 0x0001U,
        0x0000U },
    /* PU */
    { 0x0000U, 0x0000U, 0x0200U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PD */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PODC */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0008U, 0x0000U, 0x0000U,
        0x0000U },
    /* PDSC */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0018U, 0x0000U, 0x6680U, 0x0000U, 0x0000U,
        0x0000U },
    /* PIS */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PISA */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0018U, 0x0000U, 0x6680U, 0x0000U, 0x0000U,
        0x0000U },
    /* PUCC */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PODCE */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PSFC */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PSFTS */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U },
    /* PSFTSE */
    { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U,
        0x0000U }
};

/*
    Array of analogic port register values

    Index:  |0 |1 |2 |3 |4 |
    Groups: |G0|G1|G2|G3|G4|
*/
const uint16_t aport_reg_val[PLAT_NUM_APORT_CFG_REGS][PLAT_NUM_APORT_GROUPS] = {
    /*|   G0   |   G1   |   G2   |   G3   |   G4    |*/
    /* AP */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APM */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APINV */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APIBC */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APBDC */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APODC */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APDSC */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APODCE */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APSFC */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APSFTS */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U },
    /* APSFTSE */ { 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U }
};
