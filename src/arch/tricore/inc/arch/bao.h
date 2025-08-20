/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_BAO_H__
#define __ARCH_BAO_H__

#define BAO_VAS_BASE CONFIG_HYP_BASE_ADDR

#define PAGE_SIZE    (64)
#define STACK_SIZE   (0x200)

#ifndef __ASSEMBLER__

/* The current GCC injects calls to abort() in some places, which
   results in undefined references.
   For this reason we define our own abort() for this architecture. */
void abort(void);

#endif /* !__ASSEMBLER__ */

#endif /* __ARCH_BAO_H__ */
