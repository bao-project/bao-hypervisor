/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <arch/smc.h>

unsigned long smc_call(unsigned long x0, unsigned long x1, unsigned long x2,
                    unsigned long x3, struct smc_res *res)
{
    register unsigned long r0 asm("x0") = x0;
    register unsigned long r1 asm("x1") = x1;
    register unsigned long r2 asm("x2") = x2;
    register unsigned long r3 asm("x3") = x3;

    asm volatile("smc	#0\n" : "=r"(r0) : "r"(r0), "r"(r1), "r"(r2), "r"(r3));

    if (res != NULL) {
        res->x0 = r0;
        res->x1 = r1;
        res->x2 = r2;
        res->x3 = r3;
    }

    return r0;
}
