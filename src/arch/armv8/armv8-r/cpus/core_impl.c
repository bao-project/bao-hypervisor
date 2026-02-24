/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/sysregs.h>
#include <arch/core_impl.h>

void cpu_arch_core_impl_init(void)
{
    /* Read MIDR to identify core implementation */
    unsigned long midr = sysreg_midr_el1_read();
    uint32_t part_num = MIDR_EL1_PARTNUM(midr);

    switch (part_num) {
        default:
            break;
    }
}
