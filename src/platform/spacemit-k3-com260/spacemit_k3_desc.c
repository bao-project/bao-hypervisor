/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <interrupts.h>

/**
 * SpacemiT K3 platform description (CoM260 Kit V02).
 *
 * Hardware facts taken from the vendor device tree (k3.dtsi / k3-cpus.dtsi on
 * the k3-br-v1.0.y SDK branch):
 *
 *   - 16 harts are declared, but only cpu@0-7 (X100) have the "h" extension
 *     (riscv,isa = "rv64imafdcvh"). cpu@8-15 (A100) lack "h" and cannot host a
 *     hypervisor, so Bao manages only the 8 X100 harts.
 *
 *   - DRAM (memory@102000000): reg = <0x1 0x02000000 0x1 0xfe000000>, i.e. base
 *     0x102000000, size 0x1fe000000. The low 32 MiB above 4 GiB are reserved
 *     for firmware/RCPU and are excluded from this region.
 *
 *   - AIA (Advanced Interrupt Architecture):
 *       * S-level APLIC (saplic@e0804000): 512 wired sources.
 *       * S-level IMSIC (simsic@e0400000), size 0x400000:
 *           riscv,num-ids          = 511
 *           riscv,hart-index-bits  = 4
 *           riscv,guest-index-bits = 6  => 2^6 = 64 interrupt files per hart
 *                                          (1 S-file + 63 VS-files), so the
 *                                          per-hart stride is 64 * 4 KiB =
 *                                          0x40000. With 8 harts that is exactly
 *                                          the 0x400000 region.
 *         Bao derives PLAT_IMSIC_HART_SIZE from (num_guest_files + 1) rounded up
 *         to a power of two, so num_guest_files = 63 reproduces the 0x40000
 *         stride. Bao itself only uses the first VS-file (which is one of the 7
 *         valid VS-files on X100).
 *
 *   - IPIs use the SBI IPI extension (IPIC_SBI); the riscv,clint0@e081c000 is
 *     left to the resident M-mode OpenSBI.
 */

#define K3_DRAM_BASE      (0x102000000)
#define K3_DRAM_SIZE      (0x1fe000000)

#define K3_APLIC_BASE     (0xe0804000)
#define K3_IMSIC_BASE     (0xe0400000)
#define K3_IMSIC_NUM_MSIS (511)
/* (num_guest_files + 1) rounds up to 64 => per-hart IMSIC stride of 0x40000. */
#define K3_IMSIC_NUM_GUEST_FILES (63)

struct platform platform = {

    .cpu_num = 1,

    .region_num = 1,
    .regions = (struct mem_region[]) {
        {
            .base = K3_DRAM_BASE,
            .size = K3_DRAM_SIZE,
        },
    },

    /* K3 UART0: the hypervisor's own console (page-aligned base). */
    .console = {
        .base = 0xd4017000,
    },

    .arch = {
        .irqc.aia.aplic.base = K3_APLIC_BASE,
        .irqc.aia.imsic.base = K3_IMSIC_BASE,
        .irqc.aia.imsic.num_msis = K3_IMSIC_NUM_MSIS,
        .irqc.aia.imsic.num_guest_files = K3_IMSIC_NUM_GUEST_FILES,
    },

};
