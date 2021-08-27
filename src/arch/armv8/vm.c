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
#include <page_table.h>
#include <arch/sysregs.h>
#include <fences.h>
#include <arch/tlb.h>
#include <string.h>

void vm_arch_init(vm_t* vm, const vm_config_t* config)
{
    if (vm->master == cpu.id) {
        vgic_init(vm, &config->platform.arch.gic);
    }
}

vcpu_t* vm_get_vcpu_by_mpidr(vm_t* vm, uint64_t mpidr)
{
    list_foreach(vm->vcpu_list, vcpu_t, vcpu)
    {
        if ((vcpu->arch.vmpidr & MPIDR_AFF_MSK) == (mpidr & MPIDR_AFF_MSK))  {
            return vcpu;
        }
    }

    return NULL;
}

static uint64_t vm_cpuid_to_mpidr(vm_t* vm, uint64_t cpuid)
{
    return platform_arch_cpuid_to_mpdir(&vm->config->platform, cpuid);
}

void vcpu_arch_init(vcpu_t* vcpu, vm_t* vm)
{
    vcpu->arch.vmpidr = vm_cpuid_to_mpidr(vm, vcpu->id);
    MSR(VMPIDR_EL2, vcpu->arch.vmpidr);

    vcpu->arch.psci_ctx.state = vcpu->id == 0 ? ON : OFF;

    uint64_t root_pt_pa;
    mem_translate(&cpu.as, vm->as.pt.root, &root_pt_pa);
    MSR(VTTBR_EL2, ((vm->id << VTTBR_VMID_OFF) & VTTBR_VMID_MSK) |
                       (root_pt_pa & ~VTTBR_VMID_MSK));

    ISB();  // make sure vmid is commited befor tlbi
    tlb_vm_inv_all(vm->id);

    vgic_cpu_init(vcpu);
}

void vcpu_arch_reset(vcpu_t* vcpu, uint64_t entry)
{
    memset(vcpu->regs, 0, sizeof(struct arch_regs));

    vcpu->regs->elr_el2 = entry;
    vcpu->regs->spsr_el2 = SPSR_EL1h | SPSR_F | SPSR_I | SPSR_A | SPSR_D;

    MSR(CNTVOFF_EL2, 0);

    /**
     *  See ARMv8-A ARM section D1.9.1 for registers that must be in a known
     * state at reset.
     */
    MSR(SCTLR_EL1, SCTLR_RES1);
    MSR(CNTKCTL_EL1, 0);
    MSR(PMCR_EL0, 0);

    /**
     *  TODO: ARMv8-A ARM mentions another implementation optional registers
     * that reset to a known value.
     */
}

uint64_t vcpu_readreg(vcpu_t* vcpu, uint64_t reg)
{
    if (reg > 30) return 0;
    return vcpu->regs->x[reg];
}

void vcpu_writereg(vcpu_t* vcpu, uint64_t reg, uint64_t val)
{
    if (reg > 30) return;
    vcpu->regs->x[reg] = val;
}

uint64_t vcpu_readpc(vcpu_t* vcpu)
{
    return vcpu->regs->elr_el2;
}

void vcpu_writepc(vcpu_t* vcpu, uint64_t pc)
{
    vcpu->regs->elr_el2 = pc;
}

void vcpu_arch_run(vcpu_t* vcpu)
{
    // TODO: consider using TPIDR_EL2 to store vcpu pointer
    if (vcpu->arch.psci_ctx.state == ON) {
        vcpu_arch_entry();
    } else {
        cpu_idle();
    }
    
}
