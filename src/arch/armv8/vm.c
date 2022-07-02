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

#include <vm.h>
#include <arch/sysregs.h>
#include <fences.h>
#include <string.h>
#include <config.h>

void vm_arch_init(struct vm* vm, const struct vm_config* config)
{
    if (vm->master == cpu()->id) {
        vgic_init(vm, &config->platform.arch.gic);
    }
}

struct vcpu* vm_get_vcpu_by_mpidr(struct vm* vm, unsigned long mpidr)
{
    list_foreach(vm->vcpu_list, struct vcpu, vcpu)
    {
        if ((vcpu->arch.vmpidr & MPIDR_AFF_MSK) == (mpidr & MPIDR_AFF_MSK))  {
            return vcpu;
        }
    }

    return NULL;
}

static unsigned long vm_cpuid_to_mpidr(struct vm* vm, vcpuid_t cpuid)
{
    if (cpuid > vm->cpu_num) {
        return ~(~MPIDR_RES1 & MPIDR_RES0_MSK); //return an invlid mpidr by inverting res bits
    }

    unsigned long mpidr = cpuid | MPIDR_RES1;

    if (vm->cpu_num == 1) {
        mpidr |= MPIDR_U_BIT;
    }

    return mpidr;
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    vcpu->arch.vmpidr = vm_cpuid_to_mpidr(vm, vcpu->id);
    sysreg_vmpidr_el2_write(vcpu->arch.vmpidr);

    vcpu_arch_profile_init(vcpu, vm);

    vgic_cpu_init(vcpu);
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    memset(&vcpu->regs, 0, sizeof(struct arch_regs));

    vcpu_subarch_reset(vcpu);

    vcpu_writepc(vcpu, entry);

    sysreg_cntvoff_el2_write(0);

    /**
     *  See ARMv8-A ARM section D1.9.1 for registers that must be in a known
     * state at reset.
     */
    sysreg_sctlr_el1_write(SCTLR_RES1);
    sysreg_cntkctl_el1_write(0);
    sysreg_pmcr_el0_write(0);

    /**
     *  TODO: ARMv8-A ARM mentions another implementation optional registers
     * that reset to a known value.
     */
}

void vcpu_arch_run(struct vcpu* vcpu)
{
    if (vcpu_arch_profile_on(vcpu)) {
        vcpu_arch_entry();
    } else {
        cpu_idle();
    }   
}
