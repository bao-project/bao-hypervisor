/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_HYPERCALL_H
#define ARCH_HYPERCALL_H

/* We have to add 16 to the register to make it a D_Reg for the current
bao vcpu implementation. This happens because all regs are mixed in the
upper and lower CSAs, and we use LUT to correctly interpret the regs.
Since there is no define ABI for HVCALL, we use a similar calling convention
to the normal call. D4 is the first data argument and d2 is the return value.*/
#define HYPCALL_IN_ARG_REG(ARG)  ((ARG) + 16 + 4)
#define HYPCALL_OUT_ARG_REG(ARG) ((ARG) + 16 + 2)

#endif /* ARCH_HYPERCALL_H */
