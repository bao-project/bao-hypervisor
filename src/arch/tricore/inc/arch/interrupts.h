/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>

#define ARCH_MAX_INTERRUPTS    (2048)

#define MAX_GUEST_INTERRUPTS   (ARCH_MAX_INTERRUPTS)
#define MAX_INTERRUPT_LINES    (ARCH_MAX_INTERRUPTS)
#define MAX_INTERRUPT_HANDLERS (ARCH_MAX_INTERRUPTS)

void interrupts_arch_handle(void);
void ir_init_ipi(void);

static inline bool interrupts_arch_irq_is_forwardable(irqid_t int_id)
{
    UNUSED_ARG(int_id);

    /**
     * In TC4 interrupts are assigned directly to the guests. The
     * hypervisor doesn't attend those IRQs.
     */

    return false;
}

#endif /* __ARCH_INTERRUPTS_H__ */
