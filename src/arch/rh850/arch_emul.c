/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <emul.h>
#include <srs.h>
#include <vm.h>
#include <cpu.h>

unsigned long bitwise_op_get_acc_bitop_mask(struct emul_access* acc)
{
    size_t addr_off = acc->addr & 0x1UL;
    return acc->arch.byte_mask << (addr_off * 8);
}

void bitwise_op_set_gmpse(unsigned long cur_val, unsigned long bitop_mask)
{
    unsigned long psw = get_gmpsw();
    if (cur_val & bitop_mask) {
        set_gmpsw(psw & ~PSW_Z);
    } else {
        set_gmpsw(psw | PSW_Z);
    }
}

unsigned long bitwise_op_set_val(struct emul_access* acc, unsigned long cur_val,
    unsigned long bitop_mask)
{
    unsigned long val = 0;
    switch (acc->arch.op) {
        case BWOP_SET1:
            val = cur_val | bitop_mask;
            break;
        case BWOP_NOT1:
            val = cur_val & bitop_mask ? (cur_val & ~bitop_mask) : (cur_val | bitop_mask);
            break;
        case BWOP_CLR1:
            val = cur_val & ~bitop_mask;
            break;
            /* TST1 only modifies the PSW.Z flag */
        default:
            ERROR("Invalid bitwise operation\n");
            break;
    }

    return val;
}
