/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <arch/timer.h>
#include <interrupts.h>
#include <arch/sysregs.h>
#include <platform.h>
#include <bit.h>
#include <arch/bao.h>
#include <cpu.h>

#define CNTHP_CTL_EL2_ENABLE 	0
#define CNTHP_CTL_EL2_IMASK  	1


void timer_arch_enable() {
    uint64_t ctl_value;

    ctl_value = sysreg_cnthp_ctl_el2_read();
    ctl_value = bit_set(ctl_value, CNTHP_CTL_EL2_ENABLE);
    ctl_value = bit_clear(ctl_value, CNTHP_CTL_EL2_IMASK);

    sysreg_cnthp_ctl_el2_write(ctl_value);
}

void timer_arch_disable() {
    uint64_t ctl_value;

    ctl_value = sysreg_cnthp_ctl_el2_read();
    ctl_value = bit_clear(ctl_value, CNTHP_CTL_EL2_ENABLE);

    sysreg_cnthp_ctl_el2_write(ctl_value);
}

static inline uint64_t timer_arch_get_system_frequency() {
    uint64_t frequency;

    frequency = sysreg_cntfrq_el0_read();
    return (frequency & 0xFFFFFFFF);
}

static inline void timer_arch_set_counter(uint64_t count) {
    uint64_t tval;

    count &= 0xFFFFFFFF;
    tval = sysreg_cnthp_tval_el2_read();
    tval &= 0xFFFFFFFF00000000;
    count = tval | count;

    sysreg_cnthp_tval_el2_write(count);
}

uint64_t timer_arch_init(uint64_t period) {
    uint64_t frequency;
    uint64_t count_value;

    frequency = timer_arch_get_system_frequency();
    count_value = (period * frequency) / 1000000;
    timer_arch_set_counter(count_value);
    timer_arch_enable();

    return count_value;
}

void timer_arch_reschedule_interrupt(uint64_t count) {
    timer_arch_set_counter(count);
}

uint64_t timer_arch_reschedule_interrupt_us(uint64_t period) {
    uint64_t frequency;
    uint64_t count_value;

    frequency = timer_arch_get_system_frequency();
    count_value = (period * frequency) / 1000000;
    timer_arch_set_counter(count_value);

    return count_value;
}