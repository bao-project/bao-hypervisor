/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <platform.h>
#include <arch/sysregs.h>

uint64_t platform_arch_cpuid_to_mpdir(const struct platform_desc* plat,
                                      uint64_t cpuid)
{
    if (cpuid > plat->cpu_num) {
        return 0;  // zero is and invalid mpidr since it has res1 bits
    }

    uint64_t mpidr = 0;
    bool found = false;
    if (plat->arch.clusters.num > 0) {
        for (int i = 0, j = 0; i < plat->arch.clusters.num; i++) {
            if (cpuid < (j + plat->arch.clusters.core_num[i])) {
                mpidr = (i << 8) | ((cpuid - j) & 0xff);
                found = true;
                break;
            }

            j += plat->arch.clusters.core_num[i];
        }

        if (!found) {
            ERROR("failed cpuid to mpdir translation");
        }
    } else {
        /**
         * No cluster information in configuration. Assume a singl cluster.
         */
        mpidr = cpuid;
    }

    mpidr |= MPIDR_RES1;
    if (plat->cpu_num == 1) {
        mpidr |= MPIDR_U_BIT;
    }

    return mpidr;
}
