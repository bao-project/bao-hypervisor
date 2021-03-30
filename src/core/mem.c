/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bao.h>
#include <mem.h>

#include <cpu.h>
#include <page_table.h>
#include <platform.h>
#include <bitmap.h>
#include <objcache.h>
#include <cache.h>
#include <string.h>
#include <vm.h>
#include <fences.h>
#include <tlb.h>

extern uint8_t _image_start, _image_end, _dmem_phys_beg, _dmem_beg,
    _cpu_private_beg, _cpu_private_end, _vm_beg, _vm_end, _config_start,
    _config_end;

extern struct dev _dev_init_table_start, _dev_init_table_end;

void switch_space(cpu_t *, uint64_t);

/**
 * An important note about sections its that they must have diferent entries
 * at the root page table.
 */

typedef struct section {
    void *beg;
    void *end;
    bool shared;
    spinlock_t lock;
} section_t;

section_t hyp_secs[] = {
    [SEC_HYP_GLOBAL] = {&_dmem_beg, &_cpu_private_beg - 1, true,
                        SPINLOCK_INITVAL},
    [SEC_HYP_IMAGE] = {&_image_start, &_image_end - 1, true, SPINLOCK_INITVAL},
    [SEC_HYP_DEVICE] = {&_image_end, &_dmem_beg - 1, true, SPINLOCK_INITVAL},
    [SEC_HYP_PRIVATE] = {&_cpu_private_beg, &_cpu_private_end - 1, false,
                         SPINLOCK_INITVAL},
    [SEC_HYP_VM] = {&_vm_beg, &_vm_end - 1, true, SPINLOCK_INITVAL},
};

section_t vm_secs[] = {
    [SEC_VM_ANY] = {0x0, (void *)-1, false, SPINLOCK_INITVAL}};

struct {
    section_t *sec;
    size_t sec_size;
} sections[] = {
    [AS_HYP] = {hyp_secs, sizeof(hyp_secs) / sizeof(struct section)},
    [AS_HYP_CPY] = {hyp_secs, sizeof(hyp_secs) / sizeof(struct section)},
    [AS_VM] = {vm_secs, sizeof(vm_secs) / sizeof(struct section)},
};

typedef struct {
    node_t node;  // must be first element
    uint64_t base;
    size_t size;
    size_t free;
    size_t last;
    bitmap_t bitmap;
    spinlock_t lock;
} page_pool_t;

static list_t page_pool_list;
static page_pool_t root_pool;
static objcache_t pagepool_cache;

static bool config_found = false;

static inline uint64_t pp_next_clr(uint64_t base, int from, uint64_t colors)
{
    uint64_t clr_offset = (base / PAGE_SIZE) % (COLOR_NUM * COLOR_SIZE);
    uint64_t index = from;

    while (!((colors >> ((index + clr_offset) / COLOR_SIZE % COLOR_NUM)) & 1))
        index++;

    return index;
}

static void mem_free_ppages(ppages_t *ppages)
{
    list_foreach(page_pool_list, page_pool_t, pool)
    {
        spin_lock(&pool->lock);
        if (in_range(ppages->base, pool->base, pool->size * PAGE_SIZE)) {
            uint64_t index = (ppages->base - pool->base) / PAGE_SIZE;
            if (!all_clrs(ppages->colors)) {
                uint64_t index = 0;
                for (int i = 0; i < ppages->size; i++) {
                    index = pp_next_clr(pool->base, index, ppages->colors);
                    bitmap_set(pool->bitmap, index++);
                }
            } else {
                bitmap_clear_consecutive(pool->bitmap, index, ppages->size);
            }
        }
        spin_unlock(&pool->lock);
    }
}

static bool pp_alloc_clr(page_pool_t *pool, size_t n, uint64_t colors,
                         ppages_t *ppages)
{
    uint64_t allocated = 0;

    uint64_t first_index = 0;
    bool ok = false;

    ppages->colors = colors;
    ppages->size = 0;

    spin_lock(&pool->lock);

    /**
     * Lets start the search at the first available color after the last
     * known free position to the top of the pool.
     */
    uint64_t index = pp_next_clr(pool->base, pool->last, colors);
    uint64_t top = pool->size;

    /**
     * Two iterations. One starting from the last known free page,
     * other starting from the beggining of page pool to the start of the
     * previous iteration.
     */
    for (int i = 0; i < 2 && !ok; i++) {
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
            ppages->size = n;
            ppages->base = pool->base + (first_index * PAGE_SIZE);
            for (int i = 0; i < n; i++) {
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
            top = pool->last;
        }
    }

    spin_unlock(&pool->lock);

    return ok;
}

static bool pp_alloc(page_pool_t *pool, size_t n, bool aligned,
                     ppages_t *ppages)
{
    ppages->colors = 0;
    ppages->size = 0;

    bool ok = false;
    uint64_t base = -1;

    if (n == 0) return base;

    spin_lock(&pool->lock);

    /**
     *  If we need a contigous segment aligned to its size, lets start
     * at an already aligned index.
     */
    size_t start = aligned ?  n - (pool->base / PAGE_SIZE % n) : 0;
    size_t curr = pool->last + ((pool->last + start) % n);

    /**
     * Lets make two searches:
     *  - one starting from the last known free index.
     *  - in case this does not work, start from index 0.
     */
    for (int i = 0; i < 2 && !ok; i++) {
        while (pool->free != 0) {
            int64_t bit =
                bitmap_find_consec(pool->bitmap, pool->size, curr, n, false);

            if (bit < 0) {
                /**
                 * No n page sement was found. If this is the first iteration
                 * set position to 0 to start next search from index 0.
                 */
                curr = aligned ? (n - ((pool->base / PAGE_SIZE) % n)) % n : 0;
                break;
            } else if (aligned && (((bit + start) % n) != 0)) {
                /**
                 *  If we're looking for an aligned segment and the found
                 * contigous segment is not aligned, start the search again
                 * from the last aligned index
                 */
                curr = bit + ((bit + start) % n);
            } else {
                /**
                 * We've found our pages. Fill output argument info, mark
                 * them as allocated, and update page pool bookkeeping.
                 */
                ppages->base = pool->base + (bit * PAGE_SIZE);
                ppages->size = n;
                bitmap_set_consecutive(pool->bitmap, bit, n);
                pool->free -= n;
                pool->last = bit + n;
                ok = true;
                break;
            }
        }
    }
    spin_unlock(&pool->lock);

    return ok;
}

ppages_t mem_alloc_ppages(uint64_t colors, size_t n, bool aligned)
{
    ppages_t pages = {.size = 0};

    list_foreach(page_pool_list, page_pool_t, pool)
    {
        bool ok = (!all_clrs(colors) && !aligned)
                      ? pp_alloc_clr(pool, n, colors, &pages)
                      : pp_alloc(pool, n, aligned, &pages);
        if (ok) break;
    }

    return pages;
}

static section_t *mem_find_sec(addr_space_t *as, void *va)
{
    for (int i = 0; i < sections[as->type].sec_size; i++) {
        if ((va >= sections[as->type].sec[i].beg) &&
            (va <= sections[as->type].sec[i].end)) {
            return &sections[as->type].sec[i];
        }
    }

    return NULL;
}

static inline bool pte_allocable(addr_space_t *as, pte_t *pte, uint64_t lvl,
                                 uint64_t left, uint64_t addr)
{
    return (lvl == (as->pt.dscr->lvls - 1)) ||
           (pt_lvl_terminal(&as->pt, lvl) && !pte_valid(pte) &&
            (pt_lvlsize(&as->pt, lvl) <= (left * PAGE_SIZE)) &&
            ((addr % pt_lvlsize(&as->pt, lvl)) == 0));
}

static inline pte_t *mem_alloc_pt(addr_space_t *as, pte_t *parent, uint64_t lvl,
                                  uint64_t addr)
{
    /* Must have lock on as and va section to call */
    size_t ptsize = pt_size(&as->pt, lvl) / PAGE_SIZE;
    ppages_t ppage = mem_alloc_ppages(as->colors, ptsize, ptsize > 1 ? true : false);
    if (ppage.size == 0) return NULL;
    pte_set(parent, ppage.base, PTE_TABLE, PTE_HYP_FLAGS);
    fence_sync_write();
    pte_t *temp_pt = pt_get(&as->pt, lvl + 1, (void *)addr);
    memset(temp_pt, 0, PAGE_SIZE);
    return temp_pt;
}

static inline bool pt_pte_mappable(addr_space_t *as, pte_t *pte, uint64_t lvl,
                                   uint64_t left, uint64_t vaddr,
                                   uint64_t paddr)
{
    return !pte_valid(pte) &&
           (pt_lvlsize(&as->pt, lvl) <= (left * PAGE_SIZE)) &&
           (((uint64_t)vaddr % pt_lvlsize(&as->pt, lvl)) == 0) &&
           ((paddr % pt_lvlsize(&as->pt, lvl)) == 0);
}

static void mem_expand_pte(addr_space_t *as, uint64_t va, uint64_t lvl)
{
    /* Must have lock on as and va section to call */

    if (as->pt.dscr->lvls - 1 <= lvl) {
        /* no more levels to expand */
        return;
    }

    pte_t *pte = pt_get_pte(&as->pt, lvl, (void *)va);

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
            tlb_inv_va(&cpu.as, (void *)va);

            /**
             *  Now traverse the new next level page table to replicate the
             * original mapping.
             */

            lvl++;
            uint64_t paddr = pte_addr(&pte_val);
            uint64_t entry = pt_getpteindex(&as->pt, pte, lvl);
            uint64_t nentries = pt_nentries(&as->pt, lvl);
            uint64_t lvlsz = pt_lvlsize(&as->pt, lvl);
            uint64_t type = pt_pte_type(&as->pt, lvl);
            uint64_t flags = as->type == AS_HYP ? PTE_HYP_FLAGS : PTE_VM_FLAGS;

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

static void mem_inflate_pt(addr_space_t *as, uint64_t va, uint64_t length)
{
    /* Must have lock on as and va section to call */

    /**
     * For each level in the pt, expand each entry in the specified range
     * as a next level page table.
     */
    for (int lvl = 0; lvl < as->pt.dscr->lvls - 1; lvl++) {
        uint64_t vaddr = va;
        uint64_t lvlsz = pt_lvlsize(&as->pt, lvl);
        while (vaddr < (va + length)) {
            mem_expand_pte(as, vaddr, lvl);
            vaddr += lvlsz;
        }
    }
}

void *mem_alloc_vpage(addr_space_t *as, enum AS_SEC section, void *at, size_t n)
{
    int lvl = 0;
    int entry = 0;
    int nentries = 0;
    int lvlsze = 0;
    int count = 0;
    void *addr = NULL;
    void *vpage = NULL;
    void *top = (void *)-1;
    pte_t *pte = NULL;
    bool failed = false;

    // TODO: maybe some bound checking here would be nice
    section_t *sec = &sections[as->type].sec[section];
    if (at != NULL) {
        if (sec != mem_find_sec(as, at)) return NULL;
        addr = at;
    } else {
        addr = sec->beg;
    }
    top = sec->end;
    addr = (void *)((uint64_t)addr & ~(PAGE_SIZE - 1));

    spin_lock(&as->lock);
    if (sec->shared) spin_lock(&sec->lock);

    while (count < n && !failed) {
        // check if there is still enough space in as
        if (((uint64_t)top + 1 - (uint64_t)addr) / PAGE_SIZE < n) {
            vpage = NULL;
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
                vpage = NULL;
                if (at != NULL) {
                    failed = true;
                    break;
                }
            } else if(!pte_valid(pte)) {
                if(pte_allocable(as, pte, lvl, n - count, (uint64_t)addr)) {
                    if (count == 0) vpage = (void *)addr;
                    count += (lvlsze / PAGE_SIZE);
                } else {
                    if (mem_alloc_pt(as, pte, lvl, (uint64_t)addr) == NULL) {
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
    if (vpage != NULL && !failed) {
        count = 0;
        addr = vpage;
        int lvl = 0;
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

void mem_free_vpage(addr_space_t *as, void *at, size_t n, bool free_ppages)
{
    void *vaddr = at;
    void *top = at + (n * PAGE_SIZE);
    int lvl = 0;

    spin_lock(&as->lock);

    section_t *sec = mem_find_sec(as, at);
    if (sec->shared) spin_lock(&sec->lock);

    while (vaddr < top) {
        pte_t *pte = pt_get_pte(&as->pt, lvl, vaddr);
        if (pte == NULL) {
            ERROR("invalid pte while freeing vpages");
        } else if (!pte_valid(pte)) {
            uint64_t lvlsz = pt_lvlsize(&as->pt, lvl);
            vaddr += lvlsz;
        } else if (pte_table(&as->pt, pte, lvl)) {
            lvl++;
        } else {
            uint64_t entry = pt_getpteindex(&as->pt, pte, lvl);
            uint64_t nentries = pt_nentries(&as->pt, lvl);
            uint64_t lvlsz = pt_lvlsize(&as->pt, lvl);

            while ((entry < nentries) && (vaddr < top)) {
                if (!pte_table(&as->pt, pte, lvl)) {
                    void *vpage_base =
                        (void *)(((uint64_t)vaddr) & ~(lvlsz - 1));

                    if (vaddr > vpage_base || top < (vpage_base + lvlsz)) {
                        mem_expand_pte(as, (uint64_t)vaddr, lvl);
                        lvl++;
                        break;
                    }

                    if (free_ppages) {
                        uint64_t paddr = pte_addr(pte);
                        ppages_t ppages =
                            mem_ppages_get(paddr, lvlsz / PAGE_SIZE);
                        mem_free_ppages(&ppages);
                    }

                    *pte = 0;
                    tlb_inv_va(&cpu.as, (void *)vaddr);

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

int mem_map(addr_space_t *as, void *va, ppages_t *ppages, size_t n,
            uint64_t flags)
{
    size_t count = 0;
    pte_t *pte = NULL;
    void *vaddr = (void *)(((uint64_t)va) & ~(PAGE_SIZE - 1));

    section_t *sec = mem_find_sec(as, vaddr);

    if ((sec == NULL) || (sec != mem_find_sec(as, vaddr + n * PAGE_SIZE - 1)))
        return -1;

    spin_lock(&as->lock);
    if (sec->shared) spin_lock(&sec->lock);

    /**
     * TODO check if entry is reserved. Unrolling mapping if something
     * goes wrong.
     */

    if (ppages == NULL && !all_clrs(as->colors)) {
        ppages_t temp = mem_alloc_ppages(as->colors, n, false);
        if (temp.size < n) ERROR("failed to alloc colored physical pages");
        ppages = &temp;
    }

    if (ppages && !all_clrs(ppages->colors)) {
        uint64_t index = 0;
        mem_inflate_pt(as, (uint64_t)vaddr, n * PAGE_SIZE);
        for (int i = 0; i < ppages->size; i++) {
            pte = pt_get_pte(&as->pt, as->pt.dscr->lvls - 1, vaddr);
            index = pp_next_clr(ppages->base, index, ppages->colors);
            uint64_t paddr = ppages->base + (index * PAGE_SIZE);
            pte_set(pte, paddr, PTE_PAGE, flags);
            vaddr += PAGE_SIZE;
            index++;
        }
    } else {
        uint64_t paddr = ppages ? ppages->base : 0;
        while (count < n) {
            int lvl = 0;
            for (lvl = 0; lvl < as->pt.dscr->lvls; lvl++) {
                pte = pt_get_pte(&as->pt, lvl, vaddr);
                if (pt_lvl_terminal(&as->pt, lvl)) {
                    if (pt_pte_mappable(as, pte, lvl, n - count,
                                        (uint64_t)vaddr, ppages ? paddr : 0)) {
                        break;
                    } else if (!pte_valid(pte)) {
                        mem_alloc_pt(as, pte, lvl, (uint64_t)vaddr);
                    } else if (!pte_table(&as->pt, pte, lvl)) {
                        ERROR("trying to override previous mapping");
                    }
                }
            }

            uint64_t entry = pt_getpteindex(&as->pt, pte, lvl);
            uint64_t nentries = pt_nentries(&as->pt, lvl);
            uint64_t lvlsz = pt_lvlsize(&as->pt, lvl);

            while ((entry < nentries) && (count < n) &&
                   (n - count >= lvlsz / PAGE_SIZE)) {
                if (ppages == NULL) {
                    ppages_t temp =
                        mem_alloc_ppages(as->colors, lvlsz / PAGE_SIZE, true);
                    if (temp.size < lvlsz / PAGE_SIZE) {
                        if (lvl == (as->pt.dscr->lvls - 1)) {
                            // TODO: free previously allocated pages
                            ERROR("failed to alloc physical pages");
                        } else {
                            pte = pt_get_pte(&as->pt, lvl, vaddr);
                            if (!pte_valid(pte)) {
                                mem_alloc_pt(as, pte, lvl, (uint64_t)vaddr);
                            }
                            break;
                        }
                    }
                    paddr = temp.base;
                }
                pte_set(pte, paddr, pt_pte_type(&as->pt, lvl), flags);
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

    return 0;
}

int mem_map_reclr(addr_space_t *as, void *va, ppages_t *ppages, size_t n,
                  uint64_t flags)
{
    if (ppages == NULL) {
        ERROR("no indication on what to recolor");
    }

    /**
     * Count how many pages are not colored in original images.
     * Allocate the necessary colored pages.
     * Mapped onto hypervisor address space.
     */
    uint64_t reclrd_num =
        n / (COLOR_NUM * COLOR_SIZE) * COLOR_SIZE *
        bitmap_count((bitmap_t)&as->colors, 0, COLOR_NUM, false);
    uint64_t clr_offset = (ppages->base / PAGE_SIZE) % (COLOR_NUM * COLOR_SIZE);
    for (int i = 0; i < (n % (COLOR_NUM * COLOR_SIZE)); i++) {
        if (!bitmap_get((bitmap_t)&as->colors,
                        (i + clr_offset) / COLOR_SIZE % COLOR_NUM))
            reclrd_num++;
    }

   /**
     * If the address space was not assigned any specific color,
     * or there are no pages to recolor defer to vanilla mapping.
     */
    if (all_clrs(as->colors) || (reclrd_num == 0)) {
        return mem_map(as, va, ppages, n, flags);
    }

    void *reclrd_va_base =
        mem_alloc_vpage(&cpu.as, SEC_HYP_VM, NULL, reclrd_num);
    ppages_t reclrd_ppages = mem_alloc_ppages(as->colors, reclrd_num, false);
    mem_map(&cpu.as, reclrd_va_base, &reclrd_ppages, reclrd_num, PTE_HYP_FLAGS);

    /**
     * Map original image onto hypervisor address space.
     */
    void *phys_va_base = mem_alloc_vpage(&cpu.as, SEC_HYP_VM, NULL, n);
    mem_map(&cpu.as, phys_va_base, ppages, n, PTE_HYP_FLAGS);

    pte_t *pte = NULL;
    void *vaddr = (void *)(((uint64_t)va) & ~(PAGE_SIZE - 1));
    uint64_t paddr = ppages->base;
    void *clrd_vaddr = reclrd_va_base;
    void *phys_va = phys_va_base;
    uint64_t index = 0;

    /**
     * Inflate reserved page tables to the last level. This assumes
     * coloring always needs the finest grained mapping possible.
     */
    mem_inflate_pt(as, (uint64_t)vaddr, n * PAGE_SIZE);

    for (int i = 0; i < n; i++) {
        pte = pt_get_pte(&as->pt, as->pt.dscr->lvls - 1, vaddr);

        /**
         * If image page is already color, just map it.
         * Otherwise first copy it to the previously allocated pages.
         */
        if (bitmap_get((bitmap_t)&as->colors,
                       ((i + clr_offset) / COLOR_SIZE % COLOR_NUM))) {
            pte_set(pte, paddr, PTE_PAGE, flags);

        } else {
            memcpy(clrd_vaddr, phys_va, PAGE_SIZE);
            index = pp_next_clr(reclrd_ppages.base, index, as->colors);
            uint64_t clrd_paddr = reclrd_ppages.base + (index * PAGE_SIZE);
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
    ppages_t unused_pages = {
        .base = ppages->base,
        .size = reclrd_num,
        .colors = ~as->colors
    };
    mem_free_ppages(&unused_pages);

    mem_free_vpage(&cpu.as, reclrd_va_base, reclrd_num, false);
    mem_free_vpage(&cpu.as, phys_va_base, n, false);

    return 0;
}

bool mem_are_ppages_reserved_in_pool(page_pool_t *ppool, ppages_t *ppages)
{
    bool reserved = false;
    bool rgn_found = range_in_range(ppages->base, ppages->size * PAGE_SIZE,
                                    ppool->base, ppool->size * PAGE_SIZE);
    if (rgn_found) {
        size_t numpages = ppages->size;
        size_t pageoff = NUM_PAGES(ppages->base - ppool->base);

        // verify these pages arent allocated yet
        bool is_alloced = bitmap_get(ppool->bitmap, pageoff);
        size_t avlbl_contig_pp = bitmap_count_consecutive(
            ppool->bitmap, ppool->size, pageoff, numpages);

        if (is_alloced || avlbl_contig_pp < numpages) {
            reserved = true;
        }
    }

    return reserved;
}

bool mem_are_ppages_reserved(ppages_t *ppages)
{
    bool reserved = false;
    list_foreach(page_pool_list, page_pool_t, pool)
    {
        bool is_in_rgn = range_in_range(ppages->base, ppages->size * PAGE_SIZE,
                                        pool->base, pool->size * PAGE_SIZE);

        if (is_in_rgn) {
            reserved = mem_are_ppages_reserved_in_pool(pool, ppages);
            break;
        }
    }

    return reserved;
}

bool mem_reserve_ppool_ppages(page_pool_t *pool, ppages_t *ppages)
{
    bool is_in_rgn = range_in_range(ppages->base, ppages->size * PAGE_SIZE,
                                    pool->base, pool->size * PAGE_SIZE);
    if (!is_in_rgn) return true;

    size_t numpages = ppages->size;
    size_t pageoff = NUM_PAGES(ppages->base - pool->base);

    bool was_free = true;
    if (mem_are_ppages_reserved_in_pool(pool, ppages)) {
        was_free = false;
    }

    bitmap_set_consecutive(pool->bitmap, pageoff, numpages);
    pool->free -= numpages;

    return is_in_rgn && was_free;
}

bool mem_reserve_ppages_in_pool_list(list_t *page_pool_list, ppages_t *ppages)
{
    bool reserved = false;
    list_foreach((*page_pool_list), page_pool_t, pool)
    {
        bool is_in_rgn = range_in_range(ppages->base, ppages->size * PAGE_SIZE,
                                        pool->base, pool->size * PAGE_SIZE);
        if (is_in_rgn) {
            reserved = mem_reserve_ppool_ppages(pool, ppages);
            break;
        }
    }

    return reserved;
}

bool mem_reserve_ppages(ppages_t *ppages)
{
    return mem_reserve_ppages_in_pool_list(&page_pool_list, ppages);
}

int mem_map_dev(addr_space_t *as, void *va, uint64_t base, size_t n)
{
    ppages_t pages = mem_ppages_get(base, n);
    return mem_map(as, va, &pages, n,
                   as->type == AS_HYP ? PTE_HYP_DEV_FLAGS : PTE_VM_DEV_FLAGS);
}

void *mem_alloc_page(size_t n, enum AS_SEC sec, bool phys_aligned)
{
    void *vpage = NULL;
    ppages_t ppages = mem_alloc_ppages(cpu.as.colors, n, phys_aligned);

    if (ppages.size == n) {
        vpage = mem_alloc_vpage(&cpu.as, sec, NULL, n);

        if (vpage == NULL) {
            // TODO: free allocated ppage
            ERROR("failed to allocate virtual page");
        } else {
            mem_map(&cpu.as, vpage, &ppages, n, PTE_HYP_FLAGS);
        }
    }

    return vpage;
}

bool root_pool_set_up_bitmap(uint64_t load_addr)
{
    size_t image_size = (size_t)(&_image_end - &_image_start);
    size_t config_size = (size_t)(&_config_end - &_config_start);
    size_t cpu_size = platform.cpu_num * (ALIGN(sizeof(struct cpu), PAGE_SIZE) +
                                          (PT_SIZE * (PT_LVLS - 1)));

    uint64_t bitmap_size = root_pool.size / (8 * PAGE_SIZE) +
                           ((root_pool.size % (8 * PAGE_SIZE) != 0) ? 1 : 0);
    if (root_pool.size <= bitmap_size) return false;
    uint64_t bitmap_base = load_addr + image_size + config_size + cpu_size;

    ppages_t bitmap_pp = mem_ppages_get(bitmap_base, bitmap_size);
    bitmap_t root_bitmap =
        mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL, bitmap_size);
    if (root_bitmap == NULL) return false;

    root_pool.bitmap = root_bitmap;
    mem_map(&cpu.as, root_pool.bitmap, &bitmap_pp, bitmap_size, PTE_HYP_FLAGS);
    memset(root_pool.bitmap, 0, bitmap_size * PAGE_SIZE);

    return mem_reserve_ppool_ppages(&root_pool, &bitmap_pp);
}

bool pp_root_reserve_hyp_mem(uint64_t load_addr)
{
    size_t image_size = (size_t)(&_image_end - &_image_start);
    size_t config_size = (size_t)(&_config_end - &_config_start);
    uint64_t cpu_size =
        platform.cpu_num *
        (ALIGN(sizeof(struct cpu), PAGE_SIZE) + (PT_SIZE * (PT_LVLS - 1)));
    uint64_t cpu_base_addr = load_addr + image_size + config_size;

    ppages_t images_ppages = mem_ppages_get(load_addr, NUM_PAGES(image_size));
    ppages_t cpu_ppages = mem_ppages_get(cpu_base_addr, NUM_PAGES(cpu_size));

    bool image_reserved = mem_reserve_ppool_ppages(&root_pool, &images_ppages);
    bool cpu_reserved = mem_reserve_ppool_ppages(&root_pool, &cpu_ppages);

    return image_reserved && cpu_reserved;
}

static bool pp_root_init(uint64_t load_addr, struct mem_region *root_region)
{
    memset(&root_pool, 0, sizeof(page_pool_t));

    root_pool.base = ALIGN(root_region->base, PAGE_SIZE);
    root_pool.size =
        root_region->size / PAGE_SIZE; /* TODO: what if not aligned? */
    root_pool.free = root_pool.size;

    if (!root_pool_set_up_bitmap(load_addr)) {
        return false;
    }
    if (!pp_root_reserve_hyp_mem(load_addr)) {
        return false;
    }

    root_pool.last = 0;
    return true;
}

static void pp_init(page_pool_t *pool, uint64_t base, size_t size)
{
    ppages_t pages;

    if (pool == NULL) return;

    memset(pool, 0, sizeof(page_pool_t));
    pool->base = ALIGN(base, PAGE_SIZE);
    pool->size = NUM_PAGES(size);
    uint64_t bitmap_size =
        pool->size / (8 * PAGE_SIZE) + !!(pool->size % (8 * PAGE_SIZE) != 0);

    if (size <= bitmap_size) return;

    pages = mem_alloc_ppages(cpu.as.colors, bitmap_size, false);
    if (pages.size != bitmap_size) return;

    if ((pool->bitmap = mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL,
                                        bitmap_size)) == NULL)
        return;

    mem_map(&cpu.as, pool->bitmap, &pages, bitmap_size, PTE_HYP_FLAGS);
    memset(pool->bitmap, 0, bitmap_size * PAGE_SIZE);

    pool->last = 0;
    pool->free = pool->size - bitmap_size;
}

bool mem_reserve_config(uint64_t config_addr, page_pool_t *pool)
{
    if (config_found) return true;

    bool cfg_in_pool = range_in_range(config_addr, vm_config_ptr->config_size,
                                      pool->base, pool->size * PAGE_SIZE);
    if (cfg_in_pool) {
        size_t n_pg = NUM_PAGES(vm_config_ptr->config_size);
        ppages_t pp = mem_ppages_get(config_addr, n_pg);
        if (!mem_reserve_ppool_ppages(pool, &pp)) return false;
        config_found = true;
    }
    return true;
}

bool mem_reserve_vm_cfg(page_pool_t *pool)
{
    /* for every vm config */
    for (int i = 0; i < vm_config_ptr->vmlist_size; i++) {
        vm_config_t *vm_cfg = &vm_config_ptr->vmlist[i];
        /* for every mem region */
        for (int j = 0; j < vm_cfg->platform.region_num; j++) {
            struct mem_region *reg = &vm_cfg->platform.regions[j];
            if (reg->place_phys) {
                size_t n_pg = NUM_PAGES(reg->size);
                ppages_t ppages = mem_ppages_get(reg->phys, n_pg);
                if (!mem_reserve_ppool_ppages(pool, &ppages)) {
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < vm_config_ptr->shmemlist_size; i++) {
        shmem_t *shmem = &vm_config_ptr->shmemlist[i];
        if(shmem->place_phys) {
            size_t n_pg = NUM_PAGES(shmem->size);
            ppages_t ppages = mem_ppages_get(shmem->phys, n_pg);
            if (!mem_reserve_ppool_ppages(pool, &ppages)) {
                return false;
            }           
            shmem->phys = ppages.base;
        }
    }

    return true;
}

/* true: no reserving necessary, or reserve was successful
 * false: nedded to reserve memory, but error occured */
bool mem_reserve_physical_memory(uint64_t config_addr, page_pool_t *pool)
{
    if (pool == NULL) return false;

    if (!mem_reserve_vm_cfg(pool)) {
        return false;
    }

    if (!mem_reserve_config(config_addr, pool)) {
        return false;
    }

    return true;
}

bool mem_create_ppools(uint64_t config_addr, struct mem_region *root_mem_region)
{
    /* Add remaining memory regions to a temporary page pool list */
    objcache_init(&pagepool_cache, sizeof(page_pool_t), SEC_HYP_GLOBAL, true);
    for (size_t i = 0; i < platform.region_num; i++) {
        if (&platform.regions[i] != root_mem_region) {
            struct mem_region *reg = &platform.regions[i];
            page_pool_t *pool = objcache_alloc(&pagepool_cache);
            if (pool != NULL) {
                pp_init(pool, reg->base, reg->size);
                if (!mem_reserve_physical_memory(config_addr, pool)) {
                    return false;
                }
                list_push(&page_pool_list, &pool->node);
            }
        }
    }

    return true;
}

bool mem_map_vm_config(uint64_t config_addr)
{
    vm_config_ptr = mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL, 1);
    if (vm_config_ptr == NULL) return false;

    ppages_t pages = mem_ppages_get(config_addr, 1);
    mem_map(&cpu.as, vm_config_ptr, &pages, 1, PTE_HYP_FLAGS);
    if (vm_config_ptr->config_header_size > PAGE_SIZE) {
        size_t n =
            NUM_PAGES(((uint64_t)vm_config_ptr->config_header_size) - PAGE_SIZE);
        void *va = mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL,
                                   vm_config_ptr + PAGE_SIZE, n);
        if (va == NULL) return false;
        pages = mem_ppages_get(config_addr + PAGE_SIZE, n);
        mem_map(&cpu.as, va, &pages, n, PTE_HYP_FLAGS);
    }
    config_adjust_to_va(vm_config_ptr, config_addr);

    return true;
}

bool mem_init_vm_config(uint64_t config_addr)
{
    if (!mem_map_vm_config(config_addr)) {
        return false;
    }

    if (!mem_reserve_physical_memory(config_addr, &root_pool)) {
        return false;
    }

    return true;
}

struct mem_region *mem_find_root_region(uint64_t load_addr)
{
    size_t image_size = (size_t)(&_image_end - &_image_start);

    /* Find the root memory region in which the hypervisor was loaded. */
    struct mem_region *root_mem_region = NULL;
    for (size_t i = 0; i < platform.region_num; i++) {
        struct mem_region *region = &(platform.regions[i]);
        bool is_in_rgn =
            range_in_range(load_addr, image_size, region->base, region->size);
        if (is_in_rgn) {
            root_mem_region = region;
            break;
        }
    }

    return root_mem_region;
}

bool mem_setup_root_pool(uint64_t load_addr,
                         struct mem_region **root_mem_region)
{
    *root_mem_region = mem_find_root_region(load_addr);
    if (*root_mem_region == NULL) {
        return false;
    }

    return pp_root_init(load_addr, *root_mem_region);
}

void *copy_space(void *base, const uint64_t size, ppages_t *pages)
{
    *pages = mem_alloc_ppages(cpu.as.colors, NUM_PAGES(size), false);
    void *va = mem_alloc_vpage(&cpu.as, SEC_HYP_PRIVATE, NULL, NUM_PAGES(size));
    mem_map(&cpu.as, va, pages, NUM_PAGES(size), PTE_HYP_FLAGS);
    memcpy(va, base, size);

    return va;
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
void color_hypervisor(const uint64_t load_addr, const uint64_t config_addr)
{
    volatile static pte_t shared_pte;
    void *va = NULL;
    cpu_t *cpu_new;
    ppages_t p_cpu;
    ppages_t p_image;
    ppages_t p_bitmap;
    ppages_t p_interface;

    size_t image_size = (size_t)(&_image_end - &_image_start);
    size_t cpu_boot_size =
        ALIGN(sizeof(cpu_t) + (PT_SIZE * (PT_LVLS - 1)), PAGE_SIZE);
    size_t config_size = (size_t)(&_config_end - &_config_start);
    size_t bitmap_size = (root_pool.size / (8 * PAGE_SIZE) +
                          !!(root_pool.size % (8 * PAGE_SIZE) != 0)) *
                         PAGE_SIZE;
    uint64_t colors = vm_config_ptr->hyp_colors;

    /* Set hypervisor colors in current address space */
    cpu.as.colors = vm_config_ptr->hyp_colors;

    /*
     * Copy the CPU space into a colored region.
     *
     * It's not possible to simply copy the CPU space as-is, since there are a
     * few pointers and structures that would point to the old, non-colored
     * data.
     *
     * the new CPU region is created, cleaned, prepared and finally mapped.
     */
    cpu_new = copy_space((void *)BAO_CPU_BASE, sizeof(cpu_t), &p_cpu);
    memset(cpu_new->root_pt, 0, sizeof(cpu_new->root_pt));
    as_init(&cpu_new->as, AS_HYP_CPY, 0, (pte_t *)cpu_new->root_pt, colors);
    va = mem_alloc_vpage(&cpu_new->as, SEC_HYP_PRIVATE, (void *)BAO_CPU_BASE,
                         NUM_PAGES(sizeof(cpu_t)));

    if (va != (void *)BAO_CPU_BASE)
        ERROR("Can't allocate virtual address for cpuspace");

    mem_map(&cpu_new->as, va, &p_cpu, NUM_PAGES(sizeof(cpu_t)), PTE_HYP_FLAGS);

    /*
     * Copy the Hypervisor image and root page pool bitmap into a colored
     * region.
     *
     * CPU_MASTER allocates, copies and maps the image and the root page pool
     * bitmap on a shared space, whilst other CPUs only have to copy the image
     * from the CPU_MASTER in order to be able to access it.
     */
    if (cpu.id == CPU_MASTER) {
        copy_space(&_image_start, image_size, &p_image);
        va = mem_alloc_vpage(&cpu_new->as, SEC_HYP_IMAGE, &_image_start,
                             NUM_PAGES(image_size));

        if (va != &_image_start)
            ERROR("Can't allocate virtual address for Bao Image");

        mem_map(&cpu_new->as, va, &p_image,
                NUM_PAGES(image_size), PTE_HYP_FLAGS);
        shared_pte = pte_addr(pt_get_pte(&cpu_new->as.pt, 0, &_image_start));
    } else {
        pte_t *image_pte = pt_get_pte(&cpu_new->as.pt, 0, &_image_start);

        /* Wait for CPU_MASTER to get image page table entry */
        while (shared_pte == 0);
        pte_set(image_pte, shared_pte, PTE_TABLE, PTE_HYP_FLAGS);
    }

    /*
     * Each CPU space has a public interface that needs to be accessible from
     * all the other CPUs, it is therefore needed to allocate this additional
     * virtual page into global space to allow communication.
     */
    uint64_t p_intferface_addr;
    mem_translate(&cpu.as, &cpu_new->interface, &p_intferface_addr);
    p_interface = mem_ppages_get(
        p_intferface_addr,
        NUM_PAGES(sizeof(cpu_new->interface)));
    va = mem_alloc_vpage(
        &cpu_new->as, SEC_HYP_GLOBAL,
        &_cpu_if_base + (cpu.id * sizeof(cpu_new->interface)),
        NUM_PAGES(sizeof(cpu_new->interface)));

    if (va != &_cpu_if_base + (cpu.id * sizeof(cpu_new->interface)))
        ERROR("Can't allocate address for cpu interface");

    mem_map(&cpu_new->as, va, &p_interface,
            NUM_PAGES(sizeof(cpu_new->interface)),
            PTE_HYP_FLAGS);
    cpu_sync_barrier(&cpu_glb_sync);

    /*
     * CPU_MASTER will also take care of mapping the configuration onto the new
     * space.
     *
     * The root page pool bitmap tracks all the physical allocation, so it
     * needs to be the last thing to be copied, as after that, no physical
     * allocation will be tracked.
     */
    if (cpu.id == CPU_MASTER) {
        /* Map configuration onto new space */
        size_t config_size = NUM_PAGES(vm_config_ptr->config_header_size);
        ppages_t config_pages = mem_ppages_get(config_addr, config_size);
        mem_map(&cpu_new->as, vm_config_ptr, &config_pages, config_size,
                PTE_HYP_FLAGS);

        /* Copy root pool bitmap */
        copy_space(root_pool.bitmap, bitmap_size, &p_bitmap);
        va = mem_alloc_vpage(&cpu_new->as, SEC_HYP_GLOBAL,
                             (void *)root_pool.bitmap,
                             NUM_PAGES(bitmap_size));

        if (va != (void *)root_pool.bitmap)
            ERROR("Can't allocate address for cpu interface");

        mem_map(&cpu_new->as, va, &p_bitmap,
                NUM_PAGES(bitmap_size), PTE_HYP_FLAGS);
    }
    cpu_sync_barrier(&cpu_glb_sync);

    uint64_t p_root_pt_addr;
    mem_translate(&cpu.as, cpu_new->root_pt, &p_root_pt_addr);
    switch_space(cpu_new, p_root_pt_addr);

    /**
     * Make sure the new physical pages containing image and cpu are flushed
     * to main memmory
     */

    cache_flush_range(&_image_start, image_size);
    cache_flush_range(&_cpu_private_beg, sizeof(cpu_t));

    /**
     * Bao's code from here's on still uses the static global variables, so
     * they need to be updated.
     *
     * The synchronization objects are in an inconsistent state, and they need
     * to be re-initialized before they get used again, so CPUs need a way to
     * communicate between themselves without an explicit barrier. To
     * accomplish this a static global variable is used.
     */
    if (cpu.id == CPU_MASTER) {
        cpu_sync_init(&cpu_glb_sync, platform.cpu_num);
        shared_pte = 0;
    } else {
        while (shared_pte != 0);
    }

    as_init(&cpu.as, AS_HYP, 0, (pte_t *)cpu.root_pt, colors);

    /*
     * Clear the old region that have been copied.
     *
     * CPU space regions and Hypervisor image region are contingent, starting
     * from `load_addr`. The bitmap region is on top of the root pool region.
     */
    if (cpu.id == CPU_MASTER) {
        p_image = mem_ppages_get(load_addr, NUM_PAGES(image_size));

        va = mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL, p_image.size);
        mem_map(&cpu.as, va, &p_image, p_image.size, PTE_HYP_FLAGS);
        memset(va, 0, p_image.size * PAGE_SIZE);
        mem_free_vpage(&cpu.as, va, p_image.size, true);

        p_bitmap = mem_ppages_get(load_addr + image_size + config_size +
                                      (cpu_boot_size * platform.cpu_num),
                                  NUM_PAGES(bitmap_size));

        va = mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL, p_bitmap.size);
        mem_map(&cpu.as, va, &p_bitmap, p_bitmap.size, PTE_HYP_FLAGS);
        memset(va, 0, p_bitmap.size * PAGE_SIZE);
        mem_free_vpage(&cpu.as, va, p_bitmap.size, true);
    }

    p_cpu = mem_ppages_get(
        load_addr + image_size + config_size + (cpu_boot_size * cpu.id),
        cpu_boot_size / PAGE_SIZE);
    va = mem_alloc_vpage(&cpu.as, SEC_HYP_PRIVATE, NULL, p_cpu.size);
    mem_map(&cpu.as, va, &p_cpu, p_cpu.size, PTE_HYP_FLAGS);
    memset(va, 0, p_cpu.size * PAGE_SIZE);
    mem_free_vpage(&cpu.as, va, p_cpu.size, false);
}

void as_init(addr_space_t *as, enum AS_TYPE type, uint64_t id, void *root_pt,
             uint64_t colors)
{
    as->type = type;
    as->pt.dscr =
        type == AS_HYP || type == AS_HYP_CPY ? hyp_pt_dscr : vm_pt_dscr;
    as->colors = colors;
    as->lock = SPINLOCK_INITVAL;
    as->id = id;

    if (root_pt == NULL) {
        size_t n = pt_size(&as->pt, 0) / PAGE_SIZE;
        root_pt = mem_alloc_page(n, 
            type == AS_HYP || type == AS_HYP_CPY ? SEC_HYP_PRIVATE : SEC_HYP_VM, 
            true);
        memset(root_pt, 0, n * PAGE_SIZE);
    }
    as->pt.root_flags = 0;
    as->pt.root = (pte_t *)root_pt;

    as_arch_init(as);
}

void mem_init(uint64_t load_addr, uint64_t config_addr)
{
    as_init(&cpu.as, AS_HYP, 0, cpu.root_pt, 0);

    static struct mem_region *root_mem_region = NULL;

    if (cpu.id == CPU_MASTER) {
        cache_enumerate();

        if (!mem_setup_root_pool(load_addr, &root_mem_region)) {
            ERROR("couldn't not initialize root pool");
        }

        /* Insert root pool in pool list */
        list_init(&page_pool_list);
        list_push(&page_pool_list, &(root_pool.node));

        if (config_is_builtin()) {
            config_addr =
                (uint64_t)(&_config_start - &_image_start) + load_addr;
        }

        if (!mem_init_vm_config(config_addr)) {
            ERROR("couldn't init config");
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    if (!all_clrs(vm_config_ptr->hyp_colors)) {
        color_hypervisor(load_addr, config_addr);
    }

    if (cpu.id == CPU_MASTER) {
        if (!mem_create_ppools(config_addr, root_mem_region)) {
            ERROR("couldn't create additional page pools");
        }

        if (!config_found)
            ERROR("config was not loaded in a defined platform region");
    }

    /* Wait for master core to initialize memory management */
    cpu_sync_barrier(&cpu_glb_sync);
}
