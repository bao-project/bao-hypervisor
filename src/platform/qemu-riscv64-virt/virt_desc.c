/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <interrupts.h>

#if defined(RV32)
// We use only 1 GiB for the rv32, due to limitations on how the physical memory must
// be identity mapped by the hypervisor and the fact that the hypervisor reserves for
// itsel the upper GB of the 4GB address space.
#define QEMU_VIRT_MEM_REG_SIZE (0x40000000 - 0x200000)
#else
#define QEMU_VIRT_MEM_REG_SIZE (0x100000000 - 0x200000)
#endif

struct platform platform = {

    .cpu_num = 4,

    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x80200000,
            .size = QEMU_VIRT_MEM_REG_SIZE,
        },
    },

    .arch = {

#if (IRQC == PLIC)
        .irqc.plic.base = 0xc000000,
#else
        .irqc.aia.aplic.base = 0xd000000,
        .irqc.aia.imsic.base = 0x28000000,
        .irqc.aia.imsic.num_msis = 255,
        .irqc.aia.imsic.num_guest_files = 1,
#endif

#if (IPIC == IPIC_ACLINT)
        .aclint_sswi.base = 0x2f00000,
#endif
    },

};
