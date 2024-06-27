#ifndef __ARCH_PMU_H__
#define __ARCH_PMU_H__

#include <interrupts.h>
#include <arch/sysregs.h>
#include <platform.h>
#include <printk.h>
#include <bit.h>

#define PMU_CNTR_MAX_NUM 32

#if !defined(UINT32_MAX)
    #define UINT32_MAX		0xffffffffU /* 4294967295U */
#endif


#define PMCR_EL0_N_POS		(11)
#define PMCR_EL0_N_MASK		(0x1F << PMCR_EL0_N_POS)

#define MDCR_EL2_HPME		(1 << 7)
#define MDCR_EL2_HPMN_MASK	(0x1F)

#define PMEVTYPER_P				31 
#define PMEVTYPER_U				30 
#define PMEVTYPER_NSK			29 
#define PMEVTYPER_NSU			28 
#define PMEVTYPER_NSH			27  
#define PMEVTYPER_M				26 
#define PMEVTYPER_MT			25
#define PMEVTYPER_SH			24

#define PMU_N_CNTR_GIVEN    1
#define ERROR_NO_MORE_EVENT_COUNTERS    -10


#define DATA_MEMORY_ACCESS          0x13
#define L2D_CACHE_ACCESS            0x16
#define L2D_CACHE_REFILL            0x17
#define BUS_ACCESS                  0x19
#define EXTERNAL_MEMORY_REQUEST     0xC0


static size_t events_array[] = {
    DATA_MEMORY_ACCESS,
    L2D_CACHE_ACCESS,
    BUS_ACCESS,
    EXTERNAL_MEMORY_REQUEST,
    L2D_CACHE_REFILL
};


uint64_t pmu_cntr_alloc();
void pmu_cntr_free(uint64_t);
void pmu_enable(void);
void pmu_interrupt_enable(uint64_t cpu_id);
void pmu_define_event_cntr_irq_callback(irq_handler_t handler, size_t counter);


static inline void pmu_disable(void) {
    uint64_t mdcr;

    mdcr = sysreg_mdcr_el2_read(); 
    mdcr = bit_clear(mdcr, MDCR_EL2_HPME);

    sysreg_mdcr_el2_write(mdcr);
}

static inline int pmu_cntr_enable(size_t counter) {
    uint64_t pmcntenset;

    pmcntenset = sysreg_pmcntenset_el0_read();
    pmcntenset = bit_set(pmcntenset, counter);
    sysreg_pmcntenset_el0_write(pmcntenset);

    return 0;
}

static inline void pmu_cntr_disable(size_t counter) {
    uint64_t pmcntenclr = 0;
    pmcntenclr = bit_set(pmcntenclr, counter);
    sysreg_pmcntenclr_el0_write(pmcntenclr);
}


static inline void pmu_cntr_set(size_t counter, unsigned long value) {
    uint64_t pmselr;

    pmselr = sysreg_pmselr_el0_read();
    pmselr = bit_insert(pmselr, counter, 0, 5);
    sysreg_pmselr_el0_write(pmselr);

    value = UINT32_MAX - value;
    sysreg_pmxevcntr_el0_write(value);
}

static inline unsigned long pmu_cntr_get(size_t counter) {
    uint64_t pmselr;

    pmselr = sysreg_pmselr_el0_read();
    pmselr = bit_insert(pmselr, counter, 0, 5);
    sysreg_pmselr_el0_write(pmselr);

    return sysreg_pmxevcntr_el0_read();
}

static inline void pmu_set_evtyper(size_t counter, size_t event) {
    uint64_t pmselr;

    pmselr = sysreg_pmselr_el0_read();
    pmselr = bit_insert(pmselr, counter, 0, 5);
    sysreg_pmselr_el0_write(pmselr);
    uint64_t pmxevtyper = sysreg_pmxevtyper_el0_read();

    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_P);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_U);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_NSK);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_NSU);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_NSH);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_M);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_MT);
    pmxevtyper = bit_clear(pmxevtyper, PMEVTYPER_SH);

    pmxevtyper = bit_insert(pmxevtyper, events_array[event], 0, 10);

    sysreg_pmxevtyper_el0_write(pmxevtyper);
}

static inline void pmu_interrupt_disable(uint64_t cpu_id) {
    // Set the interrupt number for the PMU event.
    uint64_t interrupt_number = platform.arch.events.events_irq_offset + cpu_id;

    // Disable the specified interrupt.
    interrupts_arch_enable(interrupt_number, false);
}

static inline void pmu_set_cntr_irq_enable(size_t counter) {
    uint64_t pmintenset;
    pmintenset = sysreg_pmintenset_el1_read();
    pmintenset = bit_set(pmintenset, counter);

    sysreg_pmintenset_el1_write(pmintenset);
}

static inline void pmu_set_cntr_irq_disable(size_t counter) {
    uint64_t pmintenset = 0;
    pmintenset = bit_set(pmintenset, counter);

    sysreg_pmintenclr_el1_write(pmintenset);
}

static inline void pmu_clear_cntr_ovs(size_t counter) {
    uint64_t pmovsclr = 0;
    pmovsclr = bit_set(pmovsclr, counter);
    sysreg_pmovsclr_el0_write(pmovsclr); 
}

#endif /* __ARCH_PMU_H__ */