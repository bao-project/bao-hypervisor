/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CPU_SYNC_H__
#define __CPU_SYNC_H__

#include <bao.h>
#include <spinlock.h>

struct cpu_synctoken {
    spinlock_t lock;
    volatile size_t n;
    volatile bool ready;
    volatile size_t count;
};

#endif /* __CPU_SYNC_H__ */
