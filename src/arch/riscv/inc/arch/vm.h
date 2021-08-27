/**
 * Bao Hypervisor
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

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <arch/vplic.h>
#include <arch/sbi.h>

#define REG_RA (1)
#define REG_SP (2)
#define REG_GP (3)
#define REG_TP (4)
#define REG_T0 (5)
#define REG_T1 (6)
#define REG_T2 (7)
#define REG_S0 (8)
#define REG_S1 (9)
#define REG_A0 (10)
#define REG_A1 (11)
#define REG_A2 (12)
#define REG_A3 (13)
#define REG_A4 (14)
#define REG_A5 (15)
#define REG_A6 (16)
#define REG_A7 (17)
#define REG_S2 (18)
#define REG_S3 (19)
#define REG_S4 (20)
#define REG_S5 (21)
#define REG_S6 (22)
#define REG_S7 (23)
#define REG_S8 (24)
#define REG_S9 (25)
#define REG_S10 (26)
#define REG_S11 (27)
#define REG_T3 (28)
#define REG_T4 (29)
#define REG_T5 (30)
#define REG_T6 (31)

typedef struct {
    vplic_t vplic;
} vm_arch_t;

typedef struct {
    unsigned hart_id;
    struct sbi_hsm sbi_ctx;
} vcpu_arch_t;

struct arch_regs {
    union {
        unsigned long x[31];
        struct {
            unsigned long ra;
            unsigned long sp;
            unsigned long gp;
            unsigned long tp;
            unsigned long t0;
            unsigned long t1;
            unsigned long t2;
            unsigned long s0;
            unsigned long s1;
            unsigned long a0;
            unsigned long a1;
            unsigned long a2;
            unsigned long a3;
            unsigned long a4;
            unsigned long a5;
            unsigned long a6;
            unsigned long a7;
            unsigned long s2;
            unsigned long s3;
            unsigned long s4;
            unsigned long s5;
            unsigned long s6;
            unsigned long s7;
            unsigned long s8;
            unsigned long s9;
            unsigned long s10;
            unsigned long s11;
            unsigned long t3;
            unsigned long t4;
            unsigned long t5;
            unsigned long t6;
        };
    };

    unsigned long hstatus;
    unsigned long sstatus;
    unsigned long sepc;

    // unsigned long vsstatus;
    // unsigned long vsie;
    // unsigned long vstvec;
    // unsigned long vsscratch;
    // unsigned long vsepc;
    // unsigned long vscause;
    // unsigned long vstval;
    // unsigned long vsip;
    // unsigned long vsatp;

} __attribute__((__packed__, aligned(sizeof(unsigned long))));

void vcpu_arch_entry();

#endif /* __ARCH_VM_H__ */
