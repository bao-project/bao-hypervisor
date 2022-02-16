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

#ifndef __ARCH_MEM_H__
#define __ARCH_MEM_H__

#include <bao.h>

#define PTE_INVALID (0)
#define PTE_HYP_FLAGS (0)
#define PTE_HYP_DEV_FLAGS PTE_HYP_FLAGS

#define PTE_VM_FLAGS (0)
#define PTE_VM_DEV_FLAGS PTE_VM_FLAGS

#endif /* __ARCH_MEM_H__ */
