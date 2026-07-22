/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>


static void temporaliy_set_system_clock(uint32_t sckcr2)
{
    uint32_t sckcr2_cpu_clock = R_SYSC_S->SCKCR2;

    /* Check if FSELCPU0 bit of sckcr2 variable is 00b and CPU0 clock is 800MHz. (Or 600MHz) */
    if (!(BSP_PRV_SCKCR2_FSELCPU0_MASK & sckcr2))
    {
        /* Set FSELCPU0 bit to 01b and CPU0 clock is 400MHz. (Or 300MHz) */
        sckcr2_cpu_clock =
            ((sckcr2_cpu_clock & ~R_SYSC_S_SCKCR2_FSELCPU0_Msk) | BSP_PRV_STARTUP_SCKCR2_FSELCPU0_ICLK_MUL2);
    }

    /* Check if FSELCPU1 bit of sckcr2 variable is 00b and CPU1 clock is 800MHz. (Or 600MHz) */
    if (!(BSP_PRV_SCKCR2_FSELCPU1_MASK & sckcr2))
    {
        /* Set FSELCPU1 bit to 01b and CPU1 clock is 400MHz. (Or 300MHz) */
        sckcr2_cpu_clock =
            ((sckcr2_cpu_clock & ~R_SYSC_S_SCKCR2_FSELCPU1_Msk) | BSP_PRV_STARTUP_SCKCR2_FSELCPU1_ICLK_MUL2);
    }

    /* Temporarily set system clock. */
    if (R_SYSC_S->SCKCR2 != sckcr2_cpu_clock)
    {
        R_SYSC_S->SCKCR2 = sckcr2_cpu_clock;

        /** In order to secure processing after clock frequency is changed,
         *  dummy read the same register at least eight times.
         *  Refer to "Notes on Clock Generation Circuit" in the RZ microprocessor manual. */
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
        FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    }
}

static void set_hard_reset(void)
{
    uint32_t sckcr  = BSP_PRV_STARTUP_SCKCR & BSP_PRV_SCKCR_MASK;
    uint32_t sckcr2 = BSP_PRV_STARTUP_SCKCR2 & BSP_PRV_SCKCR2_MASK;

    /* Note that if switching CPU clock to 800MHz, switch to 400MHz and then to 800MHz.
     * The same applies to changing the clock frequency when the bus reference clock is 150MHz.
     * This is the case if FSELCPUn bit of sckcr2 variable is 00b(CPU clock is 800MHz or 600MHz). */
    if (!(BSP_PRV_SCKCR2_FSELCPU0_MASK & sckcr2) || !(BSP_PRV_SCKCR2_FSELCPU1_MASK & sckcr2))
    {
        temporaliy_set_system_clock(sckcr2);
    }

    /* Set the system source clock */
    R_SYSC_S->SCKCR2 = sckcr2;

    /** In order to secure processing after clock frequency is changed,
     *  dummy read the same register at least eight times.
     *  Refer to "Notes on Clock Generation Circuit" in the RZ microprocessor manual. */
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);
    FSP_REGISTER_READ(R_SYSC_S->SCKCR2);

    R_SYSC_NS->SCKCR = sckcr;

    /** In order to secure processing after clock frequency is changed,
     *  dummy read the same register at least eight times.
     *  Refer to "Notes on Clock Generation Circuit" in the RZ microprocessor manual. */
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);
    FSP_REGISTER_READ(R_SYSC_NS->SCKCR);

    /* Clock is now at requested frequency. */
}

void rzt2m_clock_init (void)
{
    /* Unlock CGC protection registers. */
    register_protect_disable(BSP_REG_PROTECT_CGC);  
    
    set_hard_reset();
    
    R_SYSC_S->LOCOCR = BSP_CLOCKS_LOCO_ENABLE;

    /* Only start using the LOCO clock after
     * the LOCO oscillation stabilization time (tLOCOWT) has elapsed. */
    for (uint16_t i = 0; i < BSP_PRV_LOCO_STABILIZATION_COUNT; i++)
    {
        __asm volatile ("nop");
    }

    R_SYSC_S->HIZCTRLEN = BSP_PRV_STARTUP_HIZCTRLEN;

    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA0->CMPL = BSP_CFG_CLMA0_CMPL;
    R_CLMA0->CMPH = BSP_CFG_CLMA0_CMPH;

    /* Enabling CLMA0 operation. */
    do
    {
        R_CLMA0->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA0->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA0->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA0->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA0->CTL0)
        {
            /* Check the value of PROTSR register. */
            FSP_REGISTER_READ(R_CLMA0->PROTSR);
        }
    } while (1 == R_CLMA0->PROTSR_b.PRERR);


    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA1->CMPL = BSP_CFG_CLMA1_CMPL;
    R_CLMA1->CMPH = BSP_CFG_CLMA1_CMPH;

    /* Enabling CLMA1 operation. */
    do
    {
        R_CLMA1->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA1->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA1->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA1->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA1->CTL0)
        {
            /* Check the value of PROTSR register. */
            FSP_REGISTER_READ(R_CLMA1->PROTSR);
        }
    } while (1 == R_CLMA1->PROTSR_b.PRERR);


    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA2->CMPL = BSP_CFG_CLMA2_CMPL;
    R_CLMA2->CMPH = BSP_CFG_CLMA2_CMPH;

    /* Enabling CLMA2 operation. */
    do
    {
        R_CLMA2->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA2->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA2->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA2->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA2->CTL0)
        {
            /* Check the value of PROTSR register. */
            FSP_REGISTER_READ(R_CLMA2->PROTSR);
        }
    } while (1 == R_CLMA2->PROTSR_b.PRERR);


    /* Set the lower and upper limit for comparing frequency domains. */
    R_CLMA3->CMPL = BSP_CFG_CLMA3_CMPL;
    R_CLMA3->CMPH = BSP_CFG_CLMA3_CMPH;

    /* Enabling CLMA3 operation. */
    do
    {
        R_CLMA3->PCMD = BSP_PRV_PCMD_KEY;

        R_CLMA3->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;
        R_CLMA3->CTL0 = BSP_PRV_CTL0_ENABLE_REVERSED_CMD;
        R_CLMA3->CTL0 = BSP_PRV_CTL0_ENABLE_TARGET_CMD;

        if (1 != R_CLMA3->CTL0)
        {
            /* Check the value of PROTSR register. */
            FSP_REGISTER_READ(R_CLMA3->PROTSR);
        }
    } while (1 == R_CLMA3->PROTSR_b.PRERR);

    /* Lock CGC protection registers. */
    register_protect_enable(BSP_REG_PROTECT_CGC); 
}









