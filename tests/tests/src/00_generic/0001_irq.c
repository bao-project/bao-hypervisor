/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include "kao.h"
#include <cpu.h>
#include <plat.h>
#include <irq.h>
#include <uart.h>
#include <timer.h>

static volatile bool irq_en_timer = false;
static volatile bool irq_en_uart = false;

#define TIMER_INTERVAL (TIME_MS(100))
#define TEST_TIMEOUT   "300"

static void timer_callback(unsigned int id)
{
    (void)id;
    irq_en_timer = true;
    timer_set(TIMER_INTERVAL);
}

static void uart_rx_handler(unsigned int id)
{
    (void)id;
    uart_clear_rxirq();
    irq_en_uart = true;
}

static void timer_irq(void)
{
    if (cpu_is_master()) {
        COMMAND_SET_TIMEOUT(TEST_TIMEOUT);

        irq_set_handler(TIMER_IRQ_ID, timer_callback);
        timer_set(TIMER_INTERVAL);
        irq_enable(TIMER_IRQ_ID);
        irq_set_prio(TIMER_IRQ_ID, TIMER_IRQ_PRIO);
        timer_enable();

        while (!irq_en_timer)
            ;
        EXPECTED_TRUE(irq_en_timer);
        COMMAND_CLEAR_TIMEOUT();
    }
}
KAO_TEST(00_00_01_00, timer_irq, TAGS(functional, irq, timer), ENVS(baremetal),
    "Check that timer interrupt is triggered and handled successfully");

static void uart_irq(void)
{
    if (cpu_is_master()) {
        COMMAND_SET_TIMEOUT(TEST_TIMEOUT);

        irq_set_handler(UART_IRQ_ID, uart_rx_handler);
        uart_enable_rxirq();
        irq_enable(UART_IRQ_ID);
        irq_set_prio(UART_IRQ_ID, UART_IRQ_PRIO);
        COMMAND_SEND_CHAR("a");

        while (!irq_en_uart)
            ;
        EXPECTED_TRUE(irq_en_uart);
        COMMAND_CLEAR_TIMEOUT();
    }
}
KAO_TEST(00_00_01_01, uart_irq, TAGS(functional, irq, uart), ENVS(baremetal),
    "Check that UART interrupt is triggered and handled successfully");
