/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
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
