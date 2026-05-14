/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR5_PCTL.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR5_PCTL
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
#if !defined(S32Z2_GPR5_PCTL_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR5_PCTL_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR5_PCTL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR5_PCTL_Peripheral_Access_Layer GPR5_PCTL Peripheral Access Layer
 * @{
 */

/** GPR5_PCTL - Register Layout Typedef */
typedef struct {
    __IO uint32_t EDMA5PCTL; /**< eDMA_5 Clock Control Enable, offset: 0x0 */
    __IO uint32_t DSPI8PCTL; /**< SPI_8 Clock Control Enable, offset: 0x4 */
    __IO uint32_t DSPI9PCTL; /**< SPI_9 Clock Control Enable, offset: 0x8 */
    __IO uint32_t LIN9PCTL;  /**< LINFlex_9 Clock Control Enable, offset: 0xC */
    __IO uint32_t LIN10PCTL; /**< LINFlex_10 Clock Control Enable, offset: 0x10 */
    __IO uint32_t LIN11PCTL; /**< LINFlex_11 Clock Control Enable, offset: 0x14 */
    __IO uint32_t SIUL5PCTL; /**< SIUL2_5 Clock Control Enable, offset: 0x18 */
} GPR5_PCTL_Type, *GPR5_PCTL_MemMapPtr;

/** Number of instances of the GPR5_PCTL module. */
#define GPR5_PCTL_INSTANCE_COUNT         (1u)

/* GPR5_PCTL - Peripheral instance base addresses */
/** Peripheral GPR5_PCTL base address */
#define IP_GPR5_PCTL_BASE                (0x42810000u)
/** Peripheral GPR5_PCTL base pointer */
#define IP_GPR5_PCTL                     ((GPR5_PCTL_Type*)IP_GPR5_PCTL_BASE)
/** Array initializer of GPR5_PCTL peripheral base addresses */
#define IP_GPR5_PCTL_BASE_ADDRS          { IP_GPR5_PCTL_BASE }
/** Array initializer of GPR5_PCTL peripheral base pointers */
#define IP_GPR5_PCTL_BASE_PTRS           { IP_GPR5_PCTL }

/* ----------------------------------------------------------------------------
   -- GPR5_PCTL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR5_PCTL_Register_Masks GPR5_PCTL Register Masks
 * @{
 */

/*! @name EDMA5PCTL - eDMA_5 Clock Control Enable */
/*! @{ */

#define GPR5_PCTL_EDMA5PCTL_PCTL_0_MASK  (0x1U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_0_SHIFT (0U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_0_WIDTH (1U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_EDMA5PCTL_PCTL_0_SHIFT)) & \
        GPR5_PCTL_EDMA5PCTL_PCTL_0_MASK)

#define GPR5_PCTL_EDMA5PCTL_PCTL_1_MASK  (0x2U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_1_SHIFT (1U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_1_WIDTH (1U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_EDMA5PCTL_PCTL_1_SHIFT)) & \
        GPR5_PCTL_EDMA5PCTL_PCTL_1_MASK)

#define GPR5_PCTL_EDMA5PCTL_PCTL_2_MASK  (0x4U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_2_SHIFT (2U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_2_WIDTH (1U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_EDMA5PCTL_PCTL_2_SHIFT)) & \
        GPR5_PCTL_EDMA5PCTL_PCTL_2_MASK)

#define GPR5_PCTL_EDMA5PCTL_PCTL_3_MASK  (0x8U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_3_SHIFT (3U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_3_WIDTH (1U)
#define GPR5_PCTL_EDMA5PCTL_PCTL_3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_EDMA5PCTL_PCTL_3_SHIFT)) & \
        GPR5_PCTL_EDMA5PCTL_PCTL_3_MASK)
/*! @} */

/*! @name DSPI8PCTL - SPI_8 Clock Control Enable */
/*! @{ */

#define GPR5_PCTL_DSPI8PCTL_PCTL_MASK  (0x1U)
#define GPR5_PCTL_DSPI8PCTL_PCTL_SHIFT (0U)
#define GPR5_PCTL_DSPI8PCTL_PCTL_WIDTH (1U)
#define GPR5_PCTL_DSPI8PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_DSPI8PCTL_PCTL_SHIFT)) & \
        GPR5_PCTL_DSPI8PCTL_PCTL_MASK)
/*! @} */

/*! @name DSPI9PCTL - SPI_9 Clock Control Enable */
/*! @{ */

#define GPR5_PCTL_DSPI9PCTL_PCTL_MASK  (0x1U)
#define GPR5_PCTL_DSPI9PCTL_PCTL_SHIFT (0U)
#define GPR5_PCTL_DSPI9PCTL_PCTL_WIDTH (1U)
#define GPR5_PCTL_DSPI9PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_DSPI9PCTL_PCTL_SHIFT)) & \
        GPR5_PCTL_DSPI9PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN9PCTL - LINFlex_9 Clock Control Enable */
/*! @{ */

#define GPR5_PCTL_LIN9PCTL_PCTL_MASK  (0x1U)
#define GPR5_PCTL_LIN9PCTL_PCTL_SHIFT (0U)
#define GPR5_PCTL_LIN9PCTL_PCTL_WIDTH (1U)
#define GPR5_PCTL_LIN9PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_LIN9PCTL_PCTL_SHIFT)) & GPR5_PCTL_LIN9PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN10PCTL - LINFlex_10 Clock Control Enable */
/*! @{ */

#define GPR5_PCTL_LIN10PCTL_PCTL_MASK  (0x1U)
#define GPR5_PCTL_LIN10PCTL_PCTL_SHIFT (0U)
#define GPR5_PCTL_LIN10PCTL_PCTL_WIDTH (1U)
#define GPR5_PCTL_LIN10PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_LIN10PCTL_PCTL_SHIFT)) & \
        GPR5_PCTL_LIN10PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN11PCTL - LINFlex_11 Clock Control Enable */
/*! @{ */

#define GPR5_PCTL_LIN11PCTL_PCTL_MASK  (0x1U)
#define GPR5_PCTL_LIN11PCTL_PCTL_SHIFT (0U)
#define GPR5_PCTL_LIN11PCTL_PCTL_WIDTH (1U)
#define GPR5_PCTL_LIN11PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_LIN11PCTL_PCTL_SHIFT)) & \
        GPR5_PCTL_LIN11PCTL_PCTL_MASK)
/*! @} */

/*! @name SIUL5PCTL - SIUL2_5 Clock Control Enable */
/*! @{ */

#define GPR5_PCTL_SIUL5PCTL_PCTL_MASK  (0x1U)
#define GPR5_PCTL_SIUL5PCTL_PCTL_SHIFT (0U)
#define GPR5_PCTL_SIUL5PCTL_PCTL_WIDTH (1U)
#define GPR5_PCTL_SIUL5PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR5_PCTL_SIUL5PCTL_PCTL_SHIFT)) & \
        GPR5_PCTL_SIUL5PCTL_PCTL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR5_PCTL_Register_Masks */

/*!
 * @}
 */ /* end of group GPR5_PCTL_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR5_PCTL_H_) */
