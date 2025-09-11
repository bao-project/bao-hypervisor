/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <interrupts.h>
#include <mem.h>
#include <platform.h>
#include <vm.h>
#include <intc.h>
#include <ipir.h>

void interrupts_arch_init()
{
    intc_init();
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    intc_set_enable(int_id, en);
    intc_set_prio(int_id, INTC_MAX_PRIO);
    intc_set_trgt(int_id, cpu()->id);
}

bool interrupts_arch_check(irqid_t int_id)
{
    return intc_get_pend(int_id);
}

void interrupts_arch_clear(irqid_t int_id)
{
    intc_set_pend(int_id, false);
}

irqid_t interrupts_arch_reserve(irqid_t int_id)
{
    intc_hyp_assign(int_id);

    return int_id;
}

inline bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
{
    /* IPIR channels not used by the hypervisor are shared between VMs */
    return bitmap_get(interrupt_bitmap, int_id) &&
        !(int_id < IPIR_NUM_CHANNELS && int_id != IPI_HYP_IRQ_ID);
}

void interrupts_arch_vm_assign(struct vm* vm, irqid_t int_id)
{
    intc_vm_assign(vm, int_id);
}

void interrupts_arch_ipi_init(void)
{
    ipir_init();
}

void interrupts_arch_ipi_send(cpuid_t cpu_target)
{
    ipir_send_ipi(cpu_target);
}
