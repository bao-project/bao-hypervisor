/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef RENESAS_RLIN3_H
#define RENESAS_RLIN3_H

#include <bao.h>

#define RLIN3_LWBR_LPRS_16  (0x4 << 1)
#define RLIN3_LWBR_NSPB_10  (0x9 << 4)
#define RLN3_LBFC_UBLS_8B   (0)
#define RLN3_LBFC_UBOS_LSB  (0)
#define RLN3_LBFC_USBLS_1B  (0)
#define RLN3_LBFC_UPS_DIS   (0)
#define RLIN3_LMST_OMM0_MSK (1)
#define RLN3_LUOER_UROE     (0x1 << 1)
#define RLN3_LUOER_UTOE     (0x1 << 0)
#define RLN3_LST_UTS_MSK    (0x1 << 4)
#define RLN3_LST_URS_MSK    (0x1 << 5)
#define RLN3_LMD_UART_MODE  (0x1)
#define RLN3_LCUC_LIN_CANC  (0x1)

struct renesas_rlin3 {
    uint8_t pad0[1];               // 0x0
    volatile uint8_t RLN3nLWBR;    // 0x1
    volatile uint16_t RLN3nLBRP01; // 0x2
    volatile uint8_t RLN3nLSTC;    // 0x4
    volatile uint8_t pad1[3];      // 0x5
    volatile uint8_t RLN3nLMD;     // 0x8
    volatile uint8_t RLN3nLBFC;    // 0x9
    volatile uint8_t RLN3nLSC;     // 0xa
    volatile uint8_t RLN3nLWUP;    // 0xb
    volatile uint8_t RLN3nLIE;     // 0xc
    volatile uint8_t RLN3nLEDE;    // 0xd
    volatile uint8_t RLN3nLCUC;    // 0xe
    volatile uint8_t pad2[1];      // 0xf
    volatile uint8_t RLN3nLTRC;    // 0x10
    volatile uint8_t RLN3nLMST;    // 0x11
    volatile uint8_t RLN3nLST;     // 0x12
    volatile uint8_t RLN3nLEST;    // 0x13
    volatile uint8_t RLN3nLDFC;    // 0x14
    volatile uint8_t RLN3nLIDB;    // 0x15
    volatile uint8_t RLN3nLCBR;    // 0x16
    volatile uint8_t RLN3nLUDB0;   // 0x17
    volatile uint8_t RLN3nLDBR1;   // 0x18
    volatile uint8_t RLN3nLDBR2;   // 0x19
    volatile uint8_t RLN3nLDBR3;   // 0x1a
    volatile uint8_t RLN3nLDBR4;   // 0x1b
    volatile uint8_t RLN3nLDBR5;   // 0x1c
    volatile uint8_t RLN3nLDBR6;   // 0x1d
    volatile uint8_t RLN3nLDBR7;   // 0x1e
    volatile uint8_t RLN3nLDBR8;   // 0x1f
    volatile uint8_t RLN3nLUOER;   // 0x20
    volatile uint8_t RLN3nLUOR1;   // 0x21
    uint8_t pad3[2];               // 0x22
    volatile uint16_t RLN3nLUTDR;  // 0x24
    volatile uint16_t RLN3nLURDR;  // 0x26
    volatile uint16_t RLN3nLUWTDR; // 0x28
    volatile uint8_t RLN3nLBSS;    // 0x30
    volatile uint8_t pad4[3];      // 0x31
    volatile uint8_t RLN3nLRSS;    // 0x34
};

typedef struct renesas_rlin3 bao_uart_t;

void uart_enable(volatile struct renesas_rlin3* uart);
void uart_init(volatile struct renesas_rlin3* uart);
void uart_putc(volatile struct renesas_rlin3* uart, int8_t c);

#endif /* RENESAS_RLIN3_H */
