/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */
#ifndef __FENCES_ARCH_H__
#define __FENCES_ARCH_H__

static inline void fence_ord_write(void)
{
    __asm__ volatile("dsync\n\t" ::: "memory");
}

static inline void fence_ord_read(void)
{
    __asm__ volatile("dsync\n\t" ::: "memory");
}

static inline void fence_ord(void)
{
    __asm__ volatile("dsync\n\t" ::: "memory");
}

static inline void fence_sync_write(void)
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

static inline void fence_sync_read(void)
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

static inline void fence_sync(void)
{
    __asm__ volatile("isync\n\t" ::: "memory");
}

#endif /* __FENCES_ARCH_H__ */
