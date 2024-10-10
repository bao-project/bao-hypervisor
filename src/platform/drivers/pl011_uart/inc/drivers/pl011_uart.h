/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PL011_UART_H_
#define __PL011_UART_H_

#include <stdint.h>

#include <plat/platform.h>
#ifndef PL011_PAGE_OFFSET
#define PL011_PAGE_OFFSET (0x000) /**< offset in range of 0-0xFFF */
#endif

/* UART Base Address (PL011) */

#define UART_BASE_0      0xFDF02000
#define UART_BASE_1      0xFDF00000
#define UART_BASE_2      0xFDF03000
#define UART_BASE_4      0xFDF01000
#define UART_BASE_5      0xFDF05000
#define UART_BASE_6      0xFFF32000

/* UART Interrupts */

#define UART_0_INTERRUPT 106
#define UART_1_INTERRUPT 107
#define UART_2_INTERRUPT 108
#define UART_4_INTERRUPT 109
#define UART_5_INTERRUPT 110
#define UART_6_INTERRUPT 111

#define NUM_UART         6

#ifndef UART_CLK
#define UART_CLK 19200000
#endif
#define UART_BAUD_RATE          115200

/* UART Data Register */

#define UART_DATA_DATA          0xFFFFFF00
#define UART_DATA_FE            (1 << 8)
#define UART_DATA_PE            (1 << 9)
#define UART_DATA_BE            (1 << 10)
#define UART_DATA_OE            (1 << 11)

/* UART Receive Status Register/Error Clear Register */

#define UART_RSR_ECR_FE         (1 << 0)
#define UART_RSR_ECR_PE         (1 << 1)
#define UART_RSR_ECR_BE         (1 << 2)
#define UART_RSR_ECR_OE         (1 << 3)
#define UART_RSR_ECR_CLEAR      0xFFFFFF00

/* UART Flag Register */

#define UART_FR_CTS             (1 << 0)
#define UART_FR_DSR             (1 << 1)
#define UART_FR_DCD             (1 << 2)
#define UART_FR_BUSY            (1 << 3)
#define UART_FR_RXFE            (1 << 4)
#define UART_FR_TXFF            (1 << 5)
#define UART_FR_RXFF            (1 << 6)
#define UART_FR_TXFE            (1 << 7)
#define UART_FR_RI              (1 << 8)

/* UART Integer Baud Rate Register */

#define UART_IBRD_DIVINT        0x0000FFFF

/* UART Fractional Baud Rate Register */

#define UART_FBRD_DIVFRAC       0x0000003F

/* UART Line Control Register */

#define UART_LCR_BRK            (1U << 0)
#define UART_LCR_PEN            (1U << 1)
#define UART_LCR_EPS            (1U << 2)
#define UART_LCR_STP2           (1U << 3)
#define UART_LCR_FEN            (1U << 4)
#define UART_LCR_WLEN_8         (0x3 << 5)
#define UART_LCR_WLEN_7         (0x2 << 5)
#define UART_LCR_WLEN_6         (0x1 << 5)
#define UART_LCR_WLEN_5         (0x0 << 5)
#define UART_LCR_SPS            (1U << 7)

/* UART Control Register */

#define UART_CR_UARTEN          (1U << 0)
#define UART_CR_SIREN           (1U << 1)
#define UART_CR_SIRLP           (1U << 2)
#define UART_CR_LBE             (1U << 7)
#define UART_CR_TXE             (1U << 8)
#define UART_CR_RXE             (1U << 9)
#define UART_CR_DTR             (1U << 10)
#define UART_CR_RTS             (1U << 11)
#define UART_CR_OUT1            (1U << 12)
#define UART_CR_OUT2            (1U << 13)
#define UART_CR_RTSE            (1U << 14)
#define UART_CR_CTSE            (1U << 15)

/* UART Interrupt FIFO Level Select Register */

#define UART_IFLS_TXIFLSEL_1_8  (0x0 << 0)
#define UART_IFLS_TXIFLSEL_1_4  (0x1 << 0)
#define UART_IFLS_TXIFLSEL_1_2  (0x2 << 0)
#define UART_IFLS_TXIFLSEL_3_4  (0x3 << 0)
#define UART_IFLS_TXIFLSEL_7_8  (0x4 << 0)
#define UART_IFLS_RXIFLSEL_1_8  (0x0 << 3)
#define UART_IFLS_RXIFLSEL_1_4  (0x1 << 3)
#define UART_IFLS_RXIFLSEL_1_2  (0x2 << 3)
#define UART_IFLS_RXIFLSEL_3_4  (0x3 << 3)
#define UART_IFLS_RXIFLSEL_7_8  (0x4 << 3)

/* UART Interrupt Mask Set/Clear Register */

#define UART_IMSC_RIMIM         (1U << 0)
#define UART_IMSC_CTSMIM        (1U << 1)
#define UART_IMSC_DCDMIM        (1U << 2)
#define UART_IMSC_DSRMI         (1U << 3)
#define UART_IMSC_RXIM          (1U << 4)
#define UART_IMSC_TXIM          (1U << 5)
#define UART_IMSC_RTIM          (1U << 6)
#define UART_IMSC_FEIM          (1U << 7)
#define UART_IMSC_PEIM          (1U << 8)
#define UART_IMSC_BEIM          (1U << 9)
#define UART_IMSC_OEIM          (1U << 10)

/* UART Raw Interrupt Status Register */

#define UART_RIS_RIRMIS         (1U << 0)
#define UART_RIS_CTSRMIS        (1U << 1)
#define UART_RIS_DCDRMIS        (1U << 2)
#define UART_RIS_DSRRMIS        (1U << 3)
#define UART_RIS_RXRIS          (1U << 4)
#define UART_RIS_TXRIS          (1U << 5)
#define UART_RIS_RTRIS          (1U << 6)
#define UART_RIS_FERIS          (1U << 7)
#define UART_RIS_PERIS          (1U << 8)
#define UART_RIS_BERIS          (1U << 9)
#define UART_RIS_OERIS          (1U << 10)

/* UART Masked Interrupt Status Register */

#define UART_MIS_RIMMIS         (1U << 0)
#define UART_MIS_CTSMMIS        (1U << 1)
#define UART_MIS_DCDMMIS        (1U << 2)
#define UART_MIS_DSRMMIS        (1U << 3)
#define UART_MIS_RXMIS          (1U << 4)
#define UART_MIS_TXMIS          (1U << 5)
#define UART_MIS_RTMIS          (1U << 6)
#define UART_MIS_FEMIS          (1U << 7)
#define UART_MIS_PEMIS          (1U << 8)
#define UART_MIS_BEMIS          (1U << 9)
#define UART_MIS_OEMIS          (1U << 10)

/* UART Interrupt Clear Register */

#define UART_ICR_RIMIC          (1U << 0)
#define UART_ICR_CTSMIC         (1U << 1)
#define UART_ICR_DCDMIC         (1U << 2)
#define UART_ICR_DSRMIC         (1U << 3)
#define UART_ICR_RXIC           (1U << 4)
#define UART_ICR_TXIC           (1U << 5)
#define UART_ICR_RTIC           (1U << 6)
#define UART_ICR_FEIC           (1U << 7)
#define UART_ICR_PEIC           (1U << 8)
#define UART_ICR_BEIC           (1U << 9)
#define UART_ICR_OEIC           (1U << 10)

/* UART DMA Control Register */

#define UART_DMACR_RXDMAE       (1U << 0)
#define UART_DMACR_TXDMAE       (1U << 1)
#define UART_DMACR_DMAONERR     (1U << 2)

/* For printk */

#define serial_puts(str_buffer) uart_puts(1, str_buffer)

/* UART (PL011) register structure */

struct Pl011_Uart_hw {
    const uint8_t offset[PL011_PAGE_OFFSET]; // Offset for page alignment
    volatile uint32_t data;                  // UART Data Register
    volatile uint32_t status_error;          // UART Receive Status Register/Error Clear
                                             // Register
    const uint32_t reserved1[4];             // Reserved: 4(0x4) bytes
    volatile uint32_t flag;                  // UART Flag Register
    const uint32_t reserved2[1];             // Reserved: 1(0x1) bytes
    volatile uint32_t lp_counter;            // UART Low-power Counter Register
    volatile uint32_t integer_br;            // UART Integer Baud Rate Register
    volatile uint32_t fractional_br;         // UART Fractional Baud Rate Register
    volatile uint32_t line_control;          // UART Line Control Register
    volatile uint32_t control;               // UART Control Register
    volatile uint32_t isr_fifo_level_sel;    // UART Interrupt FIFO level Select
                                             // Register
    volatile uint32_t isr_mask;              // UART Interrupt Mask Set/Clear Register
    volatile uint32_t raw_isr_status;        // UART Raw Interrupt Status Register
    volatile uint32_t masked_isr_status;     // UART Masked Interrupt Status
                                             // Register
    volatile uint32_t isr_clear;             // UART Interrupt Clear Register
    volatile uint32_t DMA_control;           // UART DMA control Register
};

typedef struct Pl011_Uart_hw bao_uart_t;

/** Public PL011 UART interfaces */

void uart_disable(volatile struct Pl011_Uart_hw* ptr_uart);
void uart_enable(volatile struct Pl011_Uart_hw* ptr_uart);
void uart_set_baud_rate(volatile struct Pl011_Uart_hw* ptr_uart, uint32_t baud_rate);
void uart_init(volatile struct Pl011_Uart_hw* ptr_uart);
uint32_t uart_getc(volatile struct Pl011_Uart_hw* ptr_uart);
void uart_putc(volatile struct Pl011_Uart_hw* ptr_uart, int8_t c);

#endif /* __PL011_UART_H_ */
