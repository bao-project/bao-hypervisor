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

struct page_table_dscr {
    size_t lvls;
    size_t* lvl_off;
    size_t* lvl_wdt;
    bool* lvl_term;
};

struct page_table {
    pte_t* root;
    pte_t root_flags;
    struct page_table_dscr* dscr;
};

extern struct page_table_dscr* hyp_pt_dscr;
extern struct page_table_dscr* vm_pt_dscr;

static inline size_t pt_nentries(struct page_table* pt, size_t lvl)
{
    return (1ULL << pt->dscr->lvl_wdt[lvl]) >> pt->dscr->lvl_off[lvl];
}

static inline size_t pt_lvlsize(struct page_table* pt, size_t lvl)
{
    return 1ULL << pt->dscr->lvl_off[lvl];
}

static inline size_t pt_size(struct page_table* pt, size_t lvl)
{
    return pt_nentries(pt, lvl) * sizeof(pte_t);
}

static inline size_t pt_getpteindex(struct page_table* pt, pte_t* pte, size_t lvl)
{
    return (size_t)(((size_t)pte) & (pt_size(pt, lvl) - 1)) / sizeof(pte_t);
}

static inline size_t pt_getpteindex_by_va(struct page_table* pt, vaddr_t va, 
    size_t lvl)
{
    return (va >> pt->dscr->lvl_off[lvl]) & (pt_nentries(pt, lvl) - 1);
}

static inline bool pt_lvl_terminal(struct page_table* pt, size_t lvl)
{
    return pt->dscr->lvl_term[lvl];
}

/* Functions implemented in architecture dependent files */

pte_t* pt_get_pte(struct page_table* pt, size_t lvl, vaddr_t va);
pte_t* pt_get(struct page_table* pt, size_t lvl, vaddr_t va);
void pte_set(pte_t* pte, paddr_t addr, pte_t flags);

void pte_set_rsw(pte_t* pte, pte_t flag);
bool pte_check_rsw(pte_t* pte, pte_t flag);

bool pte_valid(pte_t* pte);
bool pte_table(struct page_table* pt, pte_t* pte, size_t lvl);
bool pte_page(struct page_table* pt, pte_t* pte, size_t lvl);
pte_t pt_pte_type(struct page_table* pt, size_t lvl);

#endif /* __ASSEMBLER__ */

#endif /* __PAGE_TABLE_H__ */
