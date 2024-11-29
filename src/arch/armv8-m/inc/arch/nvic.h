/**
 * SPDX-License-Identifier: Apache-2.0U
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __NVIC_H__
#define __NVIC_H__

#include <bao.h>
#include <platform.h>
#include <vm.h>

#define NVIC_MAX_INTERRUPTS (2048U)
#define NVIC_MAX_ISP        (11U)
#define NVIC_MAX_VM         (8U)
#define NVIC_MAX_GROUPS     (16U)
#define NVIC_MAX_SW_INT     (8U)
#define NVIC_MAX_PRIO       (255U)
#define NVIC_MIN_PRIO       (0U)
#define NVIC_TARGET_NONE    (0xfU)

#ifndef PLAT_NVIC_MAX_INTERRUPTS
#define PLAT_NVIC_MAX_INTERRUPTS NVIC_MAX_INTERRUPTS
#endif

#ifndef PLAT_NVIC_MAX_ISP
#define PLAT_NVIC_MAX_ISP NVIC_MAX_ISP /* TODO might not make sense */
#endif

#ifndef PLAT_NVIC_MAX_VM
#define PLAT_NVIC_MAX_VM NVIC_MAX_VM
#endif

#ifndef PLAT_NVIC_MAX_VM
#define PLAT_NVIC_MAX_GROUPS NVIC_MAX_GROUPS
#endif

#ifndef PLAT_NVIC_MAX_VM
#define PLAT_NVIC_MAX_SW_INT NVIC_MAX_SW_INT
#endif

// Define the register offset
#define REG_OFFSET               0x0004U

// Define bit positions for each field
#define NVIC_SRC_IOVCLR_POS      28U
#define NVIC_SRC_IOV_POS         27U
#define NVIC_SRC_SETR_POS        26U
#define NVIC_SRC_CLRR_POS        25U
#define NVIC_SRC_SRR_POS         24U
#define NVIC_SRC_SRE_POS         23U
#define NVIC_SRC_TOS_POS         12U
#define NVIC_SRC_CS_POS          11U
#define NVIC_SRC_VM_POS          8U
#define NVIC_SRC_SRPN_POS        0U

// Define NVIC_SRC masks for each field
#define NVIC_SRC_IOVCLR_MASK     (0x1U << NVIC_SRC_IOVCLR_POS)
#define NVIC_SRC_IOV_MASK        (0x1U << NVIC_SRC_IOV_POS)
#define NVIC_SRC_SETR_MASK       (0x1U << NVIC_SRC_SETR_POS)
#define NVIC_SRC_CLRR_MASK       (0x1U << NVIC_SRC_CLRR_POS)
#define NVIC_SRC_SRR_MASK        (0x1U << NVIC_SRC_SRR_POS)
#define NVIC_SRC_SRE_MASK        (0x1U << NVIC_SRC_SRE_POS)
#define NVIC_SRC_TOS_MASK        (0xFU << NVIC_SRC_TOS_POS)
#define NVIC_SRC_CS_MASK         (0x1U << NVIC_SRC_CS_POS)
#define NVIC_SRC_VM_MASK         (0x7U << NVIC_SRC_VM_POS)
#define NVIC_SRC_SRPN_MASK       (0xFFU << NVIC_SRC_SRPN_POS)

// Macros to read the fields from the register value
#define NVIC_SRC_GET_IOVCLR(reg) (((reg) & NVIC_SRC_IOVCLR_MASK) >> NVIC_SRC_IOVCLR_POS)
#define NVIC_SRC_GET_IOV(reg)    (((reg) & NVIC_SRC_IOV_MASK) >> NVIC_SRC_IOV_POS)
#define NVIC_SRC_GET_SETR(reg)   (((reg) & NVIC_SRC_SETR_MASK) >> NVIC_SRC_SETR_POS)
#define NVIC_SRC_GET_CLRR(reg)   (((reg) & NVIC_SRC_CLRR_MASK) >> NVIC_SRC_CLRR_POS)
#define NVIC_SRC_GET_SRR(reg)    (((reg) & NVIC_SRC_SRR_MASK) >> NVIC_SRC_SRR_POS)
#define NVIC_SRC_GET_SRE(reg)    (((reg) & NVIC_SRC_SRE_MASK) >> NVIC_SRC_SRE_POS)
#define NVIC_SRC_GET_TOS(reg)    (((reg) & NVIC_SRC_TOS_MASK) >> NVIC_SRC_TOS_POS)
#define NVIC_SRC_GET_CS(reg)     (((reg) & NVIC_SRC_CS_MASK) >> NVIC_SRC_CS_POS)
#define NVIC_SRC_GET_VM(reg)     (((reg) & NVIC_SRC_VM_MASK) >> NVIC_SRC_VM_POS)
#define NVIC_SRC_GET_SRPN(reg)   (((reg) & NVIC_SRC_SRPN_MASK) >> NVIC_SRC_SRPN_POS)

// Macros to set the fields in the register value
#define NVIC_SRC_SET_IOVCLR(reg, val)          \
    ((reg) = ((reg) & ~NVIC_SRC_IOVCLR_MASK) | \
            (((val) << NVIC_SRC_IOVCLR_POS) & NVIC_SRC_IOVCLR_MASK))
#define NVIC_SRC_SET_IOV(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_IOV_MASK) | (((val) << NVIC_SRC_IOV_POS) & NVIC_SRC_IOV_MASK))
#define NVIC_SRC_SET_SETR(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_SETR_MASK) | (((val) << NVIC_SRC_SETR_POS) & NVIC_SRC_SETR_MASK))
#define NVIC_SRC_SET_CLRR(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_CLRR_MASK) | (((val) << NVIC_SRC_CLRR_POS) & NVIC_SRC_CLRR_MASK))
#define NVIC_SRC_SET_SRR(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_SRR_MASK) | (((val) << NVIC_SRC_SRR_POS) & NVIC_SRC_SRR_MASK))
#define NVIC_SRC_SET_SRE(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_SRE_MASK) | (((val) << NVIC_SRC_SRE_POS) & NVIC_SRC_SRE_MASK))
#define NVIC_SRC_SET_TOS(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_TOS_MASK) | (((val) << NVIC_SRC_TOS_POS) & NVIC_SRC_TOS_MASK))
#define NVIC_SRC_SET_CS(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_CS_MASK) | (((val) << NVIC_SRC_CS_POS) & NVIC_SRC_CS_MASK))
#define NVIC_SRC_SET_VM(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_VM_MASK) | (((val) << NVIC_SRC_VM_POS) & NVIC_SRC_VM_MASK))
#define NVIC_SRC_SET_SRPN(reg, val) \
    ((reg) = ((reg) & ~NVIC_SRC_SRPN_MASK) | (((val) << NVIC_SRC_SRPN_POS) & NVIC_SRC_SRPN_MASK))

#define GPSRG_SR_IOVCLR_POS        31U
#define GPSRG_SR_IOV_POS           30U
#define GPSRG_SR_SETR_POS          29U
#define GPSRG_SR_SRR_POS           28U
#define GPSRG_SR_BRDIS_POS         27U
#define GPSRG_SR_LOCKSTAT_POS      18U
#define GPSRG_SR_LOCKCLR_POS       17U
#define GPSRG_SR_LOCKSET_POS       16U
#define GPSRG_SR_DATA_POS          0U

#define GPSRG_SR_IOVCLR_MASK       (0x1U << GPSRG_SR_IOVCLR_POS)   // 1 bit: 31U
#define GPSRG_SR_IOV_MASK          (0x1U << GPSRG_SR_IOV_POS)      // 1 bit: 30U
#define GPSRG_SR_SETR_MASK         (0x1U << GPSRG_SR_SETR_POS)     // 1 bit: 29U
#define GPSRG_SR_SRR_MASK          (0x1U << GPSRG_SR_SRR_POS)      // 1 bit: 28U
#define GPSRG_SR_BRDIS_MASK        (0x1U << GPSRG_SR_BRDIS_POS)    // 1 bit: 27U
#define GPSRG_SR_LOCKSTAT_MASK     (0x1U << GPSRG_SR_LOCKSTAT_POS) // 1 bit: 26U
#define GPSRG_SR_LOCKCLR_MASK      (0x1U << GPSRG_SR_LOCKCLR_POS)  // 1 bit: 18U
#define GPSRG_SR_LOCKSET_MASK      (0x1U << GPSRG_SR_LOCKSET_POS)  // 1 bit: 17U
#define GPSRG_SR_DATA_MASK         (0x1FFFFU << GPSRG_SR_DATA_POS) // 17 bits: 16-0U

#define GET_GPSRG_SR_IOV(reg)      (((reg) & GPSRG_SR_IOV_MASK) >> GPSRG_SR_IOV_POS)
#define GET_GPSRG_SR_SRR(reg)      (((reg) & GPSRG_SR_SRR_MASK) >> GPSRG_SR_SRR_POS)
#define GET_GPSRG_SR_BRDIS(reg)    (((reg) & GPSRG_SR_BRDIS_MASK) >> GPSRG_SR_BRDIS_POS)
#define GET_GPSRG_SR_LOCKSTAT(reg) (((reg) & GPSRG_SR_LOCKSTART_MASK) >> GPSRG_SR_LOCKSTART_POS)
#define GET_GPSRG_SR_DATA(reg)     (((reg) & GPSRG_SR_DATA_MASK) >> GPSRG_SR_DATA_POS)

#define SET_GPSRG_SR_IOVCLR(reg, val)          \
    ((reg) = ((reg) & ~GPSRG_SR_IOVCLR_MASK) | \
            (((val) << GPSRG_SR_IOVCLR_POS) & GPSRG_SR_IOVCLR_MASK))
#define SET_GPSRG_SR_SETR(reg, val) \
    ((reg) = ((reg) & ~GPSRG_SR_SETR_MASK) | (((val) << GPSRG_SR_SETR_POS) & GPSRG_SR_SETR_MASK))
#define SET_GPSRG_SR_BRDIS(reg, val) \
    ((reg) = ((reg) & ~GPSRG_SR_BRDIS_MASK) | (((val) << GPSRG_SR_BRDIS_POS) & GPSRG_SR_BRDIS_MASK))
#define SET_GPSRG_SR_LOCKCLR(reg, val)          \
    ((reg) = ((reg) & ~GPSRG_SR_LOCKCLR_MASK) | \
            (((val) << GPSRG_SR_LOCKCLR_POS) & GPSRG_SR_LOCKCLR_MASK))
#define SET_GPSRG_SR_LOCKSET(reg, val)          \
    ((reg) = ((reg) & ~GPSRG_SR_LOCKSET_MASK) | \
            (((val) << GPSRG_SR_LOCKSET_POS) & GPSRG_SR_LOCKSET_MASK))
#define SET_GPSRG_SR_DATA(reg, val) \
    ((reg) = ((reg) & ~GPSRG_SR_DATA_MASK) | (((val) << GPSRG_SR_DATA_POS) & GPSRG_SR_DATA_MASK))

// Define bit positions for each field
#define NVIC_SR_STAT_POS         31U
#define NVIC_SR_CS_POS           27U
#define NVIC_SR_ID_POS           16U
#define NVIC_SR_INVALID_POS      13U
#define NVIC_SR_VALID_POS        12U
#define NVIC_SR_PN_POS           0U

// Define masks for each field
#define NVIC_SR_STAT_MASK        (0x1U << NVIC_SR_STAT_POS)    // 1 bit: 31U
#define NVIC_SR_CS_MASK          (0x1U << NVIC_SR_CS_POS)      // 4 bits: 27U
#define NVIC_SR_ID_MASK          (0x7FFU << NVIC_SR_ID_POS)    // 11 bits: 26-16U
#define NVIC_SR_INVALID_MASK     (0x1U << NVIC_SR_INVALID_POS) // 1 bit: 13U
#define NVIC_SR_VALID_MASK       (0x1U << NVIC_SR_VALID_POS)   // 1 bit: 12U
#define NVIC_SR_PN_MASK          (0xFFU << NVIC_SR_PN_POS)     // 4 bits: 7-0U

// Macros to read the fields from the register value
#define GET_NVIC_SR_STAT(reg)    (((reg) & NVIC_SR_STAT_MASK) >> NVIC_SR_STAT_POS)
#define GET_NVIC_SR_CS(reg)      (((reg) & NVIC_SR_CS_MASK) >> NVIC_SR_CS_POS)
#define GET_NVIC_SR_ID(reg)      (((reg) & NVIC_SR_ID_MASK) >> NVIC_SR_ID_POS)
#define GET_NVIC_SR_INVALID(reg) (((reg) & NVIC_SR_INVALID_MASK) >> NVIC_SR_INVALID_POS)
#define GET_NVIC_SR_VALID(reg)   (((reg) & NVIC_SR_VALID_MASK) >> NVIC_SR_VALID_POS)
#define GET_NVIC_SR_PN(reg)      (((reg) & NVIC_SR_PN_MASK) >> NVIC_SR_PN_POS)

struct nvic_src_hw {
    volatile uint32_t SRC[NVIC_MAX_INTERRUPTS];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct nvic_gpsr_hw {
    volatile uint32_t SRC_GPSRG_SR[8];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct NVIC_ACCESSEN {
    volatile uint32_t WRA; // write access enable register A
    volatile uint32_t WRB; // write access enable register B
    volatile uint32_t RDA; // read access enable register A
    volatile uint32_t RDB; // read access enable register B
    volatile uint32_t VM;  // VM access enable register
    volatile uint32_t PRS; // PRS access enable register
};

struct nvic_int_gpsrg_swc {
    volatile uint32_t ACCEN; // 0x0700 + x*40H + y*4: GPRSGx_SWCy write access protection register
    volatile uint32_t CR;    // 0x0720 + x*40H + y*4: SW control register for GPSRGxSRy
};

struct nvic_int_gpsrg {
    volatile struct nvic_int_gpsrg_swc SWC[NVIC_MAX_SW_INT]; // 0x0700U
};

struct nvic_int_tos {
    volatile struct NVIC_ACCESSEN ACCENSCFG;  /* Configure access to SRC[0:15] */
    volatile struct NVIC_ACCESSEN ACCENSCTRL; /* Configure access to SRC[16:31] */
};

struct nvic_int_icu {
    volatile uint32_t VM[NVIC_MAX_VM]; // 0x0C00 + z*34H + y*4: ICU latest service request
                                       // information signaled for VMy
    volatile uint32_t LASR;  // 0x0C20 + z*34H: ICU Last Acknowledged Service Request Register
    volatile uint32_t ECR;   // 0x0C24 + z*34H: ICU error capture register
    volatile uint32_t ECTRL; // 0x0C28 + z*34H: ICU error control register
    volatile uint32_t EGEN;  // 0x0C2C + z*34H: ICU error generation register
    volatile uint32_t VMEN;  // 0x0C30 + z*34H: ICU VM control register
};

struct nvic_int_hw {
    volatile uint32_t RESERVED1;
    volatile uint32_t OCS;                   // 0x0004: OCDS Control and Status Register
    volatile uint32_t ID;                    // 0x0008: Module Identification Register
    volatile uint32_t LCLTEST;               // 0x000C: LCL Test Register
    volatile uint32_t OIXMS;                 // 0x0010: OTGB IRQ MUX Missed IRQ Select
    volatile uint32_t OIXS0;                 // 0x0014: OTGB IRQ MUX Select 0U
    volatile uint32_t OIXS1;                 // 0x0018: OTGB IRQ MUX Select 1U
    volatile uint32_t OIT;                   // 0x001C: OTGB IRQ Trace
    volatile uint32_t PROTSE;                // 0x0020: PROT Register safe endinit
    volatile uint32_t PROTCSE;               // 0x0024: PROT Register Cyber Security Endinit
    volatile uint32_t PROTTOS[NVIC_MAX_ISP]; // 0x0030 + z*4: PROT Register for TOS=z  0 <= z <= 10U
    volatile struct NVIC_ACCESSEN ACCENCS;
    volatile uint32_t reserved2[2];          // Padding to 0x00A0U
    volatile struct NVIC_ACCESSEN ACCENDBG;
    volatile uint8_t RESERVED3[0x100 - 0xB4];              // Padding to 0x0100U
    volatile struct NVIC_ACCESSEN ACCENSRB[NVIC_MAX_GROUPS];
    volatile uint32_t RESERVED4[0x300 - 0x280];            // Padding to 0x0300U
    volatile struct nvic_int_tos TOS[NVIC_MAX_ISP];        // Type Of Service
    volatile uint32_t RESERVED5[0x700 - 0x510];            // Padding to 0x0700U
    volatile struct nvic_int_gpsrg GPSRG[NVIC_MAX_GROUPS]; /* General Purpose Service Request */
    volatile uint32_t SRB[NVIC_MAX_GROUPS]; // 0x0B00 + x*4: Service request broadcast register x
    volatile uint32_t RESERVED6[0xC00 - 0xB40];     // Padding to 0x0c00U
    volatile struct nvic_int_icu ICU[NVIC_MAX_ISP]; // 0x0C00 + z*34H
} __attribute__((__packed__, aligned(PAGE_SIZE)));

extern volatile struct nvic_src_hw* nvic_src;
extern volatile struct nvic_int_hw* nvic_int;
extern volatile struct nvic_gpsr_hw* nvic_gpsr;
extern size_t NVIC_IMPL_INTERRUPTS;

void nvic_init(void);
void nvic_cpu_init(void);
void nvic_handle(void);
void nvic_set_enbl(irqid_t int_id, bool en);
bool nvic_get_enbl(irqid_t int_id);
void nvic_set_prio(irqid_t int_id, uint32_t prio);
uint32_t nvic_get_prio(irqid_t int_id);
bool nvic_get_pend(irqid_t int_id);
bool nvic_set_pend(irqid_t int_id);
bool nvic_clr_pend(irqid_t int_id);
void nvic_send_ipi(cpuid_t target_cpu);
bool nvic_id_valid(unsigned long id);

struct vm;
void nvic_assign_icu_to_vm(unsigned long id, struct vm* vm);

#endif /* __NVIC_H__ */
