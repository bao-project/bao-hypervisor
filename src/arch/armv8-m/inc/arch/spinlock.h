/**
 * baohu separation kernel
 *
 * Copyright (c) Jose Martins, Sandro Pinto
 *
 * Authors:
 *      Jose Martins <josemartins90@gmail.com>
 *
 * baohu is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __ARCH_SPINLOCK__
#define __ARCH_SPINLOCK__

typedef struct {
    uint32_t spinlock_t;
} spinlock_t;

static const spinlock_t SPINLOCK_INITVAL = { 0 };

/*static inline unsigned int cmpAndSwap (unsigned int volatile *address,
           unsigned int value, unsigned int condition)
{
  unsigned long long reg64;

  __asm__ volatile (
    "mov        %A[reg], %[cond], %[val]\n\t"
    "cmpswap.w [%[addr]]0, %A[reg]" :
    [reg] "=d" (reg64) :
    [addr] "a" (address),
    [cond] "d" (condition),
    [val] "d" (value) :
    "memory");
  return reg64;
}*/

/* TODO: ticket lock */
static inline void spin_lock(spinlock_t* lock)
{
    volatile long unsigned spinLockVal;

    bool retVal = false;

    do {
        spinLockVal = 1UL;
        // spinLockVal = cmpAndSwap(((unsigned int volatile *)lock), spinLockVal, 0);
        UNUSED_ARG(lock);

        /* Check if the SpinLock WAS set before the attempt to acquire spinlock */
        if (spinLockVal == false) {
            retVal = true;
        }
    } while (retVal == false);
}

static inline void spin_unlock(spinlock_t* lock)
{
    *lock = SPINLOCK_INITVAL;
}

#endif /* __ARCH_SPINLOCK__ */
