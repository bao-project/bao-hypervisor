/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bitmap.h>

ssize_t bitmap_find_nth(bitmap_t* map, size_t size, size_t nth, size_t start, bool set)
{
    if (size <= 0 || nth <= 0) {
        return -1;
    }

    size_t count = 0;
    unsigned bit = set ? 1 : 0;

    for (size_t i = start; i < size; i++) {
        if (bitmap_get(map, i) == bit) {
            if (++count == nth) {
                return (ssize_t)i;
            }
        }
    }

    return -1;
}

size_t bitmap_count_consecutive(bitmap_t* map, size_t size, size_t start, size_t n)
{
    if ((n == 0) || (start >= size)) {
        return 0;
    }

    size_t limit = (n > (size - start)) ? size : (start + n);
    bool set = bitmap_get(map, start) != 0U;
    bitmap_granule_t full = set ? ~((bitmap_granule_t)0) : 0;
    size_t pos = start;

    while (pos < limit) {
        if (((pos % BITMAP_GRANULE_LEN) == 0) && ((limit - pos) >= BITMAP_GRANULE_LEN) &&
            (map[pos / BITMAP_GRANULE_LEN] == full)) {
            /* A whole granule of the same value inside the window. */
            pos += BITMAP_GRANULE_LEN;
        } else if ((bitmap_get(map, pos) != 0U) == set) {
            pos++;
        } else {
            break;
        }
    }

    return pos - start;
}

ssize_t bitmap_find_consec(bitmap_t* map, size_t size, size_t start, size_t n, bool set)
{
    ssize_t count = 0;
    ssize_t i = 0;

    // find first set
    if ((i = bitmap_find_nth(map, size, 1, start, set)) < 0) {
        return -1;
    }

    while (i < (ssize_t)size) {
        // find the last (with n as maximum) contiguous set page
        count = (ssize_t)bitmap_count_consecutive(map, size, (size_t)i, n);
        if (count < (ssize_t)n) { // if didn't found enough n contiguous set pages
            i += count;
            // find the last contiguous ~set page
            i += (ssize_t)bitmap_count_consecutive(map, size, (size_t)i, SIZE_MAX);
        } else {
            break;
        }
    }

    if (i >= (ssize_t)size) {
        i = -1;
    }

    return i;
}

void bitmap_set_consecutive(bitmap_t* map, size_t start, size_t n)
{
    if (n == 0) {
        return;
    }

    size_t pos = start;
    size_t count = n;
    size_t start_offset = start % BITMAP_GRANULE_LEN;
    size_t first_word_bits = min(BITMAP_GRANULE_LEN - start_offset, count);

    map[pos / BITMAP_GRANULE_LEN] |= BITMAP_GRANULE_MASK(start_offset, first_word_bits);
    pos += first_word_bits;
    count -= first_word_bits;

    while (count >= BITMAP_GRANULE_LEN) {
        map[pos / BITMAP_GRANULE_LEN] |= ~((bitmap_granule_t)0);
        pos += BITMAP_GRANULE_LEN;
        count -= BITMAP_GRANULE_LEN;
    }

    if (count > 0) {
        map[pos / BITMAP_GRANULE_LEN] |= BITMAP_GRANULE_MASK(0, count);
    }
}
