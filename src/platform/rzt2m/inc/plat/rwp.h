/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_RWP_H__
#define __PLAT_RWP_H__


/* Key code for writing PRCR register. */
#define BSP_REG_PROTECT_PRCR_KEY          (0xA500U)

/** The different types of registers that can be protected. */
typedef enum e_bsp_reg_protect
{
    /** Enables writing to the registers related to the clock generation circuit. */
    BSP_REG_PROTECT_CGC = 0,

    /** Enables writing to the registers related to low power consumption and reset. */
    BSP_REG_PROTECT_LPC_RESET,

    /** Enables writing to the registers related to GPIO. */
    BSP_REG_PROTECT_GPIO,

    /** Enables writing to the registers related to Non-Safety reg. */
    BSP_REG_PROTECT_SYSTEM,
} bsp_reg_protect_t;

void register_protect_enable(bsp_reg_protect_t regs_to_protect);
void register_protect_disable(bsp_reg_protect_t regs_to_unprotect);

#endif /* __PLAT_RWP_H__ */