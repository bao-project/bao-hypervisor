/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file vmm.c
 * @brief This source file contains the implementation of VM management for MPU-based systems.
 * 
 */

#include <bao.h>
#include <vmm.h>
#include <io.h>

/**
 * @brief Not implemented. The supported MPU-based systems do not rely on IOMMUs.
 */
void vmm_io_init() { }

/**
 * @brief Retrieve a VM's installation information from its allocation data.
 * @param vm_alloc Pointer to VM allocation structure
 * @return struct vm_install_info Installation information for the VM
 * @see vm_install_info, vm_allocation
 */
struct vm_install_info vmm_get_vm_install_info(struct vm_allocation* vm_alloc)
{
    return (struct vm_install_info){ vm_alloc->base, vm_alloc->size };
}

/**
 * @brief Install a VM in its allocated page tables.
 * @param install_info Pointer to VM installation information
 * @see vm_install_info, NUM_PAGES(), ppages, mem_ppages_get(), mem_alloc_map(),
 *      cpu(), SEC_HYP_VM, PTE_HYP_FLAGS, addr_space.
 */
void vmm_vm_install(struct vm_install_info* install_info)
{
    size_t num_pages = NUM_PAGES(install_info->size);
    struct ppages ppages = mem_ppages_get(install_info->base_addr, num_pages);
    mem_alloc_map(&cpu()->as, SEC_HYP_VM, &ppages, install_info->base_addr, num_pages,
        PTE_HYP_FLAGS);
}
