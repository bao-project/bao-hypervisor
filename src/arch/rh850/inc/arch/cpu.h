/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CPU_H__
#define __ARCH_CPU_H__

#include <bao.h>
#include <mem.h>
#include <bitmap.h>
#include <srs.h>

extern cpuid_t CPU_MASTER;

struct cpu_arch {
    struct {
        BITMAP_ALLOC(bitmap, MPU_ARCH_MAX_NUM_ENTRIES);
    } mpu_hyp;
};

static inline struct cpu* cpu(void)
{
    return (struct cpu*)srs_fewr_read();
}

static inline void snooze(void)
{
    __asm__ volatile("snooze");
}

#endif /* __ARCH_CPU_H__ */
