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
        // TODO: inval iommu tlbs
        //
        // The SMMU (see arch/armv8 smmuv3) caches stage-2 walks in its own
        // TLB/walk-cache and is NOT reached by the CPU-side TLBI above. The
        // current drivers rely on the assumption that a bound VM's stage-2
        // mappings are static after bind, so this stays correct only while
        // nothing remaps an already-bound VM. Anyone adding dynamic stage-2
        // remapping MUST hook an IOMMU stage-2 invalidation here (by VMID, or
        // by IPA once supported) or the SMMU will translate against stale
        // tables.
    }
}

static inline void tlb_inv_all(struct addr_space* as)
{
    if (as->type == AS_HYP) {
        tlb_hyp_inv_all();
    } else if (as->type == AS_VM) {
        tlb_vm_inv_all(as->id);
        // TODO: inval iommu tlbs
        //
        // Same caveat as tlb_inv_va(): the SMMU's stage-2 TLB/walk-cache is not
        // invalidated by the CPU-side TLBI above. Correct today only because a
        // bound VM's stage-2 is static after bind; a dynamic remap MUST also
        // invalidate the IOMMU (SMMU) here.
    }
}

#endif
