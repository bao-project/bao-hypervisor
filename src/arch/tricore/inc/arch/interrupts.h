/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>

#define ARCH_MAX_INTERRUPTS    2048
#define MAX_INTERRUPTS         ARCH_MAX_INTERRUPTS

#define MAX_GUEST_INTERRUPTS   (MAX_INTERRUPTS)
#define MAX_INTERRUPT_LINES    MAX_INTERRUPTS
#define MAX_INTERRUPT_HANDLERS MAX_INTERRUPTS

/* TODO platform dependent */
#define IPI_CPU_MSG            (0x1460 / 4) /* TODO this is the first GPSR in TC49 */
#define GSPR_SRC_BASE          (0x1460 / 4) /* TODO this is the first GPSR in TC49 */

void interrupts_arch_handle(void);
void ir_init_ipi(void);

#endif /* __ARCH_INTERRUPTS_H__ */
