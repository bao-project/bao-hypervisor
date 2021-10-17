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

static inline void as_map_physical_identity(addr_space_t *as) {
    const int lvl = 0;
    size_t lvl_size = pt_lvlsize(&as->pt, lvl);
    uintptr_t lvl_mask = ~(lvl_size - 1);
    pte_t *pt = as->pt.root;

    /**
     *  Create identity mapping of existing physical memory regions using
     * the largest pages possible pte (in riscv this is always at level 0
     * pt).
     */

    for (int i = 0; i < platform.region_num; i++) {
        struct mem_region *reg = &platform.regions[i];
        uintptr_t base = reg->base & lvl_mask;
        uintptr_t top = (reg->base + reg->size) & lvl_mask;
        int num_entries = ((top - base - 1) / lvl_size) + 1;

        uintptr_t addr = base;
        for (int j = 0; j < num_entries; j++) {
            int index = pt_getpteindex_by_va(&as->pt, (void*)addr, lvl);
            pte_set(&pt[index], addr, PTE_SUPERPAGE, PTE_HYP_FLAGS);
            addr += lvl_size;
        }
    }
}

void as_arch_init(addr_space_t *as) {

    if(as->type == AS_HYP) {
        as_map_physical_identity(as);
    }

}

bool mem_translate(addr_space_t *as, void *va, uint64_t *pa)
{
    size_t pte_index = pt_getpteindex_by_va(&as->pt, va, 0);
    pte_t* pte = &(as->pt.root[pte_index]);
    size_t lvl = 0;
    for (int i = 0; i < as->pt.dscr->lvls; i++) {
        if (!pte_valid(pte) || !pte_table(&as->pt, pte, i)) {
            lvl = i;
            break;  
        }
        pte = (pte_t*)pte_addr(pte);
        int index = pt_getpteindex_by_va(&as->pt, va, i+1);
        pte = &pte[index];
    }
    if (pte && pte_valid(pte)) {
        *pa = pte_addr(pte);
        uint64_t mask = (1ULL << as->pt.dscr->lvl_off[lvl]) - 1;
        *pa = (*pa & ~mask) | ((uint64_t)va & mask);
        return true;
    } else {
        return false;
    }
}
