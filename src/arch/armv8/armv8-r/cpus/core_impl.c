/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/sysregs.h>
#include <arch/core_impl.h>

#define ARMV8R_R52_PARTNUMBER  0xD13U
#define ARMV8R_R52P_PARTNUMBER 0xD16U

#define CORTEX_R52_EVENT_L1D_CACHE_REFILL        0x03U
#define CORTEX_R52_EVENT_DATA_MEMORY_ACCESS      0x13U
#define CORTEX_R52_EVENT_L2D_CACHE_ACCESS        CPU_ARCH_EVENT_INVALID
#define CORTEX_R52_EVENT_L2D_CACHE_REFILL        CPU_ARCH_EVENT_INVALID
#define CORTEX_R52_EVENT_BUS_ACCESS              0x19U

#define CORTEX_R52P_EVENT_L1D_CACHE_REFILL        CORTEX_R52_EVENT_L1D_CACHE_REFILL
#define CORTEX_R52P_EVENT_DATA_MEMORY_ACCESS      CORTEX_R52_EVENT_DATA_MEMORY_ACCESS
#define CORTEX_R52P_EVENT_L2D_CACHE_ACCESS        CORTEX_R52_EVENT_L2D_CACHE_ACCESS
#define CORTEX_R52P_EVENT_L2D_CACHE_REFILL        CORTEX_R52_EVENT_L2D_CACHE_REFILL
#define CORTEX_R52P_EVENT_BUS_ACCESS              CORTEX_R52_EVENT_BUS_ACCESS
#define CORTEX_R52P_EVENT_EXTERNAL_MEMORY_REQUEST CORTEX_R52_EVENT_EXTERNAL_MEMORY_REQUEST

struct cpu_arch_event_row {
    enum cpu_arch_id cpu_id;
    const size_t events[CPU_ARCH_EVENT_NUM];
};

static const struct cpu_arch_event_row cpu_arch_event_matrix[] = {
    {
        .cpu_id = CPU_ARCH_ID_ARMV8_R_CORTEX_R52,
        .events = {
            [CPU_ARCH_EVENT_L1D_CACHE_REFILL] = CORTEX_R52_EVENT_L1D_CACHE_REFILL,
            [CPU_ARCH_EVENT_DATA_MEMORY_ACCESS] = CORTEX_R52_EVENT_DATA_MEMORY_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_ACCESS] = CORTEX_R52_EVENT_L2D_CACHE_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_REFILL] = CORTEX_R52_EVENT_L2D_CACHE_REFILL,
            [CPU_ARCH_EVENT_BUS_ACCESS] = CORTEX_R52_EVENT_BUS_ACCESS,
        },
    },
    {
        .cpu_id = CPU_ARCH_ID_ARMV8_R_CORTEX_R52P,
        .events = {
            [CPU_ARCH_EVENT_L1D_CACHE_REFILL] = CORTEX_R52P_EVENT_L1D_CACHE_REFILL,
            [CPU_ARCH_EVENT_DATA_MEMORY_ACCESS] = CORTEX_R52P_EVENT_DATA_MEMORY_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_ACCESS] = CORTEX_R52P_EVENT_L2D_CACHE_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_REFILL] = CORTEX_R52P_EVENT_L2D_CACHE_REFILL,
            [CPU_ARCH_EVENT_BUS_ACCESS] = CORTEX_R52P_EVENT_BUS_ACCESS,
        },
    },
};

/* Weak references to CPU implementation init functions */
extern void cortex_r52_impl_init(void) __attribute__((weak));

enum cpu_arch_id cpu_arch_core_id(void)
{
    unsigned long midr = sysreg_midr_el1_read();
    uint32_t part_num = MIDR_EL1_PARTNUM(midr);

    switch (part_num) {
        case ARMV8R_R52_PARTNUMBER:
            return CPU_ARCH_ID_ARMV8_R_CORTEX_R52;
        case ARMV8R_R52P_PARTNUMBER:
            return CPU_ARCH_ID_ARMV8_R_CORTEX_R52P;
        default:
            return CPU_ARCH_ID_UNKNOWN;
    }
}

void cpu_arch_core_impl_init(void)
{
    switch (cpu_arch_core_id()) {
        case CPU_ARCH_ID_ARMV8_R_CORTEX_R52:
        case CPU_ARCH_ID_ARMV8_R_CORTEX_R52P:
            if (cortex_r52_impl_init != NULL) {
                cortex_r52_impl_init();
            }
            break;
        default:
            break;
    }
}

size_t cpu_arch_event_id(enum cpu_arch_event event)
{
    if (event >= CPU_ARCH_EVENT_NUM) {
        return CPU_ARCH_EVENT_INVALID;
    }

    enum cpu_arch_id cpu_id = cpu_arch_core_id();

    for (size_t i = 0; i < (sizeof(cpu_arch_event_matrix) / sizeof(cpu_arch_event_matrix[0]));
         i++) {
        if (cpu_arch_event_matrix[i].cpu_id == cpu_id) {
            return cpu_arch_event_matrix[i].events[event];
        }
    }

    return CPU_ARCH_EVENT_INVALID;
}

size_t cpu_arch_mem_throt_event(void)
{
    return cpu_arch_event_id(CPU_ARCH_EVENT_L1D_CACHE_REFILL);
}
