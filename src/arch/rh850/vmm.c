/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vmm.h>
#include <arch/srs.h>
#include <arch/fences.h>

void vmm_arch_init(void)
{
    /* HVCFG.HVE is set after reset */

    /* set GMCFG.HMP, GMCFG.GSYSE, GMCFG */
    set_gmcfg(0x30012);
    if (get_gmcfg() != 0x30012){
        ERROR("GMCFG is not being written");
    }

    // TODO: set xxPSWH.GPID with the VM ID

    /* set EIPSWH.GM */
    set_eipswh(0x80000000);
    if (get_eipswh() != 0x80000000){
        ERROR("EIPSWH is not being written");
    }

    /* set FEPSWH.GM */
    set_fepswh(0x80000000);
    if (get_fepswh() != 0x80000000){
        ERROR("FEPSWH is not being written");
    }

    /* set GMMPM.GMPE */
    set_gmmpm(0x4);
    if (get_gmmpm() != 0x4){
        ERROR("GMMPM is not being written");
    }

    /* set GMSPIDLIST with available SPIDs not used by the hyp */
    set_gmspidlist(0x0);

    /* set GMSPID */
    set_gmspid(VM_SPID);

    /* clear guest-context exception registers */
    set_gmeipc(0x0);
    set_gmfepc(0x0);
    set_gmmea(0x0);
    set_gmmei(0x0);
    set_gmeiic(0x0);
    set_gmfeic(0x0);
}

void vmm_enable_access_to_vm(void)
{
    set_mpid7(HYP_SPID);
    fence_sync();
}

void vmm_disable_access_to_vm(void)
{
    set_mpid7(AUX_SPID);
    fence_sync();
}
