/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include <bao.h>
#include <spinlock.h>
#include <string.h>

struct circular_queue {
    void* buf;
    size_t elem_size;
    size_t capacity;
    int front;
    int rear;
    spinlock_t lock;
};

/**
 * Declares a typed static buffer and a circular_queue descriptor as consecutive
 * fields (in a struct body) or variables (in a local scope).
 *
 * The buffer is named __cq_buf_<name> to avoid collisions with user identifiers.
 *
 * Usage inside a struct:
 *   cq_define(struct cpu_msg, msgs, 256);
 * expands to:
 *   struct cpu_msg __cq_buf_msgs[256];
 *   struct circular_queue msgs;
 */
#define cq_define(type, name, N) \
    type __cq_buf_##name[(N)];   \
    struct circular_queue name

/**
 * Initializes a circular_queue field, transparently binding it to its static buffer.
 *
 * Takes a pointer to the struct that contains the queue (and its buffer) and the
 * bare field name so the macro can resolve __cq_buf_<name> automatically.
 *
 * Usage:  cq_init(container_ptr, field_name)
 * e.g.:   cq_init(cpu()->interface, msgs)
 */
#define cq_init(container, name)                                          \
    circular_queue_init(&(container)->name, (container)->__cq_buf_##name, \
        sizeof((container)->__cq_buf_##name[0]),                          \
        sizeof((container)->__cq_buf_##name) / sizeof((container)->__cq_buf_##name[0]))

static inline void circular_queue_init(struct circular_queue* cq, void* buf, size_t elem_size,
    size_t capacity)
{
    cq->lock = SPINLOCK_INITVAL;
    cq->buf = buf;
    cq->elem_size = elem_size;
    cq->capacity = capacity;
    cq->front = -1;
    cq->rear = -1;
}

static inline bool circular_queue_is_full(const struct circular_queue* cq)
{
    return ((cq->rear + 1) % (int)cq->capacity) == cq->front;
}

static inline bool circular_queue_is_empty(const struct circular_queue* cq)
{
    return cq->front == -1;
}

/**
 * Copies @data into the queue tail. Returns true on success, false if full.
 */
static inline bool circular_queue_push(struct circular_queue* cq, const void* data)
{
    bool ok;
    spin_lock(&cq->lock);
    ok = !circular_queue_is_full(cq);
    if (ok) {
        if (cq->front == -1) {
            cq->front = 0;
        }
        cq->rear = (cq->rear + 1) % (int)cq->capacity;
        memcpy((char*)cq->buf + (size_t)cq->rear * cq->elem_size, data, cq->elem_size);
    }
    spin_unlock(&cq->lock);
    return ok;
}

/**
 * Copies the queue head element into @data. Returns true on success, false if empty.
 */
static inline bool circular_queue_pop(struct circular_queue* cq, void* data)
{
    bool ok;
    spin_lock(&cq->lock);
    ok = !circular_queue_is_empty(cq);
    if (ok) {
        memcpy(data, (char*)cq->buf + (size_t)cq->front * cq->elem_size, cq->elem_size);
        if (cq->front == cq->rear) {
            cq->front = -1;
            cq->rear = -1;
        } else {
            cq->front = (cq->front + 1) % (int)cq->capacity;
        }
    }
    spin_unlock(&cq->lock);
    return ok;
}

#endif /* __CIRCULAR_QUEUE_H__ */
