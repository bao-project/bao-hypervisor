/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file interrupts.c
 * @brief The source file contains the interrupt management's implementation.
 * 
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

/**
 * @brief Send an inter-processor interrupt to a target CPU
 * @param target_cpu ID of the CPU receiving the IPI. 
 * @see interrupts_arch_ipi_send(), cpuid_t
 * 
 */
void interrupts_cpu_sendipi(cpuid_t target_cpu)
{
    interrupts_arch_ipi_send(target_cpu);
}

/**
 * @brief Enable or disable an interrupt line
 * @param int_id Interrupt ID to enable/disable
 * @param en true to enable, false to disable
 * @see interrupts_arch_enable(), irqid_t
 * 
 */
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

/**
 * @brief Check if an IPI is pending (weak implementation)
 * @return bool true if an IPI is pending, false otherwise
 * @see interrupts_arch_check(), interrupts_ipi_id, irqid_t
 * 
 */
__attribute__((weak)) bool interrupts_ipi_check(void)
{
    return interrupts_arch_check(interrupts_ipi_id);
}

/**
 * @brief Clear a pending IPI (weak implementation)
 * @see interrupts_arch_clear(), interrupts_ipi_id, irqid_t
 * 
 */
__attribute__((weak)) void interrupts_ipi_clear(void)
{
    interrupts_arch_clear(interrupts_ipi_id);
}

#ifdef IPI_CPU_MSG
/**
 * @brief Initialize IPI support (weak implementation)
 * 
 * Reserves an interrupt source for CPU-to-CPU messaging if running
 * on the master CPU.
 * 
 * @see cpu_is_master(), interrupts_reserve(), ERROR(), INVALID_IRQID, IPI_CPU_MSG
 * @see irq_handler_t, irqid_t, irq_handler_t
 * 
 */
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

/**
 * @brief Initialize the interrupt subsystem
 * 
 * Performs architecture-specific interrupt initialization,
 * sets up IPI support, synchronizes all CPUs and enables
 * the master's IPI interrupt source for messaging.
 * 
 * @see interrupts_arch_init(), interrupts_arch_ipi_init(), cpu_sync_barrier()
 * @see interrupts_cpu_enable(), cpu_synctoken, irqid_t
 * 
 */
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
 * @brief Identify the assignment of an interrupt (to a VM or HYP)
 *
 * @param int_id interrupt ID
 * @return true if interrupt is reserved
 * @return false if interrupt is NOT reserved
 * @see bitmap_get(), bitmap_granule_t, irqid_t
 * 
 */
static inline bool interrupt_assigned(irqid_t int_id)
{
    return bitmap_get(global_interrupt_bitmap, int_id);
}

/**
 * @brief Handle interrupts
 *
 * Routes interrupts to either a VM (if assigned), the hypervisor
 * (if a handler exists), or reports an error for unassigned interrupt.
 *
 * @param int_id ID of the interrupt to handle
 * @return enum irq_res FORWARD_TO_VM if sent to VM
 * @return enum irq_res HANDLED_BY_HYP if handled by hypervisor
 * @return ERROR if the interrupt ID is not assigned.
 * @see vm_has_interrupt(), vcpu_inject_hw_irq(), vcpu, cpu, ERROR(), irqid_t, vm
 * @see irq_res, irq_handler_t
 * 
 */
enum irq_res interrupts_handle(irqid_t int_id)
{
    if (vm_has_interrupt(cpu()->vcpu->vm, int_id)) {
        vcpu_inject_hw_irq(cpu()->vcpu, int_id);

        return FORWARD_TO_VM;

    } else if (interrupt_assigned_to_hyp(int_id)) {
        interrupt_handlers[int_id](int_id);

        return HANDLED_BY_HYP;

    } else {
        ERROR("received unassigned interrupt id = %d", int_id);
    }
}

/**
 * @brief Assign an interrupt to a VM
 *
 * Attempts to assign an interrupt line to a VM if there are no conflicts.
 * Updates both the VM's local interrupt bitmap and the global interrupt bitmap.
 *
 * @param vm Pointer to the VM to assign the interrupt to
 * @param id ID of the interrupt to assign
 * @return bool true if assignment successful, false if conflict exists
 * @see spin_lock()/spin_unlock(), interrupts_arch_conflict(), interrupts_arch_vm_assign(), bitmap_set()
 * 
 */
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

/**
 * @brief Reserve an interrupt source for the hypervisor
 *
 * Attempts to reserve an interrupt source for hypervisor use and register
 * its handler. Checks for conflicts with existing assignments.
 *
 * @param pint_id Physical interrupt ID to be reserved
 * @param handler Function pointer to the interrupt handler
 * @return irqid_t Virtual interrupt ID if successful, INVALID_IRQID on failure
 * 
 * @see spin_lock(), spin_unlock(), interrupt_assigned(), bitmap_set()
 * @see interrupts_arch_reserve(), MAX_INTERRUPT_LINES, MAX_INTERRUPT_HANDLERS
 * @see irqid_t, bitmap_t, spinlock_t, INVALID_IRQID
 * 
 */
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
