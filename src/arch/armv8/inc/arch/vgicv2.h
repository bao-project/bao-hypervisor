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

#ifndef __VGICV2_H__
#define __VGICV2_H__

#include <arch/vgic.h>
#include <vm.h>

static inline bool vgic_int_vcpu_is_target(struct vcpu *vcpu, struct vgic_int *interrupt)
{
    bool priv = gic_is_priv(interrupt->id);
    bool target = interrupt->targets & (1 << vcpu->phys_id);
    return priv || target;
}

#endif /* __VGICV2_H__ */
