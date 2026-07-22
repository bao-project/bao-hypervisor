/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#include <drivers/rzt2m_uart.h>

#include <plat/renesas.h>
#include <plat/bsp_common.h>
#include <plat/rwp.h>
#include <plat/clock.h>
#include <plat/ioport.h>
#include <plat/gicd_icfgr.h>
#include <plat/cnt.h>

#define PLAT_PERIPHERAL_MEM_BASE    (0x80000000)
#define PLAT_PERIPHERAL_MEM_SIZE    (0x2000000) // 32MB

#define PLAT_NUM_PINS   (125)

#endif
