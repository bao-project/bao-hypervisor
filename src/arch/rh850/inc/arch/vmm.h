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

#endif /* __ASSEMBLER__ */

/* No trap-vector handoff is needed until early traps are installed. */
static inline void vmm_arch_install_trap_vector(void)
{
}

#endif /* __ARCH_VMM_H__ */
