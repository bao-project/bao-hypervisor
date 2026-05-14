/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR1_PCTL.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR1_PCTL
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
#if !defined(S32Z2_GPR1_PCTL_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR1_PCTL_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR1_PCTL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR1_PCTL_Peripheral_Access_Layer GPR1_PCTL Peripheral Access Layer
 * @{
 */

/** GPR1_PCTL - Register Layout Typedef */
typedef struct {
    __IO uint32_t I3C1PCTL;  /**< LPI2C_1 Clock Control Enable, offset: 0x0 */
    __IO uint32_t EDMA1PCTL; /**< eDMA_1 Clock Control Enable, offset: 0x4 */
    __IO uint32_t DSPI2PCTL; /**< SPI_2 Clock Control Enable, offset: 0x8 */
    __IO uint32_t DSPI3PCTL; /**< SPI_3 Clock Control Enable, offset: 0xC */
    __IO uint32_t DSPI4PCTL; /**< SPI_4 Clock Control Enable, offset: 0x10 */
    __IO uint32_t LIN3PCTL;  /**< LINFlex_3 Clock Control Enable, offset: 0x14 */
    __IO uint32_t LIN4PCTL;  /**< LINFlex_4 Clock Control Enable, offset: 0x18 */
    __IO uint32_t LIN5PCTL;  /**< LINFlex_5 Clock Control Enable, offset: 0x1C */
    __IO uint32_t SIPI0PCTL; /**< SIPI_0 Clock Control Enable, offset: 0x20 */
    __IO uint32_t SIPI1PCTL; /**< SIPI_1 Clock Control Enable, offset: 0x24 */
    __IO uint32_t SRX0PCTL;  /**< SRX_0 Clock Control Enable, offset: 0x28 */
    uint8_t RESERVED_0[4];
    __IO uint32_t ENET0PCTL; /**< ENET_0 Clock Control Enable, offset: 0x30 */
    uint8_t RESERVED_1[4];
    __IO uint32_t SIUL1PCTL; /**< SIUL2_1 Clock Control Enable, offset: 0x38 */
} GPR1_PCTL_Type, *GPR1_PCTL_MemMapPtr;

/** Number of instances of the GPR1_PCTL module. */
#define GPR1_PCTL_INSTANCE_COUNT      (1u)

/* GPR1_PCTL - Peripheral instance base addresses */
/** Peripheral GPR1_PCTL base address */
#define IP_GPR1_PCTL_BASE             (0x40810000u)
/** Peripheral GPR1_PCTL base pointer */
#define IP_GPR1_PCTL                  ((GPR1_PCTL_Type*)IP_GPR1_PCTL_BASE)
/** Array initializer of GPR1_PCTL peripheral base addresses */
#define IP_GPR1_PCTL_BASE_ADDRS       { IP_GPR1_PCTL_BASE }
/** Array initializer of GPR1_PCTL peripheral base pointers */
#define IP_GPR1_PCTL_BASE_PTRS        { IP_GPR1_PCTL }

/* ----------------------------------------------------------------------------
   -- GPR1_PCTL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR1_PCTL_Register_Masks GPR1_PCTL Register Masks
 * @{
 */

/*! @name I3C1PCTL - LPI2C_1 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_I3C1PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_I3C1PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_I3C1PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_I3C1PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_I3C1PCTL_PCTL_SHIFT)) & GPR1_PCTL_I3C1PCTL_PCTL_MASK)
/*! @} */

/*! @name EDMA1PCTL - eDMA_1 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_EDMA1PCTL_PCTL_0_MASK  (0x1U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_0_SHIFT (0U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_0_WIDTH (1U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_EDMA1PCTL_PCTL_0_SHIFT)) & \
        GPR1_PCTL_EDMA1PCTL_PCTL_0_MASK)

#define GPR1_PCTL_EDMA1PCTL_PCTL_1_MASK  (0x2U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_1_SHIFT (1U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_1_WIDTH (1U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_EDMA1PCTL_PCTL_1_SHIFT)) & \
        GPR1_PCTL_EDMA1PCTL_PCTL_1_MASK)

#define GPR1_PCTL_EDMA1PCTL_PCTL_2_MASK  (0x4U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_2_SHIFT (2U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_2_WIDTH (1U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_EDMA1PCTL_PCTL_2_SHIFT)) & \
        GPR1_PCTL_EDMA1PCTL_PCTL_2_MASK)

#define GPR1_PCTL_EDMA1PCTL_PCTL_3_MASK  (0x8U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_3_SHIFT (3U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_3_WIDTH (1U)
#define GPR1_PCTL_EDMA1PCTL_PCTL_3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_EDMA1PCTL_PCTL_3_SHIFT)) & \
        GPR1_PCTL_EDMA1PCTL_PCTL_3_MASK)
/*! @} */

/*! @name DSPI2PCTL - SPI_2 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_DSPI2PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_DSPI2PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_DSPI2PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_DSPI2PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_DSPI2PCTL_PCTL_SHIFT)) & \
        GPR1_PCTL_DSPI2PCTL_PCTL_MASK)
/*! @} */

/*! @name DSPI3PCTL - SPI_3 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_DSPI3PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_DSPI3PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_DSPI3PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_DSPI3PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_DSPI3PCTL_PCTL_SHIFT)) & \
        GPR1_PCTL_DSPI3PCTL_PCTL_MASK)
/*! @} */

/*! @name DSPI4PCTL - SPI_4 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_DSPI4PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_DSPI4PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_DSPI4PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_DSPI4PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_DSPI4PCTL_PCTL_SHIFT)) & \
        GPR1_PCTL_DSPI4PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN3PCTL - LINFlex_3 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_LIN3PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_LIN3PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_LIN3PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_LIN3PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_LIN3PCTL_PCTL_SHIFT)) & GPR1_PCTL_LIN3PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN4PCTL - LINFlex_4 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_LIN4PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_LIN4PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_LIN4PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_LIN4PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_LIN4PCTL_PCTL_SHIFT)) & GPR1_PCTL_LIN4PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN5PCTL - LINFlex_5 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_LIN5PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_LIN5PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_LIN5PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_LIN5PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_LIN5PCTL_PCTL_SHIFT)) & GPR1_PCTL_LIN5PCTL_PCTL_MASK)
/*! @} */

/*! @name SIPI0PCTL - SIPI_0 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_SIPI0PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_SIPI0PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_SIPI0PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_SIPI0PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_SIPI0PCTL_PCTL_SHIFT)) & \
        GPR1_PCTL_SIPI0PCTL_PCTL_MASK)
/*! @} */

/*! @name SIPI1PCTL - SIPI_1 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_SIPI1PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_SIPI1PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_SIPI1PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_SIPI1PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_SIPI1PCTL_PCTL_SHIFT)) & \
        GPR1_PCTL_SIPI1PCTL_PCTL_MASK)
/*! @} */

/*! @name SRX0PCTL - SRX_0 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_SRX0PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_SRX0PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_SRX0PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_SRX0PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_SRX0PCTL_PCTL_SHIFT)) & GPR1_PCTL_SRX0PCTL_PCTL_MASK)
/*! @} */

/*! @name ENET0PCTL - ENET_0 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_ENET0PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_ENET0PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_ENET0PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_ENET0PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_ENET0PCTL_PCTL_SHIFT)) & \
        GPR1_PCTL_ENET0PCTL_PCTL_MASK)
/*! @} */

/*! @name SIUL1PCTL - SIUL2_1 Clock Control Enable */
/*! @{ */

#define GPR1_PCTL_SIUL1PCTL_PCTL_MASK  (0x1U)
#define GPR1_PCTL_SIUL1PCTL_PCTL_SHIFT (0U)
#define GPR1_PCTL_SIUL1PCTL_PCTL_WIDTH (1U)
#define GPR1_PCTL_SIUL1PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR1_PCTL_SIUL1PCTL_PCTL_SHIFT)) & \
        GPR1_PCTL_SIUL1PCTL_PCTL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR1_PCTL_Register_Masks */

/*!
 * @}
 */ /* end of group GPR1_PCTL_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR1_PCTL_H_) */
