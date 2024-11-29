/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cache.h>
#include <platform.h>

/**
 * The riscv spec does not include cache maintenance. There are current efforts to define and
 * standardize a set of cache management instructions, but for now this is platform dependent.
 */

void cache_arch_enumerate(struct cache* dscrp)
{
    UNUSED_ARG(dscrp);
}

__attribute__((weak)) void cache_flush_range(vaddr_t base, size_t size)
{
    UNUSED_ARG(base);
    UNUSED_ARG(size);
}
