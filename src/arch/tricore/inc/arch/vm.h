/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <arch/scr.h>
#include <cpu.h>
#include <arch/interrupts.h>

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

struct arch_vm_platform {
    unsigned int a;

    /* interrupt controller */

    /* struct ir ir; */
};

struct vm_arch {
    /* interrupt controller */
    unsigned int a;
};

struct vcpu_arch {
    vcpuid_t core_id;
    struct scr_ctx scr_ctx;
};

struct arch_regs {
    union {
        struct{
            unsigned long reg[32];
        } gprs;
        struct {
            unsigned long d0;  /* lower ctx */
            unsigned long d1;  /* lower ctx */
            unsigned long d2;  /* lower ctx */
            unsigned long d3;  /* lower ctx */
            unsigned long d4;  /* lower ctx */
            unsigned long d5;  /* lower ctx */
            unsigned long d6;  /* lower ctx */
            unsigned long d7;  /* lower ctx */
            unsigned long d8;  /* upper ctx */
            unsigned long d9;  /* upper ctx */
            unsigned long d10; /* upper ctx */
            unsigned long d11; /* upper ctx */
            unsigned long d12; /* upper ctx */
            unsigned long d13; /* upper ctx */
            unsigned long d14; /* upper ctx */
            unsigned long d15; /* upper ctx */
            unsigned long a0;  /* System global register: content not saved accross calls traps and irqs */
            unsigned long a1;  /* System global register: content not saved accross calls traps and irqs */
            unsigned long a2;  /* lower ctx */
            unsigned long a3;  /* lower ctx */
            unsigned long a4;  /* lower ctx */
            unsigned long a5;  /* lower ctx */
            unsigned long a6;  /* lower ctx */
            unsigned long a7;  /* lower ctx */
            unsigned long a8;  /* System global register: content not saved accross calls traps and irqs */
            unsigned long a9;  /* System global register: content not saved accross calls traps and irqs */
            union{
                unsigned long a10;
                unsigned long sp; /* stack pointer */
            }; /* upper ctx */
            union{
                unsigned long a11;
                unsigned long ra; /* return address */
            }; /* upper ctx */
            unsigned long a12; /* upper ctx */
            unsigned long a13; /* upper ctx */
            unsigned long a14; /* upper ctx */
            unsigned long a15; /* upper ctx */
        };
    };

    unsigned long psw; /* program status word */
    unsigned long pc; /* programm counter */
    unsigned long pcxi; /* previous ctx information */
    unsigned long pprs; /* previous protection register set registers */

} __attribute__((__packed__, aligned(sizeof(unsigned long))));

void vcpu_arch_entry();

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

#endif /* __ARCH_VM_H__ */

