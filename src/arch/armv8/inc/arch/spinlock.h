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

/**
 * TODO: this is a naive implementation to get things going.
 * Optimizations needed. See ticket locks in ARMv8-A.
 */

#ifndef __ARCH_SPINLOCK__
#define __ARCH_SPINLOCK__

#include <bao.h>

typedef volatile uint32_t spinlock_t;

#define SPINLOCK_INITVAL (0)

static inline void spin_lock(spinlock_t* lock)
{
    uint32_t const ONE = 1;
    spinlock_t tmp;

    asm volatile(
        "1:\n\t"
        "ldaxr %w0, %1 \n\t"
        "cbnz %w0, 1b \n\t"
        "stxr %w0, %w2, %1 \n\t"
        "cbnz %w0, 1b \n\t"
        : "=&r"(tmp), "+Q"(*lock)
        : "r"(ONE));
}

static inline void spin_unlock(spinlock_t* lock)
{
    asm volatile("stlr wzr, %0\n\t" ::"Q"(*lock));
}

#endif /* __ARCH_SPINLOCK__ */