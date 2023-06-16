/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SPINLOCK__
#define __ARCH_SPINLOCK__

#include <bao.h>

typedef struct {
    uint32_t ticket;
    uint32_t next;
} spinlock_t;

#define SPINLOCK_INITVAL ((spinlock_t){0,0})

static inline void spinlock_init(spinlock_t* lock)
{
    lock->ticket = 0;
    lock->next = 0;
}

/**
 * This lock follows the ticket lock algorithm described in Arm's ARM DDI0487I.a
 * Appendix K13.
 */

static inline void spin_lock(spinlock_t* lock)
{
    uint32_t ticket;
    uint32_t next;
    uint32_t temp;

    (void)lock;
    __asm__ volatile(
        /* Get ticket */
        "1:\n\t"
        "ldaxr  %w0, %3\n\t"
        "add    %w1, %w0, 1\n\t"
        "stxr   %w2, %w1, %3\n\t"
        "cbnz   %w2, 1b\n\t"
        /* Wait for your turn */
        "2:\n\t"
        "ldar   %w1, %4\n\t"
        "cmp    %w0, %w1\n\t"
        "b.eq   3f\n\t"
        "wfe\n\t"
        "b 2b\n\t"
        "3:\n\t"
        : "=&r"(ticket), "=&r"(next), "=&r"(temp)
        : "Q"(lock->ticket), "Q"(lock->next));
}

static inline void spin_unlock(spinlock_t* lock)
{
    uint32_t temp;

    __asm__ volatile(
        /* increment to next ticket */
        "ldr    %w0, %1\n\t"
        "add    %w0, %w0, 1\n\t"
        "stlr   %w0, %1\n\t"
        "dsb ish\n\t"
        "sev\n\t"
        : "=&r"(temp)
        : "Q"(lock->next));
}


#endif /* __ARCH_SPINLOCK__ */
