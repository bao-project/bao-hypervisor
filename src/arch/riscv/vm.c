/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <page_table.h>
#include <arch/csrs.h>
#include <irqc.h>
#include <arch/instructions.h>
#include <string.h>
#include <config.h>

void vm_arch_init(struct vm* vm, const struct vm_config* config)
{
    paddr_t root_pt_pa;
    mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &root_pt_pa);

    unsigned long hgatp = (root_pt_pa >> PAGE_SHIFT) | (HGATP_MODE_DFLT) |
        ((vm->id << HGATP_VMID_OFF) & HGATP_VMID_MSK);

    csrs_hgatp_write(hgatp);

    virqc_init(vm, &config->platform.arch.irqc);
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    UNUSED_ARG(vm);

    vcpu->arch.sbi_ctx.lock = SPINLOCK_INITVAL;
    vcpu->arch.sbi_ctx.state = vcpu->id == 0 ? STARTED : STOPPED;
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    memset(&vcpu->regs, 0, sizeof(struct arch_regs));

    csrs_sscratch_write((uintptr_t)&vcpu->regs);

    vcpu->regs.hstatus = HSTATUS_SPV | HSTATUS_VSXL_64;
    vcpu->regs.sstatus = SSTATUS_SPP_BIT | SSTATUS_FS_DIRTY | SSTATUS_XS_DIRTY;
    vcpu->regs.sepc = entry;
    vcpu->regs.a0 = vcpu->arch.hart_id = vcpu->id;
    vcpu->regs.a1 = 0; // according to sbi it should be the dtb load address

    if (CPU_HAS_EXTENSION(CPU_EXT_SSTC)) {
        csrs_stimecmp_write(~0U);
    }

    csrs_hcounteren_write(HCOUNTEREN_TM);
    csrs_htimedelta_write(0);
    csrs_vsstatus_write(SSTATUS_SD | SSTATUS_FS_DIRTY | SSTATUS_XS_DIRTY);
    csrs_hie_write(0);
    csrs_vstvec_write(0);
    csrs_vsscratch_write(0);
    csrs_vsepc_write(0);
    csrs_vscause_write(0);
    csrs_vstval_write(0);
    csrs_hvip_write(0);
    csrs_vsatp_write(0);
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    if ((reg <= 0) || (reg > 31)) {
        return 0;
    }
    return vcpu->regs.x[reg - 1];
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    if ((reg <= 0) || (reg > 31)) {
        return;
    }
    vcpu->regs.x[reg - 1] = val;
}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.sepc;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
{
    vcpu->regs.sepc = pc;
}

void vcpu_arch_run(struct vcpu* vcpu)
{
    if (vcpu->arch.sbi_ctx.state == STARTED) {
        vcpu_arch_entry();
    } else {
        cpu_idle();
    }
}
