/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ABORTS_H__
#define __ABORTS_H__

#include <bao.h>

void aborts_sync_handler(void);
void aborts_internal_handler(unsigned long gprs[]);
/* Entered only from the AArch64 EL2 IRQ and FIQ vectors. */
void aborts_internal_irq_handler(unsigned long gprs[]);

#endif /* __ABORTS_H__ */
