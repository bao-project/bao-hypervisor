/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aborts.h>
#include <arch/sysregs.h>
#include <cpu.h>

void internal_abort_handler(unsigned long gprs[])
{
    for (ssize_t i = 14; i >= 0; i--) {
        console_printk_unlocked("x%ld:\t\t0x%0lx\n", i, gprs[14 - i]);
    }
    console_printk_unlocked("ESR:\t0x%0lx\n", sysreg_esr_el2_read());
    console_printk_unlocked("ELR:\t0x%0lx\n", sysreg_elr_el2_read());
    console_printk_unlocked("FAR:\t0x%0lx\n", sysreg_far_el2_read());
    ERROR("cpu%lu internal hypervisor abort - PANIC\n", cpu()->id);
}

/* Called only after stack/BSS setup; no vCPU or CPU ID is required. */
__attribute__((noreturn)) void early_internal_exception_handler(unsigned long vector);
void early_internal_exception_handler(unsigned long vector)
{
    unsigned long status;
    __asm__ volatile("mrs %0, SPSR_hyp" : "=r"(status));
    unsigned long far = (vector == 3) ? sysreg_hifar_read() : sysreg_far_el2_read();
    ERROR("early hypervisor abort: vector=0x%lx ESR=0x%lx ELR=0x%lx "
                "SPSR=0x%lx FAR=0x%lx\n",
        vector, sysreg_esr_el2_read(), sysreg_elr_el2_read(), status, far);
}
