/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <interrupts.h>
#include <emul.h>
#include <vintc.h>

#define MAX_OF_GP_REGS (sizeof(union gp_regs) / sizeof(unsigned long))

struct intc_dscrp {
    paddr_t intc1_addr;
    paddr_t intc2_addr;
};

struct arch_vm_platform {
    unsigned long dummy;
};

struct vm_arch {
    /* interrupt controller */
    struct emul_mem intc1_emul;
    struct emul_mem intc2_emul;
    struct emul_mem intif_emul;
    struct emul_mem eint_emul;
    struct emul_mem fenc_emul;
    struct emul_mem feinc_emul;
    struct emul_mem ipir_emul;
    /* BOOTCTRL */
    struct emul_mem bootctrl_emul;
};

struct vcpu_arch {
    bool started;
};

struct arch_regs {
    union gp_regs {
        unsigned long r[32]; /* r0 is always 0x0 */
        struct {
            unsigned long r0;
            unsigned long r1;
            unsigned long r2;
            unsigned long sp;
            unsigned long r4;
            unsigned long r5;
            unsigned long r6;
            unsigned long r7;
            unsigned long r8;
            unsigned long r9;
            unsigned long r10;
            unsigned long r11;
            unsigned long r12;
            unsigned long r13;
            unsigned long r14;
            unsigned long r15;
            unsigned long r16;
            unsigned long r17;
            unsigned long r18;
            unsigned long r19;
            unsigned long r20;
            unsigned long r21;
            unsigned long r22;
            unsigned long r23;
            unsigned long r24;
            unsigned long r25;
            unsigned long r26;
            unsigned long r27;
            unsigned long r28;
            unsigned long r29;
            unsigned long r30;
            unsigned long r31;
        };
    } gp_regs;
    // Basic system registers
    unsigned long pc;
};

void vcpu_arch_entry(void);

static inline void vcpu_arch_inject_hw_irq(struct vcpu* vcpu, irqid_t id)
{
    vintc_inject(vcpu, id);
}

static inline void vcpu_arch_inject_irq(struct vcpu* vcpu, irqid_t id)
{
    vintc_inject(vcpu, id);
}

#endif /* __ARCH_VM_H__ */
