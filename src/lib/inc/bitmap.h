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

#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <bao.h>
#include <bit.h>

/* TODO: needs optimizations */

typedef uint32_t bitmap_granule_t;
typedef bitmap_granule_t* bitmap_t;

static const bitmap_granule_t ONE = 1;

#define BITMAP_GRANULE_LEN (sizeof(bitmap_granule_t) * 8)

#define BITMAP_ALLOC(NAME, SIZE)                        \
    bitmap_granule_t NAME[(SIZE / BITMAP_GRANULE_LEN) + \
                          (SIZE % BITMAP_GRANULE_LEN ? 1 : 0)]

#define BITMAP_ALLOC_ARRAY(NAME, SIZE ,NUM)                     \
    bitmap_granule_t NAME[NUM][(SIZE / BITMAP_GRANULE_LEN) +    \
                          (SIZE % BITMAP_GRANULE_LEN ? 1 : 0)]


static inline void bitmap_set(bitmap_t map, size_t bit)
{
    map[bit / BITMAP_GRANULE_LEN] |= ONE << (bit % BITMAP_GRANULE_LEN);
}

static inline void bitmap_clear(bitmap_t map, size_t bit)
{
    map[bit / BITMAP_GRANULE_LEN] &= ~(ONE << (bit % BITMAP_GRANULE_LEN));
}

static inline uint64_t bitmap_get(bitmap_t map, size_t bit)
{
    return (map[bit / BITMAP_GRANULE_LEN] & (ONE << (bit % BITMAP_GRANULE_LEN)))
               ? 1U
               : 0U;
}

static inline void bitmap_set_consecutive(bitmap_t map, size_t start, size_t n)
{
    for (size_t i = 0; i < n; i++) bitmap_set(map, start + i);
}

static inline void bitmap_clear_consecutive(bitmap_t map, size_t start,
                                            size_t n)
{
    for (size_t i = 0; i < n; i++) bitmap_clear(map, start + i);
}

static inline uint64_t bitmap_count(bitmap_t map, size_t start, size_t n,
                                    bool set)
{
    uint64_t count = 0;
    for (int i = start; i < n; i++) {
        if (bitmap_get(map, i) == set) count++;
    }

    return count;
}

int64_t bitmap_find_nth(bitmap_t map, size_t size, size_t nth, size_t start,
                        bool set);

size_t bitmap_count_consecutive(bitmap_t map, size_t size, size_t start,
                                size_t n);

uint64_t bitmap_find_consec(bitmap_t map, size_t size, size_t start, size_t n,
                            bool set);

#endif /* __BITMAP_H__ */
