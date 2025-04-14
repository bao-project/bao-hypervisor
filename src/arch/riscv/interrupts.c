/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <interrupts.h>

#include <irqc.h>
#include <arch/sbi.h>
#include <cpu.h>
#include <mem.h>
#include <platform.h>
#include <vm.h>
#include <arch/csrs.h>
#include <fences.h>
#include <arch/aclint.h>

#define USE_ACLINT_IPI() (ACLINT_PRESENT() && (IRQC != AIA))

irqid_t irqc_timer_int_id;

void interrupts_arch_init()
{
    if (cpu_is_master()) {
        irqc_init();
        if (USE_ACLINT_IPI()) {
            aclint_init();
        }
    }

    /* Wait for master hart to finish irqc initialization */
    cpu_sync_barrier(&cpu_glb_sync);

    irqc_cpu_init();

    /**
     * Enable external interrupts.
     */
    csrs_sie_set(SIE_SEIE);
}

void interrupts_arch_ipi_send(cpuid_t target_cpu, irqid_t ipi_id)
{
    if (USE_ACLINT_IPI()) {
        aclint_send_ipi(target_cpu);
    } else {
        irqc_send_ipi(target_cpu, ipi_id);
    }
}

inline irqid_t interrupts_arch_reserve(irqid_t pint_id)
{
    return irqc_reserve(pint_id);
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    if (int_id == interrupts_ipi_id) {
#if ((IRQC == PLIC) || ((IRQC == APLIC)))
        if (en) {
            csrs_sie_set(SIE_SSIE);
        } else {
            csrs_sie_clear(SIE_SSIE);
        }
#elif (IRQC == AIA)
        irqc_config_irq(int_id, en);
#endif
    } else if (int_id == irqc_timer_int_id) {
        if (en) {
            csrs_sie_set(SIE_STIE);
        } else {
            csrs_sie_clear(SIE_STIE);
        }
    } else {
        irqc_config_irq(int_id, en);
    }
}

void interrupts_arch_handle(void)
{
#if (IRQC == AIA)
    unsigned long stopi = csrs_stopi_read();

    stopi = stopi >> TOPI_IID_SHIFT;
    switch (stopi) {
        case IRQ_S_SOFT:
            interrupts_handle(interrupts_ipi_id);
            csrs_sip_clear(SIP_SSIP);
            break;
        case IRQ_S_TIMER:
            interrupts_handle(irqc_timer_int_id);
            break;
        case IRQ_S_EXT:
            irqc_handle();
            break;
        default:
            WARNING("unkown interrupt");
            break;
    }
#else
    unsigned long _scause = csrs_scause_read();

    switch (_scause) {
        case SCAUSE_CODE_SSI:
            csrs_sip_clear(SIP_SSIP);
            interrupts_handle(interrupts_ipi_id);
            break;
        case SCAUSE_CODE_STI:
            interrupts_handle(irqc_timer_int_id);
            /**
             * Clearing the timer pending bit actually has no effect. We could re-program the timer
             * to "infinity" but we don't know if the handler itself re-programed the timer with a
             * new event. Therefore, at this point, we must trust the handler either correctly
             * re-programms the timer or disables the interrupt so the cpu is not starved by
             * continously triggering the timer interrupt (spoiler alert, it does!)
             */
            break;
        case SCAUSE_CODE_SEI:
            irqc_handle();
            break;
        default:
            WARNING("unkown interrupt");
            break;
    }
#endif
}

bool interrupts_arch_check(irqid_t int_id)
{
    if (int_id == interrupts_ipi_id) {
#if (IRQC != AIA)
        return csrs_sip_read() & SIP_SSIP;
#else
        return irqc_get_pend(int_id);
#endif
    } else if (int_id == irqc_timer_int_id) {
        return csrs_sip_read() & SIP_STIP;
    } else {
        return irqc_get_pend(int_id);
    }
}

void interrupts_arch_clear(irqid_t int_id)
{
    if (int_id == interrupts_ipi_id) {
#if (IRQC != AIA)
        csrs_sip_clear(SIP_SSIP);
#else
        irqc_clr_pend(int_id);
#endif
    } else if (int_id == irqc_timer_int_id) {
        /**
         * It is not actually possible to clear timer by software.
         */
        WARNING("trying to clear timer interrupt");
    } else {
        irqc_clr_pend(int_id);
    }
}

bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
{
    return bitmap_get(interrupt_bitmap, int_id);
}

void interrupts_arch_vm_assign(struct vm* vm, irqid_t id)
{
    virqc_set_hw(vm, id);
}
