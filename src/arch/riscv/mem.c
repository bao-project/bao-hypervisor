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

#include <mem.h>

#include <platform.h>
#include <cpu.h>

static inline void as_map_physical_identity(struct addr_space *as) {
    const size_t lvl = 0;
    size_t lvl_size = pt_lvlsize(&as->pt, lvl);
    paddr_t lvl_mask = ~((paddr_t)lvl_size - 1);
    pte_t *pt = as->pt.root;

    /**
     *  Create identity mapping of existing physical memory regions using
     * the largest pages possible pte (in riscv this is always at level 0
     * pt).
     */

    for (size_t i = 0; i < platform.region_num; i++) {
        struct mem_region *reg = &platform.regions[i];
        paddr_t base = reg->base & lvl_mask;
        paddr_t top = (reg->base + reg->size) & lvl_mask;
        size_t num_entries = ((top - base - 1) / lvl_size) + 1;

        paddr_t addr = base;
        for (size_t j = 0; j < num_entries; j++) {
            size_t index = PTE_INDEX(lvl, addr);
            pte_set(&pt[index], addr, PTE_SUPERPAGE, PTE_HYP_FLAGS);
            addr += lvl_size;
        }
    }
}

void as_arch_init(struct addr_space *as) {

    if(as->type == AS_HYP) {
        as_map_physical_identity(as);
    }

}

bool mem_translate(struct addr_space *as, vaddr_t va, paddr_t *pa)
{
    pte_t* pte = &(as->pt.root[PTE_INDEX(0, va)]);
    size_t lvl = 0;
    for (size_t i = 0; i < as->pt.dscr->lvls; i++) {
        if (!pte_valid(pte) || !pte_table(&as->pt, pte, i)) {
            lvl = i;
            break;  
        }
        pte = (pte_t*)pte_addr(pte);
        size_t index = PTE_INDEX(i + 1, va);
        pte = &pte[index];
    }
    if (pte && pte_valid(pte)) {
        *pa = pte_addr(pte);
        paddr_t mask = (1ULL << as->pt.dscr->lvl_off[lvl]) - 1;
        *pa = (*pa & ~mask) | ((paddr_t)va & mask);
        return true;
    } else {
        return false;
    }
}
