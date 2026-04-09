/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#define UART8250_REG_WIDTH (4U)

#include <drivers/8250_uart.h>
#include <drivers/k3_sec_proxy.h>
#include <drivers/tisci.h>

/* j721e host id enumeration */
#define J721E_HOST_ID_MAIN_A72_CONTEXT_0_SECURE     (10)
#define J721E_HOST_ID_MAIN_A72_CONTEXT_1_SECURE     (11)
#define J721E_HOST_ID_MAIN_A72_CONTEXT_2_NON_SECURE (12)
#define J721E_HOST_ID_MAIN_A72_CONTEXT_3_NON_SECURE (13)
#define J721E_HOST_ID_MAIN_A72_CONTEXT_4_NON_SECURE (14)
#define J721E_HOST_ID_MAIN_A72_CONTEXT_5_NON_SECURE (30)

#endif
