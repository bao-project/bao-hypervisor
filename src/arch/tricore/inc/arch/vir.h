/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VIR_H__
#define __VIR_H__

#include <bao.h>
#include <arch/ir.h>

struct vm;
struct vcpu;
void vir_init(struct vm* vm);
void vir_vcpu_init(struct vcpu* vcpu);
void vir_inject(struct vcpu* vcpu, irqid_t id);
void vir_set_hw(struct vm* vm, irqid_t id);

#endif /*__VIR_H__ */
