/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aborts.h>
#include <arch/sysregs.h>
#include <cpu.h>

/* SAVE_HYP_GPRS stores x0-x30 and then the pre-exception sp: gprs[n] is x<n>. */
#define HYP_GPRS_X_NUM (31)
#define HYP_GPRS_SP    (HYP_GPRS_X_NUM)

static void internal_abort_print_regs(unsigned long gprs[])
{
    for (size_t i = 0; i < HYP_GPRS_X_NUM; i++) {
        console_printk("x%zu:\t\t0x%0lx\n", i, gprs[i]);
    }
    console_printk("SP:\t\t0x%0lx\n", gprs[HYP_GPRS_SP]);
    console_printk("ELR:\t0x%0lx\n", sysreg_elr_el2_read());
}

void internal_abort_handler(unsigned long gprs[])
{
    internal_abort_print_regs(gprs);
    console_printk("ESR:\t0x%0lx\n", sysreg_esr_el2_read());
    console_printk("FAR:\t0x%0lx\n", sysreg_far_el2_read());
    ERROR("cpu%lu internal hypervisor abort - PANIC\n", cpu()->id);
}

/* Entered only from the EL2 IRQ and FIQ vectors in exceptions.S. */
void internal_irq_abort_handler(unsigned long gprs[]);

/**
 * IRQ and FIQ are asynchronous and update neither ESR_EL2 nor FAR_EL2, so the values an earlier
 * exception left there are not printed.
 */
void internal_irq_abort_handler(unsigned long gprs[])
{
    internal_abort_print_regs(gprs);
    ERROR("cpu%lu interrupt taken in the hypervisor - PANIC\n", cpu()->id);
}
