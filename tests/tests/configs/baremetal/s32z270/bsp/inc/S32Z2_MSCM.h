/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_MSCM.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_MSCM
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
#if !defined(S32Z2_MSCM_H_) /* Check if memory map has not been already included */
#define S32Z2_MSCM_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MSCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Peripheral_Access_Layer MSCM Peripheral Access Layer
 * @{
 */

/** MSCM - Size of Registers Arrays */
#define MSCM_IRSPRC_COUNT 789u

/** MSCM - Register Layout Typedef */
typedef struct {
    __I uint32_t CPXTYPE; /**< Core Processor x Type, offset: 0x0 */
    __I uint32_t CPXNUM;  /**< Core Processor x Number, offset: 0x4 */
    __I uint32_t CPXREV;  /**< Core Processor x Revision, offset: 0x8 */
    __I uint32_t CPXCFG0; /**< Core Processor x Configuration 0, offset: 0xC */
    __I uint32_t CPXCFG1; /**< Core or Cluster Processor x Configuration 1, offset: 0x10 */
    __I uint32_t CPXCFG2; /**< Core Processor x Configuration 2, offset: 0x14 */
    __I uint32_t CPXCFG3; /**< Core Processor x Configuration 3, offset: 0x18 */
    uint8_t RESERVED_0[4];
    __I uint32_t CP0TYPE; /**< Cluster Processor 0 Type, offset: 0x20 */
    __I uint32_t CP0NUM;  /**< Cluster Processor 0 Number, offset: 0x24 */
    __I uint32_t CP0REV;  /**< Core Processor 0 Revision, offset: 0x28 */
    __I uint32_t CP0CFG0; /**< Core Processor 0 Configuration 0, offset: 0x2C */
    __I uint32_t CP0CFG1; /**< Cluster Processor 0 Configuration 1, offset: 0x30 */
    __I uint32_t CP0CFG2; /**< Core Processor 0 Configuration 2, offset: 0x34 */
    __I uint32_t CP0CFG3; /**< Core Processor 0 Configuration 3, offset: 0x38 */
    uint8_t RESERVED_1[4];
    __I uint32_t CP1TYPE; /**< Cluster Processor 1 Type, offset: 0x40 */
    __I uint32_t CP1NUM;  /**< Cluster Processor 1 Number, offset: 0x44 */
    __I uint32_t CP1REV;  /**< Core Processor 1 Revision, offset: 0x48 */
    __I uint32_t CP1CFG0; /**< Core Processor 1 Configuration 0, offset: 0x4C */
    __I uint32_t CP1CFG1; /**< Cluster Processor 1 Configuration 1, offset: 0x50 */
    __I uint32_t CP1CFG2; /**< Core Processor 1 Configuration 2, offset: 0x54 */
    __I uint32_t CP1CFG3; /**< Core Processor 1 Configuration 3, offset: 0x58 */
    uint8_t RESERVED_2[4];
    __I uint32_t CP2TYPE; /**< Core Processor 2 Type, offset: 0x60 */
    __I uint32_t CP2NUM;  /**< Core Processor 2 Number, offset: 0x64 */
    __I uint32_t CP2REV;  /**< Core Processor 2 Revision, offset: 0x68 */
    __I uint32_t CP2CFG0; /**< Core Processor 2 Configuration 0, offset: 0x6C */
    __I uint32_t CP2CFG1; /**< Core Processor 2 Configuration 1, offset: 0x70 */
    __I uint32_t CP2CFG2; /**< Core Processor 2 Configuration 2, offset: 0x74 */
    __I uint32_t CP2CFG3; /**< Core Processor 2 Configuration 3, offset: 0x78 */
    uint8_t RESERVED_3[4];
    __I uint32_t CP3TYPE; /**< Core Processor 3 Type, offset: 0x80 */
    __I uint32_t CP3NUM;  /**< Core Processor 3 Number, offset: 0x84 */
    __I uint32_t CP3REV;  /**< Core Processor 3 Revision, offset: 0x88 */
    __I uint32_t CP3CFG0; /**< Core Processor 3 Configuration 0, offset: 0x8C */
    __I uint32_t CP3CFG1; /**< Core Processor 3 Configuration 1, offset: 0x90 */
    __I uint32_t CP3CFG2; /**< Core Processor 3 Configuration 2, offset: 0x94 */
    __I uint32_t CP3CFG3; /**< Core Processor 3 Configuration 3, offset: 0x98 */
    uint8_t RESERVED_4[2020];
    __IO uint16_t IRSPRC[MSCM_IRSPRC_COUNT]; /**< Interrupt Router Shared Peripheral Routing
                                                Control, array offset: 0x880, array step: 0x2 */
} MSCM_Type, *MSCM_MemMapPtr;

/** Number of instances of the MSCM module. */
#define MSCM_INSTANCE_COUNT            (1u)

/* MSCM - Peripheral instance base addresses */
/** Peripheral MSCM base address */
#define IP_MSCM_BASE                   (0x419A0000u)
/** Peripheral MSCM base pointer */
#define IP_MSCM                        ((MSCM_Type*)IP_MSCM_BASE)
/** Array initializer of MSCM peripheral base addresses */
#define IP_MSCM_BASE_ADDRS             { IP_MSCM_BASE }
/** Array initializer of MSCM peripheral base pointers */
#define IP_MSCM_BASE_PTRS              { IP_MSCM }

/* ----------------------------------------------------------------------------
   -- MSCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Register_Masks MSCM Register Masks
 * @{
 */

/*! @name CPXTYPE - Core Processor x Type */
/*! @{ */

#define MSCM_CPXTYPE_PERSONALITY_MASK  (0xFFFFFFFFU)
#define MSCM_CPXTYPE_PERSONALITY_SHIFT (0U)
#define MSCM_CPXTYPE_PERSONALITY_WIDTH (32U)
#define MSCM_CPXTYPE_PERSONALITY(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXTYPE_PERSONALITY_SHIFT)) & \
        MSCM_CPXTYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CPXNUM - Core Processor x Number */
/*! @{ */

#define MSCM_CPXNUM_CPN_MASK  (0xFU)
#define MSCM_CPXNUM_CPN_SHIFT (0U)
#define MSCM_CPXNUM_CPN_WIDTH (4U)
#define MSCM_CPXNUM_CPN(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXNUM_CPN_SHIFT)) & MSCM_CPXNUM_CPN_MASK)
/*! @} */

/*! @name CPXREV - Core Processor x Revision */
/*! @{ */

#define MSCM_CPXREV_RYPZ_MASK  (0xFFU)
#define MSCM_CPXREV_RYPZ_SHIFT (0U)
#define MSCM_CPXREV_RYPZ_WIDTH (8U)
#define MSCM_CPXREV_RYPZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXREV_RYPZ_SHIFT)) & MSCM_CPXREV_RYPZ_MASK)
/*! @} */

/*! @name CPXCFG0 - Core Processor x Configuration 0 */
/*! @{ */

#define MSCM_CPXCFG0_DCWY_MASK  (0xFFU)
#define MSCM_CPXCFG0_DCWY_SHIFT (0U)
#define MSCM_CPXCFG0_DCWY_WIDTH (8U)
#define MSCM_CPXCFG0_DCWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_DCWY_SHIFT)) & MSCM_CPXCFG0_DCWY_MASK)

#define MSCM_CPXCFG0_DCSZ_MASK  (0xFF00U)
#define MSCM_CPXCFG0_DCSZ_SHIFT (8U)
#define MSCM_CPXCFG0_DCSZ_WIDTH (8U)
#define MSCM_CPXCFG0_DCSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_DCSZ_SHIFT)) & MSCM_CPXCFG0_DCSZ_MASK)

#define MSCM_CPXCFG0_ICWY_MASK  (0xFF0000U)
#define MSCM_CPXCFG0_ICWY_SHIFT (16U)
#define MSCM_CPXCFG0_ICWY_WIDTH (8U)
#define MSCM_CPXCFG0_ICWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_ICWY_SHIFT)) & MSCM_CPXCFG0_ICWY_MASK)

#define MSCM_CPXCFG0_ICSZ_MASK  (0xFF000000U)
#define MSCM_CPXCFG0_ICSZ_SHIFT (24U)
#define MSCM_CPXCFG0_ICSZ_WIDTH (8U)
#define MSCM_CPXCFG0_ICSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_ICSZ_SHIFT)) & MSCM_CPXCFG0_ICSZ_MASK)
/*! @} */

/*! @name CPXCFG1 - Core or Cluster Processor x Configuration 1 */
/*! @{ */

#define MSCM_CPXCFG1_L2WY_MASK  (0xFF0000U)
#define MSCM_CPXCFG1_L2WY_SHIFT (16U)
#define MSCM_CPXCFG1_L2WY_WIDTH (8U)
#define MSCM_CPXCFG1_L2WY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG1_L2WY_SHIFT)) & MSCM_CPXCFG1_L2WY_MASK)

#define MSCM_CPXCFG1_L2SZ_MASK  (0xFF000000U)
#define MSCM_CPXCFG1_L2SZ_SHIFT (24U)
#define MSCM_CPXCFG1_L2SZ_WIDTH (8U)
#define MSCM_CPXCFG1_L2SZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG1_L2SZ_SHIFT)) & MSCM_CPXCFG1_L2SZ_MASK)
/*! @} */

/*! @name CPXCFG2 - Core Processor x Configuration 2 */
/*! @{ */

#define MSCM_CPXCFG2_ITCM_MASK  (0xFFFFU)
#define MSCM_CPXCFG2_ITCM_SHIFT (0U)
#define MSCM_CPXCFG2_ITCM_WIDTH (16U)
#define MSCM_CPXCFG2_ITCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG2_ITCM_SHIFT)) & MSCM_CPXCFG2_ITCM_MASK)

#define MSCM_CPXCFG2_TCM_MASK  (0xFFFF0000U)
#define MSCM_CPXCFG2_TCM_SHIFT (16U)
#define MSCM_CPXCFG2_TCM_WIDTH (16U)
#define MSCM_CPXCFG2_TCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG2_TCM_SHIFT)) & MSCM_CPXCFG2_TCM_MASK)
/*! @} */

/*! @name CPXCFG3 - Core Processor x Configuration 3 */
/*! @{ */

#define MSCM_CPXCFG3_FPU_MASK  (0x1U)
#define MSCM_CPXCFG3_FPU_SHIFT (0U)
#define MSCM_CPXCFG3_FPU_WIDTH (1U)
#define MSCM_CPXCFG3_FPU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_FPU_SHIFT)) & MSCM_CPXCFG3_FPU_MASK)

#define MSCM_CPXCFG3_SIMD_MASK  (0x2U)
#define MSCM_CPXCFG3_SIMD_SHIFT (1U)
#define MSCM_CPXCFG3_SIMD_WIDTH (1U)
#define MSCM_CPXCFG3_SIMD(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_SIMD_SHIFT)) & MSCM_CPXCFG3_SIMD_MASK)

#define MSCM_CPXCFG3_MMU_MASK  (0x4U)
#define MSCM_CPXCFG3_MMU_SHIFT (2U)
#define MSCM_CPXCFG3_MMU_WIDTH (1U)
#define MSCM_CPXCFG3_MMU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_MMU_SHIFT)) & MSCM_CPXCFG3_MMU_MASK)

#define MSCM_CPXCFG3_CMP_MASK  (0x8U)
#define MSCM_CPXCFG3_CMP_SHIFT (3U)
#define MSCM_CPXCFG3_CMP_WIDTH (1U)
#define MSCM_CPXCFG3_CMP(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_CMP_SHIFT)) & MSCM_CPXCFG3_CMP_MASK)

#define MSCM_CPXCFG3_CPY_MASK  (0x10U)
#define MSCM_CPXCFG3_CPY_SHIFT (4U)
#define MSCM_CPXCFG3_CPY_WIDTH (1U)
#define MSCM_CPXCFG3_CPY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_CPY_SHIFT)) & MSCM_CPXCFG3_CPY_MASK)
/*! @} */

/*! @name CP0TYPE - Cluster Processor 0 Type */
/*! @{ */

#define MSCM_CP0TYPE_PERSONALITY_MASK  (0xFFFFFFFFU)
#define MSCM_CP0TYPE_PERSONALITY_SHIFT (0U)
#define MSCM_CP0TYPE_PERSONALITY_WIDTH (32U)
#define MSCM_CP0TYPE_PERSONALITY(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0TYPE_PERSONALITY_SHIFT)) & \
        MSCM_CP0TYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CP0NUM - Cluster Processor 0 Number */
/*! @{ */

#define MSCM_CP0NUM_CPN_MASK  (0xFU)
#define MSCM_CP0NUM_CPN_SHIFT (0U)
#define MSCM_CP0NUM_CPN_WIDTH (4U)
#define MSCM_CP0NUM_CPN(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0NUM_CPN_SHIFT)) & MSCM_CP0NUM_CPN_MASK)
/*! @} */

/*! @name CP0REV - Core Processor 0 Revision */
/*! @{ */

#define MSCM_CP0REV_RYPZ_MASK  (0xFFU)
#define MSCM_CP0REV_RYPZ_SHIFT (0U)
#define MSCM_CP0REV_RYPZ_WIDTH (8U)
#define MSCM_CP0REV_RYPZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0REV_RYPZ_SHIFT)) & MSCM_CP0REV_RYPZ_MASK)
/*! @} */

/*! @name CP0CFG0 - Core Processor 0 Configuration 0 */
/*! @{ */

#define MSCM_CP0CFG0_DCWY_MASK  (0xFFU)
#define MSCM_CP0CFG0_DCWY_SHIFT (0U)
#define MSCM_CP0CFG0_DCWY_WIDTH (8U)
#define MSCM_CP0CFG0_DCWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_DCWY_SHIFT)) & MSCM_CP0CFG0_DCWY_MASK)

#define MSCM_CP0CFG0_DCSZ_MASK  (0xFF00U)
#define MSCM_CP0CFG0_DCSZ_SHIFT (8U)
#define MSCM_CP0CFG0_DCSZ_WIDTH (8U)
#define MSCM_CP0CFG0_DCSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_DCSZ_SHIFT)) & MSCM_CP0CFG0_DCSZ_MASK)

#define MSCM_CP0CFG0_ICWY_MASK  (0xFF0000U)
#define MSCM_CP0CFG0_ICWY_SHIFT (16U)
#define MSCM_CP0CFG0_ICWY_WIDTH (8U)
#define MSCM_CP0CFG0_ICWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_ICWY_SHIFT)) & MSCM_CP0CFG0_ICWY_MASK)

#define MSCM_CP0CFG0_ICSZ_MASK  (0xFF000000U)
#define MSCM_CP0CFG0_ICSZ_SHIFT (24U)
#define MSCM_CP0CFG0_ICSZ_WIDTH (8U)
#define MSCM_CP0CFG0_ICSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_ICSZ_SHIFT)) & MSCM_CP0CFG0_ICSZ_MASK)
/*! @} */

/*! @name CP0CFG1 - Cluster Processor 0 Configuration 1 */
/*! @{ */

#define MSCM_CP0CFG1_L2WY_MASK  (0xFF0000U)
#define MSCM_CP0CFG1_L2WY_SHIFT (16U)
#define MSCM_CP0CFG1_L2WY_WIDTH (8U)
#define MSCM_CP0CFG1_L2WY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG1_L2WY_SHIFT)) & MSCM_CP0CFG1_L2WY_MASK)

#define MSCM_CP0CFG1_L2SZ_MASK  (0xFF000000U)
#define MSCM_CP0CFG1_L2SZ_SHIFT (24U)
#define MSCM_CP0CFG1_L2SZ_WIDTH (8U)
#define MSCM_CP0CFG1_L2SZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG1_L2SZ_SHIFT)) & MSCM_CP0CFG1_L2SZ_MASK)
/*! @} */

/*! @name CP0CFG2 - Core Processor 0 Configuration 2 */
/*! @{ */

#define MSCM_CP0CFG2_TCM_MASK  (0xFFFF0000U)
#define MSCM_CP0CFG2_TCM_SHIFT (16U)
#define MSCM_CP0CFG2_TCM_WIDTH (16U)
#define MSCM_CP0CFG2_TCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG2_TCM_SHIFT)) & MSCM_CP0CFG2_TCM_MASK)
/*! @} */

/*! @name CP0CFG3 - Core Processor 0 Configuration 3 */
/*! @{ */

#define MSCM_CP0CFG3_FPU_MASK  (0x1U)
#define MSCM_CP0CFG3_FPU_SHIFT (0U)
#define MSCM_CP0CFG3_FPU_WIDTH (1U)
#define MSCM_CP0CFG3_FPU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_FPU_SHIFT)) & MSCM_CP0CFG3_FPU_MASK)

#define MSCM_CP0CFG3_SIMD_MASK  (0x2U)
#define MSCM_CP0CFG3_SIMD_SHIFT (1U)
#define MSCM_CP0CFG3_SIMD_WIDTH (1U)
#define MSCM_CP0CFG3_SIMD(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_SIMD_SHIFT)) & MSCM_CP0CFG3_SIMD_MASK)

#define MSCM_CP0CFG3_MMU_MASK  (0x4U)
#define MSCM_CP0CFG3_MMU_SHIFT (2U)
#define MSCM_CP0CFG3_MMU_WIDTH (1U)
#define MSCM_CP0CFG3_MMU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_MMU_SHIFT)) & MSCM_CP0CFG3_MMU_MASK)

#define MSCM_CP0CFG3_CMP_MASK  (0x8U)
#define MSCM_CP0CFG3_CMP_SHIFT (3U)
#define MSCM_CP0CFG3_CMP_WIDTH (1U)
#define MSCM_CP0CFG3_CMP(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_CMP_SHIFT)) & MSCM_CP0CFG3_CMP_MASK)

#define MSCM_CP0CFG3_CPY_MASK  (0x10U)
#define MSCM_CP0CFG3_CPY_SHIFT (4U)
#define MSCM_CP0CFG3_CPY_WIDTH (1U)
#define MSCM_CP0CFG3_CPY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_CPY_SHIFT)) & MSCM_CP0CFG3_CPY_MASK)
/*! @} */

/*! @name CP1TYPE - Cluster Processor 1 Type */
/*! @{ */

#define MSCM_CP1TYPE_PERSONALITY_MASK  (0xFFFFFFFFU)
#define MSCM_CP1TYPE_PERSONALITY_SHIFT (0U)
#define MSCM_CP1TYPE_PERSONALITY_WIDTH (32U)
#define MSCM_CP1TYPE_PERSONALITY(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1TYPE_PERSONALITY_SHIFT)) & \
        MSCM_CP1TYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CP1NUM - Cluster Processor 1 Number */
/*! @{ */

#define MSCM_CP1NUM_CPN_MASK  (0xFU)
#define MSCM_CP1NUM_CPN_SHIFT (0U)
#define MSCM_CP1NUM_CPN_WIDTH (4U)
#define MSCM_CP1NUM_CPN(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1NUM_CPN_SHIFT)) & MSCM_CP1NUM_CPN_MASK)
/*! @} */

/*! @name CP1REV - Core Processor 1 Revision */
/*! @{ */

#define MSCM_CP1REV_RYPZ_MASK  (0xFFU)
#define MSCM_CP1REV_RYPZ_SHIFT (0U)
#define MSCM_CP1REV_RYPZ_WIDTH (8U)
#define MSCM_CP1REV_RYPZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1REV_RYPZ_SHIFT)) & MSCM_CP1REV_RYPZ_MASK)
/*! @} */

/*! @name CP1CFG0 - Core Processor 1 Configuration 0 */
/*! @{ */

#define MSCM_CP1CFG0_DCWY_MASK  (0xFFU)
#define MSCM_CP1CFG0_DCWY_SHIFT (0U)
#define MSCM_CP1CFG0_DCWY_WIDTH (8U)
#define MSCM_CP1CFG0_DCWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG0_DCWY_SHIFT)) & MSCM_CP1CFG0_DCWY_MASK)

#define MSCM_CP1CFG0_DCSZ_MASK  (0xFF00U)
#define MSCM_CP1CFG0_DCSZ_SHIFT (8U)
#define MSCM_CP1CFG0_DCSZ_WIDTH (8U)
#define MSCM_CP1CFG0_DCSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG0_DCSZ_SHIFT)) & MSCM_CP1CFG0_DCSZ_MASK)

#define MSCM_CP1CFG0_ICWY_MASK  (0xFF0000U)
#define MSCM_CP1CFG0_ICWY_SHIFT (16U)
#define MSCM_CP1CFG0_ICWY_WIDTH (8U)
#define MSCM_CP1CFG0_ICWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG0_ICWY_SHIFT)) & MSCM_CP1CFG0_ICWY_MASK)

#define MSCM_CP1CFG0_ICSZ_MASK  (0xFF000000U)
#define MSCM_CP1CFG0_ICSZ_SHIFT (24U)
#define MSCM_CP1CFG0_ICSZ_WIDTH (8U)
#define MSCM_CP1CFG0_ICSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG0_ICSZ_SHIFT)) & MSCM_CP1CFG0_ICSZ_MASK)
/*! @} */

/*! @name CP1CFG1 - Cluster Processor 1 Configuration 1 */
/*! @{ */

#define MSCM_CP1CFG1_L2WY_MASK  (0xFF0000U)
#define MSCM_CP1CFG1_L2WY_SHIFT (16U)
#define MSCM_CP1CFG1_L2WY_WIDTH (8U)
#define MSCM_CP1CFG1_L2WY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG1_L2WY_SHIFT)) & MSCM_CP1CFG1_L2WY_MASK)

#define MSCM_CP1CFG1_L2SZ_MASK  (0xFF000000U)
#define MSCM_CP1CFG1_L2SZ_SHIFT (24U)
#define MSCM_CP1CFG1_L2SZ_WIDTH (8U)
#define MSCM_CP1CFG1_L2SZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG1_L2SZ_SHIFT)) & MSCM_CP1CFG1_L2SZ_MASK)
/*! @} */

/*! @name CP1CFG2 - Core Processor 1 Configuration 2 */
/*! @{ */

#define MSCM_CP1CFG2_TCM_MASK  (0xFFFF0000U)
#define MSCM_CP1CFG2_TCM_SHIFT (16U)
#define MSCM_CP1CFG2_TCM_WIDTH (16U)
#define MSCM_CP1CFG2_TCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG2_TCM_SHIFT)) & MSCM_CP1CFG2_TCM_MASK)
/*! @} */

/*! @name CP1CFG3 - Core Processor 1 Configuration 3 */
/*! @{ */

#define MSCM_CP1CFG3_FPU_MASK  (0x1U)
#define MSCM_CP1CFG3_FPU_SHIFT (0U)
#define MSCM_CP1CFG3_FPU_WIDTH (1U)
#define MSCM_CP1CFG3_FPU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG3_FPU_SHIFT)) & MSCM_CP1CFG3_FPU_MASK)

#define MSCM_CP1CFG3_SIMD_MASK  (0x2U)
#define MSCM_CP1CFG3_SIMD_SHIFT (1U)
#define MSCM_CP1CFG3_SIMD_WIDTH (1U)
#define MSCM_CP1CFG3_SIMD(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG3_SIMD_SHIFT)) & MSCM_CP1CFG3_SIMD_MASK)

#define MSCM_CP1CFG3_MMU_MASK  (0x4U)
#define MSCM_CP1CFG3_MMU_SHIFT (2U)
#define MSCM_CP1CFG3_MMU_WIDTH (1U)
#define MSCM_CP1CFG3_MMU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG3_MMU_SHIFT)) & MSCM_CP1CFG3_MMU_MASK)

#define MSCM_CP1CFG3_CMP_MASK  (0x8U)
#define MSCM_CP1CFG3_CMP_SHIFT (3U)
#define MSCM_CP1CFG3_CMP_WIDTH (1U)
#define MSCM_CP1CFG3_CMP(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG3_CMP_SHIFT)) & MSCM_CP1CFG3_CMP_MASK)

#define MSCM_CP1CFG3_CPY_MASK  (0x10U)
#define MSCM_CP1CFG3_CPY_SHIFT (4U)
#define MSCM_CP1CFG3_CPY_WIDTH (1U)
#define MSCM_CP1CFG3_CPY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP1CFG3_CPY_SHIFT)) & MSCM_CP1CFG3_CPY_MASK)
/*! @} */

/*! @name CP2TYPE - Core Processor 2 Type */
/*! @{ */

#define MSCM_CP2TYPE_PERSONALITY_MASK  (0xFFFFFFFFU)
#define MSCM_CP2TYPE_PERSONALITY_SHIFT (0U)
#define MSCM_CP2TYPE_PERSONALITY_WIDTH (32U)
#define MSCM_CP2TYPE_PERSONALITY(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2TYPE_PERSONALITY_SHIFT)) & \
        MSCM_CP2TYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CP2NUM - Core Processor 2 Number */
/*! @{ */

#define MSCM_CP2NUM_CPN_MASK  (0xFU)
#define MSCM_CP2NUM_CPN_SHIFT (0U)
#define MSCM_CP2NUM_CPN_WIDTH (4U)
#define MSCM_CP2NUM_CPN(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2NUM_CPN_SHIFT)) & MSCM_CP2NUM_CPN_MASK)
/*! @} */

/*! @name CP2REV - Core Processor 2 Revision */
/*! @{ */

#define MSCM_CP2REV_RYPZ_MASK  (0xFFU)
#define MSCM_CP2REV_RYPZ_SHIFT (0U)
#define MSCM_CP2REV_RYPZ_WIDTH (8U)
#define MSCM_CP2REV_RYPZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2REV_RYPZ_SHIFT)) & MSCM_CP2REV_RYPZ_MASK)
/*! @} */

/*! @name CP2CFG0 - Core Processor 2 Configuration 0 */
/*! @{ */

#define MSCM_CP2CFG0_DCWY_MASK  (0xFFU)
#define MSCM_CP2CFG0_DCWY_SHIFT (0U)
#define MSCM_CP2CFG0_DCWY_WIDTH (8U)
#define MSCM_CP2CFG0_DCWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG0_DCWY_SHIFT)) & MSCM_CP2CFG0_DCWY_MASK)

#define MSCM_CP2CFG0_DCSZ_MASK  (0xFF00U)
#define MSCM_CP2CFG0_DCSZ_SHIFT (8U)
#define MSCM_CP2CFG0_DCSZ_WIDTH (8U)
#define MSCM_CP2CFG0_DCSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG0_DCSZ_SHIFT)) & MSCM_CP2CFG0_DCSZ_MASK)

#define MSCM_CP2CFG0_ICWY_MASK  (0xFF0000U)
#define MSCM_CP2CFG0_ICWY_SHIFT (16U)
#define MSCM_CP2CFG0_ICWY_WIDTH (8U)
#define MSCM_CP2CFG0_ICWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG0_ICWY_SHIFT)) & MSCM_CP2CFG0_ICWY_MASK)

#define MSCM_CP2CFG0_ICSZ_MASK  (0xFF000000U)
#define MSCM_CP2CFG0_ICSZ_SHIFT (24U)
#define MSCM_CP2CFG0_ICSZ_WIDTH (8U)
#define MSCM_CP2CFG0_ICSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG0_ICSZ_SHIFT)) & MSCM_CP2CFG0_ICSZ_MASK)
/*! @} */

/*! @name CP2CFG1 - Core Processor 2 Configuration 1 */
/*! @{ */

#define MSCM_CP2CFG1_L2WY_MASK  (0xFF0000U)
#define MSCM_CP2CFG1_L2WY_SHIFT (16U)
#define MSCM_CP2CFG1_L2WY_WIDTH (8U)
#define MSCM_CP2CFG1_L2WY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG1_L2WY_SHIFT)) & MSCM_CP2CFG1_L2WY_MASK)

#define MSCM_CP2CFG1_L2SZ_MASK  (0xFF000000U)
#define MSCM_CP2CFG1_L2SZ_SHIFT (24U)
#define MSCM_CP2CFG1_L2SZ_WIDTH (8U)
#define MSCM_CP2CFG1_L2SZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG1_L2SZ_SHIFT)) & MSCM_CP2CFG1_L2SZ_MASK)
/*! @} */

/*! @name CP2CFG2 - Core Processor 2 Configuration 2 */
/*! @{ */

#define MSCM_CP2CFG2_ITCM_MASK  (0xFFFFU)
#define MSCM_CP2CFG2_ITCM_SHIFT (0U)
#define MSCM_CP2CFG2_ITCM_WIDTH (16U)
#define MSCM_CP2CFG2_ITCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG2_ITCM_SHIFT)) & MSCM_CP2CFG2_ITCM_MASK)

#define MSCM_CP2CFG2_TCM_MASK  (0xFFFF0000U)
#define MSCM_CP2CFG2_TCM_SHIFT (16U)
#define MSCM_CP2CFG2_TCM_WIDTH (16U)
#define MSCM_CP2CFG2_TCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG2_TCM_SHIFT)) & MSCM_CP2CFG2_TCM_MASK)
/*! @} */

/*! @name CP2CFG3 - Core Processor 2 Configuration 3 */
/*! @{ */

#define MSCM_CP2CFG3_FPU_MASK  (0x1U)
#define MSCM_CP2CFG3_FPU_SHIFT (0U)
#define MSCM_CP2CFG3_FPU_WIDTH (1U)
#define MSCM_CP2CFG3_FPU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG3_FPU_SHIFT)) & MSCM_CP2CFG3_FPU_MASK)

#define MSCM_CP2CFG3_SIMD_MASK  (0x2U)
#define MSCM_CP2CFG3_SIMD_SHIFT (1U)
#define MSCM_CP2CFG3_SIMD_WIDTH (1U)
#define MSCM_CP2CFG3_SIMD(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG3_SIMD_SHIFT)) & MSCM_CP2CFG3_SIMD_MASK)

#define MSCM_CP2CFG3_MMU_MASK  (0x4U)
#define MSCM_CP2CFG3_MMU_SHIFT (2U)
#define MSCM_CP2CFG3_MMU_WIDTH (1U)
#define MSCM_CP2CFG3_MMU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG3_MMU_SHIFT)) & MSCM_CP2CFG3_MMU_MASK)

#define MSCM_CP2CFG3_CMP_MASK  (0x8U)
#define MSCM_CP2CFG3_CMP_SHIFT (3U)
#define MSCM_CP2CFG3_CMP_WIDTH (1U)
#define MSCM_CP2CFG3_CMP(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG3_CMP_SHIFT)) & MSCM_CP2CFG3_CMP_MASK)

#define MSCM_CP2CFG3_CPY_MASK  (0x10U)
#define MSCM_CP2CFG3_CPY_SHIFT (4U)
#define MSCM_CP2CFG3_CPY_WIDTH (1U)
#define MSCM_CP2CFG3_CPY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP2CFG3_CPY_SHIFT)) & MSCM_CP2CFG3_CPY_MASK)
/*! @} */

/*! @name CP3TYPE - Core Processor 3 Type */
/*! @{ */

#define MSCM_CP3TYPE_PERSONALITY_MASK  (0xFFFFFFFFU)
#define MSCM_CP3TYPE_PERSONALITY_SHIFT (0U)
#define MSCM_CP3TYPE_PERSONALITY_WIDTH (32U)
#define MSCM_CP3TYPE_PERSONALITY(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3TYPE_PERSONALITY_SHIFT)) & \
        MSCM_CP3TYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CP3NUM - Core Processor 3 Number */
/*! @{ */

#define MSCM_CP3NUM_CPN_MASK  (0xFU)
#define MSCM_CP3NUM_CPN_SHIFT (0U)
#define MSCM_CP3NUM_CPN_WIDTH (4U)
#define MSCM_CP3NUM_CPN(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3NUM_CPN_SHIFT)) & MSCM_CP3NUM_CPN_MASK)
/*! @} */

/*! @name CP3REV - Core Processor 3 Revision */
/*! @{ */

#define MSCM_CP3REV_RYPZ_MASK  (0xFFU)
#define MSCM_CP3REV_RYPZ_SHIFT (0U)
#define MSCM_CP3REV_RYPZ_WIDTH (8U)
#define MSCM_CP3REV_RYPZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3REV_RYPZ_SHIFT)) & MSCM_CP3REV_RYPZ_MASK)
/*! @} */

/*! @name CP3CFG0 - Core Processor 3 Configuration 0 */
/*! @{ */

#define MSCM_CP3CFG0_DCWY_MASK  (0xFFU)
#define MSCM_CP3CFG0_DCWY_SHIFT (0U)
#define MSCM_CP3CFG0_DCWY_WIDTH (8U)
#define MSCM_CP3CFG0_DCWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG0_DCWY_SHIFT)) & MSCM_CP3CFG0_DCWY_MASK)

#define MSCM_CP3CFG0_DCSZ_MASK  (0xFF00U)
#define MSCM_CP3CFG0_DCSZ_SHIFT (8U)
#define MSCM_CP3CFG0_DCSZ_WIDTH (8U)
#define MSCM_CP3CFG0_DCSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG0_DCSZ_SHIFT)) & MSCM_CP3CFG0_DCSZ_MASK)

#define MSCM_CP3CFG0_ICWY_MASK  (0xFF0000U)
#define MSCM_CP3CFG0_ICWY_SHIFT (16U)
#define MSCM_CP3CFG0_ICWY_WIDTH (8U)
#define MSCM_CP3CFG0_ICWY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG0_ICWY_SHIFT)) & MSCM_CP3CFG0_ICWY_MASK)

#define MSCM_CP3CFG0_ICSZ_MASK  (0xFF000000U)
#define MSCM_CP3CFG0_ICSZ_SHIFT (24U)
#define MSCM_CP3CFG0_ICSZ_WIDTH (8U)
#define MSCM_CP3CFG0_ICSZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG0_ICSZ_SHIFT)) & MSCM_CP3CFG0_ICSZ_MASK)
/*! @} */

/*! @name CP3CFG1 - Core Processor 3 Configuration 1 */
/*! @{ */

#define MSCM_CP3CFG1_L2WY_MASK  (0xFF0000U)
#define MSCM_CP3CFG1_L2WY_SHIFT (16U)
#define MSCM_CP3CFG1_L2WY_WIDTH (8U)
#define MSCM_CP3CFG1_L2WY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG1_L2WY_SHIFT)) & MSCM_CP3CFG1_L2WY_MASK)

#define MSCM_CP3CFG1_L2SZ_MASK  (0xFF000000U)
#define MSCM_CP3CFG1_L2SZ_SHIFT (24U)
#define MSCM_CP3CFG1_L2SZ_WIDTH (8U)
#define MSCM_CP3CFG1_L2SZ(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG1_L2SZ_SHIFT)) & MSCM_CP3CFG1_L2SZ_MASK)
/*! @} */

/*! @name CP3CFG2 - Core Processor 3 Configuration 2 */
/*! @{ */

#define MSCM_CP3CFG2_ITCM_MASK  (0xFFFFU)
#define MSCM_CP3CFG2_ITCM_SHIFT (0U)
#define MSCM_CP3CFG2_ITCM_WIDTH (16U)
#define MSCM_CP3CFG2_ITCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG2_ITCM_SHIFT)) & MSCM_CP3CFG2_ITCM_MASK)

#define MSCM_CP3CFG2_TCM_MASK  (0xFFFF0000U)
#define MSCM_CP3CFG2_TCM_SHIFT (16U)
#define MSCM_CP3CFG2_TCM_WIDTH (16U)
#define MSCM_CP3CFG2_TCM(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG2_TCM_SHIFT)) & MSCM_CP3CFG2_TCM_MASK)
/*! @} */

/*! @name CP3CFG3 - Core Processor 3 Configuration 3 */
/*! @{ */

#define MSCM_CP3CFG3_FPU_MASK  (0x1U)
#define MSCM_CP3CFG3_FPU_SHIFT (0U)
#define MSCM_CP3CFG3_FPU_WIDTH (1U)
#define MSCM_CP3CFG3_FPU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG3_FPU_SHIFT)) & MSCM_CP3CFG3_FPU_MASK)

#define MSCM_CP3CFG3_SIMD_MASK  (0x2U)
#define MSCM_CP3CFG3_SIMD_SHIFT (1U)
#define MSCM_CP3CFG3_SIMD_WIDTH (1U)
#define MSCM_CP3CFG3_SIMD(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG3_SIMD_SHIFT)) & MSCM_CP3CFG3_SIMD_MASK)

#define MSCM_CP3CFG3_MMU_MASK  (0x4U)
#define MSCM_CP3CFG3_MMU_SHIFT (2U)
#define MSCM_CP3CFG3_MMU_WIDTH (1U)
#define MSCM_CP3CFG3_MMU(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG3_MMU_SHIFT)) & MSCM_CP3CFG3_MMU_MASK)

#define MSCM_CP3CFG3_CMP_MASK  (0x8U)
#define MSCM_CP3CFG3_CMP_SHIFT (3U)
#define MSCM_CP3CFG3_CMP_WIDTH (1U)
#define MSCM_CP3CFG3_CMP(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG3_CMP_SHIFT)) & MSCM_CP3CFG3_CMP_MASK)

#define MSCM_CP3CFG3_CPY_MASK  (0x10U)
#define MSCM_CP3CFG3_CPY_SHIFT (4U)
#define MSCM_CP3CFG3_CPY_WIDTH (1U)
#define MSCM_CP3CFG3_CPY(x) \
    (((uint32_t)(((uint32_t)(x)) << MSCM_CP3CFG3_CPY_SHIFT)) & MSCM_CP3CFG3_CPY_MASK)
/*! @} */

/*! @name IRSPRC - Interrupt Router Shared Peripheral Routing Control */
/*! @{ */

#define MSCM_IRSPRC_RTU0_GIC_MASK  (0x1U)
#define MSCM_IRSPRC_RTU0_GIC_SHIFT (0U)
#define MSCM_IRSPRC_RTU0_GIC_WIDTH (1U)
#define MSCM_IRSPRC_RTU0_GIC(x) \
    (((uint16_t)(((uint16_t)(x)) << MSCM_IRSPRC_RTU0_GIC_SHIFT)) & MSCM_IRSPRC_RTU0_GIC_MASK)

#define MSCM_IRSPRC_RTU1_GIC_MASK  (0x2U)
#define MSCM_IRSPRC_RTU1_GIC_SHIFT (1U)
#define MSCM_IRSPRC_RTU1_GIC_WIDTH (1U)
#define MSCM_IRSPRC_RTU1_GIC(x) \
    (((uint16_t)(((uint16_t)(x)) << MSCM_IRSPRC_RTU1_GIC_SHIFT)) & MSCM_IRSPRC_RTU1_GIC_MASK)

#define MSCM_IRSPRC_SMU_CORE_MASK  (0x4U)
#define MSCM_IRSPRC_SMU_CORE_SHIFT (2U)
#define MSCM_IRSPRC_SMU_CORE_WIDTH (1U)
#define MSCM_IRSPRC_SMU_CORE(x) \
    (((uint16_t)(((uint16_t)(x)) << MSCM_IRSPRC_SMU_CORE_SHIFT)) & MSCM_IRSPRC_SMU_CORE_MASK)

#define MSCM_IRSPRC_LOCK_MASK  (0x8000U)
#define MSCM_IRSPRC_LOCK_SHIFT (15U)
#define MSCM_IRSPRC_LOCK_WIDTH (1U)
#define MSCM_IRSPRC_LOCK(x) \
    (((uint16_t)(((uint16_t)(x)) << MSCM_IRSPRC_LOCK_SHIFT)) & MSCM_IRSPRC_LOCK_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MSCM_Register_Masks */

/*!
 * @}
 */ /* end of group MSCM_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_MSCM_H_) */
