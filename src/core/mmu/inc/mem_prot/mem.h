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

#ifndef __MEM_PROT_H__
#define __MEM_PROT_H__

#include <bao.h>
#include <arch/mem.h>
#include <page_table.h>
#include <spinlock.h>

enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY };

#define HYP_ASID  0
struct addr_space {
    struct page_table pt;
    enum AS_TYPE type;
    colormap_t colors;
    asid_t id;
    spinlock_t lock;
};

typedef pte_t mem_flags_t;

void as_init(struct addr_space* as, enum AS_TYPE type, asid_t id, 
            pte_t* root_pt, colormap_t colors);

#endif /* __MEM_PROT_H__ */
