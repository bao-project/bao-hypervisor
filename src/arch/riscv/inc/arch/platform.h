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
        paddr_t base;       // Base address of the IOMMU mmapped IF
        unsigned mode;      // Overall IOMMU mode (Off, Bypass, DDT-lvl)
        irqid_t fq_irq_id;  // Fault Queue IRQ ID (wired)
    } iommu;
};

#endif /* __ARCH_PLATFORM_H__ */
