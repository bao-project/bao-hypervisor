/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cache.h>
#include <platform.h>

void cache_arch_enumerate(struct cache* dscrp)
{
    /* Cache operations not currently supported in TC4 */

    UNUSED_ARG(dscrp);
}

__attribute__((weak)) void cache_flush_range(vaddr_t base, size_t size)
{
    /* Cache operations not currently supported in TC4 */

    UNUSED_ARG(base);
    UNUSED_ARG(size);
}
