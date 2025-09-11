/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/mpu.h>
#include <vmm.h>
#include <srs.h>
#include <arch/fences.h>

void vmm_arch_init(void)
{
    /* HVCFG.HVE is set after reset */

    srs_gmcfg_write(GMCFG_GCU1 | GMCFG_GCU0 | GMCFG_GSYSE | GMCFG_HMP);

    srs_eipswh_write(EIPSWH_GM);
    srs_fepswh_write(FEPSWH_GM);
}
