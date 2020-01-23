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

#ifndef __VPLIC_H__
#define __VPLIC_H__

#include <bao.h>
#include <arch/plic.h>
#include <arch/spinlock.h>
#include <bitmap.h>

typedef struct {
    spinlock_t lock;
    BITMAP_ALLOC(pend, PLIC_MAX_INTERRUPTS);
} vplic_t;

typedef struct vm vm_t;
void vplic_init(vm_t *vm, uintptr_t vplic_base);
void vplic_inject(vplic_t *vplic, int id);

#endif /* __VPLIC_H__ */