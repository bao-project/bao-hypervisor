/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <arch/csfrs.h>
#include <cpu.h>
#include <arch/interrupts.h>
// #include <arch/vir.h>
#include <emul.h>
#include <vm.h>
#include <arch/csa.h>

#define REG_D0  (1)
#define REG_D1  (2)
#define REG_D2  (3)
#define REG_D3  (4)
#define REG_D4  (5)
#define REG_D5  (6)
#define REG_D6  (7)
#define REG_D7  (8)
#define REG_D8  (9)
#define REG_D9  (10)
#define REG_D10 (11)
#define REG_D11 (12)
#define REG_D12 (13)
#define REG_D13 (14)
#define REG_D14 (15)
#define REG_A0  (16)
#define REG_A1  (17)
#define REG_A2  (18)
#define REG_A3  (19)
#define REG_A4  (20)
#define REG_A5  (21)
#define REG_A6  (22)
#define REG_A7  (23)
#define REG_A8  (24)
#define REG_A9  (25)
#define REG_A10 (26)
#define REG_SP  (26)
#define REG_A11 (27)
#define REG_RA  (27)
#define REG_A12 (28)
#define REG_A13 (29)
#define REG_A14 (30)
#define REG_A15 (31)

struct vnvic_src {
    node_t node;
    struct vcpu* owner;
    spinlock_t lock;
    irqid_t id;
    uint8_t prio;
    uint32_t target;
    bool enabled;
};

struct vnvic_dscrp {
    paddr_t int_addr;
    paddr_t src_addr;
};

struct arch_vm_platform {
    /* interrupt controller */
    struct vnvic_dscrp vir;
};

struct vm_arch {
    /* interrupt controller */
    /* TODO needed? struct vnvic_int vnvic_int; */
    struct vnvic_src* vnvic_src;

    paddr_t vnvic_int_addr;
    spinlock_t vnvic_int_lock;
    paddr_t vnvic_src_addr;
    spinlock_t vnvic_src_lock;

    struct emul_mem vnvic_int_emul;
    struct emul_mem vnvic_src_emul;
};

struct vcpu_arch {
    vcpuid_t core_id;
    /* TODO CPU power state ctx */

    struct {
        BITMAP_ALLOC(bitmap, SAU_ARCH_MAX_NUM_ENTRIES);
        /**
         * A locked region means that it can never be removed from the MPU. For example,
         */
        BITMAP_ALLOC(locked, SAU_ARCH_MAX_NUM_ENTRIES);
    } sau_vm;
};

struct arch_regs {
    struct lower_context lower_ctx;
    struct upper_context upper_ctx;

    unsigned long a0; /* System global register: not saved accross calls traps and irqs */
    unsigned long a1; /* System global register: not saved accross calls traps and irqs */
    unsigned long a8; /* System global register: not saved accross calls traps and irqs */
    unsigned long a9; /* System global register: not saved accross calls traps and irqs */

} __attribute__((__packed__, aligned(64)));

void vcpu_arch_entry(void);

static inline void vcpu_arch_inject_hw_irq(struct vcpu* vcpu, irqid_t id)
{
    (void)vcpu;
    (void)id;
    /* virqc_inject(vcpu, id); */
}

static inline void vcpu_arch_inject_irq(struct vcpu* vcpu, irqid_t id)
{
    (void)vcpu;
    (void)id;
    /* virqc_inject(vcpu, id); */
}

void vnvic_vcpu_init(struct vcpu* vcpu);

void nvic_config_irq(irqid_t int_id, bool en);

struct vm;
void nvic_assign_int_to_vm(struct vm* vm, irqid_t id);

void nvic_assign_int_to_vm(struct vm* vm, irqid_t id);

#endif /* __ARCH_VM_H__ */
