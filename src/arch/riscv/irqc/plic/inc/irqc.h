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

#define IRQC_TIMR_INT_ID            (PLIC_MAX_INTERRUPTS + 1)
#define IRQC_SOFT_INT_ID            (PLIC_MAX_INTERRUPTS + 2)
#define IRQC_MAX_INTERRUPT_LINES    (IRQC_SOFT_INT_ID + 1)
#define IRQC_MAX_INTERRUPT_HANDLERS MAX_INTERRUPT_LINES
#define IRQC_MAX_GUEST_INTERRUPTS   MAX_INTERRUPT_LINES

#define HART_REG_OFF                PLIC_THRESHOLD_OFF
#define IRQC_HART_INST              PLIC_PLAT_CNTXT_NUM

static inline void irqc_init(void)
{
    plic_init();
}

static inline void irqc_cpu_init(void)
{
    plic_cpu_init();
}

static inline void irqc_config_irq(irqid_t int_id, bool en)
{
    plic_set_enbl(cpu()->arch.plic_cntxt, int_id, en);
    plic_set_prio(int_id, 0xFE);
}

static inline void irqc_handle(void)
{
    plic_handle();
}

static inline bool irqc_get_pend(irqid_t int_id)
{
    return plic_get_pend(int_id);
}

static inline void irqc_clr_pend(irqid_t int_id)
{
    UNUSED_ARG(int_id);

    WARNING("trying to clear external interrupt");
}

static inline void virqc_set_hw(struct vm* vm, irqid_t id)
{
    vplic_set_hw(vm, id);
}

#endif // IRQC_H
