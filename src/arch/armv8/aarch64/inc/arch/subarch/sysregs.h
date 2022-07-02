/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef ARCH_PROFILE_SYSREGS_H
#define ARCH_PROFILE_SYSREGS_H

#include <bao.h>

#ifndef __ASSEMBLER__

#define SYSREG_GEN_ACCESSORS_NAME(reg, name) \
    static inline unsigned long sysreg_##reg##_read() {\
        unsigned long _temp;\
        asm volatile("mrs %0, " XSTR(name) "\n\r" : "=r"(_temp));\
        return _temp;\
    } \
    static inline void sysreg_##reg##_write(unsigned long val) {\
        asm volatile("msr " XSTR(name)  ", %0\n\r" ::"r"(val));\
    }

#define SYSREG_GEN_ACCESSORS(reg)  SYSREG_GEN_ACCESSORS_NAME(reg, reg)

SYSREG_GEN_ACCESSORS(esr_el2);
SYSREG_GEN_ACCESSORS(elr_el2);
SYSREG_GEN_ACCESSORS(far_el2);
SYSREG_GEN_ACCESSORS(hpfar_el2);
SYSREG_GEN_ACCESSORS(clidr_el1);
SYSREG_GEN_ACCESSORS(csselr_el1);
SYSREG_GEN_ACCESSORS(ccsidr_el1);
SYSREG_GEN_ACCESSORS(ccsidr2_el1);
SYSREG_GEN_ACCESSORS(ctr_el0);
SYSREG_GEN_ACCESSORS(mpidr_el1);
SYSREG_GEN_ACCESSORS(vmpidr_el2);
SYSREG_GEN_ACCESSORS(cntvoff_el2);
SYSREG_GEN_ACCESSORS(sctlr_el1);
SYSREG_GEN_ACCESSORS(cntkctl_el1);
SYSREG_GEN_ACCESSORS(pmcr_el0);
SYSREG_GEN_ACCESSORS(par_el1);
SYSREG_GEN_ACCESSORS(tcr_el2);
SYSREG_GEN_ACCESSORS(ttbr0_el2);
SYSREG_GEN_ACCESSORS(mair_el2);
SYSREG_GEN_ACCESSORS(cptr_el2);
SYSREG_GEN_ACCESSORS(hcr_el2);
SYSREG_GEN_ACCESSORS(vtcr_el2);
SYSREG_GEN_ACCESSORS(vttbr_el2);
SYSREG_GEN_ACCESSORS(id_aa64mmfr0_el1);
SYSREG_GEN_ACCESSORS(tpidr_el2);
SYSREG_GEN_ACCESSORS_NAME(ich_misr_el2, S3_4_C12_C11_2);
SYSREG_GEN_ACCESSORS_NAME(ich_eisr_el2, S3_4_C12_C11_3);
SYSREG_GEN_ACCESSORS_NAME(ich_elrsr_el2, S3_4_C12_C11_5);
SYSREG_GEN_ACCESSORS_NAME(icc_iar1_el1, S3_0_C12_C12_0);
SYSREG_GEN_ACCESSORS_NAME(icc_eoir1_el1, S3_0_C12_C12_1);
SYSREG_GEN_ACCESSORS_NAME(icc_dir_el1, S3_0_C12_C11_1);
SYSREG_GEN_ACCESSORS_NAME(ich_vtr_el2, S3_4_C12_C11_1);
SYSREG_GEN_ACCESSORS_NAME(icc_sre_el2, S3_0_C12_C12_5);
SYSREG_GEN_ACCESSORS_NAME(icc_pmr_el1, S3_0_C4_C6_0);
SYSREG_GEN_ACCESSORS_NAME(icc_bpr1_el1, S3_0_C12_C8_3);
SYSREG_GEN_ACCESSORS_NAME(icc_ctlr_el1, S3_0_C12_C12_4);
SYSREG_GEN_ACCESSORS_NAME(icc_igrpen1_el1, S3_0_C12_C12_7);
SYSREG_GEN_ACCESSORS_NAME(ich_hcr_el2, S3_4_C12_C11_0);
SYSREG_GEN_ACCESSORS_NAME(icc_sgi1r_el1, S3_0_C12_C11_5);
SYSREG_GEN_ACCESSORS_NAME(ich_lr0_el2, S3_4_C12_C12_0);
SYSREG_GEN_ACCESSORS_NAME(ich_lr1_el2, S3_4_C12_C12_1);
SYSREG_GEN_ACCESSORS_NAME(ich_lr2_el2, S3_4_C12_C12_2);
SYSREG_GEN_ACCESSORS_NAME(ich_lr3_el2, S3_4_C12_C12_3);
SYSREG_GEN_ACCESSORS_NAME(ich_lr4_el2, S3_4_C12_C12_4);
SYSREG_GEN_ACCESSORS_NAME(ich_lr5_el2, S3_4_C12_C12_5);
SYSREG_GEN_ACCESSORS_NAME(ich_lr6_el2, S3_4_C12_C12_6);
SYSREG_GEN_ACCESSORS_NAME(ich_lr7_el2, S3_4_C12_C12_7);
SYSREG_GEN_ACCESSORS_NAME(ich_lr8_el2, S3_4_C12_C13_0);
SYSREG_GEN_ACCESSORS_NAME(ich_lr9_el2, S3_4_C12_C13_1);
SYSREG_GEN_ACCESSORS_NAME(ich_lr10_el2, S3_4_C12_C13_2);
SYSREG_GEN_ACCESSORS_NAME(ich_lr11_el2, S3_4_C12_C13_3);
SYSREG_GEN_ACCESSORS_NAME(ich_lr12_el2, S3_4_C12_C13_4);
SYSREG_GEN_ACCESSORS_NAME(ich_lr13_el2, S3_4_C12_C13_5);
SYSREG_GEN_ACCESSORS_NAME(ich_lr14_el2, S3_4_C12_C13_6);
SYSREG_GEN_ACCESSORS_NAME(ich_lr15_el2, S3_4_C12_C13_7);

static inline void arm_dc_civac(vaddr_t cache_addr) {
    asm volatile ("dc civac, %0\n\t" :: "r"(cache_addr));
}

static inline void arm_at_s1e2w(vaddr_t vaddr) {
     asm volatile("at s1e2w, %0" ::"r"(vaddr));
}

static inline void arm_at_s12e1w(vaddr_t vaddr) {
     asm volatile("at s12e1w, %0" ::"r"(vaddr));
}

#endif /* |__ASSEMBLER__ */

#endif /* __ARCH_SYSREGS_H__ */
