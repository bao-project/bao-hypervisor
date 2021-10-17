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

#ifndef __PAGE_TABLE_H__
#define __PAGE_TABLE_H__

#include <bao.h>
#include <arch/page_table.h>

#ifndef __ASSEMBLER__

typedef struct {
    size_t lvls;
    size_t* lvl_off;
    size_t* lvl_wdt;
    bool* lvl_term;
} page_table_dscr_t;

typedef struct page_table {
    pte_t* root;
    pte_t root_flags;
    page_table_dscr_t* dscr;
} page_table_t;

extern page_table_dscr_t* hyp_pt_dscr;
extern page_table_dscr_t* vm_pt_dscr;

static inline uint64_t pt_nentries(page_table_t* pt, size_t lvl)
{
    return (1ULL << pt->dscr->lvl_wdt[lvl]) >> pt->dscr->lvl_off[lvl];
}

static inline uint64_t pt_lvlsize(page_table_t* pt, size_t lvl)
{
    return 1ULL << pt->dscr->lvl_off[lvl];
}

static inline uint64_t pt_size(page_table_t* pt, size_t lvl)
{
    return pt_nentries(pt, lvl) * sizeof(pte_t);
}

static inline uint64_t pt_getpteindex(page_table_t* pt, pte_t* pte, size_t lvl)
{
    return (uint64_t)(((uint64_t)pte) & (pt_size(pt, lvl) - 1)) / sizeof(pte_t);
}

static inline uint64_t pt_getpteindex_by_va(page_table_t* pt, void* va, 
    size_t lvl)
{
    return (((uint64_t)va) >> pt->dscr->lvl_off[lvl]) &
        (pt_nentries(pt, lvl) - 1);
}

static inline bool pt_lvl_terminal(page_table_t* pt, size_t lvl)
{
    return pt->dscr->lvl_term[lvl];
}

/* Functions implemented in architecture dependent files */

pte_t* pt_get_pte(page_table_t* pt, uint64_t lvl, void* va);
pte_t* pt_get(page_table_t* pt, uint64_t lvl, void* va);
void pte_set(pte_t* pte, uint64_t addr, uint64_t type, uint64_t flags);

void pte_set_rsw(pte_t* pte, uint64_t flag);
bool pte_check_rsw(pte_t* pte, uint64_t flag);

bool pte_valid(pte_t* pte);
bool pte_table(page_table_t* pt, pte_t* pte, uint64_t lvl);
bool pte_page(page_table_t* pt, pte_t* pte, uint64_t lvl);
uint64_t pt_pte_type(page_table_t* pt, uint64_t lvl);

#endif /* __ASSEMBLER__ */

#endif /* __PAGE_TABLE_H__ */
