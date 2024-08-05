/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __IR_H__
#define __IR_H__

#include <bao.h>
#include <platform.h>

#define IR_MAX_INTERRUPTS (2024)
#define IR_MAX_ISP        (11)
#define IR_MAX_VM         (8)
#define IR_MAX_GROUPS     (16)
#define IR_MAX_SW_INT      (8)
#define IR_MAX_PRIO       (255)

#ifndef PLAT_IR_MAX_INTERRUPTS
#define PLAT_IR_MAX_INTERRUPTS IR_MAX_INTERRUPTS
#endif

#ifndef PLAT_IR_MAX_ISP
#define PLAT_IR_MAX_ISP        IR_MAX_ISP /* TODO might not make sense */
#endif

#ifndef PLAT_IR_MAX_VM
#define PLAT_IR_MAX_VM         IR_MAX_VM
#endif

#ifndef PLAT_IR_MAX_VM
#define PLAT_IR_MAX_GROUPS     IR_MAX_GROUPS
#endif

#ifndef PLAT_IR_MAX_VM
#define PLAT_IR_MAX_SW_INT      IR_MAX_SW_INT
#endif


// Define the register offset
#define REG_OFFSET 0x0004

// Define bit positions for each field
#define IR_SRC_IOVCLR_POS  28
#define IR_SRC_IOV_POS  27
#define IR_SRC_SETR_POS 26
#define IR_SRC_CLRR_POS 25
#define IR_SRC_SRR_POS  24
#define IR_SRC_SRE_POS  23
#define IR_SRC_TOS_POS  12
#define IR_SRC_CS_POS   11
#define IR_SRC_VM_POS   8
#define IR_SRC_SRPN_POS 0

// DefinIR_SRC_e masks for each field
#define IR_SRC_IOVCLR_MASK (0x1 << IR_SRC_IOVCLR_POS)
#define IR_SRC_IOV_MASK  (0x1 << IR_SRC_IOV_POS)
#define IR_SRC_SETR_MASK (0x1 << IR_SRC_SETR_POS)
#define IR_SRC_CLRR_MASK (0x1 << IR_SRC_CLRR_POS)
#define IR_SRC_SRR_MASK  (0x1 << IR_SRC_SRR_POS)
#define IR_SRC_SRE_MASK  (0x1 << IR_SRC_SRE_POS)
#define IR_SRC_TOS_MASK  (0xF << IR_SRC_TOS_POS)
#define IR_SRC_CS_MASK   (0x1 << IR_SRC_CS_POS)
#define IR_SRC_VM_MASK   (0x7 << IR_SRC_VM_POS)
#define IR_SRC_SRPN_MASK (0xFF << IR_SRC_SRPN_POS)

// Macros to read the fields from the register value
#define IR_SRC_GET_IOV(reg)  (((reg) & IR_SRC_IOV_MASK) >> IR_SRC_IOV_POS)
#define IR_SRC_GET_SRE(reg)  (((reg) & IR_SRC_SRE_MASK) >> IR_SRC_SRE_POS)
#define IR_SRC_GET_TOS(reg)  (((reg) & IR_SRC_TOS_MASK) >> IR_SRC_TOS_POS)
#define IR_SRC_GET_CS(reg)   (((reg) & IR_SRC_CS_MASK) >> IR_SRC_CS_POS)
#define IR_SRC_GET_VM(reg)   (((reg) & IR_SRC_VM_MASK) >> IR_SRC_VM_POS)
#define IR_SRC_GET_SRPN(reg) (((reg) & IR_SRC_SRPN_MASK) >> IR_SRC_SRPN_POS)

#define IR_SRC_SET_IOVCLR(reg, val) ((reg) = ((reg) & ~IR_SRC_IOVCLR_MASK) | (((val) << IR_SRC_IOVCLR_POS) & IR_SRC_IOVCLR_MASK))
#define IR_SRC_SET_SETR(reg, val) ((reg) = ((reg) & ~IR_SRC_SETR_MASK) | (((val) << SETR_POS) & IR_SRC_SETR_MASK))
#define IR_SRC_SET_CLRR(reg, val)  ((reg) = ((reg) & ~IR_SRC_CLRR_MASK) | (((val) << CLRR_POS) & IR_SRC_CLRR_MASK))
#define IR_SRC_SET_SRE(reg, val)  ((reg) = ((reg) & ~IR_SRC_RE_MASK) | (((val) << IR_SRC_SRE_POS) & IR_SRC_SRE_MASK))
#define IR_SRC_SET_TOS(reg, val)  ((reg) = ((reg) & ~IR_SRC_OS_MASK) | (((val) << IR_SRC_TOS_POS) & IR_SRC_TOS_MASK))
#define IR_SRC_SET_CS(reg, val)   ((reg) = ((reg) & ~IR_SRC_S_MASK) | (((val) << IR_SRC_CS_POS) & IR_SRC_CS_MASK))
#define IR_SRC_SET_VM(reg, val)   ((reg) = ((reg) & ~IR_SRC_M_MASK) | (((val) << IR_SRC_VM_POS) & IR_SRC_VM_MASK))
#define IR_SRC_SET_SRPN(reg, val) ((reg) = ((reg) & ~IR_SRC_RPN_MASK) | (((val) << IR_SRC_SRPN_POS) & IR_SRC_SRPN_MASK))

#define GPSRG_SR_IOVCLR_POS       31
#define GPSRG_SR_IOV_POS          30
#define GPSRG_SR_SETR_POS         29
#define GPSRG_SR_SRR_POS          28
#define GPSRG_SR_BRDIS_POS        27
#define GPSRG_SR_LOCKSTAT_POS     18
#define GPSRG_SR_LOCKCLR_POS      17
#define GPSRG_SR_LOCKSET_POS      16
#define GPSRG_SR_DATA_POS         0

#define GPSRG_SR_IOVCLR_MASK     (0x1 << GPSRG_SR_IOVCLR_POS)        // 1 bit: 31
#define GPSRG_SR_IOV_MASK        (0x1 << GPSRG_SR_IOV_POS)          // 1 bit: 30
#define GPSRG_SR_SETR_MASK       (0x1 << GPSRG_SR_SETR_POS)         // 1 bit: 29
#define GPSRG_SR_SRR_MASK        (0x1 << GPSRG_SR_SRR_POS)          // 1 bit: 28
#define GPSRG_SR_BRDIS_MASK      (0x1 << GPSRG_SR_BRDIS_POS)        // 1 bit: 27
#define GPSRG_SR_LOCKSTAT_MASK   (0x1 << GPSRG_SR_LOCKSTAT_POS)    // 1 bit: 26
#define GPSRG_SR_LOCKCLR_MASK    (0x1 << GPSRG_SR_LOCKCLR_POS)      // 1 bit: 18
#define GPSRG_SR_LOCKSET_MASK    (0x1 << GPSRG_SR_LOCKSET_POS)      // 1 bit: 17
#define GPSRG_SR_DATA_MASK       (0x1FFFF << GPSRG_SR_DATA_POS)     // 17 bits: 16-0

#define GET_GPSRG_SR_IOV(reg)        (((reg) & GPSRG_SR_IOV_MASK) >> GPSRG_SR_IOV_POS)
#define GET_GPSRG_SR_SRR(reg)        (((reg) & GPSRG_SR_SRR_MASK) >> GPSRG_SR_SRR_POS)
#define GET_GPSRG_SR_BRDIS(reg)      (((reg) & GPSRG_SR_BRDIS_MASK) >> GPSRG_SR_BRDIS_POS)
#define GET_GPSRG_SR_LOCKSTAT(reg)   (((reg) & GPSRG_SR_LOCKSTART_MASK) >> GPSRG_SR_LOCKSTART_POS)
#define GET_GPSRG_SR_DATA(reg)       (((reg) & GPSRG_SR_DATA_MASK) >> GPSRG_SR_DATA_POS)

#define SET_GPSRG_SR_IOVCLR(reg, val)      ((reg) = ((reg) & ~GPSRG_SR_IOVCLR_MASK) | (((val) << GPSRG_SR_IOVCLR_POS) & GPSRG_SR_IOVCLR_MASK))
#define SET_GPSRG_SR_SETR(reg, val)        ((reg) = ((reg) & ~GPSRG_SR_SETR_MASK) | (((val) << GPSRG_SR_SETR_POS) & GPSRG_SR_SETR_MASK))
#define SET_GPSRG_SR_BRDIS(reg, val)       ((reg) = ((reg) & ~GPSRG_SR_BRDIS_MASK) | (((val) << GPSRG_SR_BRDIS_POS) & GPSRG_SR_BRDIS_MASK))
#define SET_GPSRG_SR_LOCKCLR(reg, val)     ((reg) = ((reg) & ~GPSRG_SR_LOCKCLR_MASK) | (((val) << GPSRG_SR_LOCKCLR_POS) & GPSRG_SR_LOCKCLR_MASK))
#define SET_GPSRG_SR_LOCKSET(reg, val)     ((reg) = ((reg) & ~GPSRG_SR_LOCKSET_MASK) | (((val) << GPSRG_SR_LOCKSET_POS) & GPSRG_SR_LOCKSET_MASK))
#define SET_GPSRG_SR_DATA(reg, val)        ((reg) = ((reg) & ~GPSRG_SR_DATA_MASK) | (((val) << GPSRG_SR_DATA_POS) & GPSRG_SR_DATA_MASK))

// Define bit positions for each field
#define IR_SR_STAT_POS    31
#define IR_SR_CS_POS      27
#define IR_SR_ID_POS      16
#define IR_SR_INVALID_POS 13
#define IR_SR_VALID_POS   12
#define IR_SR_PN_POS      0

// Define masks for each field
#define IR_SR_STAT_MASK    (0x1 << IR_SR_STAT_POS)      // 1 bit: 31
#define IR_SR_CS_MASK      (0x1 << IR_SR_CS_POS)        // 4 bits: 27
#define IR_SR_ID_MASK      (0x7FF << IR_SR_ID_POS)      // 11 bits: 26-16
#define IR_SR_INVALID_MASK (0x1 << IR_SR_INVALID_POS)   // 1 bit: 13
#define IR_SR_VALID_MASK   (0x1 << IR_SR_VALID_POS)     // 1 bit: 12
#define IR_SR_PN_MASK      (0xFF << IR_SR_PN_POS)        // 4 bits: 7-0

// Macros to read the fields from the register value
#define GET_IR_SR_STAT(reg)    (((reg) & IR_SR_STAT_MASK) >> IR_SR_STAT_POS)
#define GET_IR_SR_CS(reg)      (((reg) & IR_SR_CS_MASK) >> IR_SR_CS_POS)
#define GET_IR_SR_ID(reg)      (((reg) & IR_SR_ID_MASK) >> IR_SR_ID_POS)
#define GET_IR_SR_INVALID(reg) (((reg) & IR_SR_INVALID_MASK) >> IR_SR_INVALID_POS)
#define GET_IR_SR_VALID(reg)   (((reg) & IR_SR_VALID_MASK) >> IR_SR_VALID_POS)
#define GET_IR_SR_PN(reg)      (((reg) & IR_SR_PN_MASK) >> IR_SR_PN_POS)



struct ir_src_hw {
    uint32_t SRC[IR_MAX_INTERRUPTS];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct IR_ACCESSEN {
        uint32_t WRA; // write access enable register A
        uint32_t WRB; // write access enable register B
        uint32_t RDA; // read access enable register A
        uint32_t RDB; // read access enable register B
        uint32_t VM;  // VM access enable register
        uint32_t PRS; // PRS access enable register
};

struct ir_int_hw {
typedef struct {
    uint32_t RESERVED1;
    uint32_t OCS;                    // 0x0004: OCDS Control and Status Register
    uint32_t ID;                     // 0x0008: Module Identification Register
    uint32_t LCLTEST;                // 0x000C: LCL Test Register
    uint32_t OIXMS;                  // 0x0010: OTGB IRQ MUX Missed IRQ Select
    uint32_t OIXS0;                  // 0x0014: OTGB IRQ MUX Select 0
    uint32_t OIXS1;                  // 0x0018: OTGB IRQ MUX Select 1
    uint32_t OIT;                    // 0x001C: OTGB IRQ Trace
    uint32_t PROTSE;                 // 0x0020: PROT Register safe endinit
    uint32_t PROTCSE;                // 0x0024: PROT Register Cyber Security Endinit
    uint32_t PROTTOS[IR_MAX_ISP];    // 0x0030 + z*4: PROT Register for TOS=z  0 <= z <= 10
    struct IR_ACCESSEN CS;
    uint32_t reserved2[2];           // Padding to 0x00A0
    struct IR_ACCESSEN DBG;
    uint8_t RESERVED3[0x100-0xB4];   // Padding to 0x0100
    struct IR_ACCESSEN SRB[IR_MAX_GROUPS];
    uint32_t RESERVED4[0x300-0x280]; // Padding to 0x0300
    struct {
        struct IR_ACCESSEN SCFG;
        struct IR_ACCESSEN SCTRL;
    } TOS[IR_MAX_ISP]; /* Type Of Service (TOS) */
    uint32_t RESERVED5[0x700-0x510]; // Padding to 0x0700
    struct {
        struct {
            uint32_t ACCEN; // 0x0700 + x*40H + y*4: GPRSGx_SWCy write access protection register
            uint32_t SWC;   // 0x0720 + x*40H + y*4: SW control register for GPSRGxSRy
        } SR[IR_MAX_SW_INT];
    } GPSRG[IR_MAX_GROUPS]; /* General Purpose Service Request */
    uint32_t SRB[IR_MAX_GROUPS];     // 0x0B00 + x*4: Service request broadcast register x
    uint32_t RESERVED6[0xC00-0xB40]; // Padding to 0x0c00
    struct {
        uint32_t VM[IR_MAX_VM];     // 0x0C00 + z*34H + y*4: ICU latest service request information signaled for VMy
        uint32_t LASR;      // 0x0C20 + z*34H: ICU Last Acknowledged Service Request Register
        uint32_t ECR;       // 0x0C24 + z*34H: ICU error capture register
        uint32_t ECTRL;     // 0x0C28 + z*34H: ICU error control register
        uint32_t EGEN;      // 0x0C2C + z*34H: ICU error generation register
        uint32_t VMEN;      // 0x0C30 + z*34H: ICU VM control register
    } ICU[IR_MAX_ISP];
}
} __attribute__((__packed__, aligned(PAGE_SIZE)));

extern volatile struct ir_src_hw* ir_src;
extern volatile struct ir_int_hw* ir_int;
extern size_t IR_IMPL_INTERRUPTS;

void ir_init(void);
void ir_cpu_init(void);
void ir_handle(void);
void ir_set_enbl(size_t cntxt, irqid_t int_id, bool en);
bool ir_get_enbl(size_t cntxt, irqid_t int_id);
void ir_set_prio(irqid_t int_id, uint32_t prio);
uint32_t ir_get_prio(irqid_t int_id);
bool ir_get_pend(irqid_t int_id);
bool ir_set_pend(irqid_t int_id);
bool ir_clr_pend(irqid_t int_id);
void ir_send_ipi(cpuid_t target_cpu);

struct ir_cntxt {
    cpuid_t core_id;
    enum { PRIV_M = 3, PRIV_S = 2, PRIV_U = 0 } mode;
};

ssize_t ir_plat_cntxt_to_id(struct ir_cntxt cntxt);
struct ir_cntxt ir_plat_id_to_cntxt(size_t id);

#endif /* __IR_H__ */
