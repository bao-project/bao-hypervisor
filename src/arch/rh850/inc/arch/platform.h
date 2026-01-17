/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>

// Arch-specific platform data
struct arch_platform {
    struct {
        paddr_t intc1_addr;
        paddr_t intc2_addr;
        paddr_t intif_addr;
        paddr_t eint_addr;
        paddr_t fenc_addr;
        paddr_t feinc_addr[8];
    } intc;

    paddr_t bootctrl_addr;

    paddr_t ipir_addr;
};

#endif /* __ARCH_PLATFORM_H__ */
