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
    }

}
