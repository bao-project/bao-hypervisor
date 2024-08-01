/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */
#ifndef __FENCES_ARCH_H__
#define __FENCES_ARCH_H__

static inline void fence_ord_write()
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

static inline void fence_ord_read()
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

static inline void fence_ord()
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

static inline void fence_sync_write()
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

static inline void fence_sync_read()
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

static inline void fence_sync()
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

#endif /* __FENCES_ARCH_H__ */
