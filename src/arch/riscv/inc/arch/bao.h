/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_BAO_H__
#define __ARCH_BAO_H__

#ifdef __riscv__
#define RV64 (__riscv_xlen == 64)
#define RV32 (__riscv_xlen == 32)
#else
#define RV64    1
#endif

#if (!(RV64))
#error "Unsupported __riscv_xlen #__riscv_xlen."
#endif

#if (RV64)
#define LOAD ld
#define STORE sd
#define REGLEN (8)
#elif (RV32)
#define LOAD lw
#define STORE sw
#define REGLEN (4)
#endif

#if (RV64)
#define BAO_VAS_BASE (0xffffffc000000000)
#define BAO_CPU_BASE (0xffffffc040000000)
#define BAO_VM_BASE (0xffffffe000000000)
#define BAO_VAS_TOP (0xfffffff000000000)
#elif (RV32)
#define BAO_VAS_BASE (0xc0000000)
#define BAO_CPU_BASE (0x00000000)
#define BAO_VM_BASE (0x00000000)
#define BAO_VAS_TOP (0xffffffff)
#endif

#define PAGE_SIZE (0x1000)
#define STACK_SIZE (PAGE_SIZE)

#ifndef __ASSEMBLER__

#endif /* !__ASSEMBLER__ */

#endif /* __ARCH_BAO_H__ */
