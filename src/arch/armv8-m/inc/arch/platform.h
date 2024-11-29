/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>

// Arch-specific platform data
struct arch_platform {
    struct nvic_descript {
        paddr_t int_addr;
        paddr_t src_addr;
        unsigned long num_interrupts;
        irqid_t* interrupts;
    } nvic;
};

#endif /* __ARCH_PLATFORM_H__ */
