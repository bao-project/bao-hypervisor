/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

#define PBGPROT1_SPID_MASK (((1UL << 16) - 1) | (1UL << 16))

volatile struct pbg_hw* pbg;

void pbg_init(void)
{
    /* Enable temporary access to PBG registers */
    vaddr_t pbg_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA,
        (paddr_t)(PLAT_PBG_BASE), NUM_PAGES(sizeof(struct pbg_hw)));
    if (pbg_ptr == INVALID_VA) {
        ERROR("Maping PBG MMIO failed");
    }
    pbg = (struct pbg_hw*)pbg_ptr;

    /* Enable write to PBGPROT registers */
    pbg->PBGERRSLV00.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV10.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV20.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV30.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV40.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV50.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV6L0.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV6L1.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV6H0.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV70.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV80.PBGKCPROT = PBGKCPROT_ENABLE_WR;
    pbg->PBGERRSLV90.PBGKCPROT = PBGKCPROT_ENABLE_WR;

    /* Allow SPIDs [0-16] to write to P-Bus */
    for (size_t i = 0; i < PLAT_NUM_PBG_CHANNELS; i++) {
        pbg->PBG00.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG10.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG20.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG30.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG40.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG50.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG6L0.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG6L1.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG6H0.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG70.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG80.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
        pbg->PBG90.ch[i].PBGPROT1 |= (PBGPROT1_SPID_MASK);
    }

    /* Disable write to PBGPROT registers */
    pbg->PBGERRSLV00.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV10.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV20.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV30.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV40.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV50.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV6L0.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV6L1.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV6H0.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV70.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV80.PBGKCPROT = PBGKCPROT_DISABLE_WR;
    pbg->PBGERRSLV90.PBGKCPROT = PBGKCPROT_DISABLE_WR;

    mem_unmap(&cpu()->as, (vaddr_t)(PLAT_PBG_BASE), NUM_PAGES(sizeof(struct pbg_hw)), true);
}
