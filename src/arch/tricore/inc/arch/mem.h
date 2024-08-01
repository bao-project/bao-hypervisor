/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MEM_H__
#define __ARCH_MEM_H__

#include <bao.h>

typedef struct {
    /* each variable is a bit */
    /* TODO this encompasses bits in 3 registers DPWE_0 DPRE_0 CPXE_0*/
    unsigned long write;
    unsigned long read;
    unsigned long exec;

} mem_flags_t;

#define PTE_FLAGS(w, r, x) \
    ((mem_flags_t){ .write = (w), .read = (r), .exec = (x) })

#define PTE_INVALID         PTE_FLAGS(0, 0, 0)
#define PTE_HYP_FLAGS       PTE_FLAGS(1, 1, 1)
#define PTE_HYP_DEV_FLAGS   PTE_FLAGS(1, 1, 0)
#define PTE_VM_FLAGS        PTE_FLAGS(1, 1, 1)
#define PTE_VM_DEV_FLAGS    PTE_FLAGS(1, 1, 0)

#define MPU_ARCH_MAX_NUM_ENTRIES (64)

static inline size_t mpu_granularity()
{
    return (size_t)PAGE_SIZE;
}
#endif /* __ARCH_MEM_H__ */
