/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/sysregs.h>
#include <fences.h>
#include <string.h>
#include <config.h>

void vm_arch_init(struct vm* vm, const struct vm_config* vm_config)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(vm_config);
}

struct vcpu* vm_get_vcpu_by_mpidr(struct vm* vm, unsigned long mpidr)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(mpidr);

    return NULL;
}

static unsigned long vm_cpuid_to_mpidr(struct vm* vm, vcpuid_t cpuid)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(cpuid);

    return 0;
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    UNUSED_ARG(vcpu);
    UNUSED_ARG(vm);
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    UNUSED_ARG(vcpu);
    UNUSED_ARG(entry);
}

bool vcpu_arch_is_on(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);

    return false;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    (void)vcpu;
    (void)reg;
    return 0;
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    (void)vcpu;
    (void)reg;
    (void)val;
}
