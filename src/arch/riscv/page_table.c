/**
 * Bao Hypervisor
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

#include <bao.h>
#include <page_table.h>

#if (SV32)
page_table_dscr_t sv32_pt_dscr = {.lvls = 2,
                                  .lvl_wdt = (size_t[]){32, 22},
                                  .lvl_off = (size_t[]){22, 12},
                                  .lvl_term = (bool[]){true, true}};
page_table_dscr_t sv32x4_pt_dscr = {.lvls = 2,
                                    .lvl_wdt = (size_t[]){34, 22},
                                    .lvl_off = (size_t[]){22, 12},
                                    .lvl_term = (bool[]){true, true}};
page_table_dscr_t* hyp_pt_dscr = &sv32_pt_dscr;
page_table_dscr_t* vm_pt_dscr = &sv32x2_pt_dscr;
#elif (RV64)
page_table_dscr_t sv39_pt_dscr = {.lvls = 3,
                                  .lvl_wdt = (size_t[]){39, 30, 21},
                                  .lvl_off = (size_t[]){30, 21, 12},
                                  .lvl_term = (bool[]){true, true, true}};
page_table_dscr_t sv39x4_pt_dscr = {.lvls = 3,
                                    .lvl_wdt = (size_t[]){41, 30, 21},
                                    .lvl_off = (size_t[]){30, 21, 12},
                                    .lvl_term = (bool[]){true, true, true}};
page_table_dscr_t* hyp_pt_dscr = &sv39_pt_dscr;
page_table_dscr_t* vm_pt_dscr = &sv39x4_pt_dscr;
#endif

pte_t* pt_get_pte(page_table_t* pt, uint64_t lvl, void* va)
{
    size_t pte_index = pt_getpteindex_by_va(pt, va, 0);
    pte_t* pte = &(pt->root[pte_index]);

    for (int i = 0; i < lvl; i++) {
        if (!pte_valid(pte)) return NULL;
        pte = (pte_t*)pte_addr(pte);
        int index = pt_getpteindex_by_va(pt, va, i + 1);
        pte = &pte[index];
    }

    return pte;
}

pte_t* pt_get(page_table_t* pt, uint64_t lvl, void* va)
{
    uintptr_t pte = (uintptr_t)pt_get_pte(pt, lvl, va);
    return (pte_t*)(pte & ~(pt_size(pt, lvl) - 1));
}
