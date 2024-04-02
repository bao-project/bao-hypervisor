/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/sysregs.h>

__attribute__((weak)) void vmm_arch_implementation_init()
{
    unsigned long const VALUE = 0x100;
    unsigned long reg = sysreg_actlr_el2_read();
    sysreg_actlr_el2_write((reg|VALUE));
    //sysreg_cntfrq_el0_write(0x14000); // 1s
    // Clock_Ip_Init(Clock_Ip_aClockConfig); 
}
