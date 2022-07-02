/**
 * SPDX-License-Identifier: GPL-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef MEM_PROT_VMM_H
#define MEM_PROT_VMM_H

#include <page_table.h>

struct vm_install_info {
    pte_t vm_section_pte;
};

#endif /* MEM_PROT_VMM_H */
