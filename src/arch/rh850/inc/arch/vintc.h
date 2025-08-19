/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VINTC_H__
#define __VINTC_H__

#include <vm.h>
#include <interrupts.h>

struct vcpu;
struct emul_access;

void vintc_init(struct vcpu* vcpu);
void vintc_inject(struct vcpu* vcpu, irqid_t int_id);
void vintc_vcpu_reset(struct vcpu* vcpu);
void vintc_vm_reset(struct vm* vm);
void vbootctrl_init(struct vcpu* vcpu);

bool vintc2_emul_handler(struct emul_access* acc);
bool vintif_emul_handler(struct emul_access* acc);
bool veint_emul_handler(struct emul_access* acc);
bool vfenc_emul_handler(struct emul_access* acc);
bool vfeinc_emul_handler(struct emul_access* acc);
bool vbootctrl_emul_handler(struct emul_access* acc);

#endif /* __VINTC_H__ */
