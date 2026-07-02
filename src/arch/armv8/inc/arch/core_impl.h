/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_CORE_IMPL_H
#define ARCH_CORE_IMPL_H

#include <bao.h>

#define CPU_ARCH_EVENT_INVALID ((size_t)~0UL)

enum cpu_arch_id {
    // Armv8-A
    CPU_ARCH_ID_ARMV8_A_CORTEX_A53,
    CPU_ARCH_ID_ARMV8_A_CORTEX_A57,
    CPU_ARCH_ID_ARMV8_A_CORTEX_A72,
    // Armv8-R
    CPU_ARCH_ID_ARMV8_R_CORTEX_R52,
    CPU_ARCH_ID_ARMV8_R_CORTEX_R52P,
    CPU_ARCH_ID_UNKNOWN,
};

enum cpu_arch_event {
    CPU_ARCH_EVENT_L1D_CACHE_REFILL,
    CPU_ARCH_EVENT_DATA_MEMORY_ACCESS,
    CPU_ARCH_EVENT_L2D_CACHE_ACCESS,
    CPU_ARCH_EVENT_L2D_CACHE_REFILL,
    CPU_ARCH_EVENT_BUS_ACCESS,
};

enum cpu_arch_id cpu_arch_core_id(void);
void cpu_arch_core_impl_init(void);
size_t cpu_arch_event_id(enum cpu_arch_event event);
size_t cpu_arch_mem_throt_event(void);

#endif /* ARCH_CORE_IMPL_H */
