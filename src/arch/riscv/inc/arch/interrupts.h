/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>
#include <irqc.h>

#define ACLINT_PRESENT() DEFINED(ACLINT_SSWI)

#define SOFT_INT_ID     (IRQC_SOFT_INT_ID)
#define TIMR_INT_ID     (IRQC_TIMR_INT_ID)
#define MAX_INTERRUPTS  (IRQC_MAX_INTERRUPTS)

#define IPI_CPU_MSG      SOFT_INT_ID

#endif /* __ARCH_INTERRUPTS_H__ */
