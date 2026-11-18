/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/sysregs.h>

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    if (reg > 30) {
        return 0;
    }
    return vcpu->regs.x[reg];
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    if (reg > 30) {
        return;
    }
    vcpu->regs.x[reg] = val;
}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.elr_el2;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
{
    vcpu->regs.elr_el2 = pc;
}

void vcpu_subarch_reset(struct vcpu* vcpu)
{
    vcpu->regs.spsr_el2 = SPSR_EL1h | SPSR_F | SPSR_I | SPSR_A | SPSR_D;
}

static inline bool vcpu_at_el1(struct vcpu* vcpu)
{
    unsigned long el = vcpu->regs.spsr_el2 & SPSR_EL_MSK;

    return (el == SPSR_EL1h) || (el == SPSR_EL1t);
}

static vaddr_t vcpu_exception_vector_addr(struct vcpu* vcpu)
{
    vaddr_t vec_offset;

    if (vcpu_at_el1(vcpu)) {
        vec_offset = ((vcpu->regs.spsr_el2 & SPSR_EL_MSK) == SPSR_EL1t) ? 0x0 : 0x200;
    } else if ((vcpu->regs.spsr_el2 & SPSR_AARCH32) != 0) {
        vec_offset = 0x600;
    } else {
        vec_offset = 0x400;
    }

    return sysreg_vbar_el1_read() + vec_offset;
}

/**
 * Taking an exception to EL1 keeps NZCV, DIT and, unless SCTLR_EL1.SPAN is clear, PAN; the
 * remaining pstate fields follow the exception entry rules.
 */
static unsigned long vcpu_exception_pstate(struct vcpu* vcpu)
{
    static const unsigned long PSTATE_PRESERVED_BITS =
        ~(SPSR_M_MSK | SPSR_D | SPSR_A | SPSR_I | SPSR_F | SPSR_IL | SPSR_SS | SPSR_UAO | SPSR_TCO |
            SPSR_SSBS | SPSR_BTYPE_MSK | SPSR_ALLINT);
    unsigned long sctlr = sysreg_sctlr_el1_read();
    unsigned long pfr1 = sysreg_id_aa64pfr1_el1_read();
    unsigned long pstate = (vcpu->regs.spsr_el2 & PSTATE_PRESERVED_BITS) | SPSR_EL1h | SPSR_D |
        SPSR_A | SPSR_I | SPSR_F;

    if ((sctlr & SCTLR_SPAN) == 0) {
        pstate |= SPSR_PAN;
    }

    if ((sctlr & SCTLR_DSSBS) != 0) {
        pstate |= SPSR_SSBS;
    }

    if (bit_extract(pfr1, ID_AA64PFR1_MTE_OFF, ID_AA64PFR1_MTE_LEN) != 0) {
        pstate |= SPSR_TCO;
    }

    if ((bit_extract(pfr1, ID_AA64PFR1_NMI_OFF, ID_AA64PFR1_NMI_LEN) != 0) &&
        ((sctlr & SCTLR_SPINTMASK) == 0)) {
        pstate |= SPSR_ALLINT;
    }

    return pstate;
}

static unsigned long vcpu_mem_abort_esr(struct vcpu* vcpu, bool inst_abort, unsigned long iss)
{
    unsigned long ec;

    if (inst_abort) {
        ec = vcpu_at_el1(vcpu) ? ESR_EC_IASEL : ESR_EC_IALEL;
    } else {
        ec = vcpu_at_el1(vcpu) ? ESR_EC_DASEL : ESR_EC_DALEL;
    }

    /* The ISS layout is the same for instruction and data aborts, so the DA macros serve both */
    unsigned long esr = (ec << ESR_EC_OFF) | (iss & ESR_ISS_DA_FnV_BIT);

    if (!inst_abort) {
        esr |= iss & ESR_ISS_DA_WnR_BIT;
    }

    if ((iss & ESR_ISS_DA_S1PTW_BIT) != 0) {
        /**
         * Faults on a stage 1 walk are reported at level 0. Finding the real level would require
         * walking the guest's page tables, which are not mapped in the hypervisor and could be
         * concurrently modified by other vcpus.
         */
        esr |= ESR_ISS_DA_DSFC_SEA_PTW_L0;
    } else {
        esr |= ESR_ISS_DA_DSFC_SEA;
    }

    return esr;
}

/**
 * Deliver an exception taken from the guest to its own EL1 vector, as it would observe it on bare
 * metal: stage 2 aborts become synchronous external aborts and every other class an undefined
 * instruction (EC unknown), which is always a cause the guest can act on and avoids translating
 * between the hypervisor's and the guest's view of each exception class.
 *
 * Must be called on the vcpu's own cpu while handling a trap taken from the guest.
 */
bool vcpu_arch_inject_exception(struct vcpu* vcpu, unsigned long esr, unsigned long far)
{
    unsigned long ec = bit_extract(esr, ESR_EC_OFF, ESR_EC_LEN);
    unsigned long iss = bit_extract(esr, ESR_ISS_OFF, ESR_ISS_LEN);
    unsigned long esr_el1 = esr & ESR_IL_BIT;
    unsigned long far_el1 = 0;

    if ((ec == ESR_EC_DALEL) || (ec == ESR_EC_IALEL)) {
        esr_el1 |= vcpu_mem_abort_esr(vcpu, ec == ESR_EC_IALEL, iss);
        far_el1 = far;
    } else {
        esr_el1 |= ESR_EC_UNKWN << ESR_EC_OFF;
    }

    /* The vector depends on the pstate the guest was in, so compute it before updating spsr_el2 */
    vaddr_t vec_addr = vcpu_exception_vector_addr(vcpu);

    sysreg_esr_el1_write(esr_el1);
    sysreg_far_el1_write(far_el1);
    sysreg_spsr_el1_write(vcpu->regs.spsr_el2);
    sysreg_elr_el1_write(vcpu_readpc(vcpu));
    vcpu->regs.spsr_el2 = vcpu_exception_pstate(vcpu);
    vcpu_writepc(vcpu, vec_addr);

    return true;
}
