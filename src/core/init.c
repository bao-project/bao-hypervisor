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

/* DEBUG: direct putc to the physical K3 UART0, reachable post-MMU via the
 * identity gigapage installed in boot.S. reg-shift=2 => 4-byte stride => uint32
 * index N hits register N (LSR=5, THR=0). Removed once Bao boots. */
static inline void k3_dbg_putc(char ch)
{
    volatile uint32_t* uart = (volatile uint32_t*)0xd4017000UL;
    while ((uart[5] & 0x20U) == 0U) { }
    uart[0] = (uint32_t)ch;
}

void init(cpuid_t cpu_id)
{
    /**
     * These initializations must be executed first and in fixed order.
     */

    k3_dbg_putc('a');   /* entered init() (post-MMU C) */
    cpu_init(cpu_id);
    k3_dbg_putc('b');   /* cpu_init done (secondaries started) */
    mem_init();
    k3_dbg_putc('c');   /* mem_init done */

    /* -------------------------------------------------------------- */

    platform_init();
    k3_dbg_putc('d');   /* platform_init done */

    console_init();
    k3_dbg_putc('e');   /* console_init done */

    if (cpu_is_master()) {
        console_printk("Bao Hypervisor %s (%s - %s)\n\r", BAO_VERSION, __DATE__, __TIME__);
    }

    interrupts_init();

    vmm_init();

    /* Should never reach here */
    while (1) { }
}
