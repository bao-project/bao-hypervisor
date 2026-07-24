/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_RDC.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_RDC
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
 * The SoC header defines typedef for all modules.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
 * The SoC header defines macros for all modules and registers.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
 * These are generated macros used for accessing the bit-fields from registers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.1, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.2, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.4, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.5, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
 * This type qualifier is needed to ensure correct I/O access and addressing.
 */

/* Prevention from multiple including the same memory map */
#if !defined(S32Z2_RDC_H_) /* Check if memory map has not been already included */
#define S32Z2_RDC_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- RDC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RDC_Peripheral_Access_Layer RDC Peripheral Access Layer
 * @{
 */

/** RDC - Register Layout Typedef */
typedef struct {
    uint8_t RESERVED_0[4];
    __IO uint32_t RD1_CTRL_REG; /**< Software Reset Domain Control, offset: 0x4 */
    uint8_t RESERVED_1[124];
    __I uint32_t RD1_STAT_REG;  /**< Software Reset Domain Status, offset: 0x84 */
} RDC_Type, *RDC_MemMapPtr;

/** Number of instances of the RDC module. */
#define RDC_INSTANCE_COUNT                                        (2u)

/* RDC - Peripheral instance base addresses */
/** Peripheral RDC_0 base address */
#define IP_RDC_0_BASE                                             (0x41890000u)
/** Peripheral RDC_0 base pointer */
#define IP_RDC_0                                                  ((RDC_Type*)IP_RDC_0_BASE)
/** Peripheral RDC_1 base address */
#define IP_RDC_1_BASE                                             (0x418A0000u)
/** Peripheral RDC_1 base pointer */
#define IP_RDC_1                                                  ((RDC_Type*)IP_RDC_1_BASE)
/** Array initializer of RDC peripheral base addresses */
#define IP_RDC_BASE_ADDRS                                         { IP_RDC_0_BASE, IP_RDC_1_BASE }
/** Array initializer of RDC peripheral base pointers */
#define IP_RDC_BASE_PTRS                                          { IP_RDC_0, IP_RDC_1 }

/* ----------------------------------------------------------------------------
   -- RDC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RDC_Register_Masks RDC Register Masks
 * @{
 */

/*! @name RD1_CTRL_REG - Software Reset Domain Control */
/*! @{ */

#define RDC_RD1_CTRL_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_MASK  (0x8U)
#define RDC_RD1_CTRL_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_SHIFT (3U)
#define RDC_RD1_CTRL_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_WIDTH (1U)
#define RDC_RD1_CTRL_REG_RD1_INTERCONNECT_INTERFACE_DISABLE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RDC_RD1_CTRL_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_SHIFT)) & \
        RDC_RD1_CTRL_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_MASK)

#define RDC_RD1_CTRL_REG_RD1_CTRL_UNLOCK_MASK  (0x80000000U)
#define RDC_RD1_CTRL_REG_RD1_CTRL_UNLOCK_SHIFT (31U)
#define RDC_RD1_CTRL_REG_RD1_CTRL_UNLOCK_WIDTH (1U)
#define RDC_RD1_CTRL_REG_RD1_CTRL_UNLOCK(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RDC_RD1_CTRL_REG_RD1_CTRL_UNLOCK_SHIFT)) & \
        RDC_RD1_CTRL_REG_RD1_CTRL_UNLOCK_MASK)
/*! @} */

/*! @name RD1_STAT_REG - Software Reset Domain Status */
/*! @{ */

#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_REQ_ACK_STAT_MASK  (0x8U)
#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_REQ_ACK_STAT_SHIFT (3U)
#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_REQ_ACK_STAT_WIDTH (1U)
#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_REQ_ACK_STAT(x)            \
    (((uint32_t)(((uint32_t)(x))                                                       \
         << RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_REQ_ACK_STAT_SHIFT)) & \
        RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_REQ_ACK_STAT_MASK)

#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_STAT_MASK  (0x10U)
#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_STAT_SHIFT (4U)
#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_STAT_WIDTH (1U)
#define RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_STAT(x)            \
    (((uint32_t)(((uint32_t)(x))                                               \
         << RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_STAT_SHIFT)) & \
        RDC_RD1_STAT_REG_RD1_INTERCONNECT_INTERFACE_DISABLE_STAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group RDC_Register_Masks */

/*!
 * @}
 */ /* end of group RDC_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_RDC_H_) */
