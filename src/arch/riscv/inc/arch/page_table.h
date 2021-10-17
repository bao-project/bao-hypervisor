/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __ARCH_PAGE_TABLE_H__
#define __ARCH_PAGE_TABLE_H__

#include <bao.h>
#include <bit.h>

#define HYP_ROOT_PT_SIZE (PAGE_SIZE)
#define PAGE_SHIFT (12)

#if (RV64)
#define PTE_ADDR_MSK BIT_MASK(12, 44)
#elif (RV32)
#define PTE_ADDR_MSK BIT_MASK(12, 22)
#endif

#define PTE_FLAGS_MSK BIT_MASK(0, 8)

#define PTE_VALID (1ULL << 0)
#define PTE_READ (1ULL << 1)
#define PTE_WRITE (1ULL << 2)
#define PTE_EXECUTE (1ULL << 3)
#define PTE_USER (1ULL << 4)
#define PTE_GLOBAL (1ULL << 5)
#define PTE_ACCESS (1ULL << 6)
#define PTE_DIRTY (1ULL << 7)

#define PTE_RO (PTE_READ)
#define PTE_RW (PTE_READ | PTE_WRITE)
#define PTE_XO (PTE_EXECUTE)
#define PTE_RX (PTE_READ | PTE_EXECUTE)
#define PTE_RWX (PTE_READ | PTE_WRITE | PTE_EXECUTE)

#define PTE_RSW_OFF 8
#define PTE_RSW_LEN 2
#define PTE_RSW_MSK BIT_MASK(PTE_RSW_OFF, PTE_RSW_LEN)

#define PTE_TABLE (0)
#define PTE_PAGE (PTE_RWX)
#define PTE_SUPERPAGE (PTE_PAGE)

/* ------------------------------------------------------------- */

#define PTE_RSW_EMPT (0x0LL << PTE_RSW_OFF)
#define PTE_RSW_OPEN (0x1LL << PTE_RSW_OFF)
#define PTE_RSW_FULL (0x2LL << PTE_RSW_OFF)
#define PTE_RSW_RSRV (0x3LL << PTE_RSW_OFF)

#define PT_ROOT_FLAGS_REC_IND_OFF ? ? ?
#define PT_ROOT_FLAGS_REC_IND_LEN ? ? ?
#define PT_ROOT_FLAGS_REC_IND_MSK \
    BIT_MASK(PT_ROOT_FLAGS_REC_IND_OFF, PT_ROOT_FLAGS_REC_IND_LEN)

#define PT_CPU_REC_IND (pt_nentries(&cpu.as.pt, 0) - 1)
#define PT_VM_REC_IND (pt_nentries(&cpu.as.pt, 0) - 2)

#define PTE_INVALID (0)
#define PTE_HYP_FLAGS (PTE_VALID | PTE_GLOBAL | PTE_ACCESS | PTE_DIRTY)
#define PTE_HYP_DEV_FLAGS PTE_HYP_FLAGS

#define PTE_VM_FLAGS (PTE_VALID | PTE_ACCESS | PTE_DIRTY | PTE_USER)
#define PTE_VM_DEV_FLAGS PTE_VM_FLAGS

#ifndef __ASSEMBLER__

typedef uint64_t pte_t;

typedef struct page_table page_table_t;

static inline void pte_set(pte_t* pte, uint64_t addr, uint64_t type,
                           uint64_t flags)
{
    *pte = ((addr & PTE_ADDR_MSK) >> 2) | (flags & PTE_FLAGS_MSK) | type;
}

static inline uintptr_t pte_addr(pte_t* pte)
{
    return (*pte << 2) & PTE_ADDR_MSK;
}

static inline bool pte_valid(pte_t* pte)
{
    return (*pte & PTE_VALID);
}

static inline void pte_set_rsw(pte_t* pte, uint64_t flag)
{
    *pte = (*pte & ~PTE_RSW_MSK) | (flag & PTE_RSW_MSK);
}

static inline bool pte_check_rsw(pte_t* pte, uint64_t flag)
{
    return (*pte & PTE_RSW_MSK) == (flag & PTE_RSW_MSK);
}

static inline bool pte_table(page_table_t* pt, pte_t* pte, uint64_t lvl)
{
    return (*pte & 0xf) == PTE_VALID;
}

static inline uint64_t pt_pte_type(page_table_t* pt, uint64_t lvl)
{
    return PTE_PAGE;
}

#endif /* |__ASSEMBLER__ */

#endif /* __ARCH_PAGE_TABLE_H__ */
