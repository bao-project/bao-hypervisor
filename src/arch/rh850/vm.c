/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <config.h>
#include <string.h>
#include <vm.h>
#include <vintc.h>
#include <platform.h>
#include <vipir.h>
#include <vbootctrl.h>

void vm_arch_init(struct vm* vm, const struct vm_config* vm_config)
{
    UNUSED_ARG(vm_config);

    /* All VMs use MPID6 for memory protection */
    srs_mpid6_write(vm->id);

    vintc_init(vm);
    vipir_init(vm);
    vbootctrl_init(vm);
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(vcpu);
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    struct vm* vm = vcpu->vm;

    memset(&vcpu->regs, 0, sizeof(struct arch_regs));

    vcpu_writepc(vcpu, entry);
    srs_eipc_write(entry);

    vcpu->arch.started = vcpu->id == 0 ? true : false;

    /* Bao fixes the VMID as SPID to isolate VM memory regions */
    srs_gmspid_write(vm->id);
    srs_gmspidlist_write(0x0);

    srs_gmmpm_write(GMMPM_GMPE);

    unsigned long eipswh = srs_eipswh_read() & ~EIPSWH_GPID_MASK;
    srs_eipswh_write(eipswh | (vm->id << EIPSWH_GPID_OFF));

    unsigned long fepswh = srs_fepswh_read() & ~FEPSWH_GPID_MASK;
    srs_fepswh_write(fepswh | (vm->id << FEPSWH_GPID_OFF));

    srs_gmpeid_write(vcpu->id);

    /* clear guest-context exception registers */
    srs_gmeipc_write(0x0);
    srs_gmfepc_write(0x0);
    srs_gmmea_write(0x0);
    srs_gmmei_write(0x0);
    srs_gmeiic_write(0x0);
    srs_gmfeic_write(0x0);

    vintc_vcpu_reset(vcpu);
}

bool vcpu_arch_is_on(struct vcpu* vcpu)
{
    return vcpu->arch.started;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    if (reg > 32) {
        ERROR("reading register out of bounds");
    }

    /* r0 is always 0x0 */
    return reg == 0 ? 0 : vcpu->regs.gp_regs.r[reg];
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    if (reg > 32) {
        ERROR("writing register out of bounds");
    }

    /* r0 is always 0x0 */
    if (reg != 0) {
        vcpu->regs.gp_regs.r[reg] = val;
    }
}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.pc;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long val)
{
    vcpu->regs.pc = val;
}
