/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/psci.h>

/**
 * In Armv8-R systems there is no standard firmware readily available that
 * implements PSCI for each platform. Therefore, we provide a minimal
 * implementation of the necessary PSCI functions.
 * Note this might change in the future, or we might decide to implement
 * PSCI in Bao itself for each platform.
 */

int32_t psci_standby() { 
    asm volatile ("wfi");
    return PSCI_E_SUCCESS;
}

int32_t psci_power_down(enum wakeup_reason reason) {
    return psci_standby();
}
