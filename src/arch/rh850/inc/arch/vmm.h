/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_VMM_H__
#define __ARCH_VMM_H__

#include <bao.h>

/* Bao uses MPID7 */
#define HYP_SPID 0x10

#ifndef __ASSEMBLER__
#include <srs.h>

extern void _hyp_vector_table(void);
static inline void vmm_arch_install_trap_vector(void)
{
    srs_ebase_write((uintptr_t)_hyp_vector_table | 0x2UL);
    __asm__ volatile("syncp" ::: "memory");
}

#endif /* __ASSEMBLER__ */

#endif /* __ARCH_VMM_H__ */
