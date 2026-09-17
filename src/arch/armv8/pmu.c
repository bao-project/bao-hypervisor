/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/pmu.h>
#include <bitmap.h>
#include <cpu.h>
#include <platform.h>
#include <spinlock.h>

static size_t pmu_event_counters_num[CPU_MAX];
static size_t pmu_guest_counters_num[CPU_MAX];
static size_t pmu_mem_throt_reserved_num[CPU_MAX];
static BITMAP_ALLOC_ARRAY(pmu_events_bitmap, PMU_CNTR_MAX_NUM, CPU_MAX);
static irq_handler_t pmu_event_handlers[CPU_MAX][PMU_CNTR_MAX_NUM];
static irqid_t pmu_irq_id_reserved = INVALID_IRQID;
static spinlock_t pmu_irq_lock = SPINLOCK_INITVAL;

static inline size_t pmu_reserved_total(size_t cpu_index)
{
    return pmu_mem_throt_reserved_num[cpu_index];
}

static inline size_t pmu_hyp_alloc_start(size_t cpu_index)
{
    return pmu_guest_counters_num[cpu_index];
}

static inline void pmu_refresh_event_counter_count(size_t cpu_index)
{
    uint64_t pmcr = sysreg_pmcr_el0_read();
    size_t counters_num = (size_t)((pmcr & PMCR_EL0_N_MASK) >> PMCR_EL0_N_POS);

    if (counters_num > PMU_CNTR_MAX_NUM) {
        counters_num = PMU_CNTR_MAX_NUM;
    }

    pmu_event_counters_num[cpu_index] = counters_num;
}

static inline void pmu_recompute_counter_partition(size_t cpu_index)
{
    size_t reserved_total = pmu_reserved_total(cpu_index);
    size_t counters_num = pmu_event_counters_num[cpu_index];

    if (reserved_total > counters_num) {
        ERROR("PMU counters requested (%zu) exceed available counters (%zu)\n", reserved_total,
              counters_num);
    }

    pmu_guest_counters_num[cpu_index] = counters_num - reserved_total;
}

static inline void pmu_restore_el2_control(size_t cpu_index)
{
    uint64_t mdcr = sysreg_mdcr_el2_read();
    mdcr &= ~((uint64_t)MDCR_EL2_HPMN_MASK);
    mdcr |= (uint64_t)MDCR_EL2_HPME | (uint64_t)pmu_guest_counters_num[cpu_index];
    sysreg_mdcr_el2_write(mdcr);
}

static inline size_t pmu_cpu_index(void)
{
    if (cpu()->id >= CPU_MAX) {
        ERROR("Invalid CPU id = %lu\n", cpu()->id);
    }

    return (size_t)cpu()->id;
}

static inline irqid_t pmu_irq_id(void)
{
    irqid_t irq_id = platform.arch.events.interrupt_id;
    if ((irq_id == INVALID_IRQID) || (irq_id == 0U)) {
        ERROR("Invalid PMU interrupt id\n");
    }

    return irq_id;
}

ssize_t pmu_cntr_alloc(void)
{
    size_t cpu_index = pmu_cpu_index();
    size_t alloc_start = pmu_hyp_alloc_start(cpu_index);

    for (size_t index = alloc_start; index < pmu_event_counters_num[cpu_index]; index++) {
        if (bitmap_get(pmu_events_bitmap[cpu_index], index) == BITMAP_NOT_SET) {
            bitmap_set(pmu_events_bitmap[cpu_index], index);
            return (ssize_t)index;
        }
    }

    return ERROR_NO_MORE_EVENT_COUNTERS;
}

void pmu_cntr_free(size_t counter)
{
    size_t cpu_index = pmu_cpu_index();

    if (counter >= PMU_CNTR_MAX_NUM) {
        ERROR("Invalid PMU counter index = %zu\n", counter);
    }

    bitmap_clear(pmu_events_bitmap[cpu_index], counter);
}

static void pmu_interrupt_handler(irqid_t int_id)
{
    size_t cpu_index = pmu_cpu_index();
    size_t alloc_start = pmu_hyp_alloc_start(cpu_index);
    uint64_t overflow_status = sysreg_pmovsclr_el0_read();
    sysreg_pmovsclr_el0_write(overflow_status);

    for (size_t counter = alloc_start; counter < pmu_event_counters_num[cpu_index]; counter++) {
        if (bit64_get(overflow_status, counter) != 0U) {
            irq_handler_t handler = pmu_event_handlers[cpu_index][counter];
            if (handler != NULL) {
                handler(int_id);
            }
        }
    }
}

void pmu_configure_counter_partition(size_t mem_throt_reserved)
{
    size_t cpu_index = pmu_cpu_index();

    pmu_mem_throt_reserved_num[cpu_index] = mem_throt_reserved;

    pmu_refresh_event_counter_count(cpu_index);
    pmu_recompute_counter_partition(cpu_index);
    pmu_restore_el2_control(cpu_index);
}

void pmu_enable(void)
{
    size_t cpu_index = pmu_cpu_index();

    pmu_refresh_event_counter_count(cpu_index);
    pmu_recompute_counter_partition(cpu_index);
    bitmap_clear_consecutive(pmu_events_bitmap[cpu_index], 0, PMU_CNTR_MAX_NUM);
    for (size_t i = 0; i < PMU_CNTR_MAX_NUM; i++) {
        pmu_event_handlers[cpu_index][i] = NULL;
    }

    pmu_restore_el2_control(cpu_index);

    uint64_t pmcr = sysreg_pmcr_el0_read();
    pmcr = bit_set(pmcr, 0); // PMCR_EL0.E
    sysreg_pmcr_el0_write(pmcr);
    __asm__ volatile("isb");
}

void pmu_interrupt_enable(cpuid_t cpu_id)
{
    UNUSED_ARG(cpu_id);
    size_t cpu_index = pmu_cpu_index();
    pmu_restore_el2_control(cpu_index);

    irqid_t irq_id = pmu_irq_id();

    spin_lock(&pmu_irq_lock);
    if (pmu_irq_id_reserved == INVALID_IRQID) {
        pmu_irq_id_reserved = interrupts_reserve(irq_id, pmu_interrupt_handler);
        if (pmu_irq_id_reserved == INVALID_IRQID) {
            ERROR("Failed to assign PMU interrupt id = %u\n", irq_id);
        }
    } else if (pmu_irq_id_reserved != irq_id) {
        ERROR("Inconsistent PMU interrupt id = %u\n", irq_id);
    }
    spin_unlock(&pmu_irq_lock);

    interrupts_arch_enable(pmu_irq_id_reserved, true);
}

void pmu_interrupt_disable(cpuid_t cpu_id)
{
    UNUSED_ARG(cpu_id);
    if (pmu_irq_id_reserved != INVALID_IRQID) {
        interrupts_arch_enable(pmu_irq_id_reserved, false);
    }
}

void pmu_define_event_cntr_irq_callback(irq_handler_t handler, size_t counter)
{
    size_t cpu_index = pmu_cpu_index();

    if (counter >= PMU_CNTR_MAX_NUM) {
        ERROR("Invalid PMU counter index = %zu\n", counter);
    }

    pmu_event_handlers[cpu_index][counter] = handler;
}
