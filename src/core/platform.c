/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

__attribute__((weak)) void platform_default_init(void) { }

__attribute__((weak)) void platform_config_init(void) { }

__attribute__((weak)) void plat_cpu_init(cpuid_t cpuid, paddr_t load_addr)
{
    UNUSED_ARG(cpuid);
    UNUSED_ARG(load_addr);
    return;
}

void platform_init(void)
{
    platform_default_init();
    platform_config_init();
}
