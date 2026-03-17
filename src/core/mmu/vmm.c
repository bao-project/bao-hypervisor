/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file vmm.c
 * @brief This source file contains the implementation of VM management for MMU-based systems.
 * 
 */

#include <vmm.h>
#include <io.h>
#include <fences.h>

/**
 * @brief Initialize the IOMMU for VM management.
 * It configures the address space access control mechanism for the system's IO devices.
 * @see io_init
 * 
 */
void vmm_io_init(void)
{
    io_init();
}

/**
 * @brief Retrieve a VM's installation information from its allocation data.
 * @param vm_alloc Pointer to VM allocation structure
 * @return struct vm_install_info Installation information for the VM
 * @see vm_install_info, vm_allocation, pt_get_pte, cpu(), pagetable, vaddr_t
 *      VM_SHARED_PT_LVL
 */
struct vm_install_info vmm_get_vm_install_info(struct vm_allocation* vm_alloc)
{
    struct vm_install_info info = {
        .base = vm_alloc->base,
        .vm_section_pte = *pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, vm_alloc->base),
    };
    return info;
}

/**
 * @brief Installs a VM in its allocated page tables.
 * @param install_info Pointer to VM installation information
 * @see pte_t, vaddr_t pt_get_pte, fence_ord_write, vm_install_info, cpu(), addr_space
 * @see page_table
 */
void vmm_vm_install(struct vm_install_info* install_info)
{
    pte_t* pte = pt_get_pte(&cpu()->as.pt, VM_SHARED_PT_LVL, (vaddr_t)install_info->base);
    *pte = install_info->vm_section_pte;
    // We don't invalidate the TLB as we know there was no previous mapping or accesses to the
    // addresses in the VM section. Just make sure the write commited before leaving.
    fence_ord_write();
}
