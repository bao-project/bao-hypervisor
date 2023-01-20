/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __GICV2_H__
#define __GICV2_H__

#include <arch/gic.h>

static inline uint64_t gich_read_lr(size_t i)
{
    if (i < NUM_LRS) {
        return gich->LR[i];
    } else {
        ERROR("gic: trying to read inexistent list register");
    }
}

static inline void gich_write_lr(size_t i, uint64_t val)
{
    if (i < NUM_LRS) {
        gich->LR[i] = val;
    } else {
        ERROR("gic: trying to write inexistent list register");
    }
}

static inline uint32_t gich_get_hcr()
{
    return gich->HCR;
}

static inline void gich_set_hcr(uint32_t hcr)
{
    gich->HCR = hcr;
}

static inline uint32_t gich_get_misr()
{
    return gich->MISR;
}

static inline uint64_t gich_get_eisr()
{
    uint64_t eisr = gich->EISR[0];
    if (NUM_LRS > 32) eisr |= (((uint64_t)gich->EISR[1] << 32));
    return eisr;
}

static inline uint64_t gich_get_elrsr()
{
    uint64_t elsr = gich->ELSR[0];
    if (NUM_LRS > 32) elsr |= (((uint64_t)gich->ELSR[1] << 32));
    return elsr;
}

static inline uint32_t gicc_iar() {
    return gicc->IAR;
}

static inline void gicc_eoir(uint32_t eoir) {
     gicc->EOIR = eoir;
}

static inline void gicc_dir(uint32_t dir) {
     gicc->DIR = dir;
}

#endif /* __GICV2_H__ */
