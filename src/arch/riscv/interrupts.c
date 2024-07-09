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

void interrupts_arch_init()
{
    if (cpu_is_master()) {
        irqc_init();
        if (ACLINT_PRESENT()) {
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
    UNUSED_ARG(ipi_id);

    if (ACLINT_PRESENT()) {
        aclint_send_ipi(target_cpu);
    } else {
        sbi_send_ipi(1ULL << target_cpu, 0);
    }
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    if (int_id == SOFT_INT_ID) {
        if (en) {
            csrs_sie_set(SIE_SSIE);
        } else {
            csrs_sie_clear(SIE_SSIE);
        }
    } else if (int_id == TIMR_INT_ID) {
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
    unsigned long _scause = csrs_scause_read();

    cpu()->is_handling_irq = true;
    cpu()->arch.handling_irq.cause = _scause;

    switch (_scause) {
        case SCAUSE_CODE_SSI:
            csrs_sip_clear(SIP_SSIP);
            interrupts_handle(SOFT_INT_ID);
            break;
        case SCAUSE_CODE_STI:
            interrupts_handle(TIMR_INT_ID);
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
            // WARNING("unkown interrupt");
            break;
    }

    cpu()->is_handling_irq = false;
}

bool interrupts_arch_check(irqid_t int_id)
{
    if (int_id == SOFT_INT_ID) {
        return csrs_sip_read() & SIP_SSIP;
    } else if (int_id == TIMR_INT_ID) {
        return csrs_sip_read() & SIP_STIP;
    } else {
        return irqc_get_pend(int_id);
    }
}

void interrupts_arch_clear(irqid_t int_id)
{
    if (int_id == SOFT_INT_ID) {
        csrs_sip_clear(SIP_SSIP);
    } else if (int_id == TIMR_INT_ID) {
        /**
         * It is not actually possible to clear timer by software.
         */
        WARNING("trying to clear timer interrupt");
    } else {
        irqc_clr_pend(int_id);
    }
}

inline bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
{
    return bitmap_get(interrupt_bitmap, int_id);
}

void interrupts_arch_vm_assign(struct vm* vm, irqid_t id)
{
    virqc_set_hw(vm, id);
}

void interrupts_arch_finish()
{
    if (cpu()->is_handling_irq) {
        switch (cpu()->arch.handling_irq.cause) {
            case SCAUSE_CODE_SSI:
                csrs_sip_clear(SIP_SSIP);
                break;
            case SCAUSE_CODE_STI:
                /**
                 * Clearing the timer pending bit actually has no effect. We could re-program the
                 * timer to "infinity" but we don't know if the handler itself re-programed the
                 * timer with a new event. Therefore, at this point, we must trust the handler
                 * either correctly re-programms the timer or disables the interrupt so the cpu is
                 * not starved by continously triggering the timer interrupt (spoiler alert, it
                 * does!)
                 */
                break;
            case SCAUSE_CODE_SEI:
                irqc_finish_interrupt((irqid_t)cpu()->arch.handling_irq.external_id);
                break;
            default:
                break;
        }
    }
}
