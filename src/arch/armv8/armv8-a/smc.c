/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/smc.h>

unsigned long smc_call(unsigned long x0, unsigned long x1, unsigned long x2, unsigned long x3,
    struct smc_res* res)
{
    register unsigned long r0 __asm__(GPR(0)) = x0;
    register unsigned long r1 __asm__(GPR(1)) = x1;
    register unsigned long r2 __asm__(GPR(2)) = x2;
    register unsigned long r3 __asm__(GPR(3)) = x3;

    __asm__ volatile("smc	#0\n" : "=r"(r0) : "r"(r0), "r"(r1), "r"(r2), "r"(r3));

    if (res != NULL) {
        res->x0 = r0;
        res->x1 = r1;
        res->x2 = r2;
        res->x3 = r3;
    }

    return r0;
}
