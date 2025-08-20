/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __IR_H__
#define __IR_H__

#include <bao.h>
#include <platform.h>
#include <arch/prot.h>

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

// Define bit positions for each field
#define IR_SRC_IOVCLR_POS      28UL
#define IR_SRC_IOV_POS         27UL
#define IR_SRC_SETR_POS        26UL
#define IR_SRC_CLRR_POS        25UL
#define IR_SRC_SRR_POS         24UL
#define IR_SRC_SRE_POS         23UL
#define IR_SRC_TOS_POS         12UL
#define IR_SRC_CS_POS          11UL
#define IR_SRC_VM_POS          8UL
#define IR_SRC_SRPN_POS        0UL

// Define IR_SRC masks for each field
#define IR_SRC_IOVCLR_MASK     (0x1UL << IR_SRC_IOVCLR_POS)
#define IR_SRC_IOV_MASK        (0x1UL << IR_SRC_IOV_POS)
#define IR_SRC_SETR_MASK       (0x1UL << IR_SRC_SETR_POS)
#define IR_SRC_CLRR_MASK       (0x1UL << IR_SRC_CLRR_POS)
#define IR_SRC_SRR_MASK        (0x1UL << IR_SRC_SRR_POS)
#define IR_SRC_SRE_MASK        (0x1UL << IR_SRC_SRE_POS)
#define IR_SRC_TOS_MASK        (0xFUL << IR_SRC_TOS_POS)
#define IR_SRC_CS_MASK         (0x1UL << IR_SRC_CS_POS)
#define IR_SRC_VM_MASK         (0x7UL << IR_SRC_VM_POS)
#define IR_SRC_SRPN_MASK       (0xFFUL << IR_SRC_SRPN_POS)

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

#define GPSRG_SR_IOVCLR_POS        31UL
#define GPSRG_SR_IOV_POS           30UL
#define GPSRG_SR_SETR_POS          29UL
#define GPSRG_SR_SRR_POS           28UL
#define GPSRG_SR_BRDIS_POS         27UL
#define GPSRG_SR_LOCKSTAT_POS      18UL
#define GPSRG_SR_LOCKCLR_POS       17UL
#define GPSRG_SR_LOCKSET_POS       16UL
#define GPSRG_SR_DATA_POS          0UL

#define GPSRG_SR_IOVCLR_MASK       (0x1UL << GPSRG_SR_IOVCLR_POS)   // 1 bit: 31U
#define GPSRG_SR_IOV_MASK          (0x1UL << GPSRG_SR_IOV_POS)      // 1 bit: 30U
#define GPSRG_SR_SETR_MASK         (0x1UL << GPSRG_SR_SETR_POS)     // 1 bit: 29U
#define GPSRG_SR_SRR_MASK          (0x1UL << GPSRG_SR_SRR_POS)      // 1 bit: 28U
#define GPSRG_SR_BRDIS_MASK        (0x1UL << GPSRG_SR_BRDIS_POS)    // 1 bit: 27U
#define GPSRG_SR_LOCKSTAT_MASK     (0x1UL << GPSRG_SR_LOCKSTAT_POS) // 1 bit: 26U
#define GPSRG_SR_LOCKCLR_MASK      (0x1UL << GPSRG_SR_LOCKCLR_POS)  // 1 bit: 18U
#define GPSRG_SR_LOCKSET_MASK      (0x1UL << GPSRG_SR_LOCKSET_POS)  // 1 bit: 17U
#define GPSRG_SR_DATA_MASK         (0x1FFFFUL << GPSRG_SR_DATA_POS) // 17 bits: 16-0U

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
#define IR_SR_STAT_POS                 31UL
#define IR_SR_CS_POS                   27UL
#define IR_SR_ID_POS                   16UL
#define IR_SR_INVALID_POS              13UL
#define IR_SR_VALID_POS                12UL
#define IR_SR_PN_POS                   0UL

// Define masks for each field
#define IR_SR_STAT_MASK                (0x1UL << IR_SR_STAT_POS)    // 1 bit: 31U
#define IR_SR_CS_MASK                  (0x1UL << IR_SR_CS_POS)      // 4 bits: 27U
#define IR_SR_ID_MASK                  (0x7FFUL << IR_SR_ID_POS)    // 11 bits: 26-16U
#define IR_SR_INVALID_MASK             (0x1UL << IR_SR_INVALID_POS) // 1 bit: 13U
#define IR_SR_VALID_MASK               (0x1UL << IR_SR_VALID_POS)   // 1 bit: 12U
#define IR_SR_PN_MASK                  (0xFFUL << IR_SR_PN_POS)     // 4 bits: 7-0U

// Macros to read the fields from the register value
#define GET_IR_SR_STAT(reg)            (((reg) & IR_SR_STAT_MASK) >> IR_SR_STAT_POS)
#define GET_IR_SR_CS(reg)              (((reg) & IR_SR_CS_MASK) >> IR_SR_CS_POS)
#define GET_IR_SR_ID(reg)              (((reg) & IR_SR_ID_MASK) >> IR_SR_ID_POS)
#define GET_IR_SR_INVALID(reg)         (((reg) & IR_SR_INVALID_MASK) >> IR_SR_INVALID_POS)
#define GET_IR_SR_VALID(reg)           (((reg) & IR_SR_VALID_MASK) >> IR_SR_VALID_POS)
#define GET_IR_SR_PN(reg)              (((reg) & IR_SR_PN_MASK) >> IR_SR_PN_POS)

#define ICU_VMEN_VM0_MASK              0x1UL
#define ICU_VMx_ID_MASK                0x7FFUL
#define ICU_VMx_ID_OFFSET              16UL
#define IR_SWCACCEN_VM_OFFSET          16UL
#define IR_SWCACCEN_VM0_MASK           16UL
#define IR_SWCACCEN_CPUx_MASK          3UL
#define IR_SWCACCEN_VM_CTRL_MASK       0UL
#define IR_SWCACCEN_VM_PRS_CTRL_OFFSET 31UL
#define SRC_TOS_UNASSIGNED             0xFUL

#define IR_INVALID_NODE                (-1UL)
struct ir_src_hw {
    volatile uint32_t SRC[IR_MAX_INTERRUPTS];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct ir_int_gpsrg {
    volatile uint32_t SWCACCEN[IR_MAX_SW_INT];
    volatile uint32_t SWC[IR_MAX_SW_INT];
};

struct ir_int_tos {
    volatile struct PROT_ACCESSEN ACCENSCFG;
    volatile struct PROT_ACCESSEN ACCENSCTRL;
};

struct ir_int_icu {
    volatile uint32_t VM[IR_MAX_VM];
    volatile uint32_t LASR;
    volatile uint32_t ECR;
    volatile uint32_t ECTRL;
    volatile uint32_t EGEN;
    volatile uint32_t VMEN;
};

struct ir_int_hw {
    volatile uint32_t RESERVED1;
    volatile uint32_t OCS;
    volatile uint32_t ID;
    volatile uint32_t LCLTEST;
    volatile uint32_t OIXMS;
    volatile uint32_t OIXS0;
    volatile uint32_t OIXS1;
    volatile uint32_t OIT;
    volatile uint32_t PROTSE;
    volatile uint32_t PROTCSE;
    volatile uint8_t RESERVED2[0x30 - 0x28];
    volatile uint32_t PROTTOS[IR_MAX_ISP];
    volatile uint8_t RESERVED3[0x80 - 0x5C];
    volatile struct PROT_ACCESSEN ACCENCS;
    volatile uint32_t RESERVED4[2];
    volatile struct PROT_ACCESSEN ACCENDBG;
    volatile uint8_t RESERVED5[0x100 - 0xB8];
    volatile struct PROT_ACCESSEN ACCENSRB[IR_MAX_GROUPS];
    volatile uint8_t RESERVED6[0x300 - 0x1C0];
    volatile struct ir_int_tos TOS[IR_MAX_ISP];
    volatile uint8_t RESERVED7[0x700 - 0x510];
    volatile struct ir_int_gpsrg GPSRG[IR_MAX_GROUPS];
    volatile uint8_t RESERVED8[0xB00 - 0x900];
    volatile uint32_t SRB[IR_MAX_GROUPS];
    volatile uint8_t RESERVED9[0xC00 - 0xB20];
    volatile struct ir_int_icu ICU[IR_MAX_ISP];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

extern volatile struct ir_src_hw* ir_src;
extern volatile struct ir_int_hw* ir_int;

void ir_init(void);
void ir_cpu_init(void);
void ir_handle(void);
bool ir_get_pend(irqid_t int_id);
bool ir_set_pend(irqid_t int_id);
bool ir_clr_pend(irqid_t int_id);
void ir_send_ipi(cpuid_t target_cpu);

struct vm;
void ir_assign_icu_to_vm(cpuid_t cpuid, vmid_t vmid);
bool ir_src_enable(irqid_t id, bool en);
bool ir_src_set_node(irqid_t id, unsigned long val);
void ir_init_gpsr_group(unsigned long id, struct vm* vm);
void ir_clear_gpsr_group(unsigned long id);
unsigned long ir_src_get_node(irqid_t id);
void ir_config_irq(irqid_t int_id, bool en);
void ir_assign_int_to_vm(vmid_t vmid, irqid_t id);

#endif /* __IR_H__ */
