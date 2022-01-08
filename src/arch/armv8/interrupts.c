/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bao.h>
#include <interrupts.h>

#include <cpu.h>
#include <platform.h>
#include <arch/gic.h>
#include <mem.h>
#include <arch/sysregs.h>
#include <vm.h>
#include <arch/sdei.h>
#include <arch/psci.h>

#ifndef GIC_VERSION
#error "GIC_VERSION not defined for this platform"
#endif

extern void sdei_ipi_handler();

void interrupts_arch_init()
{
    gic_init();
    interrupts_cpu_enable(platform.arch.gic.maintenance_id, true);

    if(sdei_version() != SDEI_NOT_SUPPORTED) {
        int32_t evt = platform.arch.sdei_ipi_event;
         sdei_event_register(evt, (uint64_t) sdei_ipi_handler,
            (uint64_t) &cpu.arch.sdei_evt_is_active, 
            SDEI_F_EP_ABS | SDEI_F_RM_PE, cpu.arch.mpidr);
        sdei_event_enable(evt);
        sdei_pe_unmask();
        cpu.interface.arch.uses_sdei_ipi = true;
    }
}

void interrupts_arch_ipi_send(cpuid_t target_cpu, irqid_t ipi_id)
{
    if(cpu_if(target_cpu)->arch.uses_sdei_ipi) {
        sdei_event_signal(platform.arch.sdei_ipi_event, 
            cpu_id_to_mpidr(target_cpu));
    } else {
        if (ipi_id < GIC_MAX_SGIS) gic_send_sgi(target_cpu, ipi_id);
    }
}

void interrupts_arch_enable(irqid_t int_id, bool en)
{
    gic_set_enable(int_id, en);
    gic_set_prio(int_id, 0x01);
    if (GIC_VERSION == GICV2) {
        gicd_set_trgt(int_id, 1 << cpu.id);
    } else {
        gicd_set_route(int_id, cpu.arch.mpidr);
    }
}

bool interrupts_arch_check(irqid_t int_id)
{
    if(int_id == IPI_CPU_MSG && cpu.interface.arch.uses_sdei_ipi) {
        return cpu.arch.sdei_evt_is_active;
    } else {
        return gic_get_pend(int_id);
    }
}

inline bool interrupts_arch_conflict(bitmap_t* interrupt_bitmap, irqid_t int_id)
{
    return (bitmap_get(interrupt_bitmap, int_id) && int_id > GIC_CPU_PRIV);
}

void interrupts_arch_clear(irqid_t int_id)
{
    if(int_id == IPI_CPU_MSG && cpu.interface.arch.uses_sdei_ipi) {
        cpu.arch.sdei_evt_is_active = false;
        vcpu_arch_reset_vttbr(cpu.vcpu);
    } else {
        gic_set_act(int_id, false);
        gic_set_pend(int_id, false);
    }
}

void interrupts_arch_vm_assign(struct vm *vm, irqid_t id)
{
    vgic_set_hw(vm, id);
}
