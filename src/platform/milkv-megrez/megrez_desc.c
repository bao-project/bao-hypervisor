/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <interrupts.h>

/*
 * Milk-V Megrez -- ESWIN EIC7700X, 4x SiFive P550 (rv64imafdch + Sscofpmf).
 * Main DRAM: 16 GiB at 0x80000000 .. 0x480000000.
 *
 * The three managed regions respect the board DTS `reserved-memory` no-map
 * carveouts: the three 4 KiB G2D boundary pages just below the 4/8/12 GiB marks
 * (the G2D engine cannot cross a 4 GiB boundary) and the top-6 GiB vendor "mmz"
 * pool at 0x300000000. They start 2 MiB above the DRAM base, above the vendor
 * OpenSBI -- Bao must also be loaded there (set FW_JUMP / the U-Boot load
 * address to match). ~10 GiB usable.
 */

#define MEGREZ_RAM_BASE (0x80200000) /* 2 MiB above DRAM base: skip vendor OpenSBI */

struct platform platform = {

    .cpu_num = 4,

    .region_num = 3,
    .regions = (struct mem_region[]) {
        /* DRAM base .. below the 4 GiB G2D boundary page */
        { .base = MEGREZ_RAM_BASE, .size = 0xFFFFF000 - MEGREZ_RAM_BASE },  /* ~2.0 GiB */
        /* 4 GiB .. below the 8 GiB G2D boundary page */
        { .base = 0x100000000,     .size = 0x1FFFFF000 - 0x100000000     }, /* ~4.0 GiB */
        /* 8 GiB .. below the 12 GiB G2D page; vendor mmz reserves 0x300000000+ */
        { .base = 0x200000000,     .size = 0x2FFFFF000 - 0x200000000     }, /* ~4.0 GiB */
    },

    .console = {
        /* serial0 (chosen/stdout-path): DW-APB UART @ 0x50900000 */
        .base = 0x50900000,
    },

    .arch = {
        /* sifive,plic-1.0.0 (ndev 520, qemu-virt-compatible context layout) */
        .irqc.plic.base = 0xc000000,

        /* IPIC_SBI + no Sstc: IPIs and timer go via SBI, no aclint_sswi.base */
    },

};
