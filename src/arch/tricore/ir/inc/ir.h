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
#define IR_MAX_VM        (8)
#define IR_MAX_GROUPS        (16)
#define IR_MAX_NODES        (8)


struct ir_src_hw {
    uint32_t src[IR_MAX_INTERRUPTS];
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
    uint32_t padding;
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
    struct IR_ACCESSEN ACCENCS_PRS;
    uint32_t RESERVED2[2];           // Padding to 0x00A0
    struct IR_ACCESSEN ACCENDBG;
    uint8_t RESERVED3[0x100-0xB4];   // Padding to 0x0100
    struct IR_ACCESSEN ACCESSRB[16];
    uint32_t RESERVED4[0x300-0x280]; // Padding to 0x0300
    struct {
        struct IR_ACCESSEN ACCENSCFG;
        struct IR_ACCESSEN ACCENSCTRL;
    } TOS[IR_MAX_ISP];
    uint32_t RESERVED5[0x700-0x510]; // Padding to 0x0700
    struct {
        struct {
            uint32_t ACCEN; // 0x0700 + x*40H + y*4: GPRSGx_SWCy write access protection register
            uint32_t SWC;   // 0x0720 + x*40H + y*4: SW control register for GPSRGxSRy
        } SR[IR_MAX_NODES];
    } GPSRG[IR_MAX_GROUPS];
    uint32_t SRB[IR_MAX_GROUPS];       // 0x0B00 + x*4: Service request broadcast register x
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
void ir_set_threshold(size_t cntxt, uint32_t threshold);
uint32_t ir_get_threshold(irqid_t int_id);
bool ir_get_pend(irqid_t int_id);
bool ir_set_pend(irqid_t int_id);
bool ir_clr_pend(irqid_t int_id);

struct ir_cntxt {
    cpuid_t core_id;
    enum { PRIV_M = 3, PRIV_S = 2, PRIV_U = 0 } mode;
};

ssize_t ir_plat_cntxt_to_id(struct ir_cntxt cntxt);
struct ir_cntxt ir_plat_id_to_cntxt(size_t id);

#endif /* __IR_H__ */
