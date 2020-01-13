/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <drivers/pl011_uart.h>


void uart_disable(volatile Pl011_Uart * ptr_uart){

	uint32_t ctrl_reg = ptr_uart->control;					
	ctrl_reg &= ((~UART_CR_UARTEN) | (~UART_CR_TXE) | (~UART_CR_RXE));	
	ptr_uart->control = ctrl_reg;						

}


void uart_enable(volatile Pl011_Uart * ptr_uart){

	uint32_t ctrl_reg = ptr_uart->control;				
	ctrl_reg |= (UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE);	
	ptr_uart->control = ctrl_reg;				

}


void uart_set_baud_rate(volatile Pl011_Uart * ptr_uart, uint32_t baud_rate){

	uint32_t temp;
	uint32_t ibrd;
	uint32_t mod;
	uint32_t fbrd;

	if(baud_rate == 0)
	{
		baud_rate =  UART_BAUD_RATE;
	}

	/* Set baud rate, IBRD = UART_CLK / (16 * BAUD_RATE)
	FBRD = ROUND((64 * MOD(UART_CLK,(16 * BAUD_RATE))) / (16 * BAUD_RATE)) */
	temp = 16 * baud_rate;
	ibrd = UART_CLK / temp;
	mod = UART_CLK % temp;
	fbrd = (4 * mod) / baud_rate;

	/* Set the values of the baudrate divisors */
	ptr_uart->integer_br = ibrd;
	ptr_uart->fractional_br = fbrd;

}


void uart_init(volatile Pl011_Uart * ptr_uart/*, uint32_t baud_rate*/) {

	int lcrh_reg;

	/* First, disable everything */
	ptr_uart->control = 0x0;

	/* Disable FIFOs */
	lcrh_reg = ptr_uart->line_control;
	lcrh_reg &= ~UART_LCR_FEN;
	ptr_uart->line_control = lcrh_reg;

	/* Default baudrate = 115200 */
	uint32_t baud_rate = UART_BAUD_RATE;
	uart_set_baud_rate(ptr_uart, baud_rate);

	/* Set the UART to be 8 bits, 1 stop bit and no parity, FIFOs enable*/
	ptr_uart->line_control = (UART_LCR_WLEN_8 | UART_LCR_FEN);

	/* Enable the UART, enable TX and enable loop back*/
	ptr_uart->control = (UART_CR_UARTEN | UART_CR_TXE | UART_CR_LBE);

	/* Set the receive interrupt FIFO level to 1/2 full */
	ptr_uart->isr_fifo_level_sel = UART_IFLS_RXIFLSEL_1_2;

	ptr_uart->data = 0x0;
	while(ptr_uart->flag & UART_FR_BUSY);

	/* Enable RX */
	ptr_uart->control = (UART_CR_UARTEN | UART_CR_RXE | UART_CR_TXE);

	/* Clear interrupts */
	ptr_uart->isr_clear = (UART_ICR_OEIC | UART_ICR_BEIC | UART_ICR_PEIC | UART_ICR_FEIC);

	/* Enable receive and receive timeout interrupts */
	ptr_uart->isr_mask = (UART_MIS_RXMIS | UART_MIS_RTMIS);

}


uint32_t uart_getc(volatile Pl011_Uart * ptr_uart){

	uint32_t data = 0;

	//wait until there is data in FIFO
	while(!(ptr_uart->flag & UART_FR_RXFE));

	data = ptr_uart->data;
	return data;

}


void uart_putc(volatile Pl011_Uart * ptr_uart,int8_t c){

	//wait until txFIFO is not full
	while(ptr_uart->flag & UART_FR_TXFF);

	ptr_uart->data = c;

}


void uart_puts(volatile Pl011_Uart * ptr_uart,const char *s){

	while (*s)
	{
		uart_putc(ptr_uart,*s++);
	}

}
