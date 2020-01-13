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

#include <bitmap.h>

int64_t bitmap_find_nth(bitmap_t map, size_t size, size_t nth, size_t start,
                        bool set)
{
    if (size <= 0 || nth <= 0 || start < 0) return -1;

    size_t count = 0;
    uint64_t bit = set ? 1 : 0;

    for (size_t i = start; i < size; i++) {
        if (bitmap_get(map, i) == bit) {
            if (++count == nth) return i;
        }
    }

    return -1;
}

size_t bitmap_count_consecutive(bitmap_t map, size_t size, size_t start,
                                size_t n)
{
    if (n <= 1) return n;

    uint8_t b = bitmap_get(map, start);
    size_t count = 1;
    start += 1;

    while (start < size) {
        if (bitmap_get(map, start) == b)
            count++;
        else
            break;
        if (count == n) break;
        start++;
    }

    return count;
}

uint64_t bitmap_find_consec(bitmap_t map, size_t size, size_t start, size_t n,
                            bool set)
{
    uint64_t count = 0;
    int64_t i = 0;

    // find first set
    if ((i = bitmap_find_nth(map, size, 1, start, set)) < 0) return -1;

    while (i < size) {
        // find the last (with n as maximum) contiguous set page
        count = bitmap_count_consecutive(map, size, i, n);
        if (count < n) {  // if didn't found enough n contiguous set pages
            i += count;
            // find the last contiguous ~set page
            i += bitmap_count_consecutive(map, size, i, -1);
        } else {
            break;
        }
    }

    if (i >= size) i = -1;

    return i;
}
