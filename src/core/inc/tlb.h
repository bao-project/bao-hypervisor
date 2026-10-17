/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __TLB_H__
#define __TLB_H__

#include <bao.h>
#include <arch/tlb.h>

#include <mem.h>

static inline void tlb_inv_va(struct addr_space* as, vaddr_t va)
{
    if (as->type == AS_HYP) {
        tlb_hyp_inv_va(va);
    } else if (as->type == AS_VM) {
        tlb_vm_inv_va(as->id, va);
        /* SMMUv3 stage-2 invalidation rides on this broadcast TLBI (DVM). */
    }
}

static inline void tlb_inv_all(struct addr_space* as)
{
    if (as->type == AS_HYP) {
        tlb_hyp_inv_all();
    } else if (as->type == AS_VM) {
        tlb_vm_inv_all(as->id);
        /* SMMUv3 stage-2 invalidation rides on this broadcast TLBI (DVM). */
    }
}

#endif
