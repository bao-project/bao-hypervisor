/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_REGS_H__
#define __PLAT_REGS_H__

#include <bao.h>

#define RTU0_CORE0                   0
#define RTU0_CORE1                   1
#define RTU0_CORE2                   2
#define RTU0_CORE3                   3

/* Mode Entry Module */
#define MC_ME_BASE                   (0x41900000UL)

#define MC_ME_CTL_KEY                (MC_ME_BASE + 0x0UL)

#define MC_ME_CTL_KEY_KEY0           (0x5AF0)
#define MC_ME_CTL_KEY_KEY1           (0xA50F)

// RTU0 - S32Z Partition1
#define MC_ME_PRTN1_CORE0_PCONF      (MC_ME_BASE + 0x340UL)
#define MC_ME_PRTN1_CORE0_PUPD       (MC_ME_BASE + 0x344UL)
#define MC_ME_PRTN1_CORE0_STAT       (MC_ME_BASE + 0x348UL)
#define MC_ME_PRTN1_CORE0_ADDR       (MC_ME_BASE + 0x34CUL)

#define MC_ME_PRTN1_COREX_OFFSET     (0x20UL)

#define MC_ME_PRTN1_COREX_STAT_CCS   (1UL << 0)
#define MC_ME_PRTN1_COREX_PCONF_CCE  (1UL << 0)
#define MC_ME_PRTN1_COREX_PUPD_CCUPD (1UL << 0)

#define MC_ME_PRTN1_COREX_ADDR(cpuid) \
    (MC_ME_PRTN1_CORE0_ADDR + ((cpuid) * MC_ME_PRTN1_COREX_OFFSET))

#define MC_ME_PRTN1_COREX_STAT(cpuid) \
    (MC_ME_PRTN1_CORE0_STAT + ((cpuid) * MC_ME_PRTN1_COREX_OFFSET))

#define MC_ME_PRTN1_COREX_PCONF(cpuid) \
    (MC_ME_PRTN1_CORE0_PCONF + ((cpuid) * MC_ME_PRTN1_COREX_OFFSET))

#define MC_ME_PRTN1_COREX_PUPD(cpuid) \
    (MC_ME_PRTN1_CORE0_PUPD + ((cpuid) * MC_ME_PRTN1_COREX_OFFSET))

/* Reset Generation Module */
#define MC_RGM_BASE          (0x41850000UL)

// RTU0 - S32Z Partition1
#define MC_RGM_PRST1_0       (MC_RGM_BASE + 0x48UL)
#define MC_RGM_PSTAT1_0      (MC_RGM_BASE + 0x148UL)

#define MC_RGM_PRST1_O_CORE1 (0xFFFFFFFBUL)
#define MC_RGM_PRST1_O_CORE2 (0xFFFFFFF7UL)
#define MC_RGM_PRST1_O_CORE3 (0xFFFFFFEFUL)

#define MC_RGM_PRST1_0_VAL(cpuid)                          \
    ((cpuid) == RTU0_CORE1        ? MC_RGM_PRST1_O_CORE1 : \
            (cpuid) == RTU0_CORE2 ? MC_RGM_PRST1_O_CORE2 : \
            (cpuid) == RTU0_CORE3 ? MC_RGM_PRST1_O_CORE3 : \
                                    mmio32_read(MC_RGM_PRST1_0))

#endif /* __PLAT_REGS_H__ */
