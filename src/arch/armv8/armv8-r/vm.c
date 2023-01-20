/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <config.h>
#include <arch/sysregs.h>

void vcpu_arch_profile_init(struct vcpu* vcpu, struct vm* vm) {
    sysreg_vsctlr_el2_write(((vm->id << VSCTLR_EL2_VMID_OFF) & VSCTLR_EL2_VMID_MSK));

    if (DEFINED(MEM_PROT_MPU) && DEFINED(AARCH64) && vm->config->platform.mmu) {
        uint64_t vtcr = VTCR_MSA;
        sysreg_vtcr_el2_write(vtcr);
    }
}
