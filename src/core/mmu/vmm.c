/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vmm.h>
#include <io.h>
#include <fences.h>

void vmm_io_init(void)
{
    io_init();
}

struct vm_install_info vmm_get_vm_install_info(struct vm_allocation* vm_alloc)
{
    struct vm_install_info info = {
        .base = vm_alloc->base,
        .vm_section_pte = *pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, vm_alloc->base),
    };
    return info;
}

void vmm_vm_install(struct vm_install_info* install_info)
{
    pte_t* pte = pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, (vaddr_t)install_info->base);
    *pte = install_info->vm_section_pte;
    // We don't invalidate the TLB as we know there was no previous mapping or accesses to the
    // addresses in the VM section. Just make sure the write commited before leaving.
    fence_ord_write();
}
