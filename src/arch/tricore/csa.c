/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <arch/csa.h>

union csa csa_array[PLAT_CPU_NUM][CSA_ENTRIES] __attribute__((aligned(64)));
