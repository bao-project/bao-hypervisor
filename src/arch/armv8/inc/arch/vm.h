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
#include <arch/profile/vm.h>
#include <arch/subarch/vm.h>
#include <arch/vgic.h>
#include <list.h>

struct arch_vm_platform {
    struct vgic_dscrp {
        paddr_t gicd_addr;
        paddr_t gicc_addr;
        paddr_t gicr_addr;
        size_t interrupt_num;
    } gic;

    struct {
        streamid_t global_mask;
        size_t group_num;
        struct smmu_group {
            streamid_t mask;
            streamid_t id;
        } *groups;
    } smmu;
};

struct vm_arch {
    struct vgicd vgicd;
    vaddr_t vgicr_addr;
    struct list vgic_spilled;
    spinlock_t vgic_spilled_lock;
    struct emul_mem vgicd_emul;
    struct emul_mem vgicr_emul;
    struct emul_reg icc_sgir_emul;
    struct emul_reg icc_sre_emul;
};

struct vcpu_arch {
    unsigned long vmpidr;
    struct vcpu_arch_profile profile;
    struct vgic_priv vgic_priv;
    struct list vgic_spilled;
};

struct vcpu* vm_get_vcpu_by_mpidr(struct vm* vm, unsigned long mpidr);
void vcpu_arch_entry();

bool vcpu_arch_profile_on(struct vcpu* vcpu);
void vcpu_arch_profile_init(struct vcpu* vcpu, struct vm* vm);
void vcpu_arch_profile_reset(struct vcpu* vcpu);

static inline void vcpu_arch_inject_hw_irq(struct vcpu* vcpu, uint64_t id)
{
    vgic_inject_hw(vcpu, id);
}

static inline void vcpu_arch_inject_irq(struct vcpu* vcpu, uint64_t id)
{
    vgic_inject(vcpu, id, 0);
}

#endif /* __ARCH_VM_H__ */
