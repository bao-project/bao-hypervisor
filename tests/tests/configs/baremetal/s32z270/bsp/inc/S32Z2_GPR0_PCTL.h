/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR0_PCTL.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR0_PCTL
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
#if !defined(S32Z2_GPR0_PCTL_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR0_PCTL_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR0_PCTL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR0_PCTL_Peripheral_Access_Layer GPR0_PCTL Peripheral Access Layer
 * @{
 */

/** GPR0_PCTL - Register Layout Typedef */
typedef struct {
    uint8_t RESERVED_0[4];
    __IO uint32_t DSPI0PCTL;   /**< SPI_0 Clock Control Enable, offset: 0x4 */
    __IO uint32_t FR0PCTL;     /**< FlexRay_0 Clock Control Enable, offset: 0x8 */
    __IO uint32_t FR1PCTL;     /**< FlexRay_1 Clock Control Enable, offset: 0xC */
    __IO uint32_t I3C0PCTL;    /**< I3C_0 Clock Control Enable, offset: 0x10 */
    __IO uint32_t EDMA0PCTL;   /**< eDMA_0 Clock Control Enable, offset: 0x14 */
    __IO uint32_t MSCDSPIPCTL; /**< MSC_0_DSPI Clock Control Enable, offset: 0x18 */
    __IO uint32_t DSPI1PCTL;   /**< SPI_1 Clock Control Enable, offset: 0x1C */
    __IO uint32_t LIN0PCTL;    /**< LINFlex_0 Clock Control Enable, offset: 0x20 */
    __IO uint32_t LIN1PCTL;    /**< LINFlex_1 Clock Control Enable, offset: 0x24 */
    __IO uint32_t LIN2PCTL;    /**< LINFlex_2 Clock Control Enable, offset: 0x28 */
    __IO uint32_t MSCLINPCTL;  /**< MSC_0_LIN Clock Control Enable, offset: 0x2C */
    __IO uint32_t ADC1PCTL;    /**< ADC_1 Clock Control Enable, offset: 0x30 */
    __IO uint32_t ADC0PCTL;    /**< ADC_0 Clock Control Enable, offset: 0x34 */
    uint8_t RESERVED_1[20];
    __IO uint32_t PSI50PCTL;   /**< PSI5_0 Clock Control Enable, offset: 0x4C */
    __IO uint32_t CTUPCTL;     /**< CTU Clock Control Enable, offset: 0x50 */
    __IO uint32_t SIUL0PCTL;   /**< SIUL2_0 Clock Control Enable, offset: 0x54 */
    __IO uint32_t GTMNANOPCTL; /**< GTM NANO Clock Control Enable, offset: 0x58 */
    __IO uint32_t PSI5S0PCTL;  /**< PSI5_S_0 Clock Control Enable, offset: 0x5C */
    __IO uint32_t SINCPCTL;    /**< SINC Clock Control Enable, offset: 0x60 */
} GPR0_PCTL_Type, *GPR0_PCTL_MemMapPtr;

/** Number of instances of the GPR0_PCTL module. */
#define GPR0_PCTL_INSTANCE_COUNT       (1u)

/* GPR0_PCTL - Peripheral instance base addresses */
/** Peripheral GPR0_PCTL base address */
#define IP_GPR0_PCTL_BASE              (0x40010000u)
/** Peripheral GPR0_PCTL base pointer */
#define IP_GPR0_PCTL                   ((GPR0_PCTL_Type*)IP_GPR0_PCTL_BASE)
/** Array initializer of GPR0_PCTL peripheral base addresses */
#define IP_GPR0_PCTL_BASE_ADDRS        { IP_GPR0_PCTL_BASE }
/** Array initializer of GPR0_PCTL peripheral base pointers */
#define IP_GPR0_PCTL_BASE_PTRS         { IP_GPR0_PCTL }

/* ----------------------------------------------------------------------------
   -- GPR0_PCTL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR0_PCTL_Register_Masks GPR0_PCTL Register Masks
 * @{
 */

/*! @name DSPI0PCTL - SPI_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_DSPI0PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_DSPI0PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_DSPI0PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_DSPI0PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_DSPI0PCTL_PCTL_SHIFT)) & \
        GPR0_PCTL_DSPI0PCTL_PCTL_MASK)
/*! @} */

/*! @name FR0PCTL - FlexRay_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_FR0PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_FR0PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_FR0PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_FR0PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_FR0PCTL_PCTL_SHIFT)) & GPR0_PCTL_FR0PCTL_PCTL_MASK)
/*! @} */

/*! @name FR1PCTL - FlexRay_1 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_FR1PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_FR1PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_FR1PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_FR1PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_FR1PCTL_PCTL_SHIFT)) & GPR0_PCTL_FR1PCTL_PCTL_MASK)
/*! @} */

/*! @name I3C0PCTL - I3C_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_I3C0PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_I3C0PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_I3C0PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_I3C0PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_I3C0PCTL_PCTL_SHIFT)) & GPR0_PCTL_I3C0PCTL_PCTL_MASK)
/*! @} */

/*! @name EDMA0PCTL - eDMA_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_EDMA0PCTL_PCTL_0_MASK  (0x1U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_0_SHIFT (0U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_0_WIDTH (1U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_EDMA0PCTL_PCTL_0_SHIFT)) & \
        GPR0_PCTL_EDMA0PCTL_PCTL_0_MASK)

#define GPR0_PCTL_EDMA0PCTL_PCTL_1_MASK  (0x2U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_1_SHIFT (1U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_1_WIDTH (1U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_EDMA0PCTL_PCTL_1_SHIFT)) & \
        GPR0_PCTL_EDMA0PCTL_PCTL_1_MASK)

#define GPR0_PCTL_EDMA0PCTL_PCTL_2_MASK  (0x4U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_2_SHIFT (2U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_2_WIDTH (1U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_EDMA0PCTL_PCTL_2_SHIFT)) & \
        GPR0_PCTL_EDMA0PCTL_PCTL_2_MASK)

#define GPR0_PCTL_EDMA0PCTL_PCTL_3_MASK  (0x8U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_3_SHIFT (3U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_3_WIDTH (1U)
#define GPR0_PCTL_EDMA0PCTL_PCTL_3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_EDMA0PCTL_PCTL_3_SHIFT)) & \
        GPR0_PCTL_EDMA0PCTL_PCTL_3_MASK)
/*! @} */

/*! @name MSCDSPIPCTL - MSC_0_DSPI Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_MSCDSPIPCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_MSCDSPIPCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_MSCDSPIPCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_MSCDSPIPCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_MSCDSPIPCTL_PCTL_SHIFT)) & \
        GPR0_PCTL_MSCDSPIPCTL_PCTL_MASK)
/*! @} */

/*! @name DSPI1PCTL - SPI_1 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_DSPI1PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_DSPI1PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_DSPI1PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_DSPI1PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_DSPI1PCTL_PCTL_SHIFT)) & \
        GPR0_PCTL_DSPI1PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN0PCTL - LINFlex_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_LIN0PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_LIN0PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_LIN0PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_LIN0PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_LIN0PCTL_PCTL_SHIFT)) & GPR0_PCTL_LIN0PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN1PCTL - LINFlex_1 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_LIN1PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_LIN1PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_LIN1PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_LIN1PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_LIN1PCTL_PCTL_SHIFT)) & GPR0_PCTL_LIN1PCTL_PCTL_MASK)
/*! @} */

/*! @name LIN2PCTL - LINFlex_2 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_LIN2PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_LIN2PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_LIN2PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_LIN2PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_LIN2PCTL_PCTL_SHIFT)) & GPR0_PCTL_LIN2PCTL_PCTL_MASK)
/*! @} */

/*! @name MSCLINPCTL - MSC_0_LIN Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_MSCLINPCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_MSCLINPCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_MSCLINPCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_MSCLINPCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_MSCLINPCTL_PCTL_SHIFT)) & \
        GPR0_PCTL_MSCLINPCTL_PCTL_MASK)
/*! @} */

/*! @name ADC1PCTL - ADC_1 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_ADC1PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_ADC1PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_ADC1PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_ADC1PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_ADC1PCTL_PCTL_SHIFT)) & GPR0_PCTL_ADC1PCTL_PCTL_MASK)
/*! @} */

/*! @name ADC0PCTL - ADC_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_ADC0PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_ADC0PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_ADC0PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_ADC0PCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_ADC0PCTL_PCTL_SHIFT)) & GPR0_PCTL_ADC0PCTL_PCTL_MASK)
/*! @} */

/*! @name PSI50PCTL - PSI5_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_PSI50PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_PSI50PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_PSI50PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_PSI50PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_PSI50PCTL_PCTL_SHIFT)) & \
        GPR0_PCTL_PSI50PCTL_PCTL_MASK)
/*! @} */

/*! @name CTUPCTL - CTU Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_CTUPCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_CTUPCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_CTUPCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_CTUPCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_CTUPCTL_PCTL_SHIFT)) & GPR0_PCTL_CTUPCTL_PCTL_MASK)
/*! @} */

/*! @name SIUL0PCTL - SIUL2_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_SIUL0PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_SIUL0PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_SIUL0PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_SIUL0PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_SIUL0PCTL_PCTL_SHIFT)) & \
        GPR0_PCTL_SIUL0PCTL_PCTL_MASK)
/*! @} */

/*! @name GTMNANOPCTL - GTM NANO Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_GTMNANOPCTL_PCTL_GTM_MASK  (0x1U)
#define GPR0_PCTL_GTMNANOPCTL_PCTL_GTM_SHIFT (0U)
#define GPR0_PCTL_GTMNANOPCTL_PCTL_GTM_WIDTH (1U)
#define GPR0_PCTL_GTMNANOPCTL_PCTL_GTM(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_GTMNANOPCTL_PCTL_GTM_SHIFT)) & \
        GPR0_PCTL_GTMNANOPCTL_PCTL_GTM_MASK)

#define GPR0_PCTL_GTMNANOPCTL_PCTL_NANO_MASK  (0x2U)
#define GPR0_PCTL_GTMNANOPCTL_PCTL_NANO_SHIFT (1U)
#define GPR0_PCTL_GTMNANOPCTL_PCTL_NANO_WIDTH (1U)
#define GPR0_PCTL_GTMNANOPCTL_PCTL_NANO(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_GTMNANOPCTL_PCTL_NANO_SHIFT)) & \
        GPR0_PCTL_GTMNANOPCTL_PCTL_NANO_MASK)
/*! @} */

/*! @name PSI5S0PCTL - PSI5_S_0 Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_PSI5S0PCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_PSI5S0PCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_PSI5S0PCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_PSI5S0PCTL_PCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_PSI5S0PCTL_PCTL_SHIFT)) & \
        GPR0_PCTL_PSI5S0PCTL_PCTL_MASK)
/*! @} */

/*! @name SINCPCTL - SINC Clock Control Enable */
/*! @{ */

#define GPR0_PCTL_SINCPCTL_PCTL_MASK  (0x1U)
#define GPR0_PCTL_SINCPCTL_PCTL_SHIFT (0U)
#define GPR0_PCTL_SINCPCTL_PCTL_WIDTH (1U)
#define GPR0_PCTL_SINCPCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_PCTL_SINCPCTL_PCTL_SHIFT)) & GPR0_PCTL_SINCPCTL_PCTL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR0_PCTL_Register_Masks */

/*!
 * @}
 */ /* end of group GPR0_PCTL_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR0_PCTL_H_) */
