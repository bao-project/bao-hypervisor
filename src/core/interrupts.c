/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <interrupts.h>

#include <cpu.h>
#include <vm.h>
#include <bitmap.h>
#include <string.h>

BITMAP_ALLOC(global_interrupt_bitmap, MAX_INTERRUPT_LINES);
spinlock_t irq_reserve_lock = SPINLOCK_INITVAL;

irq_handler_t interrupt_handlers[MAX_INTERRUPT_HANDLERS];

irqid_t interrupts_ipi_id;

void interrupts_cpu_sendipi(cpuid_t target_cpu)
{
    interrupts_arch_ipi_send(target_cpu);
}

void interrupts_cpu_enable(irqid_t int_id, bool en)
{
    interrupts_arch_enable(int_id, en);
}

/*
    The following APIs are implemented with the weak attribute since they
    can be used for platforms and architectures that use a single unique ID
    for the hypervisor APIs.

    Other architectures, like TC4, that use different mechanisms for IPIs
    resulting in different ID per core or VM, should implement these APIs
    at the architectural level.
*/

__attribute__((weak)) bool interrupts_ipi_check(void)
{
    return interrupts_arch_check(interrupts_ipi_id);
}

__attribute__((weak)) void interrupts_ipi_clear(void)
{
    interrupts_arch_clear(interrupts_ipi_id);
}

#ifdef IPI_CPU_MSG
__attribute__((weak)) void interrupts_arch_ipi_init(void)
{
    if (cpu_is_master()) {
        interrupts_ipi_id = interrupts_reserve(IPI_CPU_MSG, (irq_handler_t)cpu_msg_handler);
        if (interrupts_ipi_id == INVALID_IRQID) {
            ERROR("Failed to reserve IPI_CPU_MSG interrupt");
        }
    }
}
#endif

void interrupts_init(void)
{
    interrupts_arch_init();

    interrupts_arch_ipi_init();

    cpu_sync_barrier(&cpu_glb_sync);

    interrupts_cpu_enable(interrupts_ipi_id, true);
}

static inline bool interrupt_assigned_to_hyp(irqid_t int_id)
{
    return (int_id < MAX_INTERRUPT_HANDLERS) && (interrupt_handlers[int_id] != NULL);
}

/**
 * @brief For a given interrupt intp_id, return if this interrupt is already reserved by VMM or any
 *        VM
 *
 * @param int_id interrupt ID
 * @return true if interrupt is reserved
 * @return false if interrupt is NOT reserved
 */
static inline bool interrupt_assigned(irqid_t int_id)
{
    return bitmap_get(global_interrupt_bitmap, int_id);
}

enum irq_res interrupts_handle(irqid_t int_id)
{
    if (interrupts_arch_irq_is_forwardable(int_id) && vm_has_interrupt(cpu()->vcpu->vm, int_id)) {
        vcpu_inject_hw_irq(cpu()->vcpu, int_id);

        return FORWARD_TO_VM;

    } else if (interrupt_assigned_to_hyp(int_id)) {
        interrupt_handlers[int_id](int_id);

        return HANDLED_BY_HYP;

    } else {
        ERROR("received unknown interrupt id = %d", int_id);
    }
}

bool interrupts_vm_assign(struct vm* vm, irqid_t id)
{
    bool ret = false;

    spin_lock(&irq_reserve_lock);
    if (!interrupts_arch_conflict(global_interrupt_bitmap, id)) {
        ret = true;
        interrupts_arch_vm_assign(vm, id);

        bitmap_set(vm->interrupt_bitmap, id);
        bitmap_set(global_interrupt_bitmap, id);
    }
    spin_unlock(&irq_reserve_lock);

    return ret;
}

irqid_t interrupts_reserve(irqid_t pint_id, irq_handler_t handler)
{
    irqid_t int_id = INVALID_IRQID;

    spin_lock(&irq_reserve_lock);
    if ((pint_id < MAX_INTERRUPT_LINES) && !interrupt_assigned(pint_id)) {
        bitmap_set(global_interrupt_bitmap, pint_id);

        irqid_t tmp_id = interrupts_arch_reserve(pint_id);
        if ((tmp_id != INVALID_IRQID) && (tmp_id < MAX_INTERRUPT_HANDLERS)) {
            int_id = tmp_id;
            interrupt_handlers[int_id] = handler;
        }
    }
    spin_unlock(&irq_reserve_lock);

    return int_id;
}
