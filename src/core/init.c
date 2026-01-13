/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file init.c
 * @brief This source file implements the CPUs initialization sequence.
 * 
 */

#include <bao.h>

#include <cpu.h>
#include <mem.h>
#include <interrupts.h>
#include <console.h>
#include <printk.h>
#include <platform.h>
#include <vmm.h>

/**
 * @brief CPU initialization entry point from boot code
 *
 * Performs the complete hypervisor initialization sequence.
 * The order of the initialization is critical:
 * 1. CPU and memory subsystem initialization
 * 2. Platform-specific initialization
 * 3. Console setup (master CPU prints banner)
 * 4. Interrupt subsystem initialization
 * 5. Virtual Machine Monitor initialization
 * 
 * @param cpu_id ID of the CPU being initialized
 * 
 * @see cpu_init(), mem_init(), platform_init(), console_init(), interrupts_init()
 * @see vmm_init(), cpu_is_master(), console_printk(), cpuid_t
 * 
 * @note This function should never return. If it does, the CPU enters an infinite loop.
 * 
 */
void init(cpuid_t cpu_id)
{
    /**
     * These initializations must be executed first and in fixed order.
     */

    cpu_init(cpu_id);
    mem_init();

    /* -------------------------------------------------------------- */

    platform_init();

    console_init();

    if (cpu_is_master()) {
        console_printk("Bao Hypervisor\n\r");
    }

    interrupts_init();

    vmm_init();

    /* Should never reach here */
    while (1) { }
}
