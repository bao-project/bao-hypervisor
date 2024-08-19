/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VIR_H__
#define __VIR_H__

#include <bao.h>
#include <ir.h>
#include <arch/spinlock.h>
#include <bitmap.h>
#include <emul.h>

struct vir {
    spinlock_t lock;
    size_t cntxt_num;
    BITMAP_ALLOC(hw, IR_MAX_INTERRUPTS);
    BITMAP_ALLOC(pend, IR_MAX_INTERRUPTS);
    BITMAP_ALLOC(act, IR_MAX_INTERRUPTS);
    uint32_t prio[IR_MAX_INTERRUPTS];
    BITMAP_ALLOC_ARRAY(enbl, IR_MAX_INTERRUPTS, IR_PLAT_CNTXT_NUM);
    uint32_t threshold[IR_PLAT_CNTXT_NUM];
    struct emul_mem ir_src_emul;
    struct emul_mem ir_threshold_emul;
};

struct vir_descript {
    struct{
        paddr_t src_base;
        paddr_t gpsr_base;
    } src;
    paddr_t int_base;
} ;

struct vm;
struct vcpu;
union vm_irqc_dscrp;
void vir_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp);
void vir_inject(struct vcpu* vcpu, irqid_t id);
void vir_set_hw(struct vm* vm, irqid_t id);

static inline void virqc_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp)
{
    vir_init(vm, vm_irqc_dscrp);
}

typedef struct vcpu vcpu_t;
static inline void virqc_inject(vcpu_t* vcpu, irqid_t id)
{
    vir_inject(vcpu, id);
}

#endif //__VIR_H__
