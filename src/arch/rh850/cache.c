/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cache.h>
#include <fences.h>
#include <bit.h>
#include <platform.h>
#include <srs.h>

/* #pragma inline_asm cist */
/* static void cist(void) */
/* { */
/*     cist */
/* } */

/* #pragma inline_asm cild */
/* static void cild(void) */
/* { */
/*     cild */
/* } */

void cache_arch_enumerate(struct cache* dscrp)
{
    UNUSED_ARG(dscrp);
}

void cache_flush_range(vaddr_t base, size_t size)
{
    UNUSED_ARG(base);
    UNUSED_ARG(size);
    /* unsigned long lpn = (base & (1<<(11-1))) << 11; */
    /* set_ictagl(lpn | 1); */
    /* set_ictagh(base+size-1); */
}
