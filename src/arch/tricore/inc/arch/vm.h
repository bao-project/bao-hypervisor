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
#include <arch/vir.h>
#include <emul.h>
#include <vm.h>
#include <arch/csa.h>

#define VM_TO_AS_ID(x) ((x) + 1)

#define REG_D0         (1)
#define REG_D1         (2)
#define REG_D2         (3)
#define REG_D3         (4)
#define REG_D4         (5)
#define REG_D5         (6)
#define REG_D6         (7)
#define REG_D7         (8)
#define REG_D8         (9)
#define REG_D9         (10)
#define REG_D10        (11)
#define REG_D11        (12)
#define REG_D12        (13)
#define REG_D13        (14)
#define REG_D14        (15)
#define REG_A0         (16)
#define REG_A1         (17)
#define REG_A2         (18)
#define REG_A3         (19)
#define REG_A4         (20)
#define REG_A5         (21)
#define REG_A6         (22)
#define REG_A7         (23)
#define REG_A8         (24)
#define REG_A9         (25)
#define REG_A10        (26)
#define REG_SP         (26)
#define REG_A11        (27)
#define REG_RA         (27)
#define REG_A12        (28)
#define REG_A13        (29)
#define REG_A14        (30)
#define REG_A15        (31)

struct arch_vm_platform {
    unsigned long gspr_num;
    unsigned long* gspr_groups;
};

struct vm_arch {
    struct vir_src* vir_src;

    paddr_t vir_int_addr;
    spinlock_t vir_int_lock;
    paddr_t vir_src_addr;
    spinlock_t vir_src_lock;

    struct emul_mem vir_int_emul;
    struct emul_mem vir_src_emul;
};

struct vcpu_arch {
    vcpuid_t core_id;
};

struct arch_regs {
    union {
        struct lower_context lower_ctx;
        unsigned long lower_array[16];
    };

    union {
        struct upper_context upper_ctx;
        unsigned long upper_array[16];
    };
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
}

static inline void vcpu_arch_inject_irq(struct vcpu* vcpu, irqid_t id)
{
    vir_inject(vcpu, id);
}

struct vm;

void vir_vcpu_init(struct vcpu* vcpu);

void ir_config_irq(irqid_t int_id, bool en);

void ir_assign_int_to_vm(struct vm* vm, irqid_t id);

void vcpu_arch_run(struct vcpu* vcpu);

#endif /* __ARCH_VM_H__ */
