/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <bao.h>
#include <arch/platform.h>
#include <plat/platform.h>
#include <mem.h>
#include <cache.h>
#include <ipc.h>

struct platform_desc {
    uint64_t cpu_num;

    uint64_t region_num;
    struct mem_region *regions;

    uint64_t ipc_num;
    struct ipc *ipcs;

    uint64_t dev_num;
    struct dev_region *devs;

    struct {
        uint64_t base;
    } console;

    struct cache cache;

    struct arch_platform arch;
};

extern struct platform_desc platform;

#endif /* __PLATFORM_H__ */
