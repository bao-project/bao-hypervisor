/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CSFR_H__
#define __ARCH_CSFR_H__

#include <bao.h>

#define CSFR_DCON1    0x9008
#define CSFR_PCON1    0x9204
#define CSFR_PCON0    0x920C
#define CSFR_DCON0    0x9040
#define CSFR_CORECON  0xFE14
#define CSFR_TCCON    0xFE6C
#define CSFR_COREID   0xFE38

#define CSFR_CPXE_0   0xE000
#define CSFR_CPXE_1   0xE004
#define CSFR_CPXE_2   0xE008
#define CSFR_CPXE_3   0xE00C
#define CSFR_DPRE_0   0xE010
#define CSFR_DPRE_1   0xE014
#define CSFR_DPRE_2   0xE018
#define CSFR_DPRE_3   0xE01C
#define CSFR_DPWE_0   0xE020
#define CSFR_DPWE_1   0xE024
#define CSFR_DPWE_2   0xE028
#define CSFR_DPWE_3   0xE02C

#define CSFR_CPXE_4   0xE040
#define CSFR_CPXE_5   0xE044
#define CSFR_CPXE_6   0xE048
#define CSFR_CPXE_7   0xE04C
#define CSFR_DPRE_4   0xE050
#define CSFR_DPRE_5   0xE054
#define CSFR_DPRE_6   0xE058
#define CSFR_DPRE_7   0xE05C
#define CSFR_DPWE_4   0xE060
#define CSFR_DPWE_5   0xE064
#define CSFR_DPWE_6   0xE068
#define CSFR_DPWE_7   0xE06C

#define CSFR_DPR0_L   0xC000
#define CSFR_DPR0_U   0xC004
#define CSFR_DPR1_L   0xC008
#define CSFR_DPR1_U   0xC00C
#define CSFR_DPR2_L   0xC010
#define CSFR_DPR2_U   0xC014
#define CSFR_DPR3_L   0xC018
#define CSFR_DPR3_U   0xC01C
#define CSFR_DPR4_L   0xC020
#define CSFR_DPR4_U   0xC024
#define CSFR_DPR5_L   0xC028
#define CSFR_DPR5_U   0xC02C
#define CSFR_DPR6_L   0xC030
#define CSFR_DPR6_U   0xC034
#define CSFR_DPR7_L   0xC038
#define CSFR_DPR7_U   0xC03C
#define CSFR_DPR8_L   0xC040
#define CSFR_DPR8_U   0xC044
#define CSFR_DPR9_L   0xC048
#define CSFR_DPR9_U   0xC04C
#define CSFR_DPR10_L  0xC050
#define CSFR_DPR10_U  0xC054
#define CSFR_DPR11_L  0xC058
#define CSFR_DPR11_U  0xC05C
#define CSFR_DPR12_L  0xC060
#define CSFR_DPR12_U  0xC064
#define CSFR_DPR13_L  0xC068
#define CSFR_DPR13_U  0xC06C
#define CSFR_DPR14_L  0xC070
#define CSFR_DPR14_U  0xC074
#define CSFR_DPR15_L  0xC078
#define CSFR_DPR15_U  0xC07C
#define CSFR_DPR16_L  0xC080
#define CSFR_DPR16_U  0xC084
#define CSFR_DPR17_L  0xC088
#define CSFR_DPR17_U  0xC08C
#define CSFR_DPR18_L  0xC090
#define CSFR_DPR18_U  0xC094
#define CSFR_DPR19_L  0xC098
#define CSFR_DPR19_U  0xC09C
#define CSFR_DPR20_L  0xC0A0
#define CSFR_DPR20_U  0xC0A4
#define CSFR_DPR21_L  0xC0A8
#define CSFR_DPR21_U  0xC0AC
#define CSFR_DPR22_L  0xC0B0
#define CSFR_DPR22_U  0xC0B4
#define CSFR_DPR23_L  0xC0B8
#define CSFR_DPR23_U  0xC0BC
#define CSFR_DPR24_L  0xC0C0
#define CSFR_DPR24_U  0xC0C4
#define CSFR_DPR25_L  0xC0C8
#define CSFR_DPR25_U  0xC0CC
#define CSFR_DPR26_L  0xC0D0
#define CSFR_DPR26_U  0xC0D4
#define CSFR_DPR27_L  0xC0D8
#define CSFR_DPR27_U  0xC0DC
#define CSFR_DPR28_L  0xC0E0
#define CSFR_DPR28_U  0xC0E4
#define CSFR_DPR29_L  0xC0E8
#define CSFR_DPR29_U  0xC0EC
#define CSFR_DPR30_L  0xC0F0
#define CSFR_DPR30_U  0xC0F4
#define CSFR_DPR31_L  0xC0F8
#define CSFR_DPR31_U  0xC0FC

#define CSFR_CPR0_L   0xD000
#define CSFR_CPR0_U   0xD004
#define CSFR_CPR1_L   0xD008
#define CSFR_CPR1_U   0xD00C
#define CSFR_CPR2_L   0xD010
#define CSFR_CPR2_U   0xD014
#define CSFR_CPR3_L   0xD018
#define CSFR_CPR3_U   0xD01C
#define CSFR_CPR4_L   0xD020
#define CSFR_CPR4_U   0xD024
#define CSFR_CPR5_L   0xD028
#define CSFR_CPR5_U   0xD02C
#define CSFR_CPR6_L   0xD030
#define CSFR_CPR6_U   0xD034
#define CSFR_CPR7_L   0xD038
#define CSFR_CPR7_U   0xD03C
#define CSFR_CPR8_L   0xD040
#define CSFR_CPR8_U   0xD044
#define CSFR_CPR9_L   0xD048
#define CSFR_CPR9_U   0xD04C
#define CSFR_CPR10_L  0xD050
#define CSFR_CPR10_U  0xD054
#define CSFR_CPR11_L  0xD058
#define CSFR_CPR11_U  0xD05C
#define CSFR_CPR12_L  0xD060
#define CSFR_CPR12_U  0xD064
#define CSFR_CPR13_L  0xD068
#define CSFR_CPR13_U  0xD06C
#define CSFR_CPR14_L  0xD070
#define CSFR_CPR14_U  0xD074
#define CSFR_CPR15_L  0xD078
#define CSFR_CPR15_U  0xD07C
#define CSFR_CPR16_L  0xD080
#define CSFR_CPR16_U  0xD084
#define CSFR_CPR17_L  0xD088
#define CSFR_CPR17_U  0xD08C
#define CSFR_CPR18_L  0xD090
#define CSFR_CPR18_U  0xD094
#define CSFR_CPR19_L  0xD098
#define CSFR_CPR19_U  0xD09C
#define CSFR_CPR20_L  0xD0A0
#define CSFR_CPR20_U  0xD0A4
#define CSFR_CPR21_L  0xD0A8
#define CSFR_CPR21_U  0xD0AC
#define CSFR_CPR22_L  0xD0B0
#define CSFR_CPR22_U  0xD0B4
#define CSFR_CPR23_L  0xD0B8
#define CSFR_CPR23_U  0xD0BC
#define CSFR_CPR24_L  0xD0C0
#define CSFR_CPR24_U  0xD0C4
#define CSFR_CPR25_L  0xD0C8
#define CSFR_CPR25_U  0xD0CC
#define CSFR_CPR26_L  0xD0D0
#define CSFR_CPR26_U  0xD0D4
#define CSFR_CPR27_L  0xD0D8
#define CSFR_CPR27_U  0xD0DC
#define CSFR_CPR28_L  0xD0E0
#define CSFR_CPR28_U  0xD0E4
#define CSFR_CPR29_L  0xD0E8
#define CSFR_CPR29_U  0xD0EC
#define CSFR_CPR30_L  0xD0F0
#define CSFR_CPR30_U  0xD0F4
#define CSFR_CPR31_L  0xD0F8
#define CSFR_CPR31_U  0xD0FC

#define CSFR_FCX      0xFE38
#define CSFR_LCX      0xFE3C
#define CSFR_PCXI     0xFE00
#define CSFR_BHV      0xB010
#define CSFR_VCON2    0xB008
#define CSFR_CORECON  0xFE14
#define CSFR_PCX      0xFE00

#define CSFR_DSTR     0x9010
#define CSFR_DATR     0x9018
#define CSFR_DEADD    0x901C

#define CSFR_VM0_ICR  0xB100
#define CSFR_VM1_ICR  0xB104
#define CSFR_VM2_ICR  0xB108
#define CSFR_VM3_ICR  0xB10C
#define CSFR_VM4_ICR  0xB110
#define CSFR_VM5_ICR  0xB114
#define CSFR_VM6_ICR  0xB118
#define CSFR_VM7_ICR  0xB11C

#define CSFR_BASE     0xF8830000
#define CSFR_BOOTCON  0xFE60
#define CSFR_PC       0xFE08

#define CSFR_HVHRA_A0 0xFF81
#define CSFR_HVHRA_A1 0xFF85
#define CSFR_HVHRA_A8 0xFFA1
#define CSFR_HVHRA_A9 0xFFA5

#ifndef __ASSEMBLER__

#define CSFRS_GEN_ACCESSORS_NAMED(csfr_name, csfr_id)                                \
    static inline unsigned long csfr_##csfr_name##_read(void)                        \
    {                                                                                \
        unsigned long csfr_value;                                                    \
        __asm__ volatile("mfcr %0, " XSTR(csfr_id) : "=r"(csfr_value)::"memory");    \
        return csfr_value;                                                           \
    }                                                                                \
    static inline void csfr_##csfr_name##_write(unsigned long csfr_value)            \
    {                                                                                \
        __asm__ volatile("mtcr " XSTR(csfr_id) ", %0" ::"r"(csfr_value) : "memory"); \
    }

CSFRS_GEN_ACCESSORS_NAMED(tccon, CSFR_TCCON)

CSFRS_GEN_ACCESSORS_NAMED(dpr0_l, CSFR_DPR0_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr1_l, CSFR_DPR1_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr2_l, CSFR_DPR2_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr3_l, CSFR_DPR3_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr4_l, CSFR_DPR4_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr5_l, CSFR_DPR5_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr6_l, CSFR_DPR6_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr7_l, CSFR_DPR7_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr8_l, CSFR_DPR8_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr9_l, CSFR_DPR9_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr10_l, CSFR_DPR10_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr11_l, CSFR_DPR11_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr12_l, CSFR_DPR12_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr13_l, CSFR_DPR13_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr14_l, CSFR_DPR14_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr15_l, CSFR_DPR15_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr16_l, CSFR_DPR16_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr17_l, CSFR_DPR17_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr18_l, CSFR_DPR18_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr19_l, CSFR_DPR19_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr20_l, CSFR_DPR20_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr21_l, CSFR_DPR21_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr22_l, CSFR_DPR22_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr23_l, CSFR_DPR23_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr24_l, CSFR_DPR24_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr25_l, CSFR_DPR25_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr26_l, CSFR_DPR26_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr27_l, CSFR_DPR27_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr28_l, CSFR_DPR28_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr29_l, CSFR_DPR29_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr30_l, CSFR_DPR30_L)
CSFRS_GEN_ACCESSORS_NAMED(dpr31_l, CSFR_DPR31_L)

CSFRS_GEN_ACCESSORS_NAMED(dpr0_u, CSFR_DPR0_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr1_u, CSFR_DPR1_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr2_u, CSFR_DPR2_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr3_u, CSFR_DPR3_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr4_u, CSFR_DPR4_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr5_u, CSFR_DPR5_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr6_u, CSFR_DPR6_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr7_u, CSFR_DPR7_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr8_u, CSFR_DPR8_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr9_u, CSFR_DPR9_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr10_u, CSFR_DPR10_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr11_u, CSFR_DPR11_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr12_u, CSFR_DPR12_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr13_u, CSFR_DPR13_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr14_u, CSFR_DPR14_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr15_u, CSFR_DPR15_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr16_u, CSFR_DPR16_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr17_u, CSFR_DPR17_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr18_u, CSFR_DPR18_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr19_u, CSFR_DPR19_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr20_u, CSFR_DPR20_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr21_u, CSFR_DPR21_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr22_u, CSFR_DPR22_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr23_u, CSFR_DPR23_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr24_u, CSFR_DPR24_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr25_u, CSFR_DPR25_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr26_u, CSFR_DPR26_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr27_u, CSFR_DPR27_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr28_u, CSFR_DPR28_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr29_u, CSFR_DPR29_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr30_u, CSFR_DPR30_U)
CSFRS_GEN_ACCESSORS_NAMED(dpr31_u, CSFR_DPR31_U)

CSFRS_GEN_ACCESSORS_NAMED(cpr0_l, CSFR_CPR0_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr1_l, CSFR_CPR1_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr2_l, CSFR_CPR2_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr3_l, CSFR_CPR3_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr4_l, CSFR_CPR4_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr5_l, CSFR_CPR5_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr6_l, CSFR_CPR6_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr7_l, CSFR_CPR7_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr8_l, CSFR_CPR8_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr9_l, CSFR_CPR9_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr10_l, CSFR_CPR10_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr11_l, CSFR_CPR11_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr12_l, CSFR_CPR12_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr13_l, CSFR_CPR13_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr14_l, CSFR_CPR14_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr15_l, CSFR_CPR15_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr16_l, CSFR_CPR16_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr17_l, CSFR_CPR17_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr18_l, CSFR_CPR18_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr19_l, CSFR_CPR19_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr20_l, CSFR_CPR20_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr21_l, CSFR_CPR21_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr22_l, CSFR_CPR22_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr23_l, CSFR_CPR23_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr24_l, CSFR_CPR24_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr25_l, CSFR_CPR25_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr26_l, CSFR_CPR26_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr27_l, CSFR_CPR27_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr28_l, CSFR_CPR28_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr29_l, CSFR_CPR29_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr30_l, CSFR_CPR30_L)
CSFRS_GEN_ACCESSORS_NAMED(cpr31_l, CSFR_CPR31_L)

CSFRS_GEN_ACCESSORS_NAMED(cpr0_u, CSFR_CPR0_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr1_u, CSFR_CPR1_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr2_u, CSFR_CPR2_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr3_u, CSFR_CPR3_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr4_u, CSFR_CPR4_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr5_u, CSFR_CPR5_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr6_u, CSFR_CPR6_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr7_u, CSFR_CPR7_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr8_u, CSFR_CPR8_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr9_u, CSFR_CPR9_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr10_u, CSFR_CPR10_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr11_u, CSFR_CPR11_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr12_u, CSFR_CPR12_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr13_u, CSFR_CPR13_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr14_u, CSFR_CPR14_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr15_u, CSFR_CPR15_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr16_u, CSFR_CPR16_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr17_u, CSFR_CPR17_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr18_u, CSFR_CPR18_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr19_u, CSFR_CPR19_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr20_u, CSFR_CPR20_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr21_u, CSFR_CPR21_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr22_u, CSFR_CPR22_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr23_u, CSFR_CPR23_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr24_u, CSFR_CPR24_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr25_u, CSFR_CPR25_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr26_u, CSFR_CPR26_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr27_u, CSFR_CPR27_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr28_u, CSFR_CPR28_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr29_u, CSFR_CPR29_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr30_u, CSFR_CPR30_U)
CSFRS_GEN_ACCESSORS_NAMED(cpr31_u, CSFR_CPR31_U)

CSFRS_GEN_ACCESSORS_NAMED(dpre_0, CSFR_DPRE_0)
CSFRS_GEN_ACCESSORS_NAMED(dpre_1, CSFR_DPRE_1)
CSFRS_GEN_ACCESSORS_NAMED(dpre_2, CSFR_DPRE_2)
CSFRS_GEN_ACCESSORS_NAMED(dpre_3, CSFR_DPRE_3)
CSFRS_GEN_ACCESSORS_NAMED(dpre_4, CSFR_DPRE_4)
CSFRS_GEN_ACCESSORS_NAMED(dpre_5, CSFR_DPRE_5)
CSFRS_GEN_ACCESSORS_NAMED(dpre_6, CSFR_DPRE_6)
CSFRS_GEN_ACCESSORS_NAMED(dpre_7, CSFR_DPRE_7)

CSFRS_GEN_ACCESSORS_NAMED(dpwe_0, CSFR_DPWE_0)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_1, CSFR_DPWE_1)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_2, CSFR_DPWE_2)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_3, CSFR_DPWE_3)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_4, CSFR_DPWE_4)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_5, CSFR_DPWE_5)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_6, CSFR_DPWE_6)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_7, CSFR_DPWE_7)

CSFRS_GEN_ACCESSORS_NAMED(cpxe_0, CSFR_CPXE_0)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_1, CSFR_CPXE_1)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_2, CSFR_CPXE_2)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_3, CSFR_CPXE_3)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_4, CSFR_CPXE_4)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_5, CSFR_CPXE_5)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_6, CSFR_CPXE_6)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_7, CSFR_CPXE_7)

CSFRS_GEN_ACCESSORS_NAMED(dstr, CSFR_DSTR)
CSFRS_GEN_ACCESSORS_NAMED(datr, CSFR_DATR)
CSFRS_GEN_ACCESSORS_NAMED(deadd, CSFR_DEADD)

CSFRS_GEN_ACCESSORS_NAMED(vm0_icr, CSFR_VM0_ICR)
CSFRS_GEN_ACCESSORS_NAMED(vm1_icr, CSFR_VM1_ICR)
CSFRS_GEN_ACCESSORS_NAMED(vm2_icr, CSFR_VM2_ICR)
CSFRS_GEN_ACCESSORS_NAMED(vm3_icr, CSFR_VM3_ICR)
CSFRS_GEN_ACCESSORS_NAMED(vm4_icr, CSFR_VM4_ICR)
CSFRS_GEN_ACCESSORS_NAMED(vm5_icr, CSFR_VM5_ICR)
CSFRS_GEN_ACCESSORS_NAMED(vm6_icr, CSFR_VM6_ICR)
CSFRS_GEN_ACCESSORS_NAMED(vm7_icr, CSFR_VM7_ICR)

CSFRS_GEN_ACCESSORS_NAMED(corecon, CSFR_CORECON)
CSFRS_GEN_ACCESSORS_NAMED(coreid, CSFR_COREID)
CSFRS_GEN_ACCESSORS_NAMED(fcx, CSFR_FCX)
CSFRS_GEN_ACCESSORS_NAMED(pcxi, CSFR_PCXI)
CSFRS_GEN_ACCESSORS_NAMED(pcon0, CSFR_PCON0)
CSFRS_GEN_ACCESSORS_NAMED(dcon0, CSFR_DCON0)

#define CSFRS_GEN_ACCESSORS_CPU_NAMED(csfr_name, csfr_base, csfr_offset)                           \
    static inline unsigned long csfr_cpu_##csfr_name##_read(unsigned long cpuid)                   \
    {                                                                                              \
        return *(unsigned long*)(csfr_base + (cpuid << 18) + csfr_offset);                         \
    }                                                                                              \
    static inline void csfr_cpu_##csfr_name##_write(unsigned long cpuid, unsigned long csfr_value) \
    {                                                                                              \
        *(unsigned long*)(csfr_base + (cpuid << 18) + csfr_offset) = csfr_value;                   \
    }

CSFRS_GEN_ACCESSORS_CPU_NAMED(bootcon, CSFR_BASE, CSFR_BOOTCON)
CSFRS_GEN_ACCESSORS_CPU_NAMED(pc, CSFR_BASE, CSFR_PC)

#define CSFR_PR32_CASES(M, R, OP) \
    OP(M, 0, R)                   \
    OP(M, 1, R)                   \
    OP(M, 2, R)                   \
    OP(M, 3, R)                   \
    OP(M, 4, R)                   \
    OP(M, 5, R)                   \
    OP(M, 6, R)                   \
    OP(M, 7, R)                   \
    OP(M, 8, R)                   \
    OP(M, 9, R)                   \
    OP(M, 10, R)                  \
    OP(M, 11, R)                  \
    OP(M, 12, R)                  \
    OP(M, 13, R)                  \
    OP(M, 14, R)                  \
    OP(M, 15, R)                  \
    OP(M, 16, R)                  \
    OP(M, 17, R)                  \
    OP(M, 18, R)                  \
    OP(M, 19, R)                  \
    OP(M, 20, R)                  \
    OP(M, 21, R)                  \
    OP(M, 22, R)                  \
    OP(M, 23, R)                  \
    OP(M, 24, R)                  \
    OP(M, 25, R) OP(M, 26, R) OP(M, 27, R) OP(M, 28, R) OP(M, 29, R) OP(M, 30, R) OP(M, 31, R)
#define CSFR_PR_READ_CASE(M, I, R) \
    case I:                        \
        return csfr_##M##pr##I##_##R##_read();
#define CSFR_PR_WRITE_CASE(M, I, R)         \
    case I:                                 \
        csfr_##M##pr##I##_##R##_write(val); \
        break;
#define CSFR_GEN_PR_READ(M, R)                                     \
    static inline unsigned long csfr_##M##pr_##R##_read(mpid_t id) \
    {                                                              \
        switch (id) {                                              \
            CSFR_PR32_CASES(M, R, CSFR_PR_READ_CASE)               \
            default:                                               \
                return 0UL;                                        \
        }                                                          \
    }
#define CSFR_GEN_PR_WRITE(M, R)                                               \
    static inline void csfr_##M##pr_##R##_write(mpid_t id, unsigned long val) \
    {                                                                         \
        switch (id) {                                                         \
            CSFR_PR32_CASES(M, R, CSFR_PR_WRITE_CASE)                         \
            default:                                                          \
                break;                                                        \
        }                                                                     \
    }

/* data */
CSFR_GEN_PR_WRITE(d, u)
CSFR_GEN_PR_WRITE(d, l)

CSFR_GEN_PR_READ(d, u)
CSFR_GEN_PR_READ(d, l)
/* code */
CSFR_GEN_PR_READ(c, u)
CSFR_GEN_PR_READ(c, l)

CSFR_GEN_PR_WRITE(c, u)
CSFR_GEN_PR_WRITE(c, l)

#define CSFR_PS8_CASES(M, OP) \
    OP(M, 0) OP(M, 1) OP(M, 2) OP(M, 3) OP(M, 4) OP(M, 5) OP(M, 6) OP(M, 7)

#define CSFR_PS_GET_CASE(M, I)         \
    case I:                            \
        val = csfr_##M##_##I##_read(); \
        break;
#define CSFR_PS_SET_CASE(M, I)     \
    case I:                        \
        csfr_##M##_##I##_write(v); \
        break;

#define GEN_P_ACCESSOR(m)                                                     \
    static inline unsigned long get_##m(unsigned long psid)                   \
    {                                                                         \
        unsigned long val = 0;                                                \
        switch (psid) {                                                       \
            CSFR_PS8_CASES(m, CSFR_PS_GET_CASE)                               \
            default:                                                          \
                break;                                                        \
        }                                                                     \
        return val;                                                           \
    }                                                                         \
    static inline void set_##m(unsigned long psid, unsigned long v)           \
    {                                                                         \
        switch (psid) {                                                       \
            CSFR_PS8_CASES(m, CSFR_PS_SET_CASE)                               \
            default:                                                          \
                break;                                                        \
        }                                                                     \
    }                                                                         \
    static inline bool get_##m##_bit(unsigned long psid, mpid_t mpid)         \
    {                                                                         \
        return !!(get_##m(psid) & (1UL << mpid));                             \
    }                                                                         \
    static inline void set_##m##_bit(unsigned long psid, mpid_t mpid, bool b) \
    {                                                                         \
        unsigned long tmp = get_##m(psid);                                    \
        tmp = b ? (tmp | (1UL << mpid)) : (tmp & ~(1UL << mpid));             \
        set_##m(psid, tmp);                                                   \
    }

GEN_P_ACCESSOR(dpre)
GEN_P_ACCESSOR(dpwe)
GEN_P_ACCESSOR(cpxe)

#define CORECON_PROTEN_MASK (0x2UL)
#define BOOTCON_BHALT_HALT  (0x1UL)
#define BOOTCON_BHALT_START (0UL)
#define PSW_CDC_MASK        (0x7FUL)

#endif /* __ASSEMBLER__ */

#define COREID_CORE_MASK (0x7UL)

#endif /* __ARCH_CSFRS_H__ */
