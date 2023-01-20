/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_BAO_H__
#define __ARCH_BAO_H__

#define BAO_VAS_BASE    (0xfd8000000000)
#define BAO_CPU_BASE    (0xfe0000000000)
#define BAO_VM_BASE     (0xfe8000000000)
#define BAO_VAS_TOP     (0xff0000000000)
#define PAGE_SIZE       (0x1000)
#define STACK_SIZE      (PAGE_SIZE)

#define GPR(N)  "x"#N

#ifndef __ASSEMBLER__


#endif /* !__ASSEMBLER__ */


#endif /* __ARCH_BAO_H__ */
