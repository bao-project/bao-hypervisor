/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef IMSIC_H
#define IMSIC_H

#include <bao.h>
#include <platform.h>

#define IMSIC_MAX_INTERRUPTS (PLAT_IMSIC_MAX_INTERRUPTS)
/** We only support 1 guest per hart at the moment */
#define IMSIC_NUM_VS_FILES   (1)
#define IMSIC_NUM_FILES      (IMSIC_NUM_VS_FILES + 1)

#define STOPEI_EEID          (16)

#define IMSIC_EIDELIVERY     (0x70)
#define IMSIC_EITHRESHOLD    (0x72)
#define IMSIC_EIP            (0x80)
#define IMSIC_EIE            (0xC0)

struct imsic_intp_file_hw {
    uint32_t seteipnum_le;
    uint32_t seteipnum_be;
} __attribute__((__packed__, aligned(0x1000ULL)));

struct imsic_global_hw {
    struct imsic_intp_file_hw s_file;
    struct imsic_intp_file_hw guest_file;
} __attribute__((__packed__, aligned(0x1000ULL)));

extern volatile struct imsic_global_hw* imsic[PLAT_CPU_NUM];

/**
 * @brief Initializes the IMSIC
 *
 *        The function initializes the IMSIC by configuring its registers and mapping the S-lvl
 *        interrupt file. It sets every intp as triggerable, disables all interrupts, enables
 *        interrupt delivery, and maps the S-lvl interrupt file in memory.
 *
 */
void imsic_init(void);

/**
 * @brief Check if a given interrupt is pending for the cpu that calls the function
 *
 * @param intp_id the interrupt to check
 * @return true the interrupt is pending
 * @return false the interrupt is not pending
 */
bool imsic_get_pend(irqid_t intp_id);

/**
 * @brief Clear the pending bit of a given interrupt
 *
 * @param intp_id interrupt ID
 */
void imsic_clr_pend(irqid_t intp_id);

/**
 * @brief enables a given interrupt for the IMSIC that executes the function
 *
 * @param intp_id the interrupt to enable
 */
void imsic_set_enbl(irqid_t intp_id);

/**
 * @brief Sends an MSI to the specified CPU with the specified IPI ID.
 *
 *        The function sends an MSI to the specified CPU by setting the seteipnum_le register in the
 *        IMSIC. The seteipnum_le register is used to specify the ID of the interrupt being sent.
 *        Only little endian is supported.
 *
 * @param target_cpu The ID of the target CPU
 */
static inline void imsic_send_msi(cpuid_t target_cpu, irqid_t msi_id)
{
    imsic[target_cpu]->s_file.seteipnum_le = msi_id;
}

/**
 * @brief Sends an MSI to the guest file specified CPU with the specified IPI ID.
 *
 *        The function sends an MSI to the guest file specified CPU by setting the seteipnum_le
 *        register in the IMSIC. The seteipnum_le register is used to specify the ID of the
 *        interrupt being sent. Only little endian is supported. This function assume a single guest
 *        interrupt file per hart.
 *
 * @param target_cpu The ID of the target CPU
 */
static inline void imsic_send_guest_msi(cpuid_t target_cpu, irqid_t msi_id)
{
    imsic[target_cpu]->guest_file.seteipnum_le = msi_id;
}

/**
 * @brief Handles interrupts in the IMSIC.
 *
 *        The function handles interrupts in the IMSIC by looping through
 *        all pending interrupts and calling the interrupts_handle()
 *        function to handle each one. If an interrupt is handled by the
 *        hypervisor, the function writes to the STOPEI CSR to clear the
 *        interrupt. Otherwise, the Guest cleans it.
 *
 */
void imsic_handle(void);

/**
 * @brief Allocate an MSI ID for hypervisor use
 *
 * @return irqid_t the allocated MSI ID
 */
irqid_t imsic_allocate_msi(void);

#endif // IMSIC_H
