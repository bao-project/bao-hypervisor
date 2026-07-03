/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/core_impl.h>
#include <arch/sysregs.h>

#define ARMV8A_A53_PARTNUMBER 0xD03U
#define ARMV8A_A57_PARTNUMBER 0xD07U
#define ARMV8A_A72_PARTNUMBER 0xD08U

#define CORTEX_A53_EVENT_L1D_CACHE_REFILL        0x03U
#define CORTEX_A53_EVENT_DATA_MEMORY_ACCESS      0x13U
#define CORTEX_A53_EVENT_L2D_CACHE_ACCESS        0x16U
#define CORTEX_A53_EVENT_L2D_CACHE_REFILL        0x17U
#define CORTEX_A53_EVENT_BUS_ACCESS              0x19U

#define CORTEX_A57_EVENT_L1D_CACHE_REFILL        0x03U
#define CORTEX_A57_EVENT_DATA_MEMORY_ACCESS      0x13U
#define CORTEX_A57_EVENT_L2D_CACHE_ACCESS        0x16U
#define CORTEX_A57_EVENT_L2D_CACHE_REFILL        0x17U
#define CORTEX_A57_EVENT_BUS_ACCESS              0x19U

#define CORTEX_A72_EVENT_L1D_CACHE_REFILL        0x03U
#define CORTEX_A72_EVENT_DATA_MEMORY_ACCESS      0x13U
#define CORTEX_A72_EVENT_L2D_CACHE_ACCESS        0x16U
#define CORTEX_A72_EVENT_L2D_CACHE_REFILL        0x17U
#define CORTEX_A72_EVENT_BUS_ACCESS              0x19U

#define CPU_ARCH_EVENT_NUM 8


struct cpu_arch_event_row {
    enum cpu_arch_id cpu_id;
    const size_t events[CPU_ARCH_EVENT_NUM];
};

static const struct cpu_arch_event_row cpu_arch_event_matrix[] = {
    {
        .cpu_id = CPU_ARCH_ID_ARMV8_A_CORTEX_A53,
        .events = {
            [CPU_ARCH_EVENT_L1D_CACHE_REFILL] = CORTEX_A53_EVENT_L1D_CACHE_REFILL,
            [CPU_ARCH_EVENT_DATA_MEMORY_ACCESS] = CORTEX_A53_EVENT_DATA_MEMORY_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_ACCESS] = CORTEX_A53_EVENT_L2D_CACHE_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_REFILL] = CORTEX_A53_EVENT_L2D_CACHE_REFILL,
            [CPU_ARCH_EVENT_BUS_ACCESS] = CORTEX_A53_EVENT_BUS_ACCESS,
        },
    },
    {
        .cpu_id = CPU_ARCH_ID_ARMV8_A_CORTEX_A57,
        .events = {
            [CPU_ARCH_EVENT_L1D_CACHE_REFILL] = CORTEX_A57_EVENT_L1D_CACHE_REFILL,
            [CPU_ARCH_EVENT_DATA_MEMORY_ACCESS] = CORTEX_A57_EVENT_DATA_MEMORY_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_ACCESS] = CORTEX_A57_EVENT_L2D_CACHE_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_REFILL] = CORTEX_A57_EVENT_L2D_CACHE_REFILL,
            [CPU_ARCH_EVENT_BUS_ACCESS] = CORTEX_A57_EVENT_BUS_ACCESS,
        },
    },
    {
        .cpu_id = CPU_ARCH_ID_ARMV8_A_CORTEX_A72,
        .events = {
            [CPU_ARCH_EVENT_L1D_CACHE_REFILL] = CORTEX_A72_EVENT_L1D_CACHE_REFILL,
            [CPU_ARCH_EVENT_DATA_MEMORY_ACCESS] = CORTEX_A72_EVENT_DATA_MEMORY_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_ACCESS] = CORTEX_A72_EVENT_L2D_CACHE_ACCESS,
            [CPU_ARCH_EVENT_L2D_CACHE_REFILL] = CORTEX_A72_EVENT_L2D_CACHE_REFILL,
            [CPU_ARCH_EVENT_BUS_ACCESS] = CORTEX_A72_EVENT_BUS_ACCESS,
        },
    },
};

enum cpu_arch_id cpu_arch_core_id(void)
{
    unsigned long midr = sysreg_midr_el1_read();
    uint32_t part_num = MIDR_EL1_PARTNUM(midr);

    switch (part_num) {
        case ARMV8A_A53_PARTNUMBER:
            return CPU_ARCH_ID_ARMV8_A_CORTEX_A53;
        case ARMV8A_A57_PARTNUMBER:
            return CPU_ARCH_ID_ARMV8_A_CORTEX_A57;
        case ARMV8A_A72_PARTNUMBER:
            return CPU_ARCH_ID_ARMV8_A_CORTEX_A72;
        default:
            return CPU_ARCH_ID_UNKNOWN;
    }
}

void cpu_arch_core_impl_init(void) { }

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
