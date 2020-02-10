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

#ifndef __VGICV2_H__
#define __VGICV2_H__

#include <bao.h>
#include <arch/gic.h>

typedef struct vm vm_t;
typedef struct vcpu vcpu_t;
struct gic_dscrp;

typedef struct {
    spinlock_t lock;
    vcpu_t *owner;

    uint16_t id;
    bool hw;
    bool in_lr;
    uint64_t lr;

    bool enabled;
    uint8_t state;
    uint8_t prio;
    uint8_t targets;
} vgic_int_t;

typedef struct {
    spinlock_t lock;
    uint32_t CTLR;
    uint32_t TYPER;
    uint32_t IIDR;
    vgic_int_t interrupts[GIC_MAX_SPIS];
} vgicd_t;

typedef struct {
    gich_t gich;
    int16_t curr_lrs[GIC_NUM_LIST_REGS];
    struct {
        uint8_t pend;
        uint8_t act;
    } sgis[GIC_MAX_SGIS];
    vgic_int_t interrupts[GIC_CPU_PRIV];
} vgic_priv_t;

void vgic_init(vm_t *vm, const struct gic_dscrp *gic_dscrp);
void vgic_cpu_init(vcpu_t *vcpu);
void vgic_set_hw(vm_t *vm, uint64_t id);
void vgicd_inject(vgicd_t *vgicd, uint64_t id, uint64_t source);

#endif /* __VGICV2_H__ */