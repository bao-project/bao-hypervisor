/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
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
    if (cpu.id == CPU_MASTER) {
        mem_map_dev(&cpu.as, (void *)&plic_global, platform.arch.plic_base,
                    ALIGN(sizeof(plic_global), PAGE_SIZE) / PAGE_SIZE);

        mem_map_dev(&cpu.as, (void *)plic_hart,
                    platform.arch.plic_base + PLIC_CLAIMCMPLT_OFF,
                    ALIGN(sizeof(plic_hart), PAGE_SIZE) / PAGE_SIZE);

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

void interrupts_arch_ipi_send(uint64_t target_cpu, uint64_t ipi_id)
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

void interrupts_arch_enable(uint64_t int_id, bool en)
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
        plic_set_enbl(cpu.arch.plic_cntxt, int_id, en);
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

bool interrupts_arch_check(uint64_t int_id)
{
    if (int_id == SOFT_INT_ID) {
        return CSRR(sip) & SIP_SSIP;
    } else if (int_id == TIMR_INT_ID) {
        return CSRR(sip) & SIP_STIP;
    } else {
        return plic_get_pend(int_id);
    }
}

void interrupts_arch_clear(uint64_t int_id)
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

inline bool interrupts_arch_conflict(bitmap_t interrupt_bitmap, uint64_t int_id)
{
    return bitmap_get(interrupt_bitmap, int_id);
}

void interrupts_arch_vm_assign(vm_t *vm, uint64_t id)
{
    vplic_set_hw(vm, id);
}

void interrupts_arch_vm_inject(vm_t *vm, uint64_t id)
{
    vplic_inject(cpu.vcpu, id);
}
