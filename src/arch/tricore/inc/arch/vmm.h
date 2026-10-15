/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_VMM_H
#define ARCH_VMM_H

/* No trap-vector handoff is needed until early traps are installed. */
static inline void vmm_arch_install_trap_vector(void)
{
}

#endif /* ARCH_VMM_H */
