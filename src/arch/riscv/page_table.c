/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <page_table.h>

#if (SV32)
struct page_table_dscr sv32_pt_dscr = {.lvls = 2,
                                  .lvl_wdt = (size_t[]){32, 22},
                                  .lvl_off = (size_t[]){22, 12},
                                  .lvl_term = (bool[]){true, true}};
struct page_table_dscr sv32x4_pt_dscr = {.lvls = 2,
                                    .lvl_wdt = (size_t[]){34, 22},
                                    .lvl_off = (size_t[]){22, 12},
                                    .lvl_term = (bool[]){true, true}};
struct page_table_dscr* hyp_pt_dscr = &sv32_pt_dscr;
struct page_table_dscr* vm_pt_dscr = &sv32x2_pt_dscr;
#elif (RV64)
struct page_table_dscr sv39_pt_dscr = {.lvls = 3,
                                  .lvl_wdt = (size_t[]){39, 30, 21},
                                  .lvl_off = (size_t[]){30, 21, 12},
                                  .lvl_term = (bool[]){true, true, true}};
struct page_table_dscr sv39x4_pt_dscr = {.lvls = 3,
                                    .lvl_wdt = (size_t[]){41, 30, 21},
                                    .lvl_off = (size_t[]){30, 21, 12},
                                    .lvl_term = (bool[]){true, true, true}};
struct page_table_dscr* hyp_pt_dscr = &sv39_pt_dscr;
struct page_table_dscr* vm_pt_dscr = &sv39x4_pt_dscr;
#endif

pte_t* pt_get_pte(struct page_table* pt, size_t lvl, vaddr_t va)
{
    size_t pte_index = pt_getpteindex_by_va(pt, va, 0);
    pte_t* pte = &(pt->root[pte_index]);

    for (size_t i = 0; i < lvl; i++) {
        if (!pte_valid(pte)) return NULL;
        pte = (pte_t*)pte_addr(pte);
        size_t index = pt_getpteindex_by_va(pt, va, i + 1);
        pte = &pte[index];
    }

    return pte;
}

pte_t* pt_get(struct page_table* pt, size_t lvl, vaddr_t va)
{
    uintptr_t pte = (uintptr_t)pt_get_pte(pt, lvl, va);
    return (pte_t*)(pte & ~(pt_size(pt, lvl) - 1));
}

bool pte_page(struct page_table* pt, pte_t* pte, size_t lvl)
{
    return ((*pte & PTE_VALID) != 0) && ((*pte & PTE_RWX) != 0);
}
