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

void cache_arch_enumerate(cache_t* dscrp)
{
    dscrp->lvls = 0;  // no cache

    /**
     * TODO: In riscv cache description will probably be part of a dtb
     * passed by the bootloader. For now we have no support for dtb
     * parsing, but this means we might have to. An alternative would be
     * to add it to our platform description (which could be done for all
     * architectures).
     */
}

void cache_flush_range(void* base, uint64_t size)
{
    /**
     * TODO: the spec does not include cache maintenance. In riscv, in the
     * future this function might have to be implemented by platform or
     * through an sbi call.
     */
}