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

#ifndef __BIT_H__
#define __BIT_H__

#include <bao.h>

/**
 * The extra shift is because both arm and riscv logical shift instructions
 * support a maximum of machine word length minus one bit shits. This covers
 * the corner case of runtime full machine word length masks with the cost of
 * an extra shift instruction. For static masks, there should be no extra costs.
 */
#define BIT32_MASK(OFF, LEN) ((((UINT32_C(1)<<((LEN)-1))<<1)-1)<<(OFF))
#define BIT64_MASK(OFF, LEN) ((((UINT64_C(1)<<((LEN)-1))<<1)-1)<<(OFF))
#define BIT_MASK(OFF, LEN) (((((1UL)<<((LEN)-1))<<1)-1)<<(OFF))

#ifndef __ASSEMBLER__

#define BIT_OPS_GEN(PRE, TYPE, LIT, MASK) \
    static inline TYPE PRE ## _get(TYPE word, size_t off)\
    {\
        return word & ((LIT) << off);\
    }\
    static inline TYPE PRE ## _set(TYPE word, size_t off)\
    {\
        return word |= ((LIT) << off);\
    }\
    static inline TYPE PRE ## _clear(TYPE word, size_t off)\
    {\
        return word &= ~((LIT) << off);\
    }\
    static inline TYPE PRE ## _extract(TYPE word, size_t off, size_t len)\
    {\
        return (word >> off) & MASK(0, len);\
    }\
    static inline TYPE PRE ## _insert(TYPE word, TYPE val, size_t off,\
                                    size_t len)\
    {\
        return (~MASK(off, len) & word) | ((MASK(0, len) & val) << off);\
    }\

BIT_OPS_GEN(bit32, uint32_t, UINT32_C(1), BIT32_MASK);
BIT_OPS_GEN(bit64, uint64_t, UINT64_C(1), BIT64_MASK);
BIT_OPS_GEN(bit, unsigned long, (1UL), BIT_MASK);

#endif /* |__ASSEMBLER__ */

#endif /* __BIT_H__ */
