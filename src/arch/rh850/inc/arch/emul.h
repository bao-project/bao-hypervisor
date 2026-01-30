/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_EMUL_H__
#define __ARCH_EMUL_H__

#include <emul.h>

/* The order of the operations can NOT be modified */
enum bitwise_op { BWOP_NO, BWOP_SET1, BWOP_NOT1, BWOP_CLR1, BWOP_TST1 };

struct emul_access_arch {
    enum bitwise_op op;
    unsigned long byte_mask;
};

struct emul_access;
struct vm;
unsigned long bitwise_op_get_acc_bitop_mask(struct emul_access* acc);
void bitwise_op_set_gmpse(unsigned long cur_val, unsigned long bitop_mask);

unsigned long bitwise_op_set_val(struct emul_access* acc, unsigned long cur_val,
    unsigned long bitop_mask);

#endif /* __ARCH_EMUL_H__ */
