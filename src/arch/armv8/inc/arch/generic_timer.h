/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_GENERIC_TIMER_H__
#define __ARCH_GENERIC_TIMER_H__

#include <bao.h>
#include <interrupts.h>

#define GENERIC_TIMER_CNTCTL_CNTCR_EN (0x1)

struct generic_timer_cntctrl {
    uint32_t CNTCR;
    uint32_t CNTSR;
    uint64_t CNTCV;
    uint8_t res0[0x20 - 0x10];
    uint32_t CNTDIF0;
    uint8_t res1[0xfd0 - 0x24];
    uint32_t CounterID[12];
} __attribute__((packed, aligned(PAGE_SIZE)));

uint64_t timer_arch_init(uint64_t period);
void timer_arch_enable(void);
void timer_arch_disable(void);
void timer_arch_define_irq_callback(irq_handler_t handler);
void timer_arch_reschedule_interrupt(uint64_t count);
uint64_t timer_arch_reschedule_interrupt_us(uint64_t period);

#endif /* __ARCH_GENERIC_TIMER_H__ */
