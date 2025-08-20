/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __CSA_H__
#define __CSA_H__

#include <bao.h>

#define CSA_ENTRIES       32
#define CSA_SIZE          16
#define CSA_SIZE_BYTES    (16 * 4)
#define CSA_ARRAY_SIZE    (CSA_ENTRIES * CSA_SIZE * 4)

#define PCXI_PCXO_OFF     0
#define PCXI_PCXS_OFF     16
#define PCXI_UL_OFF       20
#define PCXI_PIE_OFF      20
#define ADDR_PCXS_OFF     28
#define ADDR_PCXS_LEN     4
#define ADDR_PCXO_OFF     6
#define ADDR_PCXO_LEN     16
#define PSW_IO_OFF        10
#define PSW_IO_SUPERVISOR 2

#ifndef __ASSEMBLER__

struct lower_context {
    unsigned long pcxi;
    unsigned long a11;
    unsigned long a2;
    unsigned long a3;
    unsigned long d0;
    unsigned long d1;
    unsigned long d2;
    unsigned long d3;
    unsigned long a4;
    unsigned long a5;
    unsigned long a6;
    unsigned long a7;
    unsigned long d4;
    unsigned long d5;
    unsigned long d6;
    unsigned long d7;
} __attribute__((aligned(64)));

struct upper_context {
    unsigned long pcxi;
    unsigned long csa_psw;
    unsigned long a10;
    unsigned long a11;
    unsigned long d8;
    unsigned long d9;
    unsigned long d10;
    unsigned long d11;
    unsigned long a12;
    unsigned long a13;
    unsigned long a14;
    unsigned long a15;
    unsigned long d12;
    unsigned long d13;
    unsigned long d14;
    unsigned long d15;
} __attribute__((aligned(64)));

union csa {
    struct lower_context lower;
    struct upper_context upper;
};

extern union csa csa_array[PLAT_CPU_NUM][CSA_ENTRIES];

#endif

#endif /*__CSA_H__ */
