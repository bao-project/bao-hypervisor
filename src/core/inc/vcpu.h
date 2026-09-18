/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VCPU_H__
#define __VCPU_H__

#include <bao.h>

struct vm;
struct vcpu;
struct vcpu_public;

#include <arch/vm.h>

/**
 * The part of a vcpu's state that other cpus read or write: its identity and the architecture
 * state involved in cross-cpu operations (power management requests, private interrupts, ...).
 * One instance per physical cpu, in globally accessible memory, so a cpu never has to reach into
 * another cpu's private block.
 */
struct vcpu_public {
    vcpuid_t id;
    cpuid_t phys_id;
    struct vm* vm;
    struct vcpu_arch_public arch;
};

/**
 * A vcpu, embedded in the cpu structure of the physical cpu that runs it and only ever touched
 * by that cpu. What other cpus need is reached through pub.
 */
struct vcpu {
    struct arch_regs regs;
    struct vcpu_arch arch;

    vcpuid_t id;
    cpuid_t phys_id;
    bool active;

    struct vm* vm;
    struct vcpu_public* pub;
};

#endif /* __VCPU_H__ */
