/**
 * Bao, a Lightweight Static Partitioning Hypervisor
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
#include <arch/gic.h>

#define IPI_CPU_MSG 1
#define MAX_INTERRUPTS GIC_MAX_INTERUPTS

#endif /* __ARCH_INTERRUPTS_H__ */
