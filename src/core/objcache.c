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

#include <objcache.h>
#include <string.h>

typedef union slab {
    union {
        struct {
            node_t next;
            list_t free;
            size_t objsize;
            size_t objnum;
            size_t objcount;
            struct objcache* cache;
        };
        uint8_t fill[SLAB_MIN_HEADER_SIZE];
    } header;

    uint8_t slab[SLAB_SIZE];

} slab_t;

// TODO
// static size_t std_objcache_sizes[] = {32, 64, 128, 256, 512, 1024};
// static objcache_t
// std_objcache_list[sizeof(std_objcache_sizes)/sizeof(size_t)];

static slab_t* slab_create(objcache_t* oc, enum AS_SEC sec)
{
    slab_t* slab = NULL;
    if (oc != NULL) {
        slab = (slab_t*)mem_alloc_page(1, sec, false);

        if (slab != NULL) {
            memset(slab, 0, PAGE_SIZE);
            slab->header.cache = oc;
            slab->header.objsize =
                ALIGN((sizeof(node_t) + oc->osize), sizeof(uint64_t));
            slab->header.objnum =
                (PAGE_SIZE - sizeof(((slab_t*)NULL)->header)) /
                slab->header.objsize;
            slab->header.objcount = slab->header.objnum;
            list_t* obj_lst = &(slab->header.free);
            list_init(obj_lst);
            void* obj = &(slab->slab[sizeof(slab->header)]);
            for (int i = 0; i < slab->header.objnum; i++) {
                list_push(obj_lst, obj);
                obj += slab->header.objsize;
            }
        }
    }
    return slab;
}

static void* slab_alloc(slab_t* slab)
{
    void* obj = NULL;
    if (slab != NULL) {
        obj = list_pop(&slab->header.free);
        if (obj != NULL) {
            *((node_t*)obj) = NULL;
            obj += sizeof(node_t);
            slab->header.objcount--;
        }
    }
    return obj;
}

static bool slab_free(slab_t* slab, void* obj)
{
    void* obj_addr = obj - sizeof(node_t);

    if (slab != NULL) {
        if (((((uint64_t)slab) & ~(PAGE_SIZE - 1)) ==
             (((uint64_t)obj_addr) &
              ~(PAGE_SIZE - 1))) &&  // obj is part of slab
            ((((((uint64_t)obj_addr) & (PAGE_SIZE - 1)) -
               sizeof(slab->header)) %
              slab->header.objsize) == 0) &&  // is aligned to object in slab
            (*((node_t*)(obj - sizeof(node_t))) ==
             NULL)) {  // the node is not currently in any slab

            memset(obj_addr, 0, slab->header.objsize);
            list_push(&slab->header.free, obj_addr);
            slab->header.objcount++;
            return true;
        }
    }

    return false;
}
static slab_t* slab_get(void* obj)
{
    return (slab_t*)(((uint64_t)obj) & ~(PAGE_SIZE - 1));
}

static bool slab_full(slab_t* slab)
{
    return slab->header.objcount == 0;
}

static bool slab_empty(slab_t* slab)
{
    return slab->header.objnum == slab->header.objcount;
}

void objcache_init(objcache_t* oc, size_t osize, enum AS_SEC sec, bool prime)
{
    oc->osize = osize;
    list_init(&oc->slabs);
    oc->last_free = NULL;
    oc->lock = SPINLOCK_INITVAL;
    oc->section = sec;

    if (prime) {
        slab_t* slab = slab_create(oc, sec);
        list_push(&oc->slabs, &slab->header.next);
        oc->last_free = slab;
    }
}

void* objcache_alloc(objcache_t* oc)
{
    void* object = NULL;
    slab_t* slab = NULL;

    if (oc != NULL) {
        spin_lock(&oc->lock);

        if (oc->last_free == NULL) {
            list_foreach(oc->slabs, slab_t, islab)
            {
                if (!slab_full(islab)) {
                    slab = islab;
                    break;
                }
            }

            if (oc->last_free == NULL) {
                slab = slab_create(oc, oc->section);
                list_push(&oc->slabs, &slab->header.next);
            }

            oc->last_free = slab;
        } else {
            slab = oc->last_free;
        }

        if (slab != NULL) {
            object = slab_alloc(slab);
        }

        spin_unlock(&oc->lock);
    }

    return object;
}

bool objcache_free(objcache_t* oc, void* obj)
{
    slab_t* slab = NULL;
    bool ret = false;

    if (oc != NULL) {
        spin_lock(&oc->lock);

        slab = slab_get(obj);

        if (slab != NULL) {
            if (slab->header.cache == oc) {
                if (slab_free(slab, obj)) {
                    if (slab_empty(slab)) {
                        // TODO: deallocate slab page
                    }
                    ret = true;
                } else {
                    ret = true;
                }
            }
        }

        spin_unlock(&oc->lock);
    }

    return ret;
}
