/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef MEM_PROT_VMM_H
#define MEM_PROT_VMM_H

#include <page_table.h>

struct vm_install_info {
    vaddr_t base;
    pte_t vm_section_pte;
};

#endif /* MEM_PROT_VMM_H */
