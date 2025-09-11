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

static inline uint8_t emul_arch_bwop_emul_acc(struct emul_access_arch* acc, uint8_t cur_val)
{
    unsigned long psw = srs_gmpsw_read();
    if (cur_val & acc->bit) {
        srs_gmpsw_write(psw & ~PSW_Z);
    } else {
        srs_gmpsw_write(psw | PSW_Z);
    }
    uint8_t val = 0;
    switch (acc->bwop) {
        case EMUL_ARCH_BWOP_SET1:
            val = (uint8_t)(cur_val | acc->bit);
            ;
            break;
        case EMUL_ARCH_BWOP_NOT1:
            val = (uint8_t)(cur_val ^ acc->bit);
            ;
            break;
        case EMUL_ARCH_BWOP_CLR1:
            val = (uint8_t)(cur_val & (uint8_t)~acc->bit);
            ;
            break;
            /* TST1 only modifies the PSW.Z flag */
        default:
            ERROR("Invalid bitwise operation\n");
            break;
    }

    return val;
}

#endif /* __ASSEMBLER__ */
#endif /* __ARCH_EMUL_H__ */
