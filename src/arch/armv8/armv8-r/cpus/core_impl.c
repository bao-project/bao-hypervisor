/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/sysregs.h>
#include <arch/core_impl.h>

#define ARMV8R_R52_PARTNUMBER 0xD13

/* Weak references to CPU implementation init functions */
extern void cortex_r52_impl_init(void) __attribute__((weak));

void cpu_arch_core_impl_init(void)
{
    /* Read MIDR to identify core implementation */
    unsigned long midr = sysreg_midr_el1_read();
    uint32_t part_num = MIDR_EL1_PARTNUM(midr);

    switch (part_num) {
        case ARMV8R_R52_PARTNUMBER: /* Cortex-R52 */
            if (cortex_r52_impl_init != NULL) {
                cortex_r52_impl_init();
            }
            break;
        default:
            break;
    }
}
