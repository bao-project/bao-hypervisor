/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef IRQC_H
#define IRQC_H

#include <bao.h>
#include <plic.h>
#include <cpu.h>
#include <vplic.h>

#define IRQC_MAX_INTERRUPTS (PLIC_MAX_INTERRUPTS)

#define HART_REG_OFF        PLIC_THRESHOLD_OFF
#define IRQC_HART_INST      PLIC_PLAT_CNTXT_NUM

static inline void irqc_init()
{
    plic_init();
}

static inline void irqc_cpu_init()
{
    plic_cpu_init();
}

static inline void irqc_config_irq(irqid_t int_id, bool en)
{
    plic_set_enbl(cpu()->arch.plic_cntxt, int_id, en);
    plic_set_prio(int_id, 0xFE);
}

static inline void irqc_handle()
{
    plic_handle();
}

static inline bool irqc_get_pend(irqid_t int_id)
{
    return plic_get_pend(int_id);
}

static inline void irqc_clr_pend(irqid_t int_id)
{
    WARNING("trying to clear external interrupt");
}

static inline void virqc_set_hw(struct vm* vm, irqid_t id)
{
    vplic_set_hw(vm, id);
}

#endif // IRQC_H
