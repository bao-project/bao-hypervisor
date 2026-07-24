/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_PLLDIG.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_PLLDIG
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
#if !defined(S32Z2_PLLDIG_H_) /* Check if memory map has not been already included */
#define S32Z2_PLLDIG_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- PLLDIG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLLDIG_Peripheral_Access_Layer PLLDIG Peripheral Access Layer
 * @{
 */

/** PLLDIG - Size of Registers Arrays */
#define PLLDIG_PLLODIV_COUNT 7u

/** PLLDIG - Register Layout Typedef */
typedef struct {
    __IO uint32_t PLLCR; /**< PLL Control, offset: 0x0 */
    __IO uint32_t PLLSR; /**< PLL Status, offset: 0x4 */
    __IO uint32_t PLLDV; /**< PLL Divider, offset: 0x8 */
    __IO uint32_t PLLFM; /**< PLL Frequency Modulation, offset: 0xC, available only on: CORE_PLL,
                            DDR_PLL (missing on PERIPH_PLL) */
    __IO uint32_t PLLFD; /**< PLL Fractional Divider, offset: 0x10 */
    uint8_t RESERVED_0[12];
    __IO uint32_t PLLCLKMUX;                     /**< PLL Clock Multiplexer, offset: 0x20 */
    uint8_t RESERVED_1[92];
    __IO uint32_t PLLODIV[PLLDIG_PLLODIV_COUNT]; /**< PLL Output Divider, array offset: 0x80, array
                                                    step: 0x4, irregular array, not all indices are
                                                    valid */
} PLLDIG_Type, *PLLDIG_MemMapPtr;

/** Number of instances of the PLLDIG module. */
#define PLLDIG_INSTANCE_COUNT    (3u)

/* PLLDIG - Peripheral instance base addresses */
/** Peripheral CORE_PLL base address */
#define IP_CORE_PLL_BASE         (0x40210000u)
/** Peripheral CORE_PLL base pointer */
#define IP_CORE_PLL              ((PLLDIG_Type*)IP_CORE_PLL_BASE)
/** Peripheral DDR_PLL base address */
#define IP_DDR_PLL_BASE          (0x440A0000u)
/** Peripheral DDR_PLL base pointer */
#define IP_DDR_PLL               ((PLLDIG_Type*)IP_DDR_PLL_BASE)
/** Peripheral PERIPH_PLL base address */
#define IP_PERIPH_PLL_BASE       (0x40220000u)
/** Peripheral PERIPH_PLL base pointer */
#define IP_PERIPH_PLL            ((PLLDIG_Type*)IP_PERIPH_PLL_BASE)
/** Array initializer of PLLDIG peripheral base addresses */
#define IP_PLLDIG_BASE_ADDRS     { IP_CORE_PLL_BASE, IP_DDR_PLL_BASE, IP_PERIPH_PLL_BASE }
/** Array initializer of PLLDIG peripheral base pointers */
#define IP_PLLDIG_BASE_PTRS      { IP_CORE_PLL, IP_DDR_PLL, IP_PERIPH_PLL }

/* ----------------------------------------------------------------------------
   -- PLLDIG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLLDIG_Register_Masks PLLDIG Register Masks
 * @{
 */

/*! @name PLLCR - PLL Control */
/*! @{ */

#define PLLDIG_PLLCR_PLLPD_MASK  (0x80000000U)
#define PLLDIG_PLLCR_PLLPD_SHIFT (31U)
#define PLLDIG_PLLCR_PLLPD_WIDTH (1U)
#define PLLDIG_PLLCR_PLLPD(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLCR_PLLPD_SHIFT)) & PLLDIG_PLLCR_PLLPD_MASK)
/*! @} */

/*! @name PLLSR - PLL Status */
/*! @{ */

#define PLLDIG_PLLSR_LOCK_MASK  (0x4U)
#define PLLDIG_PLLSR_LOCK_SHIFT (2U)
#define PLLDIG_PLLSR_LOCK_WIDTH (1U)
#define PLLDIG_PLLSR_LOCK(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLSR_LOCK_SHIFT)) & PLLDIG_PLLSR_LOCK_MASK)

#define PLLDIG_PLLSR_LOL_MASK  (0x8U)
#define PLLDIG_PLLSR_LOL_SHIFT (3U)
#define PLLDIG_PLLSR_LOL_WIDTH (1U)
#define PLLDIG_PLLSR_LOL(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLSR_LOL_SHIFT)) & PLLDIG_PLLSR_LOL_MASK)
/*! @} */

/*! @name PLLDV - PLL Divider */
/*! @{ */

#define PLLDIG_PLLDV_MFI_MASK  (0xFFU)
#define PLLDIG_PLLDV_MFI_SHIFT (0U)
#define PLLDIG_PLLDV_MFI_WIDTH (8U)
#define PLLDIG_PLLDV_MFI(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLDV_MFI_SHIFT)) & PLLDIG_PLLDV_MFI_MASK)

#define PLLDIG_PLLDV_RDIV_MASK  (0x7000U)
#define PLLDIG_PLLDV_RDIV_SHIFT (12U)
#define PLLDIG_PLLDV_RDIV_WIDTH (3U)
#define PLLDIG_PLLDV_RDIV(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLDV_RDIV_SHIFT)) & PLLDIG_PLLDV_RDIV_MASK)
/*! @} */

/*! @name PLLFM - PLL Frequency Modulation */
/*! @{ */

#define PLLDIG_PLLFM_STEPNO_MASK  (0x7FFU)
#define PLLDIG_PLLFM_STEPNO_SHIFT (0U)
#define PLLDIG_PLLFM_STEPNO_WIDTH (11U)
#define PLLDIG_PLLFM_STEPNO(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLFM_STEPNO_SHIFT)) & PLLDIG_PLLFM_STEPNO_MASK)

#define PLLDIG_PLLFM_STEPSIZE_MASK  (0x3FF0000U)
#define PLLDIG_PLLFM_STEPSIZE_SHIFT (16U)
#define PLLDIG_PLLFM_STEPSIZE_WIDTH (10U)
#define PLLDIG_PLLFM_STEPSIZE(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLFM_STEPSIZE_SHIFT)) & PLLDIG_PLLFM_STEPSIZE_MASK)

#define PLLDIG_PLLFM_SPREADCTL_MASK  (0x20000000U)
#define PLLDIG_PLLFM_SPREADCTL_SHIFT (29U)
#define PLLDIG_PLLFM_SPREADCTL_WIDTH (1U)
#define PLLDIG_PLLFM_SPREADCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLFM_SPREADCTL_SHIFT)) & PLLDIG_PLLFM_SPREADCTL_MASK)

#define PLLDIG_PLLFM_SSCGBYP_MASK  (0x40000000U)
#define PLLDIG_PLLFM_SSCGBYP_SHIFT (30U)
#define PLLDIG_PLLFM_SSCGBYP_WIDTH (1U)
#define PLLDIG_PLLFM_SSCGBYP(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLFM_SSCGBYP_SHIFT)) & PLLDIG_PLLFM_SSCGBYP_MASK)
/*! @} */

/*! @name PLLFD - PLL Fractional Divider */
/*! @{ */

#define PLLDIG_PLLFD_MFN_MASK  (0x7FFFU)
#define PLLDIG_PLLFD_MFN_SHIFT (0U)
#define PLLDIG_PLLFD_MFN_WIDTH (15U)
#define PLLDIG_PLLFD_MFN(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLFD_MFN_SHIFT)) & PLLDIG_PLLFD_MFN_MASK)

#define PLLDIG_PLLFD_SDMEN_MASK  (0x40000000U)
#define PLLDIG_PLLFD_SDMEN_SHIFT (30U)
#define PLLDIG_PLLFD_SDMEN_WIDTH (1U)
#define PLLDIG_PLLFD_SDMEN(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLFD_SDMEN_SHIFT)) & PLLDIG_PLLFD_SDMEN_MASK)
/*! @} */

/*! @name PLLCLKMUX - PLL Clock Multiplexer */
/*! @{ */

#define PLLDIG_PLLCLKMUX_REFCLKSEL_MASK  (0x1U)
#define PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT (0U)
#define PLLDIG_PLLCLKMUX_REFCLKSEL_WIDTH (1U)
#define PLLDIG_PLLCLKMUX_REFCLKSEL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT)) & \
        PLLDIG_PLLCLKMUX_REFCLKSEL_MASK)
/*! @} */

/*! @name PLLODIV - PLL Output Divider */
/*! @{ */

#define PLLDIG_PLLODIV_DIV_MASK  (0xFF0000U)
#define PLLDIG_PLLODIV_DIV_SHIFT (16U)
#define PLLDIG_PLLODIV_DIV_WIDTH (8U)
#define PLLDIG_PLLODIV_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLODIV_DIV_SHIFT)) & PLLDIG_PLLODIV_DIV_MASK)

#define PLLDIG_PLLODIV_DE_MASK  (0x80000000U)
#define PLLDIG_PLLODIV_DE_SHIFT (31U)
#define PLLDIG_PLLODIV_DE_WIDTH (1U)
#define PLLDIG_PLLODIV_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << PLLDIG_PLLODIV_DE_SHIFT)) & PLLDIG_PLLODIV_DE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group PLLDIG_Register_Masks */

/*!
 * @}
 */ /* end of group PLLDIG_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_PLLDIG_H_) */
