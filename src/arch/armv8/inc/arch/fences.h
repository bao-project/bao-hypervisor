/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __FENCES_ARCH_H__
#define __FENCES_ARCH_H__

#include <bao.h>

#define DMB(shdmn) asm volatile("dmb " XSTR(shdmn) "\n\t" ::: "memory")

#define DSB(shdmn) asm volatile("dsb " XSTR(shdmn) "\n\t" ::: "memory")

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
