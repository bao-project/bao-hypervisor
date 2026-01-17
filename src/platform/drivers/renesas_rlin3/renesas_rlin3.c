/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/renesas_rlin3.h>

void uart_init(volatile struct renesas_rlin3* uart)
{
    // Set reset mode
    uart->RLN3nLCUC = 0;

    while ((uart->RLN3nLMST & RLIN3_LMST_OMM0_MSK) != 0x0)
        ;

    uart->RLN3nLWBR = 0; // prescaler reset;

    // Set baud rate to 500000 assuming CLK_RLIN = 80 MHz
    uart->RLN3nLWBR = RLIN3_LWBR_LPRS_16 | RLIN3_LWBR_NSPB_10;
    uart->RLN3nLBRP01 = 0;

    // // // Set baud rate to 9600 assuming CLK_RLIN = 80 MHz
    // uart->RLN3nLWBR = 0x76;
    // uart->RLN3nLBRP01 = 0x81;

    // Set data format
    uart->RLN3nLBFC =
        RLN3_LBFC_UBLS_8B | RLN3_LBFC_UBOS_LSB | RLN3_LBFC_USBLS_1B | RLN3_LBFC_UPS_DIS;

    // Set uart mode
    uart->RLN3nLMD = RLN3_LMD_UART_MODE;
    uart->RLN3nLCUC = RLN3_LCUC_LIN_CANC;

    while ((uart->RLN3nLMST & RLIN3_LMST_OMM0_MSK) != 0x1)
        ;
}

void uart_enable(volatile struct renesas_rlin3* uart)
{
    uart->RLN3nLUOER = RLN3_LUOER_UROE | RLN3_LUOER_UTOE;
}

void uart_putc(volatile struct renesas_rlin3* uart, int8_t c)
{
    while (uart->RLN3nLST & RLN3_LST_UTS_MSK)
        ;
    uart->RLN3nLUTDR = (uint16_t)(c);
}
