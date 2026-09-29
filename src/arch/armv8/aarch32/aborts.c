/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aborts.h>
#include <arch/sysregs.h>

/**
 * SAVE_HYP_GPRS pushes r0-r12 and then the pre-exception sp and lr, so gprs[0] is sp, gprs[1] is
 * lr and gprs[HYP_GPRS_R0 + n] is r<n>.
 */
#define HYP_GPRS_R0    (2)
#define HYP_GPRS_R_NUM (13)

void internal_abort_handler(unsigned long gprs[])
{
    for (size_t i = 0; i < HYP_GPRS_R_NUM; i++) {
        console_printk_unlocked("r%zu:\t\t0x%0lx\n", i, gprs[HYP_GPRS_R0 + i]);
    }
    console_printk_unlocked("SP:\t\t0x%0lx\n", gprs[0]);
    console_printk_unlocked("LR:\t\t0x%0lx\n", gprs[1]);
    console_printk_unlocked("ESR:\t0x%0lx\n", sysreg_esr_el2_read());
    console_printk_unlocked("ELR:\t0x%0lx\n", sysreg_elr_el2_read());
    console_printk_unlocked("FAR:\t0x%0lx\n", sysreg_far_el2_read());
    ERROR("internal hypervisor abort\n");
}
