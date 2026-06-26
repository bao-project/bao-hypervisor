/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <arch/bao.h>
#include <arch/generic_timer.h>
#include <arch/sysregs.h>
#include <bit.h>
#include <cpu.h>
#include <interrupts.h>
#include <platform.h>
#include <spinlock.h>

#define CNTHP_CTL_EL2_ENABLE 0
#define CNTHP_CTL_EL2_IMASK 1

static irq_handler_t timer_handlers[CPU_MAX];
static irqid_t timer_irq_id = INVALID_IRQID;
static spinlock_t timer_irq_lock = SPINLOCK_INITVAL;

static void timer_arch_interrupt_handler(irqid_t int_id)
{
    irq_handler_t handler = timer_handlers[cpu()->id];

    if (handler != NULL) {
        handler(int_id);
    }
}

void timer_arch_define_irq_callback(irq_handler_t handler)
{
    irqid_t interrupt_id = platform.arch.generic_timer.interrupt_id;

    if ((interrupt_id == INVALID_IRQID) || (interrupt_id == 0U)) {
        ERROR("Invalid hypervisor timer interrupt id\n");
    }

    timer_handlers[cpu()->id] = handler;

    spin_lock(&timer_irq_lock);
    if (timer_irq_id == INVALID_IRQID) {
        timer_irq_id = interrupts_reserve(interrupt_id, timer_arch_interrupt_handler);
        if (timer_irq_id == INVALID_IRQID) {
            ERROR("Failed to reserve hypervisor timer interrupt id = %u\n", interrupt_id);
        }
    } else if (timer_irq_id != interrupt_id) {
        ERROR("Inconsistent hypervisor timer interrupt id = %u\n", interrupt_id);
    }
    spin_unlock(&timer_irq_lock);

    interrupts_arch_enable(timer_irq_id, true);
}

/**
 * @brief Enables the architecture-specific timer.
 */
void timer_arch_enable(void)
{
    uint64_t ctl_value;

    // Read the current value of the control register CNTHP_CTL_EL2.
    ctl_value = sysreg_cnthp_ctl_el2_read();

    // CNTHP_CTL_EL2 --> ENABLE, bit [0]
    // --> 0b0 - Timer disabled
    // --> 0b1 - Timer enabled
    ctl_value = bit_set(ctl_value, CNTHP_CTL_EL2_ENABLE);

    // CNTHP_CTL_EL2 --> IMASK, bit [1]
    // --> 0b0 - Timer interrupt is not masked by the IMASK bit
    // --> 0b1 - Timer interrupt is masked by the IMASK bit
    ctl_value = bit_clear(ctl_value, CNTHP_CTL_EL2_IMASK);

    // Write the updated control value back to the CNTHP_CTL_EL2 register.
    sysreg_cnthp_ctl_el2_write(ctl_value);
}

/**
 * @brief Disables the architecture-specific timer.
 */
void timer_arch_disable(void)
{
    uint64_t ctl_value;

    // Read the current value of the control register CNTHP_CTL_EL2.
    ctl_value = sysreg_cnthp_ctl_el2_read();

    // CNTHP_CTL_EL2 --> ENABLE, bit [0]
    // --> 0b0 - Timer disabled
    // --> 0b1 - Timer enabled
    ctl_value = bit_clear(ctl_value, CNTHP_CTL_EL2_ENABLE);

    // Write the updated control value back to the CNTHP_CTL_EL2 register.
    sysreg_cnthp_ctl_el2_write(ctl_value);
}

/**
 * @brief Gets the system frequency from the architecture-specific timer.
 *
 * @return The system frequency in Hz.
 */
static inline uint64_t timer_arch_get_system_frequency(void)
{
    uint64_t frequency;

    // Read the system frequency from the architecture-specific register
    // CNTFRQ_EL0.
    frequency = sysreg_cntfrq_el0_read();

    // Mask the lower 32 bits of the frequency value to get the system frequency
    // in Hz.
    return frequency & UINT32_MAX;
}

/**
 * @brief Sets the architecture-specific timer counter value.
 *
 * @param count The value to set for the timer counter (lower 32 bits).
 */
static inline void timer_arch_set_counter(uint64_t count)
{
    if (count > INT32_MAX) {
        ERROR("Hypervisor timer count exceeds TVAL range\n");
    }

    // Write the new counter value to the architecture-specific register
    // CNTHP_TVAL_EL2.
    sysreg_cnthp_tval_el2_write(count);
}

/**
 * @brief Initializes the architecture-specific timer with the specified period.
 *
 * @param period The timer period in microseconds.
 * @return The calculated counter value to set for the timer.
 */
uint64_t timer_arch_init(uint64_t period)
{
    uint64_t frequency;
    uint64_t count_value;

    // Get the system frequency from the architecture-specific timer.
    frequency = timer_arch_get_system_frequency();

    // Calculate the count value to set for the timer based on the period and
    // system frequency.
    count_value = (period * frequency) / 1000000;

    // Set the timer counter to the calculated count value.
    timer_arch_set_counter(count_value);

    // Enable the architecture-specific timer.
    timer_arch_enable();

    // Return the calculated counter value for the timer.
    return count_value;
}

/**
 * @brief Reschedules the architecture-specific timer interrupt with the
 *        specified counter value.
 *
 * @param count The counter value to set for rescheduling the timer interrupt.
 */
void timer_arch_reschedule_interrupt(uint64_t count)
{
    // Set the timer counter to the specified count value for rescheduling the
    // interrupt.
    timer_arch_set_counter(count);
}

/**
 * @brief Reschedules the architecture-specific timer interrupt with the
 *        specified period in microseconds.
 *
 * @param period The timer period in microseconds to reschedule the interrupt.
 * @return The calculated counter value to set for the timer.
 */
uint64_t timer_arch_reschedule_interrupt_us(uint64_t period)
{
    uint64_t frequency;
    uint64_t count_value;

    // Get the system frequency from the architecture-specific timer.
    frequency = timer_arch_get_system_frequency();

    // Calculate the count value to set for the timer based on the period and
    // system frequency.
    count_value = (period * frequency) / 1000000;

    // Set the timer counter to the calculated count value for rescheduling
    // the interrupt.
    timer_arch_set_counter(count_value);

    // Return the calculated counter value for the timer.
    return count_value;
}
