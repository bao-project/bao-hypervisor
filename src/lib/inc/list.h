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

#ifndef __LIST_H__
#define __LIST_H__

#include <bao.h>
#include <spinlock.h>

typedef void* node_t;
typedef struct {
    node_t* head;
    node_t* tail;
    spinlock_t lock;
} list_t;

#define list_foreach(list, type, nodeptr)                     \
    for (type* nodeptr = ((type*)list.head); nodeptr != NULL; \
         nodeptr = *((type**)nodeptr))

#define list_foreach_tail(list, type, nodeptr, tail)                \
    for (type* nodeptr = ((type*)list.head), *tail = ((type*)list); \
         nodeptr != NULL; tail = nodeptr, nodeptr = *((type**)nodeptr))

static inline void list_init(list_t* list)
{
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->lock = SPINLOCK_INITVAL;
    }
}

static inline void list_push(list_t* list, node_t* node)
{
    if (list != NULL && node != NULL) {
        *node = NULL;
        spin_lock(&list->lock);

        if (list->tail != NULL) *list->tail = node;

        list->tail = node;

        if (list->head == NULL) list->head = node;

        spin_unlock(&list->lock);
    }
}

static inline node_t* list_pop(list_t* list)
{
    node_t* temp = NULL;
    if (list != NULL) {
        spin_lock(&list->lock);

        if (list->head != NULL) {
            temp = list->head;
            list->head = *list->head;

            if (list->head == NULL) list->tail = NULL;

            *temp = NULL;
        }

        spin_unlock(&list->lock);
    }
    return (void*)temp;
}

static inline node_t* list_peek(list_t* list)
{
    node_t* temp = NULL;
    if (list != NULL) {
        temp = list->head;
    }
    return (void*)temp;
}

static inline bool list_empty(list_t* list)
{
    return (list->head == NULL);
}

static inline bool list_rm(list_t* list, node_t node)
{
    if (list != NULL && node != NULL) {
        spin_lock(&list->lock);

        node_t* temp = list->head;
        node_t* temp_prev = NULL;
        while (temp != NULL && temp != node) {
            temp_prev = temp;
            temp = *temp;
        }
        if (temp != NULL && temp == node) {
            /* found the node, remove it */
            *temp_prev = *temp;
        }

        spin_unlock(&list->lock);
    }

    return true;
}

#endif /* __LIST_H__ */
