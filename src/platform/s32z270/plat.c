/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */
#include <platform.h>
#include <plat/plat_regs.h>
#include <cpu.h>
#include <drivers/linflexd_uart.h>

void plat_cpu_init(cpuid_t cpuid, paddr_t load_addr)
{
    uint32_t reg_val;
    // Set start addr
    mmio32_write(MC_ME_PRTN1_COREX_ADDR(cpuid), load_addr);

    // Reset the core
    reg_val = mmio32_read(MC_RGM_PRST1_0);
    reg_val &= MC_RGM_PRST1_0_VAL(cpuid);
    mmio32_write(MC_RGM_PRST1_0, reg_val);

    if (!(mmio32_read(MC_ME_PRTN1_COREX_STAT(cpuid)) & MC_ME_PRTN1_COREX_STAT_CCS)) {
        // Enable the core clock
        reg_val = mmio32_read(MC_ME_PRTN1_COREX_PCONF(cpuid));
        reg_val |= MC_ME_PRTN1_COREX_PCONF_CCE;
        mmio32_write(MC_ME_PRTN1_COREX_PCONF(cpuid), reg_val);

        // Trigger the hardware process to enable the core clock
        reg_val = mmio32_read(MC_ME_PRTN1_COREX_PUPD(cpuid));
        reg_val |= MC_ME_PRTN1_COREX_PUPD_CCUPD;
        mmio32_write(MC_ME_PRTN1_COREX_PUPD(cpuid), reg_val);

        // Write the key to enable the core
        mmio32_write(MC_ME_CTL_KEY, MC_ME_CTL_KEY_KEY0);

        // Wait for the key to be written. Reads return bit inverted value corresponding to last
        // write.
        do {
            reg_val = mmio32_read(MC_ME_CTL_KEY);
        } while (reg_val != MC_ME_CTL_KEY_KEY1);

        // Invert key to initiate process
        mmio32_write(MC_ME_CTL_KEY, MC_ME_CTL_KEY_KEY1);

        // Poll the core status until it is ready
        do {
            reg_val = mmio32_read(MC_ME_PRTN1_COREX_STAT(cpuid));
        } while (!(reg_val & MC_ME_PRTN1_COREX_STAT_CCS));
    }

    // Poll reset lift
    do {
        reg_val = mmio32_read(MC_RGM_PSTAT1_0);
    } while (reg_val != (reg_val & MC_RGM_PRST1_0_VAL(cpuid)));
}

static void plat_iomux(void)
{
    /* Configure IOMUX settings for console (UART TX Pin) */
    /* Map SIUL2_5 region */
    mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, (uint32_t)INVALID_VA, (uint32_t)SIUL2_5_BASE,
        NUM_PAGES(SIUL2_5_SIZE));

    /* Configure SIUL2 settings for console (UART TX Pin) */
    mmio_write(SIUL2_MSCR_OFF(UART_TX_PIN), SIUL2_MSCR_TX);

    /* Unmap SIUL2_5 region */
    mem_unmap(&cpu()->as, SIUL2_5_BASE, NUM_PAGES(SIUL2_5_SIZE), false);
}

static void plat_clock(void)
{
    uint32_t reg_val;
    /* Configure clock settings for console */
    /* Map MC_CGM_5 region */
    mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, (uint32_t)INVALID_VA, (uint32_t)MC_CGM_5_BASE,
        NUM_PAGES(MC_CGM_5_SIZE));

    /* Configure clock source for console (FIRC_CLK)*/
    mmio_write(MC_CGM_5_MUX_2_CSC, MC_CGM_5_MUX_2_CSC_SAFE);

    do {
        reg_val = mmio_read(MC_CGM_5_MUX_2_CSS);
    } while ((reg_val & MC_CGM_5_MUX_2_CSS_SWIP) != 0);

    /* Enable divider */
    mmio_write(MC_CGM_5_MUX_2_DC_0, MC_CGM_5_MUX_2_DC_0_DE);

    /* Unmap MC_CGM_5 region */
    mem_unmap(&cpu()->as, MC_CGM_5_BASE, NUM_PAGES(MC_CGM_5_SIZE), false);
}

void plat_init(void)
{
    if (cpu_is_master()) {
        plat_iomux();

        plat_clock();
    }
}
