#include "testf.h"
#include <core.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <cpu.h>
#include <wfi.h>
#include <spinlock.h>
#include <plat.h>
#include <irq.h>
#include <uart.h>
#include <timer.h>

void test_interrupt_timer_callback();
void uart_rx_handler();


volatile bool irq_en_timer = false;
volatile bool irq_en_uart = false;

#define TIMER_INTERVAL  (TIME_MS(100))
#define TEST_TIME_WAIT  (TIME_MS(200))
#define TEST_TIMEOUT    "300"

BAO_TEST(IRQ_CHECK, TIMER)
{
    if(cpu_is_master()) {
        COMMAND_SET_TIMEOUT(TEST_TIMEOUT);
    
        irq_set_handler(TIMER_IRQ_ID, test_interrupt_timer_callback);
        timer_set(TIMER_INTERVAL);
        irq_enable(TIMER_IRQ_ID);
        irq_set_prio(TIMER_IRQ_ID, IRQ_MAX_PRIO);
    
        while(!irq_en_timer);
        EXPECTED_TRUE(irq_en_timer);
        COMMAND_CLEAR_TIMEOUT();
    }
}

BAO_TEST(IRQ_CHECK, UART)
{
    if(cpu_is_master()) {
        COMMAND_SET_TIMEOUT(TEST_TIMEOUT);
    
        irq_set_handler(UART_IRQ_ID, uart_rx_handler);
        uart_enable_rxirq();
        irq_enable(UART_IRQ_ID);
        irq_set_prio(UART_IRQ_ID, IRQ_MAX_PRIO);
        COMMAND_SEND_CHAR("a");
    
        timer_wait(TEST_TIME_WAIT);
        EXPECTED_TRUE(irq_en_uart);
        COMMAND_CLEAR_TIMEOUT();
    }
}

void test_interrupt_timer_callback()
{
    irq_en_timer = true;
    timer_set(TIMER_INTERVAL);
}

void uart_rx_handler(){
    uart_clear_rxirq();
    irq_en_uart = true;
}