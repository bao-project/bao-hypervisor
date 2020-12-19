/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __GIC_H__
#define __GIC_H__

#include <bao.h>
#include <emul.h>
#include <bitmap.h>
#include <spinlock.h>
#include <arch/sysregs.h>

#define GICV2 (2)
#define GICV3 (3)

#define GIC_FIRST_SPECIAL_INTID (1020)
#define GIC_MAX_INTERUPTS 1024
#define GIC_MAX_VALID_INTERRUPTS (GIC_FIRST_SPECIAL_INTID)
#define GIC_MAX_SGIS 16
#define GIC_MAX_PPIS 16
#define GIC_CPU_PRIV (GIC_MAX_SGIS + GIC_MAX_PPIS)
#define GIC_MAX_SPIS (GIC_MAX_INTERUPTS - GIC_CPU_PRIV)
#define GIC_PRIO_BITS 8
#define GIC_TARGET_BITS 8
#define GIC_MAX_TARGETS GIC_TARGET_BITS
#define GIC_CONFIG_BITS 2
#define GIC_SEC_BITS 2
#define GIC_SGI_BITS 8
#define GICD_IROUTER_INV (~MPIDR_AFF_MSK)
#define GIC_LOWEST_PRIO (0xff)

#define GIC_INT_REG(NINT) (NINT / (sizeof(uint32_t) * 8))
#define GIC_INT_MASK(NINT) (1U << NINT % (sizeof(uint32_t) * 8))
#define GIC_NUM_INT_REGS(NINT) GIC_INT_REG(NINT)
#define GIC_NUM_PRIVINT_REGS (GIC_CPU_PRIV / (sizeof(uint32_t) * 8))

#define GIC_PRIO_REG(NINT) ((NINT * GIC_PRIO_BITS) / (sizeof(uint32_t) * 8))
#define GIC_NUM_PRIO_REGS(NINT) GIC_PRIO_REG(NINT)
#define GIC_PRIO_OFF(NINT) (NINT * GIC_PRIO_BITS) % (sizeof(uint32_t) * 8)

#define GIC_TARGET_REG(NINT) ((NINT * GIC_TARGET_BITS) / (sizeof(uint32_t) * 8))
#define GIC_NUM_TARGET_REGS(NINT) GIC_TARGET_REG(NINT)
#define GIC_TARGET_OFF(NINT) (NINT * GIC_TARGET_BITS) % (sizeof(uint32_t) * 8)

#define GIC_CONFIG_REG(NINT) ((NINT * GIC_CONFIG_BITS) / (sizeof(uint32_t) * 8))
#define GIC_NUM_CONFIG_REGS(NINT) GIC_CONFIG_REG(NINT)
#define GIC_CONFIG_OFF(NINT) (NINT * GIC_CONFIG_BITS) % (sizeof(uint32_t) * 8)

#define GIC_NUM_SEC_REGS(NINT) ((NINT * GIC_SEC_BITS) / (sizeof(uint32_t) * 8))

#define GIC_NUM_SGI_REGS \
    ((GIC_MAX_SGIS * GIC_SGI_BITS) / (sizeof(uint32_t) * 8))
#define GICD_SGI_REG(NINT) (NINT / 4)
#define GICD_SGI_OFF(NINT) ((NINT % 4) * 8)

#define GIC_NUM_APR_REGS ((1UL << (GIC_PRIO_BITS - 1)) / (sizeof(uint32_t) * 8))
#define GIC_NUM_LIST_REGS (64)

/* Distributor Control Register, GICD_CTLR */

#define GICD_CTLR_EN_BIT (0x1)
#define GICD_CTLR_ENA_BIT (0x2)
#define GICD_CTLR_ARE_NS_BIT (0x10)

/*  Interrupt Controller Type Register, GICD_TYPER */

#define GICD_TYPER_ITLINENUM_OFF (0)
#define GICD_TYPER_ITLINENUM_LEN (5)
#define GICD_TYPER_CPUNUM_OFF (5)
#define GICD_TYPER_CPUNUM_LEN (3)
#define GICD_TYPER_CPUNUM_MSK BIT_MASK(GICD_TYPER_CPUNUM_OFF, GICD_TYPER_CPUNUM_LEN)
#define GICD_TYPER_SECUREXT_BIT (1UL << 10)
#define GICD_TYPER_LSPI_OFF (11)
#define GICD_TYPER_LSPI_LEN (6)
#define GICD_TYPER_ITLN_OFF 0
#define GICD_TYPER_ITLN_LEN 5
#define GICD_TYPER_ITLN_MSK BIT_MASK(GICD_TYPER_ITLN_OFF, GICD_TYPER_ITLN_LEN)
#define GICD_TYPER_IDBITS_OFF (19)
#define GICD_TYPER_IDBITS_LEN (5)
#define GICD_TYPER_IDBITS_MSK BIT_MASK(GICD_TYPER_IDBITS_OFF, GICD_TYPER_IDBITS_LEN)

/* Software Generated Interrupt Register, GICD_SGIR */

#define GICD_SGIR_SGIINTID_OFF 0
#define GICD_SGIR_SGIINTID_LEN 4
#define GICD_SGIR_SGIINTID_MSK \
    (BIT_MASK(GICD_SGIR_SGIINTID_OFF, GICD_SGIR_SGIINTID_LEN))
#define GICD_SGIR_SGIINTID(sgir) \
    bit_extract(sgir, GICD_SGIR_SGIINTID_OFF, GICD_SGIR_SGIINTID_LEN)
#define GICD_SGIR_CPUTRGLST_OFF 16
#define GICD_SGIR_CPUTRGLST_LEN 8
#define GICD_SGIR_CPUTRGLST(sgir) \
    bit_extract(sgir, GICD_SGIR_CPUTRGLST_OFF, GICD_SGIR_CPUTRGLST_LEN)
#define GICD_SGIR_TRGLSTFLT_OFF 24
#define GICD_SGIR_TRGLSTFLT_LEN 2
#define GICD_SGIR_TRGLSTFLT(sgir) \
    bit_extract(sgir, GICD_SGIR_TRGLSTFLT_OFF, GICD_SGIR_TRGLSTFLT_LEN)

/*  Interrupt Routing Registers, GICD_IROUTER */

#define GICD_IROUTER_RES0_MSK ((1ULL << 40)-1)
#define GICD_IROUTER_IRM_BIT (1ULL << 31)
#define GICD_IROUTER_AFF_MSK (GICD_IROUTER_RES0_MSK & ~GICD_IROUTER_IRM_BIT)

typedef struct {
    uint32_t CTLR;
    uint32_t TYPER;
    uint32_t IIDR;
    uint8_t pad0[0x0010 - 0x000C];
    uint32_t STATUSR;
    uint8_t pad1[0x0040 - 0x0014];
    uint32_t SETSPI_NSR;
    uint8_t pad2[0x0048 - 0x0044];
    uint32_t CLRSPI_NSR;
    uint8_t pad3[0x0050 - 0x004C];
    uint32_t SETSPI_SR;
    uint8_t pad4[0x0058 - 0x0054];
    uint32_t CLRSPI_SR;
    uint8_t pad9[0x0080 - 0x005C];
    uint32_t IGROUPR[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];  // banked CPU
    uint32_t ISENABLER[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];
    uint32_t ICENABLER[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];
    uint32_t ISPENDR[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];
    uint32_t ICPENDR[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];
    uint32_t ISACTIVER[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];
    uint32_t ICACTIVER[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];
    uint32_t IPRIORITYR[GIC_NUM_PRIO_REGS(GIC_MAX_INTERUPTS)];
    uint32_t ITARGETSR[GIC_NUM_TARGET_REGS(GIC_MAX_INTERUPTS)];
    uint32_t ICFGR[GIC_NUM_CONFIG_REGS(GIC_MAX_INTERUPTS)];
    uint32_t IGPRMODR[GIC_NUM_INT_REGS(GIC_MAX_INTERUPTS)];
    uint8_t pad5[0x0E00 - 0x0D80];
    uint32_t NSACR[GIC_NUM_SEC_REGS(GIC_MAX_INTERUPTS)];
    uint32_t SGIR;
    uint8_t pad6[0x0F10 - 0x0F04];
    uint32_t CPENDSGIR[GIC_NUM_SGI_REGS];
    uint32_t SPENDSGIR[GIC_NUM_SGI_REGS];
    uint8_t pad7[0x6000 - 0x0F30];
    uint64_t IROUTER[GIC_MAX_INTERUPTS];
    uint8_t pad8[0xFFD0 - 0x8000];
    uint32_t ID[(0x10000 - 0xFFD0) / sizeof(uint32_t)];
} __attribute__((__packed__, aligned(0x10000))) gicd_t;

/* Redistributor Wake Register, GICD_WAKER */

#define GICR_CTRL_DS_BIT (1 << 6)
#define GICR_CTRL_DS_DPG1NS (1 << 25)
#define GICR_TYPER_LAST_OFF (4)
#define GICR_TYPER_PRCNUM_OFF (8)
#define GICR_TYPER_AFFVAL_OFF (32)
#define GICR_WAKER_ProcessorSleep_BIT (0x2)
#define GICR_WAKER_ChildrenASleep_BIT (0x4)

typedef struct {
    /* RD_base frame */
    uint32_t CTLR;
    uint32_t IIDR;
    uint64_t TYPER;
    uint32_t STATUSR;
    uint32_t WAKER;
    uint8_t pad0[0x0040 - 0x0018];
    uint64_t SETLPIR;
    uint64_t CLRLPIR;
    uint8_t pad1[0x0070 - 0x0050];
    uint64_t PROPBASER;
    uint64_t PENDBASER;
    uint8_t pad2[0x00A0 - 0x0080];
    uint64_t INVLPIR;
    uint8_t pad3[0x00B0 - 0x00A8];
    uint64_t INVALLR;
    uint8_t pad4[0x00c0 - 0x00b8];
    uint64_t SYNCR;
    uint8_t pad5[0xFFD0 - 0x00c8];
    uint32_t ID[(0x10000 - 0xFFD0) / sizeof(uint32_t)];

    /* SGI_base frame */
    uint8_t sgi_base[0] __attribute__((aligned(0x10000)));
    uint8_t pad6[0x0080 - 0x000];
    uint32_t IGROUPR0;
    uint8_t pad7[0x0100 - 0x084];
    uint32_t ISENABLER0;
    uint8_t pad8[0x0180 - 0x104];
    uint32_t ICENABLER0;
    uint8_t pad9[0x0200 - 0x184];
    uint32_t ISPENDR0;
    uint8_t pad10[0x0280 - 0x204];
    uint32_t ICPENDR0;
    uint8_t pad11[0x0300 - 0x284];
    uint32_t ISACTIVER0;
    uint8_t pad12[0x0380 - 0x304];
    uint32_t ICACTIVER0;
    uint8_t pad13[0x0400 - 0x384];
    uint32_t IPRIORITYR[GIC_NUM_PRIO_REGS(GIC_CPU_PRIV)];
    uint8_t pad14[0x0c00 - 0x420];
    uint32_t ICFGR0;
    uint32_t ICFGR1;
    uint8_t pad15[0x0D00 - 0xc08];
    uint32_t IGRPMODR0;
    uint8_t pad16[0x0e00 - 0xd04];
    uint32_t NSACR;
} __attribute__((__packed__, aligned(0x10000))) gicr_t;

/* CPU Interface Control Register, GICC_CTLR */

#define GICC_CTLR_EN_BIT (0x1)
#define GICC_CTLR_EOImodeNS_BIT (1UL << 9)
#define GICC_CTLR_WR_MSK (0x1)
#define GICC_IAR_ID_OFF (0)
#if (GIC_VERSION == GICV2)
#define GICC_IAR_ID_LEN (10)
#define GICC_IAR_CPU_OFF (10)
#define GICC_IAR_CPU_LEN (3)
#define GICC_IAR_CPU_MSK (BIT_MASK(GICC_IAR_CPU_OFF, GICC_IAR_CPU_LEN))
#else 
#define GICC_IAR_ID_LEN (24)
#endif
#define GICC_IAR_ID_MSK (BIT_MASK(GICC_IAR_ID_OFF, GICC_IAR_ID_LEN))

#define ICC_CTLR_EOIMode_BIT (0x1ULL << 1)
#define ICC_SGIR_SGIINTID_OFF 24
#define ICC_SGIR_SGIINTID_LEN 4
#define ICC_SGIR_SGIINTID(sgir) \
    bit_extract(sgir, ICC_SGIR_SGIINTID_OFF, ICC_SGIR_SGIINTID_LEN)
#define ICC_SGIR_IRM_BIT (1ull << 40)
#define ICC_SGIR_TRGLSTFLT_OFF 0
#define ICC_SGIR_TRGLSTFLT_LEN 16 
#define ICC_SGIR_TRGLSTFLT_MSK BIT_MASK(ICC_SGIR_TRGLSTFLT_OFF, ICC_SGIR_TRGLSTFLT_LEN)
#define ICC_SGIR_TRGLSTFLT(sgir) \
    bit_extract(sgir, ICC_SGIR_TRGLSTFLT_OFF, ICC_SGIR_TRGLSTFLT_LEN)
#define ICC_SGIR_AFF1_OFFSET    (16)

#define ICC_SRE_ENB_BIT  (0x8)
#define ICC_SRE_DIB_BIT  (0x4)
#define ICC_SRE_DFB_BIT  (0x2)
#define ICC_SRE_SRE_BIT  (0x1)
#define ICC_IGRPEN_EL1_ENB_BIT (0x1)

typedef struct {
    uint32_t CTLR;
    uint32_t PMR;
    uint32_t BPR;
    uint32_t IAR;
    uint32_t EOIR;
    uint32_t RPR;
    uint32_t HPPIR;
    uint32_t ABPR;
    uint32_t AIAR;
    uint32_t AEOIR;
    uint32_t AHPPIR;
    uint8_t pad0[0x00D0 - 0x002C];
    uint32_t APR[GIC_NUM_APR_REGS];
    uint32_t NSAPR[GIC_NUM_APR_REGS];
    uint8_t pad1[0x00FC - 0x00F0];
    uint32_t IIDR;
    uint8_t pad2[0x1000 - 0x0100];
    uint32_t DIR;
} __attribute__((__packed__, aligned(0x1000))) gicc_t;

#define GICH_HCR_En_BIT (1 << 0)
#define GICH_HCR_UIE_BIT (1 << 1)
#define GICH_HCR_LRENPIE_BIT (1 << 2)
#define GICH_HCR_NPIE_BIT (1 << 3)
#define GICH_HCR_VGrp0DIE_BIT (1 << 4)
#define GICH_HCR_VGrp0EIE_BIT (1 << 5)
#define GICH_HCR_VGrp1EIE_BIT (1 << 6)
#define GICH_HCR_VGrp1DIE_BIT (1 << 7)
#define GICH_HCR_EOICount_OFF (27)
#define GICH_HCR_EOICount_LEN (5)
#define GICH_HCR_EOICount_MASK \
    BIT_MASK(GICH_HCR_EOICount_OFF, GICH_HCR_EOICount_LEN)

#define ICH_HCR_VGrp1EIE_BIT (1ULL << 6)
#define ICH_HCR_LRENPIE_BIT GICH_HCR_LRENPIE_BIT

#define GICH_VTR_OFF (0)
#define GICH_VTR_LEN (6)
#define GICH_VTR_MSK BIT_MASK(GICH_VTR_OFF, GICH_VTR_LEN)

#define ICH_VTR_OFF GICH_VTR_OFF 
#define ICH_VTR_LEN GICH_VTR_LEN 
#define ICH_VTR_MSK GICH_VTR_MSK 

#if (GIC_VERSION == GICV2)
#define GICH_LR_VID_OFF (0)
#define GICH_LR_VID_LEN (10)
#define GICH_LR_PID_OFF (10)
#define GICH_LR_PID_LEN (10)
#define GICH_LR_PRIO_OFF (23)
#define GICH_LR_PRIO_LEN (5)
#define GICH_LR_STATE_OFF (28)
#define GICH_LR_STATE_LEN (2)
#define GICH_LR_HW_BIT (1U << 31)
#define GICH_LR_EOI_BIT (1U << 19)
#define GICH_NUM_ELRSR (2)
#else
#define GICH_LR_VID_OFF (0)
#define GICH_LR_VID_LEN (32)
#define GICH_LR_PID_OFF (32)
#define GICH_LR_PID_LEN (10)
#define GICH_LR_PRIO_OFF (48)
#define GICH_LR_PRIO_LEN (8)
#define GICH_LR_STATE_OFF (62)
#define GICH_LR_STATE_LEN (2)
#define GICH_LR_GRP_BIT (1ULL << 60)
#define GICH_LR_HW_BIT (1ULL << 61)
#define GICH_LR_EOI_BIT (1ULL << 41)
#define GICH_NUM_ELRSR (1)
#endif

#define GICH_LR_CPUID_OFF (10)
#define GICH_LR_CPUID_LEN (3)

#define GICH_LR_VID_MSK BIT_MASK(GICH_LR_VID_OFF, GICH_LR_VID_LEN)
#define GICH_LR_VID(LR) (bit_extract(LR, GICH_LR_VID_OFF, GICH_LR_VID_LEN))

#define GICH_LR_PID_MSK BIT_MASK(GICH_LR_PID_OFF, GICH_LR_PID_LEN)

#define GICH_LR_CPUID_MSK BIT_MASK(GICH_LR_CPUID_OFF, GICH_LR_CPUID_LEN)
#define GICH_LR_CPUID(LR) \
    (bit_extract(LR, GICH_LR_CPUID_OFF, GICH_LR_CPUID_LEN))

#define GICH_LR_PRIO_MSK BIT_MASK(GICH_LR_PRIO_OFF, GICH_LR_PRIO_LEN)

#define GICH_LR_STATE_MSK BIT_MASK(GICH_LR_STATE_OFF, GICH_LR_STATE_LEN)
#define GICH_LR_STATE(LR) \
    (bit_extract(LR, GICH_LR_STATE_OFF, GICH_LR_STATE_LEN))

#define GICH_LR_STATE_INV ((0ULL << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK)
#define GICH_LR_STATE_PND ((1ULL << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK)
#define GICH_LR_STATE_ACT ((2ULL << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK)
#define GICH_LR_STATE_ACTPEND ((3ULL << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK)

#define GICH_MISR_EOI (1U << 0)
#define GICH_MISR_U (1U << 1)
#define GICH_MISR_LRPEN (1U << 2)
#define GICH_MISR_NP (1U << 3)
#define GICH_MISR_VGrp0E (1U << 4)
#define GICH_MISR_VGrp0D (1U << 5)
#define GICH_MISR_VGrp1E (1U << 6)
#define GICH_MISR_VGrp1D (1U << 7)

typedef struct {
    uint32_t HCR;
    uint32_t VTR;
    uint32_t VMCR;
    uint8_t pad0[0x10 - 0x0c];
    uint32_t MISR;
    uint8_t pad1[0x20 - 0x14];
    uint32_t EISR[GIC_NUM_LIST_REGS / (sizeof(uint32_t) * 8)];
    uint8_t pad2[0x30 - 0x28];
    uint32_t ELSR[GIC_NUM_LIST_REGS / (sizeof(uint32_t) * 8)];
    uint8_t pad3[0xf0 - 0x38];
    uint32_t APR;
    uint8_t pad4[0x100 - 0x0f4];
    uint32_t LR[GIC_NUM_LIST_REGS];
} __attribute__((__packed__, aligned(0x1000))) gich_t;

typedef struct {
    uint32_t CTLR;
    uint32_t PMR;
    uint32_t BPR;
    uint32_t IAR;
    uint32_t EOIR;
    uint32_t RPR;
    uint32_t HPPIR;
    uint32_t ABPR;
    uint32_t AIAR;
    uint32_t AEOIR;
    uint32_t AHPPIR;
    uint8_t pad0[0xD0 - 0x2C];
    uint32_t APR[GIC_NUM_APR_REGS];
    uint8_t pad1[0x00FC - 0x00E0];
    uint32_t IIDR;
    uint8_t pad2[0x1000 - 0x0100];
    uint32_t DIR;
} __attribute__((__packed__, aligned(0x1000))) gicv_t;

extern volatile gicd_t gicd;
extern volatile gicc_t gicc;
extern volatile gich_t gich;

enum int_state { INV, PEND, ACT, PENDACT };

typedef struct {
    uint32_t CTLR;
    uint32_t PMR;
    uint32_t BPR;
    uint32_t IAR;
    uint32_t EOIR;
    uint32_t RPR;
    uint32_t HPPIR;
    uint32_t priv_ISENABLER;
    uint32_t priv_IPRIORITYR[GIC_NUM_PRIO_REGS(GIC_CPU_PRIV)];

    uint32_t HCR;
    uint32_t LR[GIC_NUM_LIST_REGS];
} gicc_state_t;

extern uint64_t NUM_LRS;

void gic_init();
void gic_cpu_init();
void gic_send_sgi(uint64_t cpu_target, uint64_t sgi_num);

void gicc_save_state(gicc_state_t *state);
void gicc_restore_state(gicc_state_t *state);

void gic_set_enable(uint64_t int_id, bool en);
void gic_set_prio(uint64_t int_id, uint8_t prio);
void gic_set_icfgr(uint64_t int_id, uint8_t cfg);
void gic_set_pend(uint64_t int_id, bool pend);
void gic_set_act(uint64_t int_id, bool act);
uint64_t gic_get_prio(uint64_t int_id);
bool gic_get_pend(uint64_t int_id);
bool gic_get_act(uint64_t int_id);

void gicd_set_enable(uint64_t int_id, bool en);
void gicd_set_pend(uint64_t int_id, bool pend);
void gicd_set_prio(uint64_t int_id, uint8_t prio);
void gicd_set_icfgr(uint64_t int_id, uint8_t cfg);
void gicd_set_act(uint64_t int_id, bool act);
void gicd_set_trgt(uint64_t int_id, uint8_t cpu_targets);
void gicd_set_route(uint64_t int_id, uint64_t route);
bool gicd_get_pend(uint64_t int_id);
bool gicd_get_act(uint64_t int_id);
uint64_t gicd_get_prio(uint64_t int_id);

void gicr_set_enable(uint64_t int_id, bool en, uint32_t gicr_id);
void gicr_set_pend(uint64_t int_id, bool pend, uint32_t gicr_id);
void gicr_set_prio(uint64_t int_id, uint8_t prio, uint32_t gicr_id);
void gicr_set_icfgr(uint64_t int_id, uint8_t cfg, uint32_t gicr_id);
void gicr_set_act(uint64_t int_id, bool act, uint32_t gicr_id);
uint64_t gicr_get_prio(uint64_t int_id, uint32_t gicr_id);

uint64_t gich_read_lr(size_t i);
void gich_write_lr(size_t i, uint64_t val);
uint32_t gich_get_hcr();
void gich_set_hcr(uint32_t);
uint32_t gich_get_misr();
uint64_t gich_get_eisr();
uint64_t gich_get_elrsr();

void gic_maintenance_handler(uint64_t arg);

extern volatile gicd_t gicd;
extern volatile gicr_t *gicr;

uint64_t gich_num_lrs();
uint32_t gicc_iar();
void gicc_eoir(uint32_t eoir);
void gicc_dir(uint32_t dir);

static inline uint64_t gic_num_irqs()
{
    uint32_t itlinenumber =
        bit_extract(gicd.TYPER, GICD_TYPER_ITLN_OFF, GICD_TYPER_ITLN_LEN);
    return 32 * itlinenumber + 1;
}

static inline bool gic_is_sgi(uint64_t int_id)
{
    return int_id < GIC_MAX_SGIS;
}

static inline bool gic_is_priv(uint64_t int_id)
{
    return int_id < GIC_CPU_PRIV;
}

#endif /* __GIC_H__ */
