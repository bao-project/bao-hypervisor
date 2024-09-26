/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef PLAT_PSCI_H
#define PLAT_PSCI_H

#define PSCI_POWER_STATE_LVL_0            0x0000000
#define PSCI_POWER_STATE_LVL_1            0x1000000
#define PSCI_POWER_STATE_LVL_2            0x2000000
#define PSCI_STATE_TYPE_STANDBY           0x00000
#define PSCI_STATE_TYPE_BIT               (1UL << 16)
#define PSCI_STATE_TYPE_POWERDOWN         PSCI_STATE_TYPE_BIT

#define PLAT_PSCI_POWERDOWN_NOT_SUPPORTED 1

#endif // PLAT_PSCI_H
