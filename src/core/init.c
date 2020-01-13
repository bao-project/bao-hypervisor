/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
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

void init(uint64_t cpu_id, uint64_t load_addr, uint64_t config_addr)
{
    /**
     * These initializations must be executed first and in fixed order.
     */

    cpu_init(cpu_id, load_addr);
    mem_init(load_addr, config_addr);

    /* -------------------------------------------------------------- */

    if (cpu.id == CPU_MASTER) {
        console_init();
        printk("Bao Hypervisor\n\r");
    }

    interrupts_init();

    vmm_init();

    /* Should never reach here */
    while (1);
}
