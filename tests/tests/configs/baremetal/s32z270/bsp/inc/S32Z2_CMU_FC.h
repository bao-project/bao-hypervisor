/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_CMU_FC.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_CMU_FC
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
#if !defined(S32Z2_CMU_FC_H_) /* Check if memory map has not been already included */
#define S32Z2_CMU_FC_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- CMU_FC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMU_FC_Peripheral_Access_Layer CMU_FC Peripheral Access Layer
 * @{
 */

/** CMU_FC - Register Layout Typedef */
typedef struct {
    __IO uint32_t GCR;  /**< Global Configuration Register, offset: 0x0 */
    __IO uint32_t RCCR; /**< Reference Count Configuration Register, offset: 0x4 */
    __IO uint32_t HTCR; /**< High Threshold Configuration Register, offset: 0x8 */
    __IO uint32_t LTCR; /**< Low Threshold Configuration Register, offset: 0xC */
    __IO uint32_t SR;   /**< Status Register, offset: 0x10 */
    __IO uint32_t IER;  /**< Interrupt Enable Register, offset: 0x14 */
} CMU_FC_Type, *CMU_FC_MemMapPtr;

/** Number of instances of the CMU_FC module. */
#define CMU_FC_INSTANCE_COUNT  (27u)

/* CMU_FC - Peripheral instance base addresses */
/** Peripheral CE_CMU_FC_0 base address */
#define IP_CE_CMU_FC_0_BASE    (0x44854000u)
/** Peripheral CE_CMU_FC_0 base pointer */
#define IP_CE_CMU_FC_0         ((CMU_FC_Type*)IP_CE_CMU_FC_0_BASE)
/** Peripheral CE_CMU_FC_1 base address */
#define IP_CE_CMU_FC_1_BASE    (0x44A54000u)
/** Peripheral CE_CMU_FC_1 base pointer */
#define IP_CE_CMU_FC_1         ((CMU_FC_Type*)IP_CE_CMU_FC_1_BASE)
/** Peripheral CE_CMU_FC_2 base address */
#define IP_CE_CMU_FC_2_BASE    (0x44E10000u)
/** Peripheral CE_CMU_FC_2 base pointer */
#define IP_CE_CMU_FC_2         ((CMU_FC_Type*)IP_CE_CMU_FC_2_BASE)
/** Peripheral CMU_FC_0 base address */
#define IP_CMU_FC_0_BASE       (0x40040000u)
/** Peripheral CMU_FC_0 base pointer */
#define IP_CMU_FC_0            ((CMU_FC_Type*)IP_CMU_FC_0_BASE)
/** Peripheral CMU_FC_1 base address */
#define IP_CMU_FC_1_BASE       (0x40840000u)
/** Peripheral CMU_FC_1 base pointer */
#define IP_CMU_FC_1            ((CMU_FC_Type*)IP_CMU_FC_1_BASE)
/** Peripheral CMU_FC_2A base address */
#define IP_CMU_FC_2A_BASE      (0x41040000u)
/** Peripheral CMU_FC_2A base pointer */
#define IP_CMU_FC_2A           ((CMU_FC_Type*)IP_CMU_FC_2A_BASE)
/** Peripheral CMU_FC_2B base address */
#define IP_CMU_FC_2B_BASE      (0x410A0000u)
/** Peripheral CMU_FC_2B base pointer */
#define IP_CMU_FC_2B           ((CMU_FC_Type*)IP_CMU_FC_2B_BASE)
/** Peripheral CMU_FC_2C base address */
#define IP_CMU_FC_2C_BASE      (0x410B0000u)
/** Peripheral CMU_FC_2C base pointer */
#define IP_CMU_FC_2C           ((CMU_FC_Type*)IP_CMU_FC_2C_BASE)
/** Peripheral CMU_FC_2D base address */
#define IP_CMU_FC_2D_BASE      (0x410C0000u)
/** Peripheral CMU_FC_2D base pointer */
#define IP_CMU_FC_2D           ((CMU_FC_Type*)IP_CMU_FC_2D_BASE)
/** Peripheral CMU_FC_3 base address */
#define IP_CMU_FC_3_BASE       (0x41840000u)
/** Peripheral CMU_FC_3 base pointer */
#define IP_CMU_FC_3            ((CMU_FC_Type*)IP_CMU_FC_3_BASE)
/** Peripheral CMU_FC_4 base address */
#define IP_CMU_FC_4_BASE       (0x42040000u)
/** Peripheral CMU_FC_4 base pointer */
#define IP_CMU_FC_4            ((CMU_FC_Type*)IP_CMU_FC_4_BASE)
/** Peripheral CMU_FC_5 base address */
#define IP_CMU_FC_5_BASE       (0x42840000u)
/** Peripheral CMU_FC_5 base pointer */
#define IP_CMU_FC_5            ((CMU_FC_Type*)IP_CMU_FC_5_BASE)
/** Peripheral CMU_FC_6 base address */
#define IP_CMU_FC_6_BASE       (0x44040000u)
/** Peripheral CMU_FC_6 base pointer */
#define IP_CMU_FC_6            ((CMU_FC_Type*)IP_CMU_FC_6_BASE)
/** Peripheral CMU_FC_DEBUG_1 base address */
#define IP_CMU_FC_DEBUG_1_BASE (0x40050000u)
/** Peripheral CMU_FC_DEBUG_1 base pointer */
#define IP_CMU_FC_DEBUG_1      ((CMU_FC_Type*)IP_CMU_FC_DEBUG_1_BASE)
/** Peripheral CMU_FC_DEBUG_2 base address */
#define IP_CMU_FC_DEBUG_2_BASE (0x40850000u)
/** Peripheral CMU_FC_DEBUG_2 base pointer */
#define IP_CMU_FC_DEBUG_2      ((CMU_FC_Type*)IP_CMU_FC_DEBUG_2_BASE)
/** Peripheral AES__CMU_FC base address */
#define IP_AES__CMU_FC_BASE    (0x472B0000u)
/** Peripheral AES__CMU_FC base pointer */
#define IP_AES__CMU_FC         ((CMU_FC_Type*)IP_AES__CMU_FC_BASE)
/** Peripheral RTU0__CMU_FC_0 base address */
#define IP_RTU0__CMU_FC_0_BASE (0x76080000u)
/** Peripheral RTU0__CMU_FC_0 base pointer */
#define IP_RTU0__CMU_FC_0      ((CMU_FC_Type*)IP_RTU0__CMU_FC_0_BASE)
/** Peripheral RTU0__CMU_FC_1 base address */
#define IP_RTU0__CMU_FC_1_BASE (0x760A0000u)
/** Peripheral RTU0__CMU_FC_1 base pointer */
#define IP_RTU0__CMU_FC_1      ((CMU_FC_Type*)IP_RTU0__CMU_FC_1_BASE)
/** Peripheral RTU0__CMU_FC_2 base address */
#define IP_RTU0__CMU_FC_2_BASE (0x760B0000u)
/** Peripheral RTU0__CMU_FC_2 base pointer */
#define IP_RTU0__CMU_FC_2      ((CMU_FC_Type*)IP_RTU0__CMU_FC_2_BASE)
/** Peripheral RTU0__CMU_FC_3 base address */
#define IP_RTU0__CMU_FC_3_BASE (0x76160000u)
/** Peripheral RTU0__CMU_FC_3 base pointer */
#define IP_RTU0__CMU_FC_3      ((CMU_FC_Type*)IP_RTU0__CMU_FC_3_BASE)
/** Peripheral RTU0__CMU_FC_4 base address */
#define IP_RTU0__CMU_FC_4_BASE (0x76170000u)
/** Peripheral RTU0__CMU_FC_4 base pointer */
#define IP_RTU0__CMU_FC_4      ((CMU_FC_Type*)IP_RTU0__CMU_FC_4_BASE)
/** Peripheral RTU1__CMU_FC_0 base address */
#define IP_RTU1__CMU_FC_0_BASE (0x76880000u)
/** Peripheral RTU1__CMU_FC_0 base pointer */
#define IP_RTU1__CMU_FC_0      ((CMU_FC_Type*)IP_RTU1__CMU_FC_0_BASE)
/** Peripheral RTU1__CMU_FC_1 base address */
#define IP_RTU1__CMU_FC_1_BASE (0x768A0000u)
/** Peripheral RTU1__CMU_FC_1 base pointer */
#define IP_RTU1__CMU_FC_1      ((CMU_FC_Type*)IP_RTU1__CMU_FC_1_BASE)
/** Peripheral RTU1__CMU_FC_2 base address */
#define IP_RTU1__CMU_FC_2_BASE (0x768B0000u)
/** Peripheral RTU1__CMU_FC_2 base pointer */
#define IP_RTU1__CMU_FC_2      ((CMU_FC_Type*)IP_RTU1__CMU_FC_2_BASE)
/** Peripheral RTU1__CMU_FC_3 base address */
#define IP_RTU1__CMU_FC_3_BASE (0x76960000u)
/** Peripheral RTU1__CMU_FC_3 base pointer */
#define IP_RTU1__CMU_FC_3      ((CMU_FC_Type*)IP_RTU1__CMU_FC_3_BASE)
/** Peripheral RTU1__CMU_FC_4 base address */
#define IP_RTU1__CMU_FC_4_BASE (0x76970000u)
/** Peripheral RTU1__CMU_FC_4 base pointer */
#define IP_RTU1__CMU_FC_4      ((CMU_FC_Type*)IP_RTU1__CMU_FC_4_BASE)
/** Peripheral SMU__CMU_FC base address */
#define IP_SMU__CMU_FC_BASE    (0x45054000u)
/** Peripheral SMU__CMU_FC base pointer */
#define IP_SMU__CMU_FC         ((CMU_FC_Type*)IP_SMU__CMU_FC_BASE)
/** Array initializer of CMU_FC peripheral base addresses */
#define IP_CMU_FC_BASE_ADDRS                                                                       \
    { IP_CE_CMU_FC_0_BASE, IP_CE_CMU_FC_1_BASE, IP_CE_CMU_FC_2_BASE, IP_CMU_FC_0_BASE,             \
        IP_CMU_FC_1_BASE, IP_CMU_FC_2A_BASE, IP_CMU_FC_2B_BASE, IP_CMU_FC_2C_BASE,                 \
        IP_CMU_FC_2D_BASE, IP_CMU_FC_3_BASE, IP_CMU_FC_4_BASE, IP_CMU_FC_5_BASE, IP_CMU_FC_6_BASE, \
        IP_CMU_FC_DEBUG_1_BASE, IP_CMU_FC_DEBUG_2_BASE, IP_AES__CMU_FC_BASE,                       \
        IP_RTU0__CMU_FC_0_BASE, IP_RTU0__CMU_FC_1_BASE, IP_RTU0__CMU_FC_2_BASE,                    \
        IP_RTU0__CMU_FC_3_BASE, IP_RTU0__CMU_FC_4_BASE, IP_RTU1__CMU_FC_0_BASE,                    \
        IP_RTU1__CMU_FC_1_BASE, IP_RTU1__CMU_FC_2_BASE, IP_RTU1__CMU_FC_3_BASE,                    \
        IP_RTU1__CMU_FC_4_BASE, IP_SMU__CMU_FC_BASE }
/** Array initializer of CMU_FC peripheral base pointers */
#define IP_CMU_FC_BASE_PTRS                                                                   \
    { IP_CE_CMU_FC_0, IP_CE_CMU_FC_1, IP_CE_CMU_FC_2, IP_CMU_FC_0, IP_CMU_FC_1, IP_CMU_FC_2A, \
        IP_CMU_FC_2B, IP_CMU_FC_2C, IP_CMU_FC_2D, IP_CMU_FC_3, IP_CMU_FC_4, IP_CMU_FC_5,      \
        IP_CMU_FC_6, IP_CMU_FC_DEBUG_1, IP_CMU_FC_DEBUG_2, IP_AES__CMU_FC, IP_RTU0__CMU_FC_0, \
        IP_RTU0__CMU_FC_1, IP_RTU0__CMU_FC_2, IP_RTU0__CMU_FC_3, IP_RTU0__CMU_FC_4,           \
        IP_RTU1__CMU_FC_0, IP_RTU1__CMU_FC_1, IP_RTU1__CMU_FC_2, IP_RTU1__CMU_FC_3,           \
        IP_RTU1__CMU_FC_4, IP_SMU__CMU_FC }

/* ----------------------------------------------------------------------------
   -- CMU_FC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMU_FC_Register_Masks CMU_FC Register Masks
 * @{
 */

/*! @name GCR - Global Configuration Register */
/*! @{ */

#define CMU_FC_GCR_FCE_MASK  (0x1U)
#define CMU_FC_GCR_FCE_SHIFT (0U)
#define CMU_FC_GCR_FCE_WIDTH (1U)
#define CMU_FC_GCR_FCE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_GCR_FCE_SHIFT)) & CMU_FC_GCR_FCE_MASK)

#define CMU_FC_GCR_FI_SCE_MASK  (0x100U)
#define CMU_FC_GCR_FI_SCE_SHIFT (8U)
#define CMU_FC_GCR_FI_SCE_WIDTH (1U)
#define CMU_FC_GCR_FI_SCE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_GCR_FI_SCE_SHIFT)) & CMU_FC_GCR_FI_SCE_MASK)

#define CMU_FC_GCR_FI_START_MASK  (0x200U)
#define CMU_FC_GCR_FI_START_SHIFT (9U)
#define CMU_FC_GCR_FI_START_WIDTH (1U)
#define CMU_FC_GCR_FI_START(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_GCR_FI_START_SHIFT)) & CMU_FC_GCR_FI_START_MASK)

#define CMU_FC_GCR_FI_AUTO_EN_MASK  (0x400U)
#define CMU_FC_GCR_FI_AUTO_EN_SHIFT (10U)
#define CMU_FC_GCR_FI_AUTO_EN_WIDTH (1U)
#define CMU_FC_GCR_FI_AUTO_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_GCR_FI_AUTO_EN_SHIFT)) & CMU_FC_GCR_FI_AUTO_EN_MASK)

#define CMU_FC_GCR_FI_INT_MASK_MASK  (0x800U)
#define CMU_FC_GCR_FI_INT_MASK_SHIFT (11U)
#define CMU_FC_GCR_FI_INT_MASK_WIDTH (1U)
#define CMU_FC_GCR_FI_INT_MASK(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_GCR_FI_INT_MASK_SHIFT)) & CMU_FC_GCR_FI_INT_MASK_MASK)

#define CMU_FC_GCR_FI_AUTO_RCOUNT_MASK  (0xFFFF0000U)
#define CMU_FC_GCR_FI_AUTO_RCOUNT_SHIFT (16U)
#define CMU_FC_GCR_FI_AUTO_RCOUNT_WIDTH (16U)
#define CMU_FC_GCR_FI_AUTO_RCOUNT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_GCR_FI_AUTO_RCOUNT_SHIFT)) & \
        CMU_FC_GCR_FI_AUTO_RCOUNT_MASK)
/*! @} */

/*! @name RCCR - Reference Count Configuration Register */
/*! @{ */

#define CMU_FC_RCCR_REF_CNT_MASK  (0xFFFFU)
#define CMU_FC_RCCR_REF_CNT_SHIFT (0U)
#define CMU_FC_RCCR_REF_CNT_WIDTH (16U)
#define CMU_FC_RCCR_REF_CNT(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_RCCR_REF_CNT_SHIFT)) & CMU_FC_RCCR_REF_CNT_MASK)
/*! @} */

/*! @name HTCR - High Threshold Configuration Register */
/*! @{ */

#define CMU_FC_HTCR_HFREF_MASK  (0xFFFFFFU)
#define CMU_FC_HTCR_HFREF_SHIFT (0U)
#define CMU_FC_HTCR_HFREF_WIDTH (24U)
#define CMU_FC_HTCR_HFREF(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_HTCR_HFREF_SHIFT)) & CMU_FC_HTCR_HFREF_MASK)
/*! @} */

/*! @name LTCR - Low Threshold Configuration Register */
/*! @{ */

#define CMU_FC_LTCR_LFREF_MASK  (0xFFFFFFU)
#define CMU_FC_LTCR_LFREF_SHIFT (0U)
#define CMU_FC_LTCR_LFREF_WIDTH (24U)
#define CMU_FC_LTCR_LFREF(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_LTCR_LFREF_SHIFT)) & CMU_FC_LTCR_LFREF_MASK)
/*! @} */

/*! @name SR - Status Register */
/*! @{ */

#define CMU_FC_SR_FLL_MASK       (0x1U)
#define CMU_FC_SR_FLL_SHIFT      (0U)
#define CMU_FC_SR_FLL_WIDTH      (1U)
#define CMU_FC_SR_FLL(x)         (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_FLL_SHIFT)) & CMU_FC_SR_FLL_MASK)

#define CMU_FC_SR_FHH_MASK       (0x2U)
#define CMU_FC_SR_FHH_SHIFT      (1U)
#define CMU_FC_SR_FHH_WIDTH      (1U)
#define CMU_FC_SR_FHH(x)         (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_FHH_SHIFT)) & CMU_FC_SR_FHH_MASK)

#define CMU_FC_SR_RS_MASK        (0x10U)
#define CMU_FC_SR_RS_SHIFT       (4U)
#define CMU_FC_SR_RS_WIDTH       (1U)
#define CMU_FC_SR_RS(x)          (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_RS_SHIFT)) & CMU_FC_SR_RS_MASK)

#define CMU_FC_SR_AFI_FAIL_MASK  (0x10000U)
#define CMU_FC_SR_AFI_FAIL_SHIFT (16U)
#define CMU_FC_SR_AFI_FAIL_WIDTH (1U)
#define CMU_FC_SR_AFI_FAIL(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_AFI_FAIL_SHIFT)) & CMU_FC_SR_AFI_FAIL_MASK)

#define CMU_FC_SR_FI_PASS_MASK  (0x100000U)
#define CMU_FC_SR_FI_PASS_SHIFT (20U)
#define CMU_FC_SR_FI_PASS_WIDTH (1U)
#define CMU_FC_SR_FI_PASS(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_FI_PASS_SHIFT)) & CMU_FC_SR_FI_PASS_MASK)

#define CMU_FC_SR_FI_COMP_MASK  (0x800000U)
#define CMU_FC_SR_FI_COMP_SHIFT (23U)
#define CMU_FC_SR_FI_COMP_WIDTH (1U)
#define CMU_FC_SR_FI_COMP(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_FI_COMP_SHIFT)) & CMU_FC_SR_FI_COMP_MASK)
/*! @} */

/*! @name IER - Interrupt Enable Register */
/*! @{ */

#define CMU_FC_IER_FLLIE_MASK  (0x1U)
#define CMU_FC_IER_FLLIE_SHIFT (0U)
#define CMU_FC_IER_FLLIE_WIDTH (1U)
#define CMU_FC_IER_FLLIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FLLIE_SHIFT)) & CMU_FC_IER_FLLIE_MASK)

#define CMU_FC_IER_FHHIE_MASK  (0x2U)
#define CMU_FC_IER_FHHIE_SHIFT (1U)
#define CMU_FC_IER_FHHIE_WIDTH (1U)
#define CMU_FC_IER_FHHIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FHHIE_SHIFT)) & CMU_FC_IER_FHHIE_MASK)

#define CMU_FC_IER_FLLAIE_MASK  (0x4U)
#define CMU_FC_IER_FLLAIE_SHIFT (2U)
#define CMU_FC_IER_FLLAIE_WIDTH (1U)
#define CMU_FC_IER_FLLAIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FLLAIE_SHIFT)) & CMU_FC_IER_FLLAIE_MASK)

#define CMU_FC_IER_FHHAIE_MASK  (0x8U)
#define CMU_FC_IER_FHHAIE_SHIFT (3U)
#define CMU_FC_IER_FHHAIE_WIDTH (1U)
#define CMU_FC_IER_FHHAIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FHHAIE_SHIFT)) & CMU_FC_IER_FHHAIE_MASK)

#define CMU_FC_IER_AFIFIE_MASK  (0x10000U)
#define CMU_FC_IER_AFIFIE_SHIFT (16U)
#define CMU_FC_IER_AFIFIE_WIDTH (1U)
#define CMU_FC_IER_AFIFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_AFIFIE_SHIFT)) & CMU_FC_IER_AFIFIE_MASK)

#define CMU_FC_IER_AFIAFIE_MASK  (0x20000U)
#define CMU_FC_IER_AFIAFIE_SHIFT (17U)
#define CMU_FC_IER_AFIAFIE_WIDTH (1U)
#define CMU_FC_IER_AFIAFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_AFIAFIE_SHIFT)) & CMU_FC_IER_AFIAFIE_MASK)

#define CMU_FC_IER_FIPIE_MASK  (0x100000U)
#define CMU_FC_IER_FIPIE_SHIFT (20U)
#define CMU_FC_IER_FIPIE_WIDTH (1U)
#define CMU_FC_IER_FIPIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FIPIE_SHIFT)) & CMU_FC_IER_FIPIE_MASK)

#define CMU_FC_IER_FIAPIE_MASK  (0x200000U)
#define CMU_FC_IER_FIAPIE_SHIFT (21U)
#define CMU_FC_IER_FIAPIE_WIDTH (1U)
#define CMU_FC_IER_FIAPIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FIAPIE_SHIFT)) & CMU_FC_IER_FIAPIE_MASK)

#define CMU_FC_IER_FICIE_MASK  (0x800000U)
#define CMU_FC_IER_FICIE_SHIFT (23U)
#define CMU_FC_IER_FICIE_WIDTH (1U)
#define CMU_FC_IER_FICIE(x) \
    (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FICIE_SHIFT)) & CMU_FC_IER_FICIE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group CMU_FC_Register_Masks */

/*!
 * @}
 */ /* end of group CMU_FC_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_CMU_FC_H_) */
