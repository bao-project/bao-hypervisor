/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Gero Schwaericke <gero.schwaericke@tum.de>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <page_table.h>
#include <arch/sysregs.h>

uint64_t CPU_MASTER __attribute__((section(".data")));

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(uint64_t cpuid, uint64_t load_addr)
{   
    cpu.arch.mpidr = MRS(MPIDR_EL1);
    if (cpuid == CPU_MASTER) {
        /* power on necessary, but still sleeping, secondary cpu cores
         * Assumes CPU zero is doing this */
        for (int cpu_core_id = 0; cpu_core_id < platform.cpu_num;
             cpu_core_id++) {
            if(cpu_core_id == cpuid) continue;
            uint64_t mpdir = cpu_id_to_mpidr(cpu_core_id);
            // TODO: pass config addr in contextid (x0 register)
            int result = psci_cpu_on(mpdir, load_addr, 0);
            if (!(result == PSCI_E_SUCCESS || result == PSCI_E_ALREADY_ON)) {
                ERROR("cant wake up cpu %d", cpu_core_id);
            }
        }
    }
}

uint64_t cpu_id_to_mpidr(uint64_t id)
{
    return platform_arch_cpuid_to_mpdir(&platform, id);
}


int64_t cpu_mpidr_to_id(uint64_t mpidr)
{
    return platform_arch_mpidr_to_cpuid(&platform, mpidr);
}
    

void cpu_arch_idle()
{
    int64_t err = psci_power_down(PSCI_WAKEUP_IDLE);
    if(err) {
        switch (err) {
            case PSCI_E_NOT_SUPPORTED:
                /**
                 * If power down is not supported let's just wait for an interrupt
                 */
                asm volatile("wfi");
                break;
            default:
                ERROR("PSCI cpu%d power down failed with error %ld", cpu.id, err);
        }
    }

    /**
     * Power down was sucessful but did not jump to requested entry
     * point. Manually rewind stack and jump to idle wake up.
     */
    asm volatile("mov sp, %0\n\r" ::"r"(&cpu.stack[STACK_SIZE]));
    cpu_idle_wakeup();
}
