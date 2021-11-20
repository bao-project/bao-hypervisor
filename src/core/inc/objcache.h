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

#ifndef __OBJCACHE_H__
#define __OBJCACHE_H__

#include <bao.h>
#include <mem.h>
#include <list.h>
#include <spinlock.h>

#define SLAB_SIZE PAGE_SIZE
#define SLAB_MIN_HEADER_SIZE (32)
#define SLAB_MAX_OBJECT_SIZE (PAGE_SIZE / 4)

struct objcache;
union slab;

struct objcache {
    size_t osize;
    struct list slabs;
    union slab* last_free;
    spinlock_t lock;
    enum AS_SEC section;
};

void objcache_init(struct objcache* oc, size_t osize, enum AS_SEC sec, bool prime);
void* objcache_alloc();
bool objcache_free(struct objcache* oc, void* obj);

#endif /* __OBJCACHE_H__ */
