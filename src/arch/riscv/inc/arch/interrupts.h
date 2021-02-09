/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>
#include <arch/plic.h>

/**
 * In riscv, the ipi (software interrupt) and timer interrupts dont actually
 * have an ID as their are treated differently from external interrupts
 * routed by the external interrupt controller, the PLIC.
 * Will define their ids as the ids after the maximum possible in the PLIC.
 */
#define SOFT_INT_ID (PLIC_MAX_INTERRUPTS + 1)
#define TIMR_INT_ID (PLIC_MAX_INTERRUPTS + 2)
#define MAX_INTERRUPTS (TIMR_INT_ID + 1)

#define IPI_CPU_MSG SOFT_INT_ID

#endif /* __ARCH_INTERRUPTS_H__ */
