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

static void psci_save_state(enum wakeup_reason wakeup_reason)
{
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
     * Although the real PSCI implementation is responsible for managing cache state, make sure the
     * saved state is in memory as we'll use this on wake up before enabling cache to restore basic
     * processor state.
     */
    cache_flush_range((vaddr_t)&cpu()->arch.profile.psci_off_state,
        sizeof(cpu()->arch.profile.psci_off_state));

    gicc_save_state(&cpu()->arch.profile.psci_off_state.gicc_state);
}

static void psci_restore_state(void)
{
    /**
     * The majority of the state is already restored in assembly routine psci_boot_entry.
     */

    gicc_restore_state(&cpu()->arch.profile.psci_off_state.gicc_state);
}

static void psci_wake_from_powerdown(void)
{
    if (cpu()->vcpu == NULL) {
        ERROR("cpu woke up but theres no vcpu to run");
    }

    vcpu_arch_reset(cpu()->vcpu, cpu()->vcpu->arch.psci_ctx.entrypoint);
    vcpu_writereg(cpu()->vcpu, 0, cpu()->vcpu->arch.psci_ctx.context_id);
    cpu_powerdown_wakeup();
}

void psci_wake_from_off(void);

void (*psci_wake_handlers[PSCI_WAKEUP_NUM])(void) = {
    [PSCI_WAKEUP_CPU_OFF] = psci_wake_from_off,
    [PSCI_WAKEUP_POWERDOWN] = psci_wake_from_powerdown,
};

void psci_wake(uint32_t handler_id)
{
    psci_restore_state();

    if (handler_id < PSCI_WAKEUP_NUM) {
        psci_wake_handlers[handler_id]();
    } else {
        ERROR("unknown reason for cpu wake up");
    }
}

int32_t psci_standby()
{
    /* We've observed that some platforms behave unexpectedly when performing
     * standby. In these cases, after standby, the CPU cores are not awaken
     * by interrupts. */
    if (DEFINED(PLAT_PSCI_STANDBY_NOT_SUPPORTED)) {
        /**
         * If standby is not supported let's just wait for an interrupt
         */
        __asm__ volatile("wfi");
        return PSCI_E_SUCCESS;
    }
    /* only apply request to core level */
    uint32_t pwr_state_aux = PSCI_POWER_STATE_LVL_0 | PSCI_STATE_TYPE_STANDBY;

    return psci_cpu_suspend(pwr_state_aux, 0, 0);
}

int32_t psci_power_down()
{
    /* We've observed that some platforms behave unexpectedly when performing
     * power down. In these cases, after powerdown, the CPU cores are not awaken
     * by interrupts as expected by Bao. */
    if (DEFINED(PLAT_PSCI_POWERDOWN_NOT_SUPPORTED)) {
        return psci_standby();
    }

    extern void psci_boot_entry(unsigned long x0);

    uint32_t pwr_state_aux = PSCI_POWER_STATE_LVL_0 | PSCI_STATE_TYPE_POWERDOWN;

    psci_save_state(PSCI_WAKEUP_POWERDOWN);
    paddr_t cntxt_paddr;
    paddr_t psci_wakeup_addr;
    mem_translate(&cpu()->as, (vaddr_t)&cpu()->arch.profile.psci_off_state, &cntxt_paddr);
    mem_translate(&cpu()->as, (vaddr_t)&psci_boot_entry, &psci_wakeup_addr);

    return psci_cpu_suspend(pwr_state_aux, psci_wakeup_addr, cntxt_paddr);
}

int32_t psci_cpu_suspend(uint32_t power_state, unsigned long entrypoint, unsigned long context_id)
{
    return (int32_t)smc_call(PSCI_CPU_SUSPEND, power_state, entrypoint, context_id, NULL);
}

int32_t psci_cpu_on(unsigned long target_cpu, unsigned long entrypoint, unsigned long context_id)
{
    return (int32_t)smc_call(PSCI_CPU_ON, target_cpu, entrypoint, context_id, NULL);
}
