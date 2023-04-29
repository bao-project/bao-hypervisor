/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __UTIL_H__
#define __UTIL_H__

/* UTILITY MACROS */

/* align VAL to TO which must be power a two */
#define ALIGN(VAL, TO) ((((VAL) + (TO)-1) / (TO)) * TO)
#define IS_ALIGNED(VAL, TO) (!((VAL)%(TO)))
#define ALIGN_FLOOR(VAL, TO) ((VAL) & ~((TO)-1))
#define NUM_PAGES(SZ) (ALIGN(SZ, PAGE_SIZE)/PAGE_SIZE)
#define PAGE_OFFSET_MASK ((PAGE_SIZE)-1)
#define PAGE_FRAME_MASK (~(PAGE_OFFSET_MASK))

#define SR_OR(VAL, SHIFT) (((VAL) >> (SHIFT)) | VAL)
/* Next Power Of Two */
#define NPOT(VAL)                                                     \
    ((SR_OR(((VAL)-1), 1) | SR_OR(SR_OR(((VAL)-1), 1), 2) |           \
      SR_OR(SR_OR(SR_OR(((VAL)-1), 1), 2), 4) |                       \
      SR_OR(SR_OR(SR_OR(SR_OR(((VAL)-1), 1), 2), 4), 8) |             \
      SR_OR(SR_OR(SR_OR(SR_OR(SR_OR(((VAL)-1), 1), 2), 4), 8), 16)) + \
     1)

/* Previous Power Of Two */
#define PPOT(VAL) (NPOT((VAL)) - (NPOT((VAL)) >> 1))

#define STR(s)  #s
#define XSTR(s)  STR(s)

#ifndef __ASSEMBLER__

#define DEFINE_OFFSET(SYMBOL, STRUCT, FIELD) \
    asm volatile("\n-> " XSTR(SYMBOL) " %0 \n" : : "i"(offsetof(STRUCT, FIELD)))

#define DEFINE_SIZE(SYMBOL, TYPE) \
    asm volatile("\n-> " XSTR(SYMBOL) " %0 \n" : : "i"(sizeof(TYPE)))

#define max(n1, n2) (((n1) > (n2)) ? (n1) : (n2))
#define min(n1, n2) (((n1) < (n2)) ? (n1) : (n2))

static inline bool range_overlap_range(unsigned long base1, unsigned long size1,
    unsigned long base2, unsigned long size2) {

    vaddr_t reg1_lim = base1 + size1 - 1;
    vaddr_t reg2_lim = base2 + size2 - 1;

    return (base1 >= base2 && base1 <= reg2_lim) ||
        (reg1_lim >= base2 && reg1_lim <= reg2_lim) || 
        (base1 <= base2 && reg1_lim >= reg2_lim);
}

static inline bool range_in_range(unsigned long base1, unsigned long size1,
    unsigned long base2, unsigned long size2) {

    unsigned long limit1 = base1 + size1;
    unsigned long limit2 = base2 + size2;

    /* Saturate possible overflows */
    if (limit1 < base1)  {
        limit1 = ULONG_MAX;
    }
    if (limit2 < base2) {
        limit2= ULONG_MAX;
    }

    return (base1 >= base2) && (limit1 <= limit2);
}

/* WARNING! does not check for overflow! */
#define in_range(_addr, _base, _size) range_in_range(_addr, 0, _base, _size)


/**
 * Check if a given macro was defined. Note it only works wither if the macro
 * is undefined or defined to the value 1. If the macro is defined with any
 * other value it will fail recognizing its defined.
 */
#define DEFINED(MACRO)  _DEFINED(MACRO)
#define _DEFINED_1   0,
#define _DEFINED(VALUE)  __DEFINED(_DEFINED_ ## VALUE)
#define __DEFINED(VALUE)  ___DEFINED(VALUE true, false)
#define ___DEFINED(IGNORE, RESULT, ...)    (RESULT)

#endif

#endif /* __UTIL_H__ */
