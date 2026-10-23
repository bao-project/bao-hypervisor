/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>

#include <cpu.h>
#include <mem.h>
#include <interrupts.h>
#include <console.h>
#include <earlycon.h>
#include <printk.h>
#include <platform.h>
#include <vmm.h>

void init(cpuid_t cpu_id)
{
    /**
     * These initializations must be executed first and in fixed order.
     */

#ifdef CONFIG_EARLYCON
    // Initialize the early console to be able to print messages in case of failure.
    earlycon_init(cpu_id);
#endif

    cpu_init(cpu_id);
    mem_init();

    /* -------------------------------------------------------------- */

    platform_init();

    console_init();

#ifdef CONFIG_EARLYCON
    /* Publish the normal console and finish early output before retiring its resources. */
    cpu_sync_and_clear_msgs(&cpu_glb_sync);

    earlycon_disable();
#endif

    if (cpu_is_master()) {
        console_printk("Bao Hypervisor %s (%s - %s)\n\r", BAO_VERSION, __DATE__, __TIME__);
    }

    interrupts_init();

    vmm_init();

    /* Should never reach here */
    while (1) { }
}
