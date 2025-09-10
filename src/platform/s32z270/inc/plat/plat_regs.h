/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_REGS_H__
#define __PLAT_REGS_H__

#include <bao.h>

#define RTU0_CORE0 0
#define RTU0_CORE1 1
#define RTU0_CORE2 2
#define RTU0_CORE3 3

/* Mode Entry Module (MC_ME) */
#define MC_ME_BASE (0x41900000UL)

struct mc_me_hw {
    uint32_t CTL_KEY;
    uint32_t MODE_CONF;
    uint32_t MODE_UPD;
    uint8_t RESERVED_0[244];
    uint32_t PRTN0_PCONF;
    uint32_t PRTN0_PUPD;
    uint32_t PRTN0_STAT;
    uint8_t RESERVED_1[52];
    struct {
        uint32_t PCONF;
        uint32_t PUPD;
        uint32_t STAT;
        uint32_t ADDR;
        uint8_t RESERVED_2[16];
    } PRTN0_COREX[8];
    uint8_t RESERVED_3[208 - 16];
    uint32_t PRTN1_PCONF;
    uint32_t PRTN1_PUPD;
    uint32_t PRTN1_STAT;
    uint8_t RESERVED_4[52];
    struct {
        uint32_t PCONF;
        uint32_t PUPD;
        uint32_t STAT;
        uint32_t ADDR;
        uint8_t RESERVED_5[16];
    } PRTN1_COREX[4];
    uint8_t RESERVED_14[336 - 16];
    uint32_t PRTN2_PCONF;
    uint32_t PRTN2_PUPD;
    uint32_t PRTN2_STAT;
    uint8_t RESERVED_6[52];
    struct {
        uint32_t PCONF;
        uint32_t PUPD;
        uint32_t STAT;
        uint32_t ADDR;
        uint8_t RESERVED_7[16];
    } PRTN2_COREX[3];
    uint32_t PRTN2_CORE3_PCONF;
    uint32_t PRTN2_CORE3_PUPD;
    uint32_t PRTN2_CORE3_STAT;
    uint32_t PRTN2_CORE3_ADDR;
};

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
#define MC_RGM_BASE (0x41850000UL)

struct mc_rgm_hw {
    uint32_t DES;
    uint8_t RESERVED_0[4];
    uint32_t FES;
    uint32_t FERD;
    uint32_t FBRE;
    uint32_t FREC;
    uint32_t FRET;
    uint32_t DRET;
    uint32_t ERCTRL;
    uint8_t RESERVED_1[4];
    uint32_t FRENTC;
    uint8_t RESERVED_2[20];
    uint32_t PRST0_0;
    uint8_t RESERVED_3[4];
    uint32_t PRST1_0;
    uint8_t RESERVED_4[4];
    uint32_t PRST2_0;
    uint8_t RESERVED_5[236];
    uint32_t PSTAT0_0;
    uint8_t RESERVED_6[4];
    uint32_t PSTAT1_0;
    uint8_t RESERVED_7[4];
    uint32_t PSTAT2_0;
};

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
                                    0xFFFFFFFFUL)

/* System Integration Unit (SIUL2) */
#define SIUL2_5_BASE (0x42D20000UL)
#define SIUL2_5_TOP  (0x42D2FFFFUL)
#define SIUL2_5_SIZE (SIUL2_5_TOP - SIUL2_5_BASE + 1)

struct siul2_hw {
    uint8_t RESERVED_0[4];
    uint32_t MIDR1;
    uint32_t MIDR2;
    uint8_t RESERVED_1[4];
    uint32_t DISR0;
    uint8_t RESERVED_2[4];
    uint32_t DIRER0;
    uint8_t RESERVED_3[4];
    uint32_t DIRSR0;
    uint8_t RESERVED_4[4];
    uint32_t IREER0;
    uint8_t RESERVED_5[4];
    uint32_t IFEER0;
    uint8_t RESERVED_6[4];
    uint32_t IFER0;
    uint8_t RESERVED_7[4];
    uint32_t IFMCR[20];
    uint8_t RESERVED_8[48];
    uint32_t IFCPR;
    uint8_t RESERVED_9[316];
    uint32_t MIDR3;
    uint32_t MIDR4;
    uint8_t RESERVED_10[56];
    uint32_t MSCR[504];
    uint8_t RESERVED_11[32];
    uint32_t IMCR[496];
    /* SIUL2 has more registers, but we only define those we need for IO muxing */
};

#define SIUL2_MSCR          (SIUL2_5_BASE + 0x240UL)
#define SIUL2_MSCR_OFF(x)   (SIUL2_MSCR + ((x) * 0x4UL))
#define SIUL2_MSCR_OBE      (1UL << 21UL)
#define SIUL2_MSCR_ODE      (1UL << 20UL)
#define SIUL2_MSCR_IBE      (1UL << 19UL)
#define SIUL2_MSCR_SRE_MSK  (0x1C000UL)
#define SIUL2_MSCR_SRE(x)   (((unsigned long)(x) << 14UL) & SIUL2_MSCR_SRE_MSK)
#define SIUL2_MSCR_RCVR_MSK (0x400UL)
#define SIUL2_MSCR_RCVR(x)  (((unsigned long)(x) << 10UL) & SIUL2_MSCR_RCVR_MSK)
#define SIUL2_MSCR_SMC_MSK  (0x20UL)
#define SIUL2_MSCR_SMC(x)   (((unsigned long)(x) << 5UL) & SIUL2_MSCR_SMC_MSK)
#define SIUL2_MSCR_SSS_MSK  (0x7UL)
#define SIUL2_MSCR_SSS(x)   (((unsigned long)(x) << 0UL) & SIUL2_MSCR_SSS_MSK)

#define SIUL2_MSCR_TX       (SIUL2_MSCR_OBE | SIUL2_MSCR_SRE(0x4) | SIUL2_MSCR_SSS(0x1))
#define SIUL2_MSCR_RX       (SIUL2_MSCR_IBE | SIUL2_MSCR_SRE(0x4))

#define SIUL2_IMCR          (SIUL2_5_BASE + 0x1144UL)
#define SIUL2_IMCR_OFF(x)   (SIUL2_IMCR + ((x) * 0x4UL))
#define SIUL2_IMCR_SSS_MSK  (0x7UL)
#define SIUL2_IMCR_SSS(x)   (((unsigned long)(x) << 0UL) & SIUL2_IMCR_SSS_MSK)

#define SIUL2_IMCR_ALT2     (0x2UL)
#define SIUL2_IMCR_RX       (SIUL2_IMCR_SSS(SIUL2_IMCR_ALT2))

/* Clock Generation Module */
#define MC_CGM_5_BASE       (0x42830000UL)
#define MC_CGM_5_TOP        (0x4283FFFFUL)
#define MC_CGM_5_SIZE       (MC_CGM_5_TOP - MC_CGM_5_BASE + 1)

struct mc_cgm_hw {
    uint32_t PCFS_SDUR;
    uint8_t RESERVED_0[132];
    uint32_t PCFS_DIVC12;
    uint32_t PCFS_DIVE12;
    uint32_t PCFS_DIVS12;
    uint8_t RESERVED_1[24];
    uint32_t PCFS_DIVC15;
    uint32_t PCFS_DIVE15;
    uint32_t PCFS_DIVS15;
    uint8_t RESERVED_2[288];
    uint32_t PCFS_DIVC40;
    uint32_t PCFS_DIVE40;
    uint32_t PCFS_DIVS40;
    uint8_t RESERVED_3[284];
    uint32_t MUX_0_CSC;
    uint32_t MUX_0_CSS;
    uint32_t MUX_0_DC_0;
    uint32_t MUX_0_DC_1;
    uint8_t RESERVED_4[44];
    uint32_t MUX_0_DIV_UPD_STAT;
    uint32_t MUX_1_CSC;
    uint32_t MUX_1_CSS;
    uint32_t MUX_1_DC_0;
    uint32_t MUX_1_DC_1;
    uint8_t RESERVED_5[44];
    uint32_t MUX_1_DIV_UPD_STAT;
    uint32_t MUX_2_CSC;
    uint32_t MUX_2_CSS;
    uint32_t MUX_2_DC_0;
    uint32_t MUX_2_DC_1;
    uint32_t MUX_2_DC_2;
    uint32_t MUX_2_DC_3;
    uint32_t MUX_2_DC_4;
    uint32_t MUX_2_DC_5;
    uint8_t RESERVED_6[28];
    uint32_t MUX_2_DIV_UPD_STAT;
    uint32_t MUX_3_CSC;
    uint32_t MUX_3_CSS;
    uint32_t MUX_3_DC_0;
    uint32_t MUX_3_DC_1;
    uint32_t MUX_3_DC_2;
    uint32_t MUX_3_DC_3;
    uint32_t MUX_3_DC_4;
    uint32_t MUX_3_DC_5;
    uint32_t MUX_3_DC_6;
    uint32_t MUX_3_DC_7;
    uint8_t RESERVED_7[20];
    uint32_t MUX_3_DIV_UPD_STAT;
    uint32_t MUX_4_CSC;
    uint32_t MUX_4_CSS;
    uint32_t MUX_4_DC_0;
    uint8_t RESERVED_8[48];
    uint32_t MUX_4_DIV_UPD_STAT;
    uint32_t MUX_5_CSC;
    uint32_t MUX_5_CSS;
    uint32_t MUX_5_DC_0;
    uint32_t MUX_5_DC_1;
    uint32_t MUX_5_DC_2;
    uint8_t RESERVED_9[40];
    uint32_t MUX_5_DIV_UPD_STAT;
    uint32_t MUX_6_CSC;
    uint32_t MUX_6_CSS;
    uint32_t MUX_6_DC_0;
    uint32_t MUX_6_DC_1;
    uint8_t RESERVED_10[44];
    uint32_t MUX_6_DIV_UPD_STAT;
    uint32_t MUX_7_CSC;
    uint32_t MUX_7_CSS;
    uint32_t MUX_7_DC_0;
    uint32_t MUX_7_DC_1;
    uint32_t MUX_7_DC_2;
    uint8_t RESERVED_11[32];
    uint32_t MUX_7_DIV_TRIG_CTRL;
    uint32_t MUX_7_DIV_TRIG;
    uint32_t MUX_7_DIV_UPD_STAT;
    uint32_t MUX_8_CSC;
    uint32_t MUX_8_CSS;
    uint32_t MUX_8_DC_0;
    uint32_t MUX_8_DC_1;
    uint8_t RESERVED_12[44];
    uint32_t MUX_8_DIV_UPD_STAT;
    uint32_t MUX_9_CSC;
    uint32_t MUX_9_CSS;
    uint32_t MUX_9_DC_0;
    uint32_t MUX_9_DC_1;
    uint32_t MUX_9_DC_2;
    uint8_t RESERVED_13[40];
    uint32_t MUX_9_DIV_UPD_STAT;
    uint32_t MUX_10_CSC;
    uint32_t MUX_10_CSS;
    uint32_t MUX_10_DC_0;
    uint8_t RESERVED_14[48];
    uint32_t MUX_10_DIV_UPD_STAT;
    uint32_t MUX_11_CSC;
    uint32_t MUX_11_CSS;
    uint32_t MUX_11_DC_0;
    uint8_t RESERVED_15[48];
    uint32_t MUX_11_DIV_UPD_STAT;
    uint32_t MUX_12_CSC;
    uint32_t MUX_12_CSS;
    uint32_t MUX_12_DC_0;
    uint8_t RESERVED_16[48];
    uint32_t MUX_12_DIV_UPD_STAT;
    uint32_t MUX_13_CSC;
    uint32_t MUX_13_CSS;
    uint8_t RESERVED_17[56];
    uint32_t MUX_14_CSC;
    uint32_t MUX_14_CSS;
    uint32_t MUX_14_DC_0;
    uint8_t RESERVED_18[48];
    uint32_t MUX_14_DIV_UPD_STAT;
};

#define MC_CGM_5_MUX_2_CSC      (MC_CGM_5_BASE + 0x380UL)
#define MC_CGM_5_MUX_2_CSS      (MC_CGM_5_BASE + 0x384UL)
#define MC_CGM_5_MUX_2_DC_0     (MC_CGM_5_BASE + 0x388UL)

#define MC_CGM_5_MUX_2_CSC_SAFE (1UL << 3UL)

#define MC_CGM_5_MUX_2_CSS_SWIP (1UL << 16UL)

#define MC_CGM_5_MUX_2_DC_0_DE  (1UL << 31UL)

#endif /* __PLAT_REGS_H__ */
