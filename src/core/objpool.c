/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <objpool.h>
#include <string.h>

void objpool_init(struct objpool* objpool)
{
    memset(objpool->pool, 0, objpool->objsize * objpool->num);
    memset(objpool->bitmap, 0, BITMAP_SIZE_IN_BYTES(objpool->num));
    objpool->lock = SPINLOCK_INITVAL;
}

void* objpool_alloc_with_id(struct objpool* objpool, objpool_id_t* id)
{
    void* obj = NULL;
    spin_lock(&objpool->lock);
    ssize_t n = bitmap_find_nth(objpool->bitmap, objpool->num, 1, 0, false);
    if (n >= 0) {
        bitmap_set(objpool->bitmap, (size_t)n);
        obj = (void*)((uintptr_t)objpool->pool + (objpool->objsize * (size_t)n));
    }
    if (id != NULL) {
        *id = (objpool_id_t)n;
    }
    spin_unlock(&objpool->lock);
    return obj;
}

void* objpool_alloc(struct objpool* objpool)
{
    return objpool_alloc_with_id(objpool, NULL);
}

void objpool_free(struct objpool* objpool, void* obj)
{
    vaddr_t obj_addr = (vaddr_t)obj;
    vaddr_t pool_addr = (vaddr_t)objpool->pool;
    bool in_pool = in_range(obj_addr, pool_addr, objpool->objsize * objpool->num);
    bool aligned = IS_ALIGNED(obj_addr - pool_addr, objpool->objsize);
    if (in_pool && aligned) {
        size_t n = (obj_addr - pool_addr) / objpool->objsize;
        spin_lock(&objpool->lock);
        bitmap_clear(objpool->bitmap, n);
        spin_unlock(&objpool->lock);
    } else {
        WARNING("leaked while trying to free stray object");
    }
}
