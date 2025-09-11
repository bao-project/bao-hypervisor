/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

extern uint16_t port_reg_val[PLAT_NUM_PORT_CFG_REGS][PLAT_NUM_PORT_GROUPS];
extern uint16_t aport_reg_val[PLAT_NUM_APORT_CFG_REGS][PLAT_NUM_APORT_GROUPS];

volatile struct port_hw* port;

void port_init(void)
{
    size_t shift = 0;

    /* Map port MMIO */
    vaddr_t port_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA,
        (paddr_t)(PLAT_PORT_BASE), NUM_PAGES(sizeof(struct port_hw)));
    if (port_ptr == INVALID_VA) {
        ERROR("Maping PORT area failed");
    }
    port = (struct port_hw*)port_ptr;

    /* Enable write to port registers */
    port->PKCPROT = PORT_PKCPROT_ENABLE_WR;
    port->PWE = PORT_PWE_ENABLE_ALL_MASK;
    port->PKCPROT = PORT_PKCPROT_DISABLE_WR;

    /* Configure port registers */
    for (size_t i = 0; i < PLAT_MAX_NUM_PORT_GROUPS; i++) {
        /* If port group is not supported, skip */
        if (!((1UL << i) & PLAT_PORT_GROUP_MASK)) {
            shift++;
            continue;
        }

        port->p_regset1[i].P = port_reg_val[Pn][i - shift];
        port->p_regset1[i].PM = port_reg_val[PMn][i - shift];
        port->p_regset1[i].PMC = port_reg_val[PMCn][i - shift];
        port->p_regset1[i].PFC = port_reg_val[PFCn][i - shift];
        port->p_regset1[i].PFCE = port_reg_val[PFCEn][i - shift];
        port->p_regset1[i].PFCAE = port_reg_val[PFCAEn][i - shift];
        port->p_regset1[i].PINV = port_reg_val[PINVn][i - shift];

        port->p_regset3[i].PIBC = port_reg_val[PIBCn][i - shift];
        port->p_regset3[i].PBDC = port_reg_val[PBDCn][i - shift];
        port->p_regset3[i].PIPC = port_reg_val[PIPCn][i - shift];
        port->p_regset3[i].PU = port_reg_val[PUn][i - shift];
        port->p_regset3[i].PD = port_reg_val[PDn][i - shift];
        port->p_regset3[i].PODC = port_reg_val[PODCn][i - shift];
        port->p_regset3[i].PDSC = port_reg_val[PDSCn][i - shift];
        port->p_regset3[i].PIS = port_reg_val[PISn][i - shift];
        port->p_regset3[i].PISA = port_reg_val[PISAn][i - shift];
        port->p_regset3[i].PUCC = port_reg_val[PUCCn][i - shift];
        port->p_regset3[i].PODCE = port_reg_val[PODCEn][i - shift];

        port->p_regset4[i].PSFC = port_reg_val[PSFCn][i - shift];
        port->p_regset4[i].PSFTS = port_reg_val[PSFTSn][i - shift];
        port->p_regset4[i].PSFTSE = port_reg_val[PSFTSEn][i - shift];

        /*
            The following port registers are not configured, since they
            either provide an alternative mechanism to access the registers
            above or they do not represent a static port configuration.
            - PSR
            - PNOT
            - PPR
            - PMSR
            - PMCSR
            - PCR
        */
    }

    shift = 0;

    /* Configure analogic port registers */
    for (size_t i = 0; i < PLAT_MAX_NUM_APORT_GROUPS; i++) {
        /* If port group is not supported, skip */
        if (!((1UL << i) & PLAT_APORT_GROUP_MASK)) {
            shift++;
            continue;
        }

        port->ap_regset1[i].AP = aport_reg_val[APn][i - shift];
        port->ap_regset1[i].APM = aport_reg_val[APMn][i - shift];
        port->ap_regset1[i].APINV = aport_reg_val[APINVn][i - shift];

        port->ap_regset3[i].APIBC = aport_reg_val[APIBCn][i - shift];
        port->ap_regset3[i].APBDC = aport_reg_val[APBDCn][i - shift];
        port->ap_regset3[i].APODC = aport_reg_val[APODCn][i - shift];
        port->ap_regset3[i].APDSC = aport_reg_val[APDSCn][i - shift];
        port->ap_regset3[i].APODCE = aport_reg_val[APODCEn][i - shift];

        port->ap_regset4[i].APSFC = aport_reg_val[APSFCn][i - shift];
        port->ap_regset4[i].APSFTS = aport_reg_val[APSFTSn][i - shift];
        port->ap_regset4[i].APSFTSE = aport_reg_val[APSFTSEn][i - shift];

        /*
            The following port registers are not configured, since they
            either provide an alternative mechanism to access the registers
            above or they do not represent a static port configuration.
            - APSR
            - APNOT
            - APPR
            - APMSR
            - APCR
        */
    }

    /* Disable write to port registers */
    port->PKCPROT = PORT_PKCPROT_ENABLE_WR;
    port->PWE = 0;
    port->PKCPROT = PORT_PKCPROT_DISABLE_WR;

    mem_unmap(&cpu()->as, (vaddr_t)(PLAT_PORT_BASE), NUM_PAGES(sizeof(struct port_hw)), true);
}
