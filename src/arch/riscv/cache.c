/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cache.h>
#include <platform.h>

/**
 * The riscv spec does not include cache maintenance. There are current
 * efforts to define and standardize a set of cache management instructions,
 * but for now this is platform dependent.
 */

void cache_arch_enumerate(struct cache* dscrp)
{
    /**
     * Currently the typical of way for system software to discover cache
     * topology is to read it of a dtb passed by the bootloader. As we are not
     * implementing an fdt parser, a platform port must add it to the platform
     * description.
     */
    *dscrp = platform.cache;
}

__attribute__((weak)) void cache_flush_range(vaddr_t base, size_t size)
{
    /**
     * A platform must define its custom cache flush operation, otherwise
     * certain mechanisms such as coloring and hypervisor relocation will
     * most probably fail.
     */
    WARNING("trying to flush caches but the operation is not defined for this "
            "platform");
}
