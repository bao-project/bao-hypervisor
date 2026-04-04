/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SPINLOCK__
#define __ARCH_SPINLOCK__

typedef struct {
    uint32_t spinlock_t;
} spinlock_t;

static const spinlock_t SPINLOCK_INITVAL = { 0 };

static inline unsigned int cmpAndSwap(unsigned int volatile* address, unsigned int value,
    unsigned int condition)
{
    unsigned long long reg64;

    __asm__ volatile("mov        %A[reg], %[cond], %[val]\n\t"
                     "cmpswap.w [%[addr]]0, %A[reg]" : [reg] "=d"(reg64)
                     : [addr] "a"(address), [cond] "d"(condition), [val] "d"(value) : "memory");
    __asm__ volatile("isync");
    return (unsigned long)reg64;
}

static inline void spin_lock(spinlock_t* lock)
{
    volatile long unsigned spinLockVal;

    bool retVal = false;

    do {
        spinLockVal = 1UL;
        spinLockVal = cmpAndSwap(((unsigned int volatile*)lock), spinLockVal, 0);

        /* Check if the SpinLock WAS set before the attempt to acquire spinlock */
        if (spinLockVal == false) {
            retVal = true;
        }
    } while (retVal == false);
}

static inline void spin_unlock(spinlock_t* lock)
{
    __asm__ volatile("dsync\n\t"         /* Ensure all previous memory ops complete */
                     "st.w [%0], %1\n\t" /* Store 0 to release lock */
                     : : "a"(lock), "d"(0) : "memory");
}

#endif /* __ARCH_SPINLOCK__ */
