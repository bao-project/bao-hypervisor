/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/sysregs.h>
#include <arch/fences.h>
#include <tlb.h>

void vcpu_arch_profile_init(struct vcpu* vcpu, struct vm* vm) {
    paddr_t root_pt_pa;
    mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &root_pt_pa);
    sysreg_vttbr_el2_write((((uint64_t)vm->id << VTTBR_VMID_OFF) & VTTBR_VMID_MSK) |
                       (root_pt_pa & ~VTTBR_VMID_MSK));

    ISB();  // make sure vmid is commited befor tlbi
    tlb_vm_inv_all(vm->id);
}
