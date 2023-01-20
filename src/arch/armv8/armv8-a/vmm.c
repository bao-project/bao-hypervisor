/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vmm.h>

void vmm_arch_profile_init()
{
    vmm_arch_init_tcr();
}
