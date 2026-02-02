/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

/* HACTLR: Enable EL1 access to all IMP DEF registers */
#define HACTLR_CPUACTLR              (1 << 0)
#define HACTLR_FLASHIFREGIONR        (1 << 7)
#define HACTLR_PERIPHPREGIONR        (1 << 8)
#define HACTLR_QOSR                  (1 << 9)
#define HACTLR_BUSTIMEOUTR           (1 << 10)
#define HACTLR_INTMONR               (1 << 12)
#define HACTLR_ERR                   (1 << 13)

/* IMP_PERIPHREGIONR (LLPP) */
#define PERIPHREGIONR_EL1_EL0_ENABLE (1 << 0)
#define PERIPHREGIONR_EL2_ENABLE     (1 << 1)

/* FLASHIFREGIONR */
#define FLASHIFREGIONR_ENABLE        (1 << 0)

/* IMP_CSCTLR : AXIM and Flash port cache way configuration */
#define ICACHE_FLASH_2_AXIM_2        (2 << 8)
#define DCACHE_FLASH_2_AXIM_2        (2 << 0)

/* AxCACHE PREFETCH CONTROL REGISTER */
#define PREFETCH_CTRL_AM_MSK         (3ULL)
#define PREFETCH_CTRL_PF_ENABLE      (1ULL << 11)
#define PREFETCH_CTRL_OB_OFF         (13)
#define PREFETCH_CTRL_OB_MSK         (7ULL << PREFETCH_CTRL_OB_OFF)
#define PREFETCH_CTRL_OB_5           (5ULL << PREFETCH_CTRL_OB_OFF)

static inline void e3650_enable_imp_def(void)
{
    unsigned long val;
    unsigned long long val64;

    /* Enable Prefetch */
    val64 = sysreg_imp_prefetch_ctrl_read();
    val64 &= ~PREFETCH_CTRL_AM_MSK;
    val64 &= ~PREFETCH_CTRL_OB_MSK;
    val64 |= (PREFETCH_CTRL_PF_ENABLE | PREFETCH_CTRL_OB_5);
    sysreg_imp_prefetch_ctrl_write(val64);

    /* Enable Branch Prediction */
    val = 0;
    sysreg_imp_bpctlr_write(val);
    ISB();

    /* HACTLR: Enable EL1 access to all IMP DEF registers */
    val = sysreg_hactlr_read();
    val |= (HACTLR_CPUACTLR | HACTLR_FLASHIFREGIONR | HACTLR_PERIPHPREGIONR | HACTLR_QOSR |
        HACTLR_BUSTIMEOUTR | HACTLR_INTMONR | HACTLR_ERR);
    sysreg_hactlr_write(val);

    /* Enable PERIPHREGIONR (LLPP) */
    val = sysreg_imp_periphregionr_read();
    val |= (PERIPHREGIONR_EL2_ENABLE | PERIPHREGIONR_EL1_EL0_ENABLE);
    sysreg_imp_periphregionr_write(val);

    /* Enable FLASHIFREGIONR (Flash) */
    val = sysreg_flashifregionr_read();
    val |= FLASHIFREGIONR_ENABLE;
    sysreg_flashifregionr_write(val);

    /* IMP_CSCTLR : AXIM and Flash port cache way configuration */
    val = (ICACHE_FLASH_2_AXIM_2 | DCACHE_FLASH_2_AXIM_2);
    sysreg_imp_csctlr_write(val);

    ISB();
}

void platform_default_init(void)
{
    e3650_enable_imp_def();
}
