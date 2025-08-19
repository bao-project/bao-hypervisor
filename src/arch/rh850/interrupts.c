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
#include <arch/intc.h>

volatile struct ipir* ipir_hw;

extern irq_handler_t interrupt_handlers[MAX_INTERRUPT_HANDLERS];

void interrupts_arch_init()
{
    intc_init();
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    intc_set_enable(int_id, en);
    intc_set_prio(int_id, 0x01);
    intc_set_trgt(int_id, cpu()->id);
}

void interrupts_arch_handle(void)
{
    ERROR("not implemented");
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
    return bitmap_get(interrupt_bitmap, int_id);
}

void interrupts_arch_vm_assign(struct vm* vm, irqid_t int_id)
{
    intc_vm_assign(int_id, vm->id);
}

void interrupts_arch_ipi_send(cpuid_t cpu_target)
{
    if (!(ipir_hw->channel[IPI_IRQ_ID].IPI_REQS & (1U << cpu_target)))
        ipir_hw->channel[IPI_IRQ_ID].IPI_REQS = (uint8_t)(1U << cpu_target);
}

static void ipir_map_global_mmio(void)
{
    vaddr_t start_addr = platform.arch.ipir_addr;
    size_t npages = NUM_PAGES(sizeof(struct ipir));

    vaddr_t ipir_va = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, start_addr, npages);
    if (ipir_va == INVALID_VA) {
        ERROR("maping ipir failed");
    }
    ipir_hw = (struct ipir*) ipir_va;
}

void ipir_handle(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    
    cpu_msg_handler();

    /* ipi clear */
    cpuid_t from = ipir_hw->channel[IPI_IRQ_ID].IPI_FLGS;
    ipir_hw->channel[IPI_IRQ_ID].IPI_FCLRS = (uint8_t)((1 << from) - 1);
}

void interrupts_arch_ipi_init(void)
{
    if (cpu_is_master()) {
        ipir_map_global_mmio();
    }
    /* TODO How to deal with interrupt being "shared" between cores */
    interrupts_reserve(IPI_IRQ_ID, ipir_handle);

    ipir_hw->channel[IPI_IRQ_ID].IPI_ENS = ((1 << PLAT_CPU_NUM) - 1);
}

void interrupts_arch_ipi_enable(void)
{
    interrupts_cpu_enable(IPI_IRQ_ID, true);
}
