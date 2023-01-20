/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_PROFILE_CPU_H
#define ARCH_PROFILE_CPU_H

#include <bao.h>
#include <arch/psci.h>

struct cpu_arch_profile {
    struct psci_off_state psci_off_state;
};

static inline struct cpu* cpu() {
    return (struct cpu*)BAO_CPU_BASE;
}

#endif /* ARCH_PROFILE_CPU_H */
