/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>

#define PLIC  (1)
#define APLIC (2)
#define AIA   (3)

// Arch-specific platform data
struct arch_platform {
    union irqc_dscrp {
        struct {
            paddr_t base;
        } plic;
        struct {
            struct {
                paddr_t base;
            } aplic;
            struct {
                paddr_t base;
                size_t num_msis;
                size_t num_guest_files;
            } imsic;
        } aia;
    } irqc;

    struct {
        paddr_t base;      // Base address of the IOMMU mmapped IF
        unsigned mode;     // Overall IOMMU mode (Off, Bypass, DDT-lvl)
        irqid_t fq_irq_id; // Fault Queue IRQ ID (wired)
    } iommu;

    struct {
        paddr_t base; // Base address of the ACLINT supervisor software interrupts
    } aclint_sswi;
};

#endif /* __ARCH_PLATFORM_H__ */
