/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SPINLOCK_H__
#define __ARCH_SPINLOCK_H__

#include <bao.h>
#include <util.h>

#define SPINLOCK_INITVAL 0

typedef uint32_t spinlock_t;

static inline void spin_lock(spinlock_t* lock)
{
    __asm__ volatile("1:\n\t"
                     "    ldl.w  [%0], r19      \n\t"
                     "    cmp    r0, r19        \n\t"
                     "    bnz    2f             \n\t"
                     "    mov    1, r19         \n\t"
                     "    stc.w  r19, [%0]      \n\t"
                     "    cmp    r0, r19        \n\t"
                     "    bnz    3f             \n\t"
                     "2:\n\t"
                     "    snooze                \n\t"
                     "    br     1b             \n\t"
                     "3:\n\t" : : "r"(lock) : "r19", "memory");
}

static inline void spin_unlock(spinlock_t* lock)
{
    __asm__ volatile("st.w r0, 0[%0]\n\t" : : "r"(lock) : "memory");
}

#endif /* __ARCH_SPINLOCK_H__ */
