/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>

#include <cpu.h>
#include <mem.h>
#include <interrupts.h>
#include <console.h>
#include <printk.h>
#include <platform.h>
#include <vmm.h>

void init(cpuid_t cpu_id)
{
    /**
     * These initializations must be executed first and in fixed order.
     */

    cpu_init(cpu_id);
    mem_init();

    /* -------------------------------------------------------------- */

    console_init();

    if (cpu_is_master()) {
        console_printk("Bao Hypervisor\n\r");
    }

    interrupts_init();

    vmm_init();

    /* Should never reach here */
    while (1) { }
}
