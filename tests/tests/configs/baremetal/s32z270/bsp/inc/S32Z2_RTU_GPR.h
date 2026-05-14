/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_RTU_GPR.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_RTU_GPR
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
#if !defined(S32Z2_RTU_GPR_H_) /* Check if memory map has not been already included */
#define S32Z2_RTU_GPR_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- RTU_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTU_GPR_Peripheral_Access_Layer RTU_GPR Peripheral Access Layer
 * @{
 */

/** RTU_GPR - Register Layout Typedef */
typedef struct {
    __IO uint32_t CFG_CORE;        /**< Core Configuration, offset: 0x0 */
    __IO uint32_t CFG_BUPERR_DIS0; /**< Bus Parity Error Disable Group0, offset: 0x4 */
    __IO uint32_t CFG_BUPERR_DIS1; /**< Bus Parity Error Disable Group0, offset: 0x8 */
    __IO uint32_t CFG_FD;          /**< Core Fence and Drain Configuration, offset: 0xC */
    __IO uint32_t CFG_CNTDV;       /**< Generic Timer Count Divider Control, offset: 0x10 */
    __IO uint32_t CFG_HALT;        /**< Core Halt Control, offset: 0x14 */
    uint8_t RESERVED_0[4];
    __I uint32_t STAT_FD;          /**< Core Fence and Drain Status, offset: 0x1C */
    uint8_t RESERVED_1[16];
    __I uint32_t STAT_WFI;         /**< Core STANDBYWFI Status, offset: 0x30 */
    __I uint32_t STAT_WFE;         /**< Core STANDBYWFE Status, offset: 0x34 */
    __I uint32_t STAT_WRSTREQ;     /**< Core WARMRSTREQ Status, offset: 0x38 */
    uint8_t RESERVED_2[4];
    __I uint32_t STAT_EVC0;        /**< Core0 External Event Status, offset: 0x40 */
    __I uint32_t STAT_EVC1;        /**< Core1 External Event Status, offset: 0x44 */
    __I uint32_t STAT_EVC2;        /**< Core2 External Event Status, offset: 0x48 */
    __I uint32_t STAT_EVC3;        /**< Core3 External Event Status, offset: 0x4C */
    __I uint32_t STAT_MERRPM0; /**< Primary Error Interface Memory Identifier Core0, offset: 0x50 */
    __I uint32_t STAT_MERRPX0; /**< Primary Error Interface Index Core0, offset: 0x54 */
    __I uint32_t STAT_MERRSM0; /**< Secondary Error Interface Memory Identifier Core0, offset: 0x58
                                */
    __I uint32_t STAT_MERRSX0; /**< Secondary Error Interface Index Core0, offset: 0x5C */
    __I uint32_t STAT_MERRPM1; /**< Primary Error Interface Memory Identifier Core1, offset: 0x60 */
    __I uint32_t STAT_MERRPX1; /**< Primary Error Interface Index Core1, offset: 0x64 */
    __I uint32_t STAT_MERRSM1; /**< Secondary Error Interface Memory Identifier Core1, offset: 0x68
                                */
    __I uint32_t STAT_MERRSX1; /**< Secondary Error Interface Index Core1, offset: 0x6C */
    __I uint32_t STAT_MERRPM2; /**< Primary Error Interface Memory Identifier Core2, offset: 0x70 */
    __I uint32_t STAT_MERRPX2; /**< Primary Error Interface Index Core2, offset: 0x74 */
    __I uint32_t STAT_MERRSM2; /**< Secondary Error Interface Memory Identifier Core2, offset: 0x78
                                */
    __I uint32_t STAT_MERRSX2; /**< Secondary Error Interface Index Core2, offset: 0x7C */
    __I uint32_t STAT_MERRPM3; /**< Primary Error Interface Memory Identifier Core3, offset: 0x80 */
    __I uint32_t STAT_MERRPX3; /**< Primary Error Interface Index Core3, offset: 0x84 */
    __I uint32_t STAT_MERRSM3; /**< Secondary Error Interface Memory Identifier Core3, offset: 0x88
                                */
    __I uint32_t STAT_MERRSX3; /**< Secondary Error Interface Index Core3, offset: 0x8C */
    __I uint32_t STAT_PMU0EV0; /**< PMU Event Core0 Group0, offset: 0x90 */
    __I uint32_t STAT_PMU1EV0; /**< PMU Event Core0 Group1, offset: 0x94 */
    __I uint32_t STAT_PMU0EV1; /**< PMU Event Core1 Group0, offset: 0x98 */
    __I uint32_t STAT_PMU1EV1; /**< PMU Event Core1 Group1, offset: 0x9C */
    __I uint32_t STAT_PMU0EV2; /**< PMU Event Core2 Group0, offset: 0xA0 */
    __I uint32_t STAT_PMU1EV2; /**< PMU Event Core2 Group1, offset: 0xA4 */
    __I uint32_t STAT_PMU0EV3; /**< PMU Event Core3 Group0, offset: 0xA8 */
    __I uint32_t STAT_PMU1EV3; /**< PMU Event Core3 Group1, offset: 0xAC */
} RTU_GPR_Type, *RTU_GPR_MemMapPtr;

/** Number of instances of the RTU_GPR module. */
#define RTU_GPR_INSTANCE_COUNT          (2u)

/* RTU_GPR - Peripheral instance base addresses */
/** Peripheral RTU0__GPR base address */
#define IP_RTU0__GPR_BASE               (0x76120000u)
/** Peripheral RTU0__GPR base pointer */
#define IP_RTU0__GPR                    ((RTU_GPR_Type*)IP_RTU0__GPR_BASE)
/** Peripheral RTU1__GPR base address */
#define IP_RTU1__GPR_BASE               (0x76920000u)
/** Peripheral RTU1__GPR base pointer */
#define IP_RTU1__GPR                    ((RTU_GPR_Type*)IP_RTU1__GPR_BASE)
/** Array initializer of RTU_GPR peripheral base addresses */
#define IP_RTU_GPR_BASE_ADDRS           { IP_RTU0__GPR_BASE, IP_RTU1__GPR_BASE }
/** Array initializer of RTU_GPR peripheral base pointers */
#define IP_RTU_GPR_BASE_PTRS            { IP_RTU0__GPR, IP_RTU1__GPR }

/* ----------------------------------------------------------------------------
   -- RTU_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTU_GPR_Register_Masks RTU_GPR Register Masks
 * @{
 */

/*! @name CFG_CORE - Core Configuration */
/*! @{ */

#define RTU_GPR_CFG_CORE_SPLT_LCK_MASK  (0x1U)
#define RTU_GPR_CFG_CORE_SPLT_LCK_SHIFT (0U)
#define RTU_GPR_CFG_CORE_SPLT_LCK_WIDTH (1U)
#define RTU_GPR_CFG_CORE_SPLT_LCK(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_CORE_SPLT_LCK_SHIFT)) & \
        RTU_GPR_CFG_CORE_SPLT_LCK_MASK)

#define RTU_GPR_CFG_CORE_TCM_BT_MASK  (0x2U)
#define RTU_GPR_CFG_CORE_TCM_BT_SHIFT (1U)
#define RTU_GPR_CFG_CORE_TCM_BT_WIDTH (1U)
#define RTU_GPR_CFG_CORE_TCM_BT(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_CORE_TCM_BT_SHIFT)) & RTU_GPR_CFG_CORE_TCM_BT_MASK)

#define RTU_GPR_CFG_CORE_THUMB_MASK  (0x4U)
#define RTU_GPR_CFG_CORE_THUMB_SHIFT (2U)
#define RTU_GPR_CFG_CORE_THUMB_WIDTH (1U)
#define RTU_GPR_CFG_CORE_THUMB(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_CORE_THUMB_SHIFT)) & RTU_GPR_CFG_CORE_THUMB_MASK)

#define RTU_GPR_CFG_CORE_CAINV_MASK  (0x8U)
#define RTU_GPR_CFG_CORE_CAINV_SHIFT (3U)
#define RTU_GPR_CFG_CORE_CAINV_WIDTH (1U)
#define RTU_GPR_CFG_CORE_CAINV(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_CORE_CAINV_SHIFT)) & RTU_GPR_CFG_CORE_CAINV_MASK)

#define RTU_GPR_CFG_CORE_INITREG_MASK  (0x10U)
#define RTU_GPR_CFG_CORE_INITREG_SHIFT (4U)
#define RTU_GPR_CFG_CORE_INITREG_WIDTH (1U)
#define RTU_GPR_CFG_CORE_INITREG(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_CORE_INITREG_SHIFT)) & \
        RTU_GPR_CFG_CORE_INITREG_MASK)

#define RTU_GPR_CFG_CORE_PMC_DIS_MASK  (0x100U)
#define RTU_GPR_CFG_CORE_PMC_DIS_SHIFT (8U)
#define RTU_GPR_CFG_CORE_PMC_DIS_WIDTH (1U)
#define RTU_GPR_CFG_CORE_PMC_DIS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_CORE_PMC_DIS_SHIFT)) & \
        RTU_GPR_CFG_CORE_PMC_DIS_MASK)
/*! @} */

/*! @name CFG_BUPERR_DIS0 - Bus Parity Error Disable Group0 */
/*! @{ */

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR0_MASK  (0x1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR0_SHIFT (0U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR0_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR0_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR0_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR1_MASK  (0x2U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR1_SHIFT (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR1_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR1_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR1_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR2_MASK  (0x4U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR2_SHIFT (2U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR2_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR2_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR2_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR3_MASK  (0x8U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR3_SHIFT (3U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR3_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR3_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR3_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR4_MASK  (0x10U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR4_SHIFT (4U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR4_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR4(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR4_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR4_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR5_MASK  (0x20U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR5_SHIFT (5U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR5_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR5(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR5_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR5_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR6_MASK  (0x40U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR6_SHIFT (6U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR6_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR6(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR6_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR6_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR7_MASK  (0x80U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR7_SHIFT (7U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR7_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR7(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR7_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR7_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR8_MASK  (0x100U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR8_SHIFT (8U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR8_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR8(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR8_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR8_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR9_MASK  (0x200U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR9_SHIFT (9U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR9_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR9(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR9_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR9_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR10_MASK  (0x400U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR10_SHIFT (10U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR10_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR10(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR10_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR10_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR11_MASK  (0x800U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR11_SHIFT (11U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR11_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR11(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR11_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR11_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR12_MASK  (0x1000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR12_SHIFT (12U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR12_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR12(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR12_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR12_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR13_MASK  (0x2000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR13_SHIFT (13U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR13_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR13(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR13_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR13_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR14_MASK  (0x4000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR14_SHIFT (14U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR14_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR14(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR14_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR14_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR15_MASK  (0x8000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR15_SHIFT (15U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR15_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR15(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR15_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR15_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR16_MASK  (0x10000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR16_SHIFT (16U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR16_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR16(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR16_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR16_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR17_MASK  (0x20000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR17_SHIFT (17U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR17_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR17(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR17_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR17_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR18_MASK  (0x40000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR18_SHIFT (18U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR18_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR18(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR18_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR18_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR19_MASK  (0x80000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR19_SHIFT (19U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR19_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR19(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR19_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR19_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR20_MASK  (0x100000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR20_SHIFT (20U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR20_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR20(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR20_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR20_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR21_MASK  (0x200000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR21_SHIFT (21U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR21_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR21(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR21_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR21_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR22_MASK  (0x400000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR22_SHIFT (22U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR22_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR22(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR22_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR22_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR23_MASK  (0x800000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR23_SHIFT (23U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR23_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR23(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR23_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR23_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR24_MASK  (0x1000000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR24_SHIFT (24U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR24_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR24(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR24_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR24_MASK)

#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR25_MASK  (0x2000000U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR25_SHIFT (25U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR25_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS0_BUPERR25(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS0_BUPERR25_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS0_BUPERR25_MASK)
/*! @} */

/*! @name CFG_BUPERR_DIS1 - Bus Parity Error Disable Group0 */
/*! @{ */

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR0_MASK  (0x1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR0_SHIFT (0U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR0_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR0_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR0_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR1_MASK  (0x2U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR1_SHIFT (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR1_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR1_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR1_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR2_MASK  (0x4U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR2_SHIFT (2U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR2_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR2_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR2_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR3_MASK  (0x8U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR3_SHIFT (3U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR3_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR3_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR3_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR4_MASK  (0x10U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR4_SHIFT (4U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR4_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR4(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR4_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR4_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR5_MASK  (0x20U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR5_SHIFT (5U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR5_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR5(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR5_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR5_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR6_MASK  (0x40U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR6_SHIFT (6U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR6_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR6(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR6_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR6_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR7_MASK  (0x80U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR7_SHIFT (7U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR7_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR7(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR7_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR7_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR8_MASK  (0x100U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR8_SHIFT (8U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR8_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR8(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR8_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR8_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR9_MASK  (0x200U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR9_SHIFT (9U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR9_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR9(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR9_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR9_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR10_MASK  (0x400U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR10_SHIFT (10U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR10_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR10(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR10_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR10_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR11_MASK  (0x800U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR11_SHIFT (11U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR11_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR11(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR11_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR11_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR12_MASK  (0x1000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR12_SHIFT (12U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR12_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR12(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR12_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR12_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR13_MASK  (0x2000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR13_SHIFT (13U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR13_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR13(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR13_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR13_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR14_MASK  (0x4000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR14_SHIFT (14U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR14_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR14(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR14_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR14_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR15_MASK  (0x8000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR15_SHIFT (15U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR15_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR15(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR15_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR15_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR16_MASK  (0x10000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR16_SHIFT (16U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR16_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR16(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR16_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR16_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR17_MASK  (0x20000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR17_SHIFT (17U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR17_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR17(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR17_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR17_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR18_MASK  (0x40000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR18_SHIFT (18U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR18_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR18(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR18_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR18_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR19_MASK  (0x80000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR19_SHIFT (19U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR19_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR19(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR19_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR19_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR20_MASK  (0x100000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR20_SHIFT (20U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR20_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR20(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR20_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR20_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR21_MASK  (0x200000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR21_SHIFT (21U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR21_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR21(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR21_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR21_MASK)

#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR22_MASK  (0x400000U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR22_SHIFT (22U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR22_WIDTH (1U)
#define RTU_GPR_CFG_BUPERR_DIS1_BUPERR22(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_BUPERR_DIS1_BUPERR22_SHIFT)) & \
        RTU_GPR_CFG_BUPERR_DIS1_BUPERR22_MASK)
/*! @} */

/*! @name CFG_FD - Core Fence and Drain Configuration */
/*! @{ */

#define RTU_GPR_CFG_FD_MFDEN0_MASK  (0x1U)
#define RTU_GPR_CFG_FD_MFDEN0_SHIFT (0U)
#define RTU_GPR_CFG_FD_MFDEN0_WIDTH (1U)
#define RTU_GPR_CFG_FD_MFDEN0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_MFDEN0_SHIFT)) & RTU_GPR_CFG_FD_MFDEN0_MASK)

#define RTU_GPR_CFG_FD_MFDEN1_MASK  (0x2U)
#define RTU_GPR_CFG_FD_MFDEN1_SHIFT (1U)
#define RTU_GPR_CFG_FD_MFDEN1_WIDTH (1U)
#define RTU_GPR_CFG_FD_MFDEN1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_MFDEN1_SHIFT)) & RTU_GPR_CFG_FD_MFDEN1_MASK)

#define RTU_GPR_CFG_FD_MFDEN2_MASK  (0x4U)
#define RTU_GPR_CFG_FD_MFDEN2_SHIFT (2U)
#define RTU_GPR_CFG_FD_MFDEN2_WIDTH (1U)
#define RTU_GPR_CFG_FD_MFDEN2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_MFDEN2_SHIFT)) & RTU_GPR_CFG_FD_MFDEN2_MASK)

#define RTU_GPR_CFG_FD_MFDEN3_MASK  (0x8U)
#define RTU_GPR_CFG_FD_MFDEN3_SHIFT (3U)
#define RTU_GPR_CFG_FD_MFDEN3_WIDTH (1U)
#define RTU_GPR_CFG_FD_MFDEN3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_MFDEN3_SHIFT)) & RTU_GPR_CFG_FD_MFDEN3_MASK)

#define RTU_GPR_CFG_FD_FFDEN0_MASK  (0x10U)
#define RTU_GPR_CFG_FD_FFDEN0_SHIFT (4U)
#define RTU_GPR_CFG_FD_FFDEN0_WIDTH (1U)
#define RTU_GPR_CFG_FD_FFDEN0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_FFDEN0_SHIFT)) & RTU_GPR_CFG_FD_FFDEN0_MASK)

#define RTU_GPR_CFG_FD_FFDEN1_MASK  (0x20U)
#define RTU_GPR_CFG_FD_FFDEN1_SHIFT (5U)
#define RTU_GPR_CFG_FD_FFDEN1_WIDTH (1U)
#define RTU_GPR_CFG_FD_FFDEN1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_FFDEN1_SHIFT)) & RTU_GPR_CFG_FD_FFDEN1_MASK)

#define RTU_GPR_CFG_FD_FFDEN2_MASK  (0x40U)
#define RTU_GPR_CFG_FD_FFDEN2_SHIFT (6U)
#define RTU_GPR_CFG_FD_FFDEN2_WIDTH (1U)
#define RTU_GPR_CFG_FD_FFDEN2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_FFDEN2_SHIFT)) & RTU_GPR_CFG_FD_FFDEN2_MASK)

#define RTU_GPR_CFG_FD_FFDEN3_MASK  (0x80U)
#define RTU_GPR_CFG_FD_FFDEN3_SHIFT (7U)
#define RTU_GPR_CFG_FD_FFDEN3_WIDTH (1U)
#define RTU_GPR_CFG_FD_FFDEN3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_FFDEN3_SHIFT)) & RTU_GPR_CFG_FD_FFDEN3_MASK)

#define RTU_GPR_CFG_FD_LFDEN0_MASK  (0x100U)
#define RTU_GPR_CFG_FD_LFDEN0_SHIFT (8U)
#define RTU_GPR_CFG_FD_LFDEN0_WIDTH (1U)
#define RTU_GPR_CFG_FD_LFDEN0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_LFDEN0_SHIFT)) & RTU_GPR_CFG_FD_LFDEN0_MASK)

#define RTU_GPR_CFG_FD_LFDEN1_MASK  (0x200U)
#define RTU_GPR_CFG_FD_LFDEN1_SHIFT (9U)
#define RTU_GPR_CFG_FD_LFDEN1_WIDTH (1U)
#define RTU_GPR_CFG_FD_LFDEN1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_LFDEN1_SHIFT)) & RTU_GPR_CFG_FD_LFDEN1_MASK)

#define RTU_GPR_CFG_FD_LFDEN2_MASK  (0x400U)
#define RTU_GPR_CFG_FD_LFDEN2_SHIFT (10U)
#define RTU_GPR_CFG_FD_LFDEN2_WIDTH (1U)
#define RTU_GPR_CFG_FD_LFDEN2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_LFDEN2_SHIFT)) & RTU_GPR_CFG_FD_LFDEN2_MASK)

#define RTU_GPR_CFG_FD_LFDEN3_MASK  (0x800U)
#define RTU_GPR_CFG_FD_LFDEN3_SHIFT (11U)
#define RTU_GPR_CFG_FD_LFDEN3_WIDTH (1U)
#define RTU_GPR_CFG_FD_LFDEN3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_LFDEN3_SHIFT)) & RTU_GPR_CFG_FD_LFDEN3_MASK)

#define RTU_GPR_CFG_FD_SFDEN_MASK  (0x10000U)
#define RTU_GPR_CFG_FD_SFDEN_SHIFT (16U)
#define RTU_GPR_CFG_FD_SFDEN_WIDTH (1U)
#define RTU_GPR_CFG_FD_SFDEN(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_SFDEN_SHIFT)) & RTU_GPR_CFG_FD_SFDEN_MASK)

#define RTU_GPR_CFG_FD_ISOLEN0_MASK  (0x10000000U)
#define RTU_GPR_CFG_FD_ISOLEN0_SHIFT (28U)
#define RTU_GPR_CFG_FD_ISOLEN0_WIDTH (1U)
#define RTU_GPR_CFG_FD_ISOLEN0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_ISOLEN0_SHIFT)) & RTU_GPR_CFG_FD_ISOLEN0_MASK)

#define RTU_GPR_CFG_FD_ISOLEN1_MASK  (0x20000000U)
#define RTU_GPR_CFG_FD_ISOLEN1_SHIFT (29U)
#define RTU_GPR_CFG_FD_ISOLEN1_WIDTH (1U)
#define RTU_GPR_CFG_FD_ISOLEN1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_ISOLEN1_SHIFT)) & RTU_GPR_CFG_FD_ISOLEN1_MASK)

#define RTU_GPR_CFG_FD_ISOLEN2_MASK  (0x40000000U)
#define RTU_GPR_CFG_FD_ISOLEN2_SHIFT (30U)
#define RTU_GPR_CFG_FD_ISOLEN2_WIDTH (1U)
#define RTU_GPR_CFG_FD_ISOLEN2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_ISOLEN2_SHIFT)) & RTU_GPR_CFG_FD_ISOLEN2_MASK)

#define RTU_GPR_CFG_FD_ISOLEN3_MASK  (0x80000000U)
#define RTU_GPR_CFG_FD_ISOLEN3_SHIFT (31U)
#define RTU_GPR_CFG_FD_ISOLEN3_WIDTH (1U)
#define RTU_GPR_CFG_FD_ISOLEN3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_FD_ISOLEN3_SHIFT)) & RTU_GPR_CFG_FD_ISOLEN3_MASK)
/*! @} */

/*! @name CFG_CNTDV - Generic Timer Count Divider Control */
/*! @{ */

#define RTU_GPR_CFG_CNTDV_CNTDV_MASK  (0x7U)
#define RTU_GPR_CFG_CNTDV_CNTDV_SHIFT (0U)
#define RTU_GPR_CFG_CNTDV_CNTDV_WIDTH (3U)
#define RTU_GPR_CFG_CNTDV_CNTDV(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_CNTDV_CNTDV_SHIFT)) & RTU_GPR_CFG_CNTDV_CNTDV_MASK)
/*! @} */

/*! @name CFG_HALT - Core Halt Control */
/*! @{ */

#define RTU_GPR_CFG_HALT_HALT0_MASK  (0x1U)
#define RTU_GPR_CFG_HALT_HALT0_SHIFT (0U)
#define RTU_GPR_CFG_HALT_HALT0_WIDTH (1U)
#define RTU_GPR_CFG_HALT_HALT0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_HALT_HALT0_SHIFT)) & RTU_GPR_CFG_HALT_HALT0_MASK)

#define RTU_GPR_CFG_HALT_HALT1_MASK  (0x2U)
#define RTU_GPR_CFG_HALT_HALT1_SHIFT (1U)
#define RTU_GPR_CFG_HALT_HALT1_WIDTH (1U)
#define RTU_GPR_CFG_HALT_HALT1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_HALT_HALT1_SHIFT)) & RTU_GPR_CFG_HALT_HALT1_MASK)

#define RTU_GPR_CFG_HALT_HALT2_MASK  (0x4U)
#define RTU_GPR_CFG_HALT_HALT2_SHIFT (2U)
#define RTU_GPR_CFG_HALT_HALT2_WIDTH (1U)
#define RTU_GPR_CFG_HALT_HALT2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_HALT_HALT2_SHIFT)) & RTU_GPR_CFG_HALT_HALT2_MASK)

#define RTU_GPR_CFG_HALT_HALT3_MASK  (0x8U)
#define RTU_GPR_CFG_HALT_HALT3_SHIFT (3U)
#define RTU_GPR_CFG_HALT_HALT3_WIDTH (1U)
#define RTU_GPR_CFG_HALT_HALT3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_CFG_HALT_HALT3_SHIFT)) & RTU_GPR_CFG_HALT_HALT3_MASK)
/*! @} */

/*! @name STAT_FD - Core Fence and Drain Status */
/*! @{ */

#define RTU_GPR_STAT_FD_MFDID0_MASK  (0x1U)
#define RTU_GPR_STAT_FD_MFDID0_SHIFT (0U)
#define RTU_GPR_STAT_FD_MFDID0_WIDTH (1U)
#define RTU_GPR_STAT_FD_MFDID0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_MFDID0_SHIFT)) & RTU_GPR_STAT_FD_MFDID0_MASK)

#define RTU_GPR_STAT_FD_MFDID1_MASK  (0x2U)
#define RTU_GPR_STAT_FD_MFDID1_SHIFT (1U)
#define RTU_GPR_STAT_FD_MFDID1_WIDTH (1U)
#define RTU_GPR_STAT_FD_MFDID1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_MFDID1_SHIFT)) & RTU_GPR_STAT_FD_MFDID1_MASK)

#define RTU_GPR_STAT_FD_MFDID2_MASK  (0x4U)
#define RTU_GPR_STAT_FD_MFDID2_SHIFT (2U)
#define RTU_GPR_STAT_FD_MFDID2_WIDTH (1U)
#define RTU_GPR_STAT_FD_MFDID2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_MFDID2_SHIFT)) & RTU_GPR_STAT_FD_MFDID2_MASK)

#define RTU_GPR_STAT_FD_MFDID3_MASK  (0x8U)
#define RTU_GPR_STAT_FD_MFDID3_SHIFT (3U)
#define RTU_GPR_STAT_FD_MFDID3_WIDTH (1U)
#define RTU_GPR_STAT_FD_MFDID3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_MFDID3_SHIFT)) & RTU_GPR_STAT_FD_MFDID3_MASK)

#define RTU_GPR_STAT_FD_FFDID0_MASK  (0x10U)
#define RTU_GPR_STAT_FD_FFDID0_SHIFT (4U)
#define RTU_GPR_STAT_FD_FFDID0_WIDTH (1U)
#define RTU_GPR_STAT_FD_FFDID0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_FFDID0_SHIFT)) & RTU_GPR_STAT_FD_FFDID0_MASK)

#define RTU_GPR_STAT_FD_FFDID1_MASK  (0x20U)
#define RTU_GPR_STAT_FD_FFDID1_SHIFT (5U)
#define RTU_GPR_STAT_FD_FFDID1_WIDTH (1U)
#define RTU_GPR_STAT_FD_FFDID1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_FFDID1_SHIFT)) & RTU_GPR_STAT_FD_FFDID1_MASK)

#define RTU_GPR_STAT_FD_FFDID2_MASK  (0x40U)
#define RTU_GPR_STAT_FD_FFDID2_SHIFT (6U)
#define RTU_GPR_STAT_FD_FFDID2_WIDTH (1U)
#define RTU_GPR_STAT_FD_FFDID2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_FFDID2_SHIFT)) & RTU_GPR_STAT_FD_FFDID2_MASK)

#define RTU_GPR_STAT_FD_FFDID3_MASK  (0x80U)
#define RTU_GPR_STAT_FD_FFDID3_SHIFT (7U)
#define RTU_GPR_STAT_FD_FFDID3_WIDTH (1U)
#define RTU_GPR_STAT_FD_FFDID3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_FFDID3_SHIFT)) & RTU_GPR_STAT_FD_FFDID3_MASK)

#define RTU_GPR_STAT_FD_LFDID0_MASK  (0x100U)
#define RTU_GPR_STAT_FD_LFDID0_SHIFT (8U)
#define RTU_GPR_STAT_FD_LFDID0_WIDTH (1U)
#define RTU_GPR_STAT_FD_LFDID0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_LFDID0_SHIFT)) & RTU_GPR_STAT_FD_LFDID0_MASK)

#define RTU_GPR_STAT_FD_LFDID1_MASK  (0x200U)
#define RTU_GPR_STAT_FD_LFDID1_SHIFT (9U)
#define RTU_GPR_STAT_FD_LFDID1_WIDTH (1U)
#define RTU_GPR_STAT_FD_LFDID1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_LFDID1_SHIFT)) & RTU_GPR_STAT_FD_LFDID1_MASK)

#define RTU_GPR_STAT_FD_LFDID2_MASK  (0x400U)
#define RTU_GPR_STAT_FD_LFDID2_SHIFT (10U)
#define RTU_GPR_STAT_FD_LFDID2_WIDTH (1U)
#define RTU_GPR_STAT_FD_LFDID2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_LFDID2_SHIFT)) & RTU_GPR_STAT_FD_LFDID2_MASK)

#define RTU_GPR_STAT_FD_LFDID3_MASK  (0x800U)
#define RTU_GPR_STAT_FD_LFDID3_SHIFT (11U)
#define RTU_GPR_STAT_FD_LFDID3_WIDTH (1U)
#define RTU_GPR_STAT_FD_LFDID3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_LFDID3_SHIFT)) & RTU_GPR_STAT_FD_LFDID3_MASK)

#define RTU_GPR_STAT_FD_SFDID_MASK  (0x10000U)
#define RTU_GPR_STAT_FD_SFDID_SHIFT (16U)
#define RTU_GPR_STAT_FD_SFDID_WIDTH (1U)
#define RTU_GPR_STAT_FD_SFDID(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_FD_SFDID_SHIFT)) & RTU_GPR_STAT_FD_SFDID_MASK)
/*! @} */

/*! @name STAT_WFI - Core STANDBYWFI Status */
/*! @{ */

#define RTU_GPR_STAT_WFI_WFI0_MASK  (0x1U)
#define RTU_GPR_STAT_WFI_WFI0_SHIFT (0U)
#define RTU_GPR_STAT_WFI_WFI0_WIDTH (1U)
#define RTU_GPR_STAT_WFI_WFI0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFI_WFI0_SHIFT)) & RTU_GPR_STAT_WFI_WFI0_MASK)

#define RTU_GPR_STAT_WFI_WFI1_MASK  (0x2U)
#define RTU_GPR_STAT_WFI_WFI1_SHIFT (1U)
#define RTU_GPR_STAT_WFI_WFI1_WIDTH (1U)
#define RTU_GPR_STAT_WFI_WFI1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFI_WFI1_SHIFT)) & RTU_GPR_STAT_WFI_WFI1_MASK)

#define RTU_GPR_STAT_WFI_WFI2_MASK  (0x4U)
#define RTU_GPR_STAT_WFI_WFI2_SHIFT (2U)
#define RTU_GPR_STAT_WFI_WFI2_WIDTH (1U)
#define RTU_GPR_STAT_WFI_WFI2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFI_WFI2_SHIFT)) & RTU_GPR_STAT_WFI_WFI2_MASK)

#define RTU_GPR_STAT_WFI_WFI3_MASK  (0x8U)
#define RTU_GPR_STAT_WFI_WFI3_SHIFT (3U)
#define RTU_GPR_STAT_WFI_WFI3_WIDTH (1U)
#define RTU_GPR_STAT_WFI_WFI3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFI_WFI3_SHIFT)) & RTU_GPR_STAT_WFI_WFI3_MASK)
/*! @} */

/*! @name STAT_WFE - Core STANDBYWFE Status */
/*! @{ */

#define RTU_GPR_STAT_WFE_WFE0_MASK  (0x1U)
#define RTU_GPR_STAT_WFE_WFE0_SHIFT (0U)
#define RTU_GPR_STAT_WFE_WFE0_WIDTH (1U)
#define RTU_GPR_STAT_WFE_WFE0(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFE_WFE0_SHIFT)) & RTU_GPR_STAT_WFE_WFE0_MASK)

#define RTU_GPR_STAT_WFE_WFE1_MASK  (0x2U)
#define RTU_GPR_STAT_WFE_WFE1_SHIFT (1U)
#define RTU_GPR_STAT_WFE_WFE1_WIDTH (1U)
#define RTU_GPR_STAT_WFE_WFE1(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFE_WFE1_SHIFT)) & RTU_GPR_STAT_WFE_WFE1_MASK)

#define RTU_GPR_STAT_WFE_WFE2_MASK  (0x4U)
#define RTU_GPR_STAT_WFE_WFE2_SHIFT (2U)
#define RTU_GPR_STAT_WFE_WFE2_WIDTH (1U)
#define RTU_GPR_STAT_WFE_WFE2(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFE_WFE2_SHIFT)) & RTU_GPR_STAT_WFE_WFE2_MASK)

#define RTU_GPR_STAT_WFE_WFE3_MASK  (0x8U)
#define RTU_GPR_STAT_WFE_WFE3_SHIFT (3U)
#define RTU_GPR_STAT_WFE_WFE3_WIDTH (1U)
#define RTU_GPR_STAT_WFE_WFE3(x) \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WFE_WFE3_SHIFT)) & RTU_GPR_STAT_WFE_WFE3_MASK)
/*! @} */

/*! @name STAT_WRSTREQ - Core WARMRSTREQ Status */
/*! @{ */

#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ0_MASK  (0x1U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ0_SHIFT (0U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ0_WIDTH (1U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WRSTREQ_WARMRSTREQ0_SHIFT)) & \
        RTU_GPR_STAT_WRSTREQ_WARMRSTREQ0_MASK)

#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ1_MASK  (0x2U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ1_SHIFT (1U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ1_WIDTH (1U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WRSTREQ_WARMRSTREQ1_SHIFT)) & \
        RTU_GPR_STAT_WRSTREQ_WARMRSTREQ1_MASK)

#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ2_MASK  (0x4U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ2_SHIFT (2U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ2_WIDTH (1U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WRSTREQ_WARMRSTREQ2_SHIFT)) & \
        RTU_GPR_STAT_WRSTREQ_WARMRSTREQ2_MASK)

#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ3_MASK  (0x8U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ3_SHIFT (3U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ3_WIDTH (1U)
#define RTU_GPR_STAT_WRSTREQ_WARMRSTREQ3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_WRSTREQ_WARMRSTREQ3_SHIFT)) & \
        RTU_GPR_STAT_WRSTREQ_WARMRSTREQ3_MASK)
/*! @} */

/*! @name STAT_EVC0 - Core0 External Event Status */
/*! @{ */

#define RTU_GPR_STAT_EVC0_C0_EV0_MASK  (0x1U)
#define RTU_GPR_STAT_EVC0_C0_EV0_SHIFT (0U)
#define RTU_GPR_STAT_EVC0_C0_EV0_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV0_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV0_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV1_MASK  (0x2U)
#define RTU_GPR_STAT_EVC0_C0_EV1_SHIFT (1U)
#define RTU_GPR_STAT_EVC0_C0_EV1_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV1_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV1_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV2_MASK  (0x4U)
#define RTU_GPR_STAT_EVC0_C0_EV2_SHIFT (2U)
#define RTU_GPR_STAT_EVC0_C0_EV2_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV2_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV2_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV3_MASK  (0x8U)
#define RTU_GPR_STAT_EVC0_C0_EV3_SHIFT (3U)
#define RTU_GPR_STAT_EVC0_C0_EV3_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV3_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV3_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV4_MASK  (0x10U)
#define RTU_GPR_STAT_EVC0_C0_EV4_SHIFT (4U)
#define RTU_GPR_STAT_EVC0_C0_EV4_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV4(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV4_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV4_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV5_MASK  (0x20U)
#define RTU_GPR_STAT_EVC0_C0_EV5_SHIFT (5U)
#define RTU_GPR_STAT_EVC0_C0_EV5_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV5(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV5_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV5_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV6_MASK  (0x40U)
#define RTU_GPR_STAT_EVC0_C0_EV6_SHIFT (6U)
#define RTU_GPR_STAT_EVC0_C0_EV6_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV6(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV6_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV6_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV7_MASK  (0x80U)
#define RTU_GPR_STAT_EVC0_C0_EV7_SHIFT (7U)
#define RTU_GPR_STAT_EVC0_C0_EV7_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV7(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV7_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV7_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV8_MASK  (0x100U)
#define RTU_GPR_STAT_EVC0_C0_EV8_SHIFT (8U)
#define RTU_GPR_STAT_EVC0_C0_EV8_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV8(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV8_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV8_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV9_MASK  (0x200U)
#define RTU_GPR_STAT_EVC0_C0_EV9_SHIFT (9U)
#define RTU_GPR_STAT_EVC0_C0_EV9_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV9(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV9_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV9_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV10_MASK  (0x400U)
#define RTU_GPR_STAT_EVC0_C0_EV10_SHIFT (10U)
#define RTU_GPR_STAT_EVC0_C0_EV10_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV10(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV10_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV10_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV11_MASK  (0x800U)
#define RTU_GPR_STAT_EVC0_C0_EV11_SHIFT (11U)
#define RTU_GPR_STAT_EVC0_C0_EV11_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV11(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV11_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV11_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV12_MASK  (0x1000U)
#define RTU_GPR_STAT_EVC0_C0_EV12_SHIFT (12U)
#define RTU_GPR_STAT_EVC0_C0_EV12_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV12(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV12_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV12_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV13_MASK  (0x2000U)
#define RTU_GPR_STAT_EVC0_C0_EV13_SHIFT (13U)
#define RTU_GPR_STAT_EVC0_C0_EV13_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV13(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV13_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV13_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV14_MASK  (0x4000U)
#define RTU_GPR_STAT_EVC0_C0_EV14_SHIFT (14U)
#define RTU_GPR_STAT_EVC0_C0_EV14_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV14(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV14_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV14_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV15_MASK  (0x8000U)
#define RTU_GPR_STAT_EVC0_C0_EV15_SHIFT (15U)
#define RTU_GPR_STAT_EVC0_C0_EV15_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV15(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV15_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV15_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV16_MASK  (0x10000U)
#define RTU_GPR_STAT_EVC0_C0_EV16_SHIFT (16U)
#define RTU_GPR_STAT_EVC0_C0_EV16_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV16(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV16_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV16_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV17_MASK  (0x20000U)
#define RTU_GPR_STAT_EVC0_C0_EV17_SHIFT (17U)
#define RTU_GPR_STAT_EVC0_C0_EV17_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV17(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV17_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV17_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV18_MASK  (0x40000U)
#define RTU_GPR_STAT_EVC0_C0_EV18_SHIFT (18U)
#define RTU_GPR_STAT_EVC0_C0_EV18_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV18(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV18_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV18_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV19_MASK  (0x80000U)
#define RTU_GPR_STAT_EVC0_C0_EV19_SHIFT (19U)
#define RTU_GPR_STAT_EVC0_C0_EV19_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV19(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV19_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV19_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV20_MASK  (0x100000U)
#define RTU_GPR_STAT_EVC0_C0_EV20_SHIFT (20U)
#define RTU_GPR_STAT_EVC0_C0_EV20_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV20(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV20_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV20_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV21_MASK  (0x200000U)
#define RTU_GPR_STAT_EVC0_C0_EV21_SHIFT (21U)
#define RTU_GPR_STAT_EVC0_C0_EV21_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV21(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV21_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV21_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV22_MASK  (0x400000U)
#define RTU_GPR_STAT_EVC0_C0_EV22_SHIFT (22U)
#define RTU_GPR_STAT_EVC0_C0_EV22_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV22(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV22_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV22_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV23_MASK  (0x800000U)
#define RTU_GPR_STAT_EVC0_C0_EV23_SHIFT (23U)
#define RTU_GPR_STAT_EVC0_C0_EV23_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV23(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV23_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV23_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV24_MASK  (0x1000000U)
#define RTU_GPR_STAT_EVC0_C0_EV24_SHIFT (24U)
#define RTU_GPR_STAT_EVC0_C0_EV24_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV24(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV24_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV24_MASK)

#define RTU_GPR_STAT_EVC0_C0_EV25_MASK  (0x2000000U)
#define RTU_GPR_STAT_EVC0_C0_EV25_SHIFT (25U)
#define RTU_GPR_STAT_EVC0_C0_EV25_WIDTH (1U)
#define RTU_GPR_STAT_EVC0_C0_EV25(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC0_C0_EV25_SHIFT)) & \
        RTU_GPR_STAT_EVC0_C0_EV25_MASK)
/*! @} */

/*! @name STAT_EVC1 - Core1 External Event Status */
/*! @{ */

#define RTU_GPR_STAT_EVC1_C1_EV0_MASK  (0x1U)
#define RTU_GPR_STAT_EVC1_C1_EV0_SHIFT (0U)
#define RTU_GPR_STAT_EVC1_C1_EV0_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV0_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV0_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV1_MASK  (0x2U)
#define RTU_GPR_STAT_EVC1_C1_EV1_SHIFT (1U)
#define RTU_GPR_STAT_EVC1_C1_EV1_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV1_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV1_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV2_MASK  (0x4U)
#define RTU_GPR_STAT_EVC1_C1_EV2_SHIFT (2U)
#define RTU_GPR_STAT_EVC1_C1_EV2_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV2_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV2_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV3_MASK  (0x8U)
#define RTU_GPR_STAT_EVC1_C1_EV3_SHIFT (3U)
#define RTU_GPR_STAT_EVC1_C1_EV3_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV3_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV3_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV4_MASK  (0x10U)
#define RTU_GPR_STAT_EVC1_C1_EV4_SHIFT (4U)
#define RTU_GPR_STAT_EVC1_C1_EV4_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV4(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV4_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV4_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV5_MASK  (0x20U)
#define RTU_GPR_STAT_EVC1_C1_EV5_SHIFT (5U)
#define RTU_GPR_STAT_EVC1_C1_EV5_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV5(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV5_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV5_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV6_MASK  (0x40U)
#define RTU_GPR_STAT_EVC1_C1_EV6_SHIFT (6U)
#define RTU_GPR_STAT_EVC1_C1_EV6_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV6(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV6_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV6_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV7_MASK  (0x80U)
#define RTU_GPR_STAT_EVC1_C1_EV7_SHIFT (7U)
#define RTU_GPR_STAT_EVC1_C1_EV7_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV7(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV7_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV7_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV8_MASK  (0x100U)
#define RTU_GPR_STAT_EVC1_C1_EV8_SHIFT (8U)
#define RTU_GPR_STAT_EVC1_C1_EV8_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV8(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV8_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV8_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV9_MASK  (0x200U)
#define RTU_GPR_STAT_EVC1_C1_EV9_SHIFT (9U)
#define RTU_GPR_STAT_EVC1_C1_EV9_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV9(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV9_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV9_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV10_MASK  (0x400U)
#define RTU_GPR_STAT_EVC1_C1_EV10_SHIFT (10U)
#define RTU_GPR_STAT_EVC1_C1_EV10_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV10(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV10_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV10_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV11_MASK  (0x800U)
#define RTU_GPR_STAT_EVC1_C1_EV11_SHIFT (11U)
#define RTU_GPR_STAT_EVC1_C1_EV11_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV11(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV11_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV11_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV12_MASK  (0x1000U)
#define RTU_GPR_STAT_EVC1_C1_EV12_SHIFT (12U)
#define RTU_GPR_STAT_EVC1_C1_EV12_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV12(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV12_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV12_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV13_MASK  (0x2000U)
#define RTU_GPR_STAT_EVC1_C1_EV13_SHIFT (13U)
#define RTU_GPR_STAT_EVC1_C1_EV13_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV13(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV13_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV13_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV14_MASK  (0x4000U)
#define RTU_GPR_STAT_EVC1_C1_EV14_SHIFT (14U)
#define RTU_GPR_STAT_EVC1_C1_EV14_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV14(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV14_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV14_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV15_MASK  (0x8000U)
#define RTU_GPR_STAT_EVC1_C1_EV15_SHIFT (15U)
#define RTU_GPR_STAT_EVC1_C1_EV15_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV15(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV15_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV15_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV16_MASK  (0x10000U)
#define RTU_GPR_STAT_EVC1_C1_EV16_SHIFT (16U)
#define RTU_GPR_STAT_EVC1_C1_EV16_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV16(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV16_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV16_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV17_MASK  (0x20000U)
#define RTU_GPR_STAT_EVC1_C1_EV17_SHIFT (17U)
#define RTU_GPR_STAT_EVC1_C1_EV17_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV17(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV17_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV17_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV18_MASK  (0x40000U)
#define RTU_GPR_STAT_EVC1_C1_EV18_SHIFT (18U)
#define RTU_GPR_STAT_EVC1_C1_EV18_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV18(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV18_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV18_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV19_MASK  (0x80000U)
#define RTU_GPR_STAT_EVC1_C1_EV19_SHIFT (19U)
#define RTU_GPR_STAT_EVC1_C1_EV19_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV19(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV19_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV19_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV20_MASK  (0x100000U)
#define RTU_GPR_STAT_EVC1_C1_EV20_SHIFT (20U)
#define RTU_GPR_STAT_EVC1_C1_EV20_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV20(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV20_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV20_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV21_MASK  (0x200000U)
#define RTU_GPR_STAT_EVC1_C1_EV21_SHIFT (21U)
#define RTU_GPR_STAT_EVC1_C1_EV21_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV21(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV21_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV21_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV22_MASK  (0x400000U)
#define RTU_GPR_STAT_EVC1_C1_EV22_SHIFT (22U)
#define RTU_GPR_STAT_EVC1_C1_EV22_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV22(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV22_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV22_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV23_MASK  (0x800000U)
#define RTU_GPR_STAT_EVC1_C1_EV23_SHIFT (23U)
#define RTU_GPR_STAT_EVC1_C1_EV23_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV23(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV23_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV23_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV24_MASK  (0x1000000U)
#define RTU_GPR_STAT_EVC1_C1_EV24_SHIFT (24U)
#define RTU_GPR_STAT_EVC1_C1_EV24_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV24(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV24_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV24_MASK)

#define RTU_GPR_STAT_EVC1_C1_EV25_MASK  (0x2000000U)
#define RTU_GPR_STAT_EVC1_C1_EV25_SHIFT (25U)
#define RTU_GPR_STAT_EVC1_C1_EV25_WIDTH (1U)
#define RTU_GPR_STAT_EVC1_C1_EV25(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC1_C1_EV25_SHIFT)) & \
        RTU_GPR_STAT_EVC1_C1_EV25_MASK)
/*! @} */

/*! @name STAT_EVC2 - Core2 External Event Status */
/*! @{ */

#define RTU_GPR_STAT_EVC2_C2_EV0_MASK  (0x1U)
#define RTU_GPR_STAT_EVC2_C2_EV0_SHIFT (0U)
#define RTU_GPR_STAT_EVC2_C2_EV0_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV0_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV0_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV1_MASK  (0x2U)
#define RTU_GPR_STAT_EVC2_C2_EV1_SHIFT (1U)
#define RTU_GPR_STAT_EVC2_C2_EV1_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV1_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV1_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV2_MASK  (0x4U)
#define RTU_GPR_STAT_EVC2_C2_EV2_SHIFT (2U)
#define RTU_GPR_STAT_EVC2_C2_EV2_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV2_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV2_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV3_MASK  (0x8U)
#define RTU_GPR_STAT_EVC2_C2_EV3_SHIFT (3U)
#define RTU_GPR_STAT_EVC2_C2_EV3_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV3_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV3_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV4_MASK  (0x10U)
#define RTU_GPR_STAT_EVC2_C2_EV4_SHIFT (4U)
#define RTU_GPR_STAT_EVC2_C2_EV4_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV4(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV4_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV4_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV5_MASK  (0x20U)
#define RTU_GPR_STAT_EVC2_C2_EV5_SHIFT (5U)
#define RTU_GPR_STAT_EVC2_C2_EV5_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV5(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV5_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV5_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV6_MASK  (0x40U)
#define RTU_GPR_STAT_EVC2_C2_EV6_SHIFT (6U)
#define RTU_GPR_STAT_EVC2_C2_EV6_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV6(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV6_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV6_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV7_MASK  (0x80U)
#define RTU_GPR_STAT_EVC2_C2_EV7_SHIFT (7U)
#define RTU_GPR_STAT_EVC2_C2_EV7_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV7(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV7_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV7_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV8_MASK  (0x100U)
#define RTU_GPR_STAT_EVC2_C2_EV8_SHIFT (8U)
#define RTU_GPR_STAT_EVC2_C2_EV8_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV8(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV8_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV8_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV9_MASK  (0x200U)
#define RTU_GPR_STAT_EVC2_C2_EV9_SHIFT (9U)
#define RTU_GPR_STAT_EVC2_C2_EV9_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV9(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV9_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV9_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV10_MASK  (0x400U)
#define RTU_GPR_STAT_EVC2_C2_EV10_SHIFT (10U)
#define RTU_GPR_STAT_EVC2_C2_EV10_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV10(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV10_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV10_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV11_MASK  (0x800U)
#define RTU_GPR_STAT_EVC2_C2_EV11_SHIFT (11U)
#define RTU_GPR_STAT_EVC2_C2_EV11_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV11(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV11_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV11_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV12_MASK  (0x1000U)
#define RTU_GPR_STAT_EVC2_C2_EV12_SHIFT (12U)
#define RTU_GPR_STAT_EVC2_C2_EV12_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV12(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV12_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV12_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV13_MASK  (0x2000U)
#define RTU_GPR_STAT_EVC2_C2_EV13_SHIFT (13U)
#define RTU_GPR_STAT_EVC2_C2_EV13_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV13(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV13_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV13_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV14_MASK  (0x4000U)
#define RTU_GPR_STAT_EVC2_C2_EV14_SHIFT (14U)
#define RTU_GPR_STAT_EVC2_C2_EV14_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV14(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV14_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV14_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV15_MASK  (0x8000U)
#define RTU_GPR_STAT_EVC2_C2_EV15_SHIFT (15U)
#define RTU_GPR_STAT_EVC2_C2_EV15_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV15(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV15_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV15_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV16_MASK  (0x10000U)
#define RTU_GPR_STAT_EVC2_C2_EV16_SHIFT (16U)
#define RTU_GPR_STAT_EVC2_C2_EV16_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV16(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV16_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV16_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV17_MASK  (0x20000U)
#define RTU_GPR_STAT_EVC2_C2_EV17_SHIFT (17U)
#define RTU_GPR_STAT_EVC2_C2_EV17_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV17(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV17_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV17_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV18_MASK  (0x40000U)
#define RTU_GPR_STAT_EVC2_C2_EV18_SHIFT (18U)
#define RTU_GPR_STAT_EVC2_C2_EV18_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV18(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV18_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV18_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV19_MASK  (0x80000U)
#define RTU_GPR_STAT_EVC2_C2_EV19_SHIFT (19U)
#define RTU_GPR_STAT_EVC2_C2_EV19_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV19(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV19_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV19_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV20_MASK  (0x100000U)
#define RTU_GPR_STAT_EVC2_C2_EV20_SHIFT (20U)
#define RTU_GPR_STAT_EVC2_C2_EV20_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV20(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV20_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV20_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV21_MASK  (0x200000U)
#define RTU_GPR_STAT_EVC2_C2_EV21_SHIFT (21U)
#define RTU_GPR_STAT_EVC2_C2_EV21_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV21(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV21_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV21_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV22_MASK  (0x400000U)
#define RTU_GPR_STAT_EVC2_C2_EV22_SHIFT (22U)
#define RTU_GPR_STAT_EVC2_C2_EV22_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV22(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV22_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV22_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV23_MASK  (0x800000U)
#define RTU_GPR_STAT_EVC2_C2_EV23_SHIFT (23U)
#define RTU_GPR_STAT_EVC2_C2_EV23_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV23(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV23_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV23_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV24_MASK  (0x1000000U)
#define RTU_GPR_STAT_EVC2_C2_EV24_SHIFT (24U)
#define RTU_GPR_STAT_EVC2_C2_EV24_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV24(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV24_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV24_MASK)

#define RTU_GPR_STAT_EVC2_C2_EV25_MASK  (0x2000000U)
#define RTU_GPR_STAT_EVC2_C2_EV25_SHIFT (25U)
#define RTU_GPR_STAT_EVC2_C2_EV25_WIDTH (1U)
#define RTU_GPR_STAT_EVC2_C2_EV25(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC2_C2_EV25_SHIFT)) & \
        RTU_GPR_STAT_EVC2_C2_EV25_MASK)
/*! @} */

/*! @name STAT_EVC3 - Core3 External Event Status */
/*! @{ */

#define RTU_GPR_STAT_EVC3_C3_EV0_MASK  (0x1U)
#define RTU_GPR_STAT_EVC3_C3_EV0_SHIFT (0U)
#define RTU_GPR_STAT_EVC3_C3_EV0_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV0_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV0_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV1_MASK  (0x2U)
#define RTU_GPR_STAT_EVC3_C3_EV1_SHIFT (1U)
#define RTU_GPR_STAT_EVC3_C3_EV1_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV1_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV1_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV2_MASK  (0x4U)
#define RTU_GPR_STAT_EVC3_C3_EV2_SHIFT (2U)
#define RTU_GPR_STAT_EVC3_C3_EV2_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV2_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV2_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV3_MASK  (0x8U)
#define RTU_GPR_STAT_EVC3_C3_EV3_SHIFT (3U)
#define RTU_GPR_STAT_EVC3_C3_EV3_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV3_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV3_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV4_MASK  (0x10U)
#define RTU_GPR_STAT_EVC3_C3_EV4_SHIFT (4U)
#define RTU_GPR_STAT_EVC3_C3_EV4_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV4(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV4_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV4_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV5_MASK  (0x20U)
#define RTU_GPR_STAT_EVC3_C3_EV5_SHIFT (5U)
#define RTU_GPR_STAT_EVC3_C3_EV5_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV5(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV5_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV5_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV6_MASK  (0x40U)
#define RTU_GPR_STAT_EVC3_C3_EV6_SHIFT (6U)
#define RTU_GPR_STAT_EVC3_C3_EV6_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV6(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV6_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV6_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV7_MASK  (0x80U)
#define RTU_GPR_STAT_EVC3_C3_EV7_SHIFT (7U)
#define RTU_GPR_STAT_EVC3_C3_EV7_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV7(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV7_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV7_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV8_MASK  (0x100U)
#define RTU_GPR_STAT_EVC3_C3_EV8_SHIFT (8U)
#define RTU_GPR_STAT_EVC3_C3_EV8_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV8(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV8_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV8_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV9_MASK  (0x200U)
#define RTU_GPR_STAT_EVC3_C3_EV9_SHIFT (9U)
#define RTU_GPR_STAT_EVC3_C3_EV9_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV9(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV9_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV9_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV10_MASK  (0x400U)
#define RTU_GPR_STAT_EVC3_C3_EV10_SHIFT (10U)
#define RTU_GPR_STAT_EVC3_C3_EV10_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV10(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV10_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV10_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV11_MASK  (0x800U)
#define RTU_GPR_STAT_EVC3_C3_EV11_SHIFT (11U)
#define RTU_GPR_STAT_EVC3_C3_EV11_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV11(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV11_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV11_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV12_MASK  (0x1000U)
#define RTU_GPR_STAT_EVC3_C3_EV12_SHIFT (12U)
#define RTU_GPR_STAT_EVC3_C3_EV12_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV12(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV12_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV12_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV13_MASK  (0x2000U)
#define RTU_GPR_STAT_EVC3_C3_EV13_SHIFT (13U)
#define RTU_GPR_STAT_EVC3_C3_EV13_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV13(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV13_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV13_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV14_MASK  (0x4000U)
#define RTU_GPR_STAT_EVC3_C3_EV14_SHIFT (14U)
#define RTU_GPR_STAT_EVC3_C3_EV14_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV14(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV14_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV14_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV15_MASK  (0x8000U)
#define RTU_GPR_STAT_EVC3_C3_EV15_SHIFT (15U)
#define RTU_GPR_STAT_EVC3_C3_EV15_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV15(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV15_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV15_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV16_MASK  (0x10000U)
#define RTU_GPR_STAT_EVC3_C3_EV16_SHIFT (16U)
#define RTU_GPR_STAT_EVC3_C3_EV16_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV16(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV16_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV16_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV17_MASK  (0x20000U)
#define RTU_GPR_STAT_EVC3_C3_EV17_SHIFT (17U)
#define RTU_GPR_STAT_EVC3_C3_EV17_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV17(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV17_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV17_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV18_MASK  (0x40000U)
#define RTU_GPR_STAT_EVC3_C3_EV18_SHIFT (18U)
#define RTU_GPR_STAT_EVC3_C3_EV18_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV18(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV18_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV18_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV19_MASK  (0x80000U)
#define RTU_GPR_STAT_EVC3_C3_EV19_SHIFT (19U)
#define RTU_GPR_STAT_EVC3_C3_EV19_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV19(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV19_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV19_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV20_MASK  (0x100000U)
#define RTU_GPR_STAT_EVC3_C3_EV20_SHIFT (20U)
#define RTU_GPR_STAT_EVC3_C3_EV20_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV20(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV20_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV20_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV21_MASK  (0x200000U)
#define RTU_GPR_STAT_EVC3_C3_EV21_SHIFT (21U)
#define RTU_GPR_STAT_EVC3_C3_EV21_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV21(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV21_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV21_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV22_MASK  (0x400000U)
#define RTU_GPR_STAT_EVC3_C3_EV22_SHIFT (22U)
#define RTU_GPR_STAT_EVC3_C3_EV22_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV22(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV22_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV22_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV23_MASK  (0x800000U)
#define RTU_GPR_STAT_EVC3_C3_EV23_SHIFT (23U)
#define RTU_GPR_STAT_EVC3_C3_EV23_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV23(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV23_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV23_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV24_MASK  (0x1000000U)
#define RTU_GPR_STAT_EVC3_C3_EV24_SHIFT (24U)
#define RTU_GPR_STAT_EVC3_C3_EV24_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV24(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV24_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV24_MASK)

#define RTU_GPR_STAT_EVC3_C3_EV25_MASK  (0x2000000U)
#define RTU_GPR_STAT_EVC3_C3_EV25_SHIFT (25U)
#define RTU_GPR_STAT_EVC3_C3_EV25_WIDTH (1U)
#define RTU_GPR_STAT_EVC3_C3_EV25(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_EVC3_C3_EV25_SHIFT)) & \
        RTU_GPR_STAT_EVC3_C3_EV25_MASK)
/*! @} */

/*! @name STAT_MERRPM0 - Primary Error Interface Memory Identifier Core0 */
/*! @{ */

#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEM0_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEM0_SHIFT (0U)
#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEM0_WIDTH (15U)
#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEM0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM0_PRIMEMERRMEM0_SHIFT)) & \
        RTU_GPR_STAT_MERRPM0_PRIMEMERRMEM0_MASK)

#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEMV0_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEMV0_SHIFT (31U)
#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEMV0_WIDTH (1U)
#define RTU_GPR_STAT_MERRPM0_PRIMEMERRMEMV0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM0_PRIMEMERRMEMV0_SHIFT)) & \
        RTU_GPR_STAT_MERRPM0_PRIMEMERRMEMV0_MASK)
/*! @} */

/*! @name STAT_MERRPX0 - Primary Error Interface Index Core0 */
/*! @{ */

#define RTU_GPR_STAT_MERRPX0_PRIMEMERRMEIDX0_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRPX0_PRIMEMERRMEIDX0_SHIFT (0U)
#define RTU_GPR_STAT_MERRPX0_PRIMEMERRMEIDX0_WIDTH (25U)
#define RTU_GPR_STAT_MERRPX0_PRIMEMERRMEIDX0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPX0_PRIMEMERRMEIDX0_SHIFT)) & \
        RTU_GPR_STAT_MERRPX0_PRIMEMERRMEIDX0_MASK)
/*! @} */

/*! @name STAT_MERRSM0 - Secondary Error Interface Memory Identifier Core0 */
/*! @{ */

#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEM0_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEM0_SHIFT (0U)
#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEM0_WIDTH (15U)
#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEM0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM0_SECMEMERRMEM0_SHIFT)) & \
        RTU_GPR_STAT_MERRSM0_SECMEMERRMEM0_MASK)

#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEMV0_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEMV0_SHIFT (31U)
#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEMV0_WIDTH (1U)
#define RTU_GPR_STAT_MERRSM0_SECMEMERRMEMV0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM0_SECMEMERRMEMV0_SHIFT)) & \
        RTU_GPR_STAT_MERRSM0_SECMEMERRMEMV0_MASK)
/*! @} */

/*! @name STAT_MERRSX0 - Secondary Error Interface Index Core0 */
/*! @{ */

#define RTU_GPR_STAT_MERRSX0_SECMEMERRMEIDX0_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRSX0_SECMEMERRMEIDX0_SHIFT (0U)
#define RTU_GPR_STAT_MERRSX0_SECMEMERRMEIDX0_WIDTH (25U)
#define RTU_GPR_STAT_MERRSX0_SECMEMERRMEIDX0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSX0_SECMEMERRMEIDX0_SHIFT)) & \
        RTU_GPR_STAT_MERRSX0_SECMEMERRMEIDX0_MASK)
/*! @} */

/*! @name STAT_MERRPM1 - Primary Error Interface Memory Identifier Core1 */
/*! @{ */

#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEM1_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEM1_SHIFT (0U)
#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEM1_WIDTH (15U)
#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEM1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM1_PRIMEMERRMEM1_SHIFT)) & \
        RTU_GPR_STAT_MERRPM1_PRIMEMERRMEM1_MASK)

#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEMV1_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEMV1_SHIFT (31U)
#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEMV1_WIDTH (1U)
#define RTU_GPR_STAT_MERRPM1_PRIMEMERRMEMV1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM1_PRIMEMERRMEMV1_SHIFT)) & \
        RTU_GPR_STAT_MERRPM1_PRIMEMERRMEMV1_MASK)
/*! @} */

/*! @name STAT_MERRPX1 - Primary Error Interface Index Core1 */
/*! @{ */

#define RTU_GPR_STAT_MERRPX1_PRIMEMERRMEIDX1_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRPX1_PRIMEMERRMEIDX1_SHIFT (0U)
#define RTU_GPR_STAT_MERRPX1_PRIMEMERRMEIDX1_WIDTH (25U)
#define RTU_GPR_STAT_MERRPX1_PRIMEMERRMEIDX1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPX1_PRIMEMERRMEIDX1_SHIFT)) & \
        RTU_GPR_STAT_MERRPX1_PRIMEMERRMEIDX1_MASK)
/*! @} */

/*! @name STAT_MERRSM1 - Secondary Error Interface Memory Identifier Core1 */
/*! @{ */

#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEM1_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEM1_SHIFT (0U)
#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEM1_WIDTH (15U)
#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEM1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM1_SECMEMERRMEM1_SHIFT)) & \
        RTU_GPR_STAT_MERRSM1_SECMEMERRMEM1_MASK)

#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEMV1_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEMV1_SHIFT (31U)
#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEMV1_WIDTH (1U)
#define RTU_GPR_STAT_MERRSM1_SECMEMERRMEMV1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM1_SECMEMERRMEMV1_SHIFT)) & \
        RTU_GPR_STAT_MERRSM1_SECMEMERRMEMV1_MASK)
/*! @} */

/*! @name STAT_MERRSX1 - Secondary Error Interface Index Core1 */
/*! @{ */

#define RTU_GPR_STAT_MERRSX1_SECMEMERRMEIDX1_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRSX1_SECMEMERRMEIDX1_SHIFT (0U)
#define RTU_GPR_STAT_MERRSX1_SECMEMERRMEIDX1_WIDTH (25U)
#define RTU_GPR_STAT_MERRSX1_SECMEMERRMEIDX1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSX1_SECMEMERRMEIDX1_SHIFT)) & \
        RTU_GPR_STAT_MERRSX1_SECMEMERRMEIDX1_MASK)
/*! @} */

/*! @name STAT_MERRPM2 - Primary Error Interface Memory Identifier Core2 */
/*! @{ */

#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEM2_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEM2_SHIFT (0U)
#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEM2_WIDTH (15U)
#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEM2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM2_PRIMEMERRMEM2_SHIFT)) & \
        RTU_GPR_STAT_MERRPM2_PRIMEMERRMEM2_MASK)

#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEMV2_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEMV2_SHIFT (31U)
#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEMV2_WIDTH (1U)
#define RTU_GPR_STAT_MERRPM2_PRIMEMERRMEMV2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM2_PRIMEMERRMEMV2_SHIFT)) & \
        RTU_GPR_STAT_MERRPM2_PRIMEMERRMEMV2_MASK)
/*! @} */

/*! @name STAT_MERRPX2 - Primary Error Interface Index Core2 */
/*! @{ */

#define RTU_GPR_STAT_MERRPX2_PRIMEMERRMEIDX2_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRPX2_PRIMEMERRMEIDX2_SHIFT (0U)
#define RTU_GPR_STAT_MERRPX2_PRIMEMERRMEIDX2_WIDTH (25U)
#define RTU_GPR_STAT_MERRPX2_PRIMEMERRMEIDX2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPX2_PRIMEMERRMEIDX2_SHIFT)) & \
        RTU_GPR_STAT_MERRPX2_PRIMEMERRMEIDX2_MASK)
/*! @} */

/*! @name STAT_MERRSM2 - Secondary Error Interface Memory Identifier Core2 */
/*! @{ */

#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEM2_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEM2_SHIFT (0U)
#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEM2_WIDTH (15U)
#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEM2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM2_SECMEMERRMEM2_SHIFT)) & \
        RTU_GPR_STAT_MERRSM2_SECMEMERRMEM2_MASK)

#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEMV2_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEMV2_SHIFT (31U)
#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEMV2_WIDTH (1U)
#define RTU_GPR_STAT_MERRSM2_SECMEMERRMEMV2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM2_SECMEMERRMEMV2_SHIFT)) & \
        RTU_GPR_STAT_MERRSM2_SECMEMERRMEMV2_MASK)
/*! @} */

/*! @name STAT_MERRSX2 - Secondary Error Interface Index Core2 */
/*! @{ */

#define RTU_GPR_STAT_MERRSX2_SECMEMERRMEIDX2_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRSX2_SECMEMERRMEIDX2_SHIFT (0U)
#define RTU_GPR_STAT_MERRSX2_SECMEMERRMEIDX2_WIDTH (25U)
#define RTU_GPR_STAT_MERRSX2_SECMEMERRMEIDX2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSX2_SECMEMERRMEIDX2_SHIFT)) & \
        RTU_GPR_STAT_MERRSX2_SECMEMERRMEIDX2_MASK)
/*! @} */

/*! @name STAT_MERRPM3 - Primary Error Interface Memory Identifier Core3 */
/*! @{ */

#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEM3_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEM3_SHIFT (0U)
#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEM3_WIDTH (15U)
#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEM3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM3_PRIMEMERRMEM3_SHIFT)) & \
        RTU_GPR_STAT_MERRPM3_PRIMEMERRMEM3_MASK)

#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEMV3_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEMV3_SHIFT (31U)
#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEMV3_WIDTH (1U)
#define RTU_GPR_STAT_MERRPM3_PRIMEMERRMEMV3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPM3_PRIMEMERRMEMV3_SHIFT)) & \
        RTU_GPR_STAT_MERRPM3_PRIMEMERRMEMV3_MASK)
/*! @} */

/*! @name STAT_MERRPX3 - Primary Error Interface Index Core3 */
/*! @{ */

#define RTU_GPR_STAT_MERRPX3_PRIMEMERRMEIDX3_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRPX3_PRIMEMERRMEIDX3_SHIFT (0U)
#define RTU_GPR_STAT_MERRPX3_PRIMEMERRMEIDX3_WIDTH (25U)
#define RTU_GPR_STAT_MERRPX3_PRIMEMERRMEIDX3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRPX3_PRIMEMERRMEIDX3_SHIFT)) & \
        RTU_GPR_STAT_MERRPX3_PRIMEMERRMEIDX3_MASK)
/*! @} */

/*! @name STAT_MERRSM3 - Secondary Error Interface Memory Identifier Core3 */
/*! @{ */

#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEM3_MASK  (0x7FFFU)
#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEM3_SHIFT (0U)
#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEM3_WIDTH (15U)
#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEM3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM3_SECMEMERRMEM3_SHIFT)) & \
        RTU_GPR_STAT_MERRSM3_SECMEMERRMEM3_MASK)

#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEMV3_MASK  (0x80000000U)
#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEMV3_SHIFT (31U)
#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEMV3_WIDTH (1U)
#define RTU_GPR_STAT_MERRSM3_SECMEMERRMEMV3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSM3_SECMEMERRMEMV3_SHIFT)) & \
        RTU_GPR_STAT_MERRSM3_SECMEMERRMEMV3_MASK)
/*! @} */

/*! @name STAT_MERRSX3 - Secondary Error Interface Index Core3 */
/*! @{ */

#define RTU_GPR_STAT_MERRSX3_SECMEMERRMEIDX3_MASK  (0x1FFFFFFU)
#define RTU_GPR_STAT_MERRSX3_SECMEMERRMEIDX3_SHIFT (0U)
#define RTU_GPR_STAT_MERRSX3_SECMEMERRMEIDX3_WIDTH (25U)
#define RTU_GPR_STAT_MERRSX3_SECMEMERRMEIDX3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_MERRSX3_SECMEMERRMEIDX3_SHIFT)) & \
        RTU_GPR_STAT_MERRSX3_SECMEMERRMEIDX3_MASK)
/*! @} */

/*! @name STAT_PMU0EV0 - PMU Event Core0 Group0 */
/*! @{ */

#define RTU_GPR_STAT_PMU0EV0_PMUEVENT0_MASK  (0xFFFFFFFFU)
#define RTU_GPR_STAT_PMU0EV0_PMUEVENT0_SHIFT (0U)
#define RTU_GPR_STAT_PMU0EV0_PMUEVENT0_WIDTH (32U)
#define RTU_GPR_STAT_PMU0EV0_PMUEVENT0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU0EV0_PMUEVENT0_SHIFT)) & \
        RTU_GPR_STAT_PMU0EV0_PMUEVENT0_MASK)
/*! @} */

/*! @name STAT_PMU1EV0 - PMU Event Core0 Group1 */
/*! @{ */

#define RTU_GPR_STAT_PMU1EV0_PMUEVENT0_MASK  (0xFU)
#define RTU_GPR_STAT_PMU1EV0_PMUEVENT0_SHIFT (0U)
#define RTU_GPR_STAT_PMU1EV0_PMUEVENT0_WIDTH (4U)
#define RTU_GPR_STAT_PMU1EV0_PMUEVENT0(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU1EV0_PMUEVENT0_SHIFT)) & \
        RTU_GPR_STAT_PMU1EV0_PMUEVENT0_MASK)
/*! @} */

/*! @name STAT_PMU0EV1 - PMU Event Core1 Group0 */
/*! @{ */

#define RTU_GPR_STAT_PMU0EV1_PMUEVENT1_MASK  (0xFFFFFFFFU)
#define RTU_GPR_STAT_PMU0EV1_PMUEVENT1_SHIFT (0U)
#define RTU_GPR_STAT_PMU0EV1_PMUEVENT1_WIDTH (32U)
#define RTU_GPR_STAT_PMU0EV1_PMUEVENT1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU0EV1_PMUEVENT1_SHIFT)) & \
        RTU_GPR_STAT_PMU0EV1_PMUEVENT1_MASK)
/*! @} */

/*! @name STAT_PMU1EV1 - PMU Event Core1 Group1 */
/*! @{ */

#define RTU_GPR_STAT_PMU1EV1_PMUEVENT1_MASK  (0xFU)
#define RTU_GPR_STAT_PMU1EV1_PMUEVENT1_SHIFT (0U)
#define RTU_GPR_STAT_PMU1EV1_PMUEVENT1_WIDTH (4U)
#define RTU_GPR_STAT_PMU1EV1_PMUEVENT1(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU1EV1_PMUEVENT1_SHIFT)) & \
        RTU_GPR_STAT_PMU1EV1_PMUEVENT1_MASK)
/*! @} */

/*! @name STAT_PMU0EV2 - PMU Event Core2 Group0 */
/*! @{ */

#define RTU_GPR_STAT_PMU0EV2_PMUEVENT2_MASK  (0xFFFFFFFFU)
#define RTU_GPR_STAT_PMU0EV2_PMUEVENT2_SHIFT (0U)
#define RTU_GPR_STAT_PMU0EV2_PMUEVENT2_WIDTH (32U)
#define RTU_GPR_STAT_PMU0EV2_PMUEVENT2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU0EV2_PMUEVENT2_SHIFT)) & \
        RTU_GPR_STAT_PMU0EV2_PMUEVENT2_MASK)
/*! @} */

/*! @name STAT_PMU1EV2 - PMU Event Core2 Group1 */
/*! @{ */

#define RTU_GPR_STAT_PMU1EV2_PMUEVENT2_MASK  (0xFU)
#define RTU_GPR_STAT_PMU1EV2_PMUEVENT2_SHIFT (0U)
#define RTU_GPR_STAT_PMU1EV2_PMUEVENT2_WIDTH (4U)
#define RTU_GPR_STAT_PMU1EV2_PMUEVENT2(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU1EV2_PMUEVENT2_SHIFT)) & \
        RTU_GPR_STAT_PMU1EV2_PMUEVENT2_MASK)
/*! @} */

/*! @name STAT_PMU0EV3 - PMU Event Core3 Group0 */
/*! @{ */

#define RTU_GPR_STAT_PMU0EV3_PMUEVENT3_MASK  (0xFFFFFFFFU)
#define RTU_GPR_STAT_PMU0EV3_PMUEVENT3_SHIFT (0U)
#define RTU_GPR_STAT_PMU0EV3_PMUEVENT3_WIDTH (32U)
#define RTU_GPR_STAT_PMU0EV3_PMUEVENT3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU0EV3_PMUEVENT3_SHIFT)) & \
        RTU_GPR_STAT_PMU0EV3_PMUEVENT3_MASK)
/*! @} */

/*! @name STAT_PMU1EV3 - PMU Event Core3 Group1 */
/*! @{ */

#define RTU_GPR_STAT_PMU1EV3_PMUEVENT3_MASK  (0xFU)
#define RTU_GPR_STAT_PMU1EV3_PMUEVENT3_SHIFT (0U)
#define RTU_GPR_STAT_PMU1EV3_PMUEVENT3_WIDTH (4U)
#define RTU_GPR_STAT_PMU1EV3_PMUEVENT3(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_GPR_STAT_PMU1EV3_PMUEVENT3_SHIFT)) & \
        RTU_GPR_STAT_PMU1EV3_PMUEVENT3_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group RTU_GPR_Register_Masks */

/*!
 * @}
 */ /* end of group RTU_GPR_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_RTU_GPR_H_) */
