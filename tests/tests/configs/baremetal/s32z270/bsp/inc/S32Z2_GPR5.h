/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR5.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR5
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
#if !defined(S32Z2_GPR5_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR5_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR5 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR5_Peripheral_Access_Layer GPR5 Peripheral Access Layer
 * @{
 */

/** GPR5 - Register Layout Typedef */
typedef struct {
    __IO uint32_t LVFCCUGD5;  /**< VFCCU Global DID register 5, offset: 0x0 */
    __IO uint32_t LVFCCULD15; /**< VFCCU Local DID register 15, offset: 0x4 */
    __IO uint32_t LVFCCULD16; /**< VFCCU Local DID register 16, offset: 0x8 */
    __IO uint32_t LVFCCULD17; /**< VFCCU Local DID register 17, offset: 0xC */
    uint8_t RESERVED_0[20];
    __IO uint32_t DESTC10;    /**< CANXL_PE_CLK Configuration, offset: 0x24 */
    uint8_t RESERVED_1[28];
    __I uint32_t INITM5;      /**< NoC Initiator NIU Timeout Status, offset: 0x44 */
    __I uint32_t TARGTMS5;    /**< NoC Target NIU Timeout Status, offset: 0x48 */
    __IO uint32_t TARGTMC5;   /**< NoC Target NIU Timeout Control, offset: 0x4C */
    uint8_t RESERVED_2[4];
    __IO uint32_t CLKOUT3SEL; /**< CLKOUT_3 MUX select, offset: 0x54 */
} GPR5_Type, *GPR5_MemMapPtr;

/** Number of instances of the GPR5 module. */
#define GPR5_INSTANCE_COUNT       (1u)

/* GPR5 - Peripheral instance base addresses */
/** Peripheral GPR5 base address */
#define IP_GPR5_BASE              (0x42860000u)
/** Peripheral GPR5 base pointer */
#define IP_GPR5                   ((GPR5_Type*)IP_GPR5_BASE)
/** Array initializer of GPR5 peripheral base addresses */
#define IP_GPR5_BASE_ADDRS        { IP_GPR5_BASE }
/** Array initializer of GPR5 peripheral base pointers */
#define IP_GPR5_BASE_PTRS         { IP_GPR5 }

/* ----------------------------------------------------------------------------
   -- GPR5 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR5_Register_Masks GPR5 Register Masks
 * @{
 */

/*! @name LVFCCUGD5 - VFCCU Global DID register 5 */
/*! @{ */

#define GPR5_LVFCCUGD5_FHID_MASK  (0xFU)
#define GPR5_LVFCCUGD5_FHID_SHIFT (0U)
#define GPR5_LVFCCUGD5_FHID_WIDTH (4U)
#define GPR5_LVFCCUGD5_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_LVFCCUGD5_FHID_SHIFT)) & GPR5_LVFCCUGD5_FHID_MASK)
/*! @} */

/*! @name LVFCCULD15 - VFCCU Local DID register 15 */
/*! @{ */

#define GPR5_LVFCCULD15_FHID_MASK  (0xFFFFFFFFU)
#define GPR5_LVFCCULD15_FHID_SHIFT (0U)
#define GPR5_LVFCCULD15_FHID_WIDTH (32U)
#define GPR5_LVFCCULD15_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_LVFCCULD15_FHID_SHIFT)) & GPR5_LVFCCULD15_FHID_MASK)
/*! @} */

/*! @name LVFCCULD16 - VFCCU Local DID register 16 */
/*! @{ */

#define GPR5_LVFCCULD16_FHID_MASK  (0xFFFFFFFFU)
#define GPR5_LVFCCULD16_FHID_SHIFT (0U)
#define GPR5_LVFCCULD16_FHID_WIDTH (32U)
#define GPR5_LVFCCULD16_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_LVFCCULD16_FHID_SHIFT)) & GPR5_LVFCCULD16_FHID_MASK)
/*! @} */

/*! @name LVFCCULD17 - VFCCU Local DID register 17 */
/*! @{ */

#define GPR5_LVFCCULD17_FHID_MASK  (0xFFFFFFFFU)
#define GPR5_LVFCCULD17_FHID_SHIFT (0U)
#define GPR5_LVFCCULD17_FHID_WIDTH (32U)
#define GPR5_LVFCCULD17_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_LVFCCULD17_FHID_SHIFT)) & GPR5_LVFCCULD17_FHID_MASK)
/*! @} */

/*! @name DESTC10 - CANXL_PE_CLK Configuration */
/*! @{ */

#define GPR5_DESTC10_CTRL_MASK  (0xFFFFFFFFU)
#define GPR5_DESTC10_CTRL_SHIFT (0U)
#define GPR5_DESTC10_CTRL_WIDTH (32U)
#define GPR5_DESTC10_CTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_DESTC10_CTRL_SHIFT)) & GPR5_DESTC10_CTRL_MASK)
/*! @} */

/*! @name INITM5 - NoC Initiator NIU Timeout Status */
/*! @{ */

#define GPR5_INITM5_STAT_MASK  (0xFFFFFFFFU)
#define GPR5_INITM5_STAT_SHIFT (0U)
#define GPR5_INITM5_STAT_WIDTH (32U)
#define GPR5_INITM5_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_INITM5_STAT_SHIFT)) & GPR5_INITM5_STAT_MASK)
/*! @} */

/*! @name TARGTMS5 - NoC Target NIU Timeout Status */
/*! @{ */

#define GPR5_TARGTMS5_STAT_MASK  (0xFFFFFFFFU)
#define GPR5_TARGTMS5_STAT_SHIFT (0U)
#define GPR5_TARGTMS5_STAT_WIDTH (32U)
#define GPR5_TARGTMS5_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_TARGTMS5_STAT_SHIFT)) & GPR5_TARGTMS5_STAT_MASK)
/*! @} */

/*! @name TARGTMC5 - NoC Target NIU Timeout Control */
/*! @{ */

#define GPR5_TARGTMC5_EN_MASK  (0xFFFFFFFFU)
#define GPR5_TARGTMC5_EN_SHIFT (0U)
#define GPR5_TARGTMC5_EN_WIDTH (32U)
#define GPR5_TARGTMC5_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_TARGTMC5_EN_SHIFT)) & GPR5_TARGTMC5_EN_MASK)
/*! @} */

/*! @name CLKOUT3SEL - CLKOUT_3 MUX select */
/*! @{ */

#define GPR5_CLKOUT3SEL_MUXSEL_MASK  (0xFU)
#define GPR5_CLKOUT3SEL_MUXSEL_SHIFT (0U)
#define GPR5_CLKOUT3SEL_MUXSEL_WIDTH (4U)
#define GPR5_CLKOUT3SEL_MUXSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR5_CLKOUT3SEL_MUXSEL_SHIFT)) & GPR5_CLKOUT3SEL_MUXSEL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR5_Register_Masks */

/*!
 * @}
 */ /* end of group GPR5_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR5_H_) */
