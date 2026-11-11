/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PSCI_H__
#define __PLAT_PSCI_H__

#define PSCI_POWER_STATE_LVL_0    (0x0U)

#define PSCI_STATE_TYPE_STANDBY   (0x0U)
#define PSCI_STATE_TYPE_BIT       (1UL << 16)

#define PSCI_STATE_ID_RUN         (0x0U)
#define PSCI_STATE_ID_RETENTION   (0x1U)
#define PSCI_STATE_ID_POWERDOWN   (0x2U)

#define PSCI_STATE_TYPE_POWERDOWN PSCI_STATE_TYPE_BIT | PSCI_STATE_ID_POWERDOWN

#endif // __PLAT_PSCI_H__
