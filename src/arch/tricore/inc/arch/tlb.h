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
}

static inline void tlb_hyp_inv_all()
{
}

static inline void tlb_vm_inv_va(asid_t vmid, vaddr_t va)
{
}

static inline void tlb_vm_inv_all(asid_t vmid)
{
}

#endif /* __ARCH_TLB_H__ */
