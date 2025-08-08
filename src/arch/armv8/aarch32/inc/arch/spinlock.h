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

static const spinlock_t SPINLOCK_INITVAL = { 0, 0 };

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
        "ldaex  %0, %3\n\t"
        "add    %1, %0, #1\n\t"
        "strex  %2, %1, %3\n\t"
        "cmp  %2, #0\n\t"
        "bne 1b \n\t"
        /* Wait for your turn */
        "2:\n\t"
        "ldr    %1, %4\n\t"
        "cmp    %0, %1\n\t"
        "beq   3f\n\t"
        "wfe \n\t"
        "b 2b\n\t"
        "3:\n\t" : "=&r"(ticket), "=&r"(next), "=&r"(temp) : "Q"(lock->ticket), "Q"(lock->next)
        : "memory");
}

static inline void spin_unlock(spinlock_t* lock)
{
    uint32_t temp;

    __asm__ volatile(
        /* increment to next ticket */
        "ldr    %0, %1\n\t"
        "add    %0, %0, #1\n\t"
        "stl    %0, %1\n\t"
        "dsb ish\n\t"
        "sev\n\t" : "=&r"(temp) : "Q"(lock->next) : "memory");
}

#endif /* __ARCH_SPINLOCK__ */
