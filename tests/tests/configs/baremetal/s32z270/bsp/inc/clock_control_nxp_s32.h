/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */
#include <Clock_Ip.h>

Clock_Ip_StatusType nxp_s32_clock_init(void);
void Sys_EL1ResumeInterrupts(void);
void Sys_EL1SuspendInterrupts(void);
uint8 Sys_GetCoreID(void);