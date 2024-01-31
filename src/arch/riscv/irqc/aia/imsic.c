/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <imsic.h>
#include <mem.h>
#include <arch/csrs.h>
#include <irqc.h>
#include <cpu.h>
#include <interrupts.h>

volatile struct imsic_global_hw* imsic[PLAT_CPU_NUM];
BITMAP_ALLOC(msi_reserved, IMSIC_MAX_INTERRUPTS);

void imsic_init(void){
    /** Every intp is triggrable */
    CSRW(CSR_SISELECT, IMSIC_EITHRESHOLD);
    CSRW(CSR_SIREG, 0);

    /** Disable all interrupts */
    CSRW(CSR_SISELECT, IMSIC_EIE);
    CSRW(CSR_SIREG, 0x0);

    /** Enable interrupt delivery */
    CSRW(CSR_SISELECT, IMSIC_EIDELIVERY);
    CSRW(CSR_SIREG, 1);

    /** Map the interrupt files */
    imsic[cpu()->id] = (void*) mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, 
                    INVALID_VA, 
                    platform.arch.irqc.aia.imsic.base+(cpu()->id*PAGE_SIZE*IMSIC_NUM_FILES), 
                    NUM_PAGES(sizeof(struct imsic_global_hw)));
}

void imsic_set_enbl(irqid_t intp_id){
    CSRW(CSR_SISELECT, IMSIC_EIE+(intp_id/64));
    CSRS(CSR_SIREG, 1ULL << (intp_id%64));
}

bool imsic_get_pend(irqid_t intp_id){
    CSRW(CSR_SISELECT, IMSIC_EIP+(intp_id/64));
    return CSRR(CSR_SIREG) && (1ULL << (intp_id%64));
}

void imsic_clr_pend(irqid_t intp_id){
    CSRW(CSR_SISELECT, IMSIC_EIP+(intp_id/64));
    CSRC(CSR_SIREG, 1ULL << (intp_id%64));
}

/**
 * For now we only support 1 guest file per hart.
 * Should I remove the guest_file from the API? 
 */
void imsic_inject_pend(size_t guest_file, irqid_t intp_id){
    // vcpu->regs.hstatus = (guest_file << HSTATUS_VGEIN_OFF);
    CSRW(CSR_VSISELECT, IMSIC_EIP+(intp_id/64));
    CSRC(CSR_VSIREG, 1ULL << (intp_id%64));
}

void imsic_send_msi(cpuid_t target_cpu, irqid_t ipi_id){
    imsic[target_cpu]->s_file.seteipnum_le = ipi_id;
}

ssize_t imsic_find_available_msi(void){
    return bitmap_find_nth(msi_reserved, IMSIC_MAX_INTERRUPTS, 1, 0, 0);
}

void imsic_reserve_msi(irqid_t msi_id){
    bitmap_set(msi_reserved, msi_id);
}

void imsic_handle(void){
    uint32_t intp_identity = (CSRR(CSR_STOPEI) >> STOPEI_EEID);

    if (intp_identity != 0){
        enum irq_res res = interrupts_handle(intp_identity + IRQC_MSI_INTERRUPTS_START_ID);
        if (res == HANDLED_BY_HYP){
            /** Write to STOPEI to clear the interrupt */
            CSRW(CSR_STOPEI, 0);
        }
    };
}