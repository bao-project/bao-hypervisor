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

#ifndef __FENCES_ARCH_H__
#define __FENCES_ARCH_H__

#define DMB(shdmn) asm volatile("dmb " #shdmn "\n\t" ::: "memory")

#define DSB(shdmn) asm volatile("dsb " #shdmn "\n\t" ::: "memory")

#define ISB() asm volatile("isb\n\t" ::: "memory")

static inline void fence_ord_write()
{
    DMB(ishst);
}

static inline void fence_ord_read()
{
    DMB(ishld);
}

static inline void fence_ord()
{
    DMB(ish);
}

static inline void fence_sync_write()
{
    DSB(ishst);
}

static inline void fence_sync_read()
{
    DSB(ishld);
}

static inline void fence_sync()
{
    DSB(ish);
}

#endif /* __FENCES_ARCH_H__ */