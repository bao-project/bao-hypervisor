/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
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
    spinlock_t const ONE = 1;
    spinlock_t tmp;

    asm volatile(
        "1:\n\t"
        "ldaxr %w0, %1 \n\t"
        "cbnz %w0, 1b \n\t"
        "stxr %w0, %w2, %1 \n\t"
        "cbnz %w0, 1b \n\t"
        : "=&r"(tmp), "+Q"(*lock)
        : "r"(ONE) : "memory");
}

static inline void spin_unlock(spinlock_t* lock)
{
    asm volatile("stlr wzr, %0\n\t" ::"Q"(*lock) : "memory");
}

#endif /* __ARCH_SPINLOCK__ */
