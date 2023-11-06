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

void interrupts_arch_init()
{
    if (cpu()->id == CPU_MASTER) {
        irqc_init();
    }

    /* Wait for master hart to finish irqc initialization */
    cpu_sync_barrier(&cpu_glb_sync);

    irqc_cpu_init();

    /**
     * Enable external interrupts.
     */
    CSRS(sie, SIE_SEIE);
}

void interrupts_arch_ipi_send(cpuid_t target_cpu, irqid_t ipi_id)
{
    sbi_send_ipi(1ULL << target_cpu, 0);
}

void interrupts_arch_cpu_enable(bool en)
{
    if (en) {
        CSRS(sstatus, SSTATUS_SIE_BIT);
    } else {
        CSRC(sstatus, SSTATUS_SIE_BIT);
    }
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    if (int_id == SOFT_INT_ID) {
        if (en) {
            CSRS(sie, SIE_SSIE);
        } else {
            CSRC(sie, SIE_SSIE);
        }
    } else if (int_id == TIMR_INT_ID) {
        if (en) {
            CSRS(sie, SIE_STIE);
        } else {
            CSRC(sie, SIE_STIE);
        }
    } else {
        irqc_config_irq(int_id, en);
    }
}

void interrupts_arch_handle()
{
    unsigned long _scause = CSRR(scause);

    switch (_scause) {
        case SCAUSE_CODE_SSI:
            CSRC(sip, SIP_SSIP);
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
}

bool interrupts_arch_check(irqid_t int_id)
{
    if (int_id == SOFT_INT_ID) {
        return CSRR(sip) & SIP_SSIP;
    } else if (int_id == TIMR_INT_ID) {
        return CSRR(sip) & SIP_STIP;
    } else {
        return irqc_get_pend(int_id);
    }
}

void interrupts_arch_clear(irqid_t int_id)
{
    if (int_id == SOFT_INT_ID) {
        CSRC(sip, SIP_SSIP);
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
