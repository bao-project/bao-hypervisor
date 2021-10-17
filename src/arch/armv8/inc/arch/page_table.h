/**
 * Bao, a Lightweight Static Partitioning Hypervisor
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

#ifdef __ASSEMBLER__
#define PT_SIZE PAGE_SIZE
#define PT_LVLS 4

#define PTE_INDEX_SHIFT(LEVEL) ((9 * (3 - LEVEL)) + 12)
#define PTE_INDEX(LEVEL, ADDR) ((ADDR >> PTE_INDEX_SHIFT(LEVEL)) & (0x1FF))

.macro PTE_INDEX_ASM	index, addr, level
	lsr \index, \addr, #PTE_INDEX_SHIFT(\level) 
	and \index, \index, #0x1ff
	lsl \index, \index, #3
.endm
#endif

#define HYP_ROOT_PT_SIZE PAGE_SIZE

#define ADDR_MSK(MSB, LSB) (((1UL << (MSB + 1)) - 1) & ~((1UL << (LSB)) - 1))
#define PTE_ADDR_MSK ADDR_MSK(47, 12)
#define PTE_FLAGS_MSK (~PTE_ADDR_MSK)

#define PTE_TYPE_MSK (0x3)
#define PTE_VALID (0x1)
#define PTE_SUPERPAGE (0x1)
#define PTE_TABLE (0x3)
#define PTE_PAGE (0x3)

#define PTE_NSTable (1LL << 63)
#define PTE_APTable_OFF (61)
#define PTE_APTable_MSK (0x3LL << PTE_APTable_OFF)
#define PTE_APTable_ALL (0x0LL << PTE_APTable_OFF)
#define PTE_APTable_NOEL0 (0x1LL << PTE_APTable_OFF)
#define PTE_APTable_RO (0x2LL << PTE_APTable_OFF)
#define PTE_APTable_RO_NOEL0 (0x3LL << PTE_APTable_OFF)
#define PTE_XNTable (1LL << 60)
#define PTE_PXNTable (1LL << 59)

#define PTE_PBHA_OFF (59)
#define PTE_PBHA_MSK (0xf << PTE_PBHA_OFF)
#define PTE_PBHA(VAL) ((VAL << PTE_PBHA_OFF) & PTE_PBHA_MSK)
#define PTE_XN (1LL << 54)
#define PTE_PXN (1LL << 53)
#define PTE_Con (1LL << 52)
#define PTE_DBM (1LL << 51)
#define PTE_nG (1LL << 11)
#define PTE_AF (1LL << 10)
#define PTE_SH_OFF (8)
#define PTE_SH_MSK (0x3LL << PTE_SH_OFF)
#define PTE_SH_NS (0x0LL << PTE_SH_OFF)
#define PTE_SH_OS (0x2LL << PTE_SH_OFF)
#define PTE_SH_IS (0x3LL << PTE_SH_OFF)
#define PTE_AP_OFF (6)
#define PTE_AP_MSK (0x3LL << PTE_AP_OFF)
#define PTE_AP_RW_PRIV (0x0LL << PTE_AP_OFF)
#define PTE_AP_RO_PRIV (0x2LL << PTE_AP_OFF)
#define PTE_AP_RW (0x1LL << PTE_AP_OFF)
#define PTE_AP_RO (0x3LL << PTE_AP_OFF)
#define PTE_NS (1 << 5)
#define PTE_ATTR_OFF (2)
#define PTE_ATTR_MSK (0x7LL << PTE_ATTR_OFF)
#define PTE_ATTR(N) ((N << PTE_ATTR_OFF) & PTE_ATTR_MSK)

/* Stage 2 fields */

#define PTE_MEMATTR_OFF (2)
#define PTE_MEMATTR_DEV_nGnRnE ((0x00 << 0) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_DEV_nGnRE ((0x01 << 0) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_DEV_nGRE ((0x02 << 0) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_DEV_GRE ((0x03 << 0) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_NRML_ONC ((0x01 << 2) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_NRML_OWTC ((0x02 << 2) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_NRML_OWBC ((0x03 << 2) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_NRML_INC ((0x01 << 0) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_NRML_IWTC ((0x02 << 0) << PTE_MEMATTR_OFF)
#define PTE_MEMATTR_NRML_IWBC ((0x03 << 0) << PTE_MEMATTR_OFF)

#define PTE_S2AP_RO (0x1 << PTE_AP_OFF)
#define PTE_S2AP_WO (0x2 << PTE_AP_OFF)
#define PTE_S2AP_RW (0x3 << PTE_AP_OFF)

#define PTE_RSW_OFF (55)
#define PTE_RSW_WDT (4)
#define PTE_RSW_MSK \
    (((1UL << (PTE_RSW_OFF + PTE_RSW_WDT)) - 1) - ((1UL << (PTE_RSW_OFF)) - 1))

/* ------------------------------------------------------------- */

#define PTE_RSW_EMPT (0x0LL << PTE_RSW_OFF)
#define PTE_RSW_OPEN (0x1LL << PTE_RSW_OFF)
#define PTE_RSW_FULL (0x2LL << PTE_RSW_OFF)
#define PTE_RSW_RSRV (0x3LL << PTE_RSW_OFF)

#define PT_ROOT_FLAGS_REC_IND_OFF (0)
#define PT_ROOT_FLAGS_REC_IND_LEN (13)
#define PT_ROOT_FLAGS_REC_IND_MSK \
    BIT_MASK(PT_ROOT_FLAGS_REC_IND_OFF, PT_ROOT_FLAGS_REC_IND_LEN)

#define PT_CPU_REC_IND (pt_nentries(&cpu.as.pt, 0) - 1)
#define PT_VM_REC_IND (pt_nentries(&cpu.as.pt, 0) - 2)

#define PTE_INVALID (0)
#define PTE_HYP_FLAGS (PTE_ATTR(1) | PTE_AP_RW | PTE_SH_IS | PTE_AF)
#define PTE_HYP_DEV_FLAGS \
    (PTE_ATTR(2) | PTE_AP_RW | PTE_SH_IS | PTE_AF | PTE_XN)

#define PTE_VM_FLAGS                                                           \
    (PTE_MEMATTR_NRML_OWBC | PTE_MEMATTR_NRML_IWBC | PTE_SH_NS | PTE_S2AP_RW | \
     PTE_AF)

#define PTE_VM_DEV_FLAGS \
    (PTE_MEMATTR_DEV_GRE | PTE_SH_NS | PTE_S2AP_RW | PTE_AF)

#ifndef __ASSEMBLER__

    typedef uint64_t pte_t;
extern uint64_t parange;
extern uint64_t parange_table[];

typedef struct page_table page_table_t;

void pt_set_recursive(page_table_t* pt, uint64_t index);

static inline void pte_set(pte_t* pte, uint64_t addr, uint64_t type,
                           uint64_t flags)
{
    *pte =
        (addr & PTE_ADDR_MSK) | (type & PTE_TYPE_MSK) | (flags & PTE_FLAGS_MSK);
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

static inline uint64_t pte_addr(pte_t* pte)
{
    return *pte & PTE_ADDR_MSK;
}

#endif /* |__ASSEMBLER__ */

#endif /* __ARCH_PAGE_TABLE_H__ */
