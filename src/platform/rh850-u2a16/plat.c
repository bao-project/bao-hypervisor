/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

void platform_default_init(void)
{
    if (cpu_is_master()) {
        /*** Module Standby Initialization ***/
        stbc_init();

        /*** MCU Clock Initialization ***/
        clock_init();

        /*** IO Ports Initialization ***/
        port_init();
    }

    cpu_sync_and_clear_msgs(&cpu_glb_sync);
}
