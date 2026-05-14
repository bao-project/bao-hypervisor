/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR1.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR1
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
#if !defined(S32Z2_GPR1_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR1_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR1 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR1_Peripheral_Access_Layer GPR1 Peripheral Access Layer
 * @{
 */

/** GPR1 - Register Layout Typedef */
typedef struct {
    __IO uint32_t LVFCCUGD1;  /**< VFCCU Global DID register 1, offset: 0x0 */
    __IO uint32_t LVFCCULD3;  /**< VFCCU Local DID register 3, offset: 0x4 */
    __IO uint32_t LVFCCULD4;  /**< VFCCU Local DID register 4, offset: 0x8 */
    __IO uint32_t LVFCCULD5;  /**< VFCCU Local DID register 5, offset: 0xC */
    uint8_t RESERVED_0[20];
    __IO uint32_t DESTC2;     /**< Source Control for RGMII TX CLK, offset: 0x24 */
    uint8_t RESERVED_1[12];
    __IO uint32_t FUNCC2;     /**< Zipwire Configuration, offset: 0x34 */
    uint8_t RESERVED_2[12];
    __I uint32_t INITM1;      /**< NoC Initiator NIU Timeout Status, offset: 0x44 */
    __I uint32_t TARGTMS1;    /**< NoC Target NIU Timeout Status, offset: 0x48 */
    __IO uint32_t TARGTMC1;   /**< NoC Target NIU Timeout Control, offset: 0x4C */
    uint8_t RESERVED_3[4];
    __IO uint32_t NETCC0;     /**< NETC Control register 0, offset: 0x54 */
    __IO uint32_t NETCC1;     /**< NETC Control register 1, offset: 0x58 */
    __IO uint32_t CLKOUT1SEL; /**< CLKOUT_1 MUX select, offset: 0x5C */
    uint8_t RESERVED_4[20];
    __IO uint32_t XPAR1;      /**< Interface parity control and status register, offset: 0x74 */
} GPR1_Type, *GPR1_MemMapPtr;

/** Number of instances of the GPR1 module. */
#define GPR1_INSTANCE_COUNT       (1u)

/* GPR1 - Peripheral instance base addresses */
/** Peripheral GPR1 base address */
#define IP_GPR1_BASE              (0x40860000u)
/** Peripheral GPR1 base pointer */
#define IP_GPR1                   ((GPR1_Type*)IP_GPR1_BASE)
/** Array initializer of GPR1 peripheral base addresses */
#define IP_GPR1_BASE_ADDRS        { IP_GPR1_BASE }
/** Array initializer of GPR1 peripheral base pointers */
#define IP_GPR1_BASE_PTRS         { IP_GPR1 }

/* ----------------------------------------------------------------------------
   -- GPR1 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR1_Register_Masks GPR1 Register Masks
 * @{
 */

/*! @name LVFCCUGD1 - VFCCU Global DID register 1 */
/*! @{ */

#define GPR1_LVFCCUGD1_FHID_MASK  (0xFU)
#define GPR1_LVFCCUGD1_FHID_SHIFT (0U)
#define GPR1_LVFCCUGD1_FHID_WIDTH (4U)
#define GPR1_LVFCCUGD1_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_LVFCCUGD1_FHID_SHIFT)) & GPR1_LVFCCUGD1_FHID_MASK)
/*! @} */

/*! @name LVFCCULD3 - VFCCU Local DID register 3 */
/*! @{ */

#define GPR1_LVFCCULD3_FHID_MASK  (0xFFFFFFFFU)
#define GPR1_LVFCCULD3_FHID_SHIFT (0U)
#define GPR1_LVFCCULD3_FHID_WIDTH (32U)
#define GPR1_LVFCCULD3_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_LVFCCULD3_FHID_SHIFT)) & GPR1_LVFCCULD3_FHID_MASK)
/*! @} */

/*! @name LVFCCULD4 - VFCCU Local DID register 4 */
/*! @{ */

#define GPR1_LVFCCULD4_FHID_MASK  (0xFFFFFFFFU)
#define GPR1_LVFCCULD4_FHID_SHIFT (0U)
#define GPR1_LVFCCULD4_FHID_WIDTH (32U)
#define GPR1_LVFCCULD4_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_LVFCCULD4_FHID_SHIFT)) & GPR1_LVFCCULD4_FHID_MASK)
/*! @} */

/*! @name LVFCCULD5 - VFCCU Local DID register 5 */
/*! @{ */

#define GPR1_LVFCCULD5_FHID_MASK  (0xFFFFFFFFU)
#define GPR1_LVFCCULD5_FHID_SHIFT (0U)
#define GPR1_LVFCCULD5_FHID_WIDTH (32U)
#define GPR1_LVFCCULD5_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_LVFCCULD5_FHID_SHIFT)) & GPR1_LVFCCULD5_FHID_MASK)
/*! @} */

/*! @name DESTC2 - Source Control for RGMII TX CLK */
/*! @{ */

#define GPR1_DESTC2_CTRL_MASK  (0xFFFFFFFFU)
#define GPR1_DESTC2_CTRL_SHIFT (0U)
#define GPR1_DESTC2_CTRL_WIDTH (32U)
#define GPR1_DESTC2_CTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_DESTC2_CTRL_SHIFT)) & GPR1_DESTC2_CTRL_MASK)
/*! @} */

/*! @name FUNCC2 - Zipwire Configuration */
/*! @{ */

#define GPR1_FUNCC2_CTRL_MASK  (0xFFFFFFFFU)
#define GPR1_FUNCC2_CTRL_SHIFT (0U)
#define GPR1_FUNCC2_CTRL_WIDTH (32U)
#define GPR1_FUNCC2_CTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_FUNCC2_CTRL_SHIFT)) & GPR1_FUNCC2_CTRL_MASK)
/*! @} */

/*! @name INITM1 - NoC Initiator NIU Timeout Status */
/*! @{ */

#define GPR1_INITM1_STAT_MASK  (0xFFFFFFFFU)
#define GPR1_INITM1_STAT_SHIFT (0U)
#define GPR1_INITM1_STAT_WIDTH (32U)
#define GPR1_INITM1_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_INITM1_STAT_SHIFT)) & GPR1_INITM1_STAT_MASK)
/*! @} */

/*! @name TARGTMS1 - NoC Target NIU Timeout Status */
/*! @{ */

#define GPR1_TARGTMS1_STAT_MASK  (0xFFFFFFFFU)
#define GPR1_TARGTMS1_STAT_SHIFT (0U)
#define GPR1_TARGTMS1_STAT_WIDTH (32U)
#define GPR1_TARGTMS1_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_TARGTMS1_STAT_SHIFT)) & GPR1_TARGTMS1_STAT_MASK)
/*! @} */

/*! @name TARGTMC1 - NoC Target NIU Timeout Control */
/*! @{ */

#define GPR1_TARGTMC1_EN_MASK  (0xFFFFFFFFU)
#define GPR1_TARGTMC1_EN_SHIFT (0U)
#define GPR1_TARGTMC1_EN_WIDTH (32U)
#define GPR1_TARGTMC1_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_TARGTMC1_EN_SHIFT)) & GPR1_TARGTMC1_EN_MASK)
/*! @} */

/*! @name NETCC0 - NETC Control register 0 */
/*! @{ */

#define GPR1_NETCC0_IERBLOCK_MASK  (0x1U)
#define GPR1_NETCC0_IERBLOCK_SHIFT (0U)
#define GPR1_NETCC0_IERBLOCK_WIDTH (1U)
#define GPR1_NETCC0_IERBLOCK(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_NETCC0_IERBLOCK_SHIFT)) & GPR1_NETCC0_IERBLOCK_MASK)
/*! @} */

/*! @name NETCC1 - NETC Control register 1 */
/*! @{ */

#define GPR1_NETCC1_LINK0MIIP_MASK  (0xFU)
#define GPR1_NETCC1_LINK0MIIP_SHIFT (0U)
#define GPR1_NETCC1_LINK0MIIP_WIDTH (4U)
#define GPR1_NETCC1_LINK0MIIP(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_NETCC1_LINK0MIIP_SHIFT)) & GPR1_NETCC1_LINK0MIIP_MASK)

#define GPR1_NETCC1_LINK1MIIP_MASK  (0xF0U)
#define GPR1_NETCC1_LINK1MIIP_SHIFT (4U)
#define GPR1_NETCC1_LINK1MIIP_WIDTH (4U)
#define GPR1_NETCC1_LINK1MIIP(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_NETCC1_LINK1MIIP_SHIFT)) & GPR1_NETCC1_LINK1MIIP_MASK)
/*! @} */

/*! @name CLKOUT1SEL - CLKOUT_1 MUX select */
/*! @{ */

#define GPR1_CLKOUT1SEL_MUXSEL_MASK  (0x3FU)
#define GPR1_CLKOUT1SEL_MUXSEL_SHIFT (0U)
#define GPR1_CLKOUT1SEL_MUXSEL_WIDTH (6U)
#define GPR1_CLKOUT1SEL_MUXSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_CLKOUT1SEL_MUXSEL_SHIFT)) & GPR1_CLKOUT1SEL_MUXSEL_MASK)
/*! @} */

/*! @name XPAR1 - Interface parity control and status register */
/*! @{ */

#define GPR1_XPAR1_DIS_MASK  (0x1U)
#define GPR1_XPAR1_DIS_SHIFT (0U)
#define GPR1_XPAR1_DIS_WIDTH (1U)
#define GPR1_XPAR1_DIS(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_XPAR1_DIS_SHIFT)) & GPR1_XPAR1_DIS_MASK)

#define GPR1_XPAR1_STAT_MASK  (0x100U)
#define GPR1_XPAR1_STAT_SHIFT (8U)
#define GPR1_XPAR1_STAT_WIDTH (1U)
#define GPR1_XPAR1_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR1_XPAR1_STAT_SHIFT)) & GPR1_XPAR1_STAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR1_Register_Masks */

/*!
 * @}
 */ /* end of group GPR1_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR1_H_) */
