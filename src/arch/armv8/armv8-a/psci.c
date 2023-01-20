/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/psci.h>
#include <arch/smc.h>
#include <vm.h>
#include <cpu.h>
#include <mem.h>

extern uint8_t root_l1_flat_pt;

static void psci_save_state(enum wakeup_reason wakeup_reason){

    cpu()->arch.profile.psci_off_state.tcr_el2 = sysreg_tcr_el2_read();
    cpu()->arch.profile.psci_off_state.ttbr0_el2 = sysreg_ttbr0_el2_read();
    cpu()->arch.profile.psci_off_state.mair_el2 = sysreg_mair_el2_read();
    cpu()->arch.profile.psci_off_state.cptr_el2 = sysreg_cptr_el2_read();
    cpu()->arch.profile.psci_off_state.hcr_el2 = sysreg_hcr_el2_read();
    cpu()->arch.profile.psci_off_state.vmpidr_el2 = sysreg_vmpidr_el2_read();
    cpu()->arch.profile.psci_off_state.vtcr_el2 = sysreg_vtcr_el2_read();
    cpu()->arch.profile.psci_off_state.vttbr_el2 = sysreg_vttbr_el2_read();
    mem_translate(&cpu()->as, (vaddr_t)&root_l1_flat_pt,
                    &cpu()->arch.profile.psci_off_state.flat_map);
    cpu()->arch.profile.psci_off_state.wakeup_reason = wakeup_reason;

    /**
     * Although the real PSCI implementation is responsible for managing cache
     * state, make sure the saved state is in memory as we'll use this on wake
     * up before enabling cache to restore basic processor state. 
     */
    cache_flush_range((vaddr_t)&cpu()->arch.profile.psci_off_state,
                    sizeof(cpu()->arch.profile.psci_off_state));

    gicc_save_state(&cpu()->arch.profile.psci_off_state.gicc_state);
}


static void psci_restore_state(){

    /**
     * The majority of the state is already restored in assembly routine
     *  psci_boot_entry.
     */
    
    gicc_restore_state(&cpu()->arch.profile.psci_off_state.gicc_state);
}

void psci_wake_from_powerdown(){

    if(cpu()->vcpu == NULL){
        ERROR("cpu woke up but theres no vcpu to run");
    }

    vcpu_arch_reset(cpu()->vcpu, cpu()->vcpu->arch.psci_ctx.entrypoint);
    vcpu_writereg(cpu()->vcpu, 0, cpu()->vcpu->arch.psci_ctx.context_id);
    vcpu_run(cpu()->vcpu);
}

void psci_wake_from_idle(){

    cpu_idle_wakeup();

}

void psci_wake_from_off();

void (*psci_wake_handlers[PSCI_WAKEUP_NUM])(void) = {
    [PSCI_WAKEUP_CPU_OFF] = psci_wake_from_off,
    [PSCI_WAKEUP_POWERDOWN] = psci_wake_from_powerdown,
    [PSCI_WAKEUP_IDLE] = psci_wake_from_idle,
};

void psci_wake(uint32_t handler_id)
{    

    psci_restore_state();

    if(handler_id < PSCI_WAKEUP_NUM){
        psci_wake_handlers[handler_id]();
    } else {
        ERROR("unkown reason for cpu wake up");
    }

}

int32_t psci_standby(){
    /* only apply request to core level */
    uint32_t pwr_state_aux = PSCI_POWER_STATE_LVL_0 | PSCI_STATE_TYPE_STANDBY;

    return psci_cpu_suspend(pwr_state_aux, 0, 0);
}

int32_t psci_power_down(enum wakeup_reason reason){

    extern void psci_boot_entry(unsigned long x0);

    uint32_t pwr_state_aux = PSCI_POWER_STATE_LVL_0 | PSCI_STATE_TYPE_POWERDOWN;

    psci_save_state(reason);
    paddr_t cntxt_paddr;
    paddr_t psci_wakeup_addr;
    mem_translate(&cpu()->as, (vaddr_t)&cpu()->arch.profile.psci_off_state, &cntxt_paddr);
    mem_translate(&cpu()->as, (vaddr_t)&psci_boot_entry, &psci_wakeup_addr);

    return psci_cpu_suspend(pwr_state_aux, psci_wakeup_addr, cntxt_paddr);
}

int32_t psci_cpu_suspend(uint32_t power_state, unsigned long entrypoint, 
                        unsigned long context_id)
{

    return smc_call(PSCI_CPU_SUSPEND, power_state, entrypoint, context_id, NULL);
}

int32_t psci_cpu_on(unsigned long target_cpu, unsigned long entrypoint, 
                    unsigned long context_id)
{
    return smc_call(PSCI_CPU_ON, target_cpu, entrypoint, context_id, NULL);
}
