/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bitmap.h>

ssize_t bitmap_find_nth(bitmap_t* map, size_t size, size_t nth, size_t start,
                        bool set)
{
    if (size <= 0 || nth <= 0 || start < 0) return -1;

    size_t count = 0;
    unsigned bit = set ? 1 : 0;

    for (ssize_t i = start; i < size; i++) {
        if (bitmap_get(map, i) == bit) {
            if (++count == nth) return i;
        }
    }

    return -1;
}

size_t bitmap_count_consecutive(bitmap_t* map, size_t size, size_t start,
                                size_t n)
{
    if (n <= 1) return n;

    unsigned b = bitmap_get(map, start);
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

ssize_t bitmap_find_consec(bitmap_t* map, size_t size, size_t start, size_t n,
                            bool set)
{
    ssize_t count = 0;
    ssize_t i = 0;

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
