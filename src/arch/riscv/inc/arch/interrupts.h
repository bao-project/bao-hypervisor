/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>
#include <irqc.h>

#define PLIC                   (1)
#define APLIC                  (2)

#define ACLINT_PRESENT()       DEFINED(ACLINT_SSWI)

#define SOFT_INT_ID            (IRQC_SOFT_INT_ID)
#define TIMR_INT_ID            (IRQC_TIMR_INT_ID)
#define MAX_INTERRUPT_LINES    (IRQC_MAX_INTERRUPT_LINES)
#define MAX_INTERRUPT_HANDLERS (IRQC_MAX_INTERRUPT_HANDLERS)
#define MAX_GUEST_INTERRUPTS   (IRQC_MAX_GUEST_INTERRUPTS)

#define IPI_CPU_MSG            SOFT_INT_ID

extern irqid_t irqc_timer_int_id;

void interrupts_arch_handle(void);

#endif /* __ARCH_INTERRUPTS_H__ */
