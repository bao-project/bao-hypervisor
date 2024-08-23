/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <interrupts.h>

#include <arch/ir.h>
#include <cpu.h>
#include <mem.h>
#include <platform.h>
#include <vm.h>
#include <arch/csfrs.h>
#include <fences.h>
#include <arch/aclint.h>

void interrupts_arch_init()
{
    if (cpu_is_master()) {
        ir_init();
    }

    /* Wait for master hart to finish irqc initialization */
    cpu_sync_barrier(&cpu_glb_sync);

    ir_cpu_init();

    /* TODO: enable interrupts */
}

void interrupts_arch_ipi_send(cpuid_t target_cpu, irqid_t ipi_id)
{
    (void)ipi_id;
    ir_send_ipi(target_cpu);
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    ir_config_irq(int_id, en);
}

void interrupts_arch_handle(void)
{
    ir_handle();
}

bool interrupts_arch_check(irqid_t int_id)
{
    return ir_get_pend(int_id);
}

void interrupts_arch_clear(irqid_t int_id)
{
    ir_clr_pend(int_id);
}

inline bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
{
    return bitmap_get(interrupt_bitmap, int_id);
}

void interrupts_arch_vm_assign(struct vm* vm, irqid_t id)
{
    ir_assign_int_to_vm(vm, id);
}

