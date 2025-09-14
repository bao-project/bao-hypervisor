#include "testf.h"
// #include <plat.h>
// #include <irq.h>
// #include <timer.h>
// #include <uart.h>
// #include <core.h>
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


bool irq_en_timer = false;
bool irq_en_uart = false;

#define TIMER_INTERVAL  (TIME_MS(100))
#define TEST_TIMEOUT    (TIME_S(1))

BAO_TEST(IRQ_CHECK, TIMER)
{
    irq_set_handler(TIMER_IRQ_ID, test_interrupt_timer_callback);
    irq_enable(TIMER_IRQ_ID);
    timer_set(TIMER_INTERVAL);
    irq_set_prio(TIMER_IRQ_ID, IRQ_MAX_PRIO);

    timer_wait(TEST_TIMEOUT);

    EXPECTED_TRUE(irq_en_timer);
}

BAO_TEST(IRQ_CHECK, UART)
{
    irq_set_handler(33, uart_rx_handler);
    uart_enable_rxirq();
    irq_enable(33);
    irq_set_prio(33, IRQ_MAX_PRIO);
    COMMAND_SEND_CHAR("a");

    timer_wait(TEST_TIMEOUT);
    EXPECTED_TRUE(irq_en_uart);
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