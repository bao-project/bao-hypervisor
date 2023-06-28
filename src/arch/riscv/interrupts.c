/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <interrupts.h>

#include <arch/plic.h>
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
        plic_global = (void*) mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, 
            platform.arch.plic_base, NUM_PAGES(sizeof(struct plic_global_hw)));

        plic_hart = (void*) mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
            platform.arch.plic_base + PLIC_THRESHOLD_OFF,
            NUM_PAGES(sizeof(struct plic_hart_hw)*PLIC_PLAT_CNTXT_NUM));

        fence_sync();

        plic_init();
    }

    /* Wait for master hart to finish plic initialization */
    cpu_sync_barrier(&cpu_glb_sync);

    plic_cpu_init();

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
        if (en)
            CSRS(sie, SIE_SSIE);
        else
            CSRC(sie, SIE_SSIE);
    } else if (int_id == TIMR_INT_ID) {
        if (en)
            CSRS(sie, SIE_STIE);
        else
            CSRC(sie, SIE_STIE);
    } else {
        plic_set_enbl(cpu()->arch.plic_cntxt, int_id, en);
        plic_set_prio(int_id, 0xFE);
    }
}

void interrupts_arch_handle()
{
    unsigned long _scause = CSRR(scause);

    switch (_scause) {
        case SCAUSE_CODE_SSI:
            interrupts_handle(SOFT_INT_ID);
            CSRC(sip, SIP_SSIP);
            break;
        case SCAUSE_CODE_STI:
            interrupts_handle(TIMR_INT_ID);
            /**
             * Clearing the timer pending bit actually has no
             * effect. We should call sbi_set_timer(-1), but at
             * the moment this is having no effect on opensbi/qemu.
             */
            // CSRC(sip, SIP_STIP);
            // sbi_set_timer(-1);
            break;
        case SCAUSE_CODE_SEI:
            plic_handle();
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
        return plic_get_pend(int_id);
    }
}

void interrupts_arch_clear(irqid_t int_id)
{
    if (int_id == SOFT_INT_ID) {
        CSRC(sip, SIP_SSIP);
    } else {
        /**
         * It is not actually possible to clear timer
         * or external interrupt pending bits by software.
         */
        WARNING("trying to clear timer or external interrupt");
    }
}

inline bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
{
    return bitmap_get(interrupt_bitmap, int_id);
}

void interrupts_arch_vm_assign(struct vm *vm, irqid_t id)
{
    vplic_set_hw(vm, id);
}
