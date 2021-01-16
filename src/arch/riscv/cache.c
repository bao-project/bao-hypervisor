/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <cache.h>
#include <platform.h>

/**
 * The riscv spec does not include cache maintenance. There are current
 * efforts to define and standardize a set of cache management instructions,
 * but for now this is platform dependent.
 */

void cache_arch_enumerate(cache_t* dscrp)
{
    /**
     * Currently the typical of way for system software to discover cache
     * topology is to read it of a dtb passed by the bootloader. As we are not
     * implementing an fdt parser, a platform port must add it to the platform
     * description.
     */
    *dscrp = platform.cache;
}

__attribute__((weak)) void cache_flush_range(void* base, uint64_t size)
{
    /**
     * A platform must define its custom cache flush operation, otherwise
     * certain mechanisms such as coloring and hypervisor relocation will
     * most probably fail.
     */
    WARNING("trying to flush caches but the operation is not defined for this "
            "platform");
}
