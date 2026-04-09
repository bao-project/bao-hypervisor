/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_RTU_MC_CGM.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_RTU_MC_CGM
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
#if !defined(S32Z2_RTU_MC_CGM_H_) /* Check if memory map has not been already included */
#define S32Z2_RTU_MC_CGM_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- RTU_MC_CGM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTU_MC_CGM_Peripheral_Access_Layer RTU_MC_CGM Peripheral Access Layer
 * @{
 */

/** RTU_MC_CGM - Register Layout Typedef */
typedef struct {
    __IO uint32_t PCFS_SDUR;         /**< PCFS Step Duration, offset: 0x0 */
    uint8_t RESERVED_0[108];
    __IO uint32_t PCFS_DIVC10;       /**< PCFS Divider Change 10 Register, offset: 0x70 */
    __IO uint32_t PCFS_DIVE10;       /**< PCFS Divider End 10 Register, offset: 0x74 */
    __IO uint32_t PCFS_DIVS10;       /**< PCFS Divider Start 10 Register, offset: 0x78 */
    __IO uint32_t PCFS_DIVC11;       /**< PCFS Divider Change 11 Register, offset: 0x7C */
    __IO uint32_t PCFS_DIVE11;       /**< PCFS Divider End 11 Register, offset: 0x80 */
    __IO uint32_t PCFS_DIVS11;       /**< PCFS Divider Start 11 Register, offset: 0x84 */
    __IO uint32_t PCFS_DIVC12;       /**< PCFS Divider Change 12 Register, offset: 0x88 */
    __IO uint32_t PCFS_DIVE12;       /**< PCFS Divider End 12 Register, offset: 0x8C */
    __IO uint32_t PCFS_DIVS12;       /**< PCFS Divider Start 12 Register, offset: 0x90 */
    uint8_t RESERVED_1[620];
    __IO uint32_t MUX_0_CSC;         /**< Clock Mux 0 Select Control Register, offset: 0x300 */
    __I uint32_t MUX_0_CSS;          /**< Clock Mux 0 Select Status Register, offset: 0x304 */
    __IO uint32_t MUX_0_DC_0;        /**< Clock Mux 0 Divider 0 Control Register, offset: 0x308 */
    uint8_t RESERVED_2[48];
    __I uint32_t MUX_0_DIV_UPD_STAT; /**< Clock Mux 0 Divider Update Status Register, offset: 0x33C
                                      */
    __IO uint32_t MUX_1_CSC;         /**< Clock Mux 1 Select Control Register, offset: 0x340 */
    __I uint32_t MUX_1_CSS;          /**< Clock Mux 1 Select Status Register, offset: 0x344 */
    __IO uint32_t MUX_1_DC_0;        /**< Clock Mux 1 Divider 0 Control Register, offset: 0x348 */
    uint8_t RESERVED_3[48];
    __I uint32_t MUX_1_DIV_UPD_STAT; /**< Clock Mux 1 Divider Update Status Register, offset: 0x37C
                                      */
} RTU_MC_CGM_Type, *RTU_MC_CGM_MemMapPtr;

/** Number of instances of the RTU_MC_CGM module. */
#define RTU_MC_CGM_INSTANCE_COUNT       (2u)

/* RTU_MC_CGM - Peripheral instance base addresses */
/** Peripheral RTU0__MC_CGM base address */
#define IP_RTU0__MC_CGM_BASE            (0x762C0000u)
/** Peripheral RTU0__MC_CGM base pointer */
#define IP_RTU0__MC_CGM                 ((RTU_MC_CGM_Type*)IP_RTU0__MC_CGM_BASE)
/** Peripheral RTU1__MC_CGM base address */
#define IP_RTU1__MC_CGM_BASE            (0x76AC0000u)
/** Peripheral RTU1__MC_CGM base pointer */
#define IP_RTU1__MC_CGM                 ((RTU_MC_CGM_Type*)IP_RTU1__MC_CGM_BASE)
/** Array initializer of RTU_MC_CGM peripheral base addresses */
#define IP_RTU_MC_CGM_BASE_ADDRS        { IP_RTU0__MC_CGM_BASE, IP_RTU1__MC_CGM_BASE }
/** Array initializer of RTU_MC_CGM peripheral base pointers */
#define IP_RTU_MC_CGM_BASE_PTRS         { IP_RTU0__MC_CGM, IP_RTU1__MC_CGM }

/* ----------------------------------------------------------------------------
   -- RTU_MC_CGM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTU_MC_CGM_Register_Masks RTU_MC_CGM Register Masks
 * @{
 */

/*! @name PCFS_SDUR - PCFS Step Duration */
/*! @{ */

#define RTU_MC_CGM_PCFS_SDUR_SDUR_MASK  (0xFFFFU)
#define RTU_MC_CGM_PCFS_SDUR_SDUR_SHIFT (0U)
#define RTU_MC_CGM_PCFS_SDUR_SDUR_WIDTH (16U)
#define RTU_MC_CGM_PCFS_SDUR_SDUR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_SDUR_SDUR_SHIFT)) & \
        RTU_MC_CGM_PCFS_SDUR_SDUR_MASK)
/*! @} */

/*! @name PCFS_DIVC10 - PCFS Divider Change 10 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVC10_RATE_MASK  (0xFFU)
#define RTU_MC_CGM_PCFS_DIVC10_RATE_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVC10_RATE_WIDTH (8U)
#define RTU_MC_CGM_PCFS_DIVC10_RATE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVC10_RATE_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVC10_RATE_MASK)

#define RTU_MC_CGM_PCFS_DIVC10_INIT_MASK  (0xFFFF0000U)
#define RTU_MC_CGM_PCFS_DIVC10_INIT_SHIFT (16U)
#define RTU_MC_CGM_PCFS_DIVC10_INIT_WIDTH (16U)
#define RTU_MC_CGM_PCFS_DIVC10_INIT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVC10_INIT_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVC10_INIT_MASK)
/*! @} */

/*! @name PCFS_DIVE10 - PCFS Divider End 10 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVE10_DIVE_MASK  (0xFFFFFU)
#define RTU_MC_CGM_PCFS_DIVE10_DIVE_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVE10_DIVE_WIDTH (20U)
#define RTU_MC_CGM_PCFS_DIVE10_DIVE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVE10_DIVE_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVE10_DIVE_MASK)
/*! @} */

/*! @name PCFS_DIVS10 - PCFS Divider Start 10 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVS10_DIVS_MASK  (0xFFFFFU)
#define RTU_MC_CGM_PCFS_DIVS10_DIVS_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVS10_DIVS_WIDTH (20U)
#define RTU_MC_CGM_PCFS_DIVS10_DIVS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVS10_DIVS_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVS10_DIVS_MASK)
/*! @} */

/*! @name PCFS_DIVC11 - PCFS Divider Change 11 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVC11_RATE_MASK  (0xFFU)
#define RTU_MC_CGM_PCFS_DIVC11_RATE_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVC11_RATE_WIDTH (8U)
#define RTU_MC_CGM_PCFS_DIVC11_RATE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVC11_RATE_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVC11_RATE_MASK)

#define RTU_MC_CGM_PCFS_DIVC11_INIT_MASK  (0xFFFF0000U)
#define RTU_MC_CGM_PCFS_DIVC11_INIT_SHIFT (16U)
#define RTU_MC_CGM_PCFS_DIVC11_INIT_WIDTH (16U)
#define RTU_MC_CGM_PCFS_DIVC11_INIT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVC11_INIT_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVC11_INIT_MASK)
/*! @} */

/*! @name PCFS_DIVE11 - PCFS Divider End 11 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVE11_DIVE_MASK  (0xFFFFFU)
#define RTU_MC_CGM_PCFS_DIVE11_DIVE_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVE11_DIVE_WIDTH (20U)
#define RTU_MC_CGM_PCFS_DIVE11_DIVE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVE11_DIVE_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVE11_DIVE_MASK)
/*! @} */

/*! @name PCFS_DIVS11 - PCFS Divider Start 11 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVS11_DIVS_MASK  (0xFFFFFU)
#define RTU_MC_CGM_PCFS_DIVS11_DIVS_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVS11_DIVS_WIDTH (20U)
#define RTU_MC_CGM_PCFS_DIVS11_DIVS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVS11_DIVS_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVS11_DIVS_MASK)
/*! @} */

/*! @name PCFS_DIVC12 - PCFS Divider Change 12 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVC12_RATE_MASK  (0xFFU)
#define RTU_MC_CGM_PCFS_DIVC12_RATE_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVC12_RATE_WIDTH (8U)
#define RTU_MC_CGM_PCFS_DIVC12_RATE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVC12_RATE_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVC12_RATE_MASK)

#define RTU_MC_CGM_PCFS_DIVC12_INIT_MASK  (0xFFFF0000U)
#define RTU_MC_CGM_PCFS_DIVC12_INIT_SHIFT (16U)
#define RTU_MC_CGM_PCFS_DIVC12_INIT_WIDTH (16U)
#define RTU_MC_CGM_PCFS_DIVC12_INIT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVC12_INIT_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVC12_INIT_MASK)
/*! @} */

/*! @name PCFS_DIVE12 - PCFS Divider End 12 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVE12_DIVE_MASK  (0xFFFFFU)
#define RTU_MC_CGM_PCFS_DIVE12_DIVE_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVE12_DIVE_WIDTH (20U)
#define RTU_MC_CGM_PCFS_DIVE12_DIVE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVE12_DIVE_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVE12_DIVE_MASK)
/*! @} */

/*! @name PCFS_DIVS12 - PCFS Divider Start 12 Register */
/*! @{ */

#define RTU_MC_CGM_PCFS_DIVS12_DIVS_MASK  (0xFFFFFU)
#define RTU_MC_CGM_PCFS_DIVS12_DIVS_SHIFT (0U)
#define RTU_MC_CGM_PCFS_DIVS12_DIVS_WIDTH (20U)
#define RTU_MC_CGM_PCFS_DIVS12_DIVS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_PCFS_DIVS12_DIVS_SHIFT)) & \
        RTU_MC_CGM_PCFS_DIVS12_DIVS_MASK)
/*! @} */

/*! @name MUX_0_CSC - Clock Mux 0 Select Control Register */
/*! @{ */

#define RTU_MC_CGM_MUX_0_CSC_RAMPUP_MASK  (0x1U)
#define RTU_MC_CGM_MUX_0_CSC_RAMPUP_SHIFT (0U)
#define RTU_MC_CGM_MUX_0_CSC_RAMPUP_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSC_RAMPUP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSC_RAMPUP_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSC_RAMPUP_MASK)

#define RTU_MC_CGM_MUX_0_CSC_RAMPDOWN_MASK  (0x2U)
#define RTU_MC_CGM_MUX_0_CSC_RAMPDOWN_SHIFT (1U)
#define RTU_MC_CGM_MUX_0_CSC_RAMPDOWN_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSC_RAMPDOWN(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSC_RAMPDOWN_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSC_RAMPDOWN_MASK)

#define RTU_MC_CGM_MUX_0_CSC_CLK_SW_MASK  (0x4U)
#define RTU_MC_CGM_MUX_0_CSC_CLK_SW_SHIFT (2U)
#define RTU_MC_CGM_MUX_0_CSC_CLK_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSC_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSC_CLK_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSC_CLK_SW_MASK)

#define RTU_MC_CGM_MUX_0_CSC_SAFE_SW_MASK  (0x8U)
#define RTU_MC_CGM_MUX_0_CSC_SAFE_SW_SHIFT (3U)
#define RTU_MC_CGM_MUX_0_CSC_SAFE_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSC_SAFE_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSC_SAFE_SW_MASK)

#define RTU_MC_CGM_MUX_0_CSC_SELCTL_MASK  (0xF000000U)
#define RTU_MC_CGM_MUX_0_CSC_SELCTL_SHIFT (24U)
#define RTU_MC_CGM_MUX_0_CSC_SELCTL_WIDTH (4U)
#define RTU_MC_CGM_MUX_0_CSC_SELCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSC_SELCTL_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_0_CSS - Clock Mux 0 Select Status Register */
/*! @{ */

#define RTU_MC_CGM_MUX_0_CSS_RAMPUP_MASK  (0x1U)
#define RTU_MC_CGM_MUX_0_CSS_RAMPUP_SHIFT (0U)
#define RTU_MC_CGM_MUX_0_CSS_RAMPUP_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSS_RAMPUP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSS_RAMPUP_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSS_RAMPUP_MASK)

#define RTU_MC_CGM_MUX_0_CSS_RAMPDOWN_MASK  (0x2U)
#define RTU_MC_CGM_MUX_0_CSS_RAMPDOWN_SHIFT (1U)
#define RTU_MC_CGM_MUX_0_CSS_RAMPDOWN_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSS_RAMPDOWN(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSS_RAMPDOWN_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSS_RAMPDOWN_MASK)

#define RTU_MC_CGM_MUX_0_CSS_CLK_SW_MASK  (0x4U)
#define RTU_MC_CGM_MUX_0_CSS_CLK_SW_SHIFT (2U)
#define RTU_MC_CGM_MUX_0_CSS_CLK_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSS_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSS_CLK_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSS_CLK_SW_MASK)

#define RTU_MC_CGM_MUX_0_CSS_SAFE_SW_MASK  (0x8U)
#define RTU_MC_CGM_MUX_0_CSS_SAFE_SW_SHIFT (3U)
#define RTU_MC_CGM_MUX_0_CSS_SAFE_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSS_SAFE_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSS_SAFE_SW_MASK)

#define RTU_MC_CGM_MUX_0_CSS_SWIP_MASK  (0x10000U)
#define RTU_MC_CGM_MUX_0_CSS_SWIP_SHIFT (16U)
#define RTU_MC_CGM_MUX_0_CSS_SWIP_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_CSS_SWIP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSS_SWIP_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSS_SWIP_MASK)

#define RTU_MC_CGM_MUX_0_CSS_SWTRG_MASK  (0xE0000U)
#define RTU_MC_CGM_MUX_0_CSS_SWTRG_SHIFT (17U)
#define RTU_MC_CGM_MUX_0_CSS_SWTRG_WIDTH (3U)
#define RTU_MC_CGM_MUX_0_CSS_SWTRG(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSS_SWTRG_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSS_SWTRG_MASK)

#define RTU_MC_CGM_MUX_0_CSS_SELSTAT_MASK  (0xF000000U)
#define RTU_MC_CGM_MUX_0_CSS_SELSTAT_SHIFT (24U)
#define RTU_MC_CGM_MUX_0_CSS_SELSTAT_WIDTH (4U)
#define RTU_MC_CGM_MUX_0_CSS_SELSTAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)) & \
        RTU_MC_CGM_MUX_0_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_0_DC_0 - Clock Mux 0 Divider 0 Control Register */
/*! @{ */

#define RTU_MC_CGM_MUX_0_DC_0_DIV_MASK  (0xFF0000U)
#define RTU_MC_CGM_MUX_0_DC_0_DIV_SHIFT (16U)
#define RTU_MC_CGM_MUX_0_DC_0_DIV_WIDTH (8U)
#define RTU_MC_CGM_MUX_0_DC_0_DIV(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_DC_0_DIV_SHIFT)) & \
        RTU_MC_CGM_MUX_0_DC_0_DIV_MASK)

#define RTU_MC_CGM_MUX_0_DC_0_DE_MASK  (0x80000000U)
#define RTU_MC_CGM_MUX_0_DC_0_DE_SHIFT (31U)
#define RTU_MC_CGM_MUX_0_DC_0_DE_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_DC_0_DE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_DC_0_DE_SHIFT)) & \
        RTU_MC_CGM_MUX_0_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_0_DIV_UPD_STAT - Clock Mux 0 Divider Update Status Register */
/*! @{ */

#define RTU_MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define RTU_MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define RTU_MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define RTU_MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        RTU_MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_1_CSC - Clock Mux 1 Select Control Register */
/*! @{ */

#define RTU_MC_CGM_MUX_1_CSC_CLK_SW_MASK  (0x4U)
#define RTU_MC_CGM_MUX_1_CSC_CLK_SW_SHIFT (2U)
#define RTU_MC_CGM_MUX_1_CSC_CLK_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_1_CSC_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSC_CLK_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSC_CLK_SW_MASK)

#define RTU_MC_CGM_MUX_1_CSC_SAFE_SW_MASK  (0x8U)
#define RTU_MC_CGM_MUX_1_CSC_SAFE_SW_SHIFT (3U)
#define RTU_MC_CGM_MUX_1_CSC_SAFE_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_1_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSC_SAFE_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSC_SAFE_SW_MASK)

#define RTU_MC_CGM_MUX_1_CSC_SELCTL_MASK  (0xF000000U)
#define RTU_MC_CGM_MUX_1_CSC_SELCTL_SHIFT (24U)
#define RTU_MC_CGM_MUX_1_CSC_SELCTL_WIDTH (4U)
#define RTU_MC_CGM_MUX_1_CSC_SELCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSC_SELCTL_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_1_CSS - Clock Mux 1 Select Status Register */
/*! @{ */

#define RTU_MC_CGM_MUX_1_CSS_CLK_SW_MASK  (0x4U)
#define RTU_MC_CGM_MUX_1_CSS_CLK_SW_SHIFT (2U)
#define RTU_MC_CGM_MUX_1_CSS_CLK_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_1_CSS_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSS_CLK_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSS_CLK_SW_MASK)

#define RTU_MC_CGM_MUX_1_CSS_SAFE_SW_MASK  (0x8U)
#define RTU_MC_CGM_MUX_1_CSS_SAFE_SW_SHIFT (3U)
#define RTU_MC_CGM_MUX_1_CSS_SAFE_SW_WIDTH (1U)
#define RTU_MC_CGM_MUX_1_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSS_SAFE_SW_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSS_SAFE_SW_MASK)

#define RTU_MC_CGM_MUX_1_CSS_SWIP_MASK  (0x10000U)
#define RTU_MC_CGM_MUX_1_CSS_SWIP_SHIFT (16U)
#define RTU_MC_CGM_MUX_1_CSS_SWIP_WIDTH (1U)
#define RTU_MC_CGM_MUX_1_CSS_SWIP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSS_SWIP_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSS_SWIP_MASK)

#define RTU_MC_CGM_MUX_1_CSS_SWTRG_MASK  (0xE0000U)
#define RTU_MC_CGM_MUX_1_CSS_SWTRG_SHIFT (17U)
#define RTU_MC_CGM_MUX_1_CSS_SWTRG_WIDTH (3U)
#define RTU_MC_CGM_MUX_1_CSS_SWTRG(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSS_SWTRG_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSS_SWTRG_MASK)

#define RTU_MC_CGM_MUX_1_CSS_SELSTAT_MASK  (0xF000000U)
#define RTU_MC_CGM_MUX_1_CSS_SELSTAT_SHIFT (24U)
#define RTU_MC_CGM_MUX_1_CSS_SELSTAT_WIDTH (4U)
#define RTU_MC_CGM_MUX_1_CSS_SELSTAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)) & \
        RTU_MC_CGM_MUX_1_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_1_DC_0 - Clock Mux 1 Divider 0 Control Register */
/*! @{ */

#define RTU_MC_CGM_MUX_1_DC_0_DIV_MASK  (0xFF0000U)
#define RTU_MC_CGM_MUX_1_DC_0_DIV_SHIFT (16U)
#define RTU_MC_CGM_MUX_1_DC_0_DIV_WIDTH (8U)
#define RTU_MC_CGM_MUX_1_DC_0_DIV(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_DC_0_DIV_SHIFT)) & \
        RTU_MC_CGM_MUX_1_DC_0_DIV_MASK)

#define RTU_MC_CGM_MUX_1_DC_0_DE_MASK  (0x80000000U)
#define RTU_MC_CGM_MUX_1_DC_0_DE_SHIFT (31U)
#define RTU_MC_CGM_MUX_1_DC_0_DE_WIDTH (1U)
#define RTU_MC_CGM_MUX_1_DC_0_DE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_DC_0_DE_SHIFT)) & \
        RTU_MC_CGM_MUX_1_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_1_DIV_UPD_STAT - Clock Mux 1 Divider Update Status Register */
/*! @{ */

#define RTU_MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define RTU_MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define RTU_MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define RTU_MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << RTU_MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        RTU_MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group RTU_MC_CGM_Register_Masks */

/*!
 * @}
 */ /* end of group RTU_MC_CGM_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_RTU_MC_CGM_H_) */
