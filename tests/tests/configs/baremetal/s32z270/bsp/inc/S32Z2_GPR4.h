/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR4.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR4
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
#if !defined(S32Z2_GPR4_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR4_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR4 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR4_Peripheral_Access_Layer GPR4 Peripheral Access Layer
 * @{
 */

/** GPR4 - Register Layout Typedef */
typedef struct {
    __IO uint32_t LVFCCUGD4;     /**< VFCCU Global DID register 4, offset: 0x0 */
    __IO uint32_t LVFCCULD12;    /**< VFCCU Local DID register 12, offset: 0x4 */
    __IO uint32_t LVFCCULD13;    /**< VFCCU Local DID register 13, offset: 0x8 */
    __IO uint32_t LVFCCULD14;    /**< VFCCU Local DID register 14, offset: 0xC */
    uint8_t RESERVED_0[52];
    __I uint32_t INITM4;         /**< NoC Initiator NIU Timeout Status, offset: 0x44 */
    __I uint32_t TARGTMS4;       /**< NoC Target NIU Timeout Status, offset: 0x48 */
    __IO uint32_t TARGTMC4;      /**< NoC Target NIU Timeout Control, offset: 0x4C */
    uint8_t RESERVED_1[4];
    __IO uint32_t CLKOUT2SEL;    /**< CLKOUT_2 MUX select, offset: 0x54 */
    uint8_t RESERVED_2[56];
    __IO uint32_t MEW0MSTDIS;    /**< MEW_0 Master ID Disable, offset: 0x90 */
    __IO uint32_t MEW1MSTDIS;    /**< MEW_1 Master ID Disable, offset: 0x94 */
    uint8_t RESERVED_3[8];
    __IO uint32_t HSE_SYS_FUSEC; /**< System Fuse Update Disable, offset: 0xA0 */
} GPR4_Type, *GPR4_MemMapPtr;

/** Number of instances of the GPR4 module. */
#define GPR4_INSTANCE_COUNT       (1u)

/* GPR4 - Peripheral instance base addresses */
/** Peripheral GPR4 base address */
#define IP_GPR4_BASE              (0x42060000u)
/** Peripheral GPR4 base pointer */
#define IP_GPR4                   ((GPR4_Type*)IP_GPR4_BASE)
/** Array initializer of GPR4 peripheral base addresses */
#define IP_GPR4_BASE_ADDRS        { IP_GPR4_BASE }
/** Array initializer of GPR4 peripheral base pointers */
#define IP_GPR4_BASE_PTRS         { IP_GPR4 }

/* ----------------------------------------------------------------------------
   -- GPR4 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR4_Register_Masks GPR4 Register Masks
 * @{
 */

/*! @name LVFCCUGD4 - VFCCU Global DID register 4 */
/*! @{ */

#define GPR4_LVFCCUGD4_FHID_MASK  (0xFU)
#define GPR4_LVFCCUGD4_FHID_SHIFT (0U)
#define GPR4_LVFCCUGD4_FHID_WIDTH (4U)
#define GPR4_LVFCCUGD4_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_LVFCCUGD4_FHID_SHIFT)) & GPR4_LVFCCUGD4_FHID_MASK)
/*! @} */

/*! @name LVFCCULD12 - VFCCU Local DID register 12 */
/*! @{ */

#define GPR4_LVFCCULD12_FHID_MASK  (0xFFFFFFFFU)
#define GPR4_LVFCCULD12_FHID_SHIFT (0U)
#define GPR4_LVFCCULD12_FHID_WIDTH (32U)
#define GPR4_LVFCCULD12_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_LVFCCULD12_FHID_SHIFT)) & GPR4_LVFCCULD12_FHID_MASK)
/*! @} */

/*! @name LVFCCULD13 - VFCCU Local DID register 13 */
/*! @{ */

#define GPR4_LVFCCULD13_FHID_MASK  (0xFFFFFFFFU)
#define GPR4_LVFCCULD13_FHID_SHIFT (0U)
#define GPR4_LVFCCULD13_FHID_WIDTH (32U)
#define GPR4_LVFCCULD13_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_LVFCCULD13_FHID_SHIFT)) & GPR4_LVFCCULD13_FHID_MASK)
/*! @} */

/*! @name LVFCCULD14 - VFCCU Local DID register 14 */
/*! @{ */

#define GPR4_LVFCCULD14_FHID_MASK  (0xFFFFFFFFU)
#define GPR4_LVFCCULD14_FHID_SHIFT (0U)
#define GPR4_LVFCCULD14_FHID_WIDTH (32U)
#define GPR4_LVFCCULD14_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_LVFCCULD14_FHID_SHIFT)) & GPR4_LVFCCULD14_FHID_MASK)
/*! @} */

/*! @name INITM4 - NoC Initiator NIU Timeout Status */
/*! @{ */

#define GPR4_INITM4_STAT_MASK  (0xFFFFFFFFU)
#define GPR4_INITM4_STAT_SHIFT (0U)
#define GPR4_INITM4_STAT_WIDTH (32U)
#define GPR4_INITM4_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_INITM4_STAT_SHIFT)) & GPR4_INITM4_STAT_MASK)
/*! @} */

/*! @name TARGTMS4 - NoC Target NIU Timeout Status */
/*! @{ */

#define GPR4_TARGTMS4_STAT_MASK  (0xFFFFFFFFU)
#define GPR4_TARGTMS4_STAT_SHIFT (0U)
#define GPR4_TARGTMS4_STAT_WIDTH (32U)
#define GPR4_TARGTMS4_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_TARGTMS4_STAT_SHIFT)) & GPR4_TARGTMS4_STAT_MASK)
/*! @} */

/*! @name TARGTMC4 - NoC Target NIU Timeout Control */
/*! @{ */

#define GPR4_TARGTMC4_EN_MASK  (0xFFFFFFFFU)
#define GPR4_TARGTMC4_EN_SHIFT (0U)
#define GPR4_TARGTMC4_EN_WIDTH (32U)
#define GPR4_TARGTMC4_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_TARGTMC4_EN_SHIFT)) & GPR4_TARGTMC4_EN_MASK)
/*! @} */

/*! @name CLKOUT2SEL - CLKOUT_2 MUX select */
/*! @{ */

#define GPR4_CLKOUT2SEL_MUXSEL_MASK  (0x1FU)
#define GPR4_CLKOUT2SEL_MUXSEL_SHIFT (0U)
#define GPR4_CLKOUT2SEL_MUXSEL_WIDTH (5U)
#define GPR4_CLKOUT2SEL_MUXSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_CLKOUT2SEL_MUXSEL_SHIFT)) & GPR4_CLKOUT2SEL_MUXSEL_MASK)
/*! @} */

/*! @name MEW0MSTDIS - MEW_0 Master ID Disable */
/*! @{ */

#define GPR4_MEW0MSTDIS_MSTRDIS_MASK  (0x1U)
#define GPR4_MEW0MSTDIS_MSTRDIS_SHIFT (0U)
#define GPR4_MEW0MSTDIS_MSTRDIS_WIDTH (1U)
#define GPR4_MEW0MSTDIS_MSTRDIS(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_MEW0MSTDIS_MSTRDIS_SHIFT)) & GPR4_MEW0MSTDIS_MSTRDIS_MASK)

#define GPR4_MEW0MSTDIS_MID_MASK  (0x7EU)
#define GPR4_MEW0MSTDIS_MID_SHIFT (1U)
#define GPR4_MEW0MSTDIS_MID_WIDTH (6U)
#define GPR4_MEW0MSTDIS_MID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_MEW0MSTDIS_MID_SHIFT)) & GPR4_MEW0MSTDIS_MID_MASK)
/*! @} */

/*! @name MEW1MSTDIS - MEW_1 Master ID Disable */
/*! @{ */

#define GPR4_MEW1MSTDIS_MSTRDIS_MASK  (0x1U)
#define GPR4_MEW1MSTDIS_MSTRDIS_SHIFT (0U)
#define GPR4_MEW1MSTDIS_MSTRDIS_WIDTH (1U)
#define GPR4_MEW1MSTDIS_MSTRDIS(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_MEW1MSTDIS_MSTRDIS_SHIFT)) & GPR4_MEW1MSTDIS_MSTRDIS_MASK)

#define GPR4_MEW1MSTDIS_MID_MASK  (0x7EU)
#define GPR4_MEW1MSTDIS_MID_SHIFT (1U)
#define GPR4_MEW1MSTDIS_MID_WIDTH (6U)
#define GPR4_MEW1MSTDIS_MID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_MEW1MSTDIS_MID_SHIFT)) & GPR4_MEW1MSTDIS_MID_MASK)
/*! @} */

/*! @name HSE_SYS_FUSEC - System Fuse Update Disable */
/*! @{ */

#define GPR4_HSE_SYS_FUSEC_CTRL_MASK  (0x1U)
#define GPR4_HSE_SYS_FUSEC_CTRL_SHIFT (0U)
#define GPR4_HSE_SYS_FUSEC_CTRL_WIDTH (1U)
#define GPR4_HSE_SYS_FUSEC_CTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR4_HSE_SYS_FUSEC_CTRL_SHIFT)) & GPR4_HSE_SYS_FUSEC_CTRL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR4_Register_Masks */

/*!
 * @}
 */ /* end of group GPR4_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR4_H_) */
