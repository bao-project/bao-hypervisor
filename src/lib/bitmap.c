/**
 * SPDX-License-Identifier: Apache-2.0
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
    size_t pos = start;
    size_t count = 0;
    size_t start_offset = start % BITMAP_GRANULE_LEN;
    size_t first_word_bits = min(BITMAP_GRANULE_LEN - start_offset, n);
    bool set = !!bitmap_get(map, start);
    bitmap_granule_t init_mask = BITMAP_GRANULE_MASK(start_offset, first_word_bits);
    bitmap_granule_t mask;

    if (n <= 1) return n;

    mask = set ? init_mask : ~init_mask;
    if (!((map[pos/BITMAP_GRANULE_LEN] ^ mask) & init_mask)) {
        count += first_word_bits;
        pos += first_word_bits;
    }

    mask = set ? ~0 : 0;
    while ((pos < size) && !(map[pos/BITMAP_GRANULE_LEN] ^ mask) && (count < n)) {
        count += BITMAP_GRANULE_LEN;
        pos += BITMAP_GRANULE_LEN;
    }

    while ((pos < size) && (!!bitmap_get(map, pos) == set) && (count < n)) {
        count++;
        pos += 1;
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

void bitmap_set_consecutive(bitmap_t* map, size_t start, size_t n)
{
    size_t pos = start;
    size_t count = n;
    size_t start_offset = start % BITMAP_GRANULE_LEN;
    size_t first_word_bits = min(BITMAP_GRANULE_LEN - start_offset, count); 

    map[pos/BITMAP_GRANULE_LEN] |= BITMAP_GRANULE_MASK(start_offset, first_word_bits);
    pos += first_word_bits;
    count -= first_word_bits;

    while (count >= BITMAP_GRANULE_LEN) {
        map[pos/BITMAP_GRANULE_LEN] |= ~0;
        pos += BITMAP_GRANULE_LEN;
        count -= BITMAP_GRANULE_LEN;
    }

    if (count > 0) {
        map[pos/BITMAP_GRANULE_LEN] |= BITMAP_GRANULE_MASK(0, count);
    }
}
