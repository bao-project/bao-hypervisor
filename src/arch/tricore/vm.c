/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/csfrs.h>
#include <arch/vir.h>
#include <arch/instructions.h>
#include <string.h>
#include <config.h>
#include <platform.h>

void vm_arch_init(struct vm* vm, const struct vm_config* vm_config)
{
    (void) vm;
    (void) vm_config;

    if (vm->master == cpu()->id) {
        vir_init(vm, &vm_config->platform.arch.vir);
    }
    cpu_sync_and_clear_msgs(&vm->sync);
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    (void) vcpu;
    (void) vm;

    vir_vcpu_init(vcpu);
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    (void) vcpu;
    (void) entry;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    (void) vcpu;
    (void) reg;
    return 0;
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    (void) vcpu;
    (void) reg;
    (void) val;

}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.pc;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
{
    vcpu->regs.pc = pc;
}

void vcpu_arch_run(struct vcpu* vcpu)
{
    (void)vcpu;
    /* if (vcpu->arch.scr_ctx.state == STARTED) { */
    if (1) {
        vcpu_arch_entry();
    } else {
        cpu_idle();
    }
}
