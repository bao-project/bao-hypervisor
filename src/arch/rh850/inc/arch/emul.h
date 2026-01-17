/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_EMUL_H__
#define __ARCH_EMUL_H__

#include <emul.h>

/* The order of the operations can NOT be modified */
enum bitwise_op { NO_OP, SET1, NOT1, CLR1, TST1 };

struct emul_access_arch {
    enum bitwise_op op;
    unsigned long byte_mask;
};

#endif /* __ARCH_EMUL_H__ */
