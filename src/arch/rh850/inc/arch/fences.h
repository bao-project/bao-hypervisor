/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_FENCES_H__
#define __ARCH_FENCES_H__

#include <bao.h>

static inline void syncp(void)
{
    __asm__ volatile("syncp" ::: "memory");
}

static inline void syncm(void)
{
    __asm__ volatile("syncm" ::: "memory");
}

static inline void synci(void)
{
    __asm__ volatile("synci" ::: "memory");
}

static inline void synce(void)
{
    __asm__ volatile("synce" ::: "memory");
}

static inline void fence_ord_write(void)
{
    syncm();
}

static inline void fence_ord_read(void)
{
    syncp();
}

static inline void fence_ord(void)
{
    syncm();
}

static inline void fence_sync_write(void)
{
    syncm();
}

static inline void fence_sync_read(void)
{
    syncp();
}

static inline void fence_sync(void)
{
    syncm();
}

#endif /* __ARCH_FENCES_H__ */
