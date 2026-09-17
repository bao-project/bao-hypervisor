/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VCPU_H__
#define __VCPU_H__

#include <bao.h>

struct vm;
struct vcpu;

#include <arch/vm.h>

/* A vcpu, embedded in the cpu structure of the physical cpu that runs it */
struct vcpu {
    struct arch_regs regs;
    struct vcpu_arch arch;

    vcpuid_t id;
    cpuid_t phys_id;
    bool active;

    struct vm* vm;
};

#endif /* __VCPU_H__ */
