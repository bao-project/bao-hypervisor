/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <cpu.h>
#include <arch/interrupts.h>
#include <arch/vir.h>
#include <emul.h>
#include <vm.h>
#include <arch/csa.h>

/* The VMID used in HW is bao's internal vm.id + 1 because VM0 is
reserved for the hypervisor. */
#define VMID_TO_HWVM(x) ((x) + 1)

#define VM_ARCH_MAX_NUM 7

struct arch_vm_platform {
    unsigned long gpsr_num;
    unsigned long* gpsr_groups;
};

struct vm_arch {
    struct emul_mem vir_src_emul;
};

struct vcpu_arch {
    EMPTY_STRUCT_FIELDS
};

struct arch_regs {
    union {
        struct lower_context lower_ctx;
        unsigned long lower_array[CSA_SIZE];
    };

    union {
        struct upper_context upper_ctx;
        unsigned long upper_array[CSA_SIZE];
    };
    /* System global registers: not saved accross calls traps and irqs */
    unsigned long a0;
    unsigned long a1;
    unsigned long a8;
    unsigned long a9;

} __attribute__((__packed__, aligned(64)));

void vcpu_arch_entry(void);

static inline void vcpu_arch_inject_hw_irq(struct vcpu* vcpu, irqid_t id)
{
    vir_inject(vcpu, id);
}

static inline void vcpu_arch_inject_irq(struct vcpu* vcpu, irqid_t id)
{
    vcpu_arch_inject_hw_irq(vcpu, id);
}

#endif /* __ARCH_VM_H__ */
