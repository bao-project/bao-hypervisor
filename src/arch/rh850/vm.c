/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <config.h>
#include <list.h>
#include <mem.h>
#include <platform.h>
#include <string.h>
#include <vm.h>
#include <arch/srs.h>
#include <arch/vintc.h>

void vm_arch_init(struct vm* vm, const struct vm_config* vm_config)
{
    UNUSED_ARG(vm);
    /* set EIPC with VM entry address */
    set_eipc((unsigned long)(vm_config->entry));

    /* set xxPSW.EBV */
    set_eipsw(0x8000);
    set_fepsw(0x8000);
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    vintc_init(vcpu);
    vbootctrl_init(vcpu);
    set_gmpeid(vcpu->id);
    
    /* set EIPSWH.GPID */
    set_eipswh(get_eipswh() | (vm->id << 8));

    // TODO: Need to set FEPSWH.GPID ?
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    memset(&vcpu->regs, 0, sizeof(struct arch_regs));

    vcpu_writepc(vcpu, entry);
    set_eipc(entry);
    set_gmpeid(vcpu->id);

    vintc_vcpu_reset(vcpu);
}

bool vcpu_arch_is_on(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);
    return true;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    if (reg > 32) {
        ERROR("reading register out of bounds");
    }

    return vcpu->regs.gp_regs.r[reg];
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    if (reg > 32) {
        ERROR("writing register out of bounds");
    }

    vcpu->regs.gp_regs.r[reg] = val;
}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.pc;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long val)
{
    vcpu->regs.pc = val;
}

void vcpu_restore_state(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);
    ERROR("%s not implemented", __func__);
}

void vcpu_save_state(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);
    ERROR("%s not implemented", __func__);
}

bool vm_arch_reset(struct vm* vm)
{
    vintc_vm_reset(vm);
    return true;
}
