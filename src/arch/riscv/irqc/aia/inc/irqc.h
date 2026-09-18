
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef IRQC_H
#define IRQC_H

#include <aplic.h>
#include <cpu.h>
#include <vaplic.h>
#include <arch/sbi.h>
#if (IRQC == AIA)
#include <imsic.h>
#include <vimsic.h>
#endif

static inline void irqc_init(void)
{
    aplic_init();
}

#if (IRQC == APLIC)

static inline void irqc_cpu_init(void)
{
    aplic_idc_init();
}

static inline irqid_t irqc_reserve(irqid_t pintp_id)
{
    return pintp_id;
}

static inline void irqc_send_ipi(cpuid_t target_cpu)
{
    sbi_send_ipi(1UL << target_cpu, 0);
}

static inline void irqc_handle(void)
{
    aplic_handle();
}

static inline bool irqc_get_pend(irqid_t int_id)
{
    return aplic_get_pend(int_id);
}

static inline void irqc_clr_pend(irqid_t int_id)
{
    aplic_clr_pend(int_id);
}

#else

static inline void irqc_cpu_init(void)
{
    imsic_init();
}

static inline irqid_t irqc_reserve(irqid_t pintp_id)
{
    irqid_t msi_id = imsic_allocate_msi();
    if ((msi_id != INVALID_IRQID) && (pintp_id < APLIC_MAX_INTERRUPTS)) {
        aplic_link_msi_id_to_pintp(msi_id, pintp_id);
    }
    return msi_id;
}

static inline void irqc_send_ipi(cpuid_t target_cpu)
{
    extern irqid_t interrupts_ipi_id;
    imsic_send_msi(target_cpu, interrupts_ipi_id);
}

static inline void irqc_handle(void)
{
    imsic_handle();
}

static inline bool irqc_get_pend(irqid_t int_id)
{
    return imsic_get_pend(int_id);
}

static inline void irqc_clr_pend(irqid_t int_id)
{
    imsic_clr_pend(int_id);
}

#endif

static inline void irqc_config_irq(irqid_t int_id, bool en)
{
    irqid_t pintp_id = int_id;

    if (en) {
#if (IRQC == AIA)
        imsic_set_enbl(int_id);
        pintp_id = aplic_get_pintp_id_from_msi_id(int_id);
        if (pintp_id == 0) {
            return;
        }
        aplic_set_target_eiid(pintp_id, int_id);
        aplic_set_target_guest(pintp_id, HYP_IRQ);
#elif (IRQC == APLIC)
        aplic_set_target_prio(pintp_id, HYP_IRQ_PRIO);
#endif

        aplic_set_sourcecfg(pintp_id, HYP_IRQ_SM_EDGE_RISE);
        aplic_set_enbl(pintp_id);
        aplic_set_target_hart(pintp_id, cpu()->id);
    } else {
#if (IRQC == AIA)
        imsic_clr_pend(int_id);
        pintp_id = aplic_get_pintp_id_from_msi_id(int_id);
#endif
        aplic_clr_enbl(pintp_id);
    }
}

/**
 * @brief Wrapper for the virtual irqc initialization function
 *
 * @param vm Virtual Machine
 * @param vm_irqc_dscrp virtual irqc platform configuration
 */
static inline void virqc_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp)
{
    vaplic_init(vm, vm_irqc_dscrp);
#if (IRQC == AIA)
    vimsic_init(vm, vm_irqc_dscrp);
#endif
}

static inline void virqc_set_hw(struct vm* vm, irqid_t id)
{
    vaplic_set_hw(vm, id);
}

#endif // IRQC_H
