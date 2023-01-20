/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VMM_H__
#define __VMM_H__

#include <bao.h>
#include <arch/vmm.h>
#include <vm.h>
#include <mem_prot/vmm.h>

void vmm_init();
void vmm_arch_init();

void vmm_io_init();

struct vm_install_info vmm_get_vm_install_info(struct vm_allocation *vm_alloc);
void vmm_vm_install(struct vm_install_info *install_info);

#endif /* __VMM_H__ */
