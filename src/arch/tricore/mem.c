/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>

#include <platform.h>
#include <cpu.h>

void as_arch_init(struct addr_space* as)
{
    UNUSED_ARG(as);
}

size_t mpu_granularity(void)
{
    return (size_t)PAGE_SIZE;
}
