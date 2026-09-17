/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <fences.h>
#include <config_defs.h>

/* The top-level page table entry of each vm's section, set by the master, copied by the others */
static pte_t vm_section_pte[CONFIG_VM_NUM];

#include <config.h>
#include <mem.h>

void vm_mem_prot_init(struct vm* vm, const struct vm_config* vm_config)
{
    as_init(&vm->mut->as, AS_VM, NULL, vm_config->colors);

    vm_section_pte[vm->id] =
        *pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, (vaddr_t)vm->mut->as.pt.root);
    fence_ord_write();
}

void vm_mem_prot_cpu_init(struct vm* vm)
{
    if (vm->master != cpu()->id) {
        pte_t* pte = pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, (vaddr_t)vm->mut->as.pt.root);
        *pte = vm_section_pte[vm->id];
        // We don't invalidate the TLB as we know there was no previous mapping or accesses to the
        // addresses in the VM section. Just make sure the write commited before leaving.
        fence_ord_write();
    }
}
