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

#include <vmm.h>
#include <arch/sysregs.h>
#include <interrupts.h>

void vmm_arch_init()
{
    /**
     * Check available physical address range which will limit
     * IPA size. Patch 2-stage page table descriptors if this forces
     * the initial lookup to level 1.
     *
     * In multi-cluster heterogenous we only support the minimum parange 
     * for a vm's physicall adress space.
     * TODO: we could make this more dynamic and adapt it to each virtual 
     * machine.
     */

    static uint64_t min_parange = 0b111;
    static spinlock_t lock = SPINLOCK_INITVAL;

    uint64_t temp_parange = MRS(ID_AA64MMFR0_EL1) & ID_AA64MMFR0_PAR_MSK;
    spin_lock(&lock);
    if(temp_parange < min_parange) {
        min_parange = temp_parange;
    }
    spin_unlock(&lock);

    cpu_sync_barrier(&cpu_glb_sync);

    if (cpu.id == CPU_MASTER) {
        parange = min_parange;
        if (parange_table[parange] < 44) {
            for (int i = 0; i < vm_pt_dscr->lvls - 1; i++) {
                vm_pt_dscr->lvl_wdt[i] = vm_pt_dscr->lvl_wdt[i + 1];
                vm_pt_dscr->lvl_off[i] = vm_pt_dscr->lvl_off[i + 1];
                vm_pt_dscr->lvl_term[i] = vm_pt_dscr->lvl_term[i + 1];
            }
            vm_pt_dscr->lvl_wdt[0] = parange_table[parange];
            vm_pt_dscr->lvls = vm_pt_dscr->lvls - 1;
        }
    }

    cpu_sync_barrier(&cpu_glb_sync);

    uint64_t vtcr = VTCR_RES1 | ((parange << VTCR_PS_OFF) & VTCR_PS_MSK) |
                    VTCR_TG0_4K | VTCR_ORGN0_WB_RA_WA | VTCR_IRGN0_WB_RA_WA |
                    VTCR_T0SZ(64 - parange_table[parange]) | VTCR_SH0_IS |
                    ((parange_table[parange] < 44) ? VTCR_SL0_12 : VTCR_SL0_01);

    MSR(VTCR_EL2, vtcr);

    uint64_t hcr = HCR_VM_BIT | HCR_RW_BIT | HCR_IMO_BIT | HCR_FMO_BIT |
                   HCR_TSC_BIT; /* trap smc */

    MSR(HCR_EL2, hcr);
}
