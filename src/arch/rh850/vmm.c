/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/mpu.h>
#include <vmm.h>
#include <arch/srs.h>
#include <arch/fences.h>

void vmm_arch_init(void)
{
    /* HVCFG.HVE is set after reset */

    /* configure Hypervisor MPIDs for memory protection */
    mpu_arch_disable();
    set_mpid0(HYP_SPID);
    set_mpid7(HYP_AUX_SPID);
    set_spid(HYP_SPID);
    mpu_arch_enable();

    set_gmcfg(GMCFG_GCU1 | GMCFG_GCU0 | GMCFG_GSYSE | GMCFG_HMP);

    set_eipswh(EIPSWH_GM);
    set_fepswh(FEPSWH_GM);
}
