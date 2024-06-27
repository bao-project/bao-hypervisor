#include <arch/pmu.h>
#include <cpu.h>
#include <bitmap.h>

uint64_t pmu_cntr_alloc()
{
    uint32_t index = PMU_N_CNTR_GIVEN;

    for (int __bit = bitmap_get(cpu()->events_bitmap, index); index < cpu()->implemented_event_counters;
                        __bit = bitmap_get(cpu()->events_bitmap, ++index))
        if(!__bit)
            break;

    if(index == cpu()->implemented_event_counters)
        return ERROR_NO_MORE_EVENT_COUNTERS;

    bitmap_set(cpu()->events_bitmap, index);
    return index;
}

void pmu_cntr_free(uint64_t counter)
{
    bitmap_clear(cpu()->events_bitmap, counter);
}

void pmu_interrupt_handler(irqid_t int_id)
{
    uint64_t pmovsclr = sysreg_pmovsclr_el0_read(); // MRS(PMOVSCLR_EL0);

    for (uint32_t index = PMU_N_CNTR_GIVEN; index < (cpu()->implemented_event_counters - 1); index++)
    {
        if(bit_get(pmovsclr, index))
        {
            cpu()->array_interrupt_functions[index](int_id);
        }
    }
}

/* Enable the pmu in the EL2*/
void pmu_enable(void)
{
    uint32_t pmcr = sysreg_pmcr_el0_read(); //MRS(PMCR_EL0);
    uint64_t mdcr = sysreg_mdcr_el2_read(); //MRS(MDCR_EL2);

    cpu()->implemented_event_counters = ((pmcr & PMCR_EL0_N_MASK) >> PMCR_EL0_N_POS);

    mdcr &= ~MDCR_EL2_HPMN_MASK;
	mdcr |= MDCR_EL2_HPME + (PMU_N_CNTR_GIVEN);

    sysreg_mdcr_el2_write(mdcr); //MSR(MDCR_EL2, mdcr);
}

void pmu_interrupt_enable(uint64_t cpu_id)
{
    if(!interrupts_reserve((platform.arch.events.events_irq_offset + cpu_id), 
                            pmu_interrupt_handler)) {
        ERROR("Failed to assign PMU interrupt id = %d\n", 
            platform.arch.events.events_irq_offset + cpu_id);
    }
    interrupts_arch_enable((platform.arch.events.events_irq_offset + cpu_id), true);
}

void pmu_define_event_cntr_irq_callback(irq_handler_t handler, size_t counter)
{
    cpu()->array_interrupt_functions[counter] = handler;
}
