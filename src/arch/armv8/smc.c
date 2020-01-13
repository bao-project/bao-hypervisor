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

uint64_t smc_call(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3,
                  smc_res_t *res)
{
    register uint64_t r0 asm("x0") = x0;
    register uint64_t r1 asm("x1") = x1;
    register uint64_t r2 asm("x2") = x2;
    register uint64_t r3 asm("x3") = x3;

    asm volatile("smc	#0\n" : "=r"(r0) : "r"(r0), "r"(r1), "r"(r2), "r"(r3));

    if (res != NULL) {
        res->x0 = r0;
        res->x1 = r1;
        res->x2 = r2;
        res->x3 = r3;
    }

    return r0;
}