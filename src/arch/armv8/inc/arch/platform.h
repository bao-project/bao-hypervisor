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

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>

struct arch_platform {
    struct gic_dscrp {
        uint64_t gicc_addr;
        uint64_t gich_addr;
        uint64_t gicv_addr;
        uint64_t gicd_addr;
        uint64_t gich_alias_addr;

        uint64_t maintenance_id;
    } gic;

    struct {
        uint64_t base_addr;
    } generic_timer;

    struct clusters {
        uint64_t num;
        uint8_t* core_num;
    } clusters;
};

struct platform_desc;
uint64_t platform_arch_cpuid_to_mpdir(const struct platform_desc* plat,
                                      uint64_t cpuid);

#endif /* __ARCH_PLATFORM_H__ */