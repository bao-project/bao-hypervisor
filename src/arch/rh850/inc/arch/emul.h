/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_EMUL_H__
#define __ARCH_EMUL_H__

#ifndef __ASSEMBLER__

#include <bao.h>
#include <srs.h>

/* The order of the operations can NOT be modified */
enum emul_arch_bwop {
    EMUL_ARCH_BWOP_NO,
    EMUL_ARCH_BWOP_SET1,
    EMUL_ARCH_BWOP_NOT1,
    EMUL_ARCH_BWOP_CLR1,
    EMUL_ARCH_BWOP_TST1
};

struct emul_access_arch {
    enum emul_arch_bwop bwop;
    uint8_t bit;
};

static inline bool emul_arch_is_bwop(struct emul_access_arch* acc)
{
    return acc->bwop != EMUL_ARCH_BWOP_NO;
}

/**
 * Emulate a bit manipulation instruction (set1, not1, clr1 or tst1) on the byte at reg. All four
 * set PSW.Z from the bit's current value; only the first three store a result. tst1 must not
 * store: on hardware it only reads, and writing the byte back would overwrite a bit the hardware
 * changed between the read and the write, such as an interrupt request flag.
 */
static inline void emul_arch_bwop_emul_acc(struct emul_access_arch* acc, volatile uint8_t* reg)
{
    unsigned long psw = srs_gmpsw_read();
    uint8_t bitmask = (uint8_t)(1UL << acc->bit);
    uint8_t cur_val = *reg;

    if (cur_val & bitmask) {
        srs_gmpsw_write(psw & ~PSW_Z);
    } else {
        srs_gmpsw_write(psw | PSW_Z);
    }

    switch (acc->bwop) {
        case EMUL_ARCH_BWOP_SET1:
            *reg = (uint8_t)(cur_val | bitmask);
            break;
        case EMUL_ARCH_BWOP_NOT1:
            *reg = (uint8_t)(cur_val ^ bitmask);
            break;
        case EMUL_ARCH_BWOP_CLR1:
            *reg = (uint8_t)(cur_val & (uint8_t)~bitmask);
            break;
        case EMUL_ARCH_BWOP_TST1:
            break;
        default:
            ERROR("Invalid bitwise operation\n");
            break;
    }
}

#endif /* __ASSEMBLER__ */
#endif /* __ARCH_EMUL_H__ */
