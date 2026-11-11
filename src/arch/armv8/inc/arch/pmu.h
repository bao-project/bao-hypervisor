/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_PMU_H__
#define __ARCH_PMU_H__

#include <arch/sysregs.h>
#include <bit.h>
#include <interrupts.h>

#define PMU_CNTR_MAX_NUM 32UL

#define PMCR_EL0_N_POS 11UL
#define PMCR_EL0_N_MASK (0x1FUL << PMCR_EL0_N_POS)

#define MDCR_EL2_HPME (1UL << 7)
#define MDCR_EL2_HPMN_MASK 0x1FUL

#define PMEVTYPER_P 31UL
#define PMEVTYPER_U 30UL
#define PMEVTYPER_NSK 29UL
#define PMEVTYPER_NSU 28UL
#define PMEVTYPER_NSH 27UL
#define PMEVTYPER_M 26UL
#define PMEVTYPER_MT 25UL
#define PMEVTYPER_SH 24UL

#define ERROR_NO_MORE_EVENT_COUNTERS ((ssize_t)-1)

ssize_t pmu_cntr_alloc(void);
void pmu_cntr_free(size_t counter);
void pmu_configure_counter_partition(size_t mem_throt_reserved);
void pmu_enable(void);
void pmu_interrupt_enable(cpuid_t cpu_id);
void pmu_interrupt_disable(cpuid_t cpu_id);
void pmu_define_event_cntr_irq_callback(irq_handler_t handler, size_t counter);

static inline void pmu_disable(void)
{
    uint64_t mdcr = sysreg_mdcr_el2_read();
    mdcr = bit_clear(mdcr, MDCR_EL2_HPME);
    sysreg_mdcr_el2_write(mdcr);
}

static inline int pmu_cntr_enable(size_t counter)
{
    uint64_t pmcntenset = 0;
    pmcntenset = bit_set(pmcntenset, counter);
    sysreg_pmcntenset_el0_write(pmcntenset);
    __asm__ volatile("isb");
    return 0;
}

static inline void pmu_cntr_disable(size_t counter)
{
    uint64_t pmcntenclr = 0;
    pmcntenclr = bit_set(pmcntenclr, counter);
    sysreg_pmcntenclr_el0_write(pmcntenclr);
}

static inline void pmu_cntr_set(size_t counter, unsigned long value)
{
    uint64_t pmselr = sysreg_pmselr_el0_read();
    pmselr = bit_insert(pmselr, (uint64_t)counter, 0, 5);
    sysreg_pmselr_el0_write(pmselr);
    __asm__ volatile("isb");

    if ((value == 0UL) || (value > UINT32_MAX)) {
        ERROR("Invalid PMU counter budget = %lu\n", value);
    }

    unsigned long preload = (UINT32_MAX - value) + 1UL;
    sysreg_pmxevcntr_el0_write(preload);
    __asm__ volatile("isb");
}

static inline unsigned long pmu_cntr_get(size_t counter)
{
    uint64_t pmselr = sysreg_pmselr_el0_read();
    pmselr = bit_insert(pmselr, (uint64_t)counter, 0, 5);
    sysreg_pmselr_el0_write(pmselr);
    return sysreg_pmxevcntr_el0_read();
}

static inline void pmu_set_evtyper(size_t counter, size_t event)
{
    uint64_t pmselr = sysreg_pmselr_el0_read();
    pmselr = bit_insert(pmselr, (uint64_t)counter, 0, 5);
    sysreg_pmselr_el0_write(pmselr);
    __asm__ volatile("isb");

    uint64_t pmxevtyper = sysreg_pmxevtyper_el0_read();

    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_P);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_U);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_NSK);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_NSU);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_NSH);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_M);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_MT);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_SH);

    pmxevtyper = bit_insert(pmxevtyper, (uint64_t)event, 0, 16);
    sysreg_pmxevtyper_el0_write(pmxevtyper);
    __asm__ volatile("isb");
}

static inline void pmu_set_cntr_irq_enable(size_t counter)
{
    uint64_t pmintenset = 0;
    pmintenset = bit_set(pmintenset, counter);
    sysreg_pmintenset_el1_write(pmintenset);
    __asm__ volatile("isb");
}

static inline void pmu_set_cntr_irq_disable(size_t counter)
{
    uint64_t pmintenset = 0;
    pmintenset = bit_set(pmintenset, counter);
    sysreg_pmintenclr_el1_write(pmintenset);
    __asm__ volatile("isb");
}

static inline void pmu_clear_cntr_ovs(size_t counter)
{
    uint64_t pmovsclr = 0;
    pmovsclr = bit_set(pmovsclr, counter);
    sysreg_pmovsclr_el0_write(pmovsclr);
    __asm__ volatile("isb");
}

#endif /* __ARCH_PMU_H__ */
