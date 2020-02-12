/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <cache.h>

cache_t cache_dscr;

size_t COLOR_NUM = 1;
size_t COLOR_SIZE = 1;

static void cache_calc_colors()
{
    size_t llc = cache_dscr.min_shared_lvl;

    if ((cache_dscr.type[llc] != UNIFIED) ||
        (cache_dscr.indexed[llc][UNIFIED] != PIPT))
        return;

    size_t llc_way_size =
        cache_dscr.numset[llc][UNIFIED] * cache_dscr.line_size[llc][UNIFIED];

    size_t flc_way_size = 0;
    if ((cache_dscr.type[0] != UNIFIED)) {
        flc_way_size = cache_dscr.numset[0][0] * cache_dscr.line_size[0][0];
        size_t flc_i_way_size =
            cache_dscr.numset[0][1] * cache_dscr.line_size[0][1];
        if (((cache_dscr.indexed[0][0] == PIPT) ||
             (flc_i_way_size < flc_way_size)) &&
            (cache_dscr.indexed[0][1] == PIPT)) {
            flc_way_size = flc_i_way_size;
        }
    }

    size_t llc_num_colors = llc_way_size / PAGE_SIZE;
    size_t flc_num_colors = flc_way_size / PAGE_SIZE;

    COLOR_SIZE = flc_num_colors;
    COLOR_NUM = llc_num_colors / COLOR_SIZE;
}

void cache_enumerate()
{
    cache_arch_enumerate();
    cache_calc_colors();
}
