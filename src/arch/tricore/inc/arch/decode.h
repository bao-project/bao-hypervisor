/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __DECODE_H__
#define __DECODE_H__

bool decode_16b_access(unsigned long ins, struct emul_access* emul);
bool decode_32b_access(unsigned long ins, struct emul_access* emul);
unsigned long decode_cfr_access(unsigned long ins, struct emul_access* emul);

#endif /*__DECODE_H__ */
