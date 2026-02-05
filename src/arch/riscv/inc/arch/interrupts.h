/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>
#include <irqc.h>

#define ACLINT_PRESENT()       DEFINED(ACLINT_SSWI)

#define SOFT_INT_ID            (IRQC_SOFT_INT_ID)
#define TIMR_INT_ID            (IRQC_TIMR_INT_ID)
#define MAX_INTERRUPT_LINES    (IRQC_MAX_INTERRUPT_LINES)
#define MAX_INTERRUPT_HANDLERS (IRQC_MAX_INTERRUPT_HANDLERS)
#define MAX_GUEST_INTERRUPTS   (IRQC_MAX_GUEST_INTERRUPTS)

#define IPI_CPU_MSG            SOFT_INT_ID

extern irqid_t irqc_timer_int_id;

void interrupts_arch_handle(void);

static inline bool interrupts_arch_irq_is_forwardable(irqid_t int_id)
{
    UNUSED_ARG(int_id);

    /**
     * Under full AIA support, interrupts delivered to HS mode are always
     * reserved for the hypervisor. Guest-directed interrupts are forwarded to
     * the guest interrupt files and do not arrive at the hypervisor handler. Any
     * guest-related interrupt trapping is signaled via the dedicated
     * "Supervisor guest external interrupt" id which can be handled by the
     * hypervisor in the future.
     *
     * Only for PLIC and APLIC-only systems interrupts need to be re-directed
     * to guests.
     */

    return IRQC != AIA;
}

#endif /* __ARCH_INTERRUPTS_H__ */
