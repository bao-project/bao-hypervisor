/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <platform.h>

void platform_init(void) {

    if (cpu_is_master()) {

        /*** Peripheral Bus Guard Initialization ***/
        pbg_init();

        /*** Module Standby Initialization ***/
        stbc_init();

        /*** MCU Clock Initialization ***/
        clock_init();

        /*** IO Ports Initialization ***/
        port_init();

        /*** Custom Platform Initilization ***/
        custom_platform_init();
    }

    cpu_sync_and_clear_msgs(&cpu_glb_sync);
}

__attribute__((weak)) void custom_platform_init(void) { }
