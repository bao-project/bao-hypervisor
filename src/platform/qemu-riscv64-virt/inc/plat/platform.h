/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <drivers/sbi_uart.h>

#define CPU_EXT_SSTC           1
#define CPU_EXT_ZICBOM         1
#define CPU_EXT_ZICBOZ         1
#define CPU_EXT_SSNPM          0
#define CPU_EXT_SSNPM_PMM_MODE HENVCFG_PMM_PMLEN_7

#define IPIC_SBI               (1)
#define IPIC_ACLINT            (2)

#endif
