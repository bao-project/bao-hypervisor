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

#include <arch/vgic.h>

#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>

enum VGIC_EVENTS { VGIC_UPDATE_ENABLE, VGIC_ROUTE, VGIC_INJECT, VGIC_SET_REG };
extern volatile const uint64_t VGIC_IPI_ID;

#define GICD_IS_REG(REG, offset)            \
    (((offset) >= offsetof(gicd_t, REG)) && \
     (offset) < (offsetof(gicd_t, REG) + sizeof(gicd.REG)))
#define GICD_REG_GROUP(REG) ((offsetof(gicd_t, REG) & 0xff80) >> 7)
#define GICD_REG_MASK(ADDR) ((ADDR)&(GIC_VERSION == GICV2 ? 0xfffULL : 0xffffULL))
#define GICD_REG_IND(REG) (offsetof(gicd_t, REG) & 0x7f)

#define VGIC_MSG_DATA(VM_ID, VGICRID, INT_ID, REG, VAL)                 \
    (((uint64_t)(VM_ID) << 48) | (((uint64_t)(VGICRID)&0xffff) << 32) | \
     (((INT_ID)&0x7fff) << 16) | (((REG)&0xff) << 8) | ((VAL)&0xff))
#define VGIC_MSG_VM(DATA) ((DATA) >> 48)
#define VGIC_MSG_VGICRID(DATA) (((DATA) >> 32) & 0xffff)
#define VGIC_MSG_INTID(DATA) (((DATA) >> 16) & 0x7fff)
#define VGIC_MSG_REG(DATA) (((DATA) >> 8) & 0xff)
#define VGIC_MSG_VAL(DATA) ((DATA)&0xff)

void vgic_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vgic_ipi_handler, VGIC_IPI_ID);

static inline vgic_int_t *vgic_get_int(vcpu_t *vcpu, uint64_t int_id,
                                       uint64_t vgicr_id)
{
    if (int_id < GIC_CPU_PRIV) {
        vcpu_t *target_vcpu =
            vgicr_id == vcpu->id ? vcpu : vm_get_vcpu(vcpu->vm, vgicr_id);
        return &target_vcpu->arch.vgic_priv.interrupts[int_id];
    } else if (int_id < vcpu->vm->arch.vgicd.int_num) {
        return &vcpu->vm->arch.vgicd.interrupts[int_id - GIC_CPU_PRIV];
    }

    return NULL;
}

static inline bool vgic_int_is_hw(vgic_int_t *interrupt)
{
    return !(interrupt->id < GIC_MAX_SGIS) && interrupt->hw;
}

static inline int64_t gich_get_lr(vgic_int_t *interrupt, uint64_t *lr)
{
    if (!interrupt->in_lr || interrupt->owner->phys_id != cpu.id) {
        return -1;
    }

    uint64_t lr_val = gich_read_lr(interrupt->lr);
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

    uint64_t lr_val = 0;
    if (gich_get_lr(interrupt, &lr_val) >= 0) {
        state = GICH_LR_STATE(lr_val);
    } else {
        state = interrupt->state;
    }

#if (GIC_VERSION == GICV2)
    if (interrupt->id < GIC_MAX_SGIS && interrupt->sgi.pend) {
        state |= PEND;
    }
#endif

    return state;
}

bool vgic_get_ownership(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool ret = false;

    if (interrupt->owner == vcpu) {
        ret = true;
    } else if (interrupt->owner == NULL) {
        interrupt->owner = vcpu;
        ret = true;
    }

    return ret;
}

bool vgic_owns(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return interrupt->owner == vcpu;
}

void vgic_yield_ownership(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    if ((GIC_VERSION == GICV2 && gic_is_priv(interrupt->id)) ||
        !vgic_owns(vcpu, interrupt) || interrupt->in_lr ||
        (vgic_get_state(interrupt) & ACT)) {
        return;
    }

    interrupt->owner = NULL;
}

void vgic_send_sgi_msg(vcpu_t *vcpu, uint64_t pcpu_mask, uint64_t int_id)
{
    cpu_msg_t msg = {
        VGIC_IPI_ID, VGIC_INJECT,
        VGIC_MSG_DATA(cpu.vcpu->vm->id, 0, int_id, 0, cpu.vcpu->id)};

    for (int i = 0; i < platform.cpu_num; i++) {
        if (pcpu_mask & (1ull << i)) {
            cpu_send_msg(i, &msg);
        }
    }
}

void vgic_route(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    if ((interrupt->state == INV) || !interrupt->enabled) {
        return;
    }

    if (vgic_int_vcpu_is_target(vcpu, interrupt)) {
        vgic_add_lr(vcpu, interrupt);
    }

    if (!interrupt->in_lr && vgic_int_has_other_target(vcpu, interrupt)) {
        cpu_msg_t msg = {
            VGIC_IPI_ID, VGIC_ROUTE,
            VGIC_MSG_DATA(vcpu->vm->id, vcpu->id, interrupt->id, 0, 0)};
        vgic_yield_ownership(vcpu, interrupt);
        uint64_t trgtlist =
            vgic_int_ptarget_mask(vcpu, interrupt) & ~(1ull << vcpu->phys_id);
        for (int i = 0; i < platform.cpu_num; i++) {
            if (trgtlist & (1ull << i)) {
                cpu_send_msg(i, &msg);
            }
        }
    }
}

static inline void vgic_write_lr(vcpu_t *vcpu, vgic_int_t *interrupt,
                                 uint64_t lr_ind)
{
    uint64_t prev_int_id = vcpu->arch.vgic_priv.curr_lrs[lr_ind];

    if ((prev_int_id != interrupt->id) && !gic_is_priv(prev_int_id)) {
        vgic_int_t *prev_interrupt = vgic_get_int(vcpu, prev_int_id, vcpu->id);
        if (prev_interrupt != NULL) {
            spin_lock(&prev_interrupt->lock);
            if (vgic_owns(vcpu, prev_interrupt) && prev_interrupt->in_lr &&
                (prev_interrupt->lr == lr_ind)) {
                prev_interrupt->in_lr = false;
                vgic_yield_ownership(vcpu, prev_interrupt);
            }
            spin_unlock(&prev_interrupt->lock);
        }
    }

    uint64_t state = vgic_get_state(interrupt);

    uint64_t lr = ((interrupt->id << GICH_LR_VID_OFF) & GICH_LR_VID_MSK);

#if (GIC_VERSION == GICV2)
    lr |= ((uint64_t)(interrupt->prio >> 3) << GICH_LR_PRIO_OFF) &
          GICH_LR_PRIO_MSK;
#else
    lr |= (((uint64_t)interrupt->prio << GICH_LR_PRIO_OFF) & GICH_LR_PRIO_MSK) |
          GICH_LR_GRP_BIT;
#endif

    if (vgic_int_is_hw(interrupt)) {
        lr |= GICH_LR_HW_BIT;
        lr |= (((uint64_t)interrupt->id) << GICH_LR_PID_OFF) & GICH_LR_PID_MSK;
        if (state == PENDACT) {
            lr |= GICH_LR_STATE_ACT;
        } else {
            lr |= (state << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK;
        }
    }
#if (GIC_VERSION == GICV2)
    else if (interrupt->id < GIC_MAX_SGIS) {
        if (state & ACT) {
            lr |= (interrupt->sgi.act << GICH_LR_CPUID_OFF) & GICH_LR_CPUID_MSK;
            lr |= GICH_LR_STATE_ACT;
        } else {
            for (int i = GIC_MAX_TARGETS - 1; i >= 0; i--) {
                if (interrupt->sgi.pend & (1U << i)) {
                    lr |= (i << GICH_LR_CPUID_OFF) & GICH_LR_CPUID_MSK;
                    interrupt->sgi.pend &= ~(1U << i);

                    lr |= GICH_LR_STATE_PND;
                    break;
                }
            }
        }

        if (interrupt->sgi.pend) {
            lr |= GICH_LR_EOI_BIT;
        }

    }
#endif
    else {
        if (!gic_is_priv(interrupt->id) && !vgic_int_is_hw(interrupt)) {
            lr |= GICH_LR_EOI_BIT;
        }

        lr |= (state << GICH_LR_STATE_OFF) & GICH_LR_STATE_MSK;
    }

    interrupt->state = 0;
    interrupt->in_lr = true;
    interrupt->lr = lr_ind;
    vcpu->arch.vgic_priv.curr_lrs[lr_ind] = interrupt->id;
    gich_write_lr(lr_ind, lr);
}

bool vgic_remove_lr(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool ret = false;

    if (!vgic_owns(vcpu, interrupt) || !interrupt->in_lr) {
        return ret;
    }

    uint64_t lr_val = 0;
    int64_t lr_ind = -1;
    if ((lr_ind = gich_get_lr(interrupt, &lr_val)) >= 0) {
        gich_write_lr(lr_ind, 0);
    }

    interrupt->in_lr = false;

    if (GICH_LR_STATE(lr_val) != INV) {
        interrupt->state = GICH_LR_STATE(lr_val);
#if (GIC_VERSION == GICV2)
        if (interrupt->id < GIC_MAX_SGIS) {
            if (interrupt->state & ACT) {
                interrupt->sgi.act = GICH_LR_CPUID(lr_val);
            } else if (interrupt->state & PEND) {
                interrupt->sgi.pend |= (1U << GICH_LR_CPUID(lr_val));
            }
        }
#endif
        if ((interrupt->state & PEND) && interrupt->enabled) {
            gich_set_hcr(gich_get_hcr() | GICH_HCR_NPIE_BIT);
        }

        ret = true;
    }

    return ret;
}

bool vgic_add_lr(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool ret = false;

    if (!interrupt->enabled || interrupt->in_lr) {
        return ret;
    }

    int64_t lr_ind = -1;
    uint64_t elrsr = gich_get_elrsr();
    for (int i = 0; i < NUM_LRS; i++) {
        if (bit_get(elrsr, i)) {
            lr_ind = i;
            break;
        }
    }

    if (lr_ind < 0) {
        uint64_t min_prio_pend = 0, min_prio_act = 0;
        uint64_t pend_found = 0, act_found = 0;
        int64_t pend_ind = -1, act_ind = -1;

        for (int i = 0; i < NUM_LRS; i++) {
            uint64_t lr = gich_read_lr(i);
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
                vgic_get_int(vcpu, GICH_LR_VID(gich_read_lr(lr_ind)), vcpu->id);

            if (spilled_int != NULL) {
                // TODO: possible deadlock?
                spin_lock(&spilled_int->lock);
                vgic_remove_lr(vcpu, spilled_int);
                vgic_yield_ownership(vcpu, spilled_int);
                spin_unlock(&spilled_int->lock);
            }
        }
    }

    if (lr_ind >= 0) {
        vgic_write_lr(vcpu, interrupt, lr_ind);
        ret = true;
    } else {
        // turn on maintenance interrupts
        if (vgic_get_state(interrupt) & PEND) {
            gich_set_hcr(gich_get_hcr() | GICH_HCR_NPIE_BIT);
        }
    }

    return ret;
}

#define VGIC_ENABLE_MASK \
    ((GIC_VERSION == GICV2) ? GICD_CTLR_EN_BIT : GICD_CTLR_ENA_BIT)

static inline void vgic_update_enable(vcpu_t *vcpu)
{
    if (cpu.vcpu->vm->arch.vgicd.CTLR & VGIC_ENABLE_MASK) {
        gich_set_hcr(gich_get_hcr() | GICH_HCR_En_BIT);
    } else {
        gich_set_hcr(gich_get_hcr() & ~GICH_HCR_En_BIT);
    }
}

void vgicd_emul_misc_access(emul_access_t *acc,
                            struct vgic_reg_handler_info *handlers,
                            bool gicr_access, uint64_t vgicr_id)
{
    vgicd_t *vgicd = &cpu.vcpu->vm->arch.vgicd;
    uint64_t reg = acc->addr & 0x7F;

    switch (reg) {
        case GICD_REG_IND(CTLR):
            if (acc->write) {
                uint32_t prev_ctrl = vgicd->CTLR;
                vgicd->CTLR =
                    vcpu_readreg(cpu.vcpu, acc->reg) & VGIC_ENABLE_MASK;
                if (prev_ctrl ^ vgicd->CTLR) {
                    vgic_update_enable(cpu.vcpu);
                    cpu_msg_t msg = {
                        VGIC_IPI_ID, VGIC_UPDATE_ENABLE,
                        VGIC_MSG_DATA(cpu.vcpu->vm->id, 0, 0, 0, 0)};
                    vm_msg_broadcast(cpu.vcpu->vm, &msg);
                }
            } else {
                vcpu_writereg(cpu.vcpu, acc->reg,
                              vgicd->CTLR | GICD_CTLR_ARE_NS_BIT);
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

void vgicd_emul_pidr_access(emul_access_t *acc,
                            struct vgic_reg_handler_info *handlers,
                            bool gicr_access, uint64_t vgicr_id)
{
    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg,
                      gicd.ID[((acc->addr & 0xff) - 0xd0) / 4]);
    }
}

bool vgic_int_update_enable(vcpu_t *vcpu, vgic_int_t *interrupt, bool enable)
{
    if (GIC_VERSION == GICV2 && gic_is_sgi(interrupt->id)) {
        return false;
    }

    if (enable != interrupt->enabled) {
        interrupt->enabled = enable;
        return true;
    } else {
        return false;
    }
}

void vgic_int_enable_hw(vcpu_t *vcpu, vgic_int_t *interrupt)
{
#if (GIC_VERSION != GICV2)
    if (gic_is_priv(interrupt->id)) {
        gicr_set_enable(interrupt->id, interrupt->enabled,
                        interrupt->phys.redist);
    } else {
        gicd_set_enable(interrupt->id, interrupt->enabled);
    }
#else
    gic_set_enable(interrupt->id, interrupt->enabled);
#endif
}

bool vgic_int_clear_enable(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t data)
{
    if (!data)
        return false;
    else
        return vgic_int_update_enable(vcpu, interrupt, false);
}

bool vgic_int_set_enable(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t data)
{
    if (!data)
        return false;
    else
        return vgic_int_update_enable(vcpu, interrupt, true);
}

uint64_t vgic_int_get_enable(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return (uint64_t)interrupt->enabled;
}

bool vgic_int_update_pend(vcpu_t *vcpu, vgic_int_t *interrupt, bool pend)
{
    if (GIC_VERSION == GICV2 && gic_is_sgi(interrupt->id)) {
        return false;
    }

    if (pend ^ !!(interrupt->state & PEND)) {
        if (pend)
            interrupt->state |= PEND;
        else
            interrupt->state &= ~PEND;
        return true;
    } else {
        return false;
    }
}

void vgic_int_state_hw(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    uint8_t state = interrupt->state == PEND ? ACT : interrupt->state;
    bool pend = (state & PEND) != 0;
    bool act = (state & ACT) != 0;
#if (GIC_VERSION != GICV2)
    if (gic_is_priv(interrupt->id)) {
        gicr_set_act(interrupt->id, act, interrupt->phys.redist);
        gicr_set_pend(interrupt->id, pend, interrupt->phys.redist);
    } else {
        gicd_set_act(interrupt->id, act);
        gicd_set_pend(interrupt->id, pend);
    }
#else
    gicd_set_act(interrupt->id, act);
    gicd_set_pend(interrupt->id, pend);
#endif
}

bool vgic_int_clear_pend(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t data)
{
    if (!data)
        return false;
    else
        return vgic_int_update_pend(vcpu, interrupt, false);
}

bool vgic_int_set_pend(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t data)
{
    if (!data)
        return false;
    else
        return vgic_int_update_pend(vcpu, interrupt, true);
}

uint64_t vgic_int_get_pend(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return (interrupt->state & PEND) ? 1 : 0;
}

bool vgic_int_update_act(vcpu_t *vcpu, vgic_int_t *interrupt, bool act)
{
    if (act ^ !!(interrupt->state & ACT)) {
        if (act)
            interrupt->state |= ACT;
        else
            interrupt->state &= ~ACT;
        return true;
    } else {
        return false;
    }
}

bool vgic_int_clear_act(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t data)
{
    if (!data)
        return false;
    else
        return vgic_int_update_act(vcpu, interrupt, false);
}

bool vgic_int_set_act(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t data)
{
    if (!data)
        return false;
    else
        return vgic_int_update_act(vcpu, interrupt, true);
}

uint64_t vgic_int_get_act(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return (interrupt->state & ACT) ? 1 : 0;
}

bool vgic_int_set_cfg(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t cfg)
{
    uint8_t prev_cfg = interrupt->cfg;
    interrupt->cfg = (uint8_t)cfg;
    return prev_cfg != cfg;
}

uint64_t vgic_int_get_cfg(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return (uint64_t)interrupt->cfg;
}

void vgic_int_set_cfg_hw(vcpu_t *vcpu, vgic_int_t *interrupt)
{
#if (GIC_VERSION != GICV2)
    if (gic_is_priv(interrupt->id)) {
        gicr_set_icfgr(interrupt->id, interrupt->cfg, interrupt->phys.redist);
    } else {
        gicd_set_icfgr(interrupt->id, interrupt->cfg);
    }
#else
    gic_set_icfgr(interrupt->id, interrupt->cfg);
#endif
}

bool vgic_int_set_prio(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t prio)
{
    uint8_t prev_prio = interrupt->prio;
    interrupt->prio = (uint8_t)prio;
    return prev_prio != prio;
}

uint64_t vgic_int_get_prio(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return (uint64_t)interrupt->prio;
}

void vgic_int_set_prio_hw(vcpu_t *vcpu, vgic_int_t *interrupt)
{
#if (GIC_VERSION != GICV2)
    if (gic_is_priv(interrupt->id)) {
        gicr_set_prio(interrupt->id, interrupt->prio, interrupt->phys.redist);
    } else {
        gicd_set_prio(interrupt->id, interrupt->prio);
    }
#else
    gic_set_prio(interrupt->id, interrupt->prio);
#endif
}

void vgic_emul_razwi(emul_access_t *acc, struct vgic_reg_handler_info *handlers,
                     bool gicr_access, uint64_t vgicr_id)
{
    if (!acc->write) vcpu_writereg(cpu.vcpu, acc->reg, 0);
}

void vgic_int_set_field(struct vgic_reg_handler_info *handlers, vcpu_t *vcpu,
                        vgic_int_t *interrupt, uint64_t data)
{
    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        vgic_remove_lr(vcpu, interrupt);
        if (handlers->update_field(vcpu, interrupt, data) &&
            vgic_int_is_hw(interrupt)) {
            handlers->update_hw(vcpu, interrupt);
        }
        vgic_route(vcpu, interrupt);
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {VGIC_IPI_ID, VGIC_SET_REG,
                         VGIC_MSG_DATA(vcpu->vm->id, 0, interrupt->id,
                                       handlers->regid, data)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

void vgic_emul_generic_access(emul_access_t *acc,
                              struct vgic_reg_handler_info *handlers,
                              bool gicr_access, uint64_t vgicr_id)
{
    size_t field_width = handlers->field_width;
    uint64_t first_int =
        (GICD_REG_MASK(acc->addr) - handlers->regroup_base) * 8 / field_width;
    uint64_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    uint64_t mask = (1ull << field_width) - 1;
    bool valid_access =
        (GIC_VERSION == GICV2) || !(gicr_access ^ gic_is_priv(first_int));

    if (valid_access) {
        for (int i = 0; i < ((acc->width * 8) / field_width); i++) {
            vgic_int_t *interrupt =
                vgic_get_int(cpu.vcpu, first_int + i, vgicr_id);
            if (interrupt == NULL) break;
            if (acc->write) {
                uint64_t data = bit_extract(val, i * field_width, field_width);
                vgic_int_set_field(handlers, cpu.vcpu, interrupt, data);
            } else {
                val |= (handlers->read_field(cpu.vcpu, interrupt) & mask)
                       << (i * field_width);
            }
        }
    }

    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

struct vgic_reg_handler_info isenabler_info = {
    vgic_emul_generic_access,
    0b0100,
    VGIC_ISENABLER_ID,
    offsetof(gicd_t, ISENABLER),
    1,
    vgic_int_get_enable,
    vgic_int_set_enable,
    vgic_int_enable_hw,
};

struct vgic_reg_handler_info ispendr_info = {
    vgic_emul_generic_access,
    0b0100,
    VGIC_ISPENDR_ID,
    offsetof(gicd_t, ISPENDR),
    1,
    vgic_int_get_pend,
    vgic_int_set_pend,
    vgic_int_state_hw,
};

struct vgic_reg_handler_info isactiver_info = {
    vgic_emul_generic_access,
    0b0100,
    VGIC_ISACTIVER_ID,
    offsetof(gicd_t, ISACTIVER),
    1,
    vgic_int_get_act,
    vgic_int_set_act,
    vgic_int_state_hw,
};

struct vgic_reg_handler_info icenabler_info = {
    vgic_emul_generic_access,
    0b0100,
    VGIC_ICENABLER_ID,
    offsetof(gicd_t, ICENABLER),
    1,
    vgic_int_get_enable,
    vgic_int_clear_enable,
    vgic_int_enable_hw,
};

struct vgic_reg_handler_info icpendr_info = {
    vgic_emul_generic_access,
    0b0100,
    VGIC_ICPENDR_ID,
    offsetof(gicd_t, ICPENDR),
    1,
    vgic_int_get_pend,
    vgic_int_clear_pend,
    vgic_int_state_hw,
};

struct vgic_reg_handler_info iactiver_info = {
    vgic_emul_generic_access,
    0b0100,
    VGIC_ICACTIVER_ID,
    offsetof(gicd_t, ICACTIVER),
    1,
    vgic_int_get_act,
    vgic_int_clear_act,
    vgic_int_state_hw,
};

struct vgic_reg_handler_info icfgr_info = {
    vgic_emul_generic_access,
    0b0100,
    VGIC_ICFGR_ID,
    offsetof(gicd_t, ICFGR),
    2,
    vgic_int_get_cfg,
    vgic_int_set_cfg,
    vgic_int_set_cfg_hw,
};

struct vgic_reg_handler_info ipriorityr_info = {
    vgic_emul_generic_access,
    0b0101,
    VGIC_IPRIORITYR_ID,
    offsetof(gicd_t, IPRIORITYR),
    8,
    vgic_int_get_prio,
    vgic_int_set_prio,
    vgic_int_set_prio_hw,
};

struct vgic_reg_handler_info vgicd_misc_info = {
    vgicd_emul_misc_access,
    0b0100,
};

struct vgic_reg_handler_info vgicd_pidr_info = {
    vgicd_emul_pidr_access,
    0b0100,
};

struct vgic_reg_handler_info razwi_info = {
    vgic_emul_razwi,
    0b0100,
};

__attribute__((weak)) struct vgic_reg_handler_info itargetr_info = {
    vgic_emul_razwi,
    0b0101,
};

__attribute__((weak)) struct vgic_reg_handler_info sgir_info = {
    vgic_emul_razwi,
    0b0100,
};

__attribute__((weak)) struct vgic_reg_handler_info irouter_info = {
    vgic_emul_razwi,
    0b0100,
};

struct vgic_reg_handler_info *reg_handler_info_table[VGIC_REG_HANDLER_ID_NUM] =
    {[VGIC_ISENABLER_ID] = &isenabler_info,
     [VGIC_ISPENDR_ID] = &ispendr_info,
     [VGIC_ISACTIVER_ID] = &isactiver_info,
     [VGIC_ICENABLER_ID] = &icenabler_info,
     [VGIC_ICPENDR_ID] = &icpendr_info,
     [VGIC_ICACTIVER_ID] = &iactiver_info,
     [VGIC_ICFGR_ID] = &icfgr_info,
     [VGIC_IROUTER_ID] = &irouter_info,
     [VGIC_IPRIORITYR_ID] = &ipriorityr_info,
     [VGIC_ITARGETSR_ID] = &itargetr_info};

struct vgic_reg_handler_info *vgic_get_reg_handler_info(uint64_t id)
{
    if (id < VGIC_REG_HANDLER_ID_NUM) {
        return reg_handler_info_table[id];
    } else {
        return NULL;
    }
}

bool vgic_check_reg_alignment(emul_access_t *acc,
                              struct vgic_reg_handler_info *handlers)
{
    if (!(handlers->alignment & acc->width) ||
        ((acc->addr & (acc->width - 1)) != 0)) {
        return false;
    } else {
        return true;
    }
}

bool vgicd_emul_handler(emul_access_t *acc)
{
    struct vgic_reg_handler_info *handler_info = NULL;
    switch (GICD_REG_MASK(acc->addr) >> 7) {
        case GICD_REG_GROUP(CTLR):
            handler_info = &vgicd_misc_info;
            break;
        case GICD_REG_GROUP(ISENABLER):
            handler_info = &isenabler_info;
            break;
        case GICD_REG_GROUP(ISPENDR):
            handler_info = &ispendr_info;
            break;
        case GICD_REG_GROUP(ISACTIVER):
            handler_info = &isactiver_info;
            break;
        case GICD_REG_GROUP(ICENABLER):
            handler_info = &icenabler_info;
            break;
        case GICD_REG_GROUP(ICPENDR):
            handler_info = &icpendr_info;
            break;
        case GICD_REG_GROUP(ICACTIVER):
            handler_info = &iactiver_info;
            break;
        case GICD_REG_GROUP(ICFGR):
            handler_info = &icfgr_info;
            break;
        case GICD_REG_GROUP(SGIR):
            handler_info = &sgir_info;
            break;
        default: {
            uint64_t acc_off = GICD_REG_MASK(acc->addr);
            if (GICD_IS_REG(IPRIORITYR, acc_off)) {
                handler_info = &ipriorityr_info;
            } else if (GICD_IS_REG(ITARGETSR, acc_off)) {
                handler_info = &itargetr_info;
            } else if (GICD_IS_REG(IROUTER, acc_off)) {
                handler_info = &irouter_info;
            } else if (GICD_IS_REG(ID, acc_off)) {
                handler_info = &vgicd_pidr_info;
            } else {
                handler_info = &razwi_info;
            }
        }
    }

    if (vgic_check_reg_alignment(acc, handler_info)) {
        spin_lock(&cpu.vcpu->vm->arch.vgicd.lock);
        handler_info->reg_access(acc, handler_info, false, cpu.vcpu->id);
        spin_unlock(&cpu.vcpu->vm->arch.vgicd.lock);
        return true;
    } else {
        return false;
    }
}

void vgic_inject(vgicd_t *vgicd, uint64_t id, uint64_t source)
{
    vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, id, cpu.vcpu->id);
    if (interrupt != NULL) {
        if (vgic_int_is_hw(interrupt)) {
            spin_lock(&interrupt->lock);
            interrupt->owner = cpu.vcpu;
            interrupt->state = PEND;
            interrupt->in_lr = false;
            vgic_route(cpu.vcpu, interrupt);
            spin_unlock(&interrupt->lock);
        } else {
            if (GIC_VERSION == GICV2 && gic_is_sgi(id)) {
                vgic_inject_sgi(cpu.vcpu, interrupt, source);
            } else {
                vgic_int_set_field(&ispendr_info, cpu.vcpu, interrupt, true);
            }
        }
    }
}

void vgic_ipi_handler(uint32_t event, uint64_t data)
{
    uint16_t vm_id = VGIC_MSG_VM(data);
    uint16_t vgicr_id = VGIC_MSG_VGICRID(data);
    uint16_t int_id = VGIC_MSG_INTID(data);
    uint64_t val = VGIC_MSG_VAL(data);

    if (vm_id != cpu.vcpu->vm->id) {
        ERROR("received vgic3 msg target to another vcpu");
        // TODO: need to fetch vcpu from other vm if the taget vm for this
        // is not active
    }

    switch (event) {
        case VGIC_UPDATE_ENABLE: {
            vgic_update_enable(cpu.vcpu);
        } break;

        case VGIC_ROUTE: {
            vgic_int_t *interrupt =
                vgic_get_int(cpu.vcpu, int_id, cpu.vcpu->id);
            if (interrupt != NULL) {
                spin_lock(&interrupt->lock);
                if (vgic_get_ownership(cpu.vcpu, interrupt)) {
                    if (vgic_int_vcpu_is_target(cpu.vcpu, interrupt)) {
                        vgic_add_lr(cpu.vcpu, interrupt);
                    }
                    vgic_yield_ownership(cpu.vcpu, interrupt);
                }
                spin_unlock(&interrupt->lock);
            }
        } break;

        case VGIC_INJECT: {
            vgic_inject(&cpu.vcpu->vm->arch.vgicd, int_id, val);
        } break;

        case VGIC_SET_REG: {
            uint64_t reg_id = VGIC_MSG_REG(data);
            struct vgic_reg_handler_info *handlers =
                vgic_get_reg_handler_info(reg_id);
            vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, int_id, vgicr_id);
            if (handlers != NULL && interrupt != NULL) {
                vgic_int_set_field(handlers, cpu.vcpu, interrupt, val);
            }
        } break;
    }
}

void vgic_refill_lrs(vcpu_t *vcpu)
{
    bool has_pend = false;
    for (int i = 0; i < NUM_LRS; i++) {
        uint64_t lr = gich_read_lr(i);
        if (GICH_LR_STATE(lr) & PEND) {
            has_pend = true;
            break;
        }
    }

    /**
     * TODO: the following cycle can be highly otpimized using per-vcpu
     * active/pending interrupt lists.
     */
    int64_t lr_ind;
    uint64_t elrsr;
    while (elrsr = gich_get_elrsr(),
           (lr_ind = bitmap_find_nth((bitmap_t)&elrsr, NUM_LRS, 1, 0, true)) >=
               0) {
        vgic_int_t *interrupt = NULL;
        bool prev_pend = false;
        uint8_t prev_prio = GIC_LOWEST_PRIO;

        for (int i = 0; i < gic_num_irqs(); i++) {
            vgic_int_t *temp_int = vgic_get_int(vcpu, i, vcpu->id);
            if (temp_int == NULL) break;
            spin_lock(&temp_int->lock);
            if (vgic_get_ownership(vcpu, temp_int)) {
                uint8_t temp_state = vgic_get_state(temp_int);
                bool cpu_is_target = vgic_int_vcpu_is_target(vcpu, temp_int);
                if (cpu_is_target && temp_state != INV && !temp_int->in_lr) {
                    bool is_higher_prio = temp_int->prio < prev_prio;
                    bool is_act = (temp_state & ACT) != 0;
                    bool is_pend = (temp_state & PEND) != 0;
                    bool is_first_pend = !has_pend && is_pend && !prev_pend;
                    bool is_act_after_pend = has_pend && is_act && prev_pend;
                    if ((interrupt == NULL) || is_first_pend ||
                        is_act_after_pend || is_higher_prio) {
                        prev_pend = is_pend;
                        prev_prio = temp_int->prio;
                        vgic_int_t *aux = interrupt;
                        interrupt = temp_int;
                        temp_int = aux;
                    }
                }
            }

            if (temp_int != NULL) {
                vgic_yield_ownership(vcpu, temp_int);
                spin_unlock(&temp_int->lock);
            }
        }

        if (interrupt != NULL) {
            vgic_write_lr(vcpu, interrupt, lr_ind);
            has_pend = has_pend || prev_pend;
            spin_unlock(&interrupt->lock);
        } else {
            gich_set_hcr(gich_get_hcr() & ~(GICH_HCR_NPIE_BIT));
            break;
        }
    }
}

void vgic_eoir_highest_spilled_active(vcpu_t *vcpu)
{
    vgic_int_t *interrupt = NULL;
    for (int i = 0; i < gic_num_irqs(); i++) {
        vgic_int_t *temp_int = vgic_get_int(vcpu, i, vcpu->id);
        if (temp_int == NULL) break;

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
        if (vgic_int_is_hw(interrupt)) {
            gic_set_act(interrupt->id, false);
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
    uint64_t eisr = 0;
    while (
        eisr = gich_get_eisr(),
        (lr_ind = bitmap_find_nth((bitmap_t)&eisr, NUM_LRS, 1, 0, true)) >= 0) {
        uint64_t lr_val = gich_read_lr(lr_ind);
        gich_write_lr(lr_ind, 0);

        vgic_int_t *interrupt =
            vgic_get_int(vcpu, GICH_LR_VID(lr_val), vcpu->id);
        if (interrupt == NULL) continue;

        spin_lock(&interrupt->lock);
        interrupt->in_lr = false;
        if (interrupt->id < GIC_MAX_SGIS) {
            vgic_add_lr(vcpu, interrupt);
        } else {
            vgic_yield_ownership(vcpu, interrupt);
        }
        spin_unlock(&interrupt->lock);
    }
}

void gic_maintenance_handler(uint64_t arg)
{
    uint32_t misr = gich_get_misr();

    if (misr & GICH_MISR_EOI) {
        vgic_handle_trapped_eoir(cpu.vcpu);
    }

    if (misr & GICH_MISR_NP) {
        vgic_refill_lrs(cpu.vcpu);
    }

    if (misr & GICH_MISR_LRPEN) {
        uint32_t hcr_el2 = 0;
        while (hcr_el2 = gich_get_hcr(), hcr_el2 & GICH_HCR_EOICount_MASK) {
            vgic_eoir_highest_spilled_active(cpu.vcpu);
            hcr_el2 -= (1U << GICH_HCR_EOICount_OFF);
            gich_set_hcr(hcr_el2);
        }
    }
}

uint64_t vgic_get_itln(const struct gic_dscrp *gic_dscrp) {

    /**
     * By default the guest sees the real platforms interrupt line number
     * in the virtual gic. However a user can control this using the 
     * interrupt_num in the platform description configuration which be at
     * least the number os ppis and a multiple of 32.
     */

    uint64_t vtyper_itln =
        bit_extract(gicd.TYPER, GICD_TYPER_ITLN_OFF, GICD_TYPER_ITLN_LEN);

    if(gic_dscrp->interrupt_num > GIC_MAX_PPIS) {
        vtyper_itln = (ALIGN(gic_dscrp->interrupt_num, 32)/32 - 1) & 
            BIT_MASK(0, GICD_TYPER_ITLN_LEN);
    }

    return vtyper_itln;
}

void vgic_set_hw(vm_t *vm, uint64_t id)
{
    if (id < GIC_MAX_SGIS) return;

    vgic_int_t *interrupt = NULL;

    if (id < GIC_CPU_PRIV) {
        list_foreach(vm->vcpu_list, vcpu_t, vcpu)
        {
            interrupt = vgic_get_int(vcpu, id, vcpu->id);
            if (interrupt != NULL) {
                spin_lock(&interrupt->lock);
                interrupt->hw = true;
                spin_unlock(&interrupt->lock);
            }
        }
    } else {
        /**
         * This assumes this method is called only during VM initlization
         */
        interrupt = vgic_get_int((vcpu_t *)list_peek(&vm->vcpu_list), id, 0);
        if (interrupt != NULL) {
            spin_lock(&interrupt->lock);
            interrupt->hw = true;
            spin_unlock(&interrupt->lock);
        } else {
            WARNING("trying to link non-existent virtual irq to physical irq")
        }
    }
}
