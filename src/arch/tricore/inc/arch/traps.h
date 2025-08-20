/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __TRAPS_H__
#define __TRAPS_H__

#define D15_TIN_MASK 0xFF

void sys_bus_errors_handler(void);
void l2_dmem_prot_trap_handler(unsigned long* addr, unsigned long access);
void hyp_csfr_access_handler(unsigned long* addr, unsigned long hvtin);
void hvcall_handler(unsigned long function_id);

#endif /* __TRAPS_H__ */
