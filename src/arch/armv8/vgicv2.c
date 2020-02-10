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

#include <arch/vgicv2.h>

#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>

#define GICD_IS_REG(REG, offset)            \
    (((offset) >= offsetof(gicd_t, REG)) && \
     (offset) < (offsetof(gicd_t, REG) + sizeof(gicd.REG)))
#define GICD_REG_GROUP(REG) ((offsetof(gicd_t, REG) & 0xf80) >> 7)
#define GICD_REG_IND(REG) (offsetof(gicd_t, REG) & 0x7f)

#define VGIC_MSG_DATA(VM_ID, INT_ID, VAL) \
    (((VM_ID) << 32) | (((INT_ID)&0x7fff) << 8) | ((VAL)&0xff))
#define VGIC_MSG_VM(DATA) ((DATA) >> 32)
#define VGIC_MSG_INTID(DATA) (((DATA) >> 8) & 0x7fff)
#define VGIC_MSG_VAL(DATA) ((DATA)&0xff)

enum VGICD_EVENTS {
    VGICD_GICH_EN,
    VGICD_SET_EN,
    VGICD_SET_ACT,
    VGICD_SET_PEND,
    VGICD_SET_PRIO,
    VGICD_SET_TRGT,
    VGICD_SET_CFG,
    VGICD_ROUTE
};

void gicv2_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(gicv2_ipi_handler, GICV2_IPI_ID);

static inline vgic_int_t *vgic_get_int(vcpu_t *vcpu, uint64_t int_id)
{
    if (int_id < GIC_CPU_PRIV) {
        return &vcpu->arch.vgicd_priv.interrupts[int_id];
    } else if (int_id >= GIC_CPU_PRIV && int_id < GIC_MAX_INTERUPTS) {
        return &vcpu->vm->arch.vgicd.interrupts[int_id - GIC_CPU_PRIV];
    } else {
        return NULL;
    }
}

bool vgic_owns(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return interrupt->owner == vcpu;
}

void vgic_set_hw(vm_t *vm, uint64_t id)
{
    if (id < GIC_MAX_SGIS) return;

    vgic_int_t *interrupt = NULL;

    if (id < GIC_CPU_PRIV) {
        list_foreach(vm->vcpu_list, vcpu_t, vcpu)
        {
            interrupt = vgic_get_int(vcpu, id);
            spin_lock(&interrupt->lock);
            interrupt->hw = true;
            spin_unlock(&interrupt->lock);
        }
    } else {
        /**
         * This assumes this method is called only during VM initlization
         */
        interrupt = vgic_get_int((vcpu_t *)list_peek(&vm->vcpu_list), id);
        spin_lock(&interrupt->lock);
        interrupt->hw = true;
        spin_unlock(&interrupt->lock);
    }
}

static inline int64_t gich_get_lr(vgic_int_t *interrupt, uint32_t *lr)
{
    if (!interrupt->in_lr || interrupt->owner->phys_id != cpu.id) {
        return -1;
    }

    uint32_t lr_val = gich.LR[interrupt->lr];
    if ((GICH_LR_VID(lr_val) == interrupt->id) &&
        (GICH_LR_STATE(lr_val) != INV)) {
        if (lr != NULL) *lr = lr_val;
        return interrupt->lr;
    }

    return -1;
}

static inline uint8_t vgic_get_state(vgic_int_t *interrupt)
{
    uint8_t state = 0;

    uint32_t lr_val = 0;
    if (interrupt->in_lr && interrupt->owner->phys_id == cpu.id &&
        gich_get_lr(interrupt, &lr_val) >= 0) {
        state = GICH_LR_STATE(lr_val);
    } else {
        state = interrupt->state;
    }

    if (interrupt->id < GIC_MAX_SGIS &&
        interrupt->owner->arch.vgicd_priv.sgis[interrupt->id].pend) {
        state |= PEND;
    }

    return state;
}

/**
 * This method must be invoked already with a lock on the interrupt
 */
bool vgic_get_ownership(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool ret = false;

    /**
     *  what if the vcpu is not a target for this interrupt? -
     * can it be the owner?
     */

    if (interrupt->owner == vcpu) {
        ret = true;
    } else if (interrupt->owner == NULL) {
        interrupt->owner = vcpu;
        ret = true;
    }

    return ret;
}

void vgic_yield_ownership(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    if (!vgic_owns(vcpu, interrupt) || interrupt->in_lr) return;

    if (!(interrupt->id < GIC_CPU_PRIV) && !(vgic_get_state(interrupt) & ACT)) {
        interrupt->owner = NULL;
    }
}

static inline void vgic_write_lr(vcpu_t *vcpu, vgic_int_t *interrupt,
                                 uint64_t lr_ind)
{
    uint64_t prev_int_id = vcpu->arch.vgicd_priv.curr_lrs[lr_ind];

    if ((prev_int_id != interrupt->id) && !gic_is_priv(prev_int_id)) {
        vgic_int_t *prev_interrupt = vgic_get_int(vcpu, prev_int_id);
        spin_lock(&prev_interrupt->lock);
        if (vgic_owns(vcpu, prev_interrupt) && prev_interrupt->in_lr &&
            (prev_interrupt->lr == lr_ind)) {
            prev_interrupt->in_lr = false;
            vgic_yield_ownership(vcpu, prev_interrupt);
        }
        spin_unlock(&prev_interrupt->lock);
    }

    uint8_t state = vgic_get_state(interrupt);

    if (state == INV || interrupt->in_lr) {
        return;
    }

    uint32_t lr =
        ((interrupt->id << GICH_LR_VID_OFF) & GICH_LR_VID_MSK) |
        (((interrupt->prio >> 3) << GICH_LR_PRIO_OFF) & GICH_LR_PRIO_MSK);

    if (interrupt->hw) {
        lr |= GICH_LR_HW_BIT;
        lr |= (interrupt->id << GICH_LR_PID_OFF) & GICH_LR_PID_MSK;
        if (state == PENDACT) {
            lr |= GICH_LR_STATE_ACT;
        } else {
            lr |= (state << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK;
        }
        // TODO: maybe make sure of actual hardware state is active?
    } else {
        if (interrupt->id < GIC_MAX_SGIS) {
            if (state & ACT) {
                lr |= (vcpu->arch.vgicd_priv.sgis[interrupt->id].act
                       << GICH_LR_CPUID_OFF) &
                      GICH_LR_CPUID_MSK;
                lr |= GICH_LR_STATE_ACT;
            } else {
                for (int i = GIC_MAX_TARGETS - 1; i >= 0; i--) {
                    if (vcpu->arch.vgicd_priv.sgis[interrupt->id].pend &
                        (1U << i)) {
                        lr |= (i << GICH_LR_CPUID_OFF) & GICH_LR_CPUID_MSK;
                        vcpu->arch.vgicd_priv.sgis[interrupt->id].pend &=
                            ~(1U << i);

                        lr |= GICH_LR_STATE_PND;
                        break;
                    }
                }
            }

            if (vcpu->arch.vgicd_priv.sgis[interrupt->id].pend) {
                lr |= GICH_LR_EOI_BIT;
            }

        } else {
            if (!gic_is_priv(interrupt->id) && !interrupt->hw) {
                lr |= GICH_LR_EOI_BIT;
            }

            lr |= (state << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK;
        }
    }

    interrupt->in_lr = true;
    interrupt->lr = lr_ind;
    vcpu->arch.vgicd_priv.curr_lrs[lr_ind] = interrupt->id;
    gich.LR[lr_ind] = lr;
}

bool vgic_remove_lr(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool ret = false;

    if (!vgic_owns(vcpu, interrupt) || !interrupt->in_lr) {
        return ret;
    }

    uint32_t lr_val = 0;
    int64_t lr_ind = -1;
    if ((lr_ind = gich_get_lr(interrupt, &lr_val)) >= 0) {
        gich.LR[interrupt->lr] = 0;
    }

    interrupt->in_lr = false;

    if (GICH_LR_STATE(lr_val) != INV) {
        interrupt->state = GICH_LR_STATE(lr_val);
        if (interrupt->id < GIC_MAX_SGIS) {
            if (interrupt->state & ACT) {
                vcpu->arch.vgicd_priv.sgis[interrupt->id].act =
                    GICH_LR_CPUID(lr_val);
            } else if (interrupt->state & PEND) {
                vcpu->arch.vgicd_priv.sgis[interrupt->id].pend |=
                    (1U << GICH_LR_CPUID(lr_val));
            }
        }

        if ((interrupt->state & PEND) && interrupt->enabled) {
            gich.HCR |= GICH_HCR_NPIE_BIT;
        }

        ret = true;
    }

    return ret;
}

bool vgic_add_lr(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool ret = false;

    if (!interrupt->enabled && !interrupt->in_lr) {
        return ret;
    }

    int64_t lr_ind = -1;
    for (int i = 0; i < NUM_LRS; i++) {
        if (bit_get(gich.ELSR[i / 32], i % 32)) {
            lr_ind = i;
            break;
        }
    }

    if (lr_ind < 0) {
        uint64_t min_prio_pend = 0, min_prio_act = 0;
        uint64_t pend_found = 0, act_found = 0;
        int64_t pend_ind = -1, act_ind = -1;

        for (int i = 0; i < NUM_LRS; i++) {
            uint32_t lr = gich.LR[i];
            uint64_t lr_prio = (lr & GICH_LR_PRIO_MSK) >> GICH_LR_PRIO_OFF;
            uint64_t lr_state = (lr & GICH_LR_STATE_MSK);

            if (lr_state & GICH_LR_STATE_ACT) {
                if (lr_prio > min_prio_act) {
                    min_prio_act = lr_prio;
                    act_ind = i;
                }
                pend_found++;
            } else if (lr_state & GICH_LR_STATE_PND) {
                if (lr_prio > min_prio_pend) {
                    min_prio_pend = lr_prio;
                    pend_ind = i;
                }
                act_found++;
            }
        }

        if (pend_found > 1) {
            lr_ind = pend_ind;
        } else {
            lr_ind = act_ind;
        }

        if (lr_ind >= 0) {
            vgic_int_t *spilled_int =
                vgic_get_int(vcpu, GICH_LR_VID(gich.LR[lr_ind]));

            // TODO: possible deadlock?
            spin_lock(&spilled_int->lock);
            vgic_remove_lr(vcpu, spilled_int);
            vgic_yield_ownership(vcpu, spilled_int);
            spin_unlock(&spilled_int->lock);
        }
    }

    if (lr_ind >= 0) {
        vgic_write_lr(vcpu, interrupt, lr_ind);
        ret = true;
    } else {
        // turn on maintenance interrupts
        if (vgic_get_state(interrupt) & PEND) {
            gich.HCR |= GICH_HCR_NPIE_BIT;
        }
    }

    return ret;
}

void vgicd_emul_misc_access(emul_access_t *acc)
{
    vgicd_t *vgicd = &cpu.vcpu->vm->arch.vgicd;
    uint64_t reg = acc->addr & 0x7F;

    switch (reg) {
        case GICD_REG_IND(CTLR):
            if (acc->write) {
                uint32_t prev_ctrl = vgicd->CTLR;
                vgicd->CTLR = vcpu_readreg(cpu.vcpu, acc->reg) & 0x1;
                if (prev_ctrl ^ vgicd->CTLR) {
                    bool enable = vgicd->CTLR ? true : false;
                    if (enable)
                        gich.HCR |= GICH_HCR_En_BIT;
                    else
                        gich.HCR &= ~GICH_HCR_En_BIT;
                    cpu_msg_t msg = {GICV2_IPI_ID, VGICD_GICH_EN, enable};
                    vm_msg_broadcast(cpu.vcpu->vm, &msg);
                }
            } else {
                vcpu_writereg(cpu.vcpu, acc->reg, vgicd->CTLR);
            }
            break;
        case GICD_REG_IND(TYPER):
            if (!acc->write) {
                vcpu_writereg(cpu.vcpu, acc->reg, vgicd->TYPER);
            }
            break;
        case GICD_REG_IND(IIDR):
            if (!acc->write) {
                vcpu_writereg(cpu.vcpu, acc->reg, vgicd->IIDR);
            }
            break;
    }
}

void vgic_route(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    if (!((interrupt->state & PEND) && interrupt->enabled)) {
        return;
    }

    if (interrupt->targets & (1 << cpu.id)) {
        vgic_add_lr(vcpu, interrupt);
    }

    if (!interrupt->in_lr && (interrupt->targets & ~(1 << cpu.id))) {
        cpu_msg_t msg = {GICV2_IPI_ID, VGICD_ROUTE,
                         VGIC_MSG_DATA(vcpu->vm->id, interrupt->id, 0)};
        vgic_yield_ownership(vcpu, interrupt);
        vm_msg_broadcast(cpu.vcpu->vm, &msg);
    }
}

void vgicd_set_enable(vcpu_t *vcpu, uint64_t int_id, bool en)
{
    if (int_id < GIC_MAX_SGIS) return;

    vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, int_id);

    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        if (interrupt->enabled ^ en) {
            interrupt->enabled = en;
            if (interrupt->enabled) {
                vgic_remove_lr(vcpu, interrupt);
            } else {
                vgic_route(vcpu, interrupt);
            }
            if (interrupt->hw) gicd_set_enable(interrupt->id, en);
        }
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {GICV2_IPI_ID, VGICD_SET_EN,
                         VGIC_MSG_DATA(vcpu->vm->id, interrupt->id, en)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

bool vgicd_get_enable(vcpu_t *vcpu, uint64_t int_id)
{
    return vgic_get_int(vcpu, int_id)->enabled;
}

void vgicd_emul_isenabler_access(emul_access_t *acc)
{
    uint64_t reg_ind = (acc->addr & 0x7F) / sizeof(uint32_t);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    uint64_t first_int = 32 * reg_ind;

    if (acc->write) {
        for (int i = 0; i < 32; i++) {
            if (bit_get(val, i)) {
                vgicd_set_enable(cpu.vcpu, i + first_int, true);
            }
        }
    } else {
        for (int i = 0; i < 32; i++) {
            if (vgicd_get_enable(cpu.vcpu, i + first_int)) {
                val |= 1U << i;
            }
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgicd_emul_icenabler_access(emul_access_t *acc)
{
    uint64_t reg_ind = (acc->addr & 0x7F) / sizeof(uint32_t);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    uint64_t first_int = 32 * reg_ind;

    if (acc->write) {
        for (int i = 0; i < 32; i++) {
            if (bit_get(val, i)) {
                vgicd_set_enable(cpu.vcpu, i + first_int, false);
            }
        }
    } else {
        for (int i = 0; i < 32; i++) {
            if (vgicd_get_enable(cpu.vcpu, i + first_int)) {
                val |= 1U << i;
            }
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgicd_sgi_set_pend(vcpu_t *vcpu, uint64_t int_id, bool pend)
{
    if ((int_id & 0x3ff) > GIC_MAX_SGIS) return;

    vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, (int_id & 0x3ff));
    uint64_t source = (int_id & 0x7c00) >> 10;

    spin_lock(&interrupt->lock);

    vgic_remove_lr(vcpu, interrupt);

    uint8_t pendstate = vcpu->arch.vgicd_priv.sgis[interrupt->id].pend;
    uint8_t new_pendstate =
        pend ? pendstate | (1U << source) : pendstate & ~(1U << source);

    if (pendstate ^ new_pendstate) {
        vcpu->arch.vgicd_priv.sgis[interrupt->id].pend = new_pendstate;
        if (new_pendstate) {
            interrupt->state |= PEND;
        } else {
            interrupt->state &= ~PEND;
        }

        if (interrupt->state != INV) {
            vgic_add_lr(vcpu, interrupt);
        }
    }

    spin_unlock(&interrupt->lock);
}

void vgicd_set_pend(vcpu_t *vcpu, uint64_t int_id, bool pend)
{
    if ((int_id & 0x3ff) < GIC_MAX_SGIS) {
        vgicd_sgi_set_pend(vcpu, int_id, pend);
        return;
    }

    vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, int_id & 0x3ff);

    spin_lock(&interrupt->lock);

    if (vgic_get_ownership(vcpu, interrupt)) {
        vgic_remove_lr(vcpu, interrupt);
        uint8_t state = interrupt->state;
        if (pend && !(state & PEND)) {
            interrupt->state = state | PEND;
        } else if (!pend && (state & PEND)) {
            interrupt->state = state & ~PEND;
        }

        if (interrupt->hw) {
            gicd_set_state(interrupt->id,
                           interrupt->state == PEND ? ACT : interrupt->state);
        }

        if (interrupt->state != INV) {
            vgic_route(vcpu, interrupt);
        }

        vgic_yield_ownership(vcpu, interrupt);

    } else {
        cpu_msg_t msg = {GICV2_IPI_ID, VGICD_SET_PEND,
                         VGIC_MSG_DATA(vcpu->vm->id, interrupt->id, pend)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }

    spin_unlock(&interrupt->lock);
}

void vgicd_emul_ispendr_access(emul_access_t *acc)
{
    uint64_t reg_ind = (acc->addr & 0x7F) / sizeof(uint32_t);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    uint64_t first_int = 32 * reg_ind;

    if (acc->write) {
        for (int i = 0; i < 32; i++) {
            if (bit_get(val, i)) {
                vgicd_set_pend(cpu.vcpu, i + first_int, true);
            }
        }
    } else {
        // TODO
        vcpu_writereg(cpu.vcpu, acc->reg, 0);
    }
}

void vgicd_emul_icpendr_access(emul_access_t *acc)
{
    // TODO
}

void vgicd_set_actv(vcpu_t *vcpu, uint64_t int_id, bool pend)
{
    // TODO
}

void vgicd_emul_isactiver_access(emul_access_t *acc)
{
    // TODO
}

void vgicd_emul_icativer_access(emul_access_t *acc)
{
    // TODO
}

void vgicd_set_prio(vcpu_t *vcpu, uint64_t int_id, uint8_t prio)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id);
    prio &= 0xF0;  // gic-400 only allows 4 priority bits in non-secure state
    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        if (interrupt->prio != prio) {
            vgic_remove_lr(vcpu, interrupt);
            uint8_t prev_prio = interrupt->prio;
            interrupt->prio = prio;
            if (prio <= prev_prio) {
                vgic_route(vcpu, interrupt);
            }
            if (interrupt->hw) gicd_set_prio(interrupt->id, prio);
        }
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {GICV2_IPI_ID, VGICD_SET_PRIO,
                         VGIC_MSG_DATA(vcpu->vm->id, interrupt->id, prio)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

uint8_t vgicd_get_prio(vcpu_t *vcpu, uint64_t int_id)
{
    return vgic_get_int(vcpu, int_id)->prio;
}

void vgicd_emul_ipriorityr_access(emul_access_t *acc)
{
    /* We look at prio regs as 8 bit registers */
    uint64_t first_int = (8 / GIC_PRIO_BITS) * (acc->addr & 0x1ff);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;

    if (acc->write) {
        for (int i = 0; i < acc->width; i++) {
            vgicd_set_prio(cpu.vcpu, first_int + i,
                           bit_extract(val, GIC_PRIO_BITS * i, GIC_PRIO_BITS));
        }
    } else {
        for (int i = 0; i < acc->width; i++) {
            val |= vgicd_get_prio(cpu.vcpu, first_int + i)
                   << (GIC_PRIO_BITS * i);
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

static uint32_t vgic_target_translate(vm_t *vm, uint32_t trgt, bool topcpu)
{
    union {
        uint32_t mask;
        uint8_t buf[4];
    } from, to;

    from.mask = trgt;
    to.mask = 0;

    for (int i = 0; i < sizeof(trgt) * 8 / GIC_TARGET_BITS; i++) {
        to.buf[i] =
            topcpu
                ? vm_translate_to_pcpu_mask(vm, from.buf[i], GIC_TARGET_BITS)
                : vm_translate_to_vcpu_mask(vm, from.buf[i], GIC_TARGET_BITS);
    }

    return to.mask;
}

void vgicd_set_trgt(vcpu_t *vcpu, uint64_t int_id, uint8_t trgt)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id);

    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        if (interrupt->targets != trgt) {
            interrupt->targets = trgt;
            if (interrupt->hw) gicd_set_trgt(interrupt->id, trgt);
            if (vgic_get_state(interrupt) != INV) {
                vgic_route(vcpu, interrupt);
            }
        }
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {GICV2_IPI_ID, VGICD_SET_TRGT,
                         VGIC_MSG_DATA(vcpu->vm->id, interrupt->id, trgt)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

uint8_t vgicd_get_trgt(vcpu_t *vcpu, uint64_t int_id)
{
    return vgic_get_int(vcpu, int_id)->targets;
}

void vgicd_emul_itargetr_access(emul_access_t *acc)
{
    uint64_t first_int = (8 / GIC_TARGET_BITS) * (acc->addr & 0x1ff);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;

    if (acc->write) {
        val = vgic_target_translate(cpu.vcpu->vm, val, true);
        for (int i = 0; i < acc->width; i++) {
            vgicd_set_trgt(
                cpu.vcpu, first_int + i,
                bit_extract(val, GIC_TARGET_BITS * i, GIC_TARGET_BITS));
        }
    } else {
        for (int i = 0; i < acc->width; i++) {
            val |= vgicd_get_trgt(cpu.vcpu, first_int + i)
                   << (GIC_TARGET_BITS * i);
        }
        val = vgic_target_translate(cpu.vcpu->vm, val, false);
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgicd_emul_icfgr_access(emul_access_t *acc)
{
    // TODO
}

void vgicd_emul_sgiregs_access(emul_access_t *acc)
{
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;

    if ((acc->addr & 0xfff) == (((uint64_t)&gicd.SGIR) & 0xfff)) {
        if (acc->write) {
            uint64_t trgtlist = 0;
            switch (GICD_SGIR_TRGLSTFLT(val)) {
                case 0:
                    trgtlist = vgic_target_translate(
                        cpu.vcpu->vm, GICD_SGIR_CPUTRGLST(val), true);
                    break;
                case 1:
                    trgtlist = cpu.vcpu->vm->cpus & ~(1U << cpu.id);
                    break;
                case 2:
                    trgtlist = (1U << cpu.id);
                    break;
                case 3:
                    return;
            }

            cpu_msg_t msg = {
                GICV2_IPI_ID, VGICD_SET_PEND,
                VGIC_MSG_DATA(cpu.vcpu->vm->id,
                              GICD_SGIR_SGIINTID(val) | (cpu.vcpu->id << 10),
                              true)};

            for (int i = 0; i < GIC_TARGET_BITS; i++) {
                if (trgtlist & (1U << i)) cpu_send_msg(i, &msg);
            }
        }

    } else {
        // TODO: CPENDSGIR and SPENDSGIR access
    }
}

bool vgicd_emul_handler(emul_access_t *acc)
{
    if (acc->width > 4) return false;

    uint32_t acc_offset = acc->addr & 0xfff;

    switch ((acc->addr & 0xf80) >> 7) {
        case GICD_REG_GROUP(CTLR):
        case GICD_REG_GROUP(ISENABLER):
        case GICD_REG_GROUP(ISPENDR):
        case GICD_REG_GROUP(ISACTIVER):
        case GICD_REG_GROUP(ICENABLER):
        case GICD_REG_GROUP(ICPENDR):
        case GICD_REG_GROUP(ICACTIVER):
        case GICD_REG_GROUP(ICFGR):
            /* Only allow aligned 32-bit accesses or byte */
            if (acc->width != 4 || acc->addr & 0x3) {
                return false;
            }
            break;

        case GICD_REG_GROUP(SGIR):
            /* Allow byte access or align 16-bit accesses */
            if ((acc->width == 4 && (acc->addr & 0x3)) ||
                (acc->width == 2 && (acc->addr & 0x1))) {
                return false;
            }
            break;

        default:
            if (GICD_IS_REG(IPRIORITYR, acc_offset) ||
                GICD_IS_REG(ITARGETSR, acc_offset)) {
                /* Allow byte access or align 16-bit accesses */
                if ((acc->width == 4 && (acc->addr & 0x3)) ||
                    (acc->width == 2 && (acc->addr & 0x1))) {
                    return false;
                }
            }
    }

    // spin_lock(&cpu.vcpu->vm->arch.vgicd.lock);
    switch ((acc->addr & 0xf80) >> 7) {
        case GICD_REG_GROUP(CTLR):
            vgicd_emul_misc_access(acc);
            break;
        case GICD_REG_GROUP(ISENABLER):
            vgicd_emul_isenabler_access(acc);
            break;
        case GICD_REG_GROUP(ISPENDR):
            vgicd_emul_ispendr_access(acc);
            break;
        case GICD_REG_GROUP(ISACTIVER):
            vgicd_emul_isactiver_access(acc);
            break;
        case GICD_REG_GROUP(ICENABLER):
            vgicd_emul_icenabler_access(acc);
            break;
        case GICD_REG_GROUP(ICPENDR):
            vgicd_emul_icpendr_access(acc);
            break;
        case GICD_REG_GROUP(ICACTIVER):
            vgicd_emul_icativer_access(acc);
            break;
        case GICD_REG_GROUP(ICFGR):
            vgicd_emul_icfgr_access(acc);
            break;
        case GICD_REG_GROUP(SGIR):
            vgicd_emul_sgiregs_access(acc);
            break;
        default:
            if (GICD_IS_REG(IPRIORITYR, acc_offset)) {
                vgicd_emul_ipriorityr_access(acc);
            } else if (GICD_IS_REG(ITARGETSR, acc_offset)) {
                vgicd_emul_itargetr_access(acc);
            }
    }
    // spin_unlock(&cpu.vcpu->vm->arch.vgicd.lock);

    return true;
}

void vgicd_inject(vgicd_t *vgicd, uint64_t id, uint64_t source)
{
    vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, id & 0x3ff);

    if (interrupt->hw) {
        spin_lock(&interrupt->lock);
        interrupt->owner = cpu.vcpu;
        interrupt->state = PEND;
        interrupt->in_lr = false;
        vgic_route(cpu.vcpu, interrupt);
        spin_unlock(&interrupt->lock);
    } else {
        vgicd_set_pend(cpu.vcpu, id, true);
    }
}

void gicv2_ipi_handler(uint32_t event, uint64_t data)
{
    uint8_t val = VGIC_MSG_VAL(data);
    uint16_t int_id = VGIC_MSG_INTID(data);
    uint16_t vm_id = VGIC_MSG_VM(data);

    if (vm_id != cpu.vcpu->vm->id) {
        ERROR("received vgic msg target to another vcpu");
        // TODO: need to fetch vcpu from other vm if the taget vm for this
        // is not active
    }

    switch (event) {
        case VGICD_GICH_EN: {
            bool enable = data ? true : false;
            if (enable)
                gich.HCR |= GICH_HCR_En_BIT;
            else
                gich.HCR &= ~GICH_HCR_En_BIT;

        } break;
        case VGICD_SET_EN: {
            vgicd_set_enable(cpu.vcpu, int_id, val);
        } break;

        case VGICD_SET_PEND: {
            vgicd_set_pend(cpu.vcpu, int_id, val);
        } break;

        case VGICD_SET_PRIO: {
            vgicd_set_prio(cpu.vcpu, int_id, val);
        } break;

        case VGICD_SET_TRGT: {
            vgicd_set_trgt(cpu.vcpu, int_id, val);
        } break;

        case VGICD_ROUTE: {
            vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, int_id);
            spin_lock(&interrupt->lock);
            if (vgic_get_ownership(cpu.vcpu, interrupt)) {
                if (interrupt->targets & (1 << cpu.id)) {
                    vgic_add_lr(cpu.vcpu, interrupt);
                }
                vgic_yield_ownership(cpu.vcpu, interrupt);
            }
            spin_unlock(&interrupt->lock);
        } break;
    }
}

void vgic_refill_lrs(vcpu_t *vpcu)
{
    bool has_pending = false;
    for (int i = 0; i < NUM_LRS; i++) {
        uint32_t lr = gich.LR[i];
        if (GICH_LR_STATE(lr) & PEND) {
            has_pending = true;
            break;
        }
    }

    int64_t lr_ind;
    while ((lr_ind = bitmap_find_nth((bitmap_t)&gich.ELSR, NUM_LRS, 1, 0,
                                     true)) >= 0) {
        vgic_int_t *interrupt = NULL;
        uint8_t state = INV;

        for (int i = 0; i < gic_num_irqs(); i++) {
            vgic_int_t *temp_int = vgic_get_int(cpu.vcpu, i);
            spin_lock(&temp_int->lock);

            if (vgic_get_ownership(cpu.vcpu, temp_int)) {
                uint8_t temp_state = vgic_get_state(temp_int);
                bool cpu_is_target =
                    !!(vgicd_get_trgt(cpu.vcpu, i) & (1 << cpu.id));
                if (cpu_is_target && temp_state != INV && !temp_int->in_lr) {
                    if ((interrupt == NULL) ||

                        (!has_pending &&
                         ((temp_state & PEND) &&
                          ((state & ACT) ||
                           ((state & PEND) &&
                            (temp_int->prio < interrupt->prio))))) ||

                        (has_pending &&
                         ((temp_state & ACT) && (state & PEND))) ||

                        (has_pending && (temp_int->prio < interrupt->prio))) {
                        vgic_int_t *aux = interrupt;
                        interrupt = temp_int;
                        temp_int = aux;

                        state = vgic_get_state(interrupt);
                    }
                }
            }

            if (temp_int) {
                vgic_yield_ownership(cpu.vcpu, temp_int);
                spin_unlock(&temp_int->lock);
            }
        }

        if (interrupt != NULL) {
            vgic_write_lr(cpu.vcpu, interrupt, lr_ind);
            if (state & PEND) has_pending = true;
            spin_unlock(&interrupt->lock);
        } else {
            gich.HCR &= ~(GICH_HCR_NPIE_BIT);
            break;
        }
    }
}

void vgic_eoir_highest_spilled_active(vcpu_t *vcpu)
{
    vgic_int_t *interrupt = NULL;
    for (int i = 0; i < gic_num_irqs(); i++) {
        vgic_int_t *temp_int = vgic_get_int(vcpu, i);
        spin_lock(&temp_int->lock);

        if (vgic_get_ownership(vcpu, temp_int) && (temp_int->state & ACT)) {
            if (interrupt == NULL || (interrupt->prio < temp_int->prio)) {
                vgic_int_t *aux = interrupt;
                interrupt = temp_int;
                temp_int = aux;
            }
        }

        if (temp_int != NULL) {
            vgic_yield_ownership(vcpu, temp_int);
            spin_unlock(&temp_int->lock);
        }
    }

    if (interrupt) {
        interrupt->state &= ~ACT;
        if (interrupt->hw) {
            gicd_set_act(interrupt->id, false);
        } else {
            if (interrupt->state & PEND) {
                vgic_add_lr(vcpu, interrupt);
            }
        }
        spin_unlock(&interrupt->lock);
    }
}

void vgic_handle_trapped_eoir(vcpu_t *vcpu)
{
    int64_t lr_ind = -1;
    while ((lr_ind = bitmap_find_nth((bitmap_t)&gich.EISR, NUM_LRS, 1, 0,
                                     true)) >= 0) {
        uint32_t lr_val = gich.LR[lr_ind];
        gich.LR[lr_ind] = 0;

        vgic_int_t *interrupt = vgic_get_int(vcpu, GICH_LR_VID(lr_val));
        spin_lock(&interrupt->lock);
        if (interrupt->id < GIC_MAX_SGIS) {
            vgic_add_lr(vcpu, interrupt);
        } else {
            interrupt->in_lr = false;
            vgic_yield_ownership(vcpu, interrupt);
        }
        spin_unlock(&interrupt->lock);
    }
}

void gic_maintenance_handler(uint64_t arg, uint64_t source)
{
    uint32_t misr = gich.MISR;

    if (misr & GICH_MISR_EOI) {
        vgic_handle_trapped_eoir(cpu.vcpu);
    }

    if (misr & GICH_MISR_NP) {
        vgic_refill_lrs(cpu.vcpu);
    }

    if (misr & GICH_MISR_LRPEN) {
        while (gich.HCR & GICH_HCR_EOICount_MASK) {
            vgic_eoir_highest_spilled_active(cpu.vcpu);
            gich.HCR -= (1U << GICH_HCR_EOICount_OFF);
        }
    }
}

void vgic_init(vm_t *vm, const struct gic_dscrp *gic_dscrp)
{
    vm->arch.vgicd.CTLR = 0;
    vm->arch.vgicd.TYPER =
        (gicd.TYPER & GICD_TYPER_ITLN_MSK) |
        (((vm->cpu_num - 1) << GICD_TYPER_CPUN_OFF) & GICD_TYPER_CPUN_MSK);
    vm->arch.vgicd.IIDR = gicd.IIDR;

    size_t n = NUM_PAGES(sizeof(gicc_t));
    void *va =
        mem_alloc_vpage(&vm->as, SEC_VM_ANY, (void *)gic_dscrp->gicc_addr, n);
    if (va != (void *)gic_dscrp->gicc_addr)
        ERROR("failed to alloc vm address space to hold gicc");
    mem_map_dev(&vm->as, va, platform.arch.gic.gicv_addr, n);

    for (int i = 0; i < GIC_MAX_SPIS; i++) {
        vm->arch.vgicd.interrupts[i].id = i + GIC_CPU_PRIV;
        vm->arch.vgicd.interrupts[i].owner = NULL;
        vm->arch.vgicd.interrupts[i].hw = false;
        vm->arch.vgicd.interrupts[i].enabled = false;
        vm->arch.vgicd.interrupts[i].state = INV;
        vm->arch.vgicd.interrupts[i].prio = 0xFF;
        vm->arch.vgicd.interrupts[i].targets = 0;
        vm->arch.vgicd.interrupts[i].lock = 0;
    }

    emul_region_t emu = {.va_base = gic_dscrp->gicd_addr,
                         .pa_base = (uint64_t)&gicd,
                         .size = ALIGN(sizeof(gicd_t), PAGE_SIZE),
                         .handler = vgicd_emul_handler};

    vm_add_emul(vm, &emu);
}

void vgic_cpu_init(vcpu_t *vcpu)
{
    for (int i = 0; i < GIC_CPU_PRIV; i++) {
        vcpu->arch.vgicd_priv.interrupts[i].id = i;
        vcpu->arch.vgicd_priv.interrupts[i].owner = vcpu;
        vcpu->arch.vgicd_priv.interrupts[i].hw = false;
        vcpu->arch.vgicd_priv.interrupts[i].enabled = false;
        vcpu->arch.vgicd_priv.interrupts[i].state = INV;
        vcpu->arch.vgicd_priv.interrupts[i].prio = 0xFF;
        vcpu->arch.vgicd_priv.interrupts[i].targets = (1U << vcpu->phys_id);;
        vcpu->arch.vgicd_priv.interrupts[i].lock = 0;
        vcpu->arch.vgicd_priv.interrupts[i].in_lr = 0;
        vcpu->arch.vgicd_priv.interrupts[i].lr = 0;
    }

    for (int i = 0; i < GIC_MAX_SGIS; i++) {
        vcpu->arch.vgicd_priv.interrupts[i].enabled = true;
    }
}
