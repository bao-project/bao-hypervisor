/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __EARLYCON_H__
#define __EARLYCON_H__

#include <bao.h>

#ifdef EARLY_CONSOLE_UART
#include <platform_defs.h>
#define EARLY_CONSOLE_BASE PLAT_CONSOLE_BASE
#ifdef MEM_PROT_MMU
/* Last page covered by the image's existing bootstrap L3 table. */
#define EARLY_CONSOLE_VA (BAO_VAS_BASE + 0x1ff000)
#else
#define EARLY_CONSOLE_VA EARLY_CONSOLE_BASE
#endif
#endif

#ifndef __ASSEMBLER__

#ifdef EARLY_CONSOLE_UART

/* Driver setup for polling output, with peripheral interrupts disabled. */
void earlycon_uart_init(void* base);
void earlycon_uart_putc(void* base, char c);
/* Boot CPU only, before allocation and MPU enable; firmware prerequisites apply. */
void earlycon_platform_init(void);
#endif

/*
 * Optional setup hook called on every CPU after early trap setup, before cpu_init().
 * Use cpu_id to coordinate shared hardware setup; cpu()->id is not initialized yet.
 * Any MMIO mapping must be accessible before the hook touches the device.
 * The weak default does nothing.
 */
void earlycon_init(cpuid_t cpu_id);

/*
 * Optional output hook, usable after earlycon_init() with a valid C runtime.
 * Must not depend on console_init(), allocation, or the normal console lock.
 * MMIO implementations must provide an accessible device mapping and a working
 * transmitter before this point. The weak default silently drops output.
 */
void earlycon_putchar(char c);

/*
 * Called on every CPU after normal-console publication and a global barrier.
 * Retire resources still owned by earlycon; preserve those used by the console.
 * No earlycon_putchar() calls may remain in flight or start after this point.
 * The weak default does nothing.
 */
void earlycon_disable(void);

#endif /* __ASSEMBLER__ */

#endif /* __EARLYCON_H__ */
