/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
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
    struct page_table_dscr* dscr;
    struct page_table_arch arch;
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
void pte_set(pte_t* pte, paddr_t addr, pte_type_t type, pte_flags_t flags);

void pte_set_rsw(pte_t* pte, pte_t flag);
bool pte_check_rsw(pte_t* pte, pte_t flag);

bool pte_valid(pte_t* pte);
bool pte_table(struct page_table* pt, pte_t* pte, size_t lvl);
bool pte_page(struct page_table* pt, pte_t* pte, size_t lvl);

#endif /* __ASSEMBLER__ */

#endif /* __PAGE_TABLE_H__ */
