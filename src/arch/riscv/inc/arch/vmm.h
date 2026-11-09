/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_VMM_H
#define ARCH_VMM_H

#include <arch/csrs.h>

extern void _hyp_trap_vector(void);

/* Called once after VM setup, when sscratch points to the current vCPU. */
static inline void vmm_arch_install_trap_vector(void)
{
    csrs_stvec_write((uintptr_t)_hyp_trap_vector);
}

#endif /* ARCH_VMM_H */
