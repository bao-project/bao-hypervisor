/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __INTC_H__
#define __INTC_H__

#include <bao.h>

#define INTC_PRIVATE_IRQS_NUM 32

#define INTC_MAX_PRIO         0x0

struct intc1_unit {
    uint16_t EIC[INTC_PRIVATE_IRQS_NUM];
    uint8_t pad0[0xF0 - 0x40];
    uint32_t IMR;
    uint8_t pad1[0x100 - 0xF4];
    uint32_t EIBD[INTC_PRIVATE_IRQS_NUM];
    uint8_t pad2[0x1C0 - 0x180];
    uint32_t FIBD;
    uint8_t pad3[0x200 - 0x1C4];
    uint32_t EEIC[INTC_PRIVATE_IRQS_NUM];
    uint32_t EIBG;
    uint8_t pad4[0x2C0 - 0x284];
    uint32_t FIBG;
    uint8_t pad5[0x2F0 - 0x2C4];
    uint32_t IHVCFG;
    uint8_t pad6[0x4000 - 0x2F4];
};

struct intc1 {
    struct intc1_unit self;
    struct intc1_unit pe[PLAT_CPU_NUM];
};

#define INTC2_IRQ_NUM    (ARCH_MAX_INTERRUPTS - INTC_PRIVATE_IRQS_NUM)
#define INTC2_IMR_NUM    ((ARCH_MAX_INTERRUPTS + 31) / 32 - 1)
#define INTC2_I2EIBG_OFF (0x1FE0)
#define INTC2_EIBD_OFF   (0x2000)
#define PAD3_LEN         ((INTC2_EIBD_OFF - INTC2_I2EIBG_OFF) - (PLAT_CPU_NUM * 4) + 0x80)

struct intc2 {
    uint8_t PAD0[64];              /* 0x0000 - 0x003F */
    uint16_t EIC[INTC2_IRQ_NUM];   /* 0x0040 - 0x0FFF */
    uint8_t PAD1[4];               /* 0x1000 - 0x1003 */
    uint32_t IMR[INTC2_IMR_NUM];   /* 0x1004 - 0x10FF */
    uint8_t PAD2[3808];            /* 0x1100 - 0x1FDF */
    uint32_t I2EIBG[PLAT_CPU_NUM]; /* 0x1FE0 - (0x1FE0 + 4*cpu_num - 1) */
    uint8_t PAD3[PAD3_LEN];        /* (0x1FE0 + 4*cpu_num) - 0x203F */
    uint32_t EIBD[INTC2_IRQ_NUM];  /* 0x2080 - 0x3FFF */
    uint8_t PAD4[128];             /* 0x4000 - 0x407F */
    uint32_t EEIC[INTC2_IRQ_NUM];  /* 0x4080 - 0x5FFF */
};

struct intif {
    uint32_t PINT[8];
    uint32_t PINTCLR[8];
    uint32_t PAD[112];
    uint32_t TPTMSEL;
};

struct eint {
    uint8_t sintr[PLAT_CPU_NUM];
};

struct fenc {
    uint64_t FENMIF;
    uint32_t FENMIC;
};

struct feinc {
    uint32_t FEINTF;
    uint32_t FEINTFMSK;
    uint32_t FEINTC;
};

void intc_init(void);
void intc_map_mmio(void);

void intc_set_trgt(irqid_t int_id, cpuid_t cpu_id);
void intc_set_enable(irqid_t int_id, bool en);
void intc_set_prio(irqid_t int_id, unsigned long prio);

void intc_vm_assign(struct vm* vm, irqid_t int_id);
void intc_hyp_assign(irqid_t int_id);

void intc_set_pend(irqid_t int_id, bool en);
bool intc_get_pend(irqid_t int_id);

#endif /* INTC_H */
