/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VINTC_H__
#define __VINTC_H__

#include <vm.h>

void vintc_init(struct vm* vm);
void vintc_inject(struct vcpu* vcpu, irqid_t int_id);
void vintc_vcpu_reset(struct vcpu* vcpu);
void vintc_vm_reset(struct vm* vm);

#endif /* __VINTC_H__ */
