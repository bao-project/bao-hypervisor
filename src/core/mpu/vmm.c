/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <vmm.h>
#include <io.h>

void vmm_io_init() {

}

struct vm_install_info vmm_get_vm_install_info(struct vm_allocation* vm_alloc) {
    return (struct vm_install_info) { vm_alloc->base,  vm_alloc->size };
}

void vmm_vm_install(struct vm_install_info *install_info) {
    size_t num_pages = NUM_PAGES(install_info->size);
    struct ppages ppages = 
        mem_ppages_get(install_info->base_addr, num_pages);
    mem_alloc_map(&cpu()->as, SEC_HYP_VM, &ppages, install_info->base_addr, 
        num_pages, PTE_HYP_FLAGS);
}
