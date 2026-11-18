/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_INSTRUCTIONS_H
#define ARCH_INSTRUCTIONS_H

#include <bao.h>

/**
 * Read a guest halfword with hlvx.hu, returning false if it faults. A fault
 * clobbers the trap CSRs.
 */
static inline bool hlvxhu(uintptr_t addr, uint16_t* value)
{
    unsigned long val;
    unsigned long ok = 0;
    unsigned long stvec;

    /* A fault traps to label 1, skipping the update of ok. */
    __asm__ volatile("la    %[stvec], 1f\n\t"
                     "csrrw %[stvec], stvec, %[stvec]\n\t"
                     ".insn r 0x73, 0x4, 0x32, %[val], %[addr], x3\n\t"
                     "li    %[ok], 1\n\t"
                     ".balign 4\n"
                     "1:\n\t"
                     "csrw  stvec, %[stvec]\n\t"
                     : [val] "=r"(val), [ok] "+r"(ok), [stvec] "=&r"(stvec) : [addr] "r"(addr)
                     : "memory");

    *value = (uint16_t)val;
    return ok != 0;
}

#endif /* ARCH_INSTRUCTIONS_H */
