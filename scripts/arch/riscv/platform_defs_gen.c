/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <platform.h>

void arch_platform_defs() {

    if (platform.arch.aclint_sswi.base != 0) {
        printf("#define ACLINT_SSWI 1\n");
    }

    if (IRQC == AIA) {
        printf("#define PLAT_IMSIC_MAX_INTERRUPTS %ld\n", platform.arch.irqc.aia.imsic.num_msis);

        /**
         * This calculation follows the rules for the arrangement of memory regions for multiple
         * interrupt files defined in section 3.6 of "The RISC-V Advanced Interrupt Architecture"
         * version 1.0, with the smallest constant D as defined by the spec.
         */
        size_t num_addr_bits = 0;
        while ((1UL << num_addr_bits) < (platform.arch.irqc.aia.imsic.num_guest_files + 1)) {
            num_addr_bits += 1;
        }
        printf("#define PLAT_IMSIC_HART_SIZE (%ld)\n", ((1UL << (num_addr_bits)) * PAGE_SIZE));
    }

}
