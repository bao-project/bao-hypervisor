/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#ifndef __PL011_UART_H_
#define __PL011_UART_H_

#include <stdint.h>

/* UART Base Address (PL011) */

#define UART_BASE_0              0xFDF02000
#define UART_BASE_1              0xFDF00000
#define UART_BASE_2              0xFDF03000
#define UART_BASE_4              0xFDF01000
#define UART_BASE_5              0xFDF05000
#define UART_BASE_6              0xFFF32000

/* UART Interrupts */

#define UART_0_INTERRUPT         106
#define UART_1_INTERRUPT         107
#define UART_2_INTERRUPT         108
#define UART_4_INTERRUPT         109
#define UART_5_INTERRUPT         110
#define UART_6_INTERRUPT         111

#define NUM_UART                 6

#define UART_CLK                 19200000
#define UART_BAUD_RATE           115200

/* UART Data Register */

#define UART_DATA_DATA           0xFFFFFF00
#define UART_DATA_FE             (1 << 8
#define UART_DATA_PE             (1 << 9)
#define UART_DATA_BE             (1 << 10)
#define UART_DATA_OE             (1 << 11)

/* UART Receive Status Register/Error Clear Register */

#define UART_RSR_ECR_FE          (1 << 0)
#define UART_RSR_ECR_PE          (1 << 1)
#define UART_RSR_ECR_BE          (1 << 2)
#define UART_RSR_ECR_OE          (1 << 3)
#define UART_RSR_ECR_CLEAR       0xFFFFFF00

/* UART Flag Register */

#define UART_FR_CTS              (1 << 0)
#define UART_FR_DSR              (1 << 1)
#define UART_FR_DCD              (1 << 2)
#define UART_FR_BUSY             (1 << 3)
#define UART_FR_RXFE             (1 << 4)
#define UART_FR_TXFF             (1 << 5)
#define UART_FR_RXFF             (1 << 6)
#define UART_FR_TXFE             (1 << 7)
#define UART_FR_RI               (1 << 8)

/* UART Integer Baud Rate Register */

#define UART_IBRD_DIVINT         0x0000FFFF 

/* UART Fractional Baud Rate Register */

#define UART_FBRD_DIVFRAC        0x0000003F 

/* UART Line Control Register */

#define UART_LCR_BRK             (1 << 0)
#define UART_LCR_PEN             (1 << 1)
#define UART_LCR_EPS             (1 << 2)
#define UART_LCR_STP2            (1 << 3)
#define UART_LCR_FEN             (1 << 4)
#define UART_LCR_WLEN_8          (0b11 << 5)
#define UART_LCR_WLEN_7          (0b10 << 5)
#define UART_LCR_WLEN_6          (0b01 << 5)
#define UART_LCR_WLEN_5          (0b00 << 5)
#define UART_LCR_SPS             (1 << 7)

/* UART Control Register */

#define UART_CR_UARTEN           (1 << 0)
#define UART_CR_SIREN            (1 << 1)
#define UART_CR_SIRLP            (1 << 2)
#define UART_CR_LBE              (1 << 7)
#define UART_CR_TXE              (1 << 8)
#define UART_CR_RXE              (1 << 9)
#define UART_CR_DTR              (1 << 10)
#define UART_CR_RTS              (1 << 11)
#define UART_CR_OUT1             (1 << 12)
#define UART_CR_OUT2             (1 << 13)
#define UART_CR_RTSE             (1 << 14)
#define UART_CR_CTSE             (1 << 15)

/* UART Interrupt FIFO Level Select Register */

#define UART_IFLS_TXIFLSEL_1_8   (0b000 << 0)
#define UART_IFLS_TXIFLSEL_1_4   (0b001 << 0)
#define UART_IFLS_TXIFLSEL_1_2   (0b010 << 0)
#define UART_IFLS_TXIFLSEL_3_4   (0b011 << 0)
#define UART_IFLS_TXIFLSEL_7_8   (0b100 << 0)
#define UART_IFLS_RXIFLSEL_1_8   (0b000 << 3)
#define UART_IFLS_RXIFLSEL_1_4   (0b001 << 3)
#define UART_IFLS_RXIFLSEL_1_2   (0b010 << 3)
#define UART_IFLS_RXIFLSEL_3_4   (0b011 << 3)
#define UART_IFLS_RXIFLSEL_7_8   (0b100 << 3)

/* UART Interrupt Mask Set/Clear Register */

#define UART_IMSC_RIMIM          (1 << 0)
#define UART_IMSC_CTSMIM         (1 << 1)
#define UART_IMSC_DCDMIM         (1 << 2)
#define UART_IMSC_DSRMI          (1 << 3)
#define UART_IMSC_RXIM           (1 << 4)
#define UART_IMSC_TXIM           (1 << 5)
#define UART_IMSC_RTIM           (1 << 6) 
#define UART_IMSC_FEIM           (1 << 7)
#define UART_IMSC_PEIM           (1 << 8)
#define UART_IMSC_BEIM           (1 << 9)
#define UART_IMSC_OEIM           (1 << 10)

/* UART Raw Interrupt Status Register */

#define UART_RIS_RIRMIS          (1 << 0)
#define UART_RIS_CTSRMIS         (1 << 1)
#define UART_RIS_DCDRMIS         (1 << 2)
#define UART_RIS_DSRRMIS         (1 << 3)
#define UART_RIS_RXRIS           (1 << 4)
#define UART_RIS_TXRIS           (1 << 5)
#define UART_RIS_RTRIS           (1 << 6)
#define UART_RIS_FERIS           (1 << 7)
#define UART_RIS_PERIS           (1 << 8)
#define UART_RIS_BERIS           (1 << 9)
#define UART_RIS_OERIS           (1 << 10)

/* UART Masked Interrupt Status Register */

#define UART_MIS_RIMMIS          (1 << 0)
#define UART_MIS_CTSMMIS         (1 << 1)
#define UART_MIS_DCDMMIS         (1 << 2)
#define UART_MIS_DSRMMIS         (1 << 3)
#define UART_MIS_RXMIS           (1 << 4)
#define UART_MIS_TXMIS           (1 << 5)
#define UART_MIS_RTMIS           (1 << 6)
#define UART_MIS_FEMIS           (1 << 7)
#define UART_MIS_PEMIS           (1 << 8)
#define UART_MIS_BEMIS           (1 << 9)
#define UART_MIS_OEMIS           (1 << 10)

/* UART Interrupt Clear Register */

#define UART_ICR_RIMIC           (1 << 0) 
#define UART_ICR_CTSMIC          (1 << 1) 
#define UART_ICR_DCDMIC          (1 << 2) 
#define UART_ICR_DSRMIC          (1 << 3) 
#define UART_ICR_RXIC            (1 << 4) 
#define UART_ICR_TXIC            (1 << 5) 
#define UART_ICR_RTIC            (1 << 6) 
#define UART_ICR_FEIC            (1 << 7) 
#define UART_ICR_PEIC            (1 << 8) 
#define UART_ICR_BEIC            (1 << 9) 
#define UART_ICR_OEIC            (1 << 10)

/* UART DMA Control Register */

#define UART_DMACR_RXDMAE        (1 << 0)
#define UART_DMACR_TXDMAE        (1 << 1)
#define UART_DMACR_DMAONERR      (1 << 2)

/* For printk */

#define serial_puts(str_buffer) uart_puts(1,str_buffer) 

/* UART (PL011) register structure */

typedef struct
{
   volatile uint32_t data;                // UART Data Register
   volatile uint32_t status_error;        // UART Receive Status Register/Error Clear Register
   const uint32_t reserved1[4];           	// Reserved: 4(0x4) bytes
   volatile uint32_t flag;                // UART Flag Register
   const uint32_t reserved2[1];            	// Reserved: 1(0x1) bytes
   volatile uint32_t lp_counter;          // UART Low-power Counter Register
   volatile uint32_t integer_br;          // UART Integer Baud Rate Register
   volatile uint32_t fractional_br;       // UART Fractional Baud Rate Register
   volatile uint32_t line_control;        // UART Line Control Register
   volatile uint32_t control;             // UART Control Register
   volatile uint32_t isr_fifo_level_sel;  // UART Interrupt FIFO level Select Register
   volatile uint32_t isr_mask;            // UART Interrupt Mask Set/Clear Register
   volatile uint32_t raw_isr_status;      // UART Raw Interrupt Status Register
   volatile uint32_t masked_isr_status;   // UART Masked Interrupt Status Register
   volatile uint32_t isr_clear;           // UART Interrupt Clear Register
   volatile uint32_t DMA_control;         // UART DMA control Register
} Pl011_Uart;

typedef Pl011_Uart bao_uart_t;

/** Public PL011 UART interfaces */

void uart_disable(volatile Pl011_Uart * ptr_uart);
void uart_enable(volatile Pl011_Uart * ptr_uart);
void uart_set_baud_rate(volatile Pl011_Uart * ptr_uart, uint32_t baud_rate);
void uart_init(volatile Pl011_Uart * ptr_uart);
uint32_t uart_getc(volatile Pl011_Uart * ptr_uart);
void uart_putc(volatile Pl011_Uart * ptr_uart,int8_t c);
void uart_puts(volatile Pl011_Uart * ptr_uart,const char *s);

#endif /* __PL011_UART_H_ */
