/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <arch/sysregs.h>

unsigned long platform_arch_cpuid_to_mpidr(const struct platform* plat, cpuid_t cpuid)
{
    if (cpuid >= plat->cpu_num) {
        return ~(~MPIDR_RES1 & MPIDR_RES0_MSK);
    }

    unsigned long mpidr = 0;

    /* Prefer MPIDR table if available */
    if (plat->arch.mpidr_table.table != NULL) {
        mpidr = plat->arch.mpidr_table.table[cpuid];

        mpidr |= MPIDR_RES1;

        if (plat->cpu_num == 1) {
            mpidr |= MPIDR_U_BIT;
        }

        return mpidr;
    }

    /* SoCs use a uniform topology; use current CPU MT bit */
    unsigned long cur_mpidr = sysreg_mpidr_el1_read();
    bool has_mt = (cur_mpidr & MPIDR_MT_BIT) != 0;

    /* Use cluster topology if available */
    if (plat->arch.clusters.num > 0) {
        size_t base = 0;

        for (size_t cluster = 0; cluster < plat->arch.clusters.num; cluster++) {
            size_t cores = plat->arch.clusters.core_num[cluster];

            if (cpuid < base + cores) {
                unsigned long core = cpuid - base;

                if (has_mt) {
                    mpidr = (cluster << 16) | (core << 8);
                } else {
                    mpidr = (cluster << 8) | (core & 0xff);
                }

                goto done;
            }

            base += cores;
        }

        ERROR("failed cpuid to mpidr translation\n");
    }

    if (has_mt) {
        mpidr = (cpuid << 8);
    } else {
        mpidr = cpuid;
    }

done:

    mpidr |= MPIDR_RES1;

    if (plat->cpu_num == 1) {
        mpidr |= MPIDR_U_BIT;
    }

    if (has_mt) {
        mpidr |= MPIDR_MT_BIT;
    }

    return mpidr;
}
