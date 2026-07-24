/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR4_PCTL.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR4_PCTL
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
#if !defined(S32Z2_GPR4_PCTL_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR4_PCTL_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR4_PCTL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR4_PCTL_Peripheral_Access_Layer GPR4_PCTL Peripheral Access Layer
 * @{
 */

/** GPR4_PCTL - Register Layout Typedef */
typedef struct {
    __IO uint32_t QSPI0PCTL;  /**< QuadSPI_0 Clock Control Enable, offset: 0x0 */
    __IO uint32_t QSPI1PCTL;  /**< QuadSPI_1 Clock Control Enable, offset: 0x4 */
    __IO uint32_t EDMA4PCTL;  /**< eDMA_4 Clock Control Enable, offset: 0x8 */
    __IO uint32_t DSPI5PCTL;  /**< SPI_5 Clock Control Enable, offset: 0xC */
    __IO uint32_t DSPI6PCTL;  /**< SPI_6 Clock Control Enable, offset: 0x10 */
    __IO uint32_t DSPI7PCTL;  /**< SPI_7 Clock Control Enable, offset: 0x14 */
    __IO uint32_t LIN6PCTL;   /**< LINFlex_6 Clock Control Enable, offset: 0x18 */
    __IO uint32_t LIN7PCTL;   /**< LINFlex_7 Clock Control Enable, offset: 0x1C */
    __IO uint32_t LIN8PCTL;   /**< LINFlex_8 Clock Control Enable, offset: 0x20 */
    __IO uint32_t SDHCPCTL;   /**< uSDHC Clock Control Enable, offset: 0x24 */
    __IO uint32_t SRX1PCTL;   /**< SRX_1 Clock Control Enable, offset: 0x28 */
    __IO uint32_t I3C2PCTL;   /**< LPI2C_2 Clock Control Enable, offset: 0x2C */
    __IO uint32_t PSI51PCTL;  /**< PSI5_1 Clock Control Enable, offset: 0x30 */
    __IO uint32_t SIUL4PCTL;  /**< SIUL2_4 Clock Control Enable, offset: 0x34 */
    __IO uint32_t PSI5S1PCTL; /**< PSI5_S_1 Clock Control Enable, offset: 0x38 */
} GPR4_PCTL_Type, *GPR4_PCTL_MemMapPtr;

/** Number of instances of the GPR4_PCTL module. */
#define GPR4_PCTL_INSTANCE_COUNT       (1u)

/* GPR4_PCTL - Peripheral instance base addresses */
/** Peripheral GPR4_PCTL base address */
#define IP_GPR4_PCTL_BASE              (0x42010000u)
/** Peripheral GPR4_PCTL base pointer */
#define IP_GPR4_PCTL                   ((GPR4_PCTL_Type*)IP_GPR4_PCTL_BASE)
/** Array initializer of GPR4_PCTL peripheral base addresses */
#define IP_GPR4_PCTL_BASE_ADDRS        { IP_GPR4_PCTL_BASE }
/** Array initializer of GPR4_PCTL peripheral base pointers */
#define IP_GPR4_PCTL_BASE_PTRS         { IP_GPR4_PCTL }

/* ----------------------------------------------------------------------------
   -- GPR4_PCTL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR4_PCTL_Register_Masks GPR4_PCTL Register Masks
 * @{
 */

/*! @name QSPI0PCTL - QuadSPI_0 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_QSPI0PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_QSPI0PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_QSPI0PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_QSPI0PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_QSPI0PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_QSPI0PCTL_PCTL_MASK)
/*! @} */

/*! @name QSPI1PCTL - QuadSPI_1 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_QSPI1PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_QSPI1PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_QSPI1PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_QSPI1PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_QSPI1PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_QSPI1PCTL_PCTL_MASK)
/*! @} */

/*! @name EDMA4PCTL - eDMA_4 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_EDMA4PCTL_PCTL_0_MASK  (0x1U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_0_SHIFT (0U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_0_WIDTH (1U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_EDMA4PCTL_PCTL_0_SHIFT)) & \
        GPR4_PCTL_EDMA4PCTL_PCTL_0_MASK)

#define GPR4_PCTL_EDMA4PCTL_PCTL_1_MASK  (0x2U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_1_SHIFT (1U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_1_WIDTH (1U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_EDMA4PCTL_PCTL_1_SHIFT)) & \
        GPR4_PCTL_EDMA4PCTL_PCTL_1_MASK)

#define GPR4_PCTL_EDMA4PCTL_PCTL_2_MASK  (0x4U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_2_SHIFT (2U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_2_WIDTH (1U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_EDMA4PCTL_PCTL_2_SHIFT)) & \
        GPR4_PCTL_EDMA4PCTL_PCTL_2_MASK)

#define GPR4_PCTL_EDMA4PCTL_PCTL_3_MASK  (0x8U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_3_SHIFT (3U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_3_WIDTH (1U)
#define GPR4_PCTL_EDMA4PCTL_PCTL_3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_EDMA4PCTL_PCTL_3_SHIFT)) & \
        GPR4_PCTL_EDMA4PCTL_PCTL_3_MASK)
/*! @} */

/*! @name DSPI5PCTL - SPI_5 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_DSPI5PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_DSPI5PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_DSPI5PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_DSPI5PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_DSPI5PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_DSPI5PCTL_PCTL_MASK)
/*! @} */

/*! @name DSPI6PCTL - SPI_6 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_DSPI6PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_DSPI6PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_DSPI6PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_DSPI6PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_DSPI6PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_DSPI6PCTL_PCTL_MASK)
/*! @} */

/*! @name DSPI7PCTL - SPI_7 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_DSPI7PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_DSPI7PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_DSPI7PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_DSPI7PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_DSPI7PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_DSPI7PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN6PCTL - LINFlex_6 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_LIN6PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_LIN6PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_LIN6PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_LIN6PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_LIN6PCTL_PCTL_SHIFT)) & GPR4_PCTL_LIN6PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN7PCTL - LINFlex_7 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_LIN7PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_LIN7PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_LIN7PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_LIN7PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_LIN7PCTL_PCTL_SHIFT)) & GPR4_PCTL_LIN7PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN8PCTL - LINFlex_8 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_LIN8PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_LIN8PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_LIN8PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_LIN8PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_LIN8PCTL_PCTL_SHIFT)) & GPR4_PCTL_LIN8PCTL_PCTL_MASK)
/*! @} */

/*! @name SDHCPCTL - uSDHC Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_SDHCPCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_SDHCPCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_SDHCPCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_SDHCPCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_SDHCPCTL_PCTL_SHIFT)) & GPR4_PCTL_SDHCPCTL_PCTL_MASK)
/*! @} */

/*! @name SRX1PCTL - SRX_1 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_SRX1PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_SRX1PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_SRX1PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_SRX1PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_SRX1PCTL_PCTL_SHIFT)) & GPR4_PCTL_SRX1PCTL_PCTL_MASK)
/*! @} */

/*! @name I3C2PCTL - LPI2C_2 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_I3C2PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_I3C2PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_I3C2PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_I3C2PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_I3C2PCTL_PCTL_SHIFT)) & GPR4_PCTL_I3C2PCTL_PCTL_MASK)
/*! @} */

/*! @name PSI51PCTL - PSI5_1 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_PSI51PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_PSI51PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_PSI51PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_PSI51PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_PSI51PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_PSI51PCTL_PCTL_MASK)
/*! @} */

/*! @name SIUL4PCTL - SIUL2_4 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_SIUL4PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_SIUL4PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_SIUL4PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_SIUL4PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_SIUL4PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_SIUL4PCTL_PCTL_MASK)
/*! @} */

/*! @name PSI5S1PCTL - PSI5_S_1 Clock Control Enable */
/*! @{ */

#define GPR4_PCTL_PSI5S1PCTL_PCTL_MASK  (0x1U)
#define GPR4_PCTL_PSI5S1PCTL_PCTL_SHIFT (0U)
#define GPR4_PCTL_PSI5S1PCTL_PCTL_WIDTH (1U)
#define GPR4_PCTL_PSI5S1PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR4_PCTL_PSI5S1PCTL_PCTL_SHIFT)) & \
        GPR4_PCTL_PSI5S1PCTL_PCTL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR4_PCTL_Register_Masks */

/*!
 * @}
 */ /* end of group GPR4_PCTL_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR4_PCTL_H_) */
