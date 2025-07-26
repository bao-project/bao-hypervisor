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

/* Mode Entry Module (MC_ME) */
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

/* Reset Generation Module (MC_RGM) */
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

/* System Integration Unit (SIUL2) */
#define SIUL2_5_BASE            (0x42D20000UL)
#define SIUL2_5_TOP             (0x42D2FFFFUL)
#define SIUL2_5_SIZE            (SIUL2_5_TOP - SIUL2_5_BASE + 1)

#define SIUL2_MSCR              (SIUL2_5_BASE + 0x240UL)
#define SIUL2_MSCR_OFF(x)       (SIUL2_MSCR + ((x) * 0x4UL))
#define SIUL2_MSCR_OBE          (1UL << 21UL)
#define SIUL2_MSCR_ODE          (1UL << 20UL)
#define SIUL2_MSCR_IBE          (1UL << 19UL)
#define SIUL2_MSCR_SRE_MSK      (0x1C000UL)
#define SIUL2_MSCR_SRE(x)       (((unsigned long)(x) << 14UL) & SIUL2_MSCR_SRE_MSK)
#define SIUL2_MSCR_RCVR_MSK     (0x400UL)
#define SIUL2_MSCR_RCVR(x)      (((unsigned long)(x) << 10UL) & SIUL2_MSCR_RCVR_MSK)
#define SIUL2_MSCR_SMC_MSK      (0x20UL)
#define SIUL2_MSCR_SMC(x)       (((unsigned long)(x) << 5UL) & SIUL2_MSCR_SMC_MSK)
#define SIUL2_MSCR_SSS_MSK      (0x7UL)
#define SIUL2_MSCR_SSS(x)       (((unsigned long)(x) << 0UL) & SIUL2_MSCR_SSS_MSK)

#define SIUL2_MSCR_TX           (SIUL2_MSCR_OBE | SIUL2_MSCR_SRE(0x4) | SIUL2_MSCR_SSS(0x1))
#define SIUL2_MSCR_RX           (SIUL2_MSCR_IBE | SIUL2_MSCR_SRE(0x4))

/* Clock Generation Module */
#define MC_CGM_5_BASE           (0x42830000UL)
#define MC_CGM_5_TOP            (0x4283FFFFUL)
#define MC_CGM_5_SIZE           (MC_CGM_5_TOP - MC_CGM_5_BASE + 1)
#define MC_CGM_5_MUX_2_CSC      ((MC_CGM_5_BASE + 0x380UL))
#define MC_CGM_5_MUX_2_CSS      ((MC_CGM_5_BASE + 0x384UL))
#define MC_CGM_5_MUX_2_DC_0     ((MC_CGM_5_BASE + 0x388UL))

#define MC_CGM_5_MUX_2_CSC_SAFE (1UL << 3UL)

#define MC_CGM_5_MUX_2_CSS_SWIP (1UL << 16UL)

#define MC_CGM_5_MUX_2_DC_0_DE  (1UL << 31UL)

#endif /* __PLAT_REGS_H__ */
