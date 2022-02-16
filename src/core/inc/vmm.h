/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
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

struct vm_install_info vmm_get_vm_install_info(struct vm* vm);
void vmm_vm_install(struct vm* vm, struct vm_install_info *install_info);

#endif /* __VMM_H__ */
