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

size_t bit_ctz(uint64_t n)
{
    int i = 0;

    for (i = 0; i < sizeof(n) * 8; i++) {
        if ((n >> i) & 0x1) return i;
    }

    return i;
}

size_t bit_clz(uint64_t n)
{
    int i = 0, j;

    for (i = (sizeof(n) * 8) - 1, j = 0; i >= 0; i--, j++) {
        if ((n >> i) & 0x1) return j;
    }

    return j;
}