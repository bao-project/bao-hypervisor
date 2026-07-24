/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * Minimal ARM SMMUv3 (IHI 0070) driver interface for Bao.
 *
 * Scope: stage-2-only translation. Bao owns stage 2 (the VM's IPA->PA page
 * table); stage 1 is disabled (VMs see no SMMU). The driver installs a linear
 * stream table, a command queue and an event queue, leaves every stream in
 * BYPASS by default (so masters the firmware set up keep working unchanged),
 * and promotes individual streams to stage-2 translation when a VM binds them.
 *
 * Register layout and field encodings follow the ARM SMMUv3 architecture
 * specification (IHI 0070).
 */

#ifndef __ARCH_SMMUV3_H__
#define __ARCH_SMMUV3_H__

#include <bao.h>
#include <bit.h>

typedef deviceid_t streamid_t;

/* ----------------------------------------------------------------------- */
/* Non-secure register page (offsets from platform.arch.smmu.base)          */
/* ----------------------------------------------------------------------- */

struct smmuv3_hw {
    uint32_t IDR0;            /* +0x0000 */
    uint32_t IDR1;            /* +0x0004 */
    uint32_t IDR2;            /* +0x0008 */
    uint32_t IDR3;            /* +0x000C */
    uint32_t IDR4;            /* +0x0010 */
    uint32_t IDR5;            /* +0x0014 */
    uint32_t IIDR;            /* +0x0018 */
    uint32_t AIDR;            /* +0x001C */
    uint32_t CR0;             /* +0x0020 */
    uint32_t CR0ACK;          /* +0x0024 */
    uint32_t CR1;             /* +0x0028 */
    uint32_t CR2;             /* +0x002C */
    uint8_t pad0[0x40 - 0x30];
    uint32_t STATUSR;         /* +0x0040 */
    uint32_t GBPA;            /* +0x0044 */
    uint32_t AGBPA;           /* +0x0048 */
    uint8_t pad1[0x50 - 0x4C];
    uint32_t IRQ_CTRL;        /* +0x0050 */
    uint32_t IRQ_CTRLACK;     /* +0x0054 */
    uint8_t pad2[0x60 - 0x58];
    uint32_t GERROR;          /* +0x0060 */
    uint32_t GERRORN;         /* +0x0064 */
    uint64_t GERROR_IRQ_CFG0; /* +0x0068 */
    uint32_t GERROR_IRQ_CFG1; /* +0x0070 */
    uint32_t GERROR_IRQ_CFG2; /* +0x0074 */
    uint8_t pad3[0x80 - 0x78];
    uint64_t STRTAB_BASE;     /* +0x0080 */
    uint32_t STRTAB_BASE_CFG; /* +0x0088 */
    uint8_t pad4[0x90 - 0x8C];
    uint64_t CMDQ_BASE;       /* +0x0090 */
    uint32_t CMDQ_PROD;       /* +0x0098 */
    uint32_t CMDQ_CONS;       /* +0x009C */
    uint64_t EVENTQ_BASE;     /* +0x00A0 */
    uint32_t EVENTQ_PROD;     /* +0x00A8 (alias of page-1 PROD) */
    uint32_t EVENTQ_CONS;     /* +0x00AC (alias of page-1 CONS) */
};

/* Every register is at its natural alignment, so the struct is NOT packed
 * (packing would force -Waddress-of-packed-member on the &reg poll helpers).
 * Guard the hand-computed offsets so a layout slip is caught at compile time. */
_Static_assert(__builtin_offsetof(struct smmuv3_hw, CR0) == 0x20, "smmuv3 CR0 offset");
_Static_assert(__builtin_offsetof(struct smmuv3_hw, GBPA) == 0x44, "smmuv3 GBPA offset");
_Static_assert(__builtin_offsetof(struct smmuv3_hw, STRTAB_BASE) == 0x80,
    "smmuv3 STRTAB_BASE offset");
_Static_assert(__builtin_offsetof(struct smmuv3_hw, CMDQ_BASE) == 0x90, "smmuv3 CMDQ_BASE offset");
_Static_assert(__builtin_offsetof(struct smmuv3_hw, EVENTQ_PROD) == 0xA8,
    "smmuv3 EVENTQ_PROD offset");

/* SMMU_IDR0 */
#define SMMUV3_IDR0_ST_LEVEL_OFF  (27)
#define SMMUV3_IDR0_ST_LEVEL_LEN  (2)
#define SMMUV3_IDR0_COHACC_BIT    (1U << 4)
#define SMMUV3_IDR0_VMID16_BIT    (1U << 18)
#define SMMUV3_IDR0_TTF_OFF       (2)
#define SMMUV3_IDR0_TTF_LEN       (2)
#define SMMUV3_IDR0_S2P_BIT       (1U << 0)

/* SMMU_IDR1 */
#define SMMUV3_IDR1_SIDSIZE_OFF   (0)
#define SMMUV3_IDR1_SIDSIZE_LEN   (6)

/* SMMU_IDR5 */
#define SMMUV3_IDR5_OAS_OFF       (0)
#define SMMUV3_IDR5_OAS_LEN       (3)
#define SMMUV3_IDR5_GRAN4K_BIT    (1U << 4)

/* SMMU_CR0 / CR0ACK */
#define SMMUV3_CR0_SMMUEN         (1U << 0)
#define SMMUV3_CR0_EVENTQEN       (1U << 2)
#define SMMUV3_CR0_CMDQEN         (1U << 3)

/* SMMU_CR1 cacheability/shareability for table & queue accesses */
#define SMMUV3_CR1_INSH           (0x3) /* inner shareable */
#define SMMUV3_CR1_WBCACHE        (0x1) /* normal WB cacheable */
#define SMMUV3_CR1_DEFAULT                                    \
    ((SMMUV3_CR1_INSH << 10) | (SMMUV3_CR1_WBCACHE << 8) |    \
        (SMMUV3_CR1_WBCACHE << 6) |     /* table: SH/OC/IC */ \
        (SMMUV3_CR1_INSH << 4) | (SMMUV3_CR1_WBCACHE << 2) | (SMMUV3_CR1_WBCACHE)) /* queue */

/* SMMU_GBPA */
#define SMMUV3_GBPA_UPDATE                  (1U << 31)
#define SMMUV3_GBPA_ABORT                   (1U << 20)

/* SMMU_IRQ_CTRL / _CTRLACK (wired-SPI delivery of fault interrupts) */
#define SMMUV3_IRQ_CTRL_GERROR              (1U << 0)
#define SMMUV3_IRQ_CTRL_PRIQ                (1U << 1)
#define SMMUV3_IRQ_CTRL_EVENTQ              (1U << 2)

/* SMMU_STRTAB_BASE / _CFG */
#define SMMUV3_STRTAB_BASE_RA               (1ULL << 62)
#define SMMUV3_STRTAB_BASE_ADDR_MASK        BIT64_MASK(6, 46)
#define SMMUV3_STRTAB_BASE_CFG_FMT_LINEAR   (0x0U << 16)
#define SMMUV3_STRTAB_BASE_CFG_LOG2SIZE_OFF (0)

/* SMMU_CMDQ_BASE / EVENTQ_BASE */
#define SMMUV3_Q_BASE_RA                    (1ULL << 62)
#define SMMUV3_Q_BASE_ADDR_MASK             BIT64_MASK(5, 47)
#define SMMUV3_Q_BASE_LOG2SIZE_MASK         (0x1FULL)
/* PROD/CONS wrap bit sits just above the index field */
#define SMMUV3_Q_WRAP(log2size)             (1U << (log2size))
#define SMMUV3_Q_IDX_MASK(log2size)         (SMMUV3_Q_WRAP(log2size) - 1U)

/* ----------------------------------------------------------------------- */
/* Stream Table Entry (8 x 64-bit). Stage-2-only / bypass fields.           */
/* Bit positions per ARM IHI 0070.                                          */
/* ----------------------------------------------------------------------- */

#define SMMUV3_STE_DWORDS                   (8)

struct smmuv3_ste {
    uint64_t data[SMMUV3_STE_DWORDS];
} __attribute__((__aligned__(64)));

/* word 0 */
#define STE_W0_V                  (1ULL << 0)
#define STE_W0_CONFIG_OFF         (1)
#define STE_W0_CONFIG_BYPASS      (0x4ULL) /* S1 bypass, S2 bypass */
#define STE_W0_CONFIG_S2          (0x6ULL) /* S1 bypass, S2 translate */

/* word 1 (attribute overrides used in bypass STEs) */
#define STE_W1_SHCFG_OFF          (44)
#define STE_W1_SHCFG_USE_INCOMING (0x1ULL) /* pass master's shareability */

/* word 2 (stage-2 config) */
#define STE_W2_S2VMID_OFF         (0)
#define STE_W2_S2T0SZ_OFF         (32)
#define STE_W2_S2SL0_OFF          (38)
#define STE_W2_S2IR0_OFF          (40)
#define STE_W2_S2OR0_OFF          (42)
#define STE_W2_S2SH0_OFF          (44)
#define STE_W2_S2TG_OFF           (46)
#define STE_W2_S2PS_OFF           (48)
#define STE_W2_S2AA64             (1ULL << 51)
#define STE_W2_S2AFFD             (1ULL << 53)
#define STE_W2_S2R                (1ULL << 58) /* record stage-2 faults to evtq */
#define STE_W2_WB                 (0x1ULL)     /* IR0/OR0: WB cacheable RA/WA */
#define STE_W2_ISH                (0x3ULL)     /* SH0: inner shareable */
#define STE_W2_TG_4K              (0x0ULL)

/* word 3 stage-2 translation table base */
#define STE_W3_S2TTB_MASK         BIT64_MASK(4, 48)

/* ----------------------------------------------------------------------- */
/* Command queue: 128-bit commands (2 x 64-bit).                            */
/* ----------------------------------------------------------------------- */

#define SMMUV3_CMDQ_ENT_DWORDS    (2)

#define CMD_OP_CFGI_STE           (0x03ULL)
#define CMD_OP_CFGI_STE_RANGE     (0x04ULL)
#define CMD_OP_TLBI_S12_VMALL     (0x28ULL)
#define CMD_OP_TLBI_NSNH_ALL      (0x30ULL)
#define CMD_OP_SYNC               (0x46ULL)

/* CMD_CFGI_STE / _RANGE: StreamID in [63:32] of dword0 */
#define CMD_CFGI_SID_OFF          (32)
#define CMD_CFGI_STE_LEAF         (1ULL << 0)  /* dword1 */
#define CMD_CFGI_STE_RANGE_ALL    (31ULL << 0) /* dword1: Range=31 -> all */

/* CMD_TLBI_S12_VMALL: VMID in [47:32] of dword0 */
#define CMD_TLBI_VMID_OFF         (32)

/* CMD_SYNC: CS (completion signal) = none; we poll CONS instead */
#define CMD_SYNC_CS_NONE          (0x0ULL << 12)

/* Event queue record: 4 x 64-bit. dword0 [7:0]=fault type, [63:32]=StreamID;
 * dword2 = input (IPA) address for translation/permission faults. */
#define SMMUV3_EVTQ_ENT_DWORDS    (4)
#define SMMUV3_EVT_TYPE_MASK      (0xFFULL)
#define SMMUV3_EVT_SID_OFF        (32)

/* ----------------------------------------------------------------------- */
/* Driver API (consumed by iommu.c).                                        */
/* ----------------------------------------------------------------------- */

void smmuv3_init(void);
bool smmuv3_write_ste_s2(streamid_t sid, paddr_t root_pt, uint16_t vmid);
bool smmuv3_write_ste_bypass(streamid_t sid);
void smmuv3_poll_events(void); /* drain+log SMMU faults; safe before init */

#endif                         /* __ARCH_SMMUV3_H__ */
