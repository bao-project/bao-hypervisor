/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLIC_H__
#define __PLIC_H__

#include <bao.h>
#include <platform.h>

#define PLIC_MAX_INTERRUPTS (1024)
#define PLIC_NUM_PRIO_REGS (PLIC_MAX_INTERRUPTS)
#define PLIC_NUM_PEND_REGS (PLIC_MAX_INTERRUPTS)
#define PLIC_NUM_ENBL_REGS (PLIC_MAX_INTERRUPTS / 32)

#define PLIC_ENBL_OFF (0x002000)
#define PLIC_THRESHOLD_OFF (0x200000)

#ifndef PLAT_PLIC_CNTXT_PER_HART
#define PLAT_PLIC_CNTXT_PER_HART 2
#endif

#define PLIC_PLAT_CNTXT_NUM ((PLAT_PLIC_CNTXT_PER_HART) * (PLAT_CPU_NUM))

struct plic_global_hw {
    uint32_t prio[PLIC_NUM_PRIO_REGS];
    uint32_t pend[PLIC_NUM_PEND_REGS];
    uint32_t enbl[PLIC_PLAT_CNTXT_NUM][PLIC_NUM_ENBL_REGS];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct plic_hart_hw {
    uint32_t threshold;
    union {
        uint32_t claim;
        uint32_t complete;
    };
    uint8_t res[0x1000 - 0x0008];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

extern volatile struct plic_global_hw *plic_global;
extern volatile struct plic_hart_hw *plic_hart;
extern size_t PLIC_IMPL_INTERRUPTS;

void plic_init();
void plic_cpu_init();
void plic_handle();
void plic_set_enbl(unsigned cntxt, irqid_t int_id, bool en);
bool plic_get_enbl(unsigned cntxt, irqid_t int_id);
void plic_set_prio(irqid_t int_id, uint32_t prio);
uint32_t plic_get_prio(irqid_t int_id);
void plic_set_threshold(unsigned cntxt, uint32_t threshold);
uint32_t plic_get_threshold(irqid_t int_id);
bool plic_get_pend(irqid_t int_id);

struct plic_cntxt {
    cpuid_t hart_id;
    enum { PRIV_M = 3, PRIV_S = 2, PRIV_U = 0 } mode;
};

int plic_plat_cntxt_to_id(struct plic_cntxt cntxt);
struct plic_cntxt plic_plat_id_to_cntxt(int id);

#endif /* __PLIC_H__ */
