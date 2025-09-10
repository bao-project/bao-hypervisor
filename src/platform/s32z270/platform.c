/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */
#include <platform.h>
#include <plat/plat_regs.h>
#include <cpu.h>
#include <drivers/linflexd_uart.h>

volatile struct mc_me_hw* mc_me = (struct mc_me_hw*)MC_ME_BASE;
volatile struct mc_rgm_hw* mc_rgm = (struct mc_rgm_hw*)MC_RGM_BASE;
volatile struct siul2_hw* siul2_5 = (struct siul2_hw*)SIUL2_5_BASE;
volatile struct mc_cgm_hw* mc_cgm_5 = (struct mc_cgm_hw*)MC_CGM_5_BASE;

void plat_cpu_init(cpuid_t cpuid, paddr_t load_addr)
{
    uint32_t reg_val;

    // Set start addr
    mc_me->PRTN1_COREX[cpuid].ADDR = load_addr;

    // Reset the core
    mc_rgm->PRST1_0 &= MC_RGM_PRST1_0_VAL(cpuid);

    if (!(mc_me->PRTN1_COREX[cpuid].STAT & MC_ME_PRTN1_COREX_STAT_CCS)) {
        // Enable the core clock
        mc_me->PRTN1_COREX[cpuid].PCONF |= MC_ME_PRTN1_COREX_PCONF_CCE;

        // Trigger the hardware process to enable the core clock
        mc_me->PRTN1_COREX[cpuid].PUPD |= MC_ME_PRTN1_COREX_PUPD_CCUPD;

        // Write the key to enable the core
        mc_me->CTL_KEY = MC_ME_CTL_KEY_KEY0;

        // Wait for the key to be written. Reads return bit inverted value corresponding to last
        // write.
        do {
            reg_val = mc_me->CTL_KEY;
        } while (reg_val != MC_ME_CTL_KEY_KEY1);

        // Invert key to initiate process
        mc_me->CTL_KEY = MC_ME_CTL_KEY_KEY1;

        // Poll the core status until it is ready
        while (!(mc_me->PRTN1_COREX[cpuid].STAT & MC_ME_PRTN1_COREX_STAT_CCS))
            ;
    }

    // Poll reset lift
    while (mc_rgm->PSTAT1_0 != (mc_rgm->PSTAT1_0 & MC_RGM_PRST1_0_VAL(cpuid)))
        ;
}

static void plat_iomux(void)
{
    /* Configure IOMUX settings for console (UART TX Pin) */
    /* Map SIUL2_5 region */
    mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, (uint32_t)INVALID_VA, (uint32_t)SIUL2_5_BASE,
        NUM_PAGES(sizeof(struct siul2_hw)));
    /* Configure SIUL2 settings for console (UART TX Pin) */
    siul2_5->MSCR[UART_TX_PIN] = SIUL2_MSCR_TX;

    /* Unmap SIUL2_5 region */
    mem_unmap(&cpu()->as, SIUL2_5_BASE, NUM_PAGES(sizeof(struct siul2_hw)), false);
}

static void plat_clock(void)
{
    /* Configure clock settings for console */
    /* Map MC_CGM_5 region */
    mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, (uint32_t)INVALID_VA, (uint32_t)MC_CGM_5_BASE,
        NUM_PAGES(sizeof(struct mc_cgm_hw)));

    /* Configure clock source for console (FIRC_CLK)*/
    mc_cgm_5->MUX_2_CSC = MC_CGM_5_MUX_2_CSC_SAFE;

    while ((mc_cgm_5->MUX_2_CSC & MC_CGM_5_MUX_2_CSS_SWIP) != 0)
        ;

    /* Enable divider */
    mc_cgm_5->MUX_2_DC_0 = MC_CGM_5_MUX_2_DC_0_DE;

    /* Unmap MC_CGM_5 region */
    mem_unmap(&cpu()->as, MC_CGM_5_BASE, NUM_PAGES(sizeof(struct mc_cgm_hw)), false);
}

void platform_default_init(void)
{
    if (cpu_is_master()) {
        plat_iomux();

        plat_clock();
    }
}
