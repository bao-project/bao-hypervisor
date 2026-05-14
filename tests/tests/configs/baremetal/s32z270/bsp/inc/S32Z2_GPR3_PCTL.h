/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR3_PCTL.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR3_PCTL
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
#if !defined(S32Z2_GPR3_PCTL_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR3_PCTL_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR3_PCTL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR3_PCTL_Peripheral_Access_Layer GPR3_PCTL Peripheral Access Layer
 * @{
 */

/** GPR3_PCTL - Register Layout Typedef */
typedef struct {
    __IO uint32_t EDMA3PCTL;  /**< eDMA_3 Clock Control Enable, offset: 0x0 */
    __IO uint32_t EDMACEPCTL; /**< CE_eDMA Clock Control Enable, offset: 0x4 */
    uint8_t RESERVED_0[4];
    __IO uint32_t CAN0PCTL;   /**< CE_CAN_0 Clock Control Enable, offset: 0xC */
    __IO uint32_t CAN1PCTL;   /**< CE_CAN_1 Clock Control Enable, offset: 0x10 */
    __IO uint32_t CAN2PCTL;   /**< CE_CAN_2 Clock Control Enable, offset: 0x14 */
    __IO uint32_t CAN3PCTL;   /**< CE_CAN_3 Clock Control Enable, offset: 0x18 */
    __IO uint32_t CAN4PCTL;   /**< CE_CAN_4 Clock Control Enable, offset: 0x1C */
    __IO uint32_t CAN5PCTL;   /**< CE_CAN_5 Clock Control Enable, offset: 0x20 */
    __IO uint32_t CAN6PCTL;   /**< CE_CAN_6 Clock Control Enable, offset: 0x24 */
    __IO uint32_t CAN7PCTL;   /**< CE_CAN_7 Clock Control Enable, offset: 0x28 */
    __IO uint32_t CAN8PCTL;   /**< CE_CAN_8 Clock Control Enable, offset: 0x2C */
    __IO uint32_t CAN9PCTL;   /**< CE_CAN_9 Clock Control Enable, offset: 0x30 */
    __IO uint32_t CAN10PCTL;  /**< CE_CAN_10 Clock Control Enable, offset: 0x34 */
    __IO uint32_t CAN11PCTL;  /**< CE_CAN_11 Clock Control Enable, offset: 0x38 */
    __IO uint32_t CAN12PCTL;  /**< CE_CAN_12 Clock Control Enable, offset: 0x3C */
    __IO uint32_t CAN13PCTL;  /**< CE_CAN_13 Clock Control Enable, offset: 0x40 */
    __IO uint32_t CAN14PCTL;  /**< CE_CAN_14 Clock Control Enable, offset: 0x44 */
    __IO uint32_t CAN15PCTL;  /**< CE_CAN_15 Clock Control Enable, offset: 0x48 */
    __IO uint32_t CAN16PCTL;  /**< CE_CAN_16 Clock Control Enable, offset: 0x4C */
    __IO uint32_t CAN17PCTL;  /**< CE_CAN_17 Clock Control Enable, offset: 0x50 */
    __IO uint32_t CAN18PCTL;  /**< CE_CAN_18 Clock Control Enable, offset: 0x54 */
    __IO uint32_t CAN19PCTL;  /**< CE_CAN_19 Clock Control Enable, offset: 0x58 */
    __IO uint32_t CAN20PCTL;  /**< CE_CAN_20 Clock Control Enable, offset: 0x5C */
    __IO uint32_t CAN21PCTL;  /**< CE_CAN_21 Clock Control Enable, offset: 0x60 */
    __IO uint32_t CAN22PCTL;  /**< CE_CAN_22 Clock Control Enable, offset: 0x64 */
    __IO uint32_t CAN23PCTL;  /**< CE_CAN_23 Clock Control Enable, offset: 0x68 */
    __IO uint32_t PIT0PCTL;   /**< CE_PIT_0 Clock Control Enable, offset: 0x6C */
    __IO uint32_t PIT1PCTL;   /**< CE_PIT_1 Clock Control Enable, offset: 0x70 */
    __IO uint32_t PIT2PCTL;   /**< CE_PIT_2 Clock Control Enable, offset: 0x74 */
    __IO uint32_t PIT3PCTL;   /**< CE_PIT_3 Clock Control Enable, offset: 0x78 */
    __IO uint32_t PIT4PCTL;   /**< CE_PIT_4 Clock Control Enable, offset: 0x7C */
    __IO uint32_t PIT5PCTL;   /**< CE_PIT_5 Clock Control Enable, offset: 0x80 */
    __IO uint32_t RXLUTPCTL;  /**< RXLUT Clock Control Enable, offset: 0x84 */
} GPR3_PCTL_Type, *GPR3_PCTL_MemMapPtr;

/** Number of instances of the GPR3_PCTL module. */
#define GPR3_PCTL_INSTANCE_COUNT       (1u)

/* GPR3_PCTL - Peripheral instance base addresses */
/** Peripheral GPR3_PCTL base address */
#define IP_GPR3_PCTL_BASE              (0x41810000u)
/** Peripheral GPR3_PCTL base pointer */
#define IP_GPR3_PCTL                   ((GPR3_PCTL_Type*)IP_GPR3_PCTL_BASE)
/** Array initializer of GPR3_PCTL peripheral base addresses */
#define IP_GPR3_PCTL_BASE_ADDRS        { IP_GPR3_PCTL_BASE }
/** Array initializer of GPR3_PCTL peripheral base pointers */
#define IP_GPR3_PCTL_BASE_PTRS         { IP_GPR3_PCTL }

/* ----------------------------------------------------------------------------
   -- GPR3_PCTL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR3_PCTL_Register_Masks GPR3_PCTL Register Masks
 * @{
 */

/*! @name EDMA3PCTL - eDMA_3 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_EDMA3PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_EDMA3PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_EDMA3PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_EDMA3PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_EDMA3PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_EDMA3PCTL_PCTL_MASK)
/*! @} */

/*! @name EDMACEPCTL - CE_eDMA Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_EDMACEPCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_EDMACEPCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_EDMACEPCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_EDMACEPCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_EDMACEPCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_EDMACEPCTL_PCTL_MASK)
/*! @} */

/*! @name CAN0PCTL - CE_CAN_0 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN0PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN0PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN0PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN0PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN0PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN0PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN1PCTL - CE_CAN_1 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN1PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN1PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN1PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN1PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN1PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN1PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN2PCTL - CE_CAN_2 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN2PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN2PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN2PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN2PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN2PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN2PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN3PCTL - CE_CAN_3 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN3PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN3PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN3PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN3PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN3PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN3PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN4PCTL - CE_CAN_4 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN4PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN4PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN4PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN4PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN4PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN4PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN5PCTL - CE_CAN_5 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN5PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN5PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN5PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN5PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN5PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN5PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN6PCTL - CE_CAN_6 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN6PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN6PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN6PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN6PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN6PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN6PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN7PCTL - CE_CAN_7 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN7PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN7PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN7PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN7PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN7PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN7PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN8PCTL - CE_CAN_8 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN8PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN8PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN8PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN8PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN8PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN8PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN9PCTL - CE_CAN_9 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN9PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN9PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN9PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN9PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN9PCTL_PCTL_SHIFT)) & GPR3_PCTL_CAN9PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN10PCTL - CE_CAN_10 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN10PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN10PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN10PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN10PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN10PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN10PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN11PCTL - CE_CAN_11 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN11PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN11PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN11PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN11PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN11PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN11PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN12PCTL - CE_CAN_12 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN12PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN12PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN12PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN12PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN12PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN12PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN13PCTL - CE_CAN_13 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN13PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN13PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN13PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN13PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN13PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN13PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN14PCTL - CE_CAN_14 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN14PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN14PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN14PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN14PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN14PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN14PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN15PCTL - CE_CAN_15 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN15PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN15PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN15PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN15PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN15PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN15PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN16PCTL - CE_CAN_16 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN16PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN16PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN16PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN16PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN16PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN16PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN17PCTL - CE_CAN_17 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN17PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN17PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN17PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN17PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN17PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN17PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN18PCTL - CE_CAN_18 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN18PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN18PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN18PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN18PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN18PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN18PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN19PCTL - CE_CAN_19 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN19PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN19PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN19PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN19PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN19PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN19PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN20PCTL - CE_CAN_20 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN20PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN20PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN20PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN20PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN20PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN20PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN21PCTL - CE_CAN_21 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN21PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN21PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN21PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN21PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN21PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN21PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN22PCTL - CE_CAN_22 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN22PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN22PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN22PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN22PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN22PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN22PCTL_PCTL_MASK)
/*! @} */

/*! @name CAN23PCTL - CE_CAN_23 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_CAN23PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_CAN23PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_CAN23PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_CAN23PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_CAN23PCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_CAN23PCTL_PCTL_MASK)
/*! @} */

/*! @name PIT0PCTL - CE_PIT_0 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_PIT0PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_PIT0PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_PIT0PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_PIT0PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_PIT0PCTL_PCTL_SHIFT)) & GPR3_PCTL_PIT0PCTL_PCTL_MASK)
/*! @} */

/*! @name PIT1PCTL - CE_PIT_1 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_PIT1PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_PIT1PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_PIT1PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_PIT1PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_PIT1PCTL_PCTL_SHIFT)) & GPR3_PCTL_PIT1PCTL_PCTL_MASK)
/*! @} */

/*! @name PIT2PCTL - CE_PIT_2 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_PIT2PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_PIT2PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_PIT2PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_PIT2PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_PIT2PCTL_PCTL_SHIFT)) & GPR3_PCTL_PIT2PCTL_PCTL_MASK)
/*! @} */

/*! @name PIT3PCTL - CE_PIT_3 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_PIT3PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_PIT3PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_PIT3PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_PIT3PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_PIT3PCTL_PCTL_SHIFT)) & GPR3_PCTL_PIT3PCTL_PCTL_MASK)
/*! @} */

/*! @name PIT4PCTL - CE_PIT_4 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_PIT4PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_PIT4PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_PIT4PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_PIT4PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_PIT4PCTL_PCTL_SHIFT)) & GPR3_PCTL_PIT4PCTL_PCTL_MASK)
/*! @} */

/*! @name PIT5PCTL - CE_PIT_5 Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_PIT5PCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_PIT5PCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_PIT5PCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_PIT5PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_PIT5PCTL_PCTL_SHIFT)) & GPR3_PCTL_PIT5PCTL_PCTL_MASK)
/*! @} */

/*! @name RXLUTPCTL - RXLUT Clock Control Enable */
/*! @{ */

#define GPR3_PCTL_RXLUTPCTL_PCTL_MASK  (0x1U)
#define GPR3_PCTL_RXLUTPCTL_PCTL_SHIFT (0U)
#define GPR3_PCTL_RXLUTPCTL_PCTL_WIDTH (1U)
#define GPR3_PCTL_RXLUTPCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_PCTL_RXLUTPCTL_PCTL_SHIFT)) & \
        GPR3_PCTL_RXLUTPCTL_PCTL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR3_PCTL_Register_Masks */

/*!
 * @}
 */ /* end of group GPR3_PCTL_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR3_PCTL_H_) */
