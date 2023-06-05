/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <arch/sysregs.h>

unsigned long platform_arch_cpuid_to_mpidr(const struct platform* plat,
                                      cpuid_t cpuid)
{
    if (cpuid > plat->cpu_num) {
        return ~(~MPIDR_RES1 & MPIDR_RES0_MSK); //return an invlid mpidr by inverting res bits
    }

    unsigned long mpidr = 0;
    bool found = false;
    if (plat->arch.clusters.num > 0) {
        for (size_t i = 0, j = 0; i < plat->arch.clusters.num; i++) {
            if (cpuid < (j + plat->arch.clusters.core_num[i])) {
                mpidr = (i << 8) | ((cpuid - j) & 0xff);
                found = true;
                break;
            }

            j += plat->arch.clusters.core_num[i];
        }

        if (!found) {
            ERROR("failed cpuid to mpidr translation");
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
