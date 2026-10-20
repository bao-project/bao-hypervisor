/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aborts.h>
#include <arch/sysregs.h>
#include <cpu.h>

/**
 * SAVE_HYP_GPRS pushes r0-r12 and then the pre-exception sp and lr, so gprs[0] is sp, gprs[1] is
 * lr and gprs[2 + n] is r<n>.
 */
void internal_abort_handler(unsigned long gprs[])
{
    for (size_t i = 0; i < 13; i++) {
        console_printk("r%zu:\t\t0x%0lx\n", i, gprs[2 + i]);
    }
    console_printk("SP:\t\t0x%0lx\n", gprs[0]);
    console_printk("LR:\t\t0x%0lx\n", gprs[1]);
    console_printk("ESR:\t0x%0lx\n", sysreg_esr_el2_read());
    console_printk("ELR:\t0x%0lx\n", sysreg_elr_el2_read());
    console_printk("FAR:\t0x%0lx\n", sysreg_far_el2_read());
    ERROR("cpu%lu internal hypervisor abort - PANIC\n", cpu()->id);
}
