/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <bao.h>
#include <spinlock.h>

typedef void* node_t;
struct list {
    node_t* head;
    node_t* tail;
    spinlock_t lock;
};

#define list_foreach(list, type, nodeptr)                     \
    for (type* nodeptr = ((type*)list.head); nodeptr != NULL; \
         nodeptr = *((type**)nodeptr))

#define list_foreach_tail(list, type, nodeptr, tail)        \
    for (type* nodeptr = ((type*)list.head), *tail = NULL;  \
         nodeptr != NULL; tail = nodeptr, nodeptr = *((type**)nodeptr))

static inline void list_init(struct list* list)
{
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->lock = SPINLOCK_INITVAL;
    }
}

static inline void list_push(struct list* list, node_t* node)
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

static inline node_t* list_pop(struct list* list)
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
    return temp;
}

static inline node_t* list_peek(struct list* list)
{
    node_t* temp = NULL;
    if (list != NULL) {
        temp = list->head;
    }
    return temp;
}

static inline bool list_empty(struct list* list)
{
    return (list->head == NULL);
}

static inline bool list_rm(struct list* list, node_t* node)
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
            if(temp_prev != NULL) {
                *temp_prev = *temp;
            } else {
                list->head = *temp;
            }

            if(list->head == NULL) {
                list->tail = NULL;
            }
        }

        spin_unlock(&list->lock);
    }

    return true;
}

typedef int (*node_cmp_t)(node_t*, node_t*);

static inline void list_insert_ordered(struct list* list, node_t* node, node_cmp_t cmp)
{
    if (list != NULL && node != NULL) {
        *node = NULL;
        spin_lock(&list->lock);

        node_t *cur = list->head;
        node_t *tail = NULL;

        while (cur != NULL) {
            if (cmp(cur, node) > 0) {
                break;
            }
            tail = cur;
            cur = *cur;
        }

        if (cur != NULL) {
            *node = cur;
        } else {
            list->tail = node;
        }

        if (tail != NULL) {
            *tail = node;
        } else {
            list->head = node;
        }

        spin_unlock(&list->lock);
    }
}

#endif /* __LIST_H__ */
