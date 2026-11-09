/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <earlycon.h>
#include <cpu.h>
#include <fences.h>
#include <mem.h>

static volatile bool early_uart_ready;

__attribute__((weak)) void earlycon_platform_init(void)
{
}

void earlycon_init(cpuid_t cpu_id)
{
    if (cpu_id == CPU_MASTER) {
        earlycon_platform_init();
        earlycon_uart_init((void*)EARLY_CONSOLE_VA);
        fence_sync_write();
        early_uart_ready = true;
    }

    /* One-way boot barrier: the boot CPU must not wait for secondary CPUs. */
    while (!early_uart_ready) { }
    fence_sync_read();
}

void earlycon_disable(void)
{
    early_uart_ready = false;
    fence_sync_write();
    mem_unmap_early_devices();
}

void earlycon_putchar(char c)
{
    /* Fault reporting must not wait for an initializer that may have faulted. */
    if (early_uart_ready) {
        fence_sync_read();
        earlycon_uart_putc((void*)EARLY_CONSOLE_VA, c);
    }
}
