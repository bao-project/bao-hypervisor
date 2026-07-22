/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_BSP_COMMON_H__
#define __PLAT_BSP_COMMON_H__

/* Function-like macro used to wait for a condition to be met, most often used to wait for hardware register updates.
 * This macro can be redefined to add a timeout if necessary. */
#ifndef FSP_HARDWARE_REGISTER_WAIT
    #define FSP_HARDWARE_REGISTER_WAIT(reg, required_value)     while (reg != required_value) {__asm volatile ("nop");}
#endif

/* Read a register and discard the result. */
#ifndef FSP_REGISTER_READ
    #define FSP_REGISTER_READ(A)    __asm volatile ("" : : "r" (A));
#endif

#ifdef BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION
    #undef BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION
#endif
#define BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION    (0U)

#define BSP_FEATURE_BSP_IRQ_PRIORITY_POS_BIT           (3U)

/* This macro defines a variable for saving previous mask value */
#ifndef FSP_CRITICAL_SECTION_DEFINE
    #define FSP_CRITICAL_SECTION_DEFINE                   uintptr_t old_mask_level = 0U
#endif

/* These macros abstract methods to save and restore the interrupt state. */
#define FSP_CRITICAL_SECTION_GET_CURRENT_STATE         sysreg_icc_pmr_el1_read
#define FSP_CRITICAL_SECTION_SET_STATE                 sysreg_icc_pmr_el1_write
#define FSP_CRITICAL_SECTION_IRQ_MASK_SET              ((uint8_t) (BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION << \
                                                                BSP_FEATURE_BSP_IRQ_PRIORITY_POS_BIT))

/** This macro temporarily saves the current interrupt state and disables interrupts. */
 #ifndef FSP_CRITICAL_SECTION_ENTER
    #define FSP_CRITICAL_SECTION_ENTER                              \
        old_mask_level = FSP_CRITICAL_SECTION_GET_CURRENT_STATE();  \
        FSP_CRITICAL_SECTION_SET_STATE(FSP_CRITICAL_SECTION_IRQ_MASK_SET)
 #endif

/** This macro restores the previously saved interrupt state, reenabling interrupts. */
 #ifndef FSP_CRITICAL_SECTION_EXIT
  #define FSP_CRITICAL_SECTION_EXIT              FSP_CRITICAL_SECTION_SET_STATE(old_mask_level)
 #endif


/*******************************************************************************************************************//**
 * Cancels the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
 #define R_BSP_MODULE_START(ip, channel)    {FSP_CRITICAL_SECTION_DEFINE;                                   \
                                             FSP_CRITICAL_SECTION_ENTER;                                    \
                                             BSP_MSTP_REG_ ## ip(channel) &= ~BSP_MSTP_BIT_ ## ip(channel); \
                                             BSP_MSTP_REG_ ## ip(channel);                                  \
                                             BSP_MSTP_DMY_ ## ip(channel);                                  \
                                             BSP_MSTP_DMY_ ## ip(channel);                                  \
                                             BSP_MSTP_DMY_ ## ip(channel);                                  \
                                             BSP_MSTP_DMY_ ## ip(channel);                                  \
                                             BSP_MSTP_DMY_ ## ip(channel);                                  \
                                             BSP_MSTP_DMY_ ## ip(channel);                                  \
                                             BSP_MSTP_DMY_ ## ip(channel);                                  \
                                             FSP_CRITICAL_SECTION_EXIT;}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
 #define R_BSP_MODULE_STOP(ip, channel)     {FSP_CRITICAL_SECTION_DEFINE;                                  \
                                             FSP_CRITICAL_SECTION_ENTER;                                   \
                                             BSP_MSTP_REG_ ## ip(channel) |= BSP_MSTP_BIT_ ## ip(channel); \
                                             BSP_MSTP_REG_ ## ip(channel);                                 \
                                             FSP_CRITICAL_SECTION_EXIT;}


#define BSP_MSTP_REG_FSP_IP_SCI(channel)    *((4U >= channel) ? &R_SYSC_NS->MSTPCRA : &R_SYSC_S->MSTPCRG)
#define BSP_MSTP_BIT_FSP_IP_SCI(channel)    ((4U >= channel) ? (1U << (8U + channel)) : (1U))
#define BSP_MSTP_DMY_FSP_IP_SCI(channel)    ((0U == channel) ? R_SCI0->RDR :        \
                                             ((1U >= channel) ? R_SCI1->RDR :       \
                                              ((2U >= channel) ? R_SCI2->RDR :      \
                                               ((3U >= channel) ? R_SCI3->RDR :     \
                                                ((4U >= channel) ? R_SCI4->RDR :    \
                                                 ((5U >= channel) ? R_SCI5->RDR :   \
                                                  0))))))

#endif /* __PLAT_BSP_COMMON_H__ */