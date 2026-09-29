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
    as_init(&vm->as, AS_VM, NULL, vm_config->colors);

    vm_section_pte[vm->id] = *pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, (vaddr_t)vm->as.pt.root);
    fence_ord_write();
}

void vm_mem_prot_cpu_init(struct vm* vm)
{
    if (vm->master != cpu()->id) {
        pte_t* pte = pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, (vaddr_t)vm->as.pt.root);
        *pte = vm_section_pte[vm->id];
        // We don't invalidate the TLB as we know there was no previous mapping or accesses to the
        // addresses in the VM section. Just make sure the write commited before leaving.
        fence_ord_write();
    }
}

struct vcpu* vm_mem_prot_share_vcpu(struct vcpu* vcpu)
{
    /**
     * The cpu structure is private to each cpu, mapped at the same address on all of them, so the
     * vcpu it holds must be mapped in the global section as well to be reached by the other cpus.
     * The structure is page-aligned and, when the hypervisor is colored, its pages follow the
     * hypervisor colors from the first one, so the ppages that allocated them describe them again.
     */
    paddr_t base;
    size_t num_pages = NUM_PAGES(sizeof(struct cpu));
    if (!mem_translate(&cpu()->as, (vaddr_t)cpu(), &base)) {
        ERROR("Can't translate the cpu structure address\n");
    }
    struct ppages ppages = { .base = base, .num_pages = num_pages, .colors = cpu()->as.colors };
    vaddr_t va =
        mem_alloc_map(&cpu()->as, SEC_HYP_GLOBAL, &ppages, INVALID_VA, num_pages, PTE_HYP_FLAGS);
    if (va == INVALID_VA) {
        ERROR("Can't map the cpu structure in the global section\n");
    }
    return (struct vcpu*)(va + ((vaddr_t)vcpu - (vaddr_t)cpu()));
}
