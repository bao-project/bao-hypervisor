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

#ifndef __VGIC_H__
#define __VGIC_H__

#include <bao.h>
#include <arch/gic.h>

typedef struct vm vm_t;
typedef struct vcpu vcpu_t;
struct gic_dscrp;

/**
 * TODO: optimize the vgic_int struct's size
 */
typedef struct vgic_int {
    vcpu_t *owner;
#if (GIC_VERSION != GICV2)
    uint64_t route;
    union {
        uint64_t redist;
        uint64_t route;
    } phys;
#endif
    spinlock_t lock;
    uint16_t id;
    uint8_t state;
    uint8_t prio;
    uint8_t cfg;
    uint8_t lr;
#if (GIC_VERSION == GICV2)
    union {
        uint8_t targets;
        struct {
            uint8_t act;
            uint8_t pend;
        } sgi;
    };
#endif
    bool hw;
    bool in_lr;
    bool enabled;
} vgic_int_t;

typedef struct {
    vgic_int_t *interrupts;
    spinlock_t lock;
    size_t int_num;
    uint32_t CTLR;
    uint32_t TYPER;
    uint32_t IIDR;
} vgicd_t;

typedef struct {
    spinlock_t lock;
    uint64_t TYPER;
    uint32_t CTLR;
    uint32_t IIDR;
} vgicr_t;

typedef struct {
#if (GIC_VERSION != GICV2)
    vgicr_t vgicr;
#endif
    int16_t curr_lrs[GIC_NUM_LIST_REGS];
    vgic_int_t interrupts[GIC_CPU_PRIV];
} vgic_priv_t;

void vgic_init(vm_t *vm, const struct gic_dscrp *gic_dscrp);
void vgic_cpu_init(vcpu_t *vcpu);
void vgic_set_hw(vm_t *vm, uint64_t id);
void vgic_inject(vgicd_t *vgicd, uint64_t id, uint64_t source);

/* VGIC INTERNALS */

enum vgic_reg_handler_info_id {
    VGIC_ISENABLER_ID,
    VGIC_ISPENDR_ID,
    VGIC_ISACTIVER_ID,
    VGIC_ICENABLER_ID,
    VGIC_ICPENDR_ID,
    VGIC_ICACTIVER_ID,
    VGIC_ICFGR_ID,
    VGIC_IROUTER_ID,
    VGIC_IPRIORITYR_ID,
    VGIC_ITARGETSR_ID,
    VGIC_REG_HANDLER_ID_NUM
};

struct vgic_reg_handler_info {
    void (*reg_access)(emul_access_t *, struct vgic_reg_handler_info *,
                       bool gicr_accces, uint64_t vgicr_id);
    uint8_t alignment;
    size_t regid;
    uintptr_t regroup_base;
    size_t field_width;
    uint64_t (*read_field)(vcpu_t *, vgic_int_t *);
    bool (*update_field)(vcpu_t *, vgic_int_t *, uint64_t data);
    void (*update_hw)(vcpu_t *, vgic_int_t *);
};

/* interface for version agnostic vgic */
bool vgicd_emul_handler(emul_access_t *);
bool vgic_check_reg_alignment(emul_access_t *acc,
                              struct vgic_reg_handler_info *handlers);
bool vgic_add_lr(vcpu_t *vcpu, vgic_int_t *interrupt);
bool vgic_remove_lr(vcpu_t *vcpu, vgic_int_t *interrupt);
bool vgic_get_ownership(vcpu_t *vcpu, vgic_int_t *interrupt);
void vgic_yield_ownership(vcpu_t *vcpu, vgic_int_t *interrupt);
void vgic_emul_generic_access(emul_access_t *, struct vgic_reg_handler_info *,
                              bool, uint64_t);
void vgic_send_sgi_msg(vcpu_t *vcpu, uint64_t pcpu_mask, uint64_t int_id);
uint64_t vgic_get_itln(const struct gic_dscrp *gic_dscrp);

/* interface for version specific vgic */
bool vgic_int_vcpu_is_target(vcpu_t *vcpu, vgic_int_t *interrupt);
bool vgic_int_has_other_target(vcpu_t *vcpu, vgic_int_t *interrupt);
uint64_t vgic_int_ptarget_mask(vcpu_t *vcpu, vgic_int_t *interrupt);
void vgic_inject_sgi(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t source);

#endif /* __VGIC_H__ */
