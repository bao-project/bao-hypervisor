/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_HYPERCALL_H
#define ARCH_HYPERCALL_H

#define HYPCALL_IN_ARG_REG(ARG)  ((ARG) + 1 + 15 + 5)
#define HYPCALL_OUT_ARG_REG(ARG) (HYPCALL_IN_ARG_REG(ARG))

#endif /* ARCH_HYPERCALL_H */
