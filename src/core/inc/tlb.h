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

#ifndef __TLB_H__
#define __TLB_H__

#include <bao.h>
#include <arch/tlb.h>

#include <mem.h>

static inline void tlb_inv_va(addr_space_t *as, void *va)
{
    if (as->type == AS_HYP) {
        tlb_hyp_inv_va(va);
    } else if (as->type == AS_VM) {
        tlb_vm_inv_va(as->id, va);
        // TODO: inval iommu tlbs
    }
}

static inline void tlb_inv_all(addr_space_t *as)
{
    if (as->type == AS_HYP) {
        tlb_hyp_inv_all();
    } else if (as->type == AS_VM) {
        tlb_vm_inv_all(as->id);
        // TODO: inval iommu tlbs
    }
}

#endif