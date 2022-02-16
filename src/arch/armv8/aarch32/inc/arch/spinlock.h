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
    /* TBD */
}

static inline void spin_unlock(spinlock_t* lock)
{
    /* TBD */
}

#endif /* __ARCH_SPINLOCK__ */
