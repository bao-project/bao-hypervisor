/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SPINLOCK__
#define __ARCH_SPINLOCK__

#include <bao.h>

typedef volatile uint32_t __attribute__((aligned(4))) spinlock_t;

#define SPINLOCK_INITVAL (0)

static inline void spin_lock(spinlock_t* lock)
{
    spinlock_t const ONE = 1;
    spinlock_t tmp = SPINLOCK_INITVAL;

    asm volatile("1:\n\t"
                 "lr.w.aq  %0, %1 \n\t"
                 "bne      %0, zero, 1b \n\t"
                 "sc.w.rl  %0, %2, %1 \n\t"
                 "bne      %0, zero, 1b \n\t"
                 : "=&r"(tmp), "+A"(*lock)
                 : "r"(ONE) : "memory");
}

static inline void spin_unlock(spinlock_t* lock)
{
    asm volatile("sw zero, %0\n\t"
                 "fence rw, rw\n\t"  // Is the full blown barrier really needed?
                 ::"m"(*lock) : "memory");
}

#endif /* __ARCH_SPINLOCK__ */
