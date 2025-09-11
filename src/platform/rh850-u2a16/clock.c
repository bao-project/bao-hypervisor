/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

volatile struct clk_ctl_iso_hw* clk_ctl_iso;
volatile struct clk_ctl_awo_hw* clk_ctl_awo;

void clock_init(void)
{
    size_t stab_cnt = 0;

    /* Map ISO clock controller MMIO */
    vaddr_t clk_iso_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA,
        (paddr_t)(PLAT_CLK_ISO_BASE), NUM_PAGES(sizeof(struct clk_ctl_iso_hw)));
    if (clk_iso_ptr == INVALID_VA) {
        ERROR("Maping clock ISO area failed");
    }
    clk_ctl_iso = (struct clk_ctl_iso_hw*)clk_iso_ptr;

    /* Map AWO clock controller MMIO */
    vaddr_t clk_awo_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA,
        (paddr_t)(PLAT_CLK_AWO_BASE), NUM_PAGES(sizeof(struct clk_ctl_awo_hw)));
    if (clk_awo_ptr == INVALID_VA) {
        ERROR("maping clock AWO area failed");
    }
    clk_ctl_awo = (struct clk_ctl_awo_hw*)clk_awo_ptr;

    /* Disable CLK registers protection */
    clk_ctl_iso->CLKKCPROT1 = CLKKCPROT1_ENABLE_WR;

    /* Start main oscillator, if not started */
    if (!(clk_ctl_awo->MOSCS & MOSCS_MOSCEN_BIT) && !(clk_ctl_awo->MOSCS & MOSCS_MOSCSTAB_BIT)) {
        /* Start the Main OSC */
        clk_ctl_awo->MOSCE = MOSCE_MOSCENTRG_BIT;
        /* Confirm that the Main OSC has been stable */
        while (!(clk_ctl_awo->MOSCS & MOSCS_MOSCEN_BIT) ||
            !(clk_ctl_awo->MOSCS & MOSCS_MOSCSTAB_BIT))
            ;
        /* Wait 1.4us or Read the MOSCS.MOSCSTAB = 1 four times */
        while (stab_cnt < 4) {
            stab_cnt += ((clk_ctl_awo->MOSCS & MOSCS_MOSCSTAB_BIT) >> 1);
        }
    }

    stab_cnt = 0;

    /* Trigger PLL, if not already started */
    if (!(clk_ctl_iso->PLLS & PLLS_PLLCLKEN_BIT) && !(clk_ctl_iso->PLLS & PLLS_PLLCLKSTAB_BIT)) {
        /* Trigger PLL */
        clk_ctl_iso->PLLE = PLLE_PLLENTRG_BIT;
        /* Confirm that the PLL has been stable */
        while (!(clk_ctl_iso->PLLS & PLLS_PLLCLKEN_BIT) ||
            !(clk_ctl_iso->PLLS & PLLS_PLLCLKSTAB_BIT))
            ;
        /* Wait 1.4us or Read the PLLS.PLLCLKSTAB = 1 four times */
        while (stab_cnt < 4) {
            stab_cnt += ((clk_ctl_iso->PLLS & PLLS_PLLCLKSTAB_BIT) >> 1);
        }
    }

    /* Select CLK_PLLO clock source */
    clk_ctl_iso->CKSC_CPUC = 0UL;

    /* Set CLKs to continue in standby mode */
    clk_ctl_iso->PLLSTPM = 1UL;
    clk_ctl_awo->MOSCSTPM = 1UL;

    /* Enable CLK registers protection */
    clk_ctl_iso->CLKKCPROT1 = CLKKCPROT1_DISABLE_WR;

    mem_unmap(&cpu()->as, (vaddr_t)(PLAT_CLK_ISO_BASE), NUM_PAGES(sizeof(struct clk_ctl_iso_hw)),
        true);
    mem_unmap(&cpu()->as, (vaddr_t)(PLAT_CLK_AWO_BASE), NUM_PAGES(sizeof(struct clk_ctl_awo_hw)),
        true);
}
