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

#ifndef __GICV3_H__
#define __GICV3_H__

#include <arch/gic.h>

static inline uint64_t gich_read_lr(size_t i)
{
    if (i >= NUM_LRS) {
        ERROR("gic: trying to read inexistent list register");
    }

    switch (i) {
        case 0: return MRS(ICH_LR0_EL2);
        case 1: return MRS(ICH_LR1_EL2);
        case 2: return MRS(ICH_LR2_EL2);
        case 3: return MRS(ICH_LR3_EL2);
        case 4: return MRS(ICH_LR4_EL2);
        case 5: return MRS(ICH_LR5_EL2);
        case 6: return MRS(ICH_LR6_EL2);
        case 7: return MRS(ICH_LR7_EL2);
        case 8: return MRS(ICH_LR8_EL2);
        case 9: return MRS(ICH_LR9_EL2);
        case 10: return MRS(ICH_LR10_EL2);
        case 11: return MRS(ICH_LR11_EL2);
        case 12: return MRS(ICH_LR12_EL2);
        case 13: return MRS(ICH_LR13_EL2);
        case 14: return MRS(ICH_LR14_EL2);
        case 15: return MRS(ICH_LR15_EL2);
        default: return 0;
    }
}

static inline void gich_write_lr(size_t i, uint64_t val)
{
    if (i >= NUM_LRS) {
        ERROR("gic: trying to write inexistent list register");
    }

    switch (i) {
        case 0: MSR(ICH_LR0_EL2, val);   break;        
        case 1: MSR(ICH_LR1_EL2, val);   break;         
        case 2: MSR(ICH_LR2_EL2, val);   break;         
        case 3: MSR(ICH_LR3_EL2, val);   break;         
        case 4: MSR(ICH_LR4_EL2, val);   break;         
        case 5: MSR(ICH_LR5_EL2, val);   break;         
        case 6: MSR(ICH_LR6_EL2, val);   break;         
        case 7: MSR(ICH_LR7_EL2, val);   break;         
        case 8: MSR(ICH_LR8_EL2, val);   break;         
        case 9: MSR(ICH_LR9_EL2, val);   break;         
        case 10: MSR(ICH_LR10_EL2, val); break;           
        case 11: MSR(ICH_LR11_EL2, val); break;           
        case 12: MSR(ICH_LR12_EL2, val); break;           
        case 13: MSR(ICH_LR13_EL2, val); break;           
        case 14: MSR(ICH_LR14_EL2, val); break;           
        case 15: MSR(ICH_LR15_EL2, val); break;
    }
}

static inline uint32_t gich_get_hcr()
{
    return MRS(ICH_HCR_EL2);
}

static inline void gich_set_hcr(uint32_t hcr)
{
    MSR(ICH_HCR_EL2, hcr);
}

static inline uint32_t gich_get_misr()
{
    return MRS(ICH_MISR_EL2);
}

static inline uint64_t gich_get_eisr()
{
    return MRS(ICH_EISR_EL2);
}

static inline uint64_t gich_get_elrsr()
{
    return MRS(ICH_ELRSR_EL2);
}

static inline uint32_t gicc_iar() {
    return MRS(ICC_IAR1_EL1);
}

static inline void gicc_eoir(uint32_t eoir) {
    MSR(ICC_EOIR1_EL1, eoir);
}

static inline void gicc_dir(uint32_t dir) {
    MSR(ICC_DIR_EL1, dir);
}

#endif /* __GICV3_H__ */
