/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR6_PCTL.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR6_PCTL
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
#if !defined(S32Z2_GPR6_PCTL_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR6_PCTL_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR6_PCTL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR6_PCTL_Peripheral_Access_Layer GPR6_PCTL Peripheral Access Layer
 * @{
 */

/** GPR6_PCTL - Register Layout Typedef */
typedef struct {
    __IO uint32_t DDRPCTL; /**< DDRC Clock Control Enable, offset: 0x0 */
} GPR6_PCTL_Type, *GPR6_PCTL_MemMapPtr;

/** Number of instances of the GPR6_PCTL module. */
#define GPR6_PCTL_INSTANCE_COUNT     (1u)

/* GPR6_PCTL - Peripheral instance base addresses */
/** Peripheral GPR6_PCTL base address */
#define IP_GPR6_PCTL_BASE            (0x44010000u)
/** Peripheral GPR6_PCTL base pointer */
#define IP_GPR6_PCTL                 ((GPR6_PCTL_Type*)IP_GPR6_PCTL_BASE)
/** Array initializer of GPR6_PCTL peripheral base addresses */
#define IP_GPR6_PCTL_BASE_ADDRS      { IP_GPR6_PCTL_BASE }
/** Array initializer of GPR6_PCTL peripheral base pointers */
#define IP_GPR6_PCTL_BASE_PTRS       { IP_GPR6_PCTL }

/* ----------------------------------------------------------------------------
   -- GPR6_PCTL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR6_PCTL_Register_Masks GPR6_PCTL Register Masks
 * @{
 */

/*! @name DDRPCTL - DDRC Clock Control Enable */
/*! @{ */

#define GPR6_PCTL_DDRPCTL_PCTL_MASK  (0x1U)
#define GPR6_PCTL_DDRPCTL_PCTL_SHIFT (0U)
#define GPR6_PCTL_DDRPCTL_PCTL_WIDTH (1U)
#define GPR6_PCTL_DDRPCTL_PCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR6_PCTL_DDRPCTL_PCTL_SHIFT)) & GPR6_PCTL_DDRPCTL_PCTL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR6_PCTL_Register_Masks */

/*!
 * @}
 */ /* end of group GPR6_PCTL_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR6_PCTL_H_) */
