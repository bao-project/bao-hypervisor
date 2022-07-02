/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aborts.h>
#include <cpu.h>
#include <vm.h>
#include <arch/psci.h>

void smc_handler(unsigned long iss, unsigned long far, unsigned long il)
{
    unsigned long smc_fid = vcpu_readreg(cpu()->vcpu, 0);
    unsigned long x1 = vcpu_readreg(cpu()->vcpu, 1);
    unsigned long x2 = vcpu_readreg(cpu()->vcpu, 2);
    unsigned long x3 = vcpu_readreg(cpu()->vcpu, 3);

    int64_t ret = -1;

    if (is_psci_fid(smc_fid)) {
        ret = psci_smc_handler(smc_fid, x1, x2, x3);
    } else {
        INFO("unknown smc_fid 0x%lx", smc_fid);
    }

    vcpu_writereg(cpu()->vcpu, 0, ret);
    unsigned long pc_step = 2 + (2 * il);
    vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
}
