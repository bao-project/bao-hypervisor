/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/sysregs.h>

void vcpu_arch_profile_init(struct vcpu* vcpu, struct vm* vm) {
    sysreg_vsctlr_el2_write(((vm->id << VSCTLR_EL2_VMID_OFF) & VSCTLR_EL2_VMID_MSK));
}

bool vcpu_arch_profile_on(struct vcpu* vcpu) {
    return true;
}
