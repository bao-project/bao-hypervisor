/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>

#define CPU_HAS_EXTENSION(EXT) (DEFINED(EXT))

extern cpuid_t CPU_MASTER;

#define MPU_ARCH_MAX_NUM_ENTRIES 32

struct cpu_arch {
    struct {
        BITMAP_ALLOC(bitmap, MPU_ARCH_MAX_NUM_ENTRIES);
        /**
         * A locked region means that it can never be removed from the MPU. For example,
         */
        BITMAP_ALLOC(locked, MPU_ARCH_MAX_NUM_ENTRIES);
        struct mpu_perms {
            perms_t el2;
            perms_t el1;
        } perms[MPU_ARCH_MAX_NUM_ENTRIES];
        /**
         * We maintain an ordered list of the regions currently in the mpu to simplify the merging
         * algorithm when mapping an overllaping region.
         */
        struct {
            struct list list;
            struct mpu_node {
                node_t node;
                mpid_t mpid;
            } node[MPU_ARCH_MAX_NUM_ENTRIES];
        } order;
    } mpu;
};

static inline struct cpu* cpu()
{
    return (struct cpu*)BAO_CPU_BASE;
}

#endif /* __ARCH_CPU_H__ */
