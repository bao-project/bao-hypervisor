/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VGICV3_H__
#define __VGICV3_H__

#include <arch/vgic.h>
#include <vm.h>

static inline bool vgic_broadcast(struct vcpu *vcpu, struct vgic_int *interrupt)
{
    return (interrupt->route & GICD_IROUTER_IRM_BIT);
}

static inline bool vgic_int_vcpu_is_target(struct vcpu *vcpu, struct vgic_int *interrupt)
{
    bool priv = gic_is_priv(interrupt->id);
    bool local = priv && (interrupt->phys.redist == vcpu->phys_id);
    bool routed_here =
        !priv && !(interrupt->phys.route ^ (sysreg_mpidr_el1_read() & MPIDR_AFF_MSK));
    bool any = !priv && vgic_broadcast(vcpu, interrupt);
    return local || routed_here || any;
}


#endif /* __VGICV3_H__ */
