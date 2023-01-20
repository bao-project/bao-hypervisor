/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_TLB_H__
#define __ARCH_TLB_H__

#include <bao.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

static inline void tlb_hyp_inv_va(vaddr_t va)
{
    DSB(ish);
    arm_tlbi_vae2is(va);
    DSB(ish);
    ISB();
}

static inline void tlb_hyp_inv_all()
{
    DSB(ish);
    arm_tlbi_alle2is();
    DSB(ish);
    ISB();
}

static inline void tlb_vm_inv_va(asid_t vmid, vaddr_t va)
{
    uint64_t vttbr = 0;
    vttbr = sysreg_vttbr_el2_read();
    bool switch_vmid =
        bit64_extract(vttbr, VTTBR_VMID_OFF, VTTBR_VMID_LEN) != vmid;

    if (switch_vmid) {
        sysreg_vttbr_el2_write((((uint64_t)vmid << VTTBR_VMID_OFF) & VTTBR_VMID_MSK));
        DSB(ish);
        ISB();
    }

    arm_tlbi_ipas2e1is(va);

    if (switch_vmid) {
        DSB(ish);
        sysreg_vttbr_el2_write((((uint64_t)vmid << VTTBR_VMID_OFF) & VTTBR_VMID_MSK));
    }
}

static inline void tlb_vm_inv_all(asid_t vmid)
{
    uint64_t vttbr = 0;
    vttbr = sysreg_vttbr_el2_read();
    bool switch_vmid =
        bit64_extract(vttbr, VTTBR_VMID_OFF, VTTBR_VMID_LEN) != vmid;

    if (switch_vmid) {
        sysreg_vttbr_el2_write((((uint64_t)vmid << VTTBR_VMID_OFF) & VTTBR_VMID_MSK));
        DSB(ish);
        ISB();
    }

    arm_tlbi_vmalls12e1is();

    if (switch_vmid) {
        DSB(ish);
        sysreg_vttbr_el2_write((((uint64_t)vmid << VTTBR_VMID_OFF) & VTTBR_VMID_MSK));
    }
}

#endif /* __ARCH_TLB_H__ */
