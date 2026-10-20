/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cache.h>

static struct cache cache_dscr;

size_t COLOR_NUM = 1;
size_t COLOR_SIZE = 1;

static void cache_calc_colors(struct cache* dscrp, size_t page_size)
{
    if (dscrp->lvls == 0) {
        /* No cache? */
        return;
    }

    size_t llc = dscrp->min_shared_lvl;

    if ((dscrp->type[llc] != UNIFIED) || (dscrp->indexed[llc][0] != PIPT)) {
        return;
    }

    size_t llc_way_size = dscrp->numset[llc][UNIFIED] * dscrp->line_size[llc][UNIFIED];

    size_t flc_way_size = 0;
    if (dscrp->type[0] != UNIFIED) {
        flc_way_size = dscrp->numset[0][0] * dscrp->line_size[0][0];
        size_t flc_i_way_size = dscrp->numset[0][1] * dscrp->line_size[0][1];
        if (((dscrp->indexed[0][0] == PIPT) || (flc_i_way_size < flc_way_size)) &&
            (dscrp->indexed[0][1] == PIPT)) {
            flc_way_size = flc_i_way_size;
        }
    }

    size_t llc_num_colors = llc_way_size / page_size;
    size_t flc_num_colors = flc_way_size / page_size;

    /* A unified first level, or a first-level way smaller than a page, does not constrain the
     * colouring; a last-level way smaller than the first-level one leaves a single colour. */
    if (flc_num_colors == 0) {
        flc_num_colors = 1;
    }
    if (llc_num_colors < flc_num_colors) {
        return;
    }

    COLOR_SIZE = flc_num_colors;
    COLOR_NUM = llc_num_colors / COLOR_SIZE;
}

void cache_enumerate(void)
{
    cache_arch_enumerate(&cache_dscr);
    cache_calc_colors(&cache_dscr, PAGE_SIZE);
}
