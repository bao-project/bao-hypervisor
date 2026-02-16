/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/psci.h>
#include <arch/sysregs.h>
#include <fences.h>
#include <vm.h>
#include <cpu.h>
#include <mem.h>
#include <cache.h>
#include <config.h>

enum { PSCI_MSG_ON };

/* --------------------------------
    SMC Trapping
--------------------------------- */

void psci_wake_from_off(void)
{
    if (cpu()->vcpu == NULL) {
        return;
    }

    /* update vcpu()->psci_ctx */
    spin_lock(&cpu()->vcpu->arch.psci_ctx.lock);
    if (cpu()->vcpu->arch.psci_ctx.state == ON_PENDING) {
        vcpu_arch_reset(cpu()->vcpu, cpu()->vcpu->arch.psci_ctx.entrypoint);
        cpu()->vcpu->arch.psci_ctx.state = ON;
        vcpu_writereg(cpu()->vcpu, 0, cpu()->vcpu->arch.psci_ctx.context_id);
    }
    spin_unlock(&cpu()->vcpu->arch.psci_ctx.lock);
}

static void psci_cpumsg_handler(uint32_t event, uint64_t data)
{
    UNUSED_ARG(data);

    switch (event) {
        case PSCI_MSG_ON:
            psci_wake_from_off();
            break;
        default:
            WARNING("Unknown PSCI IPI event");
            break;
    }
}

CPU_MSG_HANDLER(psci_cpumsg_handler, PSCI_CPUMSG_ID)

static int32_t psci_cpu_suspend_handler(uint32_t power_state, unsigned long entrypoint,
    unsigned long context_id)
{
    /**
     * !! Ignoring the rest of the requested  powerstate for now. This might be a problem howwver
     * since powerlevel and stateid are implementation defined.
     */
    uint32_t state_type = power_state & PSCI_STATE_TYPE_BIT;
    int32_t ret;

    if (state_type) {
        // PSCI_STATE_TYPE_POWERDOWN:
        spin_lock(&cpu()->vcpu->arch.psci_ctx.lock);
        cpu()->vcpu->arch.psci_ctx.entrypoint = entrypoint;
        cpu()->vcpu->arch.psci_ctx.context_id = context_id;
        spin_unlock(&cpu()->vcpu->arch.psci_ctx.lock);
        ret = psci_power_down();
    } else {
        // PSCI_STATE_TYPE_STANDBY:
        ret = psci_standby();
    }

    return ret;
}

static int32_t psci_cpu_off_handler(void)
{
    /**
     *  Right now we only support one vcpu por cpu, so passthrough the request directly to the
     *  monitor psci implementation. Later another vcpu, will call cpu_on on this vcpu()->
     */

    spin_lock(&cpu()->vcpu->arch.psci_ctx.lock);
    cpu()->vcpu->arch.psci_ctx.state = OFF;
    spin_unlock(&cpu()->vcpu->arch.psci_ctx.lock);

    cpu_powerdown();

    spin_lock(&cpu()->vcpu->arch.psci_ctx.lock);
    cpu()->vcpu->arch.psci_ctx.state = ON;
    spin_unlock(&cpu()->vcpu->arch.psci_ctx.lock);

    return PSCI_E_DENIED;
}

static int32_t psci_cpu_on_handler(unsigned long target_cpu, unsigned long entrypoint,
    unsigned long context_id)
{
    int32_t ret;
    struct vm* vm = cpu()->vcpu->vm;
    struct vcpu* target_vcpu = vm_get_vcpu_by_mpidr(vm, target_cpu);

    if (target_vcpu != NULL) {
        bool already_on = true;
        spin_lock(&cpu()->vcpu->arch.psci_ctx.lock);
        if (target_vcpu->arch.psci_ctx.state == OFF) {
            target_vcpu->arch.psci_ctx.state = ON_PENDING;
            target_vcpu->arch.psci_ctx.entrypoint = entrypoint;
            target_vcpu->arch.psci_ctx.context_id = context_id;
            fence_sync_write();
            already_on = false;
        }
        spin_unlock(&cpu()->vcpu->arch.psci_ctx.lock);

        if (already_on) {
            return PSCI_E_ALREADY_ON;
        }

        cpuid_t pcpuid = vm_translate_to_pcpuid(vm, target_vcpu->id);
        if (pcpuid == INVALID_CPUID) {
            ret = PSCI_E_INVALID_PARAMS;
        } else {
            struct cpu_msg msg = { (uint32_t)PSCI_CPUMSG_ID, PSCI_MSG_ON, 0 };
            cpu_send_msg(pcpuid, &msg);
            ret = PSCI_E_SUCCESS;
        }

    } else {
        ret = PSCI_E_INVALID_PARAMS;
    }

    return ret;
}

static int32_t psci_affinity_info_handler(unsigned long target_affinity,
    uint32_t lowest_affinity_level)
{
    /* return ON, if at least one core in the affinity instance: has been enabled with a call to
    CPU_ON, and that core has not called CPU_OFF */

    /* return off if all of the cores in the affinity instance have called CPU_OFF and each of
    these calls has been processed by the PSCI implementation. */

    /*  return ON_PENDING if at least one core in the affinity instance is in the ON_PENDING state
     */

    /**
     * TODO
     */

    UNUSED_ARG(target_affinity);
    UNUSED_ARG(lowest_affinity_level);

    return 0;
}

static int32_t psci_features_handler(uint32_t feature_id)
{
    int32_t ret = PSCI_E_NOT_SUPPORTED;

    switch (feature_id) {
        case PSCI_VERSION:
        case PSCI_CPU_OFF:
        case PSCI_CPU_SUSPEND_SMC32:
        case PSCI_CPU_SUSPEND_SMC64:
        case PSCI_CPU_ON_SMC32:
        case PSCI_CPU_ON_SMC64:
        case PSCI_AFFINITY_INFO_SMC32:
        case PSCI_AFFINITY_INFO_SMC64:
        case PSCI_FEATURES:
            ret = PSCI_E_SUCCESS;
            break;
        default:
            ret = PSCI_E_NOT_SUPPORTED;
            break;
    }

    return ret;
}

int32_t psci_smc_handler(uint32_t smc_fid, unsigned long x1, unsigned long x2, unsigned long x3)
{
    int32_t ret = PSCI_E_NOT_SUPPORTED;

    switch (smc_fid) {
        case PSCI_VERSION:
            ret = PSCI_VERSION_0_2;
            break;

        case PSCI_CPU_OFF:
            ret = psci_cpu_off_handler();
            break;

        case PSCI_CPU_SUSPEND_SMC32:
        case PSCI_CPU_SUSPEND_SMC64:
            ret = psci_cpu_suspend_handler((uint32_t)x1, x2, x3);
            break;

        case PSCI_CPU_ON_SMC32:
        case PSCI_CPU_ON_SMC64:
            ret = psci_cpu_on_handler(x1, x2, x3);
            break;

        case PSCI_AFFINITY_INFO_SMC32:
        case PSCI_AFFINITY_INFO_SMC64:
            ret = psci_affinity_info_handler(x1, (uint32_t)x2);
            break;

        case PSCI_FEATURES:
            ret = psci_features_handler((uint32_t)x1);
            break;

        case PSCI_MIG_INFO_TYPE:
            ret = PSCI_TOS_NOT_PRESENT_MP;
            break;

        default:
            INFO("unknown psci smc_fid 0x%lx", smc_fid);
    }

    return ret;
}
