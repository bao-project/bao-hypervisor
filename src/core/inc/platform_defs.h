/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef PLATFORM_DEFS_H
#define PLATFORM_DEFS_H

#ifdef GENERATING_DEFS

#define PLAT_CPU_NUM      1
#define PLAT_BASE_ADDR    0
#define PLAT_CPU_SLOT_NUM 1
#define PLAT_CPU_BASES    { CPU_SLOT(0) }

#else /* GENERATING_DEFS */

#include <platform_defs_gen.h>

#endif /* GENERATING_DEFS */

#endif /* PLATFORM_DEFS_H */
