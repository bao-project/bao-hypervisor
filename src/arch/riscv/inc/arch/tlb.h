/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_TLB_H__
#define __ARCH_TLB_H__

#include <bao.h>
#include <platform.h>
#include <arch/sbi.h>

/**
 * TODO: we are assuming platform.cpu_num is power of two. Make this not true.
 */

static inline void tlb_hyp_inv_va(vaddr_t va)
{
    sbi_remote_sfence_vma((1 << platform.cpu_num) - 1, 0, (unsigned long)va,
                          PAGE_SIZE);
}

static inline void tlb_hyp_inv_all()
{
    sbi_remote_sfence_vma((1 << platform.cpu_num) - 1, 0, 0, 0);
}

/**
 * TODO: change hart_mask to only take into account the vm physical cpus.
 */

static inline void tlb_vm_inv_va(asid_t vmid, vaddr_t va)
{
    sbi_remote_hfence_gvma_vmid((1 << platform.cpu_num)- 1, 0, (unsigned long)va,
                                PAGE_SIZE, vmid);
}

static inline void tlb_vm_inv_all(asid_t vmid)
{
    sbi_remote_hfence_gvma_vmid((1 << platform.cpu_num) - 1, 0, 0, 0, vmid);
}

#endif /* __ARCH_TLB_H__ */
