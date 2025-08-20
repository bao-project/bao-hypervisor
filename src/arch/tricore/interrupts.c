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

void interrupts_arch_init()
{
    ir_init();

    if (cpu_is_master()) {
        ir_cpu_init();
    }

    /* Wait for master core to finish IR initialization */
    cpu_sync_barrier(&cpu_glb_sync);
}

void interrupts_arch_ipi_send(cpuid_t target_cpu)
{
    ir_send_ipi(target_cpu);
}

void interrupts_arch_ipi_init(void)
{
    if (cpu_is_master()) {
        ir_init_ipi();

        for (int i = 0; i < PLAT_CPU_NUM; i++) {
            if (interrupts_reserve((irqid_t)(IPI_CPU_MSG + i), (irq_handler_t)cpu_msg_handler) ==
                INVALID_IRQID) {
                ERROR("Failed to reserve IPI_CPU_MSG interrupt");
            }
        }
    }
    /* Wait for master core to finish IPI initialization */
    cpu_sync_barrier(&cpu_glb_sync);
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    ir_src_enable(int_id, en);
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
    uint32_t vmid = VMID_TO_HWVM(vm->id);
    if (vmid > VM_ARCH_MAX_NUM) {
        ERROR("Unsuported vm id %u > %u", vmid, VM_ARCH_MAX_NUM);
        return;
    }

    ir_assign_int_to_vm(vmid, id);
}

inline irqid_t interrupts_arch_reserve(irqid_t pint_id)
{
    return pint_id;
}
