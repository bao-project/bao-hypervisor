/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_BAO_H__
#define __ARCH_BAO_H__

#if (RV_XLEN == 64)
#define RV64 1
#else
#define RV32 1
#endif

#if defined(RV64)
#define LOAD   ld
#define STORE  sd
#define REGLEN (8)
#elif defined(RV32)
#define LOAD   lw
#define STORE  sw
#define REGLEN (4)
#endif

#if (RV64)
// This layout assumes Sv39 is available as mandated by the RVA23S64 profile
#define BAO_VAS_BASE (0xffffffc000000000)
#define BAO_CPU_BASE (0xffffffc040000000)
#define BAO_VM_BASE  (0xffffffe000000000)
#define BAO_VAS_TOP  (0xfffffff000000000)
#else
// Because sv32 only lowest level only supports 4MiB pages, this should be enough for each section
// otherwise we need allow for N shared PTEs for each section. For now, it seems to suffice. We also
// are assuming, for now that all available physical memory resides in 0x0 - 0xefffffff of virtual
// memory. Otherwise we need to implement a "highmem"-like mechanism.
#define BAO_VAS_BASE (0xc0000000)
#define BAO_CPU_BASE (0xcf400000)
#define BAO_VM_BASE  (0xcf800000)
#define BAO_VAS_TOP  (0xcfc00000)
#endif

#define PAGE_SIZE        (0x1000)
#define STACK_SIZE       (PAGE_SIZE)
#define VM_SHARED_PT_LVL (0)

#ifndef __ASSEMBLER__

#endif /* !__ASSEMBLER__ */

#endif /* __ARCH_BAO_H__ */
