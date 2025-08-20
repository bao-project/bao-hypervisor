/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CSFR_H__
#define __ARCH_CSFR_H__

#include <bao.h>

#define csfr_dcon1    0x9008
#define csfr_pcon1    0x9204
#define csfr_pcon0    0x920C
#define csfr_dcon0    0x9040
#define csfr_corecon  0xFE14
#define csfr_tccon    0xFE6C

#define csfr_cpxe_0   0xE000
#define csfr_cpxe_1   0xE004
#define csfr_cpxe_2   0xE008
#define csfr_cpxe_3   0xE00C
#define csfr_dpre_0   0xE010
#define csfr_dpre_1   0xE014
#define csfr_dpre_2   0xE018
#define csfr_dpre_3   0xE01C
#define csfr_dpwe_0   0xE020
#define csfr_dpwe_1   0xE024
#define csfr_dpwe_2   0xE028
#define csfr_dpwe_3   0xE02C

#define csfr_cpxe_4   0xE040
#define csfr_cpxe_5   0xE044
#define csfr_cpxe_6   0xE048
#define csfr_cpxe_7   0xE04C
#define csfr_dpre_4   0xE050
#define csfr_dpre_5   0xE054
#define csfr_dpre_6   0xE058
#define csfr_dpre_7   0xE05C
#define csfr_dpwe_4   0xE060
#define csfr_dpwe_5   0xE064
#define csfr_dpwe_6   0xE068
#define csfr_dpwe_7   0xE06C

#define csfr_dpr0_l   0xC000
#define csfr_dpr0_u   0xC004
#define csfr_dpr1_l   0xC008
#define csfr_dpr1_u   0xC00C
#define csfr_dpr2_l   0xC010
#define csfr_dpr2_u   0xC014
#define csfr_dpr3_l   0xC018
#define csfr_dpr3_u   0xC01C
#define csfr_dpr4_l   0xC020
#define csfr_dpr4_u   0xC024
#define csfr_dpr5_l   0xC028
#define csfr_dpr5_u   0xC02C
#define csfr_dpr6_l   0xC030
#define csfr_dpr6_u   0xC034
#define csfr_dpr7_l   0xC038
#define csfr_dpr7_u   0xC03C
#define csfr_dpr8_l   0xC040
#define csfr_dpr8_u   0xC044
#define csfr_dpr9_l   0xC048
#define csfr_dpr9_u   0xC04C
#define csfr_dpr10_l  0xC050
#define csfr_dpr10_u  0xC054
#define csfr_dpr11_l  0xC058
#define csfr_dpr11_u  0xC05C
#define csfr_dpr12_l  0xC060
#define csfr_dpr12_u  0xC064
#define csfr_dpr13_l  0xC068
#define csfr_dpr13_u  0xC06C
#define csfr_dpr14_l  0xC070
#define csfr_dpr14_u  0xC074
#define csfr_dpr15_l  0xC078
#define csfr_dpr15_u  0xC07C

#define csfr_cpr0_l   0xD000
#define csfr_cpr0_u   0xD004
#define csfr_cpr1_l   0xD008
#define csfr_cpr1_u   0xD00C
#define csfr_cpr2_l   0xD010
#define csfr_cpr2_u   0xD014
#define csfr_cpr3_l   0xD018
#define csfr_cpr3_u   0xD01C
#define csfr_cpr4_l   0xD020
#define csfr_cpr4_u   0xD024
#define csfr_cpr5_l   0xD028
#define csfr_cpr5_u   0xD02C
#define csfr_cpr6_l   0xD030
#define csfr_cpr6_u   0xD034
#define csfr_cpr7_l   0xD038
#define csfr_cpr7_u   0xD03C
#define csfr_cpr8_l   0xD040
#define csfr_cpr8_u   0xD044
#define csfr_cpr9_l   0xD048
#define csfr_cpr9_u   0xD04C
#define csfr_cpr10_l  0xD050
#define csfr_cpr10_u  0xD054
#define csfr_cpr11_l  0xD058
#define csfr_cpr11_u  0xD05C
#define csfr_cpr12_l  0xD060
#define csfr_cpr12_u  0xD064
#define csfr_cpr13_l  0xD068
#define csfr_cpr13_u  0xD06C
#define csfr_cpr14_l  0xD070
#define csfr_cpr14_u  0xD074
#define csfr_cpr15_l  0xD078
#define csfr_cpr15_u  0xD07C

#define csfr_fcx      0xFE38
#define csfr_lcx      0xFE3C
#define csfr_pcxi     0xFE00
#define csfr_bhv      0xB010
#define csfr_corecon  0xFE14
#define csfr_pcx      0xFE00

#define csfr_dstr     0x9010
#define csfr_datr     0x9018
#define csfr_deadd    0x901C

#define csfr_vm0_icr  0xB100
#define csfr_vm1_icr  0xB104
#define csfr_vm2_icr  0xB108
#define csfr_vm3_icr  0xB10C
#define csfr_vm4_icr  0xB110
#define csfr_vm5_icr  0xB114
#define csfr_vm6_icr  0xB118
#define csfr_vm7_icr  0xB11C

#define csfr_base     0xF8830000
#define csfr_bootcon  0xFE60
#define csfr_pc       0xFE08

#define csfr_hvhra_a0 0xFF81
#define csfr_hvhra_a1 0xFF85
#define csfr_hvhra_a8 0xFFA1
#define csfr_hvhra_a9 0xFFA5

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

CSFRS_GEN_ACCESSORS_NAMED(dstr, csfr_dstr)
CSFRS_GEN_ACCESSORS_NAMED(datr, csfr_datr)
CSFRS_GEN_ACCESSORS_NAMED(deadd, csfr_deadd)

CSFRS_GEN_ACCESSORS_NAMED(vm0_icr, csfr_vm0_icr)
CSFRS_GEN_ACCESSORS_NAMED(vm1_icr, csfr_vm1_icr)
CSFRS_GEN_ACCESSORS_NAMED(vm2_icr, csfr_vm2_icr)
CSFRS_GEN_ACCESSORS_NAMED(vm3_icr, csfr_vm3_icr)
CSFRS_GEN_ACCESSORS_NAMED(vm4_icr, csfr_vm4_icr)
CSFRS_GEN_ACCESSORS_NAMED(vm5_icr, csfr_vm5_icr)
CSFRS_GEN_ACCESSORS_NAMED(vm6_icr, csfr_vm6_icr)
CSFRS_GEN_ACCESSORS_NAMED(vm7_icr, csfr_vm7_icr)

CSFRS_GEN_ACCESSORS_NAMED(corecon, csfr_corecon)

#define CSFRS_GEN_ACCESSORS_CPU_NAMED(csfr_name, csfr_base, csfr_offset)                           \
    static inline unsigned long csfr_cpu_##csfr_name##_read(unsigned long cpuid)                   \
    {                                                                                              \
        return *(unsigned long*)(csfr_base + (cpuid << 18) + csfr_offset);                         \
    }                                                                                              \
    static inline void csfr_cpu_##csfr_name##_write(unsigned long cpuid, unsigned long csfr_value) \
    {                                                                                              \
        *(unsigned long*)(csfr_base + (cpuid << 18) + csfr_offset) = csfr_value;                   \
    }

CSFRS_GEN_ACCESSORS_CPU_NAMED(bootcon, csfr_base, csfr_bootcon)
CSFRS_GEN_ACCESSORS_CPU_NAMED(pc, csfr_base, csfr_pc)

#define CSFR_GEN_PR_READ(m, r)                                     \
    static inline unsigned long csfr_##m##pr_##r##_read(mpid_t id) \
    {                                                              \
        switch (id) {                                              \
            case 0:                                                \
                return csfr_##m##pr0_##r##_read();                 \
            case 1:                                                \
                return csfr_##m##pr1_##r##_read();                 \
            case 2:                                                \
                return csfr_##m##pr2_##r##_read();                 \
            case 3:                                                \
                return csfr_##m##pr3_##r##_read();                 \
            case 4:                                                \
                return csfr_##m##pr4_##r##_read();                 \
            case 5:                                                \
                return csfr_##m##pr5_##r##_read();                 \
            case 6:                                                \
                return csfr_##m##pr6_##r##_read();                 \
            case 7:                                                \
                return csfr_##m##pr7_##r##_read();                 \
            case 8:                                                \
                return csfr_##m##pr8_##r##_read();                 \
            case 9:                                                \
                return csfr_##m##pr9_##r##_read();                 \
            case 10:                                               \
                return csfr_##m##pr10_##r##_read();                \
            case 11:                                               \
                return csfr_##m##pr11_##r##_read();                \
            case 12:                                               \
                return csfr_##m##pr12_##r##_read();                \
            case 13:                                               \
                return csfr_##m##pr13_##r##_read();                \
            case 14:                                               \
                return csfr_##m##pr14_##r##_read();                \
            case 15:                                               \
                return csfr_##m##pr15_##r##_read();                \
            default:                                               \
                return 0;                                          \
        }                                                          \
    }

#define CSFR_GEN_PR_WRITE(m, r)                                               \
    static inline void csfr_##m##pr_##r##_write(mpid_t id, unsigned long val) \
    {                                                                         \
        switch (id) {                                                         \
            case 0:                                                           \
                csfr_##m##pr0_##r##_write(val);                               \
                break;                                                        \
            case 1:                                                           \
                csfr_##m##pr1_##r##_write(val);                               \
                break;                                                        \
            case 2:                                                           \
                csfr_##m##pr2_##r##_write(val);                               \
                break;                                                        \
            case 3:                                                           \
                csfr_##m##pr3_##r##_write(val);                               \
                break;                                                        \
            case 4:                                                           \
                csfr_##m##pr4_##r##_write(val);                               \
                break;                                                        \
            case 5:                                                           \
                csfr_##m##pr5_##r##_write(val);                               \
                break;                                                        \
            case 6:                                                           \
                csfr_##m##pr6_##r##_write(val);                               \
                break;                                                        \
            case 7:                                                           \
                csfr_##m##pr7_##r##_write(val);                               \
                break;                                                        \
            case 8:                                                           \
                csfr_##m##pr8_##r##_write(val);                               \
                break;                                                        \
            case 9:                                                           \
                csfr_##m##pr9_##r##_write(val);                               \
                break;                                                        \
            case 10:                                                          \
                csfr_##m##pr10_##r##_write(val);                              \
                break;                                                        \
            case 11:                                                          \
                csfr_##m##pr11_##r##_write(val);                              \
                break;                                                        \
            case 12:                                                          \
                csfr_##m##pr12_##r##_write(val);                              \
                break;                                                        \
            case 13:                                                          \
                csfr_##m##pr13_##r##_write(val);                              \
                break;                                                        \
            case 14:                                                          \
                csfr_##m##pr14_##r##_write(val);                              \
                break;                                                        \
            case 15:                                                          \
                csfr_##m##pr15_##r##_write(val);                              \
                break;                                                        \
            default:                                                          \
                break;                                                        \
        }                                                                     \
        return;                                                               \
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

#define GEN_P_ACCESSOR(m)                                                       \
    static inline bool get_##m##_bit(unsigned long psid, mpid_t mpid)           \
    {                                                                           \
        unsigned long val = 0;                                                  \
        switch (psid) {                                                         \
            case 0:                                                             \
                val = csfr_##m##_0_read();                                      \
                break;                                                          \
            case 1:                                                             \
                val = csfr_##m##_1_read();                                      \
                break;                                                          \
            case 2:                                                             \
                val = csfr_##m##_2_read();                                      \
                break;                                                          \
            case 3:                                                             \
                val = csfr_##m##_3_read();                                      \
                break;                                                          \
            case 4:                                                             \
                val = csfr_##m##_4_read();                                      \
                break;                                                          \
            case 5:                                                             \
                val = csfr_##m##_5_read();                                      \
                break;                                                          \
            case 6:                                                             \
                val = csfr_##m##_6_read();                                      \
                break;                                                          \
            case 7:                                                             \
                val = csfr_##m##_7_read();                                      \
                break;                                                          \
            default:                                                            \
                break;                                                          \
        }                                                                       \
        return !!(val & (1UL << mpid));                                         \
    }                                                                           \
    static inline void set_##m##_bit(unsigned long psid, mpid_t mpid, bool val) \
    {                                                                           \
        unsigned long tmp = 0;                                                  \
        switch (psid) {                                                         \
            case 0:                                                             \
                tmp = csfr_##m##_0_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_0_write(tmp);                                        \
                break;                                                          \
            case 1:                                                             \
                tmp = csfr_##m##_1_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_1_write(tmp);                                        \
                break;                                                          \
            case 2:                                                             \
                tmp = csfr_##m##_2_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_2_write(tmp);                                        \
                break;                                                          \
            case 3:                                                             \
                tmp = csfr_##m##_3_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_3_write(tmp);                                        \
                break;                                                          \
            case 4:                                                             \
                tmp = csfr_##m##_4_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_4_write(tmp);                                        \
                break;                                                          \
            case 5:                                                             \
                tmp = csfr_##m##_5_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_5_write(tmp);                                        \
                break;                                                          \
            case 6:                                                             \
                tmp = csfr_##m##_6_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_6_write(tmp);                                        \
                break;                                                          \
            case 7:                                                             \
                tmp = csfr_##m##_7_read();                                      \
                if (val)                                                        \
                    tmp |= 1UL << mpid;                                         \
                else                                                            \
                    tmp &= ~(1UL << mpid);                                      \
                csfr_##m##_7_write(tmp);                                        \
                break;                                                          \
            default:                                                            \
                break;                                                          \
        }                                                                       \
        return;                                                                 \
    }                                                                           \
    static inline unsigned long get_##m(unsigned long psid)                     \
    {                                                                           \
        unsigned long val = 0;                                                  \
        switch (psid) {                                                         \
            case 0:                                                             \
                val = csfr_##m##_0_read();                                      \
                break;                                                          \
            case 1:                                                             \
                val = csfr_##m##_1_read();                                      \
                break;                                                          \
            case 2:                                                             \
                val = csfr_##m##_2_read();                                      \
                break;                                                          \
            case 3:                                                             \
                val = csfr_##m##_3_read();                                      \
                break;                                                          \
            case 4:                                                             \
                val = csfr_##m##_4_read();                                      \
                break;                                                          \
            case 5:                                                             \
                val = csfr_##m##_5_read();                                      \
                break;                                                          \
            case 6:                                                             \
                val = csfr_##m##_6_read();                                      \
                break;                                                          \
            case 7:                                                             \
                val = csfr_##m##_7_read();                                      \
                break;                                                          \
            default:                                                            \
                break;                                                          \
        }                                                                       \
        return val;                                                             \
    }                                                                           \
    static inline void set_##m(unsigned long psid, unsigned long val)           \
    {                                                                           \
        switch (psid) {                                                         \
            case 0:                                                             \
                csfr_##m##_0_write(val);                                        \
                break;                                                          \
            case 1:                                                             \
                csfr_##m##_1_write(val);                                        \
                break;                                                          \
            case 2:                                                             \
                csfr_##m##_2_write(val);                                        \
                break;                                                          \
            case 3:                                                             \
                csfr_##m##_3_write(val);                                        \
                break;                                                          \
            case 4:                                                             \
                csfr_##m##_4_write(val);                                        \
                break;                                                          \
            case 5:                                                             \
                csfr_##m##_5_write(val);                                        \
                break;                                                          \
            case 6:                                                             \
                csfr_##m##_6_write(val);                                        \
                break;                                                          \
            case 7:                                                             \
                csfr_##m##_7_write(val);                                        \
                break;                                                          \
            default:                                                            \
                break;                                                          \
        }                                                                       \
    }

GEN_P_ACCESSOR(dpre)
GEN_P_ACCESSOR(dpwe)
GEN_P_ACCESSOR(cpxe)

#endif /* __ASSEMBLER__ */

#endif /* __ARCH_CSFRS_H__ */
