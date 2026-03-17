/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file objpool.c
 * @brief This source files implements the management of object pools.
 * 
 */

#include <objpool.h>
#include <string.h>

/**
 * @brief Initialize an object pool
 *
 * Clear out the object pool memory and its allocation bitmap,
 * and initialize the pool's spinlock.
 *
 * @param objpool Pointer to object pool structure to initialize
 * @see memset(), BITMAP_SIZE_IN_BYTES, SPINLOCK_INITVAL, objpool
 * 
 */
void objpool_init(struct objpool* objpool)
{
    memset(objpool->pool, 0, objpool->objsize * objpool->num);
    memset(objpool->bitmap, 0, BITMAP_SIZE_IN_BYTES(objpool->num));
    objpool->lock = SPINLOCK_INITVAL;
}

/**
 * @brief Allocate an object from a pool and return its ID
 *
 * Finds a free slot in the pool's bitmap, marks it as allocated,
 * and returns both the object pointer and optionally its ID.
 *
 * @param objpool Pointer to the object pool
 * @param id Optional pointer to receive the object's ID
 * @return void* Pointer to the allocated object, or NULL if pool is full
 * @see objpool, objpool_id_t, spin_lock()/spin_unlock(),
 * @see bitmap_find_nth(), bitmap_set()
 * 
 */
void* objpool_alloc_with_id(struct objpool* objpool, objpool_id_t* id)
{
    void* obj = NULL;
    spin_lock(&objpool->lock);
    ssize_t n = bitmap_find_nth(objpool->bitmap, objpool->num, 1, 0, BITMAP_NOT_SET);
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

/**
 * @brief Allocate an object from a pool
 *
 * Convenience wrapper around objpool_alloc_with_id() that doesn't
 * return the object's ID.
 *
 * @param objpool Pointer to the object pool
 * @return void* Pointer to the allocated object, or NULL if pool is full
 * @see objpool_alloc_with_id()
 */
void* objpool_alloc(struct objpool* objpool)
{
    return objpool_alloc_with_id(objpool, NULL);
}

/**
 * @brief Free an object back to its pool
 *
 * Returns an object to the pool by clearing its bitmap bit.
 * Validates that the object belongs to the pool and is properly aligned before
 * freeing.
 *
 * @param objpool Pointer to the object pool
 * @param obj Pointer to the object to free
 * @see in_range(), IS_ALIGNED, spin_lock(), spin_unlock(), bitmap_clear(), WARNING()
 * @see vaddr_t, objpool, spinlock_t, bitmap_t
 * 
 */
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
        WARNING("leaked while trying to free stray object\n");
    }
}
