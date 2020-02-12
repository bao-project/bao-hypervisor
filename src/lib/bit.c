/**
 * Bao, a Lightweight Static Partitioning Hypervisor
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

#include <bit.h>

uint64_t bit_ctz64(uint64_t n)
{
    uint64_t i = 0;

    for (i = 0; i < sizeof(n) * 8; i++) {
        if ((n >> i) & 0x1) return i;
    }

    return i;
}

uint64_t bit_clz64(uint64_t n)
{
    uint64_t i = 0, j;

    for (i = (sizeof(n) * 8) - 1, j = 0; i >= 0; i--, j++) {
        if ((n >> i) & 0x1) return j;
    }

    return j;
}

uint32_t bit_ctz32(uint32_t n)
{
    uint32_t i = 0;

    for (i = 0; i < sizeof(n) * 8; i++) {
        if ((n >> i) & 0x1) return i;
    }

    return i;
}

uint32_t bit_clz32(uint32_t n)
{
    uint32_t i = 0, j;

    for (i = (sizeof(n) * 8) - 1, j = 0; i >= 0; i--, j++) {
        if ((n >> i) & 0x1) return j;
    }

    return j;
}
