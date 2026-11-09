/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <earlycon.h>

__attribute__((weak)) void earlycon_init(cpuid_t cpu_id)
{
    UNUSED_ARG(cpu_id);
}

__attribute__((weak)) void earlycon_disable(void)
{
}

/* Platforms without an early-console driver silently discard output. */
__attribute__((weak)) void earlycon_putchar(char c)
{
    UNUSED_ARG(c);
}
