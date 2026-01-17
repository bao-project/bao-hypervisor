/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_STBC_H__
#define __PLAT_STBC_H__

#include <platform.h>

#define MSRKCPROT_ENABLE_WR  (0xA5A5A501UL)
#define MSRKCPROT_DISABLE_WR (0xA5A5A500UL)

#define PLAT_STBC_BASE       (0xFF981000UL)

/* Standby Controller MMIO Registers */
struct stbc_hw {
    uint32_t MSR_RSCFD;
    uint8_t pad0[0x0010 - 0x0004];
    uint32_t MSR_FLXA;
    uint8_t pad1[0x0020 - 0x0014];
    uint32_t MSR_GTM;
    uint8_t pad2[0x0030 - 0x0024];
    uint32_t MSR_ETNB;
    uint8_t pad3[0x0040 - 0x0034];
    uint32_t MSR_RSENT;
    uint8_t pad4[0x0050 - 0x0044];
    uint32_t MSR_MSPI;
    uint8_t pad5[0x0060 - 0x0054];
    uint32_t MSR_RLIN3;
    uint8_t pad6[0x0070 - 0x0064];
    uint32_t MSR_ADCJ_ISO;
    uint8_t pad7[0x0080 - 0x0074];
    uint32_t MSR_CXPI;
    uint8_t pad8[0x0090 - 0x0084];
    uint32_t MSR_MMCA;
    uint8_t pad9[0x00A0 - 0x0094];
    uint32_t MSR_ENCA;
    uint8_t pad10[0x00B0 - 0x00A4];
    uint32_t MSR_PSI5;
    uint8_t pad11[0x00C0 - 0x00B4];
    uint32_t MSR_PSI5S;
    uint8_t pad12[0x00D0 - 0x00C4];
    uint32_t MSR_PWMD;
    uint8_t pad13[0x00E0 - 0x00D4];
    uint32_t MSR_RHSIF;
    uint8_t pad14[0x00F0 - 0x00E4];
    uint32_t MSR_RIIC;
    uint8_t pad15[0x0100 - 0x00F4];
    uint32_t MSR_SCI3;
    uint8_t pad16[0x0120 - 0x0104];
    uint32_t MSR_TAPA;
    uint8_t pad17[0x0130 - 0x0124];
    uint32_t MSR_TAUD;
    uint8_t pad18[0x0140 - 0x0134];
    uint32_t MSR_TAUJ_ISO;
    uint8_t pad19[0x0150 - 0x0144];
    uint32_t MSR_TPBA;
    uint8_t pad20[0x0160 - 0x0154];
    uint32_t MSR_TSG3;
    uint8_t pad21[0x0180 - 0x0164];
    uint32_t MSR_OSTM;
    uint8_t pad22[0x0700 - 0x0184];
    uint32_t STBCKCPROT;
    uint8_t pad23[0x0710 - 0x0704];
    uint32_t MSRKCPROT;
};
// TODO: Map remainder of the STBC MMIO

void stbc_init(void);

#endif /* __PLAT_STBC_H__ */
