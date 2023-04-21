/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <bao.h>
#include <arch/platform.h>
#include <plat/platform.h>
#include <mem.h>
#include <cache.h>
#include <platform_defs.h>

struct platform {
    size_t cpu_num;
    bool    cpu_master_fixed;
    cpuid_t cpu_master;

    size_t region_num;
    struct mem_region *regions;

    struct {
        paddr_t base;
    } console;

    struct cache cache;

    struct arch_platform arch;
};

extern struct platform platform;

#endif /* __PLATFORM_H__ */
