/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_RTUP_NIC_B.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_RTUP_NIC_B
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
#if !defined(S32Z2_RTUP_NIC_B_H_) /* Check if memory map has not been already included */
#define S32Z2_RTUP_NIC_B_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- RTUP_NIC_B Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTUP_NIC_B_Peripheral_Access_Layer RTUP_NIC_B Peripheral Access Layer
 * @{
 */

/** RTUP_NIC_B - Register Layout Typedef */
typedef struct {
    __O uint32_t REMAP; /**< Remap, offset: 0x0 */
} RTUP_NIC_B_Type, *RTUP_NIC_B_MemMapPtr;

/** Number of instances of the RTUP_NIC_B module. */
#define RTUP_NIC_B_INSTANCE_COUNT    (2u)

/* RTUP_NIC_B - Peripheral instance base addresses */
/** Peripheral RTU0__RTUP_NIC_B base address */
#define IP_RTU0__RTUP_NIC_B_BASE     (0x75200000u)
/** Peripheral RTU0__RTUP_NIC_B base pointer */
#define IP_RTU0__RTUP_NIC_B          ((RTUP_NIC_B_Type*)IP_RTU0__RTUP_NIC_B_BASE)
/** Peripheral RTU1__RTUP_NIC_B base address */
#define IP_RTU1__RTUP_NIC_B_BASE     (0x75600000u)
/** Peripheral RTU1__RTUP_NIC_B base pointer */
#define IP_RTU1__RTUP_NIC_B          ((RTUP_NIC_B_Type*)IP_RTU1__RTUP_NIC_B_BASE)
/** Array initializer of RTUP_NIC_B peripheral base addresses */
#define IP_RTUP_NIC_B_BASE_ADDRS     { IP_RTU0__RTUP_NIC_B_BASE, IP_RTU1__RTUP_NIC_B_BASE }
/** Array initializer of RTUP_NIC_B peripheral base pointers */
#define IP_RTUP_NIC_B_BASE_PTRS      { IP_RTU0__RTUP_NIC_B, IP_RTU1__RTUP_NIC_B }

/* ----------------------------------------------------------------------------
   -- RTUP_NIC_B Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTUP_NIC_B_Register_Masks RTUP_NIC_B Register Masks
 * @{
 */

/*! @name REMAP - Remap */
/*! @{ */

#define RTUP_NIC_B_REMAP_remap_MASK  (0x3U)
#define RTUP_NIC_B_REMAP_remap_SHIFT (0U)
#define RTUP_NIC_B_REMAP_remap_WIDTH (2U)
#define RTUP_NIC_B_REMAP_remap(x) \
    (((uint32_t)(((uint32_t)(x)) << RTUP_NIC_B_REMAP_remap_SHIFT)) & RTUP_NIC_B_REMAP_remap_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group RTUP_NIC_B_Register_Masks */

/*!
 * @}
 */ /* end of group RTUP_NIC_B_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_RTUP_NIC_B_H_) */
