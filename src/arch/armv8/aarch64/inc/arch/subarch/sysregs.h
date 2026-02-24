/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_PROFILE_SYSREGS_H
#define ARCH_PROFILE_SYSREGS_H

#include <bao.h>

#define mpuir_el2       S3_4_C0_C0_4
#define prselr_el2      S3_4_C6_C2_1
#define prbar_el2       S3_4_C6_C8_0
#define prlar_el2       S3_4_C6_C8_1
#define prenr_el2       S3_4_C6_C1_1
#define ich_misr_el2    S3_4_C12_C11_2
#define ich_eisr_el2    S3_4_C12_C11_3
#define ich_elrsr_el2   S3_4_C12_C11_5
#define icc_iar1_el1    S3_0_C12_C12_0
#define icc_eoir1_el1   S3_0_C12_C12_1
#define icc_dir_el1     S3_0_C12_C11_1
#define ich_vtr_el2     S3_4_C12_C11_1
#define icc_sre_el2     S3_4_C12_C9_5
#define icc_pmr_el1     S3_0_C4_C6_0
#define icc_bpr1_el1    S3_0_C12_C12_3
#define icc_ctlr_el1    S3_0_C12_C12_4
#define icc_igrpen1_el1 S3_0_C12_C12_7
#define ich_hcr_el2     S3_4_C12_C11_0
#define icc_sgi1r_el1   S3_0_C12_C11_5
#define ich_lr0_el2     S3_4_C12_C12_0
#define ich_lr1_el2     S3_4_C12_C12_1
#define ich_lr2_el2     S3_4_C12_C12_2
#define ich_lr3_el2     S3_4_C12_C12_3
#define ich_lr4_el2     S3_4_C12_C12_4
#define ich_lr5_el2     S3_4_C12_C12_5
#define ich_lr6_el2     S3_4_C12_C12_6
#define ich_lr7_el2     S3_4_C12_C12_7
#define ich_lr8_el2     S3_4_C12_C13_0
#define ich_lr9_el2     S3_4_C12_C13_1
#define ich_lr10_el2    S3_4_C12_C13_2
#define ich_lr11_el2    S3_4_C12_C13_3
#define ich_lr12_el2    S3_4_C12_C13_4
#define ich_lr13_el2    S3_4_C12_C13_5
#define ich_lr14_el2    S3_4_C12_C13_6
#define ich_lr15_el2    S3_4_C12_C13_7

#ifndef __ASSEMBLER__

#define SYSREG_GEN_ACCESSORS_NAME(reg, name)                          \
    static inline unsigned long sysreg##reg##read(void)               \
    {                                                                 \
        unsigned long _temp;                                          \
        __asm__ volatile("mrs %0, " XSTR(name) "\n\r" : "=r"(_temp)); \
        return _temp;                                                 \
    }                                                                 \
    static inline void sysreg##reg##write(unsigned long val)          \
    {                                                                 \
        __asm__ volatile("msr " XSTR(name) ", %0\n\r" ::"r"(val));    \
    }

#define SYSREG_GEN_ACCESSORS(reg) SYSREG_GEN_ACCESSORS_NAME(_##reg##_, reg)

SYSREG_GEN_ACCESSORS(esr_el2)
SYSREG_GEN_ACCESSORS(elr_el2)
SYSREG_GEN_ACCESSORS(far_el2)
SYSREG_GEN_ACCESSORS(hpfar_el2)
SYSREG_GEN_ACCESSORS(clidr_el1)
SYSREG_GEN_ACCESSORS(csselr_el1)
SYSREG_GEN_ACCESSORS(ccsidr_el1)
SYSREG_GEN_ACCESSORS(ccsidr2_el1)
SYSREG_GEN_ACCESSORS(ctr_el0)
SYSREG_GEN_ACCESSORS(midr_el1)
SYSREG_GEN_ACCESSORS(mpidr_el1)
SYSREG_GEN_ACCESSORS(vmpidr_el2)
SYSREG_GEN_ACCESSORS(cntvoff_el2)
SYSREG_GEN_ACCESSORS(sctlr_el1)
SYSREG_GEN_ACCESSORS(cntkctl_el1)
SYSREG_GEN_ACCESSORS(cntfrq_el0)
SYSREG_GEN_ACCESSORS(pmcr_el0)
SYSREG_GEN_ACCESSORS(par_el1)
SYSREG_GEN_ACCESSORS(tcr_el2)
SYSREG_GEN_ACCESSORS(ttbr0_el2)
SYSREG_GEN_ACCESSORS(mair_el2)
SYSREG_GEN_ACCESSORS(cptr_el2)
SYSREG_GEN_ACCESSORS(hcr_el2)
SYSREG_GEN_ACCESSORS(vtcr_el2)
SYSREG_GEN_ACCESSORS(vttbr_el2)
SYSREG_GEN_ACCESSORS(id_aa64mmfr0_el1)
SYSREG_GEN_ACCESSORS(tpidr_el2)
SYSREG_GEN_ACCESSORS(vsctlr_el2)
SYSREG_GEN_ACCESSORS(sctlr_el2)
SYSREG_GEN_ACCESSORS(mpuir_el2)
SYSREG_GEN_ACCESSORS(prselr_el2)
SYSREG_GEN_ACCESSORS(prbar_el2)
SYSREG_GEN_ACCESSORS(prlar_el2)
SYSREG_GEN_ACCESSORS(prenr_el2)
SYSREG_GEN_ACCESSORS(ich_misr_el2)
SYSREG_GEN_ACCESSORS(ich_eisr_el2)
SYSREG_GEN_ACCESSORS(ich_elrsr_el2)
SYSREG_GEN_ACCESSORS(icc_iar1_el1)
SYSREG_GEN_ACCESSORS(icc_eoir1_el1)
SYSREG_GEN_ACCESSORS(icc_dir_el1)
SYSREG_GEN_ACCESSORS(ich_vtr_el2)
SYSREG_GEN_ACCESSORS(icc_sre_el2)
SYSREG_GEN_ACCESSORS(icc_pmr_el1)
SYSREG_GEN_ACCESSORS(icc_bpr1_el1)
SYSREG_GEN_ACCESSORS(icc_ctlr_el1)
SYSREG_GEN_ACCESSORS(icc_igrpen1_el1)
SYSREG_GEN_ACCESSORS(ich_hcr_el2)
SYSREG_GEN_ACCESSORS(icc_sgi1r_el1)
SYSREG_GEN_ACCESSORS(ich_lr0_el2)
SYSREG_GEN_ACCESSORS(ich_lr1_el2)
SYSREG_GEN_ACCESSORS(ich_lr2_el2)
SYSREG_GEN_ACCESSORS(ich_lr3_el2)
SYSREG_GEN_ACCESSORS(ich_lr4_el2)
SYSREG_GEN_ACCESSORS(ich_lr5_el2)
SYSREG_GEN_ACCESSORS(ich_lr6_el2)
SYSREG_GEN_ACCESSORS(ich_lr7_el2)
SYSREG_GEN_ACCESSORS(ich_lr8_el2)
SYSREG_GEN_ACCESSORS(ich_lr9_el2)
SYSREG_GEN_ACCESSORS(ich_lr10_el2)
SYSREG_GEN_ACCESSORS(ich_lr11_el2)
SYSREG_GEN_ACCESSORS(ich_lr12_el2)
SYSREG_GEN_ACCESSORS(ich_lr13_el2)
SYSREG_GEN_ACCESSORS(ich_lr14_el2)
SYSREG_GEN_ACCESSORS(ich_lr15_el2)

static inline void arm_dc_civac(vaddr_t cache_addr)
{
    __asm__ volatile("dc civac, %0\n\t" ::"r"(cache_addr));
}

static inline void arm_at_s1e2w(vaddr_t vaddr)
{
    __asm__ volatile("at s1e2w, %0" ::"r"(vaddr));
}

static inline void arm_at_s12e1w(vaddr_t vaddr)
{
    __asm__ volatile("at s12e1w, %0" ::"r"(vaddr));
}

static inline void arm_tlbi_alle2is(void)
{
    __asm__ volatile("tlbi alle2is");
}

static inline void arm_tlbi_vmalls12e1is(void)
{
    __asm__ volatile("tlbi vmalls12e1is");
}

static inline void arm_tlbi_vae2is(vaddr_t vaddr)
{
    __asm__ volatile("tlbi vae2is, %0" ::"r"(vaddr >> 12));
}

static inline void arm_tlbi_ipas2e1is(vaddr_t vaddr)
{
    __asm__ volatile("tlbi ipas2e1is, %0" ::"r"(vaddr >> 12));
}

#endif /* |__ASSEMBLER__ */

#endif /* __ARCH_SYSREGS_H__ */
