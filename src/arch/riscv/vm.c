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

static void vcpu_arch_config_ssnpm(enum npm_mode npm_mode)
{
    uint64_t pmm_val;

    switch (npm_mode) {
        case NPM_MODE_DISABLED:
            pmm_val = HENVCFG_PMM_DISABLED;
            break;
        case NPM_MODE_PMLEN_7:
            pmm_val = HENVCFG_PMM_PMLEN_7;
            break;
        case NPM_MODE_PMLEN_16:
            pmm_val = HENVCFG_PMM_PMLEN_16;
            break;
        default:
            ERROR("Invalid VM arch.npm_mode.\n");
    }

#if defined(RV32)
    if (npm_mode != NPM_MODE_DISABLED) {
        ERROR("Ssnpm pointer masking is not available on RV32.\n");
    }
#endif

    pmm_val <<= HENVCFG_PMM_OFF;
    csrs_henvcfg_clear(HENVCFG_PMM_MSK);
    csrs_henvcfg_set(pmm_val);
    if ((csrs_henvcfg_read() & HENVCFG_PMM_MSK) != pmm_val) {
        ERROR("Configured Ssnpm pointer masking mode is not supported by this hart.\n");
    }
}

void vm_arch_init(struct vm* vm, const struct vm_config* vm_config)
{
    paddr_t root_pt_pa;
    mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &root_pt_pa);

    unsigned long hgatp = (root_pt_pa >> PAGE_SHIFT) | (HGATP_MODE_DFLT) |
        ((vm->id << HGATP_VMID_OFF) & HGATP_VMID_MSK);

    csrs_hgatp_write(hgatp);

    virqc_init(vm, &vm_config->platform.arch.irqc);
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

    csrs_sscratch_write((uintptr_t)vcpu);

    vcpu->regs.hstatus = HSTATUS_SPV | (1ULL << HSTATUS_VGEIN_OFF);

    if (DEFINED(RV64)) {
        vcpu->regs.hstatus |= HSTATUS_VSXL_64;
    }

    /* Apply the VM policy on this hart, including when an SBI hart is restarted. */
    enum npm_mode npm_mode = vcpu->vm->config->arch.npm_mode;
    if (CPU_HAS_EXTENSION(CPU_EXT_SSNPM)) {
        vcpu_arch_config_ssnpm(npm_mode);
    } else if (npm_mode != NPM_MODE_DISABLED) {
        ERROR("VM requests pointer masking, but CPU_EXT_SSNPM is not configured.\n");
    }

    vcpu->regs.sstatus = SSTATUS_SPP_BIT | SSTATUS_FS_DIRTY | SSTATUS_XS_DIRTY;

    if (CPU_HAS_EXTENSION(CPU_EXT_F)) {
        vcpu->regs.sstatus |= SSTATUS_FS_DIRTY;
    }

    if (CPU_HAS_EXTENSION(CPU_EXT_V)) {
        vcpu->regs.sstatus |= SSTATUS_VS_DIRTY;
    }

    vcpu->regs.sepc = entry;
    vcpu->regs.a0 = vcpu->arch.hart_id = vcpu->id;
    vcpu->regs.a1 = 0; // according to sbi it should be the dtb load address

    if (CPU_HAS_EXTENSION(CPU_EXT_SSSTATEEN)) {
        csrs_sstateen0_write(0);
    }

    csrs_senvcfg_write(0);
    csrs_hcounteren_write(HCOUNTEREN_TM);
    csrs_htimedelta_write(0);
    csrs_vsstatus_write(SSTATUS_SD | SSTATUS_FS_DIRTY | SSTATUS_XS_DIRTY);

    if (CPU_HAS_EXTENSION(CPU_EXT_F)) {
        csrs_vsstatus_set(SSTATUS_FS_DIRTY);
    }

    if (CPU_HAS_EXTENSION(CPU_EXT_V)) {
        csrs_vsstatus_set(SSTATUS_VS_DIRTY);
    }

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

bool vcpu_arch_is_on(struct vcpu* vcpu)
{
    return vcpu->arch.sbi_ctx.state == STARTED;
}
