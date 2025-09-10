/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SRS_H__
#define __ARCH_SRS_H__

#include <bao.h>

/* Basic System Registers */
#define PSW_Z               (1UL << 0)
#define PSW_EBV             (1UL << 15)

#define EIPSW_EBV           (PSW_EBV)
#define FEPSW_EBV           (PSW_EBV)

/* MPU Registers */
#define MPM_MPE             (1UL << 0)
#define MPM_SVP             (1UL << 1)
#define MPCFG_HBE_OFF       (8)
#define MPCFG_HBE_LEN       (6)
#define MPCFG_HBE_MASK      (BIT_MASK(MPCFG_HBE_OFF, MPCFG_HBE_LEN))
#define MPIDX_IDX_OFF       (0)
#define MPIDX_IDX_LEN       (5)
#define MPIDX_IDX_MASK      (BIT_MASK(MPIDX_IDX_OFF, MPIDX_IDX_LEN))
#define MPLA_OFF            (2)
#define MPLA_LEN            (30)
#define MPLA_MASK           (BIT_MASK(MPLA_OFF, MPLA_LEN))
#define MPUA_OFF            (2)
#define MPUA_LEN            (30)
#define MPUA_MASK           (BIT_MASK(MPUA_OFF, MPUA_LEN))

/* Hypervisor registers */
#define GMCFG_HMP           (1UL << 1)
#define GMCFG_GSYSE         (1UL << 4)
#define GMCFG_GCU0          (1UL << 16)
#define GMCFG_GCU1          (1UL << 17)

#define EIPSWH_GPID_OFF     (8)
#define EIPSWH_GPID_LEN     (3)
#define EIPSWH_GPID_MASK    (BIT_MASK(EIPSWH_GPID_OFF, EIPSWH_GPID_LEN))
#define EIPSWH_GM           (1UL << 31)

#define FEPSWH_GPID_OFF     (EIPSWH_GPID_OFF)
#define FEPSWH_GPID_LEN     (EIPSWH_GPID_LEN)
#define FEPSWH_GPID_MASK    (EIPSWH_GPID_MASK)
#define FEPSWH_GM           (EIPSWH_GM)

/* Guest context registers */
#define GMMPM_GMPE      (1UL << 2)

#ifndef __ASSEMBLER__

/* BASIC SYS REG */
static inline unsigned long get_eipc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 0, %0, 0" : "=r"(val));
    return val;
}

static inline void set_eipc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 0, 0" : : "r"(val));
}

static inline unsigned long get_eipsw(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 1, %0, 0" : "=r"(val));
    return val;
}

static inline void set_eipsw(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 1, 0" : : "r"(val));
}

static inline unsigned long get_fepc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 2, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fepc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 2, 0" : : "r"(val));
}

static inline unsigned long get_fepsw(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 3, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fepsw(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 3, 0" : : "r"(val));
}

static inline unsigned long get_psw(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 5, %0, 0" : "=r"(val));
    return val;
}

static inline void set_psw(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 5, 0" : : "r"(val));
}

static inline unsigned long get_fpsr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 6, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fpsr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 6, 0" : : "r"(val));
}

static inline unsigned long get_fpepc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 7, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fpepc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 7, 0" : : "r"(val));
}

static inline unsigned long get_fpst(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 8, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fpst(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 8, 0" : : "r"(val));
}

static inline unsigned long get_fpcc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 9, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fpcc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 9, 0" : : "r"(val));
}

static inline unsigned long get_fpcfg(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 10, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fpcfg(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 10, 0" : : "r"(val));
}

static inline unsigned long get_eiic(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 13, %0, 0" : "=r"(val));
    return val;
}

static inline void set_eiic(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 13, 0" : : "r"(val));
}

static inline unsigned long get_feic(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 14, %0, 0" : "=r"(val));
    return val;
}

static inline void set_feic(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 14, 0" : : "r"(val));
}

static inline unsigned long get_ctpc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 16, %0, 0" : "=r"(val));
    return val;
}

static inline void set_ctpc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 16, 0" : : "r"(val));
}

static inline unsigned long get_ctpsw(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 17, %0, 0" : "=r"(val));
    return val;
}

static inline void set_ctpsw(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 17, 0" : : "r"(val));
}

static inline unsigned long get_ctbp(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 20, %0, 0" : "=r"(val));
    return val;
}

static inline void set_ctbp(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 20, 0" : : "r"(val));
}

static inline unsigned long get_snzcfg(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 21, %0, 0" : "=r"(val));
    return val;
}

static inline void set_snzcfg(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 21, 0" : : "r"(val));
}

static inline unsigned long get_eiwr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 28, %0, 0" : "=r"(val));
    return val;
}

static inline void set_eiwr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 28, 0" : : "r"(val));
}

static inline unsigned long get_fewr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 29, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fewr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 29, 0" : : "r"(val));
}

static inline unsigned long get_spid(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 0, %0, 1" : "=r"(val));
    return val;
}

static inline void set_spid(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 0, 1" : : "r"(val));
}

static inline unsigned long get_spidlist(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 1, %0, 1" : "=r"(val));
    return val;
}

static inline void set_spidlist(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 1, 1" : : "r"(val));
}

static inline unsigned long get_rbase(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 2, %0, 1" : "=r"(val));
    return val;
}

static inline void set_rbase(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 2, 1" : : "r"(val));
}

static inline unsigned long get_ebase(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 3, %0, 1" : "=r"(val));
    return val;
}

static inline void set_ebase(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 3, 1" : : "r"(val));
}

static inline unsigned long get_peid(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 0, %0, 2" : "=r"(val));
    return val;
}

static inline void set_peid(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 0, 2" : : "r"(val));
}

static inline unsigned long get_bmid(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 1, %0, 2" : "=r"(val));
    return val;
}

static inline void set_bmid(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 1, 2" : : "r"(val));
}

static inline unsigned long get_intbp(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 4, %0, 1" : "=r"(val));
    return val;
}

static inline void set_intbp(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 4, 1" : : "r"(val));
}

static inline unsigned long get_mea(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 6, %0, 2" : "=r"(val));
    return val;
}

static inline void set_mea(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 6, 2" : : "r"(val));
}

static inline unsigned long get_mei(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 8, %0, 2" : "=r"(val));
    return val;
}

static inline void set_mei(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 8, 2" : : "r"(val));
}

static inline unsigned long get_rbip(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 18, %0, 2" : "=r"(val));
    return val;
}

static inline void set_rbip(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 18, 2" : : "r"(val));
}

/* INTERRUPT SYS REGS */
static inline unsigned long get_ispr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 10, %0, 2" : "=r"(val));
    return val;
}

static inline void set_ispr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 10, 2" : : "r"(val));
}

static inline unsigned long get_imsr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 11, %0, 2" : "=r"(val));
    return val;
}

static inline void set_imsr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 11, 2" : : "r"(val));
}

static inline unsigned long get_icsr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 12, %0, 2" : "=r"(val));
    return val;
}

static inline void set_icsr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 12, 2" : : "r"(val));
}

static inline unsigned long get_intcfg(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 13, %0, 2" : "=r"(val));
    return val;
}

static inline void set_intcfg(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 13, 2" : : "r"(val));
}

static inline unsigned long get_plmr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 14, %0, 2" : "=r"(val));
    return val;
}

static inline void set_plmr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 14, 2" : : "r"(val));
}

/* MPU FUNCTION REGISTERS */
/* #pragma inline_asm get_mpm */
static inline unsigned long get_mpm(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 0, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpm(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 0, 5" : : "r"(val));
}

static inline unsigned long get_mpcfg(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 2, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpcfg(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 2, 5" : : "r"(val));
}

static inline unsigned long get_mca(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 8, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mca(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 8, 5" : : "r"(val));
}

static inline unsigned long get_mcs(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 9, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mcs(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 9, 5" : : "r"(val));
}

static inline unsigned long get_mcc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 10, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mcc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 10, 5" : : "r"(val));
}

static inline unsigned long get_mcr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 11, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mcr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 11, 5" : : "r"(val));
}

static inline unsigned long get_mci(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 12, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mci(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 12, 5" : : "r"(val));
}

static inline unsigned long get_mpidx(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 16, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpidx(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 16, 5" : : "r"(val));
}

static inline unsigned long get_mpbk(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 17, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpbk(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 17, 5" : : "r"(val));
}

static inline unsigned long get_mpla(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 20, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpla(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 20, 5" : : "r"(val));
}

static inline unsigned long get_mpua(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 21, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpua(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 21, 5" : : "r"(val));
}

static inline unsigned long get_mpat(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 22, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpat(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 22, 5" : : "r"(val));
}

static inline unsigned long get_mpid0(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 24, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid0(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 24, 5" : : "r"(val));
}

static inline unsigned long get_mpid1(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 25, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid1(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 25, 5" : : "r"(val));
}

static inline unsigned long get_mpid2(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 26, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid2(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 26, 5" : : "r"(val));
}

static inline unsigned long get_mpid3(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 27, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid3(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 27, 5" : : "r"(val));
}

static inline unsigned long get_mpid4(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 28, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid4(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 28, 5" : : "r"(val));
}

static inline unsigned long get_mpid5(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 29, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid5(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 29, 5" : : "r"(val));
}

static inline unsigned long get_mpid6(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 30, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid6(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 30, 5" : : "r"(val));
}

static inline unsigned long get_mpid7(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 31, %0, 5" : "=r"(val));
    return val;
}

static inline void set_mpid7(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 31, 5" : : "r"(val));
}

/* CACHE OPERATION REGISTERS */
static inline unsigned long get_ictagl(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 16, %0, 4" : "=r"(val));
    return val;
}

static inline void set_ictagl(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 16, 4" : : "r"(val));
}

static inline unsigned long get_ictagh(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 17, %0, 4" : "=r"(val));
    return val;
}

static inline void set_ictagh(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 17, 4" : : "r"(val));
}

static inline unsigned long get_icdatl(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 18, %0, 4" : "=r"(val));
    return val;
}

static inline void set_icdatl(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 18, 4" : : "r"(val));
}

static inline unsigned long get_icdath(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 19, %0, 4" : "=r"(val));
    return val;
}

static inline void set_icdath(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 19, 4" : : "r"(val));
}

static inline unsigned long get_icctrl(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 24, %0, 4" : "=r"(val));
    return val;
}

static inline void set_icctrl(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 24, 4" : : "r"(val));
}

static inline unsigned long get_iccfg(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 26, %0, 4" : "=r"(val));
    return val;
}

static inline void set_iccfg(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 26, 4" : : "r"(val));
}

static inline unsigned long get_icerr(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 28, %0, 4" : "=r"(val));
    return val;
}

static inline void set_icerr(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 28, 4" : : "r"(val));
}

/* VIRTUALIZATION SUPPORT REGISTERS */
static inline unsigned long get_hvcfg(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 16, %0, 1" : "=r"(val));
    return val;
}

static inline void set_hvcfg(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 16, 1" : : "r"(val));
}

static inline unsigned long get_gmcfg(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 17, %0, 1" : "=r"(val));
    return val;
}

static inline void set_gmcfg(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 17, 1" : : "r"(val));
}

static inline unsigned long get_pswh(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 15, %0, 0" : "=r"(val));
    return val;
}

static inline void set_pswh(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 15, 0" : : "r"(val));
}

static inline unsigned long get_eipswh(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 18, %0, 0" : "=r"(val));
    return val;
}

static inline void set_eipswh(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 18, 0" : : "r"(val));
}

static inline unsigned long get_fepswh(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 19, %0, 0" : "=r"(val));
    return val;
}

static inline void set_fepswh(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 19, 0" : : "r"(val));
}

static inline unsigned long get_hvsb(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 20, %0, 1" : "=r"(val));
    return val;
}

static inline void set_hvsb(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 20, 1" : : "r"(val));
}

static inline unsigned long get_dbgen(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 0, %0, 3" : "=r"(val));
    return val;
}

static inline void set_dbgen(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 0, 3" : : "r"(val));
}

/* GUEST CONTEXT REGISTERS */
static inline unsigned long get_gmeipc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 0, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmeipc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 0, 9" : : "r"(val));
}

static inline unsigned long get_gmfepc(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 2, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmfepc(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 2, 9" : : "r"(val));
}

static inline unsigned long get_gmpsw(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 5, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmpsw(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 5, 9" : : "r"(val));
}

static inline unsigned long get_gmmea(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 6, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmmea(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 6, 9" : : "r"(val));
}

static inline unsigned long get_gmmei(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 8, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmmei(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 8, 9" : : "r"(val));
}

static inline unsigned long get_gmeiic(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 13, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmeiic(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 13, 9" : : "r"(val));
}

static inline unsigned long get_gmfeic(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 14, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmfeic(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 14, 9" : : "r"(val));
}

static inline unsigned long get_gmspid(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 16, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmspid(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 16, 9" : : "r"(val));
}

static inline unsigned long get_gmspidlist(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 17, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmspidlist(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 17, 9" : : "r"(val));
}

static inline unsigned long get_gmmpm(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 25, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmmpm(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 25, 9" : : "r"(val));
}

static inline unsigned long get_gmpeid(void)
{
    unsigned long val;
    __asm__ volatile ("stsr 30, %0, 9" : "=r"(val));
    return val;
}

static inline void set_gmpeid(unsigned long val)
{
    __asm__ volatile ("ldsr %0, 30, 9" : : "r"(val));
}

#endif /* __ASSEMBLER__ */
#endif /* __ARCH_SRS_H__ */