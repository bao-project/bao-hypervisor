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

#ifndef __VGICV3_H__
#define __VGICV3_H__

#include <arch/vgic.h>
#include <vm.h>

static inline bool vgic_broadcast(vcpu_t *vcpu, struct vgic_int *interrupt)
{
    return (interrupt->route & GICD_IROUTER_IRM_BIT);
}

static inline bool vgic_int_vcpu_is_target(vcpu_t *vcpu, struct vgic_int *interrupt)
{
    bool priv = gic_is_priv(interrupt->id);
    bool local = priv && (interrupt->phys.redist == vcpu->phys_id);
    bool routed_here =
        !priv && !(interrupt->phys.route ^ (MRS(MPIDR_EL1) & MPIDR_AFF_MSK));
    bool any = !priv && vgic_broadcast(vcpu, interrupt);
    return local || routed_here || any;
}


#endif /* __VGICV3_H__ */
