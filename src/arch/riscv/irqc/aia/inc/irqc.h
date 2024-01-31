
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
#include <vimsic.h>
#endif

#define IRQC_TIMR_INT_ID (APLIC_MAX_INTERRUPTS + 1)
#define IRQC_SOFT_INT_ID (APLIC_MAX_INTERRUPTS + 2)
#if (IRQC == APLIC)
#define IRQC_MAX_INTERRUPTS (IRQC_SOFT_INT_ID + 1)
#elif (IRQC == AIA)
/**
 * Why IRQC_TIMR_INT_ID and not IRQC_SOFT_INT_ID? With the AIA specification, the software interrupt
 * is now delivered through the IMSIC, which means that the target hart will see it as an external 
 * interrupt. Thus, the total number of interrupts is the maximum number of interrupts supported by 
 * aplic, the timer interrupt, the maximum number of interrupts supported by imsic, and one to 
 * support/keep "<" logic.
 */
#define IRQC_MAX_INTERRUPTS (IRQC_TIMR_INT_ID + IMSIC_MAX_INTERRUPTS + 1)
#define IRQC_MSI_INTERRUPTS_START_ID (IRQC_TIMR_INT_ID)
#else
#error "IRQC not defined"
#endif

#define HART_REG_OFF         APLIC_IDC_OFF
#define IRQC_HART_INST       APLIC_DOMAIN_NUM_HARTS
#define HYP_IRQ_SM_EDGE_RISE APLIC_SOURCECFG_SM_EDGE_RISE
#define HYP_IRQ_SM_INACTIVE  APLIC_SOURCECFG_SM_INACTIVE
#define HYP_IRQ_PRIO         APLIC_TARGET_MAX_PRIO

static inline void irqc_init()
{
    aplic_init();
}

static inline void irqc_cpu_init()
{
    #if (IRQC == APLIC)
    aplic_idc_init();
    #elif (IRQC == AIA)
    imsic_init();
    #else
    #error "IRQC not defined"
    #endif
}

static inline irqid_t irqc_reserve(irqid_t pintp_id)
{
    #if (IRQC == APLIC)
    return pintp_id;
    #elif (IRQC == AIA)
    irqid_t msi_id = 0;
    if (pintp_id < APLIC_MAX_INTERRUPTS){
        msi_id = imsic_find_available_msi();
        aplic_link_msi_id_to_pintp(msi_id, pintp_id);
    } else {
        msi_id = pintp_id - IRQC_MSI_INTERRUPTS_START_ID;
    }
    imsic_reserve_msi(msi_id);
    msi_id += IRQC_MSI_INTERRUPTS_START_ID;
    return msi_id;
    #else
    #error "IRQC not defined"
    #endif
}

static inline void irqc_send_ipi(cpuid_t target_cpu, irqid_t ipi_id)
{
    #if (IRQC == APLIC)
    sbi_send_ipi(1ULL << target_cpu, 0);
    #elif (IRQC == AIA)
    imsic_send_msi(target_cpu, ipi_id - IRQC_MSI_INTERRUPTS_START_ID);
    #endif
}

static inline void irqc_config_irq(irqid_t int_id, bool en)
{
    irqid_t pintp_id = int_id;
    #if (IRQC == AIA)
    irqid_t msi_id = int_id - IRQC_MSI_INTERRUPTS_START_ID;
    #endif

    if (en) {
        #if (IRQC == AIA)
        imsic_set_enbl(msi_id);
        pintp_id = aplic_get_pintp_id_from_msi_id(msi_id);
        if (pintp_id == 0){
            return;
        }
        #endif
        aplic_set_sourcecfg(pintp_id, HYP_IRQ_SM_EDGE_RISE);
        aplic_set_enbl(pintp_id);
        aplic_set_target_hart(pintp_id, cpu()->id);
        #if (IRQC == AIA)
        aplic_set_target_eiid(pintp_id, msi_id);
        // 0 means is for hypervisor use
        aplic_set_target_guest(pintp_id, 0);
        #elif (IRQC == APLIC)
        aplic_set_target_prio(pintp_id, HYP_IRQ_PRIO);
        #else
        #error "IRQC not defined"
        #endif
    } else {
        #if (IRQC == AIA)
        imsic_clr_pend(msi_id);
        pintp_id = aplic_get_pintp_id_from_msi_id(msi_id);
        #endif
        aplic_clr_enbl(pintp_id);
    }
}

static inline void irqc_handle()
{
    #if (IRQC == APLIC)
    aplic_handle();
    #elif (IRQC == AIA)
    imsic_handle();
    #else
    #error "IRQC not defined"
    #endif
}

static inline bool irqc_get_pend(irqid_t int_id)
{
    #if (IRQC == APLIC)
    return aplic_get_pend(int_id);
    #elif (IRQC == AIA)
    return imsic_get_pend(int_id - IRQC_MSI_INTERRUPTS_START_ID);
    #else
    #error "IRQC not defined"
    #endif
}

static inline void irqc_clr_pend(irqid_t int_id)
{
    #if (IRQC == APLIC)
    aplic_clr_pend(int_id);
    #elif (IRQC == AIA)
    imsic_clr_pend(int_id - IRQC_MSI_INTERRUPTS_START_ID);
    #else
    #error "IRQC not defined"
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
