/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __IR_H__
#define __IR_H__

#include <bao.h>
#include <platform.h>

#define IR_MAX_INTERRUPTS (1024)
#define IR_NUM_PRIO_REGS  (IR_MAX_INTERRUPTS)
#define IR_NUM_PEND_REGS  (IR_MAX_INTERRUPTS)
#define IR_NUM_ENBL_REGS  (IR_MAX_INTERRUPTS / 32)

#define IR_ENBL_OFF       (0x002000)
#define IR_THRESHOLD_OFF  (0x200000)

#ifndef PLAT_IR_CNTXT_PER_CORE
#define PLAT_IR_CNTXT_PER_CORE 2
#endif

#define IR_PLAT_CNTXT_NUM ((PLAT_IR_CNTXT_PER_CORE) * (PLAT_CPU_NUM))

struct ir_global_hw {
    uint32_t prio[IR_NUM_PRIO_REGS];
    uint32_t pend[IR_NUM_PEND_REGS];
    uint32_t enbl[IR_PLAT_CNTXT_NUM][IR_NUM_ENBL_REGS];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct ir_core_hw {
    uint32_t threshold;
    union {
        uint32_t claim;
        uint32_t complete;
    };
    uint8_t res[0x1000 - 0x0008];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

extern volatile struct ir_global_hw* ir_global;
extern volatile struct ir_core_hw* ir_core;
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

struct ir_cntxt {
    cpuid_t core_id;
    enum { PRIV_M = 3, PRIV_S = 2, PRIV_U = 0 } mode;
};

ssize_t ir_plat_cntxt_to_id(struct ir_cntxt cntxt);
struct ir_cntxt ir_plat_id_to_cntxt(size_t id);

#endif /* __IR_H__ */
