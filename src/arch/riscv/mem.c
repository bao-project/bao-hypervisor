/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>

#include <platform.h>
#include <cpu.h>
#include <tlb.h>

static inline void as_map_physical_identity(struct addr_space* as)
{
    const size_t lvl = 0;
    size_t lvl_size = pt_lvlsize(&as->pt, lvl);
    paddr_t lvl_mask = ~((paddr_t)lvl_size - 1);
    pte_t* pt = as->pt.root;

    /**
     *  Create identity mapping of existing physical memory regions using the largest pages
     * possible pte (in riscv this is always at level 0 pt).
     */

    for (size_t i = 0; i < platform.region_num; i++) {
        struct mem_region* reg = &platform.regions[i];
        paddr_t base = reg->base & lvl_mask;
        paddr_t top = ALIGN((reg->base + reg->size), lvl_size) & lvl_mask;
        size_t num_entries = ((top - base - 1) / lvl_size) + 1;

        if (DEFINED(RV32) && ((reg->base + reg->size - 1) >= BAO_VAS_BASE)) {
            ERROR("Physical memory layout not supported for RV32. FIXME!\n");
        }

        paddr_t addr = base;
        for (unsigned int j = 0; j < num_entries; j++) {
            size_t index = pt_getpteindex_by_va(&as->pt, (vaddr_t)addr, lvl);
            pte_set(&pt[index], addr, PTE_SUPERPAGE, PTE_HYP_FLAGS);
            addr += lvl_size;
        }
    }
}

void as_arch_init(struct addr_space* as)
{
    if (as->type == AS_HYP) {
        as_map_physical_identity(as);
    }
}

bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa)
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
        size_t index = pt_getpteindex_by_va(&as->pt, va, i + 1);
        pte = &pte[index];
    }
    if (pte && pte_valid(pte)) {
        *pa = pte_addr(pte);
        paddr_t mask = (paddr_t)(1UL << as->pt.dscr->lvl_off[lvl]) - 1;
        *pa = (*pa & ~mask) | ((paddr_t)va & mask);
        return true;
    } else {
        return false;
    }
}

/**
 * RISC-V permits implementations to cache invalid PTEs unless Svvptc is
 * implemented (the SiFive P550 does; QEMU does not, which masks the bug), so
 * after an invalid->valid transition a hart may keep faulting on the new
 * mapping until the cached negative entry is evicted. Invalidate so the
 * walker re-reads the new PTEs. tlb_inv_all already scopes the fence to the
 * address space: hfence.gvma restricted to the VM's VMID for guest address
 * spaces, sfence.vma for the hypervisor's.
 *
 * TODO: for small num_pages a ranged invalidation over [va, va + num_pages)
 * would preserve the rest of the VMID's cached translations, but ranged
 * remote fences run as per-page loops in the SBI implementation, so bulk
 * mappings (VM RAM regions) must keep the full flush; picking the crossover
 * threshold needs measurement. The va/num_pages parameters exist for this.
 */
void mem_arch_map_sync_tlbs(struct addr_space* as, vaddr_t va, size_t num_pages)
{
    UNUSED_ARG(va);
    UNUSED_ARG(num_pages);
    tlb_inv_all(as);
}
