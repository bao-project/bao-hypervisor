/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PSCI_H__
#define __PLAT_PSCI_H__

#define PSCI_POWER_STATE_LVL_0          0x0000000
#define PSCI_POWER_STATE_LVL_1          0x1000000
#define PSCI_POWER_STATE_LVL_2          0x2000000
#define PSCI_STATE_TYPE_STANDBY         0x00000
#define PSCI_STATE_TYPE_POWERDOWN       (1UL << 30)
#define PSCI_STATE_TYPE_BIT             (1UL << 30)

#define PLAT_PSCI_STANDBY_NOT_SUPPORTED 1

#endif // __PLAT_PSCI_H__
