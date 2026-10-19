/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_VMM_H
#define ARCH_VMM_H

#include <arch/csfrs.h>
#include <bao.h>

extern void _trap_vector_table(void);
extern void _hyp_vector_table(void);
extern void _irq_vector(void);
static inline void vmm_arch_install_trap_vector(void)
{
    __asm__ volatile("mtcr " XSTR(CSFR_BHV) ", %0\n\t"
                     "mtcr $biv, %1\n\t"
                     "mtcr $btv, %2\n\t"
                     "isync" : : "d"((uintptr_t)_hyp_vector_table),
                     "d"((uintptr_t)_irq_vector), "d"((uintptr_t)_trap_vector_table) : "memory");
}

#endif /* ARCH_VMM_H */
