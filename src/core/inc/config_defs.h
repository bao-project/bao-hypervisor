/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef CONFIGS_DEFS_H
#define CONFIGS_DEFS_H

#ifdef GENERATING_DEFS

#define CONFIG_VCPU_NUM  1
#define CONFIG_VM_NUM  1
#define CONFIG_HYP_BASE_ADDR 0

#else /* GENERATING_DEFS */

#include <config_defs_gen.h>

#endif /* GENERATING_DEFS */

#endif /* CONFIGS_DEFS_H */
