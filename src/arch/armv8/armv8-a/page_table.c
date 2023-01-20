/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <page_table.h>
#include <arch/sysregs.h>
#include <cpu.h>

#ifdef AARCH32

struct page_table_dscr armv8_pt_dscr = {
    .lvls = 3,
    .lvl_wdt = (size_t[]){32, 30, 21},
    .lvl_off = (size_t[]){30, 21, 12},
    .lvl_term = (bool[]){true, true, true},
};


struct page_table_dscr armv8_pt_s2_dscr = {
    .lvls = 3,
    .lvl_wdt = (size_t[]){39, 30, 21},
    .lvl_off = (size_t[]){30, 21, 12},
    .lvl_term = (bool[]){true, true, true},
};

#else

struct page_table_dscr armv8_pt_dscr = {
    .lvls = 4,
    .lvl_wdt = (size_t[]){48, 39, 30, 21},
    .lvl_off = (size_t[]){39, 30, 21, 12},
    .lvl_term = (bool[]){false, true, true, true},
};

/**
 * This might be modified at initialization depending on the
 * value of parange and consequently SL0 in VTCR_EL2.
 */
struct page_table_dscr armv8_pt_s2_dscr = {
    .lvls = 4,
    .lvl_wdt = (size_t[]){48, 39, 30, 21},
    .lvl_off = (size_t[]){39, 30, 21, 12},
    .lvl_term = (bool[]){false, true, true, true},
};

#endif

size_t parange_table[] = {32, 36, 40, 42, 44, 48};

struct page_table_dscr* hyp_pt_dscr = &armv8_pt_dscr;
struct page_table_dscr* vm_pt_dscr = &armv8_pt_s2_dscr;

size_t parange __attribute__((section(".data")));

void pt_set_recursive(struct page_table* pt, size_t index)
{
    paddr_t pa;
    mem_translate(&cpu()->as, (vaddr_t)pt->root, &pa);
    pte_t* pte = cpu()->as.pt.root + index;
    pte_set(pte, pa, PTE_TABLE, PTE_HYP_FLAGS);
    pt->arch.rec_ind = index;
    pt->arch.rec_mask = 0;
    size_t cpu_rec_ind = cpu()->as.pt.arch.rec_ind;
    for (size_t i = 0; i < pt->dscr->lvls; i++) {
        size_t lvl_off = pt->dscr->lvl_off[i];
        pt->arch.rec_mask |= cpu_rec_ind << lvl_off;
    }
}

pte_t* pt_get_pte(struct page_table* pt, size_t lvl, vaddr_t va)
{
    struct page_table* cpu_pt = &cpu()->as.pt;

    size_t rec_ind_off = cpu_pt->dscr->lvl_off[cpu_pt->dscr->lvls - lvl - 1];
    size_t rec_ind_len = cpu_pt->dscr->lvl_wdt[cpu_pt->dscr->lvls - lvl - 1];
    uintptr_t rec_ind_mask = PTE_MASK(rec_ind_off, rec_ind_len - rec_ind_off);
    uintptr_t addr = cpu_pt->arch.rec_mask & ~PTE_MASK(0, rec_ind_len);
    addr |= (pt->arch.rec_ind << rec_ind_off) & rec_ind_mask;
    addr |= (va >> pt->dscr->lvl_off[lvl]) * sizeof(pte_t) & PTE_MASK(0, rec_ind_off);

    return (pte_t*)addr;
}

pte_t* pt_get(struct page_table* pt, size_t lvl, vaddr_t va)
{
    if (lvl == 0) return pt->root;

    uintptr_t pte = (uintptr_t)pt_get_pte(pt, lvl, va);
    pte &= ~(pt_size(pt, lvl) - 1);
    return (pte_t*)pte;
}

bool pte_page(struct page_table* pt, pte_t* pte, size_t lvl)
{
    if(!pt_lvl_terminal(pt, lvl)) {
        return false;
    }

    if (lvl != pt->dscr->lvls - 1) {
        return (*pte & PTE_TYPE_MSK) == PTE_SUPERPAGE;
    }

    return (*pte & PTE_TYPE_MSK) == PTE_PAGE;
}

bool pte_table(struct page_table* pt, pte_t* pte, size_t lvl)
{
    if (lvl == pt->dscr->lvls - 1) {
        return false;
    }

    return (*pte & PTE_TYPE_MSK) == PTE_TABLE;
}
