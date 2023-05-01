/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <bao.h>
#include <bit.h>

/* TODO: needs optimizations */

typedef uint32_t bitmap_granule_t;
typedef bitmap_granule_t bitmap_t;

static const bitmap_granule_t ONE = 1;

#define BITMAP_GRANULE_LEN (sizeof(bitmap_granule_t) * 8)
#define BITMAP_GRANULE_MASK(O, L)   BIT32_MASK((O), (L))

#define BITMAP_SIZE(SIZE) (((SIZE) / BITMAP_GRANULE_LEN) + \
                          ((SIZE) % BITMAP_GRANULE_LEN ? 1 : 0))

#define BITMAP_ALLOC(NAME, SIZE) bitmap_granule_t NAME[BITMAP_SIZE((SIZE))]

#define BITMAP_ALLOC_ARRAY(NAME, SIZE ,NUM) \
    bitmap_granule_t NAME[NUM][BITMAP_SIZE((SIZE))]


static inline void bitmap_set(bitmap_t* map, size_t bit)
{
    map[bit / BITMAP_GRANULE_LEN] |= ONE << (bit % BITMAP_GRANULE_LEN);
}

static inline void bitmap_clear(bitmap_t* map, size_t bit)
{
    map[bit / BITMAP_GRANULE_LEN] &= ~(ONE << (bit % BITMAP_GRANULE_LEN));
}

static inline unsigned bitmap_get(bitmap_t* map, size_t bit)
{
    return (map[bit / BITMAP_GRANULE_LEN] & (ONE << (bit % BITMAP_GRANULE_LEN)))
               ? 1U
               : 0U;
}

void bitmap_set_consecutive(bitmap_t* map, size_t start, size_t n);

static inline void bitmap_clear_consecutive(bitmap_t* map, size_t start,
                                            size_t n)
{
    for (size_t i = 0; i < n; i++) bitmap_clear(map, start + i);
}

static inline size_t bitmap_count(bitmap_t* map, size_t start, size_t n,
                                    bool set)
{
    size_t count = 0;
    for (size_t i = start; i < n; i++) {
        if (bitmap_get(map, i) == set) count++;
    }

    return count;
}

ssize_t bitmap_find_nth(bitmap_t* map, size_t size, size_t nth, size_t start,
                        bool set);

size_t bitmap_count_consecutive(bitmap_t* map, size_t size, size_t start,
                                size_t n);

ssize_t bitmap_find_consec(bitmap_t* map, size_t size, size_t start, size_t n,
                            bool set);

#endif /* __BITMAP_H__ */
