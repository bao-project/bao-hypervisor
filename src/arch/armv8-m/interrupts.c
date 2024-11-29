/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <interrupts.h>

#include <arch/nvic.h>
#include <cpu.h>
#include <mem.h>
#include <platform.h>
#include <vm.h>
#include <arch/csfrs.h>
#include <fences.h>

void interrupts_arch_init() { }

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    UNUSED_ARG(int_id);
    UNUSED_ARG(en);
}

void interrupts_arch_handle(void) { }

bool interrupts_arch_check(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    return false;
}

irqid_t interrupts_arch_reserve(irqid_t pint_id)
{
    UNUSED_ARG(pint_id);
    return 0;
}

void interrupts_arch_ipi_send(cpuid_t cpu_target, irqid_t ipi_id)
{
    UNUSED_ARG(cpu_target);
    UNUSED_ARG(ipi_id);
}

void interrupts_arch_clear(irqid_t int_id)
{
    UNUSED_ARG(int_id);
}

inline bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
{
    UNUSED_ARG(interrupt_bitmap);
    UNUSED_ARG(int_id);
    return false;
}

void interrupts_arch_vm_assign(struct vm* vm, irqid_t id)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(id);
}
