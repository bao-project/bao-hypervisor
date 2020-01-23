/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __ARCH_TLB_H__
#define __ARCH_TLB_H__

#include <bao.h>
#include <platform.h>
#include <arch/sbi.h>

static inline void tlb_hyp_inv_va(void* va)
{
    sbi_remote_sfence_vma(platform.cpu_num - 1, 0, (unsigned long)va,
                          PAGE_SIZE);
}

static inline void tlb_hyp_inv_all()
{
    sbi_remote_sfence_vma(platform.cpu_num - 1, 0, 0, 0);
}

/**
 * TODO: change hart_mask to only take into account the vm physical cpus.
 */

static inline void tlb_vm_inv_va(uint64_t vmid, void* va)
{
    sbi_remote_hfence_gvma_vmid(platform.cpu_num - 1, 0, (unsigned long)va,
                                PAGE_SIZE, vmid);
}

static inline void tlb_vm_inv_all(uint64_t vmid)
{
    sbi_remote_hfence_gvma_vmid(platform.cpu_num - 1, 0, 0, 0, vmid);
}

#endif /* __ARCH_TLB_H__ */
