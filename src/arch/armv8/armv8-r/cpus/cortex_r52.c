/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/sysregs.h>
#include <arch/fences.h>

/* HACTLR: Enable EL1 access to IMP DEF registers */
#define HACTLR_PERIPHPREGIONR        (1 << 8)
#define HACTLR_QOSR                  (1 << 9)
#define HACTLR_ERR                   (1 << 13)

/* IMP_PERIPHREGIONR (LLPP) */
#define PERIPHREGIONR_EL1_EL0_ENABLE (1 << 0)
#define PERIPHREGIONR_EL2_ENABLE     (1 << 1)

/* FLASHIFREGIONR */
#define FLASHIFREGIONR_ENABLE        (1 << 0)

void cortex_r52_impl_init(void);

static void cortex_r52_enable_hactlr(void)
{
    unsigned long val = sysreg_hactlr_read();
    val |= (HACTLR_PERIPHPREGIONR | HACTLR_QOSR | HACTLR_ERR);
    sysreg_hactlr_write(val);
}

static void cortex_r52_enable_llpp(void)
{
    unsigned long val = sysreg_imp_periphregionr_read();
    val |= (PERIPHREGIONR_EL2_ENABLE | PERIPHREGIONR_EL1_EL0_ENABLE);
    sysreg_imp_periphregionr_write(val);
}

static void cortex_r52_enable_flash_region(void)
{
    unsigned long val = sysreg_flashifregionr_read();
    val |= FLASHIFREGIONR_ENABLE;
    sysreg_flashifregionr_write(val);
}

void cortex_r52_impl_init(void)
{
    cortex_r52_enable_hactlr();

    cortex_r52_enable_llpp();

    cortex_r52_enable_flash_region();

    ISB();
}
