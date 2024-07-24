/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __FENCES_ARCH_H__
#define __FENCES_ARCH_H__

#include <bao.h>

#define DMB(shdmn) __asm__ volatile("dmb " XSTR(shdmn) "\n\t" ::: "memory")

#define DSB(shdmn) __asm__ volatile("dsb " XSTR(shdmn) "\n\t" ::: "memory")

#define ISB()      __asm__ volatile("isb\n\t" ::: "memory")

static inline void fence_ord_write(void)
{
    DMB(ishst);
}

static inline void fence_ord_read(void)
{
    DMB(ishld);
}

static inline void fence_ord(void)
{
    DMB(ish);
}

static inline void fence_sync_write(void)
{
    DSB(ishst);
}

static inline void fence_sync_read(void)
{
    DSB(ishld);
}

static inline void fence_sync(void)
{
    DSB(ish);
}

#endif /* __FENCES_ARCH_H__ */
