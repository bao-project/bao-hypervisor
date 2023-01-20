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
        uint16_t xn : 2;
        uint16_t ap : 2;
        uint16_t sh : 2;
    };
    uint16_t raw;
} prbar_flags_t;

typedef union {
    struct {
        uint16_t en : 1;
        uint16_t attr_indx : 3;
        uint16_t ns : 1;
        uint16_t res0 : 1;
    };
    uint16_t raw;
} prlar_flags_t;

typedef union {
    unsigned long raw;
    struct {
        uint16_t prbar;
        uint16_t prlar;
    };
} mem_flags_t;

#define PTE_FLAGS(_prbar, _prlar) ((mem_flags_t) { \
    .prbar = (_prbar), \
    .prlar = (_prlar), \
})

#define PTE_INVALID PTE_FLAGS(0, 0)
#define PTE_HYP_FLAGS \
    PTE_FLAGS(PRBAR_AP_RW_EL2 | PRBAR_SH_IS, PRLAR_ATTR(1) | PRLAR_EN)
#define PTE_HYP_DEV_FLAGS \
    PTE_FLAGS(PRBAR_XN | PRBAR_AP_RW_EL2 | PRBAR_SH_IS, \
        PRLAR_ATTR(2) | PRLAR_EN)
#define PTE_VM_FLAGS \
    PTE_FLAGS(PRBAR_AP_RW_EL1_EL2 | PRBAR_SH_IS, PRLAR_ATTR(1) | PRLAR_EN)
#define PTE_VM_DEV_FLAGS \
    PTE_FLAGS(PRBAR_XN |PRBAR_AP_RW_EL1_EL2 | PRBAR_SH_IS,\
        PRLAR_ATTR(2) | PRLAR_EN)

#define MPU_ARCH_MAX_NUM_ENTRIES    (64)

static inline const size_t mpu_granularity()
{
    return (size_t) PAGE_SIZE;
}


#endif /* __ARCH_MEM_H__ */
