/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

/** Used for holding reference counters for protection bits. */
volatile uint16_t g_protect_counters[4] = {
    0U, 0U, 0U, 0U
};

/** Masks for setting or clearing the PRCR register. Use -1 for size because PWPR in MPC is used differently. */
static const uint16_t g_prcr_masks[] =
{
    0x0001U,    /* PRC0. */
    0x0002U,    /* PRC1. */
    0x0004U,    /* PRC2. */
    0x0008U,    /* PRC3. */
};


/*******************************************************************************************************************//**
 *        Enable register protection. Registers that are protected cannot be written to. Register protection is
 *          enabled by using the Protect Register (PRCR) and the MPC's Write-Protect Register (PWPR).
 *
 * @param[in] regs_to_protect Registers which have write protection enabled.
 **********************************************************************************************************************/
void register_protect_enable(bsp_reg_protect_t regs_to_protect)
{
    /** Get/save the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Is it safe to disable write access? */
    if (0U != g_protect_counters[regs_to_protect])
    {
        /* Decrement the protect counter */
        g_protect_counters[regs_to_protect]--;
    }

    /* Is it safe to disable write access? */
    if (0U == g_protect_counters[regs_to_protect])
    {
        /** Enable protection using PRCR register.
         * When writing to the PRCR register the upper 8-bits must be the correct key.
         * Set lower bits to 0 to disable writes. */
        R_RWP_NS->PRCRN = ((R_RWP_NS->PRCRN | BSP_REG_PROTECT_PRCR_KEY) & (uint16_t) (~g_prcr_masks[regs_to_protect]));
        R_RWP_S->PRCRS  = ((R_RWP_S->PRCRS | BSP_REG_PROTECT_PRCR_KEY) & (uint16_t) (~g_prcr_masks[regs_to_protect]));
    }

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 *        Disable register protection. Registers that are protected cannot be written to. Register protection is
 *          disabled by using the Protect Register (PRCR) and the MPC's Write-Protect Register (PWPR).
 *
 * @param[in] regs_to_unprotect Registers which have write protection disabled.
 **********************************************************************************************************************/
void register_protect_disable(bsp_reg_protect_t regs_to_unprotect)
{
    /** Get/save the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* If this is first entry then disable protection. */
    if (0U == g_protect_counters[regs_to_unprotect])
    {
        /** Disable protection using PRCR register.
         * When writing to the PRCR register the upper 8-bits must be the correct key.
         * Set lower bits to 0 to disable writes. */
        R_RWP_NS->PRCRN = ((R_RWP_NS->PRCRN | BSP_REG_PROTECT_PRCR_KEY) | g_prcr_masks[regs_to_unprotect]);
        R_RWP_S->PRCRS  = ((R_RWP_S->PRCRS | BSP_REG_PROTECT_PRCR_KEY) | g_prcr_masks[regs_to_unprotect]);
    }

    /** Increment the protect counter */
    g_protect_counters[regs_to_unprotect]++;

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
}