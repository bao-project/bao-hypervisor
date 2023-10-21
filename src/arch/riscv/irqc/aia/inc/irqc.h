
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef IRQC_H
#define IRQC_H

#include <aplic.h>
#include <cpu.h>
#include <vaplic.h>

#define IRQC_MAX_INTERRUPTS  (APLIC_MAX_INTERRUPTS)

#define HART_REG_OFF         APLIC_IDC_OFF
#define IRQC_HART_INST       APLIC_DOMAIN_NUM_HARTS
#define HYP_IRQ_SM_EDGE_RISE APLIC_SOURCECFG_SM_EDGE_RISE
#define HYP_IRQ_SM_INACTIVE  APLIC_SOURCECFG_SM_INACTIVE
#define HYP_IRQ_PRIO         APLIC_TARGET_MAX_PRIO

static inline void irqc_init()
{
    aplic_init();
}

static inline void irqc_cpu_init()
{
    aplic_idc_init();
}

static inline void irqc_config_irq(irqid_t int_id, bool en)
{
    if (en) {
        aplic_set_sourcecfg(int_id, HYP_IRQ_SM_EDGE_RISE);
        aplic_set_enbl(int_id);
        aplic_set_target_hart(int_id, cpu()->id);
        aplic_set_target_prio(int_id, HYP_IRQ_PRIO);
    } else {
        aplic_clr_enbl(int_id);
    }
}

static inline void irqc_handle()
{
    aplic_handle();
}

static inline bool irqc_get_pend(irqid_t int_id)
{
    return aplic_get_pend(int_id);
}

static inline void irqc_clr_pend(irqid_t int_id)
{
    aplic_clr_pend(int_id);
}

static inline void virqc_set_hw(struct vm* vm, irqid_t id)
{
    vaplic_set_hw(vm, id);
}

#endif // IRQC_H
