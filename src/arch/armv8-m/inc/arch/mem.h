/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MEM_H__
#define __ARCH_MEM_H__

#include <bao.h>
#include <arch/sysregs.h>

typedef union {
    struct {
        uint16_t xn : 1;
        uint16_t ap : 2;
        uint16_t sh : 2;
    };
    uint16_t raw;
} rbar_flags_t;

typedef union {
    struct {
        uint16_t en : 1;
        uint16_t attr_indx : 3;
        uint16_t pxn : 1;
    };
    uint16_t raw;
} rlar_flags_t;

typedef union {
    unsigned long raw;
    struct {
        uint16_t rbar;
        uint16_t rlar;
    };
} mem_flags_t;

#define PTE_FLAGS(_rbar, _rlar) \
    ((mem_flags_t){             \
        .rbar = (_rbar),        \
        .rlar = (_rlar),        \
    })

#define PTE_INVALID PTE_FLAGS(0, 0)

#define PTE_HYP_FLAGS \
    PTE_FLAGS(MPU_RBAR_AP_RW_PLVL | MPU_RBAR_SH_NS, MPU_RLAR_ATTR(1) | MPU_RLAR_EN)
#define PTE_HYP_DEV_FLAGS \
    PTE_FLAGS(MPU_RBAR_XN | MPU_RBAR_AP_RW_PLVL | MPU_RBAR_SH_NS, MPU_RLAR_ATTR(2) | MPU_RLAR_EN)
// TODO:ARMV8M - We are missing flags to distinguish flags for mem regions RX or RW

#define PTE_VM_FLAGS     PTE_FLAGS(0, SAU_RLAR_EN)
#define PTE_VM_DEV_FLAGS PTE_FLAGS(0, SAU_RLAR_EN)

#define MPU_ARCH_MAX_NUM_ENTRIES \
    (8) // TODO:ARMV8M - This is implementation-def so it should be defined in the platform
#define SAU_ARCH_MAX_NUM_ENTRIES \
    (8) // TODO:ARMV8M - This is implementation-def so it should be defined in the platform

static inline size_t mpu_granularity(void)
{
    return (size_t)PAGE_SIZE;
}

#endif /* __ARCH_MEM_H__ */
