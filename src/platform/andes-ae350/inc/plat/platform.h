/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <drivers/sbi_uart.h>

/* Andes AX66 core implements the Sstc extension */
#define CPU_EXT_SSTC 1
#define CPU_EXT_SSSTATEEN 1
#define CPU_EXT_SSCSRIND 1
#define CPU_EXT_F 1
#define CPU_EXT_C 0
#define CPU_EXT_SDTRIG 0

#define IPIC_SBI    (1)
#define IPIC_ACLINT (2)

#endif /* __PLAT_PLATFORM_H__ */
