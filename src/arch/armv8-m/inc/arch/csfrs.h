/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CSFR_H__
#define __ARCH_CSFR_H__

#include <bao.h>

#define csfr_dcon1   0x9008
#define csfr_pcon1   0x9204
#define csfr_pcon0   0x920C
#define csfr_dcon0   0x9040
#define csfr_corecon 0xFE14
#define csfr_tccon   0xFE6C

#define csfr_cpxe_0  0xE000
#define csfr_cpxe_1  0xE004
#define csfr_cpxe_2  0xE008
#define csfr_cpxe_3  0xE00C
#define csfr_dpre_0  0xE010
#define csfr_dpre_1  0xE014
#define csfr_dpre_2  0xE018
#define csfr_dpre_3  0xE01C
#define csfr_dpwe_0  0xE020
#define csfr_dpwe_1  0xE024
#define csfr_dpwe_2  0xE028
#define csfr_dpwe_3  0xE02C

#define csfr_cpxe_4  0xE040
#define csfr_cpxe_5  0xE044
#define csfr_cpxe_6  0xE048
#define csfr_cpxe_7  0xE04C
#define csfr_dpre_4  0xE050
#define csfr_dpre_5  0xE054
#define csfr_dpre_6  0xE058
#define csfr_dpre_7  0xE05C
#define csfr_dpwe_4  0xE060
#define csfr_dpwe_5  0xE064
#define csfr_dpwe_6  0xE068
#define csfr_dpwe_7  0xE06C

#define csfr_dpr0_l  0xC000
#define csfr_dpr0_u  0xC004
#define csfr_dpr1_l  0xC008
#define csfr_dpr1_u  0xC00C
#define csfr_dpr2_l  0xC010
#define csfr_dpr2_u  0xC014
#define csfr_dpr3_l  0xC018
#define csfr_dpr3_u  0xC01C
#define csfr_dpr4_l  0xC020
#define csfr_dpr4_u  0xC024
#define csfr_dpr5_l  0xC028
#define csfr_dpr5_u  0xC02C
#define csfr_dpr6_l  0xC030
#define csfr_dpr6_u  0xC034
#define csfr_dpr7_l  0xC038
#define csfr_dpr7_u  0xC03C
#define csfr_dpr8_l  0xC040
#define csfr_dpr8_u  0xC044
#define csfr_dpr9_l  0xC048
#define csfr_dpr9_u  0xC04C
#define csfr_dpr10_l 0xC050
#define csfr_dpr10_u 0xC054
#define csfr_dpr11_l 0xC058
#define csfr_dpr11_u 0xC05C
#define csfr_dpr12_l 0xC060
#define csfr_dpr12_u 0xC064
#define csfr_dpr13_l 0xC068
#define csfr_dpr13_u 0xC06C
#define csfr_dpr14_l 0xC070
#define csfr_dpr14_u 0xC074
#define csfr_dpr15_l 0xC078
#define csfr_dpr15_u 0xC07C

#define csfr_cpr0_l  0xD000
#define csfr_cpr0_u  0xD004
#define csfr_cpr1_l  0xD008
#define csfr_cpr1_u  0xD00C
#define csfr_cpr2_l  0xD010
#define csfr_cpr2_u  0xD014
#define csfr_cpr3_l  0xD018
#define csfr_cpr3_u  0xD01C
#define csfr_cpr4_l  0xD020
#define csfr_cpr4_u  0xD024
#define csfr_cpr5_l  0xD028
#define csfr_cpr5_u  0xD02C
#define csfr_cpr6_l  0xD030
#define csfr_cpr6_u  0xD034
#define csfr_cpr7_l  0xD038
#define csfr_cpr7_u  0xD03C
#define csfr_cpr8_l  0xD040
#define csfr_cpr8_u  0xD044
#define csfr_cpr9_l  0xD048
#define csfr_cpr9_u  0xD04C
#define csfr_cpr10_l 0xD050
#define csfr_cpr10_u 0xD054
#define csfr_cpr11_l 0xD058
#define csfr_cpr11_u 0xD05C
#define csfr_cpr12_l 0xD060
#define csfr_cpr12_u 0xD064
#define csfr_cpr13_l 0xD068
#define csfr_cpr13_u 0xD06C
#define csfr_cpr14_l 0xD070
#define csfr_cpr14_u 0xD074
#define csfr_cpr15_l 0xD078
#define csfr_cpr15_u 0xD07C

#define csfr_fcx     0xFE38
#define csfr_lcx     0xFE3C
#define csfr_pcxi    0xFE00
#define csfr_bhv     0xB010
#define csfr_corecon 0xFE14
#define csfr_pcx     0xFE00

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

CSFRS_GEN_ACCESSORS_NAMED(tccon, csfr_tccon)

CSFRS_GEN_ACCESSORS_NAMED(dpr0_l, csfr_dpr0_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr1_l, csfr_dpr1_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr2_l, csfr_dpr2_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr3_l, csfr_dpr3_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr4_l, csfr_dpr4_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr5_l, csfr_dpr5_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr6_l, csfr_dpr6_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr7_l, csfr_dpr7_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr8_l, csfr_dpr8_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr9_l, csfr_dpr9_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr10_l, csfr_dpr10_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr11_l, csfr_dpr11_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr12_l, csfr_dpr12_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr13_l, csfr_dpr13_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr14_l, csfr_dpr14_l)
CSFRS_GEN_ACCESSORS_NAMED(dpr15_l, csfr_dpr15_l)

CSFRS_GEN_ACCESSORS_NAMED(dpr0_u, csfr_dpr0_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr1_u, csfr_dpr1_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr2_u, csfr_dpr2_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr3_u, csfr_dpr3_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr4_u, csfr_dpr4_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr5_u, csfr_dpr5_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr6_u, csfr_dpr6_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr7_u, csfr_dpr7_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr8_u, csfr_dpr8_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr9_u, csfr_dpr9_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr10_u, csfr_dpr10_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr11_u, csfr_dpr11_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr12_u, csfr_dpr12_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr13_u, csfr_dpr13_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr14_u, csfr_dpr14_u)
CSFRS_GEN_ACCESSORS_NAMED(dpr15_u, csfr_dpr15_u)

CSFRS_GEN_ACCESSORS_NAMED(cpr0_l, csfr_cpr0_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr1_l, csfr_cpr1_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr2_l, csfr_cpr2_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr3_l, csfr_cpr3_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr4_l, csfr_cpr4_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr5_l, csfr_cpr5_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr6_l, csfr_cpr6_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr7_l, csfr_cpr7_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr8_l, csfr_cpr8_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr9_l, csfr_cpr9_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr10_l, csfr_cpr10_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr11_l, csfr_cpr11_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr12_l, csfr_cpr12_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr13_l, csfr_cpr13_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr14_l, csfr_cpr14_l)
CSFRS_GEN_ACCESSORS_NAMED(cpr15_l, csfr_cpr15_l)

CSFRS_GEN_ACCESSORS_NAMED(cpr0_u, csfr_cpr0_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr1_u, csfr_cpr1_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr2_u, csfr_cpr2_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr3_u, csfr_cpr3_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr4_u, csfr_cpr4_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr5_u, csfr_cpr5_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr6_u, csfr_cpr6_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr7_u, csfr_cpr7_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr8_u, csfr_cpr8_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr9_u, csfr_cpr9_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr10_u, csfr_cpr10_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr11_u, csfr_cpr11_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr12_u, csfr_cpr12_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr13_u, csfr_cpr13_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr14_u, csfr_cpr14_u)
CSFRS_GEN_ACCESSORS_NAMED(cpr15_u, csfr_cpr15_u)

CSFRS_GEN_ACCESSORS_NAMED(dpre_0, csfr_dpre_0)
CSFRS_GEN_ACCESSORS_NAMED(dpre_1, csfr_dpre_1)
CSFRS_GEN_ACCESSORS_NAMED(dpre_2, csfr_dpre_2)
CSFRS_GEN_ACCESSORS_NAMED(dpre_3, csfr_dpre_3)
CSFRS_GEN_ACCESSORS_NAMED(dpre_4, csfr_dpre_4)
CSFRS_GEN_ACCESSORS_NAMED(dpre_5, csfr_dpre_5)
CSFRS_GEN_ACCESSORS_NAMED(dpre_6, csfr_dpre_6)
CSFRS_GEN_ACCESSORS_NAMED(dpre_7, csfr_dpre_7)

CSFRS_GEN_ACCESSORS_NAMED(dpwe_0, csfr_dpwe_0)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_1, csfr_dpwe_1)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_2, csfr_dpwe_2)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_3, csfr_dpwe_3)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_4, csfr_dpwe_4)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_5, csfr_dpwe_5)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_6, csfr_dpwe_6)
CSFRS_GEN_ACCESSORS_NAMED(dpwe_7, csfr_dpwe_7)

CSFRS_GEN_ACCESSORS_NAMED(cpxe_0, csfr_cpxe_0)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_1, csfr_cpxe_1)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_2, csfr_cpxe_2)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_3, csfr_cpxe_3)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_4, csfr_cpxe_4)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_5, csfr_cpxe_5)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_6, csfr_cpxe_6)
CSFRS_GEN_ACCESSORS_NAMED(cpxe_7, csfr_cpxe_7)

#endif /* __ASSEMBLER__ */

#endif /* __ARCH_CSFRS_H__ */
