/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>

#define MAX_INTERRUPTS 2048 // TODO PLAT_IR_MAX_INTERUPTS

/* TODO platform dependent */
#define IPI_CPU_MSG      1332 /* TODO this is the first GPSR in TC49 */

void interrupts_arch_handle(void);

#endif /* __ARCH_INTERRUPTS_H__ */
