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
#include <arch/sbi.h>

static inline void irqc_init(void)
{
    plic_init();
}

static inline irqid_t irqc_reserve(irqid_t pintp_id)
{
    return pintp_id;
}

static inline void irqc_send_ipi(cpuid_t target_cpu)
{
    sbi_send_ipi(1UL << target_cpu, 0);
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

    WARNING("trying to clear external interrupt\n");
}

static inline void virqc_set_hw(struct vm* vm, irqid_t id)
{
    vplic_set_hw(vm, id);
}

#endif // IRQC_H
