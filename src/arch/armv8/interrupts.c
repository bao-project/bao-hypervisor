/**
 * Bao, a Lightweight Static Partitioning Hypervisor
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

#include <cpu.h>
#include <platform.h>
#include <arch/gic.h>
#include <mem.h>
#include <arch/sysregs.h>
#include <vm.h>

void interrupts_arch_init()
{
    if (cpu.id == CPU_MASTER) {
        mem_map_dev(&cpu.as, (void *)&gicc, platform.arch.gic.gicc_addr,
                    NUM_PAGES(sizeof(gicc)));
        mem_map_dev(&cpu.as, (void *)&gich, platform.arch.gic.gich_addr,
                    NUM_PAGES(sizeof(gich)));
        mem_map_dev(&cpu.as, (void *)gich_alias,
                    platform.arch.gic.gich_alias_addr,
                    NUM_PAGES(sizeof(gich) * 8));
        mem_map_dev(&cpu.as, (void *)&gicd, platform.arch.gic.gicd_addr,
                    NUM_PAGES(sizeof(gicd)));
    }

    /* Wait for core 0 to map interupt controller */
    cpu_sync_barrier(&cpu_glb_sync);

    if (cpu.id == CPU_MASTER) gic_init();

    gic_cpu_init();

    interrupts_cpu_enable(platform.arch.gic.maintenance_id, true);
}

void interrupts_arch_ipi_send(uint64_t target_cpu, uint64_t ipi_id)
{
    if (ipi_id < GIC_MAX_SGIS) gicd_send_sgi(target_cpu, ipi_id);
}

void interrupts_arch_cpu_enable(bool en)
{
    if (en)
        asm volatile("msr DAIFClr, %0\n" ::"I"(PSTATE_DAIF_I_BIT));
    else
        asm volatile("msr DAIFSet, %0\n" ::"I"(PSTATE_DAIF_I_BIT));
}

void interrupts_arch_enable(uint64_t int_id, bool en)
{
    gicd_set_enable(int_id, en);
    gicd_set_prio(int_id, 0x7F);
    gicd_set_trgt(int_id, 1 << cpu.id);
}

bool interrupts_arch_check(uint64_t int_id)
{
    return gicd_get_state(int_id) & PEND;
}

void interrupts_arch_clear(uint64_t int_id)
{
    gicd_set_pend(int_id, false);
}

void interrupts_arch_vm_assign(vm_t *vm, uint64_t id)
{
    vgic_set_hw(vm, id);
}

void interrupts_arch_vm_inject(vm_t *vm, uint64_t id, uint64_t source)
{
    vgicd_inject(&vm->arch.vgicd, id, source);
}
