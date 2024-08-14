/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include "inc/arch/ir.h"
#include <arch/vir.h>
#include <arch/ir.h>


#include <bit.h>
#include <cstddef>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>
#include <platform.h>

enum VIR_EVENTS { VIR_UPDATE_ENABLE, VIR_ROUTE, VIR_INJECT, VIR_SET_REG };
extern volatile const size_t VIR_IPI_ID;

#define IRD_IS_REG(REG, offset)                    \
    (((offset) >= offsetof(struct ird_hw, REG)) && \
        (offset) < (offsetof(struct ird_hw, REG) + sizeof(ird->REG)))

#define IRD_REG_GROUP(REG) ((offsetof(struct ir_int_hw, REG) & 0xffff) >> 8)
#define IRD_REG_MASK(ADDR) ((ADDR) & (0xffffUL))

/* #define IRD_REG_IND(REG)   (offsetof(struct ird_hw, REG) & 0x7f) */

#define VIR_MSG_DATA(VM_ID, VIRRID, INT_ID, REG, VAL)                   \
    (((uint64_t)(VM_ID) << 48) | (((uint64_t)(VIRRID) & 0xffff) << 32) | \
        (((INT_ID) & 0x7fff) << 16) | (((REG) & 0xff) << 8) | ((VAL) & 0xff))
#define VIR_MSG_VM(DATA)      ((DATA) >> 48)
#define VIR_MSG_VIRRID(DATA) (((DATA) >> 32) & 0xffff)
#define VIR_MSG_INTID(DATA)   (((DATA) >> 16) & 0x7fff)
#define VIR_MSG_REG(DATA)     (((DATA) >> 8) & 0xff)
#define VIR_MSG_VAL(DATA)     ((DATA) & 0xff)

void vir_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vir_ipi_handler, VIR_IPI_ID)

inline struct vir_int* vir_get_int(struct vcpu* vcpu, irqid_t int_id, vcpuid_t virr_id)
{
    if (int_id >= vcpu->vm->arch.ir_int.int_num) {
        return NULL;
    }

    return &vcpu->vm->arch.ir_int.interrupts[int_id - IR_CPU_PRIV];
}

static inline bool vir_int_is_hw(struct vir_int* interrupt)
{
    return interrupt->hw;
}

static inline ssize_t irh_get_lr(struct vir_int* interrupt, ir_lr_t* lr)
{
    if (!interrupt->in_lr || interrupt->owner->phys_id != cpu()->id) {
        return -1;
    }

    ir_lr_t lr_val = (ir_lr_t)irh_read_lr(interrupt->lr);
    if (((irqid_t)(IRH_LR_VID(lr_val)) == interrupt->id) && (IRH_LR_STATE(lr_val) != INV)) {
        if (lr != NULL) {
            *lr = lr_val;
        }
        return interrupt->lr;
    }

    return -1;
}

static inline uint8_t vir_get_state(struct vir_int* interrupt)
{
    uint8_t state = 0;

    ir_lr_t lr_val = 0;
    if (irh_get_lr(interrupt, &lr_val) >= 0) {
        state = (uint8_t)IRH_LR_STATE(lr_val);
    } else {
        state = interrupt->state;
    }

#if (IR_VERSION == IRV2)
    if (interrupt->id < IR_MAX_SGIS && interrupt->sgi.pend) {
        state |= PEND;
    }
#endif

    return state;
}

bool vir_get_ownership(struct vcpu* vcpu, struct vir_int* interrupt)
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

static bool vir_owns(struct vcpu* vcpu, struct vir_int* interrupt)
{
    return interrupt->owner == vcpu;
}

void vir_yield_ownership(struct vcpu* vcpu, struct vir_int* interrupt)
{
    if ((IR_VERSION == IRV2 && ir_is_priv(interrupt->id)) || !vir_owns(vcpu, interrupt) ||
        interrupt->in_lr || (vir_get_state(interrupt) & ACT)) {
        return;
    }

    interrupt->owner = NULL;
}

void vir_send_sgi_msg(struct vcpu* vcpu, cpumap_t pcpu_mask, irqid_t int_id)
{
    UNUSED_ARG(vcpu);

    struct cpu_msg msg = {
        (uint32_t)VIR_IPI_ID,
        VIR_INJECT,
        VIR_MSG_DATA(cpu()->vcpu->vm->id, 0, int_id, 0, cpu()->vcpu->id),
    };

    for (size_t i = 0; i < platform.cpu_num; i++) {
        if (pcpu_mask & (1ULL << i)) {
            cpu_send_msg(i, &msg);
        }
    }
}

static void vir_route(struct vcpu* vcpu, struct vir_int* interrupt)
{
    if ((interrupt->state == INV) || !interrupt->enabled) {
        return;
    }

    if (vir_int_vcpu_is_target(vcpu, interrupt)) {
        ir_set_pend(vcpu, interrupt);
    }

    if (!interrupt->in_lr && vir_int_has_other_target(vcpu, interrupt)) {
        struct cpu_msg msg = {
            (uint32_t)VIR_IPI_ID,
            VIR_ROUTE,
            VIR_MSG_DATA(vcpu->vm->id, vcpu->id, interrupt->id, 0, 0),
        };
        vir_yield_ownership(vcpu, interrupt);
        cpumap_t trgtlist = vir_int_ptarget_mask(vcpu, interrupt) & ~(1UL << vcpu->phys_id);
        for (size_t i = 0; i < platform.cpu_num; i++) {
            if (trgtlist & (1ULL << i)) {
                cpu_send_msg(i, &msg);
            }
        }
    }
}


#define VIR_ENABLE_MASK ((IR_VERSION == IRV2) ? IRD_CTLR_EN_BIT : IRD_CTLR_ENA_BIT)

static inline void vir_update_enable(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);

    if (cpu()->vcpu->vm->arch.ir_int.CTLR & VIR_ENABLE_MASK) {
        irh_set_hcr(irh_get_hcr() | IRH_HCR_En_BIT);
    } else {
        irh_set_hcr(irh_get_hcr() & ~IRH_HCR_En_BIT);
    }
}

static void ir_int_emul_misc_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    bool irr_access, cpuid_t virr_id)
{
    UNUSED_ARG(handlers);
    UNUSED_ARG(irr_access);
    UNUSED_ARG(virr_id);

}

static void ir_int_emul_accen_acces(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    cpuid_t vcpuid, uint32_t field_offset)
{
    uint32_t acc_addr = IRD_REG_MASK(acc->addr);
    uint32_t acc_int_offset = acc_addr - field_offset;

    uint32_t idx = acc_int_offset / sizeof(struct IR_ACCESSEN);

    /* TODO: virtualize group? */

    /* TODO figure which masters this vm can control */

    if (!acc->write) {
        /* TODO */
        /* vcpu_writereg(cpu()->vcpu, acc->reg, ); */
    }
}

static void ir_int_emul_accensrb_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    cpuid_t vcpuid)
{
    /* TODO: something like this */
    ir_int_emul_accen_acces(acc, handlers, vcpuid, offsetof(struct ir_int_hw, ir_int->ACCENSRB));
}

static void vir_emul_icu_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    cpuid_t vcpuid)
{
    uint32_t acc_addr = IRD_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct ir_int_hw, ir_int->icu);
    uint32_t icu_offset = acc_addr - offset;
    uint32_t idx = icu_offset/sizeof(ir_int->ICU);

    /* TODO figure out if VM can access ICU */
    bool can_acces_icu = true;

    if(!can_acces_icu){
        ERROR("Trying to access unauthorized ICU %u", idx);
    }

    uint32_t field_offset = icu_offset - idx * sizeof(ir_int->icu);

    if(field_offset == offsetof(struct ir_int_icu, ir_int->ICU[0].LASR)){
        /* TODO */
    } else if(field_offset == offsetof(struct ir_int_icu, ir_int->ICU[0].ECR)){
        /* TODO */
    } else if(field_offset == offsetof(struct ir_int_icu, ir_int->ICU[0].ECTRL)){
        /* TODO */
    } else if(field_offset == offsetof(struct ir_int_icu, ir_int->ICU[0].EGEN)){
        /* TODO */
    } else {
        ERROR("Trying to access unauthorized ICU register 0x%x", offset);
    }
}

static void vir_emul_tos_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    cpuid_t vcpuid)
{
    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct ir_int_hw, ir_int->TOS);
    uint32_t tos_offset = acc_addr - offset;
    uint32_t idx = tos_offset/sizeof(ir_int->TOS);

    /* TODO figure out if VM can access TOS */
    bool can_acces_tos = true;

    if(!can_acces_tos){
        ERROR("Trying to access unauthorized TOS %u", idx);
    }

    uint32_t field_offset = tos_offset - idx * sizeof(ir_int->TOS);

    /* TODO cleanup */
    uint32_t accenscfg_offset = offsetof(struct ir_int_tos, ir_int->TOS[0].ACCENSCFG);
    uint32_t accensctrl_offset = offsetof(struct ir_int_tos, ir_int->TOS[0].ACCENSCTRL);
    uint32_t accen_sz =  sizeof(struct IR_ACCESSEN);
    if(field_offset >= accenscfg_offset && field_offset < accenscfg_offset + accen_sz){
        ir_int_emul_accen_acces(acc, handlers, vcpuid, field_offset);
    } else if(field_offset >= accensctrl_offset && field_offset < accensctrl_offset + accen_sz){
        ir_int_emul_accen_acces(acc, handlers, vcpuid, field_offset-accensctrl_offset);
    } else {
        ERROR("Trying to access unknwon TOS register 0x%x", offset);
    }
}

static void vir_emul_gpsrg_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    cpuid_t vcpuid)
{
    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    /* start of gpsrg */
    uint32_t offset = offsetof(struct ir_int_hw, ir_int->gpsrg);
    /* offset within the gpsrg array */
    uint32_t gpsrg_offset = acc_addr - offset;
    /* gpsrg array entry */
    uint32_t idx = gpsrg_offset/sizeof(ir_int->gpsrg);

    /* TODO figure out if VM can access gpsrg */
    bool can_acces_gpsrg = true;

    if(!can_acces_gpsrg){
        ERROR("Trying to access unauthorized gpsrg %u", idx);
    }

    /* field_offset offset within correct gpsrg */
    uint32_t field_offset = gpsrg_offset - idx * sizeof(struct ir_int->gpsrg);


    /* TODO this is essentially duplicate code */
    /* start of swc */
    uint32_t offset = offsetof(struct ir_int_gpsrg, ir_int->GPSRG[0].SWC);
    /* offset within the swc array */
    uint32_t swc_offset = field_offset - offset;
    /* swc array entry */
    uint32_t idx = swc_offset/sizeof(struct ir_int_gpsr_swc);

    /* TODO figure out if VM can access SWC */
    bool can_acces_swc = true;

    if(!can_acces_swc){
        ERROR("Trying to access unauthorized gpsrg %u", idx);
    }

    /* offset within ir_int_gpsrg_swc */
    uint32_t field_offset = swc_offset - idx * sizeof(struct ir_int_gpsr_swc);


    /* TODO cleanup */
    uint32_t accen_offset = offsetof(struct ir_int_gpsrg_swc, ir_int->GPSRG[0].swc[0].ACCEN);
    uint32_t ctrl_offset = offsetof(struct ir_int_gpsrg_swc, ir_int->GPSRG[0].swc[0].CR);
    if(field_offset == accen_offset){
        /* TODO */
    } else if(field_offset == ctrl_offset){
        /* TODO */
    } else {
        ERROR("Trying to access unknwon gpsrg register 0x%x", offset);
    }
}

static void vir_emul_srb_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    cpuid_t vcpuid)
{
    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct ir_int_hw, ir_int->SRB);
    uint32_t srb_offset = acc_addr - offset;
    uint32_t idx = srb_offset/sizeof(ir_int->SRB);

    /* TODO figure out if VM can access TOS */
    bool can_acces_srb = true;

    if(!can_acces_srb){
        ERROR("Trying to access unauthorized SRB %u", idx);
    }

    uint32_t val = vcpu_readreg(cpu.vcpu, acc->reg);
    val &= 0x7f; /* TODO */
    /* TODO figure out which CPU ISP this VM can target and if all is well perform the access */

    /* TODO should probably be abstracted in ir.c no? */
    ir_int->SRB[idx] = val;
}

static void vir_emul_misc_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    cpuid_t vcpuid)
{
    uint32_t acc_addr = IR_REG_MASK(acc->addr);

    if(acc_addr == offsetof(struct ir_int_hw, ir_int->ID)){
        /* TODO */
        vcpu_writereg(cpu.vcpu, acc->reg, ir_int->ID);
    } else {
        ERROR("unsuported register emulation 0x%x", acc_addr);
    }
}

static bool vir_int_update_enable(struct vcpu* vcpu, struct vir_int* interrupt, bool enable)
{
    UNUSED_ARG(vcpu);

    if (enable != interrupt->enabled) {
        interrupt->enabled = enable;
        return true;
    } else {
        return false;
    }
}

static void vir_int_enable_hw(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);

    ir_set_enable(interrupt->id, interrupt->enabled);
}

static bool vir_int_clear_enable(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long data)
{
    if (!data) {
        return false;
    } else {
        return vir_int_update_enable(vcpu, interrupt, false);
    }
}

static bool vir_int_set_enable(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long data)
{
    UNUSED_ARG(vcpu);

    if (!data) {
        return false;
    } else {
        return vir_int_update_enable(vcpu, interrupt, true);
    }
}

static unsigned long vir_int_get_enable(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);

    return (unsigned long)interrupt->enabled;
}

static bool vir_int_update_pend(struct vcpu* vcpu, struct vir_int* interrupt, bool pend)
{
    UNUSED_ARG(vcpu);

    if (IR_VERSION == IRV2 && ir_is_sgi(interrupt->id)) {
        return false;
    }

    if (pend ^ !!(interrupt->state & PEND)) {
        if (pend) {
            interrupt->state |= PEND;
        } else {
            interrupt->state &= (uint8_t)~PEND;
        }
        return true;
    } else {
        return false;
    }
}

static void vir_int_state_hw(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);

    uint8_t state = interrupt->state == PEND ? ACT : interrupt->state;
    bool pend = (state & PEND) != 0;
    bool act = (state & ACT) != 0;
#if (IR_VERSION != IRV2)
    if (ir_is_priv(interrupt->id)) {
        irr_set_act(interrupt->id, act, interrupt->phys.redist);
        irr_set_pend(interrupt->id, pend, interrupt->phys.redist);
    } else {
        ird_set_act(interrupt->id, act);
        ird_set_pend(interrupt->id, pend);
    }
#else
    ird_set_act(interrupt->id, act);
    ird_set_pend(interrupt->id, pend);
#endif
}

static bool vir_int_clear_pend(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long data)
{
    if (!data) {
        return false;
    } else {
        return vir_int_update_pend(vcpu, interrupt, false);
    }
}

static bool vir_int_set_pend(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long data)
{
    if (!data) {
        return false;
    } else {
        return vir_int_update_pend(vcpu, interrupt, true);
    }
}

static unsigned long vir_int_get_pend(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);

    return (interrupt->state & PEND) ? 1 : 0;
}

static bool vir_int_update_act(struct vcpu* vcpu, struct vir_int* interrupt, bool act)
{
    UNUSED_ARG(vcpu);

    if (act ^ !!(interrupt->state & ACT)) {
        if (act) {
            interrupt->state |= ACT;
        } else {
            interrupt->state &= (uint8_t)~ACT;
        }
        return true;
    } else {
        return false;
    }
}

static bool vir_int_clear_act(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long data)
{
    if (!data) {
        return false;
    } else {
        return vir_int_update_act(vcpu, interrupt, false);
    }
}

static bool vir_int_set_act(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long data)
{
    if (!data) {
        return false;
    } else {
        return vir_int_update_act(vcpu, interrupt, true);
    }
}

static unsigned long vir_int_get_act(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);

    return (interrupt->state & ACT) ? 1 : 0;
}

static bool vir_int_set_cfg(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long cfg)
{
    UNUSED_ARG(vcpu);
    uint8_t prev_cfg = interrupt->cfg;
    interrupt->cfg = (uint8_t)cfg;
    return prev_cfg != cfg;
}

static unsigned long vir_int_get_cfg(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);
    return (unsigned long)interrupt->cfg;
}

static void vir_int_set_cfg_hw(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);
#if (IR_VERSION != IRV2)
    if (ir_is_priv(interrupt->id)) {
        irr_set_icfgr(interrupt->id, interrupt->cfg, interrupt->phys.redist);
    } else {
        ird_set_icfgr(interrupt->id, interrupt->cfg);
    }
#else
    ir_set_icfgr(interrupt->id, interrupt->cfg);
#endif
}

static bool vir_int_set_prio(struct vcpu* vcpu, struct vir_int* interrupt, unsigned long prio)
{
    UNUSED_ARG(vcpu);
    uint8_t prev_prio = interrupt->prio;
    interrupt->prio = (uint8_t)(prio & BIT_MASK(8 - IRH_LR_PRIO_LEN, IRH_LR_PRIO_LEN));
    return prev_prio != prio;
}

static unsigned long vir_int_get_prio(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);
    return (unsigned long)interrupt->prio;
}

static void vir_int_set_prio_hw(struct vcpu* vcpu, struct vir_int* interrupt)
{
    UNUSED_ARG(vcpu);
#if (IR_VERSION != IRV2)
    if (ir_is_priv(interrupt->id)) {
        irr_set_prio(interrupt->id, interrupt->prio, interrupt->phys.redist);
    } else {
        ird_set_prio(interrupt->id, interrupt->prio);
    }
#else
    ir_set_prio(interrupt->id, interrupt->prio);
#endif
}

void vir_emul_razwi(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    bool irr_access, cpuid_t virr_id)
{
    UNUSED_ARG(handlers);
    UNUSED_ARG(irr_access);
    UNUSED_ARG(virr_id);

    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, 0);
    }
}

void vir_int_set_field(struct vir_reg_handler_info* handlers, struct vcpu* vcpu,
    struct vir_int* interrupt, unsigned long data)
{
    spin_lock(&interrupt->lock);
    if (vir_get_ownership(vcpu, interrupt)) {
        vir_remove_lr(vcpu, interrupt);
        if (handlers->update_field(vcpu, interrupt, data) && vir_int_is_hw(interrupt)) {
            handlers->update_hw(vcpu, interrupt);
        }
        vir_route(vcpu, interrupt);
        vir_yield_ownership(vcpu, interrupt);
    } else {
        struct cpu_msg msg = {
            (uint32_t)VIR_IPI_ID,
            VIR_SET_REG,
            VIR_MSG_DATA(vcpu->vm->id, 0, interrupt->id, handlers->regid, data),
        };
        cpu_send_msg(interrupt->owner->phys_id, &msg);
    }
    spin_unlock(&interrupt->lock);
}

void vir_emul_generic_access(struct emul_access* acc, struct vir_reg_handler_info* handlers,
    bool irr_access, cpuid_t virr_id)
{
    size_t field_width = handlers->field_width;
    size_t first_int = (IRD_REG_MASK(acc->addr) - handlers->regroup_base) * 8 / field_width;
    unsigned long val = acc->write ? vcpu_readreg(cpu()->vcpu, acc->reg) : 0;
    unsigned long mask = (1UL << field_width) - 1;
    bool valid_access = (IR_VERSION == IRV2) || !(irr_access ^ ir_is_priv((irqid_t)first_int));

    if (valid_access) {
        for (size_t i = 0; i < ((acc->width * 8) / field_width); i++) {
            struct vir_int* interrupt =
                vir_get_int(cpu()->vcpu, (irqid_t)(first_int + i), virr_id);
            if (interrupt == NULL) {
                break;
            }
            if (acc->write) {
                unsigned long data = bit_extract(val, i * field_width, field_width);
                vir_int_set_field(handlers, cpu()->vcpu, interrupt, data);
            } else {
                val |= (handlers->read_field(cpu()->vcpu, interrupt) & mask) << (i * field_width);
            }
        }
    }

    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, (unsigned long)val);
    }
}

struct vir_reg_handler_info ir_int_misc_info = {
    ir_int_emul_misc_access,
    0x4,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
};

struct vir_reg_handler_info ir_int_accensrb_info = {
    ir_int_emul_accensrb_access,
    0x4,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
};

struct vir_reg_handler_info ir_int_tos_info = {
    vir_emul_tos_access,
    0x4,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
};

struct vir_reg_handler_info ir_int_gpsrg_info = {
    vir_emul_gpsrg_access,
    0x4,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
};

struct vir_reg_handler_info ir_int_srb_info = {
    vir_emul_srb_access,
    0x4,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
};

struct vir_reg_handler_info ir_int_icu_info = {
    vir_emul_icu_access,
    0x4,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
};


struct vir_reg_handler_info* reg_handler_info_table[VIR_REG_HANDLER_ID_NUM] = {
    [VIR_INT_MISC_ID] = &ir_int_misc_info,
    [VIR_INT_ACCENSRB_ID] = &ir_int_accensrb_info,
    [VIR_INT_TOS_ID] = &ir_int_tos_info,
    [VIR_INT_GPSRG_ID] = &ir_int_gpsrg_info,
    [VIR_INT_SRB_ID] = &ir_int_srb_info,
    [VIR_INT_ICU_ID] = &ir_int_icu_info,
};

static struct vir_reg_handler_info* vir_get_reg_handler_info(enum vir_reg_handler_info_id id)
{
    if (id >= VIR_REG_HANDLER_ID_NUM) {
        return NULL;
    }

    return reg_handler_info_table[id];
}

bool vir_check_reg_alignment(struct emul_access* acc, struct vir_reg_handler_info* handlers)
{
    if (!(handlers->alignment & acc->width) || ((acc->addr & (acc->width - 1)) != 0)) {
        return false;
    }

    return true;
}

static void vir_emul_src_access(struct emul_access* acc, struct vcpu *vcpu, struct vir_int* interrupt)
{
    if(acc->write) {
        uint32_t val = vcpu_readreg(vcpu, acc->reg);
        uint32_t srpn = IR_SRC_GET_SRPN(val);

        if(srpn > HYP_PRIORITY) {
            /* TODO necessary? */
        }

        uint32_t tos = IR_SRC_GET_TOS(val);
        /* TODO check which ISP VM can access */

        bool sre = IR_SRC_GET_SRE(val) != 0;
        if(sre){
            vir_int_update_enable(vcpu, interrupt, sre);
        }

        bool clrr = IR_SRC_GET_CLRR(val) != 0;
        bool setr = IR_SRC_GET_SETR(val) != 0;

        if(!(clrr && setr)){
            if(setr){
                vir_int_update_pend(vcpu, interrupt, true);
            } else if (clrr) {
                vir_int_update_pend(vcpu, interrupt, false);
            }
        }

        bool iovclr = IR_SRC_GET_IOVCLR(val) != 0;
        /* TODO what should hyp do? */

    } else {
        uint32_t src_mask = IR_SRC_IOVCLR_MASK | IR_SRC_IOV_MASK |
            IR_SRC_SETR_MASK | IR_SRC_CLRR_MASK | IR_SRC_SRR_MASK |
            IR_SRC_SRE_MASK | IR_SRC_TOS_MASK | IR_SRC_CS_MASK | IR_SRC_SRPN_MASK;
        /* TODO we are SPH we can read directly, diferent with ctx switch */
        uint32_t val = ir_src.SCR[interrupt->idx] & src_mask;

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

bool ir_src_emul_handler(struct emul_access* acc)
{
    uint32_t addr = acc->addr;
    uint32_t src_offset = addr - cpu()->vcpu->vm->arch->ir_srb_addr;

    uint32_t intid = src_offset / sizeof(ir_src->SRC[0]);

    struct vir_int* interrupt = vir_get_int(vcpu, id, vcpu->id);
    /* TODO check if VM owns intid */
    if(!interrupt)
        ERROR("Access to unsigned interrupt %u", intid);

    spin_lock(&cpu()->vcpu->vm->arch.ir_src.lock);
    vir_emul_src_access(acc, vcpu, interrupt);
    spin_unlock(&cpu()->vcpu->vm->arch.ir_src.lock);
    return true;
}

bool ir_int_emul_handler(struct emul_access* acc)
{
    struct vir_reg_handler_info* handler_info = NULL;
    size_t acc_off = IRD_REG_MASK(acc->addr);
    if (IRD_IS_REG(SRB, acc_off)) {
        handler_info = &ir_int_srb_info;
    } else if (IRD_IS_REG(ICU, acc_off)) {
        handler_info = &ir_int_icu_info;
    } else if (IRD_IS_REG(TOS, acc_off)) {
        handler_info = &ir_int_tos_info;
    } else if (IRD_IS_REG(GPSRG, acc_off)) {
        handler_info = &ir_int_gpsrg_info;
    } else if (IRD_IS_REG(ACCENSRB, acc_off)) {
        handler_info = &ir_int_accensrb_info;
    } else if((IRD_REG_MASK(acc->addr) >> 7) == IRD_REG_GROUP(OCS)){
        handler_info = &ir_int_misc_info;
    } else {
        ERROR("Unknown IR register at 0x%x", acc->addr);
    }

    if (!vir_check_reg_alignment(acc, handler_info)) {
        return false;
    }

    spin_lock(&cpu()->vcpu->vm->arch.ir_int.lock);
    handler_info->reg_access(acc, handler_info, cpu()->vcpu->id);
    spin_unlock(&cpu()->vcpu->vm->arch.ir_int.lock);
    return true;
}

void vir_inject_hw(struct vcpu* vcpu, irqid_t id)
{
    struct vir_int* interrupt = vir_get_int(vcpu, id, vcpu->id);
    spin_lock(&interrupt->lock);
    interrupt->owner = vcpu;
    interrupt->state = PEND;
    interrupt->in_lr = false;

    /* TODO: any other considerations? */
    ir_set_pend(vcpu, interrupt);

    spin_unlock(&interrupt->lock);
}

void vir_inject(struct vcpu* vcpu, irqid_t id, vcpuid_t source)
{
    struct vir_int* interrupt = vir_get_int(vcpu, id, vcpu->id);
    if (interrupt != NULL) {
        if (vir_int_is_hw(interrupt)) {
            vir_inject_hw(vcpu, id);
        } else {
             /* TODO is it necessary to deal specailly with SGI? */
             /* maybe not SGIs but broadcast interrupts might need additional logic */
        }
    }
}

void vir_ipi_handler(uint32_t event, uint64_t data)
{
    uint16_t vm_id = (uint16_t)VIR_MSG_VM(data);
    uint16_t virr_id = (uint16_t)VIR_MSG_VIRRID(data);
    irqid_t int_id = VIR_MSG_INTID(data);
    uint64_t val = VIR_MSG_VAL(data);

    if (vm_id != cpu()->vcpu->vm->id) {
        ERROR("received vir msg target to another vcpu");
        // TODO: need to fetch vcpu from other vm if the taget vm for this is not active
    }

    switch (event) {
        case VIR_UPDATE_ENABLE: {
            vir_update_enable(cpu()->vcpu);
        } break;

        case VIR_ROUTE: {
            struct vir_int* interrupt = vir_get_int(cpu()->vcpu, int_id, cpu()->vcpu->id);
            if (interrupt != NULL) {
                spin_lock(&interrupt->lock);
                if (vir_get_ownership(cpu()->vcpu, interrupt)) {
                    if (vir_int_vcpu_is_target(cpu()->vcpu, interrupt)) {
                        ir_set_pend(cpu()->vcpu, interrupt);
                    }
                    vir_yield_ownership(cpu()->vcpu, interrupt);
                }
                spin_unlock(&interrupt->lock);
            }
        } break;

        case VIR_INJECT: {
            vir_inject(cpu()->vcpu, int_id, (vcpuid_t)val);
        } break;

        case VIR_SET_REG: {
            uint64_t reg_id = VIR_MSG_REG(data);
            struct vir_reg_handler_info* handlers = vir_get_reg_handler_info(reg_id);
            struct vir_int* interrupt = vir_get_int(cpu()->vcpu, int_id, virr_id);
            if (handlers != NULL && interrupt != NULL) {
                vir_int_set_field(handlers, cpu()->vcpu, interrupt, (unsigned long)val);
            }
        } break;

        default:
            WARNING("Unknown VIR IPI event");
            break;
    }
}

void ir_maintenance_handler(irqid_t irq_id)
{
    /* TODO: is there a maintenance interrupt? */
}

void vir_set_hw(struct vm* vm, irqid_t id)
{
    if (id < IR_MAX_SGIS) {
        return;
    }

    /**
     * This assumes this method is called only during VM initlization
     */
    struct vir_int* interrupt = vir_get_int(vm_get_vcpu(vm, 0), id, 0);
    if (interrupt != NULL) {
        spin_lock(&interrupt->lock);
        interrupt->hw = true;
        spin_unlock(&interrupt->lock);
    } else {
        WARNING("trying to link non-existent virtual irq to physical irq");
    }
}

