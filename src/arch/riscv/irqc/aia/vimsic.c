/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/platform.h>
#include <mem.h>
#include <imsic.h>

/** We only support 1 guest per hart at the moment */
#define VS_FILE_IDX 1

void vimsic_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp)
{
    struct vcpu* vcpu = cpu()->vcpu;
    cpuid_t pcpu_id = vcpu->phys_id;
    vcpuid_t vcpu_id = vcpu->id;
    paddr_t imsic_paddr;
    vaddr_t imsic_vaddr;

    imsic_vaddr = vm_irqc_dscrp->aia.imsic.base + (PAGE_SIZE * vcpu_id);

    imsic_paddr = platform.arch.irqc.aia.imsic.base + (PLAT_IMSIC_HART_SIZE * pcpu_id) +
        (PAGE_SIZE * VS_FILE_IDX);

    if (imsic_vaddr != INVALID_VA) {
        mem_alloc_map_dev(&vm->as, SEC_VM_ANY, imsic_vaddr, imsic_paddr, 1);
    }
}
