/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_VMM_H
#define ARCH_VMM_H

#include <arch/sysregs.h>

extern void _hyp_vector_table(void);
static inline void vmm_arch_install_trap_vector(void)
{
    sysreg_vbar_el2_write((uintptr_t)_hyp_vector_table);
    __asm__ volatile("isb" ::: "memory");
}

void vmm_arch_profile_init(void);
void vmm_arch_init_tcr(void);

#endif /* ARCH_VMM_H */
