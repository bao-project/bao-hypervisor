/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cache.h>
#include <platform.h>
#include <arch/fences.h>
#include <arch/cpu.h>

/**
 * RISC-V does not yet define a standard architectural mechanism to discover
 * cache topology (e.g., number of levels, associativity, sets).
 *
 * In practice, system software obtains this information from platform-specific
 * sources such as the device tree (DTB) provided by the bootloader. Since we
 * do not parse the DTB here, cache topology must be supplied by the platform.
 *
 */
void cache_arch_enumerate(struct cache* dscrp)
{
    /**
     * The platform is responsible for populating cache topology information.
     */
    *dscrp = platform.cache;
}

#if CPU_HAS_EXTENSION(CPU_EXT_ZICBOM)

/**
 * Flush a range of memory from the cache using the RISC-V Zicbom extension.
 *
 * The Zicbom extension provides standard cache-block management operations
 * (cbo.clean, cbo.flush, cbo.inval), which operate on the cache block
 * containing the specified address.
 *
 * With the Zic64b extension, cache blocks are architecturally defined as
 * 64 bytes and naturally aligned. This allows software to use a fixed block
 * size (CACHE_BLOCK_SIZE = 64).
 *
 * Implementations may use different internal cache organizations, but must
 * preserve compatibility with 64-byte cache blocks from the software
 * perspective.
 *
 * This implementation uses conservative memory ordering by placing fences
 * before and after the flush operations to ensure correct visibility with
 * respect to other harts.
 */
void cache_flush_range(vaddr_t base, size_t size)
{
    if (size == 0U) {
        return;
    }

    vaddr_t base_addr = base;
    vaddr_t end_addr = base + size;
    size_t blk_size = CACHE_BLOCK_SIZE;

    while (base_addr < end_addr) {
        cbo_flush(base_addr);
        base_addr += blk_size;
    }

    /* Ensure flush operations are ordered before subsequent accesses. */
    fence_ord();
}
#else

/**
 * Cache maintenance is not supported on this platform.
 *
 * If the Zicbom extension is not implemented, RISC-V provides no standard
 * mechanism for cache-block management. Platforms must provide their own
 * implementation if cache maintenance is required.
 *
 * This weak definition acts as a fallback and should be overridden by
 * platform-specific code.
 */
__attribute__((weak)) void cache_flush_range(vaddr_t base, size_t size)
{
    /**
     * A platform must define its custom cache flush operation, otherwise certain mechanisms such
     * as coloring and hypervisor relocation will most probably fail.
     */

    UNUSED_ARG(base);
    UNUSED_ARG(size);

    WARNING("trying to flush caches but no cache maintenance support is available on this"
            "platform\n");
}
#endif
