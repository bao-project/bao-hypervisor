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
#define BIT_MASK(OFF, LEN) ((((1ULL<<((LEN)-1))<<1)-1)<<(OFF))

#ifndef __ASSEMBLER__

size_t bit_ctz(uint64_t n);
size_t bit_clz(uint64_t n);

static inline uint64_t bit_get(uint64_t word, uint64_t off)
{
    return word & (1UL << off);
}

static inline uint64_t bit_set(uint64_t word, uint64_t off)
{
    return word |= (1UL << off);
}

static inline uint64_t bit_clear(uint64_t word, uint64_t off)
{
    return word &= ~(1UL << off);
}

static inline uint64_t bit_extract(uint64_t word, uint64_t off, uint64_t len)
{
    return (word >> off) & BIT_MASK(0, len);
}

static inline uint64_t bit_insert(uint64_t word, uint64_t val, uint64_t off,
                                  uint64_t len)
{
    return (~BIT_MASK(off, len) & word) | ((BIT_MASK(0, len) & val) << off);
}

#endif /* |__ASSEMBLER__ */

#endif /* __BIT_H__ */
