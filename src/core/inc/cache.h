/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CACHE_H__
#define __CACHE_H__

#include <bao.h>
#include <arch/cache.h>

struct cache {
    size_t lvls;
    size_t min_shared_lvl;
    enum { UNIFIED, SEPARATE, DATA, INSTRUCTION } type[CACHE_MAX_LVL];
    enum { PIPT, VIPT } indexed[CACHE_MAX_LVL][2];
    size_t line_size[CACHE_MAX_LVL][2];
    size_t assoc[CACHE_MAX_LVL][2];
    size_t numset[CACHE_MAX_LVL][2];
};

extern size_t COLOR_NUM;
extern size_t COLOR_SIZE;

void cache_enumerate();
void cache_flush_range(vaddr_t base, size_t size);

void cache_arch_enumerate(struct cache* dscrp);

#endif /* __CACHE_H__ */
