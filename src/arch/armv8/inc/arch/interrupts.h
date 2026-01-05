/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>

#define IPI_CPU_MSG            1
#define MAX_INTERRUPT_LINES    GIC_MAX_INTERUPTS
#define MAX_INTERRUPT_HANDLERS GIC_MAX_INTERUPTS
#define MAX_GUEST_INTERRUPTS   GIC_MAX_INTERUPTS

static inline bool interrupts_arch_irq_is_forwardable(irqid_t int_id)
{
    UNUSED_ARG(int_id);

    /**
     * In Arm GIC systems all interrupts must be trapped and considered
     * to be forwarded to guests.
     */

    return true;
}

#endif /* __ARCH_INTERRUPTS_H__ */
