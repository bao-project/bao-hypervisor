/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <mem.h>

#include <cpu.h>
#include <page_table.h>
#include <platform.h>
#include <cache.h>
#include <string.h>
#include <vm.h>
#include <fences.h>
#include <tlb.h>
#include <config.h>

extern uint8_t _image_start, _image_load_end, _image_end, _dmem_phys_beg,
     _dmem_beg, _cpu_private_beg, _cpu_private_end, _vm_beg, _vm_end,
     _vm_image_start, _vm_image_end;

void switch_space(struct cpu *, paddr_t);

/**
 * An important note about sections its that they must have diferent entries
 * at the root page table.
 */

struct section {
    vaddr_t beg;
    vaddr_t end;
    bool shared;
    spinlock_t lock;
};

struct section hyp_secs[] = {
    [SEC_HYP_GLOBAL] = {(vaddr_t)&_dmem_beg, (vaddr_t)&_cpu_private_beg - 1, true,
                        SPINLOCK_INITVAL},
    [SEC_HYP_IMAGE] = {(vaddr_t)&_image_start, (vaddr_t)&_image_end - 1, true, SPINLOCK_INITVAL},
    [SEC_HYP_PRIVATE] = {(vaddr_t)&_cpu_private_beg, (vaddr_t)&_cpu_private_end - 1, false,
                         SPINLOCK_INITVAL},
    [SEC_HYP_VM] = {(vaddr_t)&_vm_beg, (vaddr_t)&_vm_end - 1, true, SPINLOCK_INITVAL},
};

struct section vm_secs[] = {
    [SEC_VM_ANY] = {0x0, MAX_VA, false, SPINLOCK_INITVAL}};

struct {
    struct section *sec;
    size_t sec_size;
} sections[] = {
    [AS_HYP] = {hyp_secs, sizeof(hyp_secs) / sizeof(struct section)},
    [AS_HYP_CPY] = {hyp_secs, sizeof(hyp_secs) / sizeof(struct section)},
    [AS_VM] = {vm_secs, sizeof(vm_secs) / sizeof(struct section)},
};

size_t mem_cpu_boot_alloc_size() {
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    for (size_t i = 0; i < cpu()->as.pt.dscr->lvls; i++) {
        size += ALIGN(pt_size(&cpu()->as.pt, i), PAGE_SIZE);
    }
    return size;
}

static inline size_t pp_next_clr(paddr_t base, size_t from, colormap_t colors)
{
    size_t clr_offset = (base / PAGE_SIZE) % (COLOR_NUM * COLOR_SIZE);
    size_t index = from;

    while (!((colors >> ((index + clr_offset) / COLOR_SIZE % COLOR_NUM)) & 1))
        index++;

    return index;
}

static void mem_free_ppages(struct ppages *ppages)
{
    list_foreach(page_pool_list, struct page_pool, pool)
    {
        spin_lock(&pool->lock);
        if (in_range(ppages->base, pool->base, pool->size * PAGE_SIZE)) {
            size_t index = (ppages->base - pool->base) / PAGE_SIZE;
            if (!all_clrs(ppages->colors)) {
                for (size_t i = 0; i < ppages->num_pages; i++) {
                    index = pp_next_clr(pool->base, index, ppages->colors);
                    bitmap_clear(pool->bitmap, index++);
                }
            } else {
                bitmap_clear_consecutive(pool->bitmap, index, ppages->num_pages);
            }
        }
        spin_unlock(&pool->lock);
    }
}

bool pp_alloc_clr(struct page_pool *pool, size_t n, colormap_t colors,
                         struct ppages *ppages)
{
    size_t allocated = 0;

    size_t first_index = 0;
    bool ok = false;

    ppages->colors = colors;
    ppages->num_pages = 0;

    spin_lock(&pool->lock);

    /**
     * Lets start the search at the first available color after the last
     * known free position to the top of the pool.
     */
    size_t index = pp_next_clr(pool->base, pool->last, colors);
    size_t top = pool->size;

    /**
     * Two iterations. One starting from the last known free page,
     * other starting from the beggining of page pool to the start of the
     * previous iteration.
     */
    for (size_t i = 0; i < 2 && !ok; i++) {
        while ((allocated < n) && (index < top)) {
            allocated = 0;

            /* Find first free page on the target colors */
            while ((index < top) && bitmap_get(pool->bitmap, index)) {
                index = pp_next_clr(pool->base, ++index, colors);
            }
            first_index = index;

            /**
             * Count the number of free pages contigous on the target
             * color segement until n pages are found or we reach top page
             * of the search.
             */
            while ((index < top) && (bitmap_get(pool->bitmap, index) == 0) &&
                   (allocated < n)) {
                allocated++;
                index = pp_next_clr(pool->base, ++index, colors);
            }

            index++;
        }

        if (allocated == n) {
            /**
             * We've found n contigous free pages that fit the color pattern,
             * Fill the output ppage arg, mark the pages as allocated and
             * update page pool internal state.
             */
            ppages->num_pages = n;
            ppages->base = pool->base + (first_index * PAGE_SIZE);
            for (size_t i = 0; i < n; i++) {
                first_index = pp_next_clr(pool->base, first_index, colors);
                bitmap_set(pool->bitmap, first_index++);
            }
            pool->free -= n;
            pool->last = first_index;
            ok = true;
            break;
        } else {
            /**
             * If this is the first iteration, setup index and top to search
             * from base of the page pool until the previous iteration start
             * point
             */
            index = 0;
        }
    }

    spin_unlock(&pool->lock);

    return ok;
}


static struct section *mem_find_sec(struct addr_space *as, vaddr_t va)
{
    for (size_t i = 0; i < sections[as->type].sec_size; i++) {
        if ((va >= sections[as->type].sec[i].beg) &&
            (va <= sections[as->type].sec[i].end)) {
            return &sections[as->type].sec[i];
        }
    }

    return NULL;
}

static inline bool pte_allocable(struct addr_space *as, pte_t *pte, size_t lvl,
                                 size_t left, vaddr_t addr)
{
    return (lvl == (as->pt.dscr->lvls - 1)) ||
           (pt_lvl_terminal(&as->pt, lvl) && !pte_valid(pte) &&
            (pt_lvlsize(&as->pt, lvl) <= (left * PAGE_SIZE)) &&
            ((addr % pt_lvlsize(&as->pt, lvl)) == 0));
}

static inline pte_t *mem_alloc_pt(struct addr_space *as, pte_t *parent, size_t lvl,
                                  vaddr_t addr)
{
    /* Must have lock on as and va section to call */
    size_t ptsize = NUM_PAGES(pt_size(&as->pt, lvl + 1));
    struct ppages ppage = mem_alloc_ppages(as->colors, ptsize, ptsize > 1 ? true : false);
    if (ppage.num_pages == 0) return NULL;
    pte_t pte_dflt_val = PTE_INVALID | (*parent & PTE_RSW_MSK);
    pte_set(parent, ppage.base, PTE_TABLE, PTE_HYP_FLAGS);
    fence_sync_write();
    pte_t *temp_pt = pt_get(&as->pt, lvl + 1, addr);
    for (size_t i = 0; i < pt_nentries(&as->pt, lvl + 1); i++) {
        temp_pt[i] = pte_dflt_val;
    }
    return temp_pt;
}

static inline bool pt_pte_mappable(struct addr_space *as, pte_t *pte, size_t lvl,
                                   size_t left, vaddr_t vaddr,
                                   paddr_t paddr)
{
    return !pte_valid(pte) &&
           (pt_lvlsize(&as->pt, lvl) <= (left * PAGE_SIZE)) &&
           (((size_t)vaddr % pt_lvlsize(&as->pt, lvl)) == 0) &&
           ((paddr % pt_lvlsize(&as->pt, lvl)) == 0);
}

static inline pte_type_t pt_page_type(struct page_table* pt, size_t lvl)
{
    return (lvl == pt->dscr->lvls - 1) ? PTE_PAGE : PTE_SUPERPAGE;
}

static void mem_expand_pte(struct addr_space *as, vaddr_t va, size_t lvl)
{
    /* Must have lock on as and va section to call */

    if (as->pt.dscr->lvls - 1 <= lvl) {
        /* no more levels to expand */
        return;
    }

    pte_t *pte = pt_get_pte(&as->pt, lvl, va);

    /**
     * only can expand if the pte exists and it isnt pointing to
     * a next level table already.
     */
    if (pte != NULL && !pte_table(&as->pt, pte, lvl)) {
        pte_t pte_val = *pte;  // save the original pte
        bool rsv = pte_check_rsw(pte, PTE_RSW_RSRV);
        bool vld = pte_valid(pte);
        pte = mem_alloc_pt(as, pte, lvl, va);

        if (vld || rsv) {
            /**
             *  If this was valid before and it wasn't a table, it must
             * have been a superpage, so fill the new expanded table to
             * have the same mappings;
             */

            /**
             * Invalidate the old TLB entries with superpage entries.
             * This means that from now on to the end of the function,
             * the original spaced mapped by the entry will be unmaped.
             * Therefore this function cannot be call on the entry mapping
             * hypervisor code or data used in it (including stack).
             */
            tlb_inv_va(&cpu()->as, va);

            /**
             *  Now traverse the new next level page table to replicate the
             * original mapping.
             */

            lvl++;
            paddr_t paddr = pte_addr(&pte_val);
            size_t entry = pt_getpteindex(&as->pt, pte, lvl);
            size_t nentries = pt_nentries(&as->pt, lvl);
            size_t lvlsz = pt_lvlsize(&as->pt, lvl);
            pte_type_t type = pt_page_type(&as->pt, lvl);
            pte_flags_t flags =
                (as->type == AS_HYP ? PTE_HYP_FLAGS : PTE_VM_FLAGS);

            while (entry < nentries) {
                if (vld)
                    pte_set(pte, paddr, type, flags);
                else if (rsv)
                    pte_set_rsw(pte, PTE_RSW_RSRV);
                pte++;
                entry++;
                paddr += lvlsz;
            }

            fence_sync_write();
        }
    }
}

static void mem_inflate_pt(struct addr_space *as, vaddr_t va, size_t length)
{
    /* Must have lock on as and va section to call */

    /**
     * For each level in the pt, expand each entry in the specified range
     * as a next level page table.
     */
    for (size_t lvl = 0; lvl < as->pt.dscr->lvls - 1; lvl++) {
        vaddr_t vaddr = va;
        size_t lvlsz = pt_lvlsize(&as->pt, lvl);
        while (vaddr < (va + length)) {
            mem_expand_pte(as, vaddr, lvl);
            vaddr += lvlsz;
        }
    }
}

vaddr_t mem_alloc_vpage(struct addr_space *as, enum AS_SEC section,
                            vaddr_t at, size_t n)
{
    size_t lvl = 0;
    size_t entry = 0;
    size_t nentries = 0;
    size_t lvlsze = 0;
    size_t count = 0;
    vaddr_t addr = INVALID_VA;
    vaddr_t vpage = INVALID_VA;
    vaddr_t top = MAX_VA;
    pte_t *pte = NULL;
    bool failed = false;

    // TODO: maybe some bound checking here would be nice
    struct section *sec = &sections[as->type].sec[section];
    if (at != INVALID_VA) {
        if (sec != mem_find_sec(as, at)) return INVALID_VA;
        addr = at;
    } else {
        addr = sec->beg;
    }
    top = sec->end;

    if (addr > top || !IS_ALIGNED(addr, PAGE_SIZE)) {
        return INVALID_VA;
    }
    
    spin_lock(&as->lock);
    if (sec->shared) spin_lock(&sec->lock);

    while (count < n && !failed) {
        // Check if there is still enough space in the address space.
        // The corner case of top being the highest address in the address
        // space and the target address being 0 is handled separate
        size_t full_as = (addr == 0) && (top == MAX_VA); 
        if (!full_as && (((top+1-addr)/PAGE_SIZE) < n)) {
            vpage = INVALID_VA;
            failed = true;
            break;
        }

        pte = pt_get_pte(&as->pt, lvl, addr);
        entry = pt_getpteindex(&as->pt, pte, lvl);
        nentries = pt_nentries(&as->pt, lvl);
        lvlsze = pt_lvlsize(&as->pt, lvl);

        while ((entry < nentries) && (count < n) && !failed) {
            if(pte_check_rsw(pte, PTE_RSW_RSRV) || 
              (pte_valid(pte) && !pte_table(&as->pt, pte, lvl))) {
                count = 0;
                vpage = INVALID_VA;
                if (at != INVALID_VA) {
                    failed = true;
                    break;
                }
            } else if(!pte_valid(pte)) {
                if(pte_allocable(as, pte, lvl, n - count, addr)) {
                    if (count == 0) vpage = addr;
                    count += (lvlsze / PAGE_SIZE);
                } else {
                    if (mem_alloc_pt(as, pte, lvl, addr) == NULL) {
                        ERROR("failed to alloc page table");
                    }
                }
            }

            if(pte_table(&as->pt, pte, lvl)) {
                lvl++;
                break;
            } else {
                pte++;
                addr += lvlsze;
                if (++entry >= nentries) {
                    lvl = 0;
                    break;
                }
            }   
        }
    }

    // mark page trable entries as reserved
    if (vpage != INVALID_VA && !failed) {
        count = 0;
        addr = vpage;
        size_t lvl = 0;
        while (count < n) {
            for (lvl = 0; lvl < as->pt.dscr->lvls; lvl++) {
                pte = pt_get_pte(&as->pt, lvl, addr);
                if (!pte_valid(pte)) break;
            }
            pte_set_rsw(pte, PTE_RSW_RSRV);
            addr += pt_lvlsize(&as->pt, lvl);
            count += pt_lvlsize(&as->pt, lvl) / PAGE_SIZE;
        }
    }

    if (sec->shared) spin_unlock(&sec->lock);

    spin_unlock(&as->lock);

    return vpage;
}

void mem_unmap(struct addr_space *as, vaddr_t at, size_t num_pages,
                    bool free_ppages)
{
    vaddr_t vaddr = at;
    vaddr_t top = at + (num_pages * PAGE_SIZE);
    size_t lvl = 0;

    spin_lock(&as->lock);

    struct section *sec = mem_find_sec(as, at);
    if (sec->shared) spin_lock(&sec->lock);

    while (vaddr < top) {
        pte_t *pte = pt_get_pte(&as->pt, lvl, vaddr);
        if (pte == NULL) {
            ERROR("invalid pte while freeing vpages");
        } else if (!pte_valid(pte)) {
            size_t lvlsz = pt_lvlsize(&as->pt, lvl);
            vaddr += lvlsz;
        } else if (pte_table(&as->pt, pte, lvl)) {
            lvl++;
        } else {
            size_t entry = pt_getpteindex(&as->pt, pte, lvl);
            size_t nentries = pt_nentries(&as->pt, lvl);
            size_t lvlsz = pt_lvlsize(&as->pt, lvl);

            while ((entry < nentries) && (vaddr < top)) {
                if (!pte_table(&as->pt, pte, lvl)) {
                    vaddr_t vpage_base = vaddr & ~(lvlsz - 1);

                    if (vaddr > vpage_base || top < (vpage_base + lvlsz)) {
                        mem_expand_pte(as, vaddr, lvl);
                        lvl++;
                        break;
                    }

                    if (free_ppages) {
                        paddr_t paddr = pte_addr(pte);
                        struct ppages ppages =
                            mem_ppages_get(paddr, lvlsz / PAGE_SIZE);
                        mem_free_ppages(&ppages);
                    }

                    *pte = 0;
                    tlb_inv_va(&cpu()->as, vaddr);

                } else {
                    break;
                }
                pte++;
                entry++;
                vaddr += lvlsz;
            }

            if (entry == nentries) {
                lvl--;
            }

            /**
             * TODO: check if the current pt is now empty and if so,
             * free it too up to the root.
             */
        }
    }

    if (sec->shared) spin_unlock(&sec->lock);

    spin_unlock(&as->lock);
}

bool mem_map(struct addr_space *as, vaddr_t va, struct ppages *ppages,
            size_t num_pages, mem_flags_t flags)
{
    size_t count = 0;
    pte_t *pte = NULL;
    vaddr_t vaddr = va & ~(PAGE_SIZE - 1);

    struct section *sec = mem_find_sec(as, vaddr);

    if ((sec == NULL) || (sec != mem_find_sec(as, vaddr + num_pages * PAGE_SIZE - 1)))
        return false;

    spin_lock(&as->lock);
    if (sec->shared) spin_lock(&sec->lock);

    /**
     * TODO check if entry is reserved. Unrolling mapping if something
     * goes wrong.
     */

    struct ppages temp_ppages;
    if (ppages == NULL && !all_clrs(as->colors)) {
        temp_ppages = mem_alloc_ppages(as->colors, num_pages, false);
        if (temp_ppages.num_pages < num_pages) {
            ERROR("failed to alloc colored physical pages");
        }
        ppages = &temp_ppages;
    }

    if (ppages && !all_clrs(ppages->colors)) {
        size_t index = 0;
        mem_inflate_pt(as, vaddr, num_pages * PAGE_SIZE);
        for (size_t i = 0; i < ppages->num_pages; i++) {
            pte = pt_get_pte(&as->pt, as->pt.dscr->lvls - 1, vaddr);
            index = pp_next_clr(ppages->base, index, ppages->colors);
            paddr_t paddr = ppages->base + (index * PAGE_SIZE);
            pte_set(pte, paddr, PTE_PAGE, flags);
            vaddr += PAGE_SIZE;
            index++;
        }
    } else {
        paddr_t paddr = ppages ? ppages->base : 0;
        while (count < num_pages) {
            size_t lvl = 0;
            for (lvl = 0; lvl < as->pt.dscr->lvls; lvl++) {
                pte = pt_get_pte(&as->pt, lvl, vaddr);
                if (pt_lvl_terminal(&as->pt, lvl)) {
                    if (pt_pte_mappable(as, pte, lvl, num_pages - count,
                                        vaddr, ppages ? paddr : 0)) {
                        break;
                    } else if (!pte_valid(pte)) {
                        mem_alloc_pt(as, pte, lvl, vaddr);
                    } else if (!pte_table(&as->pt, pte, lvl)) {
                        ERROR("trying to override previous mapping");
                    }
                }
            }

            size_t entry = pt_getpteindex(&as->pt, pte, lvl);
            size_t nentries = pt_nentries(&as->pt, lvl);
            size_t lvlsz = pt_lvlsize(&as->pt, lvl);

            while ((entry < nentries) && (count < num_pages) &&
                   (num_pages - count >= lvlsz / PAGE_SIZE)) {
                if (ppages == NULL) {
                    struct ppages temp =
                        mem_alloc_ppages(as->colors, lvlsz / PAGE_SIZE, true);
                    if (temp.num_pages < lvlsz / PAGE_SIZE) {
                        if (lvl == (as->pt.dscr->lvls - 1)) {
                            // TODO: free previously allocated pages
                            ERROR("failed to alloc physical pages");
                        } else {
                            pte = pt_get_pte(&as->pt, lvl, vaddr);
                            if (!pte_valid(pte)) {
                                mem_alloc_pt(as, pte, lvl, vaddr);
                            }
                            break;
                        }
                    }
                    paddr = temp.base;
                }
                pte_set(pte, paddr, pt_page_type(&as->pt, lvl), flags);
                vaddr += lvlsz;
                paddr += lvlsz;
                count += lvlsz / PAGE_SIZE;
                pte++;
                entry++;
            }
        }
    }

    fence_sync();

    if (sec->shared) {
        spin_unlock(&sec->lock);
        // TODO tlb shootdown?
    }
    spin_unlock(&as->lock);

    return true;
}

bool mem_map_reclr(struct addr_space *as, vaddr_t va, struct ppages *ppages,
                    size_t num_pages, mem_flags_t flags)
{
    if (ppages == NULL) {
        ERROR("no indication on what to recolor");
    }

    /**
     * Count how many pages are not colored in original images.
     * Allocate the necessary colored pages.
     * Mapped onto hypervisor address space.
     */
    size_t reclrd_num =
        num_pages / (COLOR_NUM * COLOR_SIZE) * COLOR_SIZE *
        bit_count(~(as->colors & BIT_MASK(0, COLOR_NUM)));
    size_t clr_offset = (ppages->base / PAGE_SIZE) % (COLOR_NUM * COLOR_SIZE);
    for (size_t i = 0; i < (num_pages % (COLOR_NUM * COLOR_SIZE)); i++) {
        if (!bit_get(as->colors, (i + clr_offset) / COLOR_SIZE % COLOR_NUM))
            reclrd_num++;
    }

   /**
     * If the address space was not assigned any specific color,
     * or there are no pages to recolor defer to vanilla mapping.
     */
    if (all_clrs(as->colors) || (reclrd_num == 0)) {
        return mem_map(as, va, ppages, num_pages, flags);
    }

    vaddr_t reclrd_va_base =
        mem_alloc_vpage(&cpu()->as, SEC_HYP_VM, INVALID_VA, reclrd_num);
    struct ppages reclrd_ppages = mem_alloc_ppages(as->colors, reclrd_num, false);
    mem_map(&cpu()->as, reclrd_va_base, &reclrd_ppages, reclrd_num, PTE_HYP_FLAGS);

    /**
     * Map original image onto hypervisor address space.
     */
    vaddr_t phys_va_base = mem_alloc_vpage(&cpu()->as, SEC_HYP_VM, INVALID_VA, num_pages);
    mem_map(&cpu()->as, phys_va_base, ppages, num_pages, PTE_HYP_FLAGS);

    pte_t *pte = NULL;
    vaddr_t vaddr = va & ~(PAGE_SIZE - 1);
    paddr_t paddr = ppages->base;
    vaddr_t clrd_vaddr = reclrd_va_base;
    vaddr_t phys_va = phys_va_base;
    size_t index = 0;

    /**
     * Inflate reserved page tables to the last level. This assumes
     * coloring always needs the finest grained mapping possible.
     */
    mem_inflate_pt(as, vaddr, num_pages * PAGE_SIZE);

    for (size_t i = 0; i < num_pages; i++) {
        pte = pt_get_pte(&as->pt, as->pt.dscr->lvls - 1, vaddr);

        /**
         * If image page is already color, just map it.
         * Otherwise first copy it to the previously allocated pages.
         */
        if (bit_get(as->colors, ((i + clr_offset) / COLOR_SIZE % COLOR_NUM))) {
            pte_set(pte, paddr, PTE_PAGE, flags);
        } else {
            memcpy((void*)clrd_vaddr, (void*)phys_va, PAGE_SIZE);
            index = pp_next_clr(reclrd_ppages.base, index, as->colors);
            paddr_t clrd_paddr = reclrd_ppages.base + (index * PAGE_SIZE);
            pte_set(pte, clrd_paddr, PTE_PAGE, flags);

            clrd_vaddr += PAGE_SIZE;
            index++;
        }
        paddr += PAGE_SIZE;
        phys_va += PAGE_SIZE;
        vaddr += PAGE_SIZE;
    }

    /**
     * Flush the newly allocated colored pages to which parts of the
     * image was copied, and might stayed in the cache system.
     */
    cache_flush_range(reclrd_va_base, reclrd_num * PAGE_SIZE);

    /**
     * Free the uncolored pages of the original image.
     */
    struct ppages unused_pages = {
        .base = ppages->base,
        .num_pages = reclrd_num,
        .colors = ~as->colors
    };
    mem_free_ppages(&unused_pages);

    mem_unmap(&cpu()->as, reclrd_va_base, reclrd_num, false);
    mem_unmap(&cpu()->as, phys_va_base, num_pages, false);

    return true;
}

vaddr_t mem_map_cpy(struct addr_space *ass, struct addr_space *asd, vaddr_t vas,
                vaddr_t vad, size_t num_pages) {

    vaddr_t _vad = mem_alloc_vpage(asd, SEC_HYP_GLOBAL, vad, num_pages);
    size_t base_vad = _vad;
    size_t count = 0;
    size_t to_map = num_pages * PAGE_SIZE;

    while (count < num_pages) {
        size_t lvl = 0;
        pte_t *pte = pt_get_pte(&ass->pt, lvl, vas);
        while(!pte_page(&ass->pt, pte, lvl)) {
            lvl += 1;
            pte = pt_get_pte(&ass->pt, lvl, vas);
        }
        size_t lvl_size = pt_lvlsize(&ass->pt, lvl);
        size_t size = lvl_size;
        if(to_map < lvl_size) {
            size = to_map;
        }
        size_t npages = NUM_PAGES(size);
        paddr_t pa = pte_addr(pte) + (vas - ALIGN_FLOOR(vas, lvl_size));
        struct ppages pages = mem_ppages_get(pa, npages);
        mem_map(asd, _vad, &pages, npages, PTE_HYP_FLAGS);
        _vad += size;
        vas += size;
        count += npages;
        to_map -= size;
    }

    return base_vad;
}

void *copy_space(void *base, const size_t size, struct ppages *pages)
{
    *pages = mem_alloc_ppages(cpu()->as.colors, NUM_PAGES(size), false);
    vaddr_t va = mem_alloc_vpage(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA, NUM_PAGES(size));
    mem_map(&cpu()->as, va, pages, NUM_PAGES(size), PTE_HYP_FLAGS);
    memcpy((void*)va, base, size);

    return (void*)va;
}

/**
 * To have the true benefits of coloring it's necessary that not only the guest
 * images, but also the hypervisor itself, are colored.
 *
 * Bao is coloring itself by copying everything that has been allocated until
 * this point in a new colored space, jumping into this new region and then
 * then deleting all that was allocated before.
 *
 * Some regions need to be aligned due to some ARM restraint with the pagetable
 * structure, so true coloring is actually never achieved. The drawbacks of
 * this limitation are yet to be seen, and are in need of more testing.
 */
void mem_color_hypervisor(const paddr_t load_addr, struct mem_region *root_region)
{
    volatile static pte_t shared_pte;
    vaddr_t va = INVALID_VA;
    struct cpu *cpu_new;
    struct ppages p_cpu;
    struct ppages p_image;
    struct ppages p_bitmap;

    size_t image_load_size = (size_t)(&_image_load_end - &_image_start);
    size_t image_noload_size = (size_t)(&_image_end - &_image_load_end);
    size_t image_size = image_load_size + image_noload_size;
    size_t vm_image_size = (size_t)(&_vm_image_end - &_vm_image_start);    
    size_t cpu_boot_size = mem_cpu_boot_alloc_size();
    struct page_pool *root_pool = &root_region->page_pool;
    size_t bitmap_size = (root_pool->size / (8 * PAGE_SIZE) +
                          !!(root_pool->size % (8 * PAGE_SIZE) != 0)) *
                         PAGE_SIZE;
    colormap_t colors = config.hyp.colors;

    /* Set hypervisor colors in current address space */
    cpu()->as.colors = config.hyp.colors;

    /*
     * Copy the CPU space into a colored region.
     *
     * It's not possible to simply copy the CPU space as-is, since there are a
     * few pointers and structures that would point to the old, non-colored
     * data.
     *
     * the new CPU region is created, cleaned, prepared and finally mapped.
     */
    cpu_new = copy_space((void *)BAO_CPU_BASE, sizeof(struct cpu), &p_cpu);
    as_init(&cpu_new->as, AS_HYP_CPY, HYP_ASID, NULL, colors);
    va = mem_alloc_vpage(&cpu_new->as, SEC_HYP_PRIVATE,
                        (vaddr_t)BAO_CPU_BASE,
                        NUM_PAGES(sizeof(struct cpu)));
    if (va != (vaddr_t)BAO_CPU_BASE)
        ERROR("Can't allocate virtual address for cpuspace");
    mem_map(&cpu_new->as, va, &p_cpu, NUM_PAGES(sizeof(struct cpu)), PTE_HYP_FLAGS);

    /*
     * Also, map the root page table in the new address space and keep both the
     * virtual address and physical address in local variables as they will be
     * needed later to perform the address space switch and new address space
     * initialization.
     */
    paddr_t p_root_pt_addr;
    vaddr_t v_root_pt_addr;
    size_t root_pt_num_pages = NUM_PAGES(pt_size(&cpu_new->as.pt, 0));
    mem_translate(&cpu()->as, (vaddr_t)cpu_new->as.pt.root, &p_root_pt_addr);
    v_root_pt_addr = mem_alloc_vpage(&cpu_new->as, SEC_HYP_PRIVATE, INVALID_VA,
                     root_pt_num_pages);
    if (va == INVALID_VA) {
        ERROR("Can't allocate virtuall address space for root page table");
    }
    struct ppages p_root_pt_pages =
        mem_ppages_get(p_root_pt_addr, root_pt_num_pages);
    mem_map(&cpu_new->as, v_root_pt_addr, &p_root_pt_pages, root_pt_num_pages,
        PTE_HYP_FLAGS);

    /*
     * Copy the Hypervisor image and root page pool bitmap into a colored
     * region.
     *
     * CPU_MASTER allocates, copies and maps the image and the root page pool
     * bitmap on a shared space, whilst other CPUs only have to copy the image
     * from the CPU_MASTER in order to be able to access it.
     */
    if (cpu()->id == CPU_MASTER) {
        copy_space(&_image_start, image_size, &p_image);
        va = mem_alloc_vpage(&cpu_new->as, SEC_HYP_IMAGE,
                            (vaddr_t) &_image_start, NUM_PAGES(image_size));

        if (va != (vaddr_t)&_image_start)
            ERROR("Can't allocate virtual address for Bao Image");

        mem_map(&cpu_new->as, va, &p_image,
                NUM_PAGES(image_size), PTE_HYP_FLAGS);
        shared_pte = pte_addr(pt_get_pte(&cpu_new->as.pt, 0,
            (vaddr_t)&_image_start));
    } else {
        pte_t *image_pte = pt_get_pte(&cpu_new->as.pt, 0,
                                    (vaddr_t)&_image_start);

        /* Wait for CPU_MASTER to get image page table entry */
        while (shared_pte == 0);
        pte_set(image_pte, (paddr_t)shared_pte, PTE_TABLE, PTE_HYP_FLAGS);
    }

    cpu_sync_barrier(&cpu_glb_sync);

    /*
     * CPU_MASTER will also take care of mapping the configuration onto the new
     * space.
     *
     * The root page pool bitmap tracks all the physical allocation, so it
     * needs to be the last thing to be copied, as after that, no physical
     * allocation will be tracked.
     */
    if (cpu()->id == CPU_MASTER) {
        /* Copy root pool bitmap */
        copy_space((void*)root_pool->bitmap, bitmap_size, &p_bitmap);
        va = mem_alloc_vpage(&cpu_new->as, SEC_HYP_GLOBAL,
                             (vaddr_t)root_pool->bitmap,
                             NUM_PAGES(bitmap_size));

        if (va != (vaddr_t)root_pool->bitmap)
            ERROR("Can't allocate address for cpu interface");

        mem_map(&cpu_new->as, va, &p_bitmap,
                NUM_PAGES(bitmap_size), PTE_HYP_FLAGS);
    }
    cpu_sync_barrier(&cpu_glb_sync);

    switch_space(cpu_new, p_root_pt_addr);

    /**
     * Make sure the new physical pages containing image and cpu are flushed
     * to main memmory
     */

    cache_flush_range((vaddr_t)&_image_start, image_size);
    cache_flush_range((vaddr_t)&_cpu_private_beg, sizeof(struct cpu));

    /**
     * Bao's code from here's on still uses the static global variables, so
     * they need to be updated.
     *
     * The synchronization objects are in an inconsistent state, and they need
     * to be re-initialized before they get used again, so CPUs need a way to
     * communicate between themselves without an explicit barrier. To
     * accomplish this a static global variable is used.
     */
    if (cpu()->id == CPU_MASTER) {
        cpu_sync_init(&cpu_glb_sync, platform.cpu_num);
        shared_pte = 0;
    } else {
        while (shared_pte != 0);
    }

    as_init(&cpu()->as, AS_HYP, HYP_ASID, (void*)v_root_pt_addr, colors);

    /*
     * Clear the old region that have been copied.
     *
     * CPU space regions and Hypervisor image region are contingent, starting
     * from `load_addr`. The bitmap region is on top of the root pool region.
     */
    if (cpu()->id == CPU_MASTER) {
        p_image = mem_ppages_get(load_addr, NUM_PAGES(image_load_size));
        va = mem_alloc_vpage(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, p_image.num_pages);
        mem_map(&cpu()->as, va, &p_image, p_image.num_pages, PTE_HYP_FLAGS);
        memset((void*)va, 0, p_image.num_pages * PAGE_SIZE);
        mem_unmap(&cpu()->as, va, p_image.num_pages, true);

        p_image = mem_ppages_get(load_addr + image_load_size + vm_image_size,
            NUM_PAGES(image_noload_size));
        va = mem_alloc_vpage(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, p_image.num_pages);
        mem_map(&cpu()->as, va, &p_image, p_image.num_pages, PTE_HYP_FLAGS);
        memset((void*)va, 0, p_image.num_pages * PAGE_SIZE);
        mem_unmap(&cpu()->as, va, p_image.num_pages, true);

        p_bitmap = mem_ppages_get(load_addr + image_size + vm_image_size +
                                      (cpu_boot_size * platform.cpu_num),
                                  NUM_PAGES(bitmap_size));

        va = mem_alloc_vpage(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, p_bitmap.num_pages);
        mem_map(&cpu()->as, va, &p_bitmap, p_bitmap.num_pages, PTE_HYP_FLAGS);
        memset((void*)va, 0, p_bitmap.num_pages * PAGE_SIZE);
        mem_unmap(&cpu()->as, va, p_bitmap.num_pages, true);
    }

    p_cpu = mem_ppages_get(
        load_addr + image_size + vm_image_size +(cpu_boot_size * cpu()->id),
        cpu_boot_size / PAGE_SIZE);
    va = mem_alloc_vpage(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA, p_cpu.num_pages);
    mem_map(&cpu()->as, va, &p_cpu,p_cpu.num_pages, PTE_HYP_FLAGS);
    memset((void*)va, 0,p_cpu.num_pages * PAGE_SIZE);
    mem_unmap(&cpu()->as, va,p_cpu.num_pages, false);
}

void as_init(struct addr_space *as, enum AS_TYPE type, asid_t id, 
            pte_t *root_pt, colormap_t colors)
{
    as->type = type;
    as->pt.dscr =
        type == AS_HYP || type == AS_HYP_CPY ? hyp_pt_dscr : vm_pt_dscr;
    as->colors = colors;
    as->lock = SPINLOCK_INITVAL;
    as->id = id;

    if (root_pt == NULL) {
        size_t n = NUM_PAGES(pt_size(&as->pt, 0));
        root_pt = (pte_t*) mem_alloc_page(n,
            type == AS_HYP || type == AS_HYP_CPY ? SEC_HYP_PRIVATE : SEC_HYP_VM, 
            true);
        memset((void*)root_pt, 0, n * PAGE_SIZE);
    }
    as->pt.root = root_pt;

    as_arch_init(as);
}

void mem_prot_init() {
    pte_t* root_pt = (pte_t*)
        ALIGN(((vaddr_t)cpu()) + sizeof(struct cpu), PAGE_SIZE);
    as_init(&cpu()->as, AS_HYP, HYP_ASID, root_pt, config.hyp.colors);
}

vaddr_t mem_alloc_map(struct addr_space* as, enum AS_SEC section, struct ppages *page, 
                        vaddr_t at, size_t num_pages, mem_flags_t flags)
{
    vaddr_t address = mem_alloc_vpage(as, section, at, num_pages);
    if (address != INVALID_VA) {
        mem_map(as, address, page, num_pages, flags);
    }
    return address;
}

vaddr_t mem_alloc_map_dev(struct addr_space* as, enum AS_SEC section, 
                             vaddr_t at, paddr_t pa, size_t num_pages)
{
    vaddr_t address = mem_alloc_vpage(as, section, at, num_pages);
    if (address != INVALID_VA) {
        struct ppages pages = mem_ppages_get(pa, num_pages);
        mem_flags_t flags = 
            as->type == AS_HYP ? PTE_HYP_DEV_FLAGS : PTE_VM_DEV_FLAGS;
        mem_map(as, address, &pages, num_pages, flags);
    }

    return address;
}
