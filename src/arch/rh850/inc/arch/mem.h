/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_MEM_H__
#define __ARCH_MEM_H__

#include <bao.h>

#define MPU_ARCH_MAX_NUM_ENTRIES (32)

typedef union {
    struct {
        uint16_t ur : 1;
        uint16_t uw : 1;
        uint16_t ux : 1;
        uint16_t sr : 1;
        uint16_t sw : 1;
        uint16_t sx : 1;
        uint16_t res1 : 1;
        uint16_t e : 1;
        uint16_t res2 : 6;
        uint16_t rg : 1;
        uint16_t wg : 1;
        uint16_t rmpid0 : 1;
        uint16_t rmpid1 : 1;
        uint16_t rmpid2 : 1;
        uint16_t rmpid3 : 1;
        uint16_t rmpid4 : 1;
        uint16_t rmpid5 : 1;
        uint16_t rmpid6 : 1;
        uint16_t rmpid7 : 1;
        uint16_t wmpid0 : 1;
        uint16_t wmpid1 : 1;
        uint16_t wmpid2 : 1;
        uint16_t wmpid3 : 1;
        uint16_t wmpid4 : 1;
        uint16_t wmpid5 : 1;
        uint16_t wmpid6 : 1;
        uint16_t wmpid7 : 1;
    };
    uint32_t raw;
} mpat_flags_t;

struct addr_space_arch {
    unsigned long mpu_entry_mask;
};

typedef mpat_flags_t mem_flags_t;

#define PTE_INVALID ((mem_flags_t){ .e = 0 })

/**
 * Only SPID in MPID7 can read and execute this region
 */
#define PTE_HYP_FLAGS_CODE \
    ((mem_flags_t){        \
        .ur = 1,           \
        .uw = 0,           \
        .ux = 1,           \
        .sr = 1,           \
        .sw = 0,           \
        .sx = 1,           \
        .e = 1,            \
        .rg = 0,           \
        .wg = 0,           \
        .rmpid0 = 0,       \
        .rmpid1 = 0,       \
        .rmpid2 = 0,       \
        .rmpid3 = 0,       \
        .rmpid4 = 0,       \
        .rmpid5 = 0,       \
        .rmpid6 = 0,       \
        .rmpid7 = 1,       \
        .wmpid0 = 0,       \
        .wmpid1 = 0,       \
        .wmpid2 = 0,       \
        .wmpid3 = 0,       \
        .wmpid4 = 0,       \
        .wmpid5 = 0,       \
        .wmpid6 = 0,       \
        .wmpid7 = 1,       \
    })

/**
 * Only SPID in MPID7 can read and write this region
 */
#define PTE_HYP_FLAGS \
    ((mem_flags_t){   \
        .ur = 1,      \
        .uw = 1,      \
        .ux = 0,      \
        .sr = 1,      \
        .sw = 1,      \
        .sx = 0,      \
        .e = 1,       \
        .rg = 0,      \
        .wg = 0,      \
        .rmpid0 = 0,  \
        .rmpid1 = 0,  \
        .rmpid2 = 0,  \
        .rmpid3 = 0,  \
        .rmpid4 = 0,  \
        .rmpid5 = 0,  \
        .rmpid6 = 0,  \
        .rmpid7 = 1,  \
        .wmpid0 = 0,  \
        .wmpid1 = 0,  \
        .wmpid2 = 0,  \
        .wmpid3 = 0,  \
        .wmpid4 = 0,  \
        .wmpid5 = 0,  \
        .wmpid6 = 0,  \
        .wmpid7 = 1,  \
    })

/**
 * Only the SPID in MPID7 can read write this region
 */
#define PTE_HYP_DEV_FLAGS \
    ((mem_flags_t){       \
        .ur = 1,          \
        .uw = 1,          \
        .ux = 0,          \
        .sr = 1,          \
        .sw = 1,          \
        .sx = 0,          \
        .e = 1,           \
        .rg = 0,          \
        .wg = 0,          \
        .rmpid0 = 0,      \
        .rmpid1 = 0,      \
        .rmpid2 = 0,      \
        .rmpid3 = 0,      \
        .rmpid4 = 0,      \
        .rmpid5 = 0,      \
        .rmpid6 = 0,      \
        .rmpid7 = 1,      \
        .wmpid0 = 0,      \
        .wmpid1 = 0,      \
        .wmpid2 = 0,      \
        .wmpid3 = 0,      \
        .wmpid4 = 0,      \
        .wmpid5 = 0,      \
        .wmpid6 = 0,      \
        .wmpid7 = 1,      \
    })

/**
 * Only SPIDs in MPID6 can read, write or execute this region
 */
#define PTE_VM_FLAGS \
    ((mem_flags_t){  \
        .ur = 1,     \
        .uw = 1,     \
        .ux = 1,     \
        .sr = 1,     \
        .sw = 1,     \
        .sx = 1,     \
        .e = 1,      \
        .rg = 0,     \
        .wg = 0,     \
        .rmpid0 = 0, \
        .rmpid1 = 0, \
        .rmpid2 = 0, \
        .rmpid3 = 0, \
        .rmpid4 = 0, \
        .rmpid5 = 0, \
        .rmpid6 = 1, \
        .rmpid7 = 0, \
        .wmpid0 = 0, \
        .wmpid1 = 0, \
        .wmpid2 = 0, \
        .wmpid3 = 0, \
        .wmpid4 = 0, \
        .wmpid5 = 0, \
        .wmpid6 = 1, \
        .wmpid7 = 0, \
    })

/**
 * Only SPIDs in MPID6 can read and write this region
 */
#define PTE_VM_DEV_FLAGS \
    ((mem_flags_t){      \
        .ur = 1,         \
        .uw = 1,         \
        .ux = 0,         \
        .sr = 1,         \
        .sw = 1,         \
        .sx = 0,         \
        .e = 1,          \
        .rg = 0,         \
        .wg = 0,         \
        .rmpid0 = 0,     \
        .rmpid1 = 0,     \
        .rmpid2 = 0,     \
        .rmpid3 = 0,     \
        .rmpid4 = 0,     \
        .rmpid5 = 0,     \
        .rmpid6 = 1,     \
        .rmpid7 = 0,     \
        .wmpid0 = 0,     \
        .wmpid1 = 0,     \
        .wmpid2 = 0,     \
        .wmpid3 = 0,     \
        .wmpid4 = 0,     \
        .wmpid5 = 0,     \
        .wmpid6 = 1,     \
        .wmpid7 = 0,     \
    })

static inline size_t mpu_granularity(void)
{
    return (size_t)PAGE_SIZE;
}

#endif /* __ARCH_MEM_H__ */
