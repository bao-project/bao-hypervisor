/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#ifndef __PLAT_PSCI_H__
#define __PLAT_PSCI_H__

#define PSCI_POWER_STATE_LVL_0 		0x0000000
#define PSCI_POWER_STATE_LVL_1 		0x1000000
#define PSCI_POWER_STATE_LVL_2 		0x2000000
#define PSCI_STATE_TYPE_STANDBY		0x00006
#define PSCI_STATE_TYPE_BIT			(1UL << 30)
#define PSCI_STATE_TYPE_POWERDOWN		(0x7 | PSCI_STATE_TYPE_BIT)

#endif // __PLAT_PSCI_H__
