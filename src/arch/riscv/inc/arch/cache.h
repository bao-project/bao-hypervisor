/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CACHE_H__
#define __ARCH_CACHE_H__

#include <bao.h>

#define CACHE_MAX_LVL 8 // Does this make sense in all architectures?
/*
 * Cache block size:
 * - 64B guaranteed if Zic64b is implemented
 * - otherwise assumed as a safe value due to lack of standard discovery
 */
#define CACHE_BLOCK_SIZE 64UL

static inline void cbo_clean(uintptr_t base_addr)
{
    __asm__ volatile("cbo.clean 0(%0) \n\t" :: "r"(base_addr) : "memory");
}

static inline void cbo_flush(uintptr_t base_addr)
{
    __asm__ volatile("cbo.flush 0(%0) \n\t" :: "r"(base_addr) : "memory");
}

static inline void cbo_invalidate(uintptr_t base_addr)
{
    __asm__ volatile("cbo.inval 0(%0) \n\t" :: "r"(base_addr) : "memory");
}

#endif                  /* __ARCH_CACHE_H__ */
