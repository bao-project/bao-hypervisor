/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR0.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR0
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
#if !defined(S32Z2_GPR0_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR0_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR0 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR0_Peripheral_Access_Layer GPR0 Peripheral Access Layer
 * @{
 */

/** GPR0 - Register Layout Typedef */
typedef struct {
    __IO uint32_t LVFCCUGD0;  /**< VFCCU Global DID register 0, offset: 0x0 */
    __IO uint32_t LVFCCULD0;  /**< VFCCU Local DID register 0, offset: 0x4 */
    __IO uint32_t LVFCCULD1;  /**< VFCCU Local DID register 1, offset: 0x8 */
    __IO uint32_t LVFCCULD2;  /**< VFCCU Local DID register 2, offset: 0xC */
    __IO uint32_t FROSTICKC;  /**< FlexRay OS Tick Mux Selector, offset: 0x10 */
    uint8_t RESERVED_0[36];
    __IO uint32_t FUNCC0;     /**< Source Control for SINC HTRIGs, offset: 0x38 */
    uint8_t RESERVED_1[12];
    __I uint32_t INITM0;      /**< NoC Initiator NIU Timeout Status, offset: 0x48 */
    __I uint32_t TARGTMS0;    /**< NoC Target NIU Timeout Status, offset: 0x4C */
    __IO uint32_t TARGTMC0;   /**< NoC Target NIU Timeout Control, offset: 0x50 */
    uint8_t RESERVED_2[4];
    __IO uint32_t CLKOUT0SEL; /**< CLKOUT_0 MUX select, offset: 0x58 */
} GPR0_Type, *GPR0_MemMapPtr;

/** Number of instances of the GPR0 module. */
#define GPR0_INSTANCE_COUNT       (1u)

/* GPR0 - Peripheral instance base addresses */
/** Peripheral GPR0 base address */
#define IP_GPR0_BASE              (0x40060000u)
/** Peripheral GPR0 base pointer */
#define IP_GPR0                   ((GPR0_Type*)IP_GPR0_BASE)
/** Array initializer of GPR0 peripheral base addresses */
#define IP_GPR0_BASE_ADDRS        { IP_GPR0_BASE }
/** Array initializer of GPR0 peripheral base pointers */
#define IP_GPR0_BASE_PTRS         { IP_GPR0 }

/* ----------------------------------------------------------------------------
   -- GPR0 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR0_Register_Masks GPR0 Register Masks
 * @{
 */

/*! @name LVFCCUGD0 - VFCCU Global DID register 0 */
/*! @{ */

#define GPR0_LVFCCUGD0_FHID_MASK  (0xFU)
#define GPR0_LVFCCUGD0_FHID_SHIFT (0U)
#define GPR0_LVFCCUGD0_FHID_WIDTH (4U)
#define GPR0_LVFCCUGD0_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_LVFCCUGD0_FHID_SHIFT)) & GPR0_LVFCCUGD0_FHID_MASK)
/*! @} */

/*! @name LVFCCULD0 - VFCCU Local DID register 0 */
/*! @{ */

#define GPR0_LVFCCULD0_FHID_MASK  (0xFFFFFFFFU)
#define GPR0_LVFCCULD0_FHID_SHIFT (0U)
#define GPR0_LVFCCULD0_FHID_WIDTH (32U)
#define GPR0_LVFCCULD0_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_LVFCCULD0_FHID_SHIFT)) & GPR0_LVFCCULD0_FHID_MASK)
/*! @} */

/*! @name LVFCCULD1 - VFCCU Local DID register 1 */
/*! @{ */

#define GPR0_LVFCCULD1_FHID_MASK  (0xFFFFFFFFU)
#define GPR0_LVFCCULD1_FHID_SHIFT (0U)
#define GPR0_LVFCCULD1_FHID_WIDTH (32U)
#define GPR0_LVFCCULD1_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_LVFCCULD1_FHID_SHIFT)) & GPR0_LVFCCULD1_FHID_MASK)
/*! @} */

/*! @name LVFCCULD2 - VFCCU Local DID register 2 */
/*! @{ */

#define GPR0_LVFCCULD2_FHID_MASK  (0xFFFFFFFFU)
#define GPR0_LVFCCULD2_FHID_SHIFT (0U)
#define GPR0_LVFCCULD2_FHID_WIDTH (32U)
#define GPR0_LVFCCULD2_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_LVFCCULD2_FHID_SHIFT)) & GPR0_LVFCCULD2_FHID_MASK)
/*! @} */

/*! @name FROSTICKC - FlexRay OS Tick Mux Selector */
/*! @{ */

#define GPR0_FROSTICKC_SEL_MASK  (0x3U)
#define GPR0_FROSTICKC_SEL_SHIFT (0U)
#define GPR0_FROSTICKC_SEL_WIDTH (2U)
#define GPR0_FROSTICKC_SEL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_FROSTICKC_SEL_SHIFT)) & GPR0_FROSTICKC_SEL_MASK)
/*! @} */

/*! @name FUNCC0 - Source Control for SINC HTRIGs */
/*! @{ */

#define GPR0_FUNCC0_CTRL_MASK  (0xFFFFFFFFU)
#define GPR0_FUNCC0_CTRL_SHIFT (0U)
#define GPR0_FUNCC0_CTRL_WIDTH (32U)
#define GPR0_FUNCC0_CTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_FUNCC0_CTRL_SHIFT)) & GPR0_FUNCC0_CTRL_MASK)
/*! @} */

/*! @name INITM0 - NoC Initiator NIU Timeout Status */
/*! @{ */

#define GPR0_INITM0_STAT_MASK  (0xFFFFFFFFU)
#define GPR0_INITM0_STAT_SHIFT (0U)
#define GPR0_INITM0_STAT_WIDTH (32U)
#define GPR0_INITM0_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_INITM0_STAT_SHIFT)) & GPR0_INITM0_STAT_MASK)
/*! @} */

/*! @name TARGTMS0 - NoC Target NIU Timeout Status */
/*! @{ */

#define GPR0_TARGTMS0_STAT_MASK  (0xFFFFFFFFU)
#define GPR0_TARGTMS0_STAT_SHIFT (0U)
#define GPR0_TARGTMS0_STAT_WIDTH (32U)
#define GPR0_TARGTMS0_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_TARGTMS0_STAT_SHIFT)) & GPR0_TARGTMS0_STAT_MASK)
/*! @} */

/*! @name TARGTMC0 - NoC Target NIU Timeout Control */
/*! @{ */

#define GPR0_TARGTMC0_EN_MASK  (0xFFFFFFFFU)
#define GPR0_TARGTMC0_EN_SHIFT (0U)
#define GPR0_TARGTMC0_EN_WIDTH (32U)
#define GPR0_TARGTMC0_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_TARGTMC0_EN_SHIFT)) & GPR0_TARGTMC0_EN_MASK)
/*! @} */

/*! @name CLKOUT0SEL - CLKOUT_0 MUX select */
/*! @{ */

#define GPR0_CLKOUT0SEL_MUXSEL_MASK  (0x3FU)
#define GPR0_CLKOUT0SEL_MUXSEL_SHIFT (0U)
#define GPR0_CLKOUT0SEL_MUXSEL_WIDTH (6U)
#define GPR0_CLKOUT0SEL_MUXSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_CLKOUT0SEL_MUXSEL_SHIFT)) & GPR0_CLKOUT0SEL_MUXSEL_MASK)

#define GPR0_CLKOUT0SEL_CGEN_MASK  (0x40U)
#define GPR0_CLKOUT0SEL_CGEN_SHIFT (6U)
#define GPR0_CLKOUT0SEL_CGEN_WIDTH (1U)
#define GPR0_CLKOUT0SEL_CGEN(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR0_CLKOUT0SEL_CGEN_SHIFT)) & GPR0_CLKOUT0SEL_CGEN_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR0_Register_Masks */

/*!
 * @}
 */ /* end of group GPR0_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR0_H_) */
