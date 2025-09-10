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
    uint8_t RESERVED_12[256];
    uint8_t GPDO3;
    uint8_t GPDO2;
    uint8_t GPDO1;
    uint8_t GPDO0;
    uint8_t GPDO7;
    uint8_t GPDO6;
    uint8_t GPDO5;
    uint8_t GPDO4;
    uint8_t GPDO11;
    uint8_t GPDO10;
    uint8_t GPDO9;
    uint8_t GPDO8;
    uint8_t GPDO15;
    uint8_t GPDO14;
    uint8_t GPDO13;
    uint8_t GPDO12;
    uint8_t GPDO19;
    uint8_t GPDO18;
    uint8_t GPDO17;
    uint8_t GPDO16;
    uint8_t GPDO23;
    uint8_t GPDO22;
    uint8_t GPDO21;
    uint8_t GPDO20;
    uint8_t GPDO27;
    uint8_t GPDO26;
    uint8_t GPDO25;
    uint8_t GPDO24;
    uint8_t GPDO31;
    uint8_t GPDO30;
    uint8_t GPDO29;
    uint8_t GPDO28;
    uint8_t GPDO35;
    uint8_t GPDO34;
    uint8_t GPDO33;
    uint8_t GPDO32;
    uint8_t GPDO39;
    uint8_t GPDO38;
    uint8_t GPDO37;
    uint8_t GPDO36;
    uint8_t GPDO43;
    uint8_t GPDO42;
    uint8_t GPDO41;
    uint8_t GPDO40;
    uint8_t GPDO47;
    uint8_t GPDO46;
    uint8_t GPDO45;
    uint8_t GPDO44;
    uint8_t GPDO51;
    uint8_t GPDO50;
    uint8_t GPDO49;
    uint8_t GPDO48;
    uint8_t GPDO55;
    uint8_t GPDO54;
    uint8_t GPDO53;
    uint8_t GPDO52;
    uint8_t GPDO59;
    uint8_t GPDO58;
    uint8_t GPDO57;
    uint8_t GPDO56;
    uint8_t GPDO63;
    uint8_t GPDO62;
    uint8_t GPDO61;
    uint8_t GPDO60;
    uint8_t GPDO67;
    uint8_t GPDO66;
    uint8_t GPDO65;
    uint8_t GPDO64;
    uint8_t GPDO71;
    uint8_t GPDO70;
    uint8_t GPDO69;
    uint8_t GPDO68;
    uint8_t GPDO75;
    uint8_t GPDO74;
    uint8_t GPDO73;
    uint8_t GPDO72;
    uint8_t GPDO79;
    uint8_t GPDO78;
    uint8_t GPDO77;
    uint8_t GPDO76;
    uint8_t GPDO83;
    uint8_t GPDO82;
    uint8_t GPDO81;
    uint8_t GPDO80;
    uint8_t GPDO87;
    uint8_t GPDO86;
    uint8_t GPDO85;
    uint8_t GPDO84;
    uint8_t GPDO91;
    uint8_t GPDO90;
    uint8_t GPDO89;
    uint8_t GPDO88;
    uint8_t GPDO95;
    uint8_t GPDO94;
    uint8_t GPDO93;
    uint8_t GPDO92;
    uint8_t GPDO99;
    uint8_t GPDO98;
    uint8_t GPDO97;
    uint8_t GPDO96;
    uint8_t GPDO103;
    uint8_t GPDO102;
    uint8_t GPDO101;
    uint8_t GPDO100;
    uint8_t GPDO107;
    uint8_t GPDO106;
    uint8_t GPDO105;
    uint8_t GPDO104;
    uint8_t GPDO111;
    uint8_t GPDO110;
    uint8_t GPDO109;
    uint8_t GPDO108;
    uint8_t GPDO115;
    uint8_t GPDO114;
    uint8_t GPDO113;
    uint8_t GPDO112;
    uint8_t GPDO119;
    uint8_t GPDO118;
    uint8_t GPDO117;
    uint8_t GPDO116;
    uint8_t GPDO123;
    uint8_t GPDO122;
    uint8_t GPDO121;
    uint8_t GPDO120;
    uint8_t GPDO127;
    uint8_t GPDO126;
    uint8_t GPDO125;
    uint8_t GPDO124;
    uint8_t GPDO131;
    uint8_t GPDO130;
    uint8_t GPDO129;
    uint8_t GPDO128;
    uint8_t GPDO135;
    uint8_t GPDO134;
    uint8_t GPDO133;
    uint8_t GPDO132;
    uint8_t GPDO139;
    uint8_t GPDO138;
    uint8_t GPDO137;
    uint8_t GPDO136;
    uint8_t GPDO143;
    uint8_t GPDO142;
    uint8_t GPDO141;
    uint8_t GPDO140;
    uint8_t GPDO147;
    uint8_t GPDO146;
    uint8_t GPDO145;
    uint8_t GPDO144;
    uint8_t GPDO151;
    uint8_t GPDO150;
    uint8_t GPDO149;
    uint8_t GPDO148;
    uint8_t GPDO155;
    uint8_t GPDO154;
    uint8_t GPDO153;
    uint8_t GPDO152;
    uint8_t GPDO159;
    uint8_t GPDO158;
    uint8_t GPDO157;
    uint8_t GPDO156;
    uint8_t GPDO163;
    uint8_t GPDO162;
    uint8_t GPDO161;
    uint8_t GPDO160;
    uint8_t GPDO167;
    uint8_t GPDO166;
    uint8_t GPDO165;
    uint8_t GPDO164;
    uint8_t GPDO171;
    uint8_t GPDO170;
    uint8_t GPDO169;
    uint8_t GPDO168;
    uint8_t RESERVED_13[2];
    uint8_t GPDO173;
    uint8_t GPDO172;
    uint8_t RESERVED_14[336];
    uint8_t GPDI3;
    uint8_t GPDI2;
    uint8_t GPDI1;
    uint8_t GPDI0;
    uint8_t GPDI7;
    uint8_t GPDI6;
    uint8_t GPDI5;
    uint8_t GPDI4;
    uint8_t GPDI11;
    uint8_t GPDI10;
    uint8_t GPDI9;
    uint8_t GPDI8;
    uint8_t GPDI15;
    uint8_t GPDI14;
    uint8_t GPDI13;
    uint8_t GPDI12;
    uint8_t GPDI19;
    uint8_t GPDI18;
    uint8_t GPDI17;
    uint8_t GPDI16;
    uint8_t GPDI23;
    uint8_t GPDI22;
    uint8_t GPDI21;
    uint8_t GPDI20;
    uint8_t GPDI27;
    uint8_t GPDI26;
    uint8_t GPDI25;
    uint8_t GPDI24;
    uint8_t GPDI31;
    uint8_t GPDI30;
    uint8_t GPDI29;
    uint8_t GPDI28;
    uint8_t GPDI35;
    uint8_t GPDI34;
    uint8_t GPDI33;
    uint8_t GPDI32;
    uint8_t GPDI39;
    uint8_t GPDI38;
    uint8_t GPDI37;
    uint8_t GPDI36;
    uint8_t GPDI43;
    uint8_t GPDI42;
    uint8_t GPDI41;
    uint8_t GPDI40;
    uint8_t GPDI47;
    uint8_t GPDI46;
    uint8_t GPDI45;
    uint8_t GPDI44;
    uint8_t GPDI51;
    uint8_t GPDI50;
    uint8_t GPDI49;
    uint8_t GPDI48;
    uint8_t GPDI55;
    uint8_t GPDI54;
    uint8_t GPDI53;
    uint8_t GPDI52;
    uint8_t GPDI59;
    uint8_t GPDI58;
    uint8_t GPDI57;
    uint8_t GPDI56;
    uint8_t GPDI63;
    uint8_t GPDI62;
    uint8_t GPDI61;
    uint8_t GPDI60;
    uint8_t GPDI67;
    uint8_t GPDI66;
    uint8_t GPDI65;
    uint8_t GPDI64;
    uint8_t GPDI71;
    uint8_t GPDI70;
    uint8_t GPDI69;
    uint8_t GPDI68;
    uint8_t GPDI75;
    uint8_t GPDI74;
    uint8_t GPDI73;
    uint8_t GPDI72;
    uint8_t GPDI79;
    uint8_t GPDI78;
    uint8_t GPDI77;
    uint8_t GPDI76;
    uint8_t GPDI83;
    uint8_t GPDI82;
    uint8_t GPDI81;
    uint8_t GPDI80;
    uint8_t GPDI87;
    uint8_t GPDI86;
    uint8_t GPDI85;
    uint8_t GPDI84;
    uint8_t GPDI91;
    uint8_t GPDI90;
    uint8_t GPDI89;
    uint8_t GPDI88;
    uint8_t GPDI95;
    uint8_t GPDI94;
    uint8_t GPDI93;
    uint8_t GPDI92;
    uint8_t GPDI99;
    uint8_t GPDI98;
    uint8_t GPDI97;
    uint8_t GPDI96;
    uint8_t GPDI103;
    uint8_t GPDI102;
    uint8_t GPDI101;
    uint8_t GPDI100;
    uint8_t GPDI107;
    uint8_t GPDI106;
    uint8_t GPDI105;
    uint8_t GPDI104;
    uint8_t GPDI111;
    uint8_t GPDI110;
    uint8_t GPDI109;
    uint8_t GPDI108;
    uint8_t GPDI115;
    uint8_t GPDI114;
    uint8_t GPDI113;
    uint8_t GPDI112;
    uint8_t GPDI119;
    uint8_t GPDI118;
    uint8_t GPDI117;
    uint8_t GPDI116;
    uint8_t GPDI123;
    uint8_t GPDI122;
    uint8_t GPDI121;
    uint8_t GPDI120;
    uint8_t GPDI127;
    uint8_t GPDI126;
    uint8_t GPDI125;
    uint8_t GPDI124;
    uint8_t GPDI131;
    uint8_t GPDI130;
    uint8_t GPDI129;
    uint8_t GPDI128;
    uint8_t GPDI135;
    uint8_t GPDI134;
    uint8_t GPDI133;
    uint8_t GPDI132;
    uint8_t GPDI139;
    uint8_t GPDI138;
    uint8_t GPDI137;
    uint8_t GPDI136;
    uint8_t GPDI143;
    uint8_t GPDI142;
    uint8_t GPDI141;
    uint8_t GPDI140;
    uint8_t GPDI147;
    uint8_t GPDI146;
    uint8_t GPDI145;
    uint8_t GPDI144;
    uint8_t GPDI151;
    uint8_t GPDI150;
    uint8_t GPDI149;
    uint8_t GPDI148;
    uint8_t GPDI155;
    uint8_t GPDI154;
    uint8_t GPDI153;
    uint8_t GPDI152;
    uint8_t GPDI159;
    uint8_t GPDI158;
    uint8_t GPDI157;
    uint8_t GPDI156;
    uint8_t GPDI163;
    uint8_t GPDI162;
    uint8_t GPDI161;
    uint8_t GPDI160;
    uint8_t GPDI167;
    uint8_t GPDI166;
    uint8_t GPDI165;
    uint8_t GPDI164;
    uint8_t GPDI171;
    uint8_t GPDI170;
    uint8_t GPDI169;
    uint8_t GPDI168;
    uint8_t RESERVED_15[2];
    uint8_t GPDI173;
    uint8_t GPDI172;
    uint8_t RESERVED_16[336];
    uint16_t PGPDO1;
    uint16_t PGPDO0;
    uint16_t PGPDO3;
    uint16_t PGPDO2;
    uint16_t PGPDO5;
    uint16_t PGPDO4;
    uint16_t PGPDO7;
    uint16_t PGPDO6;
    uint16_t PGPDO9;
    uint16_t PGPDO8;
    uint8_t RESERVED_17[2];
    uint16_t PGPDO10;
    uint8_t RESERVED_18[40];
    uint16_t PGPDI1;
    uint16_t PGPDI0;
    uint16_t PGPDI3;
    uint16_t PGPDI2;
    uint16_t PGPDI5;
    uint16_t PGPDI4;
    uint16_t PGPDI7;
    uint16_t PGPDI6;
    uint16_t PGPDI9;
    uint16_t PGPDI8;
    uint8_t RESERVED_19[2];
    uint16_t PGPDI10;
    uint8_t RESERVED_20[40];
    uint32_t MPGPDO[11];
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
