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

#ifndef __ARCH_VM_H__
#define __ARCH_VM_H__

#include <bao.h>
#include <arch/vgic.h>
#include <arch/psci.h>

typedef struct {
    vgicd_t vgicd;
    uintptr_t vgicr_addr;
} vm_arch_t;

typedef struct {
    uint64_t vmpidr;
    vgic_priv_t vgic_priv;
    psci_ctx_t psci_ctx;
} vcpu_arch_t;

struct arch_regs {
    uint64_t x[31];
    uint64_t elr_el2;
    uint64_t spsr_el2;
} __attribute__((aligned(16)));  // makes size always aligned to 16 to respect
                                 // stack alignment

vcpu_t* vm_get_vcpu_by_mpidr(vm_t* vm, uint64_t mpidr);
void vcpu_arch_entry();


#endif /* __ARCH_VM_H__ */
