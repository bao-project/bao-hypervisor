/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>

// Arch-specific platform data
struct arch_platform {
    paddr_t plic_base;

    struct {
        paddr_t base;
        unsigned mode;
        irqid_t fq_irq_id;
    } iommu;
};

#endif /* __ARCH_PLATFORM_H__ */
