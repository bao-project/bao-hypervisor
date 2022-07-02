/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef VM_ARCH_PROFILE_H
#define VM_ARCH_PROFILE_H

#include <arch/psci.h>

struct vcpu_arch_profile {
    struct psci_ctx psci_ctx;
};

#endif /* VM_ARCH_PROFILE_H */
