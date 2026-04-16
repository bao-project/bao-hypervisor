/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * @file platform.c
 * @brief This source file defines placeholder for the platform-specific initialization procedures.
 */

#include <platform.h>

/**
 * @brief Not implemented. Platform-specific default initialization.
 * @note It shall be defined by the platform-specific code.
 */
__attribute__((weak)) void platform_default_init(void) { }

/**
 * @brief Not implemented. Platform-specific configuration initialization.
 * @note It shall be defined by the platform-specific code.
 */
__attribute__((weak)) void platform_config_init(void) { }

/**
 * @brief Not implemented. Platform-specific configuration initialization.
 * @param cpuid Unused.
 * @param load_addr Unused.
 * @note It shall be defined by the platform-specific code.
 */
__attribute__((weak)) void plat_cpu_init(cpuid_t cpuid, paddr_t load_addr)
{
    UNUSED_ARG(cpuid);
    UNUSED_ARG(load_addr);
    return;
}

/**
 * @brief Initialize platform-specific hardware and settings
 * @note Its execution relies on the platform-specific implementation.
 * @see platform_default_init(), platform_config_init()
 */
void platform_init(void)
{
    platform_default_init();
    platform_config_init();
}
