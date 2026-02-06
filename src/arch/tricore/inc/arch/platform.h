/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PLATFORM_H__
#define __ARCH_PLATFORM_H__

#include <bao.h>

// Arch-specific platform data
struct plat_device {
    unsigned long dev_base;
    unsigned long apu_num;
    unsigned long* apu_addr;
    unsigned long prot_num;
    unsigned long* prot_addr;
};
struct arch_platform {
    struct ir_descript {
        paddr_t int_addr;
        paddr_t src_addr;
        unsigned long GPSR_offset;
        unsigned long GPSR_size;
    } ir;
    unsigned long device_num;
    const struct plat_device* devices;
};

#endif /* __ARCH_PLATFORM_H__ */
