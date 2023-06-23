/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/sysregs.h>

__attribute__((weak)) void vmm_arch_implementation_init()
{
    sysreg_cntfrq_el0_write(0x14000);
}
