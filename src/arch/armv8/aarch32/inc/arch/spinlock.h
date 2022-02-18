/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */


#ifndef __ARCH_SPINLOCK__
#define __ARCH_SPINLOCK__

#include <bao.h>

typedef volatile uint32_t spinlock_t;

#define SPINLOCK_INITVAL (0)

static inline void spin_lock(spinlock_t* lock)
{
    spinlock_t const ONE = 1;
    spinlock_t tmp;

    asm volatile(
        "1:\n\t"
        "ldaex %r0, %1 \n\t"
        "cmp %r0, #0 \n\t"
        "strexeq %r0, %r2, %1 \n\t"
        "cmpeq %r0, #0 \n\t"
        "bne 1b \n\t"
        : "=&r"(tmp), "+Q"(*lock)
        : "r"(ONE));
}

static inline void spin_unlock(spinlock_t* lock)
{
    spinlock_t const ZERO = 0;
    asm volatile("stl %r0, %1\n\t" ::"r"(ZERO), "Q"(*lock));
}

#endif /* __ARCH_SPINLOCK__ */
