/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __MEM_THROT_H__
#define __MEM_THROT_H__

#include <events.h>
#include <timer.h>

#define MEM_THROT_PMU_COUNTERS 1UL

typedef struct mem_throt_info {
    unsigned long budget;
    bool throttled;
    bool initialized;
    size_t counter_id;
    uint64_t period_us;
    uint64_t period_counts;
} mem_throt_t;

void mem_throt_init(unsigned long budget, uint64_t period_us);

#endif /* __MEM_THROT_H__ */
