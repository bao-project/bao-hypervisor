/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_PROFILE_SYSREGS_H
#define ARCH_PROFILE_SYSREGS_H

#include <bao.h>

#ifndef __ASSEMBLER__

#define SYSREG_GEN_ACCESSORS(name, op1, crn, crm, op2)                                            \
    static inline unsigned long sysreg_##name##_read(void)                                        \
    {                                                                                             \
        unsigned long _temp;                                                                      \
        __asm__ volatile("mrc p15, " #op1 ", %0, " #crn ", " #crm ", %1\n\r" : "=r"(_temp)        \
                         : "i"(op2));                                                             \
        return _temp;                                                                             \
    }                                                                                             \
    static inline void sysreg_##name##_write(unsigned long val)                                   \
    {                                                                                             \
        __asm__ volatile("mcr p15, " #op1 ", %0, " #crn ", " #crm ", " #op2 "\n\r" : : "r"(val)); \
    }

#define SYSREG_GEN_ACCESSORS_BANKED(name, reg)                       \
    static inline unsigned long sysreg_##name##_read(void)           \
    {                                                                \
        unsigned long _temp;                                         \
        __asm__ volatile("mrs %0, " XSTR(reg) "\n\r" : "=r"(_temp)); \
        return _temp;                                                \
    }                                                                \
    static inline void sysreg_##name##_write(unsigned long val)      \
    {                                                                \
        __asm__ volatile("msr " XSTR(reg) ", %0\n\r" : : "r"(val));  \
    }

#define SYSREG_GEN_ACCESSORS_64(reg, op1, crm)                                                    \
    static inline unsigned long long sysreg_##reg##_read(void)                                    \
    {                                                                                             \
        unsigned long long _temp, _tempH;                                                         \
        __asm__ volatile("mrrc p15, " #op1 ", %0, %1, " #crm "\n\r" : "=r"(_temp), "=r"(_tempH)); \
        return ((_tempH << 32) | ((unsigned long)_temp));                                         \
    }                                                                                             \
    static inline void sysreg_##reg##_write(unsigned long long val)                               \
    {                                                                                             \
        unsigned long long _tempH = (val >> 32);                                                  \
        __asm__ volatile("mcrr p15, " #op1 ", %0, %1, " #crm "\n\r" : : "r"(val), "r"(_tempH));   \
    }

#define SYSREG_GEN_ACCESSORS_MERGE(reg, reg1, reg2)                                         \
    static inline unsigned long long sysreg_##reg##_read(void)                              \
    {                                                                                       \
        return ((unsigned long long)sysreg_##reg2##_read() << 32) | sysreg_##reg1##_read(); \
    }                                                                                       \
    static inline void sysreg_##reg##_write(unsigned long long val)                         \
    {                                                                                       \
        sysreg_##reg1##_write((unsigned long)val);                                          \
        sysreg_##reg2##_write((unsigned long)(val >> 32));                                  \
    }

/**
 * We give aarch32 registers the same name as aarch64's to which they are architecturally mapped
 * to, so that we can use the same name in common code.
 */
SYSREG_GEN_ACCESSORS(esr_el2, 4, c5, c2, 0) // hsr
SYSREG_GEN_ACCESSORS_BANKED(elr_el2, elr_hyp)
SYSREG_GEN_ACCESSORS(far_el2, 4, c6, c0, 0) // hdfar
SYSREG_GEN_ACCESSORS(hpfar_el2, 4, c6, c0, 4)
SYSREG_GEN_ACCESSORS(clidr_el1, 1, c0, c0, 1)
SYSREG_GEN_ACCESSORS(csselr_el1, 2, c0, c0, 0)
SYSREG_GEN_ACCESSORS(ctr_el0, 0, c0, c0, 1)
SYSREG_GEN_ACCESSORS(mpidr_el1, 0, c0, c0, 5)
SYSREG_GEN_ACCESSORS(midr_el1, 0, c0, c0, 0)
SYSREG_GEN_ACCESSORS(vmpidr_el2, 4, c0, c0, 5)
SYSREG_GEN_ACCESSORS_64(cntvoff_el2, 4, c14)
SYSREG_GEN_ACCESSORS(sctlr_el1, 0, c1, c0, 0)
SYSREG_GEN_ACCESSORS(cntkctl_el1, 0, c14, c1, 0)
SYSREG_GEN_ACCESSORS(pmcr_el0, 0, c9, c12, 0)
SYSREG_GEN_ACCESSORS_64(par_el1, 0, c7)
SYSREG_GEN_ACCESSORS(tcr_el2, 4, c2, c0, 2)    // htcr
SYSREG_GEN_ACCESSORS_64(ttbr0_el2, 4, c2)      // httbr
SYSREG_GEN_ACCESSORS(cptr_el2, 4, c1, c1, 2)   // hcptr
SYSREG_GEN_ACCESSORS(vtcr_el2, 4, c2, c1, 2)
SYSREG_GEN_ACCESSORS_64(vttbr_el2, 6, c2)
SYSREG_GEN_ACCESSORS(tpidr_el2, 4, c13, c0, 2) // htpidr
SYSREG_GEN_ACCESSORS(ccsidr_el1, 1, c0, c0, 0)
SYSREG_GEN_ACCESSORS(ccsidr2, 1, c0, c0, 2)
SYSREG_GEN_ACCESSORS(hmair0, 4, c10, c2, 0)
SYSREG_GEN_ACCESSORS(hmair1, 4, c10, c2, 1)
SYSREG_GEN_ACCESSORS_MERGE(mair_el2, hmair0, hmair1)
SYSREG_GEN_ACCESSORS(hcr, 4, c1, c1, 0)
SYSREG_GEN_ACCESSORS(hcr2, 4, c6, c0, 0)
SYSREG_GEN_ACCESSORS_MERGE(hcr_el2, hcr, hcr2)
SYSREG_GEN_ACCESSORS(cntfrq_el0, 0, c14, c0, 0)

SYSREG_GEN_ACCESSORS(mpuir_el2, 4, c0, c0, 4)
SYSREG_GEN_ACCESSORS(prselr_el2, 4, c6, c2, 1)
SYSREG_GEN_ACCESSORS(prbar_el2, 4, c6, c3, 0)
SYSREG_GEN_ACCESSORS(prlar_el2, 4, c6, c3, 1)
SYSREG_GEN_ACCESSORS(prenr_el2, 4, c6, c1, 1)

SYSREG_GEN_ACCESSORS(ich_misr_el2, 4, c12, c11, 2)
SYSREG_GEN_ACCESSORS(ich_eisr_el2, 4, c12, c11, 3)
SYSREG_GEN_ACCESSORS(ich_elrsr_el2, 4, c12, c11, 5)
SYSREG_GEN_ACCESSORS(icc_iar1_el1, 0, c12, c12, 0)
SYSREG_GEN_ACCESSORS(icc_eoir1_el1, 0, c12, c12, 1)
SYSREG_GEN_ACCESSORS(icc_dir_el1, 0, c12, c11, 1)
SYSREG_GEN_ACCESSORS(ich_vtr_el2, 4, c12, c11, 1)
SYSREG_GEN_ACCESSORS(icc_sre_el2, 4, c12, c9, 5)
SYSREG_GEN_ACCESSORS(icc_pmr_el1, 0, c4, c6, 0)
SYSREG_GEN_ACCESSORS(icc_bpr1_el1, 0, c12, c12, 3)
SYSREG_GEN_ACCESSORS(icc_ctlr_el1, 0, c12, c12, 4)
SYSREG_GEN_ACCESSORS(icc_igrpen1_el1, 0, c12, c12, 7)
SYSREG_GEN_ACCESSORS(ich_hcr_el2, 4, c12, c11, 0)
SYSREG_GEN_ACCESSORS_64(icc_sgi1r_el1, 0, c12)

SYSREG_GEN_ACCESSORS(vsctlr_el2, 4, c2, c0, 0)
SYSREG_GEN_ACCESSORS(sctlr_el2, 4, c1, c0, 0)

#define SYSREG_GEN_GIC_LR(n, crn1, crn2, op2)           \
    SYSREG_GEN_ACCESSORS(ich_lr##n, 4, c12, crn1, op2)  \
    SYSREG_GEN_ACCESSORS(ich_lrc##n, 4, c12, crn2, op2) \
    SYSREG_GEN_ACCESSORS_MERGE(ich_lr##n##_el2, ich_lr##n, ich_lrc##n)

SYSREG_GEN_GIC_LR(0, c12, c14, 0)
SYSREG_GEN_GIC_LR(1, c12, c14, 1)
SYSREG_GEN_GIC_LR(2, c12, c14, 2)
SYSREG_GEN_GIC_LR(3, c12, c14, 3)
SYSREG_GEN_GIC_LR(4, c12, c14, 4)
SYSREG_GEN_GIC_LR(5, c12, c14, 5)
SYSREG_GEN_GIC_LR(6, c12, c14, 6)
SYSREG_GEN_GIC_LR(7, c12, c14, 7)
SYSREG_GEN_GIC_LR(8, c13, c15, 0)
SYSREG_GEN_GIC_LR(9, c13, c15, 1)
SYSREG_GEN_GIC_LR(10, c13, c15, 2)
SYSREG_GEN_GIC_LR(11, c13, c15, 3)
SYSREG_GEN_GIC_LR(12, c13, c15, 4)
SYSREG_GEN_GIC_LR(13, c13, c15, 5)
SYSREG_GEN_GIC_LR(14, c13, c15, 6)
SYSREG_GEN_GIC_LR(15, c13, c15, 7)

SYSREG_GEN_ACCESSORS_BANKED(spsr_hyp, spsr_hyp)
SYSREG_GEN_ACCESSORS_BANKED(sp_usr, sp_usr)
SYSREG_GEN_ACCESSORS_BANKED(sp_irq, sp_irq)
SYSREG_GEN_ACCESSORS_BANKED(sp_fiq, sp_fiq)
SYSREG_GEN_ACCESSORS_BANKED(sp_svc, sp_svc)
SYSREG_GEN_ACCESSORS_BANKED(sp_abt, sp_abt)
SYSREG_GEN_ACCESSORS_BANKED(sp_und, sp_und)
SYSREG_GEN_ACCESSORS_BANKED(lr_usr, lr_usr)
SYSREG_GEN_ACCESSORS_BANKED(lr_irq, lr_irq)
SYSREG_GEN_ACCESSORS_BANKED(lr_fiq, lr_fiq)
SYSREG_GEN_ACCESSORS_BANKED(lr_svc, lr_svc)
SYSREG_GEN_ACCESSORS_BANKED(lr_abt, lr_abt)
SYSREG_GEN_ACCESSORS_BANKED(lr_und, lr_und)
SYSREG_GEN_ACCESSORS_BANKED(r8_fiq, r8_fiq)
SYSREG_GEN_ACCESSORS_BANKED(r9_fiq, r9_fiq)
SYSREG_GEN_ACCESSORS_BANKED(r10_fiq, r10_fiq)
SYSREG_GEN_ACCESSORS_BANKED(r11_fiq, r11_fiq)
SYSREG_GEN_ACCESSORS_BANKED(r12_fiq, r12_fiq)

SYSREG_GEN_ACCESSORS(dccivac, 0, c7, c14, 1)
static inline void arm_dc_civac(vaddr_t cache_addr)
{
    sysreg_dccivac_write(cache_addr);
}

static inline void arm_at_s1e2w(vaddr_t vaddr)
{
    __asm__ volatile("mcr p15, 4, %0, c7, c8, 1" ::"r"(vaddr)); // ats1hw
}

static inline void arm_at_s12e1w(vaddr_t vaddr)
{
    __asm__ volatile("mcr p15, 0, %0, c7, c8, 5" ::"r"(vaddr)); // ats12nsopw
}

static inline void arm_tlbi_alle2is(void)
{
    __asm__ volatile("mcr p15, 4, r0, c8, c7, 0");
}

static inline void arm_tlbi_vmalls12e1is(void)
{
    __asm__ volatile("mcr p15, 0, r0, c8, c7, 0");
}

static inline void arm_tlbi_vae2is(vaddr_t vaddr)
{
    __asm__ volatile("mcr p15, 4, %0, c8, c7, 1" ::"r"(vaddr));
}

static inline void arm_tlbi_ipas2e1is(vaddr_t vaddr)
{
    __asm__ volatile("mcr p15, 4, %0, c8, c0, 1" ::"r"(vaddr >> 12));
}

#endif /* |__ASSEMBLER__ */

#endif /* ARCH_PROFILE_SYSREGS_H */
