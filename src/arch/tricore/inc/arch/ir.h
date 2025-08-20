/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __IR_H__
#define __IR_H__

#include <bao.h>
#include <platform.h>
#include "prot.h"

#define IR_MAX_INTERRUPTS (2048U)
#define IR_MAX_ISP        (11U)
#define IR_MAX_VM         (8U)
#define IR_MAX_GROUPS     (8U)
#define IR_MAX_SW_INT     (8U)
#define IR_MAX_PRIO       (255U)
#define IR_MIN_PRIO       (0U)
#define IR_TARGET_NONE    (0xfU)

#ifndef PLAT_IR_MAX_INTERRUPTS
#define PLAT_IR_MAX_INTERRUPTS IR_MAX_INTERRUPTS
#endif

#ifndef PLAT_IR_MAX_ISP
#define PLAT_IR_MAX_ISP IR_MAX_ISP /* TODO might not make sense */
#endif

#ifndef PLAT_IR_MAX_VM
#define PLAT_IR_MAX_VM IR_MAX_VM
#endif

#ifndef PLAT_IR_MAX_VM
#define PLAT_IR_MAX_GROUPS IR_MAX_GROUPS
#endif

#ifndef PLAT_IR_MAX_VM
#define PLAT_IR_MAX_SW_INT IR_MAX_SW_INT
#endif

// Define the register offset
#define REG_OFFSET             0x0004U

// Define bit positions for each field
#define IR_SRC_IOVCLR_POS      28U
#define IR_SRC_IOV_POS         27U
#define IR_SRC_SETR_POS        26U
#define IR_SRC_CLRR_POS        25U
#define IR_SRC_SRR_POS         24U
#define IR_SRC_SRE_POS         23U
#define IR_SRC_TOS_POS         12U
#define IR_SRC_CS_POS          11U
#define IR_SRC_VM_POS          8U
#define IR_SRC_SRPN_POS        0U

// Define IR_SRC masks for each field
#define IR_SRC_IOVCLR_MASK     (0x1U << IR_SRC_IOVCLR_POS)
#define IR_SRC_IOV_MASK        (0x1U << IR_SRC_IOV_POS)
#define IR_SRC_SETR_MASK       (0x1U << IR_SRC_SETR_POS)
#define IR_SRC_CLRR_MASK       (0x1U << IR_SRC_CLRR_POS)
#define IR_SRC_SRR_MASK        (0x1U << IR_SRC_SRR_POS)
#define IR_SRC_SRE_MASK        (0x1U << IR_SRC_SRE_POS)
#define IR_SRC_TOS_MASK        (0xFU << IR_SRC_TOS_POS)
#define IR_SRC_CS_MASK         (0x1U << IR_SRC_CS_POS)
#define IR_SRC_VM_MASK         (0x7U << IR_SRC_VM_POS)
#define IR_SRC_SRPN_MASK       (0xFFU << IR_SRC_SRPN_POS)

// Macros to read the fields from the register value
#define IR_SRC_GET_IOVCLR(reg) (((reg) & IR_SRC_IOVCLR_MASK) >> IR_SRC_IOVCLR_POS)
#define IR_SRC_GET_IOV(reg)    (((reg) & IR_SRC_IOV_MASK) >> IR_SRC_IOV_POS)
#define IR_SRC_GET_SETR(reg)   (((reg) & IR_SRC_SETR_MASK) >> IR_SRC_SETR_POS)
#define IR_SRC_GET_CLRR(reg)   (((reg) & IR_SRC_CLRR_MASK) >> IR_SRC_CLRR_POS)
#define IR_SRC_GET_SRR(reg)    (((reg) & IR_SRC_SRR_MASK) >> IR_SRC_SRR_POS)
#define IR_SRC_GET_SRE(reg)    (((reg) & IR_SRC_SRE_MASK) >> IR_SRC_SRE_POS)
#define IR_SRC_GET_TOS(reg)    (((reg) & IR_SRC_TOS_MASK) >> IR_SRC_TOS_POS)
#define IR_SRC_GET_CS(reg)     (((reg) & IR_SRC_CS_MASK) >> IR_SRC_CS_POS)
#define IR_SRC_GET_VM(reg)     (((reg) & IR_SRC_VM_MASK) >> IR_SRC_VM_POS)
#define IR_SRC_GET_SRPN(reg)   (((reg) & IR_SRC_SRPN_MASK) >> IR_SRC_SRPN_POS)

// Macros to set the fields in the register value
#define IR_SRC_SET_IOVCLR(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_IOVCLR_MASK) | (((val) << IR_SRC_IOVCLR_POS) & IR_SRC_IOVCLR_MASK))
#define IR_SRC_SET_IOV(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_IOV_MASK) | (((val) << IR_SRC_IOV_POS) & IR_SRC_IOV_MASK))
#define IR_SRC_SET_SETR(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_SETR_MASK) | (((val) << IR_SRC_SETR_POS) & IR_SRC_SETR_MASK))
#define IR_SRC_SET_CLRR(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_CLRR_MASK) | (((val) << IR_SRC_CLRR_POS) & IR_SRC_CLRR_MASK))
#define IR_SRC_SET_SRR(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_SRR_MASK) | (((val) << IR_SRC_SRR_POS) & IR_SRC_SRR_MASK))
#define IR_SRC_SET_SRE(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_SRE_MASK) | (((val) << IR_SRC_SRE_POS) & IR_SRC_SRE_MASK))
#define IR_SRC_SET_TOS(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_TOS_MASK) | (((val) << IR_SRC_TOS_POS) & IR_SRC_TOS_MASK))
#define IR_SRC_SET_CS(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_CS_MASK) | (((val) << IR_SRC_CS_POS) & IR_SRC_CS_MASK))
#define IR_SRC_SET_VM(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_VM_MASK) | (((val) << IR_SRC_VM_POS) & IR_SRC_VM_MASK))
#define IR_SRC_SET_SRPN(reg, val) \
    ((reg) = ((reg) & ~IR_SRC_SRPN_MASK) | (((val) << IR_SRC_SRPN_POS) & IR_SRC_SRPN_MASK))

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
#define IR_SR_STAT_POS         31U
#define IR_SR_CS_POS           27U
#define IR_SR_ID_POS           16U
#define IR_SR_INVALID_POS      13U
#define IR_SR_VALID_POS        12U
#define IR_SR_PN_POS           0U

// Define masks for each field
#define IR_SR_STAT_MASK        (0x1U << IR_SR_STAT_POS)    // 1 bit: 31U
#define IR_SR_CS_MASK          (0x1U << IR_SR_CS_POS)      // 4 bits: 27U
#define IR_SR_ID_MASK          (0x7FFU << IR_SR_ID_POS)    // 11 bits: 26-16U
#define IR_SR_INVALID_MASK     (0x1U << IR_SR_INVALID_POS) // 1 bit: 13U
#define IR_SR_VALID_MASK       (0x1U << IR_SR_VALID_POS)   // 1 bit: 12U
#define IR_SR_PN_MASK          (0xFFU << IR_SR_PN_POS)     // 4 bits: 7-0U

// Macros to read the fields from the register value
#define GET_IR_SR_STAT(reg)    (((reg) & IR_SR_STAT_MASK) >> IR_SR_STAT_POS)
#define GET_IR_SR_CS(reg)      (((reg) & IR_SR_CS_MASK) >> IR_SR_CS_POS)
#define GET_IR_SR_ID(reg)      (((reg) & IR_SR_ID_MASK) >> IR_SR_ID_POS)
#define GET_IR_SR_INVALID(reg) (((reg) & IR_SR_INVALID_MASK) >> IR_SR_INVALID_POS)
#define GET_IR_SR_VALID(reg)   (((reg) & IR_SR_VALID_MASK) >> IR_SR_VALID_POS)
#define GET_IR_SR_PN(reg)      (((reg) & IR_SR_PN_MASK) >> IR_SR_PN_POS)
struct ir_src_hw {
    volatile uint32_t SRC[IR_MAX_INTERRUPTS];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct ir_gpsr_hw {
    volatile uint32_t SRC_GPSRG_SR[8];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct ir_int_gpsrg_swc {
    volatile uint32_t ACCEN; // 0x0700 + x*40H + y*4: GPRSGx_SWCy write access protection register
    volatile uint32_t CR;    // 0x0720 + x*40H + y*4: SW control register for GPSRGxSRy
};

struct ir_int_gpsrg {
    volatile uint32_t SWCACCEN[IR_MAX_SW_INT]; // 0x0700 + x*40H + y*4: GPRSGx_SWCy write access
                                               // protection register
    volatile uint32_t SWC[IR_MAX_SW_INT]; // 0x0720 + x*40H + y*4: SW control register for GPSRGxSRy
};

struct ir_int_tos {
    volatile struct PROT_ACCESSEN ACCENSCFG;  /* Configure access to SRC[0:15] */
    volatile struct PROT_ACCESSEN ACCENSCTRL; /* Configure access to SRC[16:31] */
};

struct ir_int_icu {
    volatile uint32_t VM[IR_MAX_VM]; // 0x0C00 + z*34H + y*4: ICU latest service request information
                                     // signaled for VMy
    volatile uint32_t LASR;  // 0x0C20 + z*34H: ICU Last Acknowledged Service Request Register
    volatile uint32_t ECR;   // 0x0C24 + z*34H: ICU error capture register
    volatile uint32_t ECTRL; // 0x0C28 + z*34H: ICU error control register
    volatile uint32_t EGEN;  // 0x0C2C + z*34H: ICU error generation register
    volatile uint32_t VMEN;  // 0x0C30 + z*34H: ICU VM control register
};

struct ir_int_hw {
    volatile uint32_t RESERVED1;
    volatile uint32_t OCS;                 // 0x0004: OCDS Control and Status Register
    volatile uint32_t ID;                  // 0x0008: Module Identification Register
    volatile uint32_t LCLTEST;             // 0x000C: LCL Test Register
    volatile uint32_t OIXMS;               // 0x0010: OTGB IRQ MUX Missed IRQ Select
    volatile uint32_t OIXS0;               // 0x0014: OTGB IRQ MUX Select 0U
    volatile uint32_t OIXS1;               // 0x0018: OTGB IRQ MUX Select 1U
    volatile uint32_t OIT;                 // 0x001C: OTGB IRQ Trace
    volatile uint32_t PROTSE;              // 0x0020: PROT Register safe endinit
    volatile uint32_t PROTCSE;             // 0x0024: PROT Register Cyber Security Endinit
    volatile uint8_t RESERVED8[0x30 - 0x28];
    volatile uint32_t PROTTOS[IR_MAX_ISP]; // 0x0030 + z*4: PROT Register for TOS=z  0 <= z <= 10U
    volatile uint8_t RESERVED7[0x80 - 0x5C];
    volatile struct PROT_ACCESSEN ACCENCS;
    volatile uint32_t reserved2[2];        // Padding to 0x00A0U
    volatile struct PROT_ACCESSEN ACCENDBG;
    volatile uint8_t RESERVED3[0x100 - 0xB8];          // Padding to 0x0100U
    volatile struct PROT_ACCESSEN ACCENSRB[IR_MAX_GROUPS];
    volatile uint8_t RESERVED4[0x300 - 0x1C0];         // Padding to 0x0300U
    volatile struct ir_int_tos TOS[IR_MAX_ISP];        // Type Of Service
    volatile uint8_t RESERVED5[0x700 - 0x510];         // Padding to 0x0700U
    volatile struct ir_int_gpsrg GPSRG[IR_MAX_GROUPS]; /* General Purpose Service Request */
    volatile uint8_t RESERVED9[0xB00 - 0x900];
    volatile uint32_t SRB[IR_MAX_GROUPS];      // 0x0B00 + x*4: Service request broadcast register x
    volatile uint8_t RESERVED6[0xC00 - 0xB20]; // Padding to 0x0c00U
    volatile struct ir_int_icu ICU[IR_MAX_ISP]; // 0x0C00 + z*34H
} __attribute__((__packed__, aligned(PAGE_SIZE)));

extern volatile struct ir_src_hw* ir_src;
extern volatile struct ir_int_hw* ir_int;
extern volatile struct ir_gpsr_hw* ir_gpsr;
extern size_t IR_IMPL_INTERRUPTS;

void ir_init(void);
void ir_cpu_init(void);
void ir_handle(void);
void ir_set_enbl(irqid_t int_id, bool en);
bool ir_get_enbl(irqid_t int_id);
void ir_set_prio(irqid_t int_id, uint32_t prio);
uint32_t ir_get_prio(irqid_t int_id);
bool ir_get_pend(irqid_t int_id);
bool ir_set_pend(irqid_t int_id);
bool ir_clr_pend(irqid_t int_id);
void ir_send_ipi(cpuid_t target_cpu);
bool ir_id_valid(unsigned long id);

struct vm;
void ir_assign_icu_to_vm(unsigned long id, struct vm* vm);
bool ir_src_config_irq(unsigned long id, unsigned long tos, unsigned long vm, unsigned long prio);
bool ir_src_config_tos(unsigned long id, unsigned long tos);
bool ir_src_config_vm(unsigned long id, unsigned long vm);
bool ir_src_config_priority(unsigned long id, unsigned long prio);
bool ir_src_enable(unsigned long id, bool en);
bool ir_src_set_node(unsigned long id, unsigned long val);
void ir_init_gspr_group(unsigned long id, struct vm* vm);
void ir_clear_gspr_group(unsigned long id);
unsigned long ir_src_get_node(unsigned long id);

#endif /* __IR_H__ */
