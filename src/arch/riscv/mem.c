/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
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
        paddr_t top = ALIGN((reg->base + reg->size), lvl_size) & lvl_mask;
        size_t num_entries = ((top - base - 1) / lvl_size) + 1;

        paddr_t addr = base;
        for (int j = 0; j < num_entries; j++) {
            int index = pt_getpteindex_by_va(&as->pt, (vaddr_t)addr, lvl);
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
    size_t pte_index = pt_getpteindex_by_va(&as->pt, va, 0);
    pte_t* pte = &(as->pt.root[pte_index]);
    size_t lvl = 0;
    for (size_t i = 0; i < as->pt.dscr->lvls; i++) {
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
        paddr_t mask = (1ULL << as->pt.dscr->lvl_off[lvl]) - 1;
        *pa = (*pa & ~mask) | ((paddr_t)va & mask);
        return true;
    } else {
        return false;
    }
}
