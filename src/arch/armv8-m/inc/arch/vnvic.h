/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VIR_H__
#define __VIR_H__

#include <bao.h>
#include <arch/nvic.h>
#include <arch/spinlock.h>
#include <bitmap.h>
#include <emul.h>
#include <vm.h>

#define IR_MAX_INTERRUPTS (2048U) /* TODO */

struct vnvic {
    spinlock_t lock;
    BITMAP_ALLOC(pend, IR_MAX_INTERRUPTS);
    BITMAP_ALLOC(act, IR_MAX_INTERRUPTS);
    uint32_t prio[IR_MAX_INTERRUPTS];
    BITMAP_ALLOC(enbl, IR_MAX_INTERRUPTS);
    struct emul_mem ir_src_emul;
};

struct vnvic_reg_handler_info {
    void (*reg_access)(struct emul_access*, cpuid_t vgicr_id);
    size_t alignment;
};

struct vm;
struct vcpu;
struct vnvic_dscrp;
void vnvic_init(struct vm* vm, const struct vnvic_dscrp* vm_vnvic_dscrp);
void vnvic_inject(struct vcpu* vcpu, irqid_t id);
void vnvic_set_hw(struct vm* vm, irqid_t id);

#endif //__VIR_H__
