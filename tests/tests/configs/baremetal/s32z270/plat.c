/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */
#include <fences.h>
#include <cpu.h>
#include <arch/sysregs.h>
#include <platform.h>
#include <plat/plat_regs.h>
#define SIUL2_0_BASE                (0x40520000UL)
#define SIUL2_IMCR_UART0_RX_OFF     (47UL)

#define UART0_TX_PIN                (0UL)
#define UART0_RX_PIN                (1UL)

#define MC_CGM_0_BASE               (0x40030000UL)
#define MC_CGM_0_MUX_4_CSC_SAFE     (1UL << 3UL)
#define MC_CGM_0_MUX_4_CSS_SWIP     (1UL << 16UL)
#define MC_CGM_0_MUX_4_DC_0_DE      (1UL << 31UL)

/* RTU General Purpose Registers */
#define RTU_GPR_BASE                    0x76120000UL
#define RTU_GPR_CFG_CNTDV               (RTU_GPR_BASE + 0x10)

volatile struct siul2_hw* siul2_0 = (struct siul2_hw*)SIUL2_0_BASE;
volatile struct mc_cgm_hw* mc_cgm_0 = (struct mc_cgm_hw*)MC_CGM_0_BASE;

extern void bsp_entrypoint(void);

static void plat_uart0_iomux(void)
{
    /* Configure IOMUX settings for console (UART TX Pin) */
    /* Configure SIUL2 settings for console (UART TX Pin) */
    siul2_0->MSCR[UART0_TX_PIN] = SIUL2_MSCR_TX;
    /* Configure SIUL2 settings for console (UART RX Pin) */
    siul2_0->MSCR[UART0_RX_PIN] = SIUL2_MSCR_RX;
    siul2_0->IMCR[SIUL2_IMCR_UART0_RX_OFF] = SIUL2_IMCR_RX;
}

static void plat_uart0_clock(void)
{
    /* Configure clock settings for console */
    /* Configure clock source for console (FIRC_CLK)*/
    mc_cgm_0->MUX_4_CSC = MC_CGM_0_MUX_4_CSC_SAFE;

    while ((mc_cgm_0->MUX_4_CSS & MC_CGM_0_MUX_4_CSS_SWIP) != 0);

    /* Enable divider */
    mc_cgm_0->MUX_4_DC_0 = MC_CGM_0_MUX_4_DC_0_DE;
}

static void plat_timer_init(void)
{
    /* Set counter div to zero */
    volatile uint32_t* rtu_gpr_cntdv = (volatile uint32_t*)RTU_GPR_CFG_CNTDV;
    *rtu_gpr_cntdv = 0;

    /* Set the timer frequency to 40MHz */
    sysreg_cntfrq_el0_write(40000000);
}

void platform_config_init(void)
{
    if (cpu_is_master()) {
        mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, 0x40000000,
                NUM_PAGES(0x77000000 - 0x40000000));

    /* Configure iomux and clock for baremetal guest (UART0) */
    plat_uart0_iomux();
    plat_uart0_clock();

    /* Set timer */
    plat_timer_init();

    /* Call BSP entrypoint to allow clock platform initialization to 1GHz */
    bsp_entrypoint();

        mem_unmap(&cpu()->as, 0x40000000, NUM_PAGES(0x77000000 - 0x40000000), false);
    }
}