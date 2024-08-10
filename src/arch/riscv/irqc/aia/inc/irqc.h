
/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef IRQC_H
#define IRQC_H

#include <aplic.h>
#include <cpu.h>
#include <vaplic.h>
#if (IRQC == APLIC)
#include <arch/sbi.h>
#elif (IRQC == AIA)
#include <imsic.h>
#endif

#define IRQC_TIMR_INT_ID         (APLIC_MAX_INTERRUPTS + 1)
#define IRQC_SOFT_INT_ID         (APLIC_MAX_INTERRUPTS + 2)
#define IRQC_MAX_INTERRUPT_LINES (IRQC_SOFT_INT_ID + 1)

#if (IRQC == APLIC)
#define IRQC_MAX_INTERRUPT_HANDLERS IRQC_MAX_INTERRUPT_LINES
#elif (IRQC == AIA)
#define IRQC_MAX_INTERRUPT_HANDLERS (PLAT_IMSIC_MAX_INTERRUPTS)
#define IMSIC_FIRST_NONRESERVED_ID  (2)
#endif

#define IRQC_MAX_GUEST_INTERRUPTS APLIC_MAX_INTERRUPTS

#define HART_REG_OFF              APLIC_IDC_OFF
#define IRQC_HART_INST            APLIC_DOMAIN_NUM_HARTS
#define HYP_IRQ_SM_EDGE_RISE      APLIC_SOURCECFG_SM_EDGE_RISE
#define HYP_IRQ_SM_INACTIVE       APLIC_SOURCECFG_SM_INACTIVE
#define HYP_IRQ_PRIO              APLIC_TARGET_MAX_PRIO
#define HYP_IRQ                   0

static inline void irqc_init(void)
{
    aplic_init();
}

static inline void irqc_cpu_init(void)
{
#if (IRQC == APLIC)
    aplic_idc_init();
#elif (IRQC == AIA)
    imsic_init();
#endif
}

static inline irqid_t irqc_reserve(irqid_t pintp_id)
{
#if (IRQC == APLIC)
    return pintp_id;
#elif (IRQC == AIA)
    irqid_t msi_id = imsic_allocate_msi();
    if ((msi_id != INVALID_IRQID) && (pintp_id < APLIC_MAX_INTERRUPTS)) {
        aplic_link_msi_id_to_pintp(msi_id, pintp_id);
    }
    return msi_id;
#endif
}

static inline void irqc_send_ipi(cpuid_t target_cpu, irqid_t ipi_id)
{
#if (IRQC == APLIC)
    UNUSED_ARG(ipi_id);
    sbi_send_ipi(1ULL << target_cpu, 0);
#elif (IRQC == AIA)
    imsic_send_msi(target_cpu, ipi_id);
#endif
}

static inline void irqc_config_irq(irqid_t int_id, bool en)
{
    irqid_t pintp_id = int_id;
#if (IRQC == AIA)
    irqid_t msi_id = int_id;
#endif

    if (en) {
#if (IRQC == AIA)
        imsic_set_enbl(msi_id);
        pintp_id = aplic_get_pintp_id_from_msi_id(msi_id);
        if (pintp_id == 0) {
            return;
        }
#endif
        aplic_set_sourcecfg(pintp_id, HYP_IRQ_SM_EDGE_RISE);
        aplic_set_enbl(pintp_id);
        aplic_set_target_hart(pintp_id, cpu()->id);
#if (IRQC == AIA)
        aplic_set_target_eiid(pintp_id, msi_id);
        aplic_set_target_guest(pintp_id, HYP_IRQ);
#elif (IRQC == APLIC)
        aplic_set_target_prio(pintp_id, HYP_IRQ_PRIO);
#endif
    } else {
#if (IRQC == AIA)
        imsic_clr_pend(msi_id);
        pintp_id = aplic_get_pintp_id_from_msi_id(msi_id);
#endif
        aplic_clr_enbl(pintp_id);
    }
}

static inline void irqc_handle(void)
{
#if (IRQC == APLIC)
    aplic_handle();
#elif (IRQC == AIA)
    imsic_handle();
#endif
}

static inline bool irqc_get_pend(irqid_t int_id)
{
#if (IRQC == APLIC)
    return aplic_get_pend(int_id);
#elif (IRQC == AIA)
    return imsic_get_pend(int_id);
#endif
}

static inline void irqc_clr_pend(irqid_t int_id)
{
#if (IRQC == APLIC)
    aplic_clr_pend(int_id);
#elif (IRQC == AIA)
    imsic_clr_pend(int_id);
#endif
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
