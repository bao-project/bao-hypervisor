/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VPLIC_H__
#define __VPLIC_H__

#include <bao.h>
#include <arch/plic.h>
#include <arch/spinlock.h>
#include <bitmap.h>
#include <emul.h>

struct vplic {
    spinlock_t lock;
    size_t cntxt_num;
    BITMAP_ALLOC(hw, PLIC_MAX_INTERRUPTS);
    BITMAP_ALLOC(pend, PLIC_MAX_INTERRUPTS);
    BITMAP_ALLOC(act, PLIC_MAX_INTERRUPTS);
    uint32_t prio[PLIC_MAX_INTERRUPTS];
    BITMAP_ALLOC_ARRAY(enbl, PLIC_MAX_INTERRUPTS, PLIC_PLAT_CNTXT_NUM);
    uint32_t threshold[PLIC_PLAT_CNTXT_NUM];
    struct emul_mem plic_global_emul;
    struct emul_mem plic_threshold_emul;
};

struct vm;
struct vcpu;
void vplic_init(struct vm *vm, vaddr_t vplic_base);
void vplic_inject(struct vcpu *vcpu, irqid_t id);
void vplic_set_hw(struct vm *vm, irqid_t id);

#endif /* __VPLIC_H__ */
