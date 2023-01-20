/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __SMC_H__
#define __SMC_H__

#include <bao.h>

struct smc_res {
    unsigned long x0;
    unsigned long x1;
    unsigned long x2;
    unsigned long x3;
};

unsigned long smc_call(unsigned long x0, unsigned long x1, unsigned long x2,
                    unsigned long x3, struct smc_res *res);

#endif
