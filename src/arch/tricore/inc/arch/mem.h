/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MEM_H__
#define __ARCH_MEM_H__

#include <bao.h>

typedef union {
    unsigned long raw;
    struct {
        unsigned long write : 1;
        unsigned long read : 1;
        unsigned long exec : 1;
    };
} mem_flags_t;

struct addr_space_arch {
    EMPTY_STRUCT_FIELDS
};

#define PTE_FLAGS(w, r, x)       ((mem_flags_t){ .write = (w), .read = (r), .exec = (x) })

#define PTE_INVALID              PTE_FLAGS(0, 0, 0)
#define PTE_HYP_FLAGS            PTE_FLAGS(1, 1, 1)
#define PTE_HYP_DEV_FLAGS        PTE_FLAGS(1, 1, 0)
#define PTE_VM_FLAGS             PTE_FLAGS(1, 1, 1)
#define PTE_VM_DEV_FLAGS         PTE_FLAGS(1, 1, 0)
#define PTE_HYP_FLAGS_CODE       PTE_FLAGS(0, 1, 1)

#define PTE_PERM_X               PTE_FLAGS(0, 0, 1)
#define PTE_PERM_RW              PTE_FLAGS(1, 1, 0)
#define PTE_PERM_NONE            PTE_FLAGS(0, 0, 0)

#define MPU_ARCH_MAX_NUM_ENTRIES (24)
#define MPU_CODE_MAX_NUM_ENTRIES (16)
#define MPU_DATA_MAX_NUM_ENTRIES (24)

size_t mpu_granularity(void);

#endif /* __ARCH_MEM_H__ */
