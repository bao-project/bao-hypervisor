/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <platform.h>
#include <arch/psci.h>
#include <arch/sysregs.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr) {
    if (cpuid == CPU_MASTER) {
        /* power on necessary, but still sleeping, secondary cpu cores
         * Assumes CPU zero is doing this */
        for (size_t cpu_core_id = 0; cpu_core_id < platform.cpu_num;
             cpu_core_id++) {
            if(cpu_core_id == cpuid) continue;
            unsigned long mpidr = cpu_id_to_mpidr(cpu_core_id);
            // TODO: pass config addr in contextid (x0 register)
            int32_t result = psci_cpu_on(mpidr, load_addr, 0);
            if (!(result == PSCI_E_SUCCESS || result == PSCI_E_ALREADY_ON)) {
                ERROR("cant wake up cpu %d", cpu_core_id);
            }
        }
    }
}

void cpu_arch_profile_idle() {

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
                ERROR("PSCI cpu%d power down failed with error %ld", cpu()->id, err);
        }
    }

    /**
     * Power down was sucessful but did not jump to requested entry
     * point. Just return to the architectural
     */
}
