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
        paddr_t gicc_addr;
        paddr_t gich_addr;
        paddr_t gicv_addr;
        paddr_t gicd_addr;
        paddr_t gicr_addr;

        irqid_t maintenance_id;
    } gic;

    struct {
        paddr_t base;
        irqid_t interrupt_id;
        streamid_t global_mask;
    } smmu;

    struct {
        paddr_t base_addr;
    } generic_timer;

    struct clusters {
        size_t num;
        size_t* core_num;
    } clusters;
};

struct platform;
unsigned long platform_arch_cpuid_to_mpdir(const struct platform* plat,
                                      cpuid_t cpuid);
#endif /* __ARCH_PLATFORM_H__ */
