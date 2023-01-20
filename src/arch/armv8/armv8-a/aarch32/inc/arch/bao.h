/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_BAO_H__
#define __ARCH_BAO_H__

#define BAO_VAS_BASE    (0x40000000)
#define BAO_CPU_BASE    (0x50000000)
#define BAO_VM_BASE     (0x60000000)
#define BAO_VAS_TOP     (0x80000000)
#define PAGE_SIZE       (0x1000)
#define STACK_SIZE      (PAGE_SIZE)

#define GPR(N)  "r"#N

#ifndef __ASSEMBLER__


#endif /* !__ASSEMBLER__ */


#endif /* __ARCH_BAO_H__ */
