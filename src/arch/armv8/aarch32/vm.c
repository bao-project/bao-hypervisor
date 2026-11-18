/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/sysregs.h>

// For the following functions which access state from different modes, for now
// we assume vcpu passed as argument is resident

static inline uint32_t vcpu_current_spsr_m(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);

    return sysreg_spsr_hyp_read() & SPSR_M_MSK;
}

static inline uint32_t vcpu_read_sp_current_el1_mode(struct vcpu* vcpu)
{
    uint32_t spsr_m = vcpu_current_spsr_m(vcpu);
    uint32_t sp_val = 0;
    switch (spsr_m) {
        case SPSR_USR:
            sp_val = sysreg_sp_usr_read();
            break;
        case SPSR_IRQ:
            sp_val = sysreg_sp_irq_read();
            break;
        case SPSR_FIQ:
            sp_val = sysreg_sp_fiq_read();
            break;
        case SPSR_SVC:
            sp_val = sysreg_sp_svc_read();
            break;
        case SPSR_ABT:
            sp_val = sysreg_sp_abt_read();
            break;
        case SPSR_UND:
            sp_val = sysreg_sp_und_read();
            break;
        default:
            ERROR("Got reserved mode from SPSR_HYP.M\n");
    }

    return sp_val;
}

static inline void vcpu_write_sp_current_el1_mode(struct vcpu* vcpu, uint32_t sp_val)
{
    uint32_t spsr_m = vcpu_current_spsr_m(vcpu);
    switch (spsr_m) {
        case SPSR_USR:
            sysreg_sp_usr_write(sp_val);
            break;
        case SPSR_IRQ:
            sysreg_sp_irq_write(sp_val);
            break;
        case SPSR_FIQ:
            sysreg_sp_fiq_write(sp_val);
            break;
        case SPSR_SVC:
            sysreg_sp_svc_write(sp_val);
            break;
        case SPSR_ABT:
            sysreg_sp_abt_write(sp_val);
            break;
        case SPSR_UND:
            sysreg_sp_und_write(sp_val);
            break;
        default:
            ERROR("Got reserved mode from SPSR_HYP.M\n");
    }
}

static inline uint32_t vcpu_read_lr_current_el1_mode(struct vcpu* vcpu)
{
    uint32_t spsr_m = vcpu_current_spsr_m(vcpu);
    uint32_t lr_val = 0;
    switch (spsr_m) {
        case SPSR_USR:
            lr_val = vcpu->regs.x[14];
            break;
        case SPSR_IRQ:
            lr_val = sysreg_lr_irq_read();
            break;
        case SPSR_FIQ:
            lr_val = sysreg_lr_fiq_read();
            break;
        case SPSR_SVC:
            lr_val = sysreg_lr_svc_read();
            break;
        case SPSR_ABT:
            lr_val = sysreg_lr_abt_read();
            break;
        case SPSR_UND:
            lr_val = sysreg_lr_und_read();
            break;
        default:
            ERROR("Got reserved mode from SPSR_HYP.M\n");
    }

    return lr_val;
}

static inline void vcpu_write_lr_current_el1_mode(struct vcpu* vcpu, uint32_t lr_val)
{
    uint32_t spsr_m = vcpu_current_spsr_m(vcpu);
    switch (spsr_m) {
        case SPSR_USR:
            vcpu->regs.x[14] = lr_val;
            break;
        case SPSR_IRQ:
            sysreg_lr_irq_write(lr_val);
            break;
        case SPSR_FIQ:
            sysreg_lr_fiq_write(lr_val);
            break;
        case SPSR_SVC:
            sysreg_lr_svc_write(lr_val);
            break;
        case SPSR_ABT:
            sysreg_lr_abt_write(lr_val);
            break;
        case SPSR_UND:
            sysreg_lr_und_write(lr_val);
            break;
        default:
            ERROR("Got reserved mode from SPSR_HYP.M\n");
    }
}

static inline uint32_t vcpu_read_current_el1_fiq_rx(struct vcpu* vcpu, unsigned long reg)
{
    UNUSED_ARG(vcpu);

    uint32_t reg_val = 0;
    switch (reg) {
        case 8:
            reg_val = sysreg_r8_fiq_read();
            break;
        case 9:
            reg_val = sysreg_r9_fiq_read();
            break;
        case 10:
            reg_val = sysreg_r10_fiq_read();
            break;
        case 11:
            reg_val = sysreg_r11_fiq_read();
            break;
        case 12:
            reg_val = sysreg_r12_fiq_read();
            break;
        default:
            reg_val = 0;
    }

    return reg_val;
}

static inline uint32_t vcpu_write_current_el1_fiq_rx(struct vcpu* vcpu, unsigned long reg,
    unsigned long reg_val)
{
    UNUSED_ARG(vcpu);

    switch (reg) {
        case 8:
            sysreg_r8_fiq_write(reg_val);
            break;
        case 9:
            sysreg_r9_fiq_write(reg_val);
            break;
        case 10:
            sysreg_r10_fiq_write(reg_val);
            break;
        case 11:
            sysreg_r11_fiq_write(reg_val);
            break;
        case 12:
            sysreg_r12_fiq_write(reg_val);
            break;
        default:
            reg_val = 0;
    }

    return reg_val;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    uint32_t reg_val = 0;

    if (reg > 14) {
        reg_val = 0;
    } else if (reg == 13) {
        reg_val = vcpu_read_sp_current_el1_mode(vcpu);
    } else if (reg == 14) {
        reg_val = vcpu_read_lr_current_el1_mode(vcpu);
    } else if ((reg >= 8) && (vcpu_current_spsr_m(vcpu) == SPSR_FIQ)) {
        reg_val = vcpu_read_current_el1_fiq_rx(vcpu, reg);
    } else {
        reg_val = vcpu->regs.x[reg];
    }

    return reg_val;
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    if (reg > 14) {
        return;
    } else if (reg == 13) {
        vcpu_write_sp_current_el1_mode(vcpu, val);
    } else if (reg == 14) {
        vcpu_write_lr_current_el1_mode(vcpu, val);
    } else if ((reg >= 8) && (vcpu_current_spsr_m(vcpu) == SPSR_FIQ)) {
        vcpu_write_current_el1_fiq_rx(vcpu, reg, val);
    } else {
        vcpu->regs.x[reg] = val;
    }
}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.elr_hyp;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
{
    vcpu->regs.elr_hyp = pc;
}

void vcpu_subarch_reset(struct vcpu* vcpu)
{
    vcpu->regs.spsr_hyp = SPSR_SVC | SPSR_F | SPSR_I | SPSR_A;
}

static vaddr_t vcpu_exception_vector_addr(uint32_t mode, bool inst_abort)
{
    vaddr_t vec_base =
        ((sysreg_sctlr_el1_read() & SCTLR_V) != 0) ? 0xFFFF0000 : sysreg_vbar_el1_read();
    vaddr_t vec_offset;

    if (mode == SPSR_UND) {
        vec_offset = 0x4;
    } else {
        vec_offset = inst_abort ? 0xC : 0x10;
    }

    return vec_base + vec_offset;
}

static uint32_t vcpu_exception_cpsr(struct vcpu* vcpu, uint32_t mode)
{
    static const uint32_t CPSR_PRESERVED_BITS = ~(SPSR_M_MSK | SPSR_IT_MSK | SPSR_J | SPSR_E |
        SPSR_T | SPSR_IL | SPSR_SS | SPSR_SSBS_AARCH32);
    uint32_t sctlr = sysreg_sctlr_el1_read();
    uint32_t cpsr = (vcpu->regs.spsr_hyp & CPSR_PRESERVED_BITS) | mode | SPSR_I;

    if (mode == SPSR_ABT) {
        cpsr |= SPSR_A;
    }

    if ((sctlr & SCTLR_TE) != 0) {
        cpsr |= SPSR_T;
    }

    if ((sctlr & SCTLR_EE) != 0) {
        cpsr |= SPSR_E;
    }

    if ((sctlr & SCTLR_SPAN) == 0) {
        cpsr |= SPSR_PAN;
    }

    if ((sctlr & SCTLR_DSSBS_AARCH32) != 0) {
        cpsr |= SPSR_SSBS_AARCH32;
    }

    return cpsr;
}

static uint32_t vcpu_exception_lr(struct vcpu* vcpu, uint32_t mode, bool inst_abort)
{
    uint32_t lr_offset;

    if (mode == SPSR_UND) {
        lr_offset = ((vcpu->regs.spsr_hyp & SPSR_T) != 0) ? 2 : 4;
    } else {
        lr_offset = inst_abort ? 4 : 8;
    }

    return (uint32_t)vcpu_readpc(vcpu) + lr_offset;
}

static void vcpu_set_mem_abort_syndrome(bool inst_abort, unsigned long iss, unsigned long far)
{
    unsigned long fsr = 0;
    unsigned long fault_addr = far;

    /* PMSAv8-32 only knows the long-descriptor fault status encoding */
    bool long_fsr = DEFINED(MEM_PROT_MPU) || ((sysreg_ttbcr_read() & TTBCR_EAE) != 0);
    if (long_fsr) {
        fsr |= FSR_LPAE_BIT;
    }

    if ((iss & ESR_ISS_DA_S1PTW_BIT) != 0) {
        /**
         * Faults on a stage 1 walk are reported at level 1. Finding the real level would require
         * walking the guest's page tables, which are not mapped in the hypervisor and could be
         * concurrently modified by other vcpus.
         */
        fsr |= long_fsr ? ESR_ISS_DA_DSFC_SEA_PTW_L1 : FSR_SEA_PTW_L1;
    } else {
        if ((iss & ESR_ISS_DA_FnV_BIT) != 0) {
            fsr |= FSR_FnV_BIT;
            fault_addr = 0;
        }
        fsr |= long_fsr ? ESR_ISS_DA_DSFC_SEA : FSR_SEA;
    }

    if (inst_abort) {
        sysreg_ifsr_write(fsr);
        sysreg_ifar_write(fault_addr);
    } else {
        if ((iss & ESR_ISS_DA_WnR_BIT) != 0) {
            fsr |= FSR_WnR_BIT;
        }
        sysreg_dfsr_write(fsr);
        sysreg_dfar_write(fault_addr);
    }
}

/**
 * Deliver an exception taken from the guest to its own vector, as it would observe it on bare
 * metal: stage 2 aborts become synchronous external aborts and every other class an undefined
 * instruction, which is always a cause the guest can act on and avoids translating between the
 * hypervisor's and the guest's view of each exception class.
 *
 * Must be called on the vcpu's own cpu while handling a trap taken from the guest.
 */
bool vcpu_arch_inject_exception(struct vcpu* vcpu, unsigned long esr, unsigned long far)
{
    unsigned long ec = bit_extract(esr, ESR_EC_OFF, ESR_EC_LEN);
    unsigned long iss = bit_extract(esr, ESR_ISS_OFF, ESR_ISS_LEN);
    bool inst_abort = ec == ESR_EC_IALEL;
    uint32_t mode = SPSR_UND;

    if (inst_abort || (ec == ESR_EC_DALEL)) {
        mode = SPSR_ABT;
        vcpu_set_mem_abort_syndrome(inst_abort, iss, far);
    }

    uint32_t lr = vcpu_exception_lr(vcpu, mode, inst_abort);

    if (mode == SPSR_ABT) {
        sysreg_lr_abt_write(lr);
        sysreg_spsr_abt_write(vcpu->regs.spsr_hyp);
    } else {
        sysreg_lr_und_write(lr);
        sysreg_spsr_und_write(vcpu->regs.spsr_hyp);
    }

    vcpu->regs.spsr_hyp = vcpu_exception_cpsr(vcpu, mode);
    vcpu_writepc(vcpu, vcpu_exception_vector_addr(mode, inst_abort));

    return true;
}
