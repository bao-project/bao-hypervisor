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
            ERROR("Got reserved mode from SPSR_HYP.M");
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
            ERROR("Got reserved mode from SPSR_HYP.M");
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
            ERROR("Got reserved mode from SPSR_HYP.M");
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
            ERROR("Got reserved mode from SPSR_HYP.M");
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
