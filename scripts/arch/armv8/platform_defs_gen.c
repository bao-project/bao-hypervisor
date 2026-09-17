/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <stdbool.h>

/**
 * The armv8-r boot code places each cpu's structure through the generated base table. The armv8-a
 * boot code lays the structures out after the image and maps them through the MMU instead.
 */
bool arch_cpu_private_placement(void)
{
#ifdef MEM_PROT_MPU
    return true;
#else
    return false;
#endif
}
