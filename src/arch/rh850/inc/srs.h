/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SRS_H__
#define __ARCH_SRS_H__

#include <bao.h>

/* Basic System Registers */
#define PSW_Z              (1UL << 0)
#define PSW_EBV            (1UL << 15)

#define EIPSW_EBV          (PSW_EBV)
#define FEPSW_EBV          (PSW_EBV)

/* MPU Registers */
#define MPM_MPE            (1UL << 0)
#define MPM_SVP            (1UL << 1)
#define MPCFG_HBE_OFF      (8)
#define MPCFG_HBE_LEN      (6)
#define MPCFG_HBE_MASK     (BIT_MASK(MPCFG_HBE_OFF, MPCFG_HBE_LEN))
#define MPIDX_IDX_OFF      (0)
#define MPIDX_IDX_LEN      (5)
#define MPIDX_IDX_MASK     (BIT_MASK(MPIDX_IDX_OFF, MPIDX_IDX_LEN))
#define MPLA_OFF           (2)
#define MPLA_LEN           (30)
#define MPLA_MASK          (BIT_MASK(MPLA_OFF, MPLA_LEN))
#define MPUA_OFF           (2)
#define MPUA_LEN           (30)
#define MPUA_MASK          (BIT_MASK(MPUA_OFF, MPUA_LEN))

#define MPCFG_NMPUE_SHIFT  (0U)
#define MPCFG_NMPUE_MASK   (0x1FUL << MPCFG_NMPUE_SHIFT)
#define MPCFG_GET_NMPUE(v) (((v) & MPCFG_NMPUE_MASK) >> MPCFG_NMPUE_SHIFT)

#define MPAT_E_SHIFT       (7U)
#define MPAT_E_MASK        (0x1UL << MPAT_E_SHIFT)
#define MPAT_GET_E(v)      (((v) & MPAT_E_MASK) >> MPAT_E_SHIFT)

/* Hypervisor registers */
#define GMCFG_HMP          (1UL << 1)
#define GMCFG_GSYSE        (1UL << 4)
#define GMCFG_GCU0         (1UL << 16)
#define GMCFG_GCU1         (1UL << 17)

#define EIPSWH_GPID_OFF    (8)
#define EIPSWH_GPID_LEN    (3)
#define EIPSWH_GPID_MASK   (BIT_MASK(EIPSWH_GPID_OFF, EIPSWH_GPID_LEN))
#define EIPSWH_GM          (1UL << 31)

#define FEPSWH_GPID_OFF    (EIPSWH_GPID_OFF)
#define FEPSWH_GPID_LEN    (EIPSWH_GPID_LEN)
#define FEPSWH_GPID_MASK   (EIPSWH_GPID_MASK)
#define FEPSWH_GM          (EIPSWH_GM)

#define TSCTRL_CEN_SHIFT   (0UL)
#define TSCTRL_CEN_MASK    (0x1UL << TSCTRL_CEN_SHIFT)
#define TSCTRL_GET_CEN(v)  (((v) & TSCTRL_CEN_MASK) >> TSCTRL_CEN_SHIFT)

#define TSCTRL_CEN_SET(v)  ((v) | TSCTRL_CEN_MASK)
#define TSCTRL_CEN_CLR(v)  ((v) & ~TSCTRL_CEN_MASK)

/* Guest context registers */
#define GMMPM_GMPE         (1UL << 2)

#ifndef __ASSEMBLER__

/* System Register accessors */
#define SRS_GEN_ACCESSORS(name, regid, selid)                                  \
    static inline unsigned long srs_##name##_read(void)                        \
    {                                                                          \
        unsigned long _temp;                                                   \
        __asm__ volatile("stsr " #regid ", %0, " #selid "\n\r" : "=r"(_temp)); \
        return _temp;                                                          \
    }                                                                          \
    static inline void srs_##name##_write(unsigned long val)                   \
    {                                                                          \
        __asm__ volatile("ldsr %0," #regid ", " #selid "\n\r" ::"r"(val));     \
    }

/* BASIC SYS REG */
SRS_GEN_ACCESSORS(eipc, 0, 0)
SRS_GEN_ACCESSORS(eipsw, 1, 0)
SRS_GEN_ACCESSORS(fepc, 2, 0)
SRS_GEN_ACCESSORS(fepsw, 3, 0)
SRS_GEN_ACCESSORS(psw, 5, 0)
SRS_GEN_ACCESSORS(fpsr, 6, 0)
SRS_GEN_ACCESSORS(fpepc, 7, 0)
SRS_GEN_ACCESSORS(fpst, 8, 0)
SRS_GEN_ACCESSORS(fpcc, 9, 0)
SRS_GEN_ACCESSORS(fpcfg, 10, 0)
SRS_GEN_ACCESSORS(eiic, 13, 0)
SRS_GEN_ACCESSORS(feic, 14, 0)
SRS_GEN_ACCESSORS(ctpc, 16, 0)
SRS_GEN_ACCESSORS(ctpsw, 17, 0)
SRS_GEN_ACCESSORS(ctbp, 20, 0)
SRS_GEN_ACCESSORS(snzcfg, 21, 0)
SRS_GEN_ACCESSORS(eiwr, 28, 0)
SRS_GEN_ACCESSORS(fewr, 29, 0)
SRS_GEN_ACCESSORS(spid, 0, 1)
SRS_GEN_ACCESSORS(spidlist, 1, 1)
SRS_GEN_ACCESSORS(rbase, 2, 1)
SRS_GEN_ACCESSORS(ebase, 3, 1)
SRS_GEN_ACCESSORS(peid, 0, 2)
SRS_GEN_ACCESSORS(bmid, 1, 2)
SRS_GEN_ACCESSORS(intbp, 4, 1)
SRS_GEN_ACCESSORS(mea, 6, 2)
SRS_GEN_ACCESSORS(mei, 8, 2)
SRS_GEN_ACCESSORS(rbip, 18, 2)

/* TIME STAMP */
SRS_GEN_ACCESSORS(tscountl, 0, 11)
SRS_GEN_ACCESSORS(tscounth, 1, 11)
SRS_GEN_ACCESSORS(tsctrl, 2, 11)

/* INTERRUPT SYS REGS */
SRS_GEN_ACCESSORS(ispr, 10, 2)
SRS_GEN_ACCESSORS(imsr, 11, 2)
SRS_GEN_ACCESSORS(icsr, 12, 2)
SRS_GEN_ACCESSORS(intcfg, 13, 2)
SRS_GEN_ACCESSORS(plmr, 14, 2)

/* MPU FUNCTION REGISTERS */
SRS_GEN_ACCESSORS(mpm, 0, 5)
SRS_GEN_ACCESSORS(mpcfg, 2, 5)
SRS_GEN_ACCESSORS(mca, 8, 5)
SRS_GEN_ACCESSORS(mcs, 9, 5)
SRS_GEN_ACCESSORS(mcc, 10, 5)
SRS_GEN_ACCESSORS(mcr, 11, 5)
SRS_GEN_ACCESSORS(mci, 12, 5)
SRS_GEN_ACCESSORS(mpidx, 16, 5)
SRS_GEN_ACCESSORS(mpbk, 17, 5)
SRS_GEN_ACCESSORS(mpla, 20, 5)
SRS_GEN_ACCESSORS(mpua, 21, 5)
SRS_GEN_ACCESSORS(mpat, 22, 5)
SRS_GEN_ACCESSORS(mpid0, 24, 5)
SRS_GEN_ACCESSORS(mpid1, 25, 5)
SRS_GEN_ACCESSORS(mpid2, 26, 5)
SRS_GEN_ACCESSORS(mpid3, 27, 5)
SRS_GEN_ACCESSORS(mpid4, 28, 5)
SRS_GEN_ACCESSORS(mpid5, 29, 5)
SRS_GEN_ACCESSORS(mpid6, 30, 5)
SRS_GEN_ACCESSORS(mpid7, 31, 5)

/* CACHE OPERATION REGISTERS */
SRS_GEN_ACCESSORS(ictagl, 16, 4)
SRS_GEN_ACCESSORS(ictagh, 17, 4)
SRS_GEN_ACCESSORS(icdatl, 18, 4)
SRS_GEN_ACCESSORS(icdath, 19, 4)
SRS_GEN_ACCESSORS(icctrl, 24, 4)
SRS_GEN_ACCESSORS(iccfg, 26, 4)
SRS_GEN_ACCESSORS(icerr, 28, 4)

/* VIRTUALIZATION SUPPORT REGISTERS */
SRS_GEN_ACCESSORS(hvcfg, 16, 1)
SRS_GEN_ACCESSORS(gmcfg, 17, 1)
SRS_GEN_ACCESSORS(pswh, 15, 0)
SRS_GEN_ACCESSORS(eipswh, 18, 0)
SRS_GEN_ACCESSORS(fepswh, 19, 0)
SRS_GEN_ACCESSORS(hvsb, 20, 1)
SRS_GEN_ACCESSORS(dbgen, 0, 3)

/* GUEST CONTEXT REGISTERS */
SRS_GEN_ACCESSORS(gmeipc, 0, 9)
SRS_GEN_ACCESSORS(gmfepc, 2, 9)
SRS_GEN_ACCESSORS(gmpsw, 5, 9)
SRS_GEN_ACCESSORS(gmmea, 6, 9)
SRS_GEN_ACCESSORS(gmmei, 8, 9)
SRS_GEN_ACCESSORS(gmeiic, 13, 9)
SRS_GEN_ACCESSORS(gmfeic, 14, 9)
SRS_GEN_ACCESSORS(gmspid, 16, 9)
SRS_GEN_ACCESSORS(gmspidlist, 17, 9)
SRS_GEN_ACCESSORS(gmmpm, 25, 9)
SRS_GEN_ACCESSORS(gmpeid, 30, 9)

#endif /* __ASSEMBLER__ */
#endif /* __ARCH_SRS_H__ */
