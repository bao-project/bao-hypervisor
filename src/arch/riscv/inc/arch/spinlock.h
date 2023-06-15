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

static inline void spin_lock(spinlock_t* lock)
{
    uint32_t const INCR = 1;
    uint32_t ticket;
    uint32_t serving;

    asm volatile(
                /* Increment next ticket */
                 "amoadd.w.aqrl  %0, %3, %2 \n\t"
                 "1:\n\t"
                 "lw %1, %4 \n\t"
                 /* Acquire barrier */
                 "fence r , rw \n\t"
                 /* Spin on lock if not serving*/
                 "bne  %0, %1, 1b \n\t"
                 : "=&r"(ticket), "=&r"(serving), "+A"(lock->next)
                 : "r"(INCR), "A"(lock->ticket)
                 : "memory"
    );
}

static inline void spin_unlock(spinlock_t* lock)
{
    uint32_t update_lock = lock->ticket + 1;
    asm volatile("fence rw, rw\n\t"
                 "sw %1, %0 \n\t"
                :"=A"(lock->ticket)
                : "r"(update_lock)
                : "memory");
}

#endif /* __ARCH_SPINLOCK__ */
