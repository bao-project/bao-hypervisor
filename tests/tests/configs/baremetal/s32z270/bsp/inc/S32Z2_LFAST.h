/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_LFAST.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_LFAST
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
#if !defined(S32Z2_LFAST_H_) /* Check if memory map has not been already included */
#define S32Z2_LFAST_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- LFAST Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LFAST_Peripheral_Access_Layer LFAST Peripheral Access Layer
 * @{
 */

/** LFAST - Size of Registers Arrays */
#define LFAST_UNSTDR_COUNT 9u
#define LFAST_UNSRDR_COUNT 9u
#define LFAST_GPR_COUNT    1u

/** LFAST - Register Layout Typedef */
typedef struct {
    __IO uint32_t MCR;                        /**< LFAST Mode Configuration, offset: 0x0 */
    __IO uint32_t SCR;                        /**< LFAST Speed Control, offset: 0x4 */
    __IO uint32_t COCR;                       /**< LFAST Correlator Control, offset: 0x8 */
    __IO uint32_t TMCR;                       /**< LFAST Test Mode Control, offset: 0xC */
    __IO uint32_t ALCR;                       /**< LFAST Auto Loopback Control, offset: 0x10 */
    __IO uint32_t RCDCR;                      /**< LFAST Rate Change Delay Control, offset: 0x14 */
    uint8_t RESERVED_0[4];
    __IO uint32_t ICR;                        /**< LFAST ICLC Control, offset: 0x1C */
    __IO uint32_t PICR;                       /**< LFAST Ping Control, offset: 0x20 */
    uint8_t RESERVED_1[8];
    __IO uint32_t RFCR;                       /**< LFAST Rx FIFO CTS Control, offset: 0x2C */
    __IO uint32_t TIER;                       /**< LFAST Tx Interrupt Enable, offset: 0x30 */
    __IO uint32_t RIER;                       /**< LFAST Rx Interrupt Enable, offset: 0x34 */
    __IO uint32_t RIIER;                      /**< LFAST Rx ICLC Interrupt Enable, offset: 0x38 */
    __IO uint32_t PLLCR;                      /**< LFAST PLL Control, offset: 0x3C */
    uint8_t RESERVED_2[4];
    __IO uint32_t UNSTCR;                     /**< LFAST Unsolicited Tx Control, offset: 0x44 */
    __IO uint32_t UNSTDR[LFAST_UNSTDR_COUNT]; /**< LFAST Unsolicited Tx Data Registers, array
                                                 offset: 0x48, array step: 0x4 */
    uint8_t RESERVED_3[20];
    __I uint32_t GSR;                         /**< LFAST Global Status, offset: 0x80 */
    __I uint32_t PISR;                        /**< LFAST Ping Status, offset: 0x84 */
    uint8_t RESERVED_4[12];
    __I uint32_t DFSR;                        /**< LFAST Data Frame Status, offset: 0x94 */
    __IO uint32_t TISR;                       /**< LFAST Tx Interrupt Status, offset: 0x98 */
    __IO uint32_t RISR;                       /**< LFAST Rx Interrupt Status, offset: 0x9C */
    __IO uint32_t RIISR;                      /**< LFAST Rx ICLC Interrupt Status, offset: 0xA0 */
    __I uint32_t PLLLSR;                      /**< LFAST PLL and LVDS Status, offset: 0xA4 */
    __IO uint32_t UNSRSR;                     /**< LFAST Unsolicited Rx Status, offset: 0xA8 */
    __I uint32_t UNSRDR[LFAST_UNSRDR_COUNT];  /**< LFAST Unsolicited Rx Data, array offset: 0xAC,
                                                 array step: 0x4 */
    uint8_t RESERVED_5[4];
    __IO uint32_t GPR[LFAST_GPR_COUNT]; /**< General Purpose registers, array offset: 0xD4, array
                                           step: 0x4 */
} LFAST_Type, *LFAST_MemMapPtr;

/** Number of instances of the LFAST module. */
#define LFAST_INSTANCE_COUNT   (2u)

/* LFAST - Peripheral instance base addresses */
/** Peripheral LFAST_0 base address */
#define IP_LFAST_0_BASE        (0x40A10000u)
/** Peripheral LFAST_0 base pointer */
#define IP_LFAST_0             ((LFAST_Type*)IP_LFAST_0_BASE)
/** Peripheral LFAST_1 base address */
#define IP_LFAST_1_BASE        (0x40A30000u)
/** Peripheral LFAST_1 base pointer */
#define IP_LFAST_1             ((LFAST_Type*)IP_LFAST_1_BASE)
/** Array initializer of LFAST peripheral base addresses */
#define IP_LFAST_BASE_ADDRS    { IP_LFAST_0_BASE, IP_LFAST_1_BASE }
/** Array initializer of LFAST peripheral base pointers */
#define IP_LFAST_BASE_PTRS     { IP_LFAST_0, IP_LFAST_1 }

/* ----------------------------------------------------------------------------
   -- LFAST Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LFAST_Register_Masks LFAST Register Masks
 * @{
 */

/*! @name MCR - LFAST Mode Configuration */
/*! @{ */

#define LFAST_MCR_DATAEN_MASK  (0x1U)
#define LFAST_MCR_DATAEN_SHIFT (0U)
#define LFAST_MCR_DATAEN_WIDTH (1U)
#define LFAST_MCR_DATAEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_DATAEN_SHIFT)) & LFAST_MCR_DATAEN_MASK)

#define LFAST_MCR_DRFRST_MASK  (0x2U)
#define LFAST_MCR_DRFRST_SHIFT (1U)
#define LFAST_MCR_DRFRST_WIDTH (1U)
#define LFAST_MCR_DRFRST(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_DRFRST_SHIFT)) & LFAST_MCR_DRFRST_MASK)

#define LFAST_MCR_CTSEN_MASK  (0x8U)
#define LFAST_MCR_CTSEN_SHIFT (3U)
#define LFAST_MCR_CTSEN_WIDTH (1U)
#define LFAST_MCR_CTSEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_CTSEN_SHIFT)) & LFAST_MCR_CTSEN_MASK)

#define LFAST_MCR_TXARBD_MASK  (0x10U)
#define LFAST_MCR_TXARBD_SHIFT (4U)
#define LFAST_MCR_TXARBD_WIDTH (1U)
#define LFAST_MCR_TXARBD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_TXARBD_SHIFT)) & LFAST_MCR_TXARBD_MASK)

#define LFAST_MCR_TXEN_MASK  (0x2000U)
#define LFAST_MCR_TXEN_SHIFT (13U)
#define LFAST_MCR_TXEN_WIDTH (1U)
#define LFAST_MCR_TXEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_TXEN_SHIFT)) & LFAST_MCR_TXEN_MASK)

#define LFAST_MCR_RXEN_MASK  (0x4000U)
#define LFAST_MCR_RXEN_SHIFT (14U)
#define LFAST_MCR_RXEN_WIDTH (1U)
#define LFAST_MCR_RXEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_RXEN_SHIFT)) & LFAST_MCR_RXEN_MASK)

#define LFAST_MCR_DRFEN_MASK  (0x8000U)
#define LFAST_MCR_DRFEN_SHIFT (15U)
#define LFAST_MCR_DRFEN_WIDTH (1U)
#define LFAST_MCR_DRFEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_DRFEN_SHIFT)) & LFAST_MCR_DRFEN_MASK)

#define LFAST_MCR_LSSEL_MASK  (0x10000U)
#define LFAST_MCR_LSSEL_SHIFT (16U)
#define LFAST_MCR_LSSEL_WIDTH (1U)
#define LFAST_MCR_LSSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_LSSEL_SHIFT)) & LFAST_MCR_LSSEL_MASK)

#define LFAST_MCR_IPGDBG_MASK  (0x1000000U)
#define LFAST_MCR_IPGDBG_SHIFT (24U)
#define LFAST_MCR_IPGDBG_WIDTH (1U)
#define LFAST_MCR_IPGDBG(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_IPGDBG_SHIFT)) & LFAST_MCR_IPGDBG_MASK)

#define LFAST_MCR_MSEN_MASK  (0x80000000U)
#define LFAST_MCR_MSEN_SHIFT (31U)
#define LFAST_MCR_MSEN_WIDTH (1U)
#define LFAST_MCR_MSEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_MCR_MSEN_SHIFT)) & LFAST_MCR_MSEN_MASK)
/*! @} */

/*! @name SCR - LFAST Speed Control */
/*! @{ */

#define LFAST_SCR_TDR_MASK   (0x1U)
#define LFAST_SCR_TDR_SHIFT  (0U)
#define LFAST_SCR_TDR_WIDTH  (1U)
#define LFAST_SCR_TDR(x)     (((uint32_t)(((uint32_t)(x)) << LFAST_SCR_TDR_SHIFT)) & LFAST_SCR_TDR_MASK)

#define LFAST_SCR_RDR_MASK   (0x100U)
#define LFAST_SCR_RDR_SHIFT  (8U)
#define LFAST_SCR_RDR_WIDTH  (1U)
#define LFAST_SCR_RDR(x)     (((uint32_t)(((uint32_t)(x)) << LFAST_SCR_RDR_SHIFT)) & LFAST_SCR_RDR_MASK)

#define LFAST_SCR_DRMD_MASK  (0x10000U)
#define LFAST_SCR_DRMD_SHIFT (16U)
#define LFAST_SCR_DRMD_WIDTH (1U)
#define LFAST_SCR_DRMD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_SCR_DRMD_SHIFT)) & LFAST_SCR_DRMD_MASK)
/*! @} */

/*! @name COCR - LFAST Correlator Control */
/*! @{ */

#define LFAST_COCR_PHSSEL_MASK  (0x1U)
#define LFAST_COCR_PHSSEL_SHIFT (0U)
#define LFAST_COCR_PHSSEL_WIDTH (1U)
#define LFAST_COCR_PHSSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_COCR_PHSSEL_SHIFT)) & LFAST_COCR_PHSSEL_MASK)

#define LFAST_COCR_CORRTH_MASK  (0xEU)
#define LFAST_COCR_CORRTH_SHIFT (1U)
#define LFAST_COCR_CORRTH_WIDTH (3U)
#define LFAST_COCR_CORRTH(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_COCR_CORRTH_SHIFT)) & LFAST_COCR_CORRTH_MASK)

#define LFAST_COCR_SMPSEL_MASK  (0xFF000000U)
#define LFAST_COCR_SMPSEL_SHIFT (24U)
#define LFAST_COCR_SMPSEL_WIDTH (8U)
#define LFAST_COCR_SMPSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_COCR_SMPSEL_SHIFT)) & LFAST_COCR_SMPSEL_MASK)
/*! @} */

/*! @name TMCR - LFAST Test Mode Control */
/*! @{ */

#define LFAST_TMCR_LPFRMTH_MASK  (0xFFFFU)
#define LFAST_TMCR_LPFRMTH_SHIFT (0U)
#define LFAST_TMCR_LPFRMTH_WIDTH (16U)
#define LFAST_TMCR_LPFRMTH(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TMCR_LPFRMTH_SHIFT)) & LFAST_TMCR_LPFRMTH_MASK)

#define LFAST_TMCR_LPMOD_MASK  (0x70000U)
#define LFAST_TMCR_LPMOD_SHIFT (16U)
#define LFAST_TMCR_LPMOD_WIDTH (3U)
#define LFAST_TMCR_LPMOD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TMCR_LPMOD_SHIFT)) & LFAST_TMCR_LPMOD_MASK)

#define LFAST_TMCR_LPON_MASK  (0x1000000U)
#define LFAST_TMCR_LPON_SHIFT (24U)
#define LFAST_TMCR_LPON_WIDTH (1U)
#define LFAST_TMCR_LPON(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TMCR_LPON_SHIFT)) & LFAST_TMCR_LPON_MASK)

#define LFAST_TMCR_CLKTST_MASK  (0x2000000U)
#define LFAST_TMCR_CLKTST_SHIFT (25U)
#define LFAST_TMCR_CLKTST_WIDTH (1U)
#define LFAST_TMCR_CLKTST(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TMCR_CLKTST_SHIFT)) & LFAST_TMCR_CLKTST_MASK)
/*! @} */

/*! @name ALCR - LFAST Auto Loopback Control */
/*! @{ */

#define LFAST_ALCR_LPFMCNT_MASK  (0xFFFFU)
#define LFAST_ALCR_LPFMCNT_SHIFT (0U)
#define LFAST_ALCR_LPFMCNT_WIDTH (16U)
#define LFAST_ALCR_LPFMCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_ALCR_LPFMCNT_SHIFT)) & LFAST_ALCR_LPFMCNT_MASK)

#define LFAST_ALCR_LPCNTEN_MASK  (0x10000U)
#define LFAST_ALCR_LPCNTEN_SHIFT (16U)
#define LFAST_ALCR_LPCNTEN_WIDTH (1U)
#define LFAST_ALCR_LPCNTEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_ALCR_LPCNTEN_SHIFT)) & LFAST_ALCR_LPCNTEN_MASK)
/*! @} */

/*! @name RCDCR - LFAST Rate Change Delay Control */
/*! @{ */

#define LFAST_RCDCR_DRCNT_MASK  (0xF0000U)
#define LFAST_RCDCR_DRCNT_SHIFT (16U)
#define LFAST_RCDCR_DRCNT_WIDTH (4U)
#define LFAST_RCDCR_DRCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RCDCR_DRCNT_SHIFT)) & LFAST_RCDCR_DRCNT_MASK)
/*! @} */

/*! @name ICR - LFAST ICLC Control */
/*! @{ */

#define LFAST_ICR_ICLCPLD_MASK  (0xFFU)
#define LFAST_ICR_ICLCPLD_SHIFT (0U)
#define LFAST_ICR_ICLCPLD_WIDTH (8U)
#define LFAST_ICR_ICLCPLD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_ICR_ICLCPLD_SHIFT)) & LFAST_ICR_ICLCPLD_MASK)

#define LFAST_ICR_SNDICLC_MASK  (0x10000U)
#define LFAST_ICR_SNDICLC_SHIFT (16U)
#define LFAST_ICR_SNDICLC_WIDTH (1U)
#define LFAST_ICR_SNDICLC(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_ICR_SNDICLC_SHIFT)) & LFAST_ICR_SNDICLC_MASK)

#define LFAST_ICR_ICLCSEQ_MASK  (0x20000U)
#define LFAST_ICR_ICLCSEQ_SHIFT (17U)
#define LFAST_ICR_ICLCSEQ_WIDTH (1U)
#define LFAST_ICR_ICLCSEQ(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_ICR_ICLCSEQ_SHIFT)) & LFAST_ICR_ICLCSEQ_MASK)
/*! @} */

/*! @name PICR - LFAST Ping Control */
/*! @{ */

#define LFAST_PICR_PNGPYLD_MASK  (0xFFU)
#define LFAST_PICR_PNGPYLD_SHIFT (0U)
#define LFAST_PICR_PNGPYLD_WIDTH (8U)
#define LFAST_PICR_PNGPYLD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PICR_PNGPYLD_SHIFT)) & LFAST_PICR_PNGPYLD_MASK)

#define LFAST_PICR_PNGAUTO_MASK  (0x8000U)
#define LFAST_PICR_PNGAUTO_SHIFT (15U)
#define LFAST_PICR_PNGAUTO_WIDTH (1U)
#define LFAST_PICR_PNGAUTO(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PICR_PNGAUTO_SHIFT)) & LFAST_PICR_PNGAUTO_MASK)

#define LFAST_PICR_PNGREQ_MASK  (0x10000U)
#define LFAST_PICR_PNGREQ_SHIFT (16U)
#define LFAST_PICR_PNGREQ_WIDTH (1U)
#define LFAST_PICR_PNGREQ(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PICR_PNGREQ_SHIFT)) & LFAST_PICR_PNGREQ_MASK)
/*! @} */

/*! @name RFCR - LFAST Rx FIFO CTS Control */
/*! @{ */

#define LFAST_RFCR_RCTSMN_MASK  (0x3FU)
#define LFAST_RFCR_RCTSMN_SHIFT (0U)
#define LFAST_RFCR_RCTSMN_WIDTH (6U)
#define LFAST_RFCR_RCTSMN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RFCR_RCTSMN_SHIFT)) & LFAST_RFCR_RCTSMN_MASK)

#define LFAST_RFCR_RCTSMX_MASK  (0x3F0000U)
#define LFAST_RFCR_RCTSMX_SHIFT (16U)
#define LFAST_RFCR_RCTSMX_WIDTH (6U)
#define LFAST_RFCR_RCTSMX(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RFCR_RCTSMX_SHIFT)) & LFAST_RFCR_RCTSMX_MASK)
/*! @} */

/*! @name TIER - LFAST Tx Interrupt Enable */
/*! @{ */

#define LFAST_TIER_TXDTIE_MASK  (0x1U)
#define LFAST_TIER_TXDTIE_SHIFT (0U)
#define LFAST_TIER_TXDTIE_WIDTH (1U)
#define LFAST_TIER_TXDTIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TIER_TXDTIE_SHIFT)) & LFAST_TIER_TXDTIE_MASK)

#define LFAST_TIER_TXICLCIE_MASK  (0x2U)
#define LFAST_TIER_TXICLCIE_SHIFT (1U)
#define LFAST_TIER_TXICLCIE_WIDTH (1U)
#define LFAST_TIER_TXICLCIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TIER_TXICLCIE_SHIFT)) & LFAST_TIER_TXICLCIE_MASK)

#define LFAST_TIER_TXUNSIE_MASK  (0x4U)
#define LFAST_TIER_TXUNSIE_SHIFT (2U)
#define LFAST_TIER_TXUNSIE_WIDTH (1U)
#define LFAST_TIER_TXUNSIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TIER_TXUNSIE_SHIFT)) & LFAST_TIER_TXUNSIE_MASK)

#define LFAST_TIER_TXPNGIE_MASK  (0x10U)
#define LFAST_TIER_TXPNGIE_SHIFT (4U)
#define LFAST_TIER_TXPNGIE_WIDTH (1U)
#define LFAST_TIER_TXPNGIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TIER_TXPNGIE_SHIFT)) & LFAST_TIER_TXPNGIE_MASK)

#define LFAST_TIER_TXOVIE_MASK  (0x10000U)
#define LFAST_TIER_TXOVIE_SHIFT (16U)
#define LFAST_TIER_TXOVIE_WIDTH (1U)
#define LFAST_TIER_TXOVIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TIER_TXOVIE_SHIFT)) & LFAST_TIER_TXOVIE_MASK)

#define LFAST_TIER_TXIIE_MASK  (0x20000U)
#define LFAST_TIER_TXIIE_SHIFT (17U)
#define LFAST_TIER_TXIIE_WIDTH (1U)
#define LFAST_TIER_TXIIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TIER_TXIIE_SHIFT)) & LFAST_TIER_TXIIE_MASK)
/*! @} */

/*! @name RIER - LFAST Rx Interrupt Enable */
/*! @{ */

#define LFAST_RIER_RXUNSIE_MASK  (0x2U)
#define LFAST_RIER_RXUNSIE_SHIFT (1U)
#define LFAST_RIER_RXUNSIE_WIDTH (1U)
#define LFAST_RIER_RXUNSIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXUNSIE_SHIFT)) & LFAST_RIER_RXUNSIE_MASK)

#define LFAST_RIER_RXDIE_MASK  (0x4U)
#define LFAST_RIER_RXDIE_SHIFT (2U)
#define LFAST_RIER_RXDIE_WIDTH (1U)
#define LFAST_RIER_RXDIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXDIE_SHIFT)) & LFAST_RIER_RXDIE_MASK)

#define LFAST_RIER_RXCTSIE_MASK  (0x8U)
#define LFAST_RIER_RXCTSIE_SHIFT (3U)
#define LFAST_RIER_RXCTSIE_WIDTH (1U)
#define LFAST_RIER_RXCTSIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXCTSIE_SHIFT)) & LFAST_RIER_RXCTSIE_MASK)

#define LFAST_RIER_RXLCEIE_MASK  (0x10000U)
#define LFAST_RIER_RXLCEIE_SHIFT (16U)
#define LFAST_RIER_RXLCEIE_WIDTH (1U)
#define LFAST_RIER_RXLCEIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXLCEIE_SHIFT)) & LFAST_RIER_RXLCEIE_MASK)

#define LFAST_RIER_RXICIE_MASK  (0x20000U)
#define LFAST_RIER_RXICIE_SHIFT (17U)
#define LFAST_RIER_RXICIE_WIDTH (1U)
#define LFAST_RIER_RXICIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXICIE_SHIFT)) & LFAST_RIER_RXICIE_MASK)

#define LFAST_RIER_RXSZIE_MASK  (0x40000U)
#define LFAST_RIER_RXSZIE_SHIFT (18U)
#define LFAST_RIER_RXSZIE_WIDTH (1U)
#define LFAST_RIER_RXSZIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXSZIE_SHIFT)) & LFAST_RIER_RXSZIE_MASK)

#define LFAST_RIER_RXOFIE_MASK  (0x80000U)
#define LFAST_RIER_RXOFIE_SHIFT (19U)
#define LFAST_RIER_RXOFIE_WIDTH (1U)
#define LFAST_RIER_RXOFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXOFIE_SHIFT)) & LFAST_RIER_RXOFIE_MASK)

#define LFAST_RIER_RXUFIE_MASK  (0x100000U)
#define LFAST_RIER_RXUFIE_SHIFT (20U)
#define LFAST_RIER_RXUFIE_WIDTH (1U)
#define LFAST_RIER_RXUFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXUFIE_SHIFT)) & LFAST_RIER_RXUFIE_MASK)

#define LFAST_RIER_RXMXIE_MASK  (0x200000U)
#define LFAST_RIER_RXMXIE_SHIFT (21U)
#define LFAST_RIER_RXMXIE_WIDTH (1U)
#define LFAST_RIER_RXMXIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXMXIE_SHIFT)) & LFAST_RIER_RXMXIE_MASK)

#define LFAST_RIER_RXMNIE_MASK  (0x400000U)
#define LFAST_RIER_RXMNIE_SHIFT (22U)
#define LFAST_RIER_RXMNIE_WIDTH (1U)
#define LFAST_RIER_RXMNIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXMNIE_SHIFT)) & LFAST_RIER_RXMNIE_MASK)

#define LFAST_RIER_RXUOIE_MASK  (0x800000U)
#define LFAST_RIER_RXUOIE_SHIFT (23U)
#define LFAST_RIER_RXUOIE_WIDTH (1U)
#define LFAST_RIER_RXUOIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIER_RXUOIE_SHIFT)) & LFAST_RIER_RXUOIE_MASK)
/*! @} */

/*! @name RIIER - LFAST Rx ICLC Interrupt Enable */
/*! @{ */

#define LFAST_RIIER_ICPONIE_MASK  (0x1U)
#define LFAST_RIIER_ICPONIE_SHIFT (0U)
#define LFAST_RIIER_ICPONIE_WIDTH (1U)
#define LFAST_RIIER_ICPONIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICPONIE_SHIFT)) & LFAST_RIIER_ICPONIE_MASK)

#define LFAST_RIIER_ICPOFIE_MASK  (0x2U)
#define LFAST_RIIER_ICPOFIE_SHIFT (1U)
#define LFAST_RIIER_ICPOFIE_WIDTH (1U)
#define LFAST_RIIER_ICPOFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICPOFIE_SHIFT)) & LFAST_RIIER_ICPOFIE_MASK)

#define LFAST_RIIER_ICTSIE_MASK  (0x4U)
#define LFAST_RIIER_ICTSIE_SHIFT (2U)
#define LFAST_RIIER_ICTSIE_WIDTH (1U)
#define LFAST_RIIER_ICTSIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICTSIE_SHIFT)) & LFAST_RIIER_ICTSIE_MASK)

#define LFAST_RIIER_ICTFIE_MASK  (0x8U)
#define LFAST_RIIER_ICTFIE_SHIFT (3U)
#define LFAST_RIIER_ICTFIE_WIDTH (1U)
#define LFAST_RIIER_ICTFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICTFIE_SHIFT)) & LFAST_RIIER_ICTFIE_MASK)

#define LFAST_RIIER_ICRSIE_MASK  (0x10U)
#define LFAST_RIIER_ICRSIE_SHIFT (4U)
#define LFAST_RIIER_ICRSIE_WIDTH (1U)
#define LFAST_RIIER_ICRSIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICRSIE_SHIFT)) & LFAST_RIIER_ICRSIE_MASK)

#define LFAST_RIIER_ICRFIE_MASK  (0x20U)
#define LFAST_RIIER_ICRFIE_SHIFT (5U)
#define LFAST_RIIER_ICRFIE_WIDTH (1U)
#define LFAST_RIIER_ICRFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICRFIE_SHIFT)) & LFAST_RIIER_ICRFIE_MASK)

#define LFAST_RIIER_ICTEIE_MASK  (0x40U)
#define LFAST_RIIER_ICTEIE_SHIFT (6U)
#define LFAST_RIIER_ICTEIE_WIDTH (1U)
#define LFAST_RIIER_ICTEIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICTEIE_SHIFT)) & LFAST_RIIER_ICTEIE_MASK)

#define LFAST_RIIER_ICTDIE_MASK  (0x80U)
#define LFAST_RIIER_ICTDIE_SHIFT (7U)
#define LFAST_RIIER_ICTDIE_WIDTH (1U)
#define LFAST_RIIER_ICTDIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICTDIE_SHIFT)) & LFAST_RIIER_ICTDIE_MASK)

#define LFAST_RIIER_ICCTIE_MASK  (0x100U)
#define LFAST_RIIER_ICCTIE_SHIFT (8U)
#define LFAST_RIIER_ICCTIE_WIDTH (1U)
#define LFAST_RIIER_ICCTIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICCTIE_SHIFT)) & LFAST_RIIER_ICCTIE_MASK)

#define LFAST_RIIER_ICLPIE_MASK  (0x200U)
#define LFAST_RIIER_ICLPIE_SHIFT (9U)
#define LFAST_RIIER_ICLPIE_WIDTH (1U)
#define LFAST_RIIER_ICLPIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICLPIE_SHIFT)) & LFAST_RIIER_ICLPIE_MASK)

#define LFAST_RIIER_ICTOIE_MASK  (0x400U)
#define LFAST_RIIER_ICTOIE_SHIFT (10U)
#define LFAST_RIIER_ICTOIE_WIDTH (1U)
#define LFAST_RIIER_ICTOIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICTOIE_SHIFT)) & LFAST_RIIER_ICTOIE_MASK)

#define LFAST_RIIER_ICPRIE_MASK  (0x800U)
#define LFAST_RIIER_ICPRIE_SHIFT (11U)
#define LFAST_RIIER_ICPRIE_WIDTH (1U)
#define LFAST_RIIER_ICPRIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICPRIE_SHIFT)) & LFAST_RIIER_ICPRIE_MASK)

#define LFAST_RIIER_ICPSIE_MASK  (0x1000U)
#define LFAST_RIIER_ICPSIE_SHIFT (12U)
#define LFAST_RIIER_ICPSIE_WIDTH (1U)
#define LFAST_RIIER_ICPSIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICPSIE_SHIFT)) & LFAST_RIIER_ICPSIE_MASK)

#define LFAST_RIIER_ICPFIE_MASK  (0x2000U)
#define LFAST_RIIER_ICPFIE_SHIFT (13U)
#define LFAST_RIIER_ICPFIE_WIDTH (1U)
#define LFAST_RIIER_ICPFIE(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIIER_ICPFIE_SHIFT)) & LFAST_RIIER_ICPFIE_MASK)
/*! @} */

/*! @name PLLCR - LFAST PLL Control */
/*! @{ */

#define LFAST_PLLCR_PREDIV_MASK  (0x3U)
#define LFAST_PLLCR_PREDIV_SHIFT (0U)
#define LFAST_PLLCR_PREDIV_WIDTH (2U)
#define LFAST_PLLCR_PREDIV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_PREDIV_SHIFT)) & LFAST_PLLCR_PREDIV_MASK)

#define LFAST_PLLCR_FBDIV_MASK  (0xFCU)
#define LFAST_PLLCR_FBDIV_SHIFT (2U)
#define LFAST_PLLCR_FBDIV_WIDTH (6U)
#define LFAST_PLLCR_FBDIV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_FBDIV_SHIFT)) & LFAST_PLLCR_FBDIV_MASK)

#define LFAST_PLLCR_FDIVEN_MASK  (0x100U)
#define LFAST_PLLCR_FDIVEN_SHIFT (8U)
#define LFAST_PLLCR_FDIVEN_WIDTH (1U)
#define LFAST_PLLCR_FDIVEN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_FDIVEN_SHIFT)) & LFAST_PLLCR_FDIVEN_MASK)

#define LFAST_PLLCR_PLCKCW_MASK  (0x600U)
#define LFAST_PLLCR_PLCKCW_SHIFT (9U)
#define LFAST_PLLCR_PLCKCW_WIDTH (2U)
#define LFAST_PLLCR_PLCKCW(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_PLCKCW_SHIFT)) & LFAST_PLLCR_PLCKCW_MASK)

#define LFAST_PLLCR_LPCFG_MASK  (0x6000U)
#define LFAST_PLLCR_LPCFG_SHIFT (13U)
#define LFAST_PLLCR_LPCFG_WIDTH (2U)
#define LFAST_PLLCR_LPCFG(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_LPCFG_SHIFT)) & LFAST_PLLCR_LPCFG_MASK)

#define LFAST_PLLCR_REFINV_MASK  (0x8000U)
#define LFAST_PLLCR_REFINV_SHIFT (15U)
#define LFAST_PLLCR_REFINV_WIDTH (1U)
#define LFAST_PLLCR_REFINV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_REFINV_SHIFT)) & LFAST_PLLCR_REFINV_MASK)

#define LFAST_PLLCR_SWPON_MASK  (0x10000U)
#define LFAST_PLLCR_SWPON_SHIFT (16U)
#define LFAST_PLLCR_SWPON_WIDTH (1U)
#define LFAST_PLLCR_SWPON(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_SWPON_SHIFT)) & LFAST_PLLCR_SWPON_MASK)

#define LFAST_PLLCR_SWPOFF_MASK  (0x20000U)
#define LFAST_PLLCR_SWPOFF_SHIFT (17U)
#define LFAST_PLLCR_SWPOFF_WIDTH (1U)
#define LFAST_PLLCR_SWPOFF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLCR_SWPOFF_SHIFT)) & LFAST_PLLCR_SWPOFF_MASK)
/*! @} */

/*! @name UNSTCR - LFAST Unsolicited Tx Control */
/*! @{ */

#define LFAST_UNSTCR_UNSHDR_MASK  (0x7FU)
#define LFAST_UNSTCR_UNSHDR_SHIFT (0U)
#define LFAST_UNSTCR_UNSHDR_WIDTH (7U)
#define LFAST_UNSTCR_UNSHDR(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_UNSTCR_UNSHDR_SHIFT)) & LFAST_UNSTCR_UNSHDR_MASK)

#define LFAST_UNSTCR_USNDRQ_MASK  (0x10000U)
#define LFAST_UNSTCR_USNDRQ_SHIFT (16U)
#define LFAST_UNSTCR_USNDRQ_WIDTH (1U)
#define LFAST_UNSTCR_USNDRQ(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_UNSTCR_USNDRQ_SHIFT)) & LFAST_UNSTCR_USNDRQ_MASK)
/*! @} */

/*! @name UNSTDR - LFAST Unsolicited Tx Data Registers */
/*! @{ */

#define LFAST_UNSTDR_UNTXD_MASK  (0xFFFFFFFFU)
#define LFAST_UNSTDR_UNTXD_SHIFT (0U)
#define LFAST_UNSTDR_UNTXD_WIDTH (32U)
#define LFAST_UNSTDR_UNTXD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_UNSTDR_UNTXD_SHIFT)) & LFAST_UNSTDR_UNTXD_MASK)
/*! @} */

/*! @name GSR - LFAST Global Status */
/*! @{ */

#define LFAST_GSR_LPCSDV_MASK  (0x1U)
#define LFAST_GSR_LPCSDV_SHIFT (0U)
#define LFAST_GSR_LPCSDV_WIDTH (1U)
#define LFAST_GSR_LPCSDV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_LPCSDV_SHIFT)) & LFAST_GSR_LPCSDV_MASK)

#define LFAST_GSR_LPCHDV_MASK  (0x2U)
#define LFAST_GSR_LPCHDV_SHIFT (1U)
#define LFAST_GSR_LPCHDV_WIDTH (1U)
#define LFAST_GSR_LPCHDV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_LPCHDV_SHIFT)) & LFAST_GSR_LPCHDV_MASK)

#define LFAST_GSR_LPCPDV_MASK  (0x4U)
#define LFAST_GSR_LPCPDV_SHIFT (2U)
#define LFAST_GSR_LPCPDV_WIDTH (1U)
#define LFAST_GSR_LPCPDV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_LPCPDV_SHIFT)) & LFAST_GSR_LPCPDV_MASK)

#define LFAST_GSR_LPFPDV_MASK  (0x8U)
#define LFAST_GSR_LPFPDV_SHIFT (3U)
#define LFAST_GSR_LPFPDV_WIDTH (1U)
#define LFAST_GSR_LPFPDV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_LPFPDV_SHIFT)) & LFAST_GSR_LPFPDV_MASK)

#define LFAST_GSR_LPTXDN_MASK  (0x10U)
#define LFAST_GSR_LPTXDN_SHIFT (4U)
#define LFAST_GSR_LPTXDN_WIDTH (1U)
#define LFAST_GSR_LPTXDN(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_LPTXDN_SHIFT)) & LFAST_GSR_LPTXDN_MASK)

#define LFAST_GSR_DRSM_MASK  (0x10000U)
#define LFAST_GSR_DRSM_SHIFT (16U)
#define LFAST_GSR_DRSM_WIDTH (1U)
#define LFAST_GSR_DRSM(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_DRSM_SHIFT)) & LFAST_GSR_DRSM_MASK)

#define LFAST_GSR_LDSM_MASK  (0x20000U)
#define LFAST_GSR_LDSM_SHIFT (17U)
#define LFAST_GSR_LDSM_WIDTH (1U)
#define LFAST_GSR_LDSM(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_LDSM_SHIFT)) & LFAST_GSR_LDSM_MASK)

#define LFAST_GSR_LRMD_MASK  (0x40000U)
#define LFAST_GSR_LRMD_SHIFT (18U)
#define LFAST_GSR_LRMD_WIDTH (1U)
#define LFAST_GSR_LRMD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_LRMD_SHIFT)) & LFAST_GSR_LRMD_MASK)

#define LFAST_GSR_DUALMD_MASK  (0x80000000U)
#define LFAST_GSR_DUALMD_SHIFT (31U)
#define LFAST_GSR_DUALMD_WIDTH (1U)
#define LFAST_GSR_DUALMD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_GSR_DUALMD_SHIFT)) & LFAST_GSR_DUALMD_MASK)
/*! @} */

/*! @name PISR - LFAST Ping Status */
/*! @{ */

#define LFAST_PISR_RXPNGD_MASK  (0xFFU)
#define LFAST_PISR_RXPNGD_SHIFT (0U)
#define LFAST_PISR_RXPNGD_WIDTH (8U)
#define LFAST_PISR_RXPNGD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PISR_RXPNGD_SHIFT)) & LFAST_PISR_RXPNGD_MASK)
/*! @} */

/*! @name DFSR - LFAST Data Frame Status */
/*! @{ */

#define LFAST_DFSR_TXFCNT_MASK  (0x7U)
#define LFAST_DFSR_TXFCNT_SHIFT (0U)
#define LFAST_DFSR_TXFCNT_WIDTH (3U)
#define LFAST_DFSR_TXFCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_DFSR_TXFCNT_SHIFT)) & LFAST_DFSR_TXFCNT_MASK)

#define LFAST_DFSR_TXDCNT_MASK  (0x3F00U)
#define LFAST_DFSR_TXDCNT_SHIFT (8U)
#define LFAST_DFSR_TXDCNT_WIDTH (6U)
#define LFAST_DFSR_TXDCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_DFSR_TXDCNT_SHIFT)) & LFAST_DFSR_TXDCNT_MASK)

#define LFAST_DFSR_RXFCNT_MASK  (0x70000U)
#define LFAST_DFSR_RXFCNT_SHIFT (16U)
#define LFAST_DFSR_RXFCNT_WIDTH (3U)
#define LFAST_DFSR_RXFCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_DFSR_RXFCNT_SHIFT)) & LFAST_DFSR_RXFCNT_MASK)

#define LFAST_DFSR_RXDCNT_MASK  (0x3F000000U)
#define LFAST_DFSR_RXDCNT_SHIFT (24U)
#define LFAST_DFSR_RXDCNT_WIDTH (6U)
#define LFAST_DFSR_RXDCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_DFSR_RXDCNT_SHIFT)) & LFAST_DFSR_RXDCNT_MASK)
/*! @} */

/*! @name TISR - LFAST Tx Interrupt Status */
/*! @{ */

#define LFAST_TISR_TXDTF_MASK  (0x1U)
#define LFAST_TISR_TXDTF_SHIFT (0U)
#define LFAST_TISR_TXDTF_WIDTH (1U)
#define LFAST_TISR_TXDTF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TISR_TXDTF_SHIFT)) & LFAST_TISR_TXDTF_MASK)

#define LFAST_TISR_TXICLCF_MASK  (0x2U)
#define LFAST_TISR_TXICLCF_SHIFT (1U)
#define LFAST_TISR_TXICLCF_WIDTH (1U)
#define LFAST_TISR_TXICLCF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TISR_TXICLCF_SHIFT)) & LFAST_TISR_TXICLCF_MASK)

#define LFAST_TISR_TXUNSF_MASK  (0x4U)
#define LFAST_TISR_TXUNSF_SHIFT (2U)
#define LFAST_TISR_TXUNSF_WIDTH (1U)
#define LFAST_TISR_TXUNSF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TISR_TXUNSF_SHIFT)) & LFAST_TISR_TXUNSF_MASK)

#define LFAST_TISR_TXPNGF_MASK  (0x10U)
#define LFAST_TISR_TXPNGF_SHIFT (4U)
#define LFAST_TISR_TXPNGF_WIDTH (1U)
#define LFAST_TISR_TXPNGF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TISR_TXPNGF_SHIFT)) & LFAST_TISR_TXPNGF_MASK)

#define LFAST_TISR_TXOVF_MASK  (0x10000U)
#define LFAST_TISR_TXOVF_SHIFT (16U)
#define LFAST_TISR_TXOVF_WIDTH (1U)
#define LFAST_TISR_TXOVF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TISR_TXOVF_SHIFT)) & LFAST_TISR_TXOVF_MASK)

#define LFAST_TISR_TXIEF_MASK  (0x20000U)
#define LFAST_TISR_TXIEF_SHIFT (17U)
#define LFAST_TISR_TXIEF_WIDTH (1U)
#define LFAST_TISR_TXIEF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_TISR_TXIEF_SHIFT)) & LFAST_TISR_TXIEF_MASK)
/*! @} */

/*! @name RISR - LFAST Rx Interrupt Status */
/*! @{ */

#define LFAST_RISR_RXUNSF_MASK  (0x2U)
#define LFAST_RISR_RXUNSF_SHIFT (1U)
#define LFAST_RISR_RXUNSF_WIDTH (1U)
#define LFAST_RISR_RXUNSF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXUNSF_SHIFT)) & LFAST_RISR_RXUNSF_MASK)

#define LFAST_RISR_RXDF_MASK  (0x4U)
#define LFAST_RISR_RXDF_SHIFT (2U)
#define LFAST_RISR_RXDF_WIDTH (1U)
#define LFAST_RISR_RXDF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXDF_SHIFT)) & LFAST_RISR_RXDF_MASK)

#define LFAST_RISR_RXCTSF_MASK  (0x8U)
#define LFAST_RISR_RXCTSF_SHIFT (3U)
#define LFAST_RISR_RXCTSF_WIDTH (1U)
#define LFAST_RISR_RXCTSF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXCTSF_SHIFT)) & LFAST_RISR_RXCTSF_MASK)

#define LFAST_RISR_RXLCEF_MASK  (0x10000U)
#define LFAST_RISR_RXLCEF_SHIFT (16U)
#define LFAST_RISR_RXLCEF_WIDTH (1U)
#define LFAST_RISR_RXLCEF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXLCEF_SHIFT)) & LFAST_RISR_RXLCEF_MASK)

#define LFAST_RISR_RXICF_MASK  (0x20000U)
#define LFAST_RISR_RXICF_SHIFT (17U)
#define LFAST_RISR_RXICF_WIDTH (1U)
#define LFAST_RISR_RXICF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXICF_SHIFT)) & LFAST_RISR_RXICF_MASK)

#define LFAST_RISR_RXSZF_MASK  (0x40000U)
#define LFAST_RISR_RXSZF_SHIFT (18U)
#define LFAST_RISR_RXSZF_WIDTH (1U)
#define LFAST_RISR_RXSZF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXSZF_SHIFT)) & LFAST_RISR_RXSZF_MASK)

#define LFAST_RISR_RXOFF_MASK  (0x80000U)
#define LFAST_RISR_RXOFF_SHIFT (19U)
#define LFAST_RISR_RXOFF_WIDTH (1U)
#define LFAST_RISR_RXOFF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXOFF_SHIFT)) & LFAST_RISR_RXOFF_MASK)

#define LFAST_RISR_RXUFF_MASK  (0x100000U)
#define LFAST_RISR_RXUFF_SHIFT (20U)
#define LFAST_RISR_RXUFF_WIDTH (1U)
#define LFAST_RISR_RXUFF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXUFF_SHIFT)) & LFAST_RISR_RXUFF_MASK)

#define LFAST_RISR_RXMXF_MASK  (0x200000U)
#define LFAST_RISR_RXMXF_SHIFT (21U)
#define LFAST_RISR_RXMXF_WIDTH (1U)
#define LFAST_RISR_RXMXF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXMXF_SHIFT)) & LFAST_RISR_RXMXF_MASK)

#define LFAST_RISR_RXMNF_MASK  (0x400000U)
#define LFAST_RISR_RXMNF_SHIFT (22U)
#define LFAST_RISR_RXMNF_WIDTH (1U)
#define LFAST_RISR_RXMNF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXMNF_SHIFT)) & LFAST_RISR_RXMNF_MASK)

#define LFAST_RISR_RXUOF_MASK  (0x800000U)
#define LFAST_RISR_RXUOF_SHIFT (23U)
#define LFAST_RISR_RXUOF_WIDTH (1U)
#define LFAST_RISR_RXUOF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RISR_RXUOF_SHIFT)) & LFAST_RISR_RXUOF_MASK)
/*! @} */

/*! @name RIISR - LFAST Rx ICLC Interrupt Status */
/*! @{ */

#define LFAST_RIISR_ICPONF_MASK  (0x1U)
#define LFAST_RIISR_ICPONF_SHIFT (0U)
#define LFAST_RIISR_ICPONF_WIDTH (1U)
#define LFAST_RIISR_ICPONF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICPONF_SHIFT)) & LFAST_RIISR_ICPONF_MASK)

#define LFAST_RIISR_ICPOFF_MASK  (0x2U)
#define LFAST_RIISR_ICPOFF_SHIFT (1U)
#define LFAST_RIISR_ICPOFF_WIDTH (1U)
#define LFAST_RIISR_ICPOFF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICPOFF_SHIFT)) & LFAST_RIISR_ICPOFF_MASK)

#define LFAST_RIISR_ICTSF_MASK  (0x4U)
#define LFAST_RIISR_ICTSF_SHIFT (2U)
#define LFAST_RIISR_ICTSF_WIDTH (1U)
#define LFAST_RIISR_ICTSF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICTSF_SHIFT)) & LFAST_RIISR_ICTSF_MASK)

#define LFAST_RIISR_ICTFF_MASK  (0x8U)
#define LFAST_RIISR_ICTFF_SHIFT (3U)
#define LFAST_RIISR_ICTFF_WIDTH (1U)
#define LFAST_RIISR_ICTFF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICTFF_SHIFT)) & LFAST_RIISR_ICTFF_MASK)

#define LFAST_RIISR_ICRSF_MASK  (0x10U)
#define LFAST_RIISR_ICRSF_SHIFT (4U)
#define LFAST_RIISR_ICRSF_WIDTH (1U)
#define LFAST_RIISR_ICRSF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICRSF_SHIFT)) & LFAST_RIISR_ICRSF_MASK)

#define LFAST_RIISR_ICRFF_MASK  (0x20U)
#define LFAST_RIISR_ICRFF_SHIFT (5U)
#define LFAST_RIISR_ICRFF_WIDTH (1U)
#define LFAST_RIISR_ICRFF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICRFF_SHIFT)) & LFAST_RIISR_ICRFF_MASK)

#define LFAST_RIISR_ICTEF_MASK  (0x40U)
#define LFAST_RIISR_ICTEF_SHIFT (6U)
#define LFAST_RIISR_ICTEF_WIDTH (1U)
#define LFAST_RIISR_ICTEF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICTEF_SHIFT)) & LFAST_RIISR_ICTEF_MASK)

#define LFAST_RIISR_ICTDF_MASK  (0x80U)
#define LFAST_RIISR_ICTDF_SHIFT (7U)
#define LFAST_RIISR_ICTDF_WIDTH (1U)
#define LFAST_RIISR_ICTDF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICTDF_SHIFT)) & LFAST_RIISR_ICTDF_MASK)

#define LFAST_RIISR_ICCTF_MASK  (0x100U)
#define LFAST_RIISR_ICCTF_SHIFT (8U)
#define LFAST_RIISR_ICCTF_WIDTH (1U)
#define LFAST_RIISR_ICCTF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICCTF_SHIFT)) & LFAST_RIISR_ICCTF_MASK)

#define LFAST_RIISR_ICLPF_MASK  (0x200U)
#define LFAST_RIISR_ICLPF_SHIFT (9U)
#define LFAST_RIISR_ICLPF_WIDTH (1U)
#define LFAST_RIISR_ICLPF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICLPF_SHIFT)) & LFAST_RIISR_ICLPF_MASK)

#define LFAST_RIISR_ICTOF_MASK  (0x400U)
#define LFAST_RIISR_ICTOF_SHIFT (10U)
#define LFAST_RIISR_ICTOF_WIDTH (1U)
#define LFAST_RIISR_ICTOF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICTOF_SHIFT)) & LFAST_RIISR_ICTOF_MASK)

#define LFAST_RIISR_ICPRF_MASK  (0x800U)
#define LFAST_RIISR_ICPRF_SHIFT (11U)
#define LFAST_RIISR_ICPRF_WIDTH (1U)
#define LFAST_RIISR_ICPRF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICPRF_SHIFT)) & LFAST_RIISR_ICPRF_MASK)

#define LFAST_RIISR_ICPSF_MASK  (0x1000U)
#define LFAST_RIISR_ICPSF_SHIFT (12U)
#define LFAST_RIISR_ICPSF_WIDTH (1U)
#define LFAST_RIISR_ICPSF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICPSF_SHIFT)) & LFAST_RIISR_ICPSF_MASK)

#define LFAST_RIISR_ICPFF_MASK  (0x2000U)
#define LFAST_RIISR_ICPFF_SHIFT (13U)
#define LFAST_RIISR_ICPFF_WIDTH (1U)
#define LFAST_RIISR_ICPFF(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_RIISR_ICPFF_SHIFT)) & LFAST_RIISR_ICPFF_MASK)
/*! @} */

/*! @name PLLLSR - LFAST PLL and LVDS Status */
/*! @{ */

#define LFAST_PLLLSR_LDSLPS_MASK  (0x4U)
#define LFAST_PLLLSR_LDSLPS_SHIFT (2U)
#define LFAST_PLLLSR_LDSLPS_WIDTH (1U)
#define LFAST_PLLLSR_LDSLPS(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLLSR_LDSLPS_SHIFT)) & LFAST_PLLLSR_LDSLPS_MASK)

#define LFAST_PLLLSR_LRSLPS_MASK  (0x8U)
#define LFAST_PLLLSR_LRSLPS_SHIFT (3U)
#define LFAST_PLLLSR_LRSLPS_WIDTH (1U)
#define LFAST_PLLLSR_LRSLPS(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLLSR_LRSLPS_SHIFT)) & LFAST_PLLLSR_LRSLPS_MASK)

#define LFAST_PLLLSR_PLDCR_MASK  (0x10000U)
#define LFAST_PLLLSR_PLDCR_SHIFT (16U)
#define LFAST_PLLLSR_PLDCR_WIDTH (1U)
#define LFAST_PLLLSR_PLDCR(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLLSR_PLDCR_SHIFT)) & LFAST_PLLLSR_PLDCR_MASK)

#define LFAST_PLLLSR_PLLDIS_MASK  (0x20000U)
#define LFAST_PLLLSR_PLLDIS_SHIFT (17U)
#define LFAST_PLLLSR_PLLDIS_WIDTH (1U)
#define LFAST_PLLLSR_PLLDIS(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_PLLLSR_PLLDIS_SHIFT)) & LFAST_PLLLSR_PLLDIS_MASK)
/*! @} */

/*! @name UNSRSR - LFAST Unsolicited Rx Status */
/*! @{ */

#define LFAST_UNSRSR_URPCNT_MASK  (0x7U)
#define LFAST_UNSRSR_URPCNT_SHIFT (0U)
#define LFAST_UNSRSR_URPCNT_WIDTH (3U)
#define LFAST_UNSRSR_URPCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_UNSRSR_URPCNT_SHIFT)) & LFAST_UNSRSR_URPCNT_MASK)

#define LFAST_UNSRSR_URXDV_MASK  (0x100U)
#define LFAST_UNSRSR_URXDV_SHIFT (8U)
#define LFAST_UNSRSR_URXDV_WIDTH (1U)
#define LFAST_UNSRSR_URXDV(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_UNSRSR_URXDV_SHIFT)) & LFAST_UNSRSR_URXDV_MASK)
/*! @} */

/*! @name UNSRDR - LFAST Unsolicited Rx Data */
/*! @{ */

#define LFAST_UNSRDR_UNRXD_MASK  (0xFFFFFFFFU)
#define LFAST_UNSRDR_UNRXD_SHIFT (0U)
#define LFAST_UNSRDR_UNRXD_WIDTH (32U)
#define LFAST_UNSRDR_UNRXD(x) \
    (((uint32_t)(((uint32_t)(x)) << LFAST_UNSRDR_UNRXD_SHIFT)) & LFAST_UNSRDR_UNRXD_MASK)
/*! @} */

/*! @name GPR - General Purpose registers */
/*! @{ */

#define LFAST_GPR_GPR_MASK  (0xFFFFFFFFU)
#define LFAST_GPR_GPR_SHIFT (0U)
#define LFAST_GPR_GPR_WIDTH (32U)
#define LFAST_GPR_GPR(x)    (((uint32_t)(((uint32_t)(x)) << LFAST_GPR_GPR_SHIFT)) & LFAST_GPR_GPR_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LFAST_Register_Masks */

/*!
 * @}
 */ /* end of group LFAST_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_LFAST_H_) */
