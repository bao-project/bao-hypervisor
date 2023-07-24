/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>
#include <arch/smmuv2.h>

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
unsigned long platform_arch_cpuid_to_mpidr(const struct platform* plat,
                                      cpuid_t cpuid);
#endif /* __ARCH_PLATFORM_H__ */
