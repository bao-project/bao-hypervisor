/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>

// Arch-specific platform data
struct arch_platform {
    struct ir_descript {
        paddr_t int_base;
        paddr_t src_base;
    } ir;
};

#endif /* __ARCH_PLATFORM_H__ */
