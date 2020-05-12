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

#define GICD_IS_REG(REG, offset)            \
    (((offset) >= offsetof(gicd_t, REG)) && \
     (offset) < (offsetof(gicd_t, REG) + sizeof(gicd.REG)))
#define GICD_REG_GROUP(REG) ((offsetof(gicd_t, REG) & 0xff80) >> 7)
#define GICD_REG_IND(REG) (offsetof(gicd_t, REG) & 0x7f)

#define GICR_IS_REG(REG, offset)            \
    (((offset) >= offsetof(gicr_t, REG)) && \
     (offset) < (offsetof(gicr_t, REG) + sizeof(gicr[0].REG)))
#define GICR_REG_GROUP(REG) ((offsetof(gicr_t, REG) & 0xf80) >> 7)
#define GICR_REG_OFF(REG) (offsetof(gicr_t, REG) & 0x1ffff)
#define GICR_REG_IND(REG) (offsetof(gicr_t, REG) & 0x1f)

#define VGIC_MSG_DATA(VM_ID, VGICRID, INT_ID, VAL) \
    (((uint64_t)(VM_ID) << 48) | (((uint64_t)(VGICRID)&0xffff) << 32) \
    | (((INT_ID)&0x7fff) << 8) | ((VAL)&0xff))
#define VGIC_MSG_VM(DATA) ((DATA) >> 48)
#define VGIC_MSG_VGICRID(DATA) (((DATA) >> 32) & 0xffff)
#define VGIC_MSG_INTID(DATA) (((DATA) >> 8) & 0x7fff)
#define VGIC_MSG_VAL(DATA) ((DATA)&0xff)

#define VGIC_NO_OWNER (-1)

enum VGIC_EVENTS {
    VGIC_ENABLE,
    VGIC_SET_EN,
    VGIC_SET_ACT,
    VGIC_SET_PEND,
    VGIC_SET_PRIO,
    VGIC_SET_IROUTER,
    VGIC_SET_CFG,
    VGIC_ROUTE
};

void gicv3_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(gicv3_ipi_handler, VGICV3_IPI_ID);

static inline vgic_int_t *vgic_get_int(vcpu_t *vcpu, uint64_t int_id,
                                       uint64_t vgicr_id)
{
    if (int_id < GIC_CPU_PRIV) {
        vcpu_t *target_vcpu =
            vgicr_id == vcpu->id ? vcpu : vm_get_vcpu(vcpu->vm, vgicr_id);
        return &target_vcpu->arch.vgic_priv.interrupts[int_id];
    } else if (int_id >= GIC_CPU_PRIV && int_id < GIC_MAX_INTERUPTS) {
        return &vcpu->vm->arch.vgicd.interrupts[int_id - GIC_CPU_PRIV];
    }

    return NULL;
}

bool vgic_owns(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return interrupt->owner == vcpu || gic_is_priv(interrupt->id);
}

void vgic_set_hw(vm_t *vm, uint64_t id)
{
    if (id < GIC_MAX_SGIS) return;

    vgic_int_t *interrupt = NULL;

    if (id < GIC_CPU_PRIV) {
        list_foreach(vm->vcpu_list, vcpu_t, vcpu)
        {
            interrupt = vgic_get_int(vcpu, id, vcpu->id);
            spin_lock(&interrupt->lock);
            interrupt->hw = true;
            spin_unlock(&interrupt->lock);
        }
    } else {
        /**
         * This assumes this method is called only during VM initlization
         */
        interrupt = vgic_get_int((vcpu_t *)list_peek(&vm->vcpu_list), id, 0);
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

    uint32_t lr_val = gich_read_lr(interrupt->lr);
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

void vgic_yield_ownership(vcpu_t* vcpu, vgic_int_t *interrupt)
{
    if (!vgic_owns(vcpu, interrupt) || interrupt->in_lr) {
        return;
    }

    if (!(vgic_get_state(interrupt) & ACT)) {
        interrupt->owner = NULL;
    }
}

static inline void vgic_write_lr(vcpu_t *vcpu, vgic_int_t *interrupt,
                                 uint64_t lr_ind)
{
    uint64_t prev_int_id = vcpu->arch.vgic_priv.curr_lrs[lr_ind];

    if ((prev_int_id != interrupt->id) && !gic_is_priv(prev_int_id)) {
        vgic_int_t *prev_interrupt = vgic_get_int(vcpu, prev_int_id, vcpu->id);
        spin_lock(&prev_interrupt->lock);
        if (vgic_owns(vcpu, prev_interrupt) && prev_interrupt->in_lr &&
            (prev_interrupt->lr == lr_ind)) {
            prev_interrupt->in_lr = false;
            vgic_yield_ownership(vcpu, prev_interrupt);
        }
        spin_unlock(&prev_interrupt->lock);
    }

    uint64_t state = vgic_get_state(interrupt);

    uint64_t lr = ((interrupt->id << GICH_LR_VID_OFF) & GICH_LR_VID_MSK) |
                  (((uint64_t)interrupt->prio & 0xff) << 48) | (1ull << 60);

    if (interrupt->hw) {
        lr |= (1ull << 61);
        lr |= ((uint64_t)interrupt->id << 32) & (0x3ffull << 32);
        if (state == PENDACT) {
            lr |= (0b10ull << 62);
        } else {
            lr |= (state << 62);
        }
        // TODO: maybe make sure of actual hardware state is active?
    } else {
        if (!gic_is_priv(interrupt->id)) {
            lr |= (1ull << 41);
        }

        lr |= (state << 62);
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

    uint32_t lr_val = 0;
    int64_t lr_ind = -1;
    if ((lr_ind = gich_get_lr(interrupt, &lr_val)) >= 0) {
        gich_write_lr(lr_ind, 0);
    }

    interrupt->in_lr = false;

    if (GICH_LR_STATE(lr_val) != INV) {
        interrupt->state = GICH_LR_STATE(lr_val);

        if ((interrupt->state & PEND) && interrupt->enabled) {
            MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) | GICH_HCR_NPIE_BIT);
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
    uint32_t elrsr = MRS(ICH_ELRSR_EL2);
    /* TODO: this could be probably be optimized with bit operations */
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
            uint32_t lr = gich_read_lr(i);
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
            MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) | GICH_HCR_NPIE_BIT);
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
                vgicd->CTLR =
                    vcpu_readreg(cpu.vcpu, acc->reg) & GICD_CTLR_ENA_BIT;
                if (prev_ctrl ^ vgicd->CTLR) {
                    bool enable = vgicd->CTLR ? true : false;
                    if (enable)
                        MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) | GICH_HCR_En_BIT);
                    else
                        MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) & ~GICH_HCR_En_BIT);

                    cpu_msg_t msg = {
                        VGICV3_IPI_ID, VGIC_ENABLE,
                        VGIC_MSG_DATA(cpu.vcpu->vm->id, 0, 0, enable)};
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


static inline bool vgic_broadcast(vcpu_t *vcpu, vgic_int_t *interrupt) 
{
    return (interrupt->route & GICD_IROUTER_IRM_BIT);
}

static inline bool vgic_pcpu_is_target(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool priv = gic_is_priv(interrupt->id);
    bool local = priv && (interrupt->phys.redist == cpu.id);
    bool routed_here =
        !priv && !(interrupt->phys.route ^ MRS(MPIDR_EL1) & MPIDR_AFF_MSK);
    bool any = !priv && vgic_broadcast(vcpu, interrupt);
    return local || routed_here || any;
}

static inline bool vgic_has_other_target(vcpu_t *vcpu, vgic_int_t *interrupt) 
{
    bool priv = gic_is_priv(interrupt->id);
    bool routed_here =
        !priv && !(interrupt->phys.route ^ MRS(MPIDR_EL1) & MPIDR_AFF_MSK);
    bool route_valid = interrupt->phys.route != GICD_IROUTER_INV;
    bool any = !priv && vgic_broadcast(vcpu, interrupt);
    return any || (!routed_here && route_valid);
}

void vgic_route(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    if ((interrupt->state == INV) || !interrupt->enabled) {
        return;
    }

    if(gic_is_sgi(interrupt->id) && !vgic_pcpu_is_target(vcpu, interrupt)) {
        ERROR("cpu not target for sgi?");
    }

    if (vgic_pcpu_is_target(vcpu, interrupt)) {
        vgic_add_lr(vcpu, interrupt);
    }

    if (!interrupt->in_lr && vgic_has_other_target(vcpu, interrupt)) {
        cpu_msg_t msg = {
            VGICV3_IPI_ID, VGIC_ROUTE,
            VGIC_MSG_DATA(vcpu->vm->id, vcpu->id, interrupt->id, 0)};
        vgic_yield_ownership(vcpu, interrupt);
        if (vgic_broadcast(vcpu, interrupt)) {
            vm_msg_broadcast(vcpu->vm, &msg);
        } else {
            uint64_t pcpuid = gic_is_priv(interrupt->id) ? 
                interrupt->phys.redist : cpu_mpidr_to_id(interrupt->phys.route);
            cpu_send_msg(pcpuid, &msg);
        }
    }
}

void vgic_set_enable(vcpu_t *vcpu, uint64_t int_id, bool en, uint64_t vgicr_id)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id, vgicr_id);

    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        if (interrupt->enabled ^ en) {
            interrupt->enabled = en;
            if (!interrupt->enabled) {
                vgic_remove_lr(vcpu, interrupt);
            } else {
                vgic_route(vcpu, interrupt);
            }
            if (interrupt->hw) {
                if (gic_is_priv(int_id)) {
                    uint64_t pgicr_id =
                        vm_translate_to_pcpuid(vcpu->vm, vgicr_id);
                    gicr_set_enable(int_id, en, pgicr_id);
                } else {
                    gicd_set_enable(int_id, en);
                }
            }
        }
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {VGICV3_IPI_ID, VGIC_SET_EN,
                         VGIC_MSG_DATA(vcpu->vm->id, vgicr_id, int_id, en)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

bool vgic_get_enable(vcpu_t *vcpu, uint64_t int_id, uint64_t vgicr_id)
{
    return vgic_get_int(vcpu, int_id, vgicr_id)->enabled;
}

void vgic_emul_isenabler_access(emul_access_t *acc, uint64_t vgicr_id)
{
    uint64_t reg_ind = (acc->addr & 0x7F) / sizeof(uint32_t);
    uint32_t val;
    uint64_t first_int = 32 * reg_ind;

    if (acc->write) {
        val = vcpu_readreg(cpu.vcpu, acc->reg);
        for (int i = 0; i < 32; i++) {
            if (bit_get(val, i)) {
                vgic_set_enable(cpu.vcpu, i + first_int, true, vgicr_id);
            }
        }
    } else {
        val = 0;
        for (int i = 0; i < 32; i++) {
            if (vgic_get_enable(cpu.vcpu, i + first_int, vgicr_id)) {
                val |= 1U << i;
            }
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgic_emul_icenabler_access(emul_access_t *acc, uint64_t vgicr_id)
{
    uint64_t reg_ind = (acc->addr & 0x7F) / sizeof(uint32_t);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    uint64_t first_int = 32 * reg_ind;

    if (acc->write) {
        for (int i = 0; i < 32; i++) {
            if (bit_get(val, i)) {
                vgic_set_enable(cpu.vcpu, i + first_int, false, vgicr_id);
            }
        }
    } else {
        for (int i = 0; i < 32; i++) {
            if (vgic_get_enable(cpu.vcpu, i + first_int, vgicr_id)) {
                val |= 1U << i;
            }
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgic_set_pend(vcpu_t *vcpu, uint64_t int_id, bool pend, uint64_t vgicr_id)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id & 0x3ff, vgicr_id);

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
            uint8_t state = interrupt->state == PEND ? ACT : interrupt->state;
            if (gic_is_priv(int_id)) {
                uint64_t pgicr_id = vm_translate_to_pcpuid(vcpu->vm, vgicr_id);
                gicr_set_state(int_id, state, pgicr_id);
            } else {
                gicd_set_state(int_id, state);
            }
        }

        vgic_route(vcpu, interrupt);
        vgic_yield_ownership(vcpu, interrupt);

    } else {
        cpu_msg_t msg = {VGICV3_IPI_ID, VGIC_SET_PEND,
                         VGIC_MSG_DATA(vcpu->vm->id, vgicr_id, int_id, pend)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }

    spin_unlock(&interrupt->lock);
}

void vgic_emul_pendr_access(emul_access_t *acc, bool set, uint64_t vgicr_id)
{
    uint64_t reg_ind = (acc->addr & 0x7F) / sizeof(uint32_t);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    uint64_t first_int = 32 * reg_ind;

    if (acc->write) {
        for (int i = 0; i < 32; i++) {
            if (bit_get(val, i)) {
                vgic_set_pend(cpu.vcpu, i + first_int, set, vgicr_id);
            }
        }
    } else {
        for (int i = 0; i < 32; i++) {
            vgic_int_t *interrupt =
                vgic_get_int(cpu.vcpu, i + first_int, vgicr_id);
            if (vgic_get_state(interrupt) & PEND) {
                val |= 1 << i;
            }
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgic_emul_ispendr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    vgic_emul_pendr_access(acc, true, vgicr_id);
}

void vgic_emul_icpendr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    vgic_emul_pendr_access(acc, false, vgicr_id);
}

void vgic_set_actv(vcpu_t *vcpu, uint64_t int_id, bool act, uint64_t vgicr_id)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id & 0x3ff, vgicr_id);

    spin_lock(&interrupt->lock);

    if (vgic_get_ownership(vcpu, interrupt)) {
        vgic_remove_lr(vcpu, interrupt);
        uint8_t state = interrupt->state;
        if (act && !(state & ACT)) {
            interrupt->state = state | ACT;
        } else if (!act && (state & ACT)) {
            interrupt->state = state & ~ACT;
        }

        if (interrupt->hw) {
            uint8_t state = interrupt->state == PEND ? ACT : interrupt->state;
            if (gic_is_priv(int_id)) {
                uint64_t pgicr_id = vm_translate_to_pcpuid(vcpu->vm, vgicr_id);
                gicr_set_state(int_id, state, pgicr_id);
            } else {
                gicd_set_state(int_id, state);
            }
        }

        vgic_route(vcpu, interrupt);
        vgic_yield_ownership(vcpu, interrupt);

    } else {
        cpu_msg_t msg = {VGICV3_IPI_ID, VGIC_SET_PEND,
                         VGIC_MSG_DATA(vcpu->vm->id, vgicr_id, int_id, act)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }

    spin_unlock(&interrupt->lock);
}

void vgic_emul_activer_access(emul_access_t *acc, bool set, uint64_t vgicr_id)
{
    uint64_t reg_ind = (acc->addr & 0x7F) / sizeof(uint32_t);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    uint64_t first_int = 32 * reg_ind;

    if (acc->write) {
        for (int i = 0; i < 32; i++) {
            if (bit_get(val, i)) {
                vgic_set_actv(cpu.vcpu, i + first_int, set, vgicr_id);
            }
        }
    } else {
        for (int i = 0; i < 32; i++) {
            vgic_int_t *interrupt =
                vgic_get_int(cpu.vcpu, i + first_int, vgicr_id);
            if (vgic_get_state(interrupt) & ACT) {
                val |= 1 << i;
            }
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgic_emul_isactiver_access(emul_access_t *acc, uint64_t vgicr_id)
{
    vgic_emul_activer_access(acc, true, vgicr_id);
}

void vgic_emul_icactiver_access(emul_access_t *acc, uint64_t vgicr_id)
{
    vgic_emul_activer_access(acc, false, vgicr_id);
}

void vgic_set_prio(vcpu_t *vcpu, uint64_t int_id, uint8_t prio,
                   uint64_t vgicr_id)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id, vgicr_id);
    prio &= 0xf0;  // priority bits are implementation defined up to 8
    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        if (interrupt->prio != prio) {
            vgic_remove_lr(vcpu, interrupt);
            uint8_t prev_prio = interrupt->prio;
            interrupt->prio = prio;
            if (prio <= prev_prio) {
                vgic_route(vcpu, interrupt);
            }
            if (interrupt->hw) {
                if (gic_is_priv(int_id)) {
                    uint64_t pgicr_id =
                        vm_translate_to_pcpuid(vcpu->vm, vgicr_id);
                    gicr_set_prio(int_id, (prio >> 1) | 0x80, pgicr_id);
                } else {
                    gicd_set_prio(int_id, (prio >> 1) | 0x80);
                }
            }
        }
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {VGICV3_IPI_ID, VGIC_SET_PRIO,
                         VGIC_MSG_DATA(vcpu->vm->id, vgicr_id, int_id, prio)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

uint8_t vgic_get_prio(vcpu_t *vcpu, uint64_t int_id, uint64_t vgicr_id)
{
    return vgic_get_int(vcpu, int_id, vgicr_id)->prio;
}

void vgic_emul_ipriorityr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    /* We look at prio regs as 8 bit registers */
    uint64_t first_int = (8 / GIC_PRIO_BITS) * (acc->addr & 0x1ff);
    uint32_t val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;

    if (acc->write) {
        for (int i = 0; i < acc->width; i++) {
            vgic_set_prio(cpu.vcpu, first_int + i,
                          bit_extract(val, GIC_PRIO_BITS * i, GIC_PRIO_BITS),
                          vgicr_id);
        }
    } else {
        for (int i = 0; i < acc->width; i++) {
            val |= vgic_get_prio(cpu.vcpu, first_int + i, vgicr_id)
                   << (GIC_PRIO_BITS * i);
        }
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

void vgicd_emul_itargetr_access(emul_access_t *acc)
{
    if (!acc->write) vcpu_writereg(cpu.vcpu, acc->reg, 0);
}

uint8_t vgic_get_icfgr(vcpu_t *vcpu, uint64_t int_id, uint64_t vgicr_id)
{
    return vgic_get_int(vcpu, int_id, vgicr_id)->cfg;
}

void vgic_set_icfgr(vcpu_t *vcpu, uint64_t int_id, uint8_t cfg,
                    uint64_t vgicr_id)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id, vgicr_id);

    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        interrupt->cfg = cfg;
        if (interrupt->hw) {
            if (gic_is_priv(int_id)) {
                gicr_set_icfgr(int_id, cfg,
                               vm_translate_to_pcpuid(vcpu->vm, vgicr_id));
            } else {
                gicd_set_icfgr(int_id, cfg);
            }
        }
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {VGICV3_IPI_ID, VGIC_SET_CFG,
                         VGIC_MSG_DATA(vcpu->vm->id, vgicr_id, int_id, cfg)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

void vgic_emul_icfgr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    uint32_t cfg;
    uint64_t first_int = (32 / GIC_CONFIG_BITS) * (acc->addr & 0x1ff) / 4;

    if (acc->write) {
        cfg = vcpu_readreg(cpu.vcpu, acc->reg);
        for (int irq = first_int, bit = 0; bit < acc->width * 8;
             bit += 2, irq++) {
            vgic_set_icfgr(cpu.vcpu, irq, (cfg >> bit) & 0b11, vgicr_id);
        }
    } else {
        cfg = 0;
        for (int irq = first_int, bit = 0; bit < acc->width * 8;
             bit += 2, irq++) {
            /* assume vgicd_get_icfgr returns two bit values on the lsbits */
            cfg |= vgic_get_icfgr(cpu.vcpu, irq, vgicr_id) << bit;
        }
        vcpu_writereg(cpu.vcpu, acc->reg, cfg);
    }
}

void vgicd_set_irouter(vcpu_t *vcpu, uint64_t int_id, uint64_t irouter)
{
    vgic_int_t *interrupt = vgic_get_int(vcpu, int_id, vcpu->id);

    if (gic_is_priv(interrupt->id) || interrupt->route == irouter) {
        return;
    }

    spin_lock(&interrupt->lock);
    if (vgic_get_ownership(vcpu, interrupt)) {
        interrupt->route = irouter & GICD_IROUTER_RES0_MSK;
        if (interrupt->hw) {
            vgic_remove_lr(vcpu, interrupt);
            if (irouter & GICD_IROUTER_IRM_BIT) {
                irouter = cpu_id_to_mpidr(vcpu->phys_id);
            } else {
                vcpu_t *tvcpu =
                    vm_get_vcpu_by_mpidr(vcpu->vm, irouter & MPIDR_AFF_MSK);
                if (tvcpu != NULL) {
                    irouter = cpu_id_to_mpidr(tvcpu->phys_id) & MPIDR_AFF_MSK;
                } else {
                    irouter = GICD_IROUTER_INV;
                }
            }
            interrupt->phys.route = irouter;
            gic_set_route(int_id, irouter);
        }
        vgic_route(vcpu, interrupt);
        vgic_yield_ownership(vcpu, interrupt);
    } else {
        cpu_msg_t msg = {
            VGICV3_IPI_ID, VGIC_SET_IROUTER,
            VGIC_MSG_DATA(vcpu->vm->id, 0, interrupt->id, irouter)};
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

uint64_t vgicd_get_irouter(vcpu_t *vcpu, uint64_t int_id)
{
    return vgic_get_int(vcpu, int_id, vcpu->id)->route;
}

void vgicd_emul_irouter_access(emul_access_t *acc)
{
    uint64_t int_id = ((acc->addr & 0xffff) - offsetof(gicd_t, IROUTER)) /
                      sizeof(gicd.IROUTER[0]);

    bool irq_has_router = !gic_is_priv(int_id) && (int_id < gic_num_irqs());

    uint64_t irouter;
    if (irq_has_router && acc->write) {
        irouter = vcpu_readreg(cpu.vcpu, acc->reg);
        vgicd_set_irouter(cpu.vcpu, int_id, irouter);
    } else if (!acc->write) {
        irouter = irq_has_router ? vgicd_get_irouter(cpu.vcpu, int_id) : 0;
        vcpu_writereg(cpu.vcpu, acc->reg, irouter);
    }
}

void vgicd_emul_id_access(emul_access_t *acc)
{
    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg,
                      gicd.ID[((acc->addr & 0xff) - 0xd0) / 4]);
    }
}

bool vgicd_emul_handler(emul_access_t *acc)
{
    if (acc->width > 8) return false;

    uint32_t acc_offset = acc->addr & 0xfff;

    switch ((acc->addr & 0xff80) >> 7) {
        case GICD_REG_GROUP(CTLR):
        case GICD_REG_GROUP(ISENABLER):
        case GICD_REG_GROUP(ISPENDR):
        case GICD_REG_GROUP(ISACTIVER):
        case GICD_REG_GROUP(ICENABLER):
        case GICD_REG_GROUP(ICPENDR):
        case GICD_REG_GROUP(ICACTIVER):
        case GICD_REG_GROUP(ICFGR):
        case GICD_REG_GROUP(ID):
            /* Only allow aligned 32-bit accesses or byte */
            if (acc->width != 4 || acc->addr & 0x3) {
                ERROR("vgicv3: missaligned access");
                return false;
            }
            break;
        default:
            if (GICD_IS_REG(IPRIORITYR, acc_offset) ||
                GICD_IS_REG(ITARGETSR, acc_offset)) {
                /* Allow byte access or align 16-bit accesses */
                if ((acc->width == 4 && (acc->addr & 0x3)) ||
                    (acc->width == 2 && (acc->addr & 0x1))) {
                    ERROR("vgicv3: missaligned access");
                    return false;
                }
            }
    }

    // spin_lock(&cpu.vcpu->vm->arch.vgicd.lock);
    switch ((acc->addr & 0xff80) >> 7) {
        case GICD_REG_GROUP(CTLR):
            vgicd_emul_misc_access(acc);
            break;
        case GICD_REG_GROUP(ISENABLER):
            vgic_emul_isenabler_access(acc, cpu.vcpu->id);
            break;
        case GICD_REG_GROUP(ISPENDR):
            vgic_emul_ispendr_access(acc, cpu.vcpu->id);
            break;
        case GICD_REG_GROUP(ISACTIVER):
            vgic_emul_isactiver_access(acc, cpu.vcpu->id);
            break;
        case GICD_REG_GROUP(ICENABLER):
            vgic_emul_icenabler_access(acc, cpu.vcpu->id);
            break;
        case GICD_REG_GROUP(ICPENDR):
            vgic_emul_icpendr_access(acc, cpu.vcpu->id);
            break;
        case GICD_REG_GROUP(ICACTIVER):
            vgic_emul_icactiver_access(acc, cpu.vcpu->id);
            break;
        case GICD_REG_GROUP(ICFGR):
            vgic_emul_icfgr_access(acc, cpu.vcpu->id);
            break;
        case GICD_REG_GROUP(IROUTER)... GICD_REG_GROUP(IROUTER[1023]):
            vgicd_emul_irouter_access(acc);
            break;
        case GICD_REG_GROUP(ID):
            vgicd_emul_id_access(acc);
            break;
        default:
            if (GICD_IS_REG(IPRIORITYR, acc_offset)) {
                vgic_emul_ipriorityr_access(acc, cpu.vcpu->id);
            } else if (GICD_IS_REG(ITARGETSR, acc_offset)) {
                vgicd_emul_itargetr_access(acc);
            }
    }
    // spin_unlock(&cpu.vcpu->vm->arch.vgicd.lock);

    return true;
}

static inline uint32_t vgicr_get_id(emul_access_t *acc)
{
    return (acc->addr - cpu.vcpu->vm->arch.gic->gicr_addr) / sizeof(gicr_t);
}

void vgicr_emul_ctlr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    // we are not actually supporting any of the write bits in gicr.CTLR
    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg, 0);
    }
}

uint32_t vgicr_get_iidr(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_iidr");
    return 0;
}

void vgicr_set_iidr(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                    uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_iidr");
}

void vgicr_emul_iidr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_iidr_access");
}

void vgicr_emul_typer_access(emul_access_t *acc, uint64_t vgicr_id)
{
    if (!acc->write) {
        vcpu_t *vcpu = vm_get_vcpu(cpu.vcpu->vm, vgicr_id);
        vcpu_writereg(cpu.vcpu, acc->reg, vcpu->arch.vgic_priv.vgicr.TYPER);
    } else {
        ERROR("No emulation for: vgicr_emul_typer_access");
    }
}

uint32_t vgicr_get_statusr(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_statusr");
    return 0;
}

void vgicr_set_statusr(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                       uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_statusr");
}

void vgicr_emul_statusr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_statusr_access");
}

void vgicr_emul_waker_access(emul_access_t *acc, uint64_t vgicr_id)
{
    /**
     * We are making waker RO, and it is not possible to make the
     * redistributor sleep.
     * TODO: is this in spec?
     */
    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg, 0);
    }
}

uint32_t vgicr_get_clrlpir(vcpu_t *vcpu, uint32_t int_id, uint32_t gicr_id)
{
    ERROR("No emulation for: vgicr_get_clrlpir");
    return 0;
}

void vgicr_set_clrlpir(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                       uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_clrlpir");
}

void vgicr_emul_clrlpir_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_clrlpir_access");
}

uint32_t vgicr_get_setlpir(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_setlpir");
    return 0;
}

void vgicr_set_setlpir(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                       uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_setlpir");
}

void vgicr_emul_setlpir_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_setlpir_access");
}

uint32_t vgicr_get_propbaser(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_propbaser");
    return 0;
}

void vgicr_set_propbaser(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                         uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_propbaser");
}

void vgicr_emul_propbaser_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_propbaser_access");
}

uint32_t vgicr_get_pendbaser(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_pendbaser");
    return 0;
}

void vgicr_set_pendbaser(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                         uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_pendbaser");
}

void vgicr_emul_pendbaser_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_pendbaser_access");
}

uint32_t vgicr_get_invlpir(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_invlpir");
    return 0;
}

void vgicr_set_invlpir(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                       uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_invlpir");
}

void vgicr_emul_invlpir_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_invlpir_access");
}

uint32_t vgicr_get_invallr(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_invallr");
    return 0;
}

void vgicr_set_invallr(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                       uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_invallr");
}

void vgicr_emul_invallr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_invallr_access");
}

uint32_t vgicr_get_syncr(vcpu_t *vcpu, uint32_t int_id, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_get_syncr");
    return 0;
}

void vgicr_set_syncr(vcpu_t *vcpu, uint32_t int_id, uint32_t val,
                     uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_set_syncr");
}

void vgicr_emul_syncr_access(emul_access_t *acc, uint64_t vgicr_id)
{
    ERROR("No emulation for: vgicr_emul_syncr_access");
}

void vgicr_emul_id_access(emul_access_t *acc, uint64_t vgicr_id)
{
    if (!acc->write) {
        uint64_t pgicr_id = vm_translate_to_pcpuid(cpu.vcpu->vm, vgicr_id);
        vcpu_writereg(cpu.vcpu, acc->reg,
                      gicr[pgicr_id].ID[((acc->addr & 0xff) - 0xd0) / 4]);
    }
}

bool vgicr_emul_handler(emul_access_t *acc)
{
    uint32_t acc_offset = acc->addr & 0xffff;

    // switch ((acc->addr & 0xf80) >> 7) {
    //     case GICD_REG_GROUP(CTLR):
    //     case GICD_REG_GROUP(ISENABLER):
    //     case GICD_REG_GROUP(ISPENDR):
    //     case GICD_REG_GROUP(ISACTIVER):
    //     case GICD_REG_GROUP(ICENABLER):
    //     case GICD_REG_GROUP(ICPENDR):
    //     case GICD_REG_GROUP(ICACTIVER):
    //     case GICD_REG_GROUP(ICFGR):
    //         /* Only allow aligned 32-bit accesses or byte */
    //         if (acc->width != 4 || acc->addr & 0x3) {
    //             return false;
    //         }
    //         break;

    //     case GICD_REG_GROUP(SGIR):
    //         /* Allow byte access or align 16-bit accesses */
    //         if ((acc->width == 4 && (acc->addr & 0x3)) ||
    //             (acc->width == 2 && (acc->addr & 0x1))) {
    //             return false;
    //         }
    //         break;

    //     default:
    //         if (GICD_IS_REG(IPRIORITYR, acc_offset) ||
    //             GICD_IS_REG(ITARGETSR, acc_offset)) {
    //             /* Allow byte access or align 16-bit accesses */
    //             if ((acc->width == 4 && (acc->addr & 0x3)) ||
    //                 (acc->width == 2 && (acc->addr & 0x1))) {
    //                 return false;
    //             }
    //         }
    // }

    uint64_t vgicr_id = vgicr_get_id(acc);

    // spin_lock(&cpu.vcpu->vm->arch.vgicd.lock);
    if (!(acc->addr & 0x10000)) {
        switch ((acc->addr & 0xffff)) {
            case GICR_REG_OFF(CTLR):
                vgicr_emul_ctlr_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(IIDR):
                vgicr_emul_iidr_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(TYPER):
                vgicr_emul_typer_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(STATUSR):
                vgicr_emul_statusr_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(WAKER):
                vgicr_emul_waker_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(SETLPIR):
                vgicr_emul_setlpir_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(CLRLPIR):
                vgicr_emul_clrlpir_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(PROPBASER):
                vgicr_emul_propbaser_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(PENDBASER):
                vgicr_emul_pendbaser_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(INVLPIR):
                vgicr_emul_invlpir_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(INVALLR):
                vgicr_emul_invallr_access(acc, vgicr_id);
                break;
            case GICR_REG_OFF(SYNCR):
                vgicr_emul_syncr_access(acc, vgicr_id);
                break;
            default:
                if (GICR_IS_REG(ID, acc->addr & 0xffff))
                    vgicr_emul_id_access(acc, vgicr_id);
                else
                    ERROR("trying to access unsoported register in gicr 0x%x",
                          acc->addr);
                break;
        }
    } else {
        switch ((acc->addr & 0xf80) >> 7) {
            case GICR_REG_GROUP(ISENABLER0):
                vgic_emul_isenabler_access(acc, vgicr_id);
                break;
            case GICR_REG_GROUP(ICENABLER0):
                vgic_emul_icenabler_access(acc, vgicr_id);
                break;
            case GICR_REG_GROUP(ISPENDR0):
                vgic_emul_ispendr_access(acc, vgicr_id);
                break;
            case GICR_REG_GROUP(ICPENDR0):
                vgic_emul_icpendr_access(acc, vgicr_id);
                break;
            case GICR_REG_GROUP(ISACTIVER0):
                vgic_emul_isactiver_access(acc, vgicr_id);
                break;
            case GICR_REG_GROUP(ICACTIVER0):
                vgic_emul_icactiver_access(acc, vgicr_id);
                break;
            case GICR_REG_GROUP(IPRIORITYR):
                vgic_emul_ipriorityr_access(acc, vgicr_id);
                break;
            case GICR_REG_GROUP(ICFGR0):
                /* ICFGR0 and ICFGR1 fall on the same group */
                vgic_emul_icfgr_access(acc, vgicr_id);
                break;
        }
    }
    // spin_unlock(&cpu.vcpu->vm->arch.vgicd.lock);

    return true;
}

static inline uint64_t icc_sgir_to_base_aff(uint64_t sgir)
{
    // Only 2 affinity levels are supported
    return (sgir & 0xff00) >> 8;
}

bool vgic_icc_sgir_handler(emul_access_t *acc)
{
    if (acc->write) {
        uint64_t sgir = vcpu_readreg(cpu.vcpu, acc->reg);

        uint64_t int_id = ICC_SGIR_SGIINTID(sgir);

        if (sgir & ICC_SGIR_IRM_BIT) {
            cpu_msg_t msg = {VGICV3_IPI_ID, VGIC_SET_PEND, 
                    VGIC_MSG_DATA(cpu.vcpu->vm->id, 0, int_id, true)}; //??
            vm_msg_broadcast(cpu.vcpu->vm, &msg);
        } else {
            uint64_t trgtlist = ICC_SGIR_TRGLSTFLT(sgir);
            uint64_t baseid = icc_sgir_to_base_aff(sgir);

            for (int i = 0; i < GIC_TARGET_BITS; i++) {
                if (trgtlist & (1U << i)) {
                    uint64_t vcpuid = baseid + i;
                    cpu_msg_t msg = {VGICV3_IPI_ID, VGIC_SET_PEND,
                         VGIC_MSG_DATA(cpu.vcpu->vm->id, vcpuid, int_id, true)};
                    cpu_send_msg(vm_translate_to_pcpuid(cpu.vcpu->vm, vcpuid),
                                 &msg);
                }
            }
        }
    }

    return true;
}

bool vgic_icc_sre_handler(emul_access_t *acc)
{
    if(!acc->write){
	    vcpu_writereg(cpu.vcpu, acc->reg, 0x1);
    }
    return true;
}

void vgic_inject(vgicd_t *vgicd, uint64_t id)
{
    vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, id & 0x3ff, cpu.vcpu->id);
    if (interrupt->hw) {
        spin_lock(&interrupt->lock);
        interrupt->owner = cpu.vcpu;
        interrupt->state = PEND;
        interrupt->in_lr = false;
        vgic_route(cpu.vcpu, interrupt);
        spin_unlock(&interrupt->lock);
    } else {
        vgic_set_pend(cpu.vcpu, id, true, cpu.vcpu->id);
    }
}

void gicv3_ipi_handler(uint32_t event, uint64_t data)
{
    uint8_t val = VGIC_MSG_VAL(data);
    uint16_t int_id = VGIC_MSG_INTID(data);
    uint16_t vm_id = VGIC_MSG_VM(data);
    uint16_t vgicr_id = VGIC_MSG_VGICRID(data);

    if (vm_id != cpu.vcpu->vm->id) {
        ERROR("received vgic3 msg target to another vcpu");
        // TODO: need to fetch vcpu from other vm if the taget vm for this
        // is not active
    }

    switch (event) {
        case VGIC_ENABLE: {
            bool enable = data ? true : false;
            if (enable)
                MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) | GICH_HCR_En_BIT);
            else
                MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) & ~GICH_HCR_En_BIT);
        } break;

        case VGIC_SET_EN: {
            vgic_set_enable(cpu.vcpu, int_id, val, vgicr_id);
        } break;

        case VGIC_SET_PEND: {
            vgic_set_pend(cpu.vcpu, int_id, val, vgicr_id);
        } break;

        case VGIC_SET_PRIO: {
            vgic_set_prio(cpu.vcpu, int_id, val, vgicr_id);
        } break;

        case VGIC_SET_IROUTER: {
            vgicd_set_irouter(cpu.vcpu, int_id, val);
        } break;

        case VGIC_ROUTE: {
            vgic_int_t *interrupt = vgic_get_int(cpu.vcpu, int_id, vgicr_id);
            spin_lock(&interrupt->lock);
            if (vgic_get_ownership(cpu.vcpu, interrupt)) {
                if (vgic_pcpu_is_target(cpu.vcpu, interrupt)) {
                    vgic_add_lr(cpu.vcpu, interrupt);
                }
                vgic_yield_ownership(cpu.vcpu, interrupt);
            }
            spin_unlock(&interrupt->lock);
        } break;
    }
}

void vgic_refill_lrs(vcpu_t *vcpu)
{
    bool has_pending = false;
    for (int i = 0; i < NUM_LRS; i++) {
        uint32_t lr = gich_read_lr(i);
        if (GICH_LR_STATE(lr) & PEND) {
            has_pending = true;
            break;
        }
    }

    int64_t lr_ind;
    uint32_t elrsr;
    while (elrsr = MRS(ICH_EISR_EL2),
           (lr_ind = bitmap_find_nth((bitmap_t)&elrsr, NUM_LRS, 1, 0, true)) >=
               0) {
        vgic_int_t *interrupt = NULL;
        uint8_t state = INV;

        for (int i = 0; i < gic_num_irqs(); i++) {
            vgic_int_t *temp_int = vgic_get_int(vcpu, i, vcpu->id);
            spin_lock(&temp_int->lock);

            if (vgic_get_ownership(vcpu, temp_int)) {
                uint8_t temp_state = vgic_get_state(temp_int);
                bool cpu_is_target = vgic_pcpu_is_target(vcpu, temp_int);
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
                vgic_yield_ownership(vcpu, temp_int);
                spin_unlock(&temp_int->lock);
            }
        }

        if (interrupt != NULL) {
            vgic_write_lr(vcpu, interrupt, lr_ind);
            if (state & PEND) has_pending = true;
            spin_unlock(&interrupt->lock);
        } else {
            MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) & ~(GICH_HCR_NPIE_BIT));
            break;
        }
    }
}

void vgic_eoir_highest_spilled_active(vcpu_t *vcpu)
{
    vgic_int_t *interrupt = NULL;
    for (int i = 0; i < gic_num_irqs(); i++) {
        vgic_int_t *temp_int = vgic_get_int(vcpu, i, vcpu->id);
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
            if (!gic_is_priv(interrupt->id)) {
                gicd_set_act(interrupt->id, false);
            } else {
                gicr_set_act(interrupt->id, false, cpu.id);
            }
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
    uint32_t eisr = 0;
    while (
        eisr = MRS(ICH_EISR_EL2),
        (lr_ind = bitmap_find_nth((bitmap_t)&eisr, NUM_LRS, 1, 0, true)) >= 0) {
        uint32_t lr_val = gich_read_lr(lr_ind);
        gich_write_lr(lr_ind, 0);

        vgic_int_t *interrupt =
            vgic_get_int(vcpu, GICH_LR_VID(lr_val), vcpu->id);
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
    uint32_t misr = MRS(ICH_MISR_EL2);

    if (misr & GICH_MISR_EOI) {
        vgic_handle_trapped_eoir(cpu.vcpu);
    }

    if (misr & GICH_MISR_NP) {
        vgic_refill_lrs(cpu.vcpu);
    }

    if (misr & GICH_MISR_LRPEN) {
        uint32_t hcr_el2 = 0;
        while (hcr_el2 = MRS(ICH_HCR_EL2), hcr_el2 & GICH_HCR_EOICount_MASK) {
            vgic_eoir_highest_spilled_active(cpu.vcpu);
            hcr_el2 -= (1U << GICH_HCR_EOICount_OFF);
            MSR(ICH_HCR_EL2, hcr_el2);
        }
    }
}

void vgic_init(vm_t *vm, const struct gic_dscrp *gic_dscrp)
{
    vm->arch.gic = gic_dscrp;

    vm->arch.vgicd.CTLR = 0;
    vm->arch.vgicd.TYPER =
        (gicd.TYPER & GICD_TYPER_ITLN_MSK) |
        (((vm->cpu_num - 1) << GICD_TYPER_CPUN_OFF) & GICD_TYPER_CPUN_MSK) |
        (9 << 19);
    vm->arch.vgicd.IIDR = gicd.IIDR;

    for (int i = 0; i < GIC_MAX_SPIS; i++) {
        vm->arch.vgicd.interrupts[i].id = i + GIC_CPU_PRIV;
        vm->arch.vgicd.interrupts[i].owner = NULL;
        vm->arch.vgicd.interrupts[i].hw = false;
        vm->arch.vgicd.interrupts[i].enabled = false;
        vm->arch.vgicd.interrupts[i].state = INV;
        vm->arch.vgicd.interrupts[i].prio = 0xFF;
        vm->arch.vgicd.interrupts[i].route = GICD_IROUTER_INV;
        vm->arch.vgicd.interrupts[i].phys.route = GICD_IROUTER_INV;
        vm->arch.vgicd.interrupts[i].lock = 0;
    }

    emul_mem_t gicd_emu = {.va_base = gic_dscrp->gicd_addr,
                           .pa_base = (uint64_t)&gicd,
                           .size = ALIGN(sizeof(gicd_t), PAGE_SIZE),
                           .handler = vgicd_emul_handler};
    vm_emul_add_mem(vm, &gicd_emu);

    list_foreach(vm->vcpu_list, vcpu_t, vcpu)
    {
        uint64_t phy_cpuid = vcpu->phys_id;
        emul_mem_t gicr_emu = {
            .va_base = gic_dscrp->gicr_addr + sizeof(gicr_t) * vcpu->id,
            .pa_base = (uint64_t) & (gicr[phy_cpuid]),
            .size = ALIGN(sizeof(gicr_t), PAGE_SIZE),
            .handler = vgicr_emul_handler};
        vm_emul_add_mem(vm, &gicr_emu);

        vcpu->arch.vgic_priv.vgicr.CTLR = 0;

        uint64_t typer = vcpu->id << GICR_TYPER_PRCNUM_OFF;
        typer |= (vcpu->arch.vmpidr & MPIDR_AFF_MSK) << GICR_TYPER_AFFVAL_OFF;
        typer |= !!(vcpu->id == vcpu->vm->cpu_num - 1) << GICR_TYPER_LAST_OFF;
        vcpu->arch.vgic_priv.vgicr.TYPER = typer;

        vcpu->arch.vgic_priv.vgicr.IIDR = gicr[cpu.id].IIDR;
    }

    emul_reg_t icc_sgir_emu = {.addr = SYSREG_ENC_ADDR(3, 0, 12, 11, 5),
                               .handler = vgic_icc_sgir_handler};
    vm_emul_add_reg(vm, &icc_sgir_emu);

    emul_reg_t icc_sre_emu = {.addr = SYSREG_ENC_ADDR(3, 0, 12, 12, 5),
                               .handler = vgic_icc_sre_handler};
    vm_emul_add_reg(vm, &icc_sre_emu);
}

void vgic_cpu_init(vcpu_t *vcpu)
{
    for (int i = 0; i < GIC_CPU_PRIV; i++) {
        vcpu->arch.vgic_priv.interrupts[i].id = i;
        vcpu->arch.vgic_priv.interrupts[i].owner = NULL;
        vcpu->arch.vgic_priv.interrupts[i].hw = false;
        vcpu->arch.vgic_priv.interrupts[i].enabled = false;
        vcpu->arch.vgic_priv.interrupts[i].state = INV;
        vcpu->arch.vgic_priv.interrupts[i].prio = 0xff;
        vcpu->arch.vgic_priv.interrupts[i].route = GICD_IROUTER_INV;
        vcpu->arch.vgic_priv.interrupts[i].phys.redist = vcpu->phys_id;
        vcpu->arch.vgic_priv.interrupts[i].lock = 0;
        vcpu->arch.vgic_priv.interrupts[i].in_lr = 0;
        vcpu->arch.vgic_priv.interrupts[i].lr = 0;
    }

    for (int i = 0; i < GIC_MAX_SGIS; i++) {
        vcpu->arch.vgic_priv.interrupts[i].enabled = true;
    }
}
