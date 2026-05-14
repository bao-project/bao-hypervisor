/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_GPR3.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_GPR3
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
#if !defined(S32Z2_GPR3_H_) /* Check if memory map has not been already included */
#define S32Z2_GPR3_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- GPR3 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR3_Peripheral_Access_Layer GPR3 Peripheral Access Layer
 * @{
 */

/** GPR3 - Register Layout Typedef */
typedef struct {
    __IO uint32_t LVFCCUGD3;      /**< VFCCU Global DID register 3, offset: 0x0 */
    __IO uint32_t LVFCCULD9;      /**< VFCCU Local DID register 9, offset: 0x4 */
    __IO uint32_t LVFCCULD10;     /**< VFCCU Local DID register 10, offset: 0x8 */
    __IO uint32_t LVFCCULD11;     /**< VFCCU Local DID register 11, offset: 0xC */
    __I uint32_t DDRCS;           /**< DDRC Status, offset: 0x10 */
    __IO uint32_t DDRCC;          /**< DDRC Control, offset: 0x14 */
    __IO uint32_t GENC0;          /**< Generic control register 0, offset: 0x18 */
    uint8_t RESERVED_0[36];
    __IO uint32_t FUNCC6;         /**< Enable for TX Ack Suppress Logic, offset: 0x40 */
    uint8_t RESERVED_1[12];
    __I uint32_t INITM3;          /**< NoC Initiator NIU Timeout Status, offset: 0x50 */
    __I uint32_t TARGTMS3;        /**< NoC Target NIU Timeout Status, offset: 0x54 */
    __IO uint32_t TARGTMC3;       /**< NoC Target NIU Timeout Control, offset: 0x58 */
    __IO uint32_t RTU0FDC;        /**< RTU0 Fence and Drain Control, offset: 0x5C */
    __I uint32_t RTU0FDS;         /**< RTU0 Fence and Drain Status, offset: 0x60 */
    __IO uint32_t RTU1FDC;        /**< RTU1 Fence and Drain Control, offset: 0x64 */
    __I uint32_t RTU1FDS;         /**< RTU1 Fence and Drain Status, offset: 0x68 */
    uint8_t RESERVED_2[4];
    __IO uint32_t CE0RSTCNT;      /**< FlexLLCE Cortex-M33 Core 0 Reset Counter, offset: 0x70 */
    __IO uint32_t CE1RSTCNT;      /**< FlexLLCE Cortex-M33 Core 1 Reset Counter, offset: 0x74 */
    __IO uint32_t CLKOUT4SEL;     /**< CLKOUT_4 MUX select, offset: 0x78 */
    __IO uint32_t RGMC;           /**< MC_RGM Control, offset: 0x7C */
    __I uint32_t XRDC_INT_S;      /**< XRDC Interrupt Source, offset: 0x80 */
    uint8_t RESERVED_3[32];
    __I uint32_t FLEXLLCECM33S;   /**< FlexLLCE Cortex-M33 Core 0 Status, offset: 0xA4 */
    __I uint32_t FLEXLLCECM33CES; /**< FlexLLCE Cortex-M33 Core 1 Status, offset: 0xA8 */
    uint8_t RESERVED_4[12];
    __IO uint32_t XPAR3;          /**< Interface parity control and status register, offset: 0xB8 */
    __IO uint32_t XPAR4;          /**< Interface parity control and status register, offset: 0xBC */
    __IO uint32_t RTU0XPAR;       /**< RTU0 global parity control register, offset: 0xC0 */
    __IO uint32_t RTU1XPAR;       /**< RTU1 global parity control register, offset: 0xC4 */
} GPR3_Type, *GPR3_MemMapPtr;

/** Number of instances of the GPR3 module. */
#define GPR3_INSTANCE_COUNT       (1u)

/* GPR3 - Peripheral instance base addresses */
/** Peripheral GPR3 base address */
#define IP_GPR3_BASE              (0x41860000u)
/** Peripheral GPR3 base pointer */
#define IP_GPR3                   ((GPR3_Type*)IP_GPR3_BASE)
/** Array initializer of GPR3 peripheral base addresses */
#define IP_GPR3_BASE_ADDRS        { IP_GPR3_BASE }
/** Array initializer of GPR3 peripheral base pointers */
#define IP_GPR3_BASE_PTRS         { IP_GPR3 }

/* ----------------------------------------------------------------------------
   -- GPR3 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPR3_Register_Masks GPR3 Register Masks
 * @{
 */

/*! @name LVFCCUGD3 - VFCCU Global DID register 3 */
/*! @{ */

#define GPR3_LVFCCUGD3_FHID_MASK  (0xFU)
#define GPR3_LVFCCUGD3_FHID_SHIFT (0U)
#define GPR3_LVFCCUGD3_FHID_WIDTH (4U)
#define GPR3_LVFCCUGD3_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_LVFCCUGD3_FHID_SHIFT)) & GPR3_LVFCCUGD3_FHID_MASK)
/*! @} */

/*! @name LVFCCULD9 - VFCCU Local DID register 9 */
/*! @{ */

#define GPR3_LVFCCULD9_FHID_MASK  (0xFFFFFFFFU)
#define GPR3_LVFCCULD9_FHID_SHIFT (0U)
#define GPR3_LVFCCULD9_FHID_WIDTH (32U)
#define GPR3_LVFCCULD9_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_LVFCCULD9_FHID_SHIFT)) & GPR3_LVFCCULD9_FHID_MASK)
/*! @} */

/*! @name LVFCCULD10 - VFCCU Local DID register 10 */
/*! @{ */

#define GPR3_LVFCCULD10_FHID_MASK  (0xFFFFFFFFU)
#define GPR3_LVFCCULD10_FHID_SHIFT (0U)
#define GPR3_LVFCCULD10_FHID_WIDTH (32U)
#define GPR3_LVFCCULD10_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_LVFCCULD10_FHID_SHIFT)) & GPR3_LVFCCULD10_FHID_MASK)
/*! @} */

/*! @name LVFCCULD11 - VFCCU Local DID register 11 */
/*! @{ */

#define GPR3_LVFCCULD11_FHID_MASK  (0xFFFFFFFFU)
#define GPR3_LVFCCULD11_FHID_SHIFT (0U)
#define GPR3_LVFCCULD11_FHID_WIDTH (32U)
#define GPR3_LVFCCULD11_FHID(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_LVFCCULD11_FHID_SHIFT)) & GPR3_LVFCCULD11_FHID_MASK)
/*! @} */

/*! @name DDRCS - DDRC Status */
/*! @{ */

#define GPR3_DDRCS_RCMC_MASK  (0x1U)
#define GPR3_DDRCS_RCMC_SHIFT (0U)
#define GPR3_DDRCS_RCMC_WIDTH (1U)
#define GPR3_DDRCS_RCMC(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_DDRCS_RCMC_SHIFT)) & GPR3_DDRCS_RCMC_MASK)
/*! @} */

/*! @name DDRCC - DDRC Control */
/*! @{ */

#define GPR3_DDRCC_CMR_MASK  (0x1U)
#define GPR3_DDRCC_CMR_SHIFT (0U)
#define GPR3_DDRCC_CMR_WIDTH (1U)
#define GPR3_DDRCC_CMR(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_DDRCC_CMR_SHIFT)) & GPR3_DDRCC_CMR_MASK)

#define GPR3_DDRCC_DSRR_MASK  (0x2U)
#define GPR3_DDRCC_DSRR_SHIFT (1U)
#define GPR3_DDRCC_DSRR_WIDTH (1U)
#define GPR3_DDRCC_DSRR(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_DDRCC_DSRR_SHIFT)) & GPR3_DDRCC_DSRR_MASK)
/*! @} */

/*! @name GENC0 - Generic control register 0 */
/*! @{ */

#define GPR3_GENC0_CTRL0_MASK  (0xFFFFFFFFU)
#define GPR3_GENC0_CTRL0_SHIFT (0U)
#define GPR3_GENC0_CTRL0_WIDTH (32U)
#define GPR3_GENC0_CTRL0(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_GENC0_CTRL0_SHIFT)) & GPR3_GENC0_CTRL0_MASK)
/*! @} */

/*! @name FUNCC6 - Enable for TX Ack Suppress Logic */
/*! @{ */

#define GPR3_FUNCC6_CTRL_MASK  (0xFFFFFFFFU)
#define GPR3_FUNCC6_CTRL_SHIFT (0U)
#define GPR3_FUNCC6_CTRL_WIDTH (32U)
#define GPR3_FUNCC6_CTRL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FUNCC6_CTRL_SHIFT)) & GPR3_FUNCC6_CTRL_MASK)
/*! @} */

/*! @name INITM3 - NoC Initiator NIU Timeout Status */
/*! @{ */

#define GPR3_INITM3_STAT_MASK  (0xFFFFFFFFU)
#define GPR3_INITM3_STAT_SHIFT (0U)
#define GPR3_INITM3_STAT_WIDTH (32U)
#define GPR3_INITM3_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_INITM3_STAT_SHIFT)) & GPR3_INITM3_STAT_MASK)
/*! @} */

/*! @name TARGTMS3 - NoC Target NIU Timeout Status */
/*! @{ */

#define GPR3_TARGTMS3_STAT_MASK  (0xFFFFFFFFU)
#define GPR3_TARGTMS3_STAT_SHIFT (0U)
#define GPR3_TARGTMS3_STAT_WIDTH (32U)
#define GPR3_TARGTMS3_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_TARGTMS3_STAT_SHIFT)) & GPR3_TARGTMS3_STAT_MASK)
/*! @} */

/*! @name TARGTMC3 - NoC Target NIU Timeout Control */
/*! @{ */

#define GPR3_TARGTMC3_EN_MASK  (0xFFFFFFFFU)
#define GPR3_TARGTMC3_EN_SHIFT (0U)
#define GPR3_TARGTMC3_EN_WIDTH (32U)
#define GPR3_TARGTMC3_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_TARGTMC3_EN_SHIFT)) & GPR3_TARGTMC3_EN_MASK)
/*! @} */

/*! @name RTU0FDC - RTU0 Fence and Drain Control */
/*! @{ */

#define GPR3_RTU0FDC_FDREQ_SYS_NOC_MASK  (0x1U)
#define GPR3_RTU0FDC_FDREQ_SYS_NOC_SHIFT (0U)
#define GPR3_RTU0FDC_FDREQ_SYS_NOC_WIDTH (1U)
#define GPR3_RTU0FDC_FDREQ_SYS_NOC(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU0FDC_FDREQ_SYS_NOC_SHIFT)) & \
        GPR3_RTU0FDC_FDREQ_SYS_NOC_MASK)

#define GPR3_RTU0FDC_FDREQ_LLC_MASK  (0x2U)
#define GPR3_RTU0FDC_FDREQ_LLC_SHIFT (1U)
#define GPR3_RTU0FDC_FDREQ_LLC_WIDTH (1U)
#define GPR3_RTU0FDC_FDREQ_LLC(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU0FDC_FDREQ_LLC_SHIFT)) & GPR3_RTU0FDC_FDREQ_LLC_MASK)

#define GPR3_RTU0FDC_SRAM_KILL_ACCESS_MASK  (0x4U)
#define GPR3_RTU0FDC_SRAM_KILL_ACCESS_SHIFT (2U)
#define GPR3_RTU0FDC_SRAM_KILL_ACCESS_WIDTH (1U)
#define GPR3_RTU0FDC_SRAM_KILL_ACCESS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU0FDC_SRAM_KILL_ACCESS_SHIFT)) & \
        GPR3_RTU0FDC_SRAM_KILL_ACCESS_MASK)
/*! @} */

/*! @name RTU0FDS - RTU0 Fence and Drain Status */
/*! @{ */

#define GPR3_RTU0FDS_IDLE_SYS_NOC_MASK  (0x1U)
#define GPR3_RTU0FDS_IDLE_SYS_NOC_SHIFT (0U)
#define GPR3_RTU0FDS_IDLE_SYS_NOC_WIDTH (1U)
#define GPR3_RTU0FDS_IDLE_SYS_NOC(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU0FDS_IDLE_SYS_NOC_SHIFT)) & \
        GPR3_RTU0FDS_IDLE_SYS_NOC_MASK)

#define GPR3_RTU0FDS_IDLE_LLC_MASK  (0x2U)
#define GPR3_RTU0FDS_IDLE_LLC_SHIFT (1U)
#define GPR3_RTU0FDS_IDLE_LLC_WIDTH (1U)
#define GPR3_RTU0FDS_IDLE_LLC(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU0FDS_IDLE_LLC_SHIFT)) & GPR3_RTU0FDS_IDLE_LLC_MASK)
/*! @} */

/*! @name RTU1FDC - RTU1 Fence and Drain Control */
/*! @{ */

#define GPR3_RTU1FDC_FDREQ_SYS_NOC_MASK  (0x1U)
#define GPR3_RTU1FDC_FDREQ_SYS_NOC_SHIFT (0U)
#define GPR3_RTU1FDC_FDREQ_SYS_NOC_WIDTH (1U)
#define GPR3_RTU1FDC_FDREQ_SYS_NOC(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU1FDC_FDREQ_SYS_NOC_SHIFT)) & \
        GPR3_RTU1FDC_FDREQ_SYS_NOC_MASK)

#define GPR3_RTU1FDC_FDREQ_LLC_MASK  (0x2U)
#define GPR3_RTU1FDC_FDREQ_LLC_SHIFT (1U)
#define GPR3_RTU1FDC_FDREQ_LLC_WIDTH (1U)
#define GPR3_RTU1FDC_FDREQ_LLC(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU1FDC_FDREQ_LLC_SHIFT)) & GPR3_RTU1FDC_FDREQ_LLC_MASK)

#define GPR3_RTU1FDC_SRAM_KILL_ACCESS_MASK  (0x4U)
#define GPR3_RTU1FDC_SRAM_KILL_ACCESS_SHIFT (2U)
#define GPR3_RTU1FDC_SRAM_KILL_ACCESS_WIDTH (1U)
#define GPR3_RTU1FDC_SRAM_KILL_ACCESS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU1FDC_SRAM_KILL_ACCESS_SHIFT)) & \
        GPR3_RTU1FDC_SRAM_KILL_ACCESS_MASK)
/*! @} */

/*! @name RTU1FDS - RTU1 Fence and Drain Status */
/*! @{ */

#define GPR3_RTU1FDS_IDLE_SYS_NOC_MASK  (0x1U)
#define GPR3_RTU1FDS_IDLE_SYS_NOC_SHIFT (0U)
#define GPR3_RTU1FDS_IDLE_SYS_NOC_WIDTH (1U)
#define GPR3_RTU1FDS_IDLE_SYS_NOC(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU1FDS_IDLE_SYS_NOC_SHIFT)) & \
        GPR3_RTU1FDS_IDLE_SYS_NOC_MASK)

#define GPR3_RTU1FDS_IDLE_LLC_MASK  (0x2U)
#define GPR3_RTU1FDS_IDLE_LLC_SHIFT (1U)
#define GPR3_RTU1FDS_IDLE_LLC_WIDTH (1U)
#define GPR3_RTU1FDS_IDLE_LLC(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU1FDS_IDLE_LLC_SHIFT)) & GPR3_RTU1FDS_IDLE_LLC_MASK)
/*! @} */

/*! @name CE0RSTCNT - FlexLLCE Cortex-M33 Core 0 Reset Counter */
/*! @{ */

#define GPR3_CE0RSTCNT_CNTVAL_MASK  (0x3FU)
#define GPR3_CE0RSTCNT_CNTVAL_SHIFT (0U)
#define GPR3_CE0RSTCNT_CNTVAL_WIDTH (6U)
#define GPR3_CE0RSTCNT_CNTVAL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_CE0RSTCNT_CNTVAL_SHIFT)) & GPR3_CE0RSTCNT_CNTVAL_MASK)
/*! @} */

/*! @name CE1RSTCNT - FlexLLCE Cortex-M33 Core 1 Reset Counter */
/*! @{ */

#define GPR3_CE1RSTCNT_CNTVAL_MASK  (0x3FU)
#define GPR3_CE1RSTCNT_CNTVAL_SHIFT (0U)
#define GPR3_CE1RSTCNT_CNTVAL_WIDTH (6U)
#define GPR3_CE1RSTCNT_CNTVAL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_CE1RSTCNT_CNTVAL_SHIFT)) & GPR3_CE1RSTCNT_CNTVAL_MASK)
/*! @} */

/*! @name CLKOUT4SEL - CLKOUT_4 MUX select */
/*! @{ */

#define GPR3_CLKOUT4SEL_MUXSEL_MASK  (0xFU)
#define GPR3_CLKOUT4SEL_MUXSEL_SHIFT (0U)
#define GPR3_CLKOUT4SEL_MUXSEL_WIDTH (4U)
#define GPR3_CLKOUT4SEL_MUXSEL(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_CLKOUT4SEL_MUXSEL_SHIFT)) & GPR3_CLKOUT4SEL_MUXSEL_MASK)
/*! @} */

/*! @name RGMC - MC_RGM Control */
/*! @{ */

#define GPR3_RGMC_FUNC_RST_ENTRY_PROC_DONE_MASK  (0xFFU)
#define GPR3_RGMC_FUNC_RST_ENTRY_PROC_DONE_SHIFT (0U)
#define GPR3_RGMC_FUNC_RST_ENTRY_PROC_DONE_WIDTH (8U)
#define GPR3_RGMC_FUNC_RST_ENTRY_PROC_DONE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RGMC_FUNC_RST_ENTRY_PROC_DONE_SHIFT)) & \
        GPR3_RGMC_FUNC_RST_ENTRY_PROC_DONE_MASK)

#define GPR3_RGMC_FUNC_RST_EXIT_PROC_DONE_MASK  (0x300U)
#define GPR3_RGMC_FUNC_RST_EXIT_PROC_DONE_SHIFT (8U)
#define GPR3_RGMC_FUNC_RST_EXIT_PROC_DONE_WIDTH (2U)
#define GPR3_RGMC_FUNC_RST_EXIT_PROC_DONE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RGMC_FUNC_RST_EXIT_PROC_DONE_SHIFT)) & \
        GPR3_RGMC_FUNC_RST_EXIT_PROC_DONE_MASK)

#define GPR3_RGMC_DEST_RST_DISABLE_MASK  (0x1FFFC00U)
#define GPR3_RGMC_DEST_RST_DISABLE_SHIFT (10U)
#define GPR3_RGMC_DEST_RST_DISABLE_WIDTH (15U)
#define GPR3_RGMC_DEST_RST_DISABLE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RGMC_DEST_RST_DISABLE_SHIFT)) & \
        GPR3_RGMC_DEST_RST_DISABLE_MASK)
/*! @} */

/*! @name XRDC_INT_S - XRDC Interrupt Source */
/*! @{ */

#define GPR3_XRDC_INT_S_XRDC_INT_SRC_MASK  (0x7FFU)
#define GPR3_XRDC_INT_S_XRDC_INT_SRC_SHIFT (0U)
#define GPR3_XRDC_INT_S_XRDC_INT_SRC_WIDTH (11U)
#define GPR3_XRDC_INT_S_XRDC_INT_SRC(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_XRDC_INT_S_XRDC_INT_SRC_SHIFT)) & \
        GPR3_XRDC_INT_S_XRDC_INT_SRC_MASK)
/*! @} */

/*! @name FLEXLLCECM33S - FlexLLCE Cortex-M33 Core 0 Status */
/*! @{ */

#define GPR3_FLEXLLCECM33S_SLEEPDEEP_MASK  (0x1U)
#define GPR3_FLEXLLCECM33S_SLEEPDEEP_SHIFT (0U)
#define GPR3_FLEXLLCECM33S_SLEEPDEEP_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_SLEEPDEEP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_SLEEPDEEP_SHIFT)) & \
        GPR3_FLEXLLCECM33S_SLEEPDEEP_MASK)

#define GPR3_FLEXLLCECM33S_SLEEPHOLDAn_MASK  (0x2U)
#define GPR3_FLEXLLCECM33S_SLEEPHOLDAn_SHIFT (1U)
#define GPR3_FLEXLLCECM33S_SLEEPHOLDAn_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_SLEEPHOLDAn(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_SLEEPHOLDAn_SHIFT)) & \
        GPR3_FLEXLLCECM33S_SLEEPHOLDAn_MASK)

#define GPR3_FLEXLLCECM33S_SLEEPING_MASK  (0x4U)
#define GPR3_FLEXLLCECM33S_SLEEPING_SHIFT (2U)
#define GPR3_FLEXLLCECM33S_SLEEPING_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_SLEEPING(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_SLEEPING_SHIFT)) & \
        GPR3_FLEXLLCECM33S_SLEEPING_MASK)

#define GPR3_FLEXLLCECM33S_CORECLKEN_MASK  (0x8U)
#define GPR3_FLEXLLCECM33S_CORECLKEN_SHIFT (3U)
#define GPR3_FLEXLLCECM33S_CORECLKEN_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_CORECLKEN(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_CORECLKEN_SHIFT)) & \
        GPR3_FLEXLLCECM33S_CORECLKEN_MASK)

#define GPR3_FLEXLLCECM33S_INTVFETCH_MASK  (0x10U)
#define GPR3_FLEXLLCECM33S_INTVFETCH_SHIFT (4U)
#define GPR3_FLEXLLCECM33S_INTVFETCH_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_INTVFETCH(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_INTVFETCH_SHIFT)) & \
        GPR3_FLEXLLCECM33S_INTVFETCH_MASK)

#define GPR3_FLEXLLCECM33S_CPULOCKUP_MASK  (0x20U)
#define GPR3_FLEXLLCECM33S_CPULOCKUP_SHIFT (5U)
#define GPR3_FLEXLLCECM33S_CPULOCKUP_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_CPULOCKUP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_CPULOCKUP_SHIFT)) & \
        GPR3_FLEXLLCECM33S_CPULOCKUP_MASK)

#define GPR3_FLEXLLCECM33S_CURRNS_MASK  (0x40U)
#define GPR3_FLEXLLCECM33S_CURRNS_SHIFT (6U)
#define GPR3_FLEXLLCECM33S_CURRNS_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_CURRNS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_CURRNS_SHIFT)) & \
        GPR3_FLEXLLCECM33S_CURRNS_MASK)

#define GPR3_FLEXLLCECM33S_SYSRSTREQ_MASK  (0x80U)
#define GPR3_FLEXLLCECM33S_SYSRSTREQ_SHIFT (7U)
#define GPR3_FLEXLLCECM33S_SYSRSTREQ_WIDTH (1U)
#define GPR3_FLEXLLCECM33S_SYSRSTREQ(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33S_SYSRSTREQ_SHIFT)) & \
        GPR3_FLEXLLCECM33S_SYSRSTREQ_MASK)
/*! @} */

/*! @name FLEXLLCECM33CES - FlexLLCE Cortex-M33 Core 1 Status */
/*! @{ */

#define GPR3_FLEXLLCECM33CES_SLEEPDEEP_MASK  (0x1U)
#define GPR3_FLEXLLCECM33CES_SLEEPDEEP_SHIFT (0U)
#define GPR3_FLEXLLCECM33CES_SLEEPDEEP_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_SLEEPDEEP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_SLEEPDEEP_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_SLEEPDEEP_MASK)

#define GPR3_FLEXLLCECM33CES_SLEEPHOLDAn_MASK  (0x2U)
#define GPR3_FLEXLLCECM33CES_SLEEPHOLDAn_SHIFT (1U)
#define GPR3_FLEXLLCECM33CES_SLEEPHOLDAn_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_SLEEPHOLDAn(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_SLEEPHOLDAn_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_SLEEPHOLDAn_MASK)

#define GPR3_FLEXLLCECM33CES_SLEEPING_MASK  (0x4U)
#define GPR3_FLEXLLCECM33CES_SLEEPING_SHIFT (2U)
#define GPR3_FLEXLLCECM33CES_SLEEPING_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_SLEEPING(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_SLEEPING_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_SLEEPING_MASK)

#define GPR3_FLEXLLCECM33CES_CORECLKEN_MASK  (0x8U)
#define GPR3_FLEXLLCECM33CES_CORECLKEN_SHIFT (3U)
#define GPR3_FLEXLLCECM33CES_CORECLKEN_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_CORECLKEN(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_CORECLKEN_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_CORECLKEN_MASK)

#define GPR3_FLEXLLCECM33CES_INTVFETCH_MASK  (0x10U)
#define GPR3_FLEXLLCECM33CES_INTVFETCH_SHIFT (4U)
#define GPR3_FLEXLLCECM33CES_INTVFETCH_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_INTVFETCH(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_INTVFETCH_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_INTVFETCH_MASK)

#define GPR3_FLEXLLCECM33CES_CPULOCKUP_MASK  (0x20U)
#define GPR3_FLEXLLCECM33CES_CPULOCKUP_SHIFT (5U)
#define GPR3_FLEXLLCECM33CES_CPULOCKUP_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_CPULOCKUP(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_CPULOCKUP_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_CPULOCKUP_MASK)

#define GPR3_FLEXLLCECM33CES_CURRNS_MASK  (0x40U)
#define GPR3_FLEXLLCECM33CES_CURRNS_SHIFT (6U)
#define GPR3_FLEXLLCECM33CES_CURRNS_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_CURRNS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_CURRNS_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_CURRNS_MASK)

#define GPR3_FLEXLLCECM33CES_SYSRSTREQ_MASK  (0x80U)
#define GPR3_FLEXLLCECM33CES_SYSRSTREQ_SHIFT (7U)
#define GPR3_FLEXLLCECM33CES_SYSRSTREQ_WIDTH (1U)
#define GPR3_FLEXLLCECM33CES_SYSRSTREQ(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << GPR3_FLEXLLCECM33CES_SYSRSTREQ_SHIFT)) & \
        GPR3_FLEXLLCECM33CES_SYSRSTREQ_MASK)
/*! @} */

/*! @name XPAR3 - Interface parity control and status register */
/*! @{ */

#define GPR3_XPAR3_DIS_MASK  (0x3FU)
#define GPR3_XPAR3_DIS_SHIFT (0U)
#define GPR3_XPAR3_DIS_WIDTH (6U)
#define GPR3_XPAR3_DIS(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_XPAR3_DIS_SHIFT)) & GPR3_XPAR3_DIS_MASK)

#define GPR3_XPAR3_STAT_MASK  (0x3F00U)
#define GPR3_XPAR3_STAT_SHIFT (8U)
#define GPR3_XPAR3_STAT_WIDTH (6U)
#define GPR3_XPAR3_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_XPAR3_STAT_SHIFT)) & GPR3_XPAR3_STAT_MASK)
/*! @} */

/*! @name XPAR4 - Interface parity control and status register */
/*! @{ */

#define GPR3_XPAR4_DIS_MASK  (0x3FU)
#define GPR3_XPAR4_DIS_SHIFT (0U)
#define GPR3_XPAR4_DIS_WIDTH (6U)
#define GPR3_XPAR4_DIS(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_XPAR4_DIS_SHIFT)) & GPR3_XPAR4_DIS_MASK)

#define GPR3_XPAR4_STAT_MASK  (0x3F00U)
#define GPR3_XPAR4_STAT_SHIFT (8U)
#define GPR3_XPAR4_STAT_WIDTH (6U)
#define GPR3_XPAR4_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_XPAR4_STAT_SHIFT)) & GPR3_XPAR4_STAT_MASK)
/*! @} */

/*! @name RTU0XPAR - RTU0 global parity control register */
/*! @{ */

#define GPR3_RTU0XPAR_DIS_MASK  (0x1U)
#define GPR3_RTU0XPAR_DIS_SHIFT (0U)
#define GPR3_RTU0XPAR_DIS_WIDTH (1U)
#define GPR3_RTU0XPAR_DIS(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU0XPAR_DIS_SHIFT)) & GPR3_RTU0XPAR_DIS_MASK)
/*! @} */

/*! @name RTU1XPAR - RTU1 global parity control register */
/*! @{ */

#define GPR3_RTU1XPAR_DIS_MASK  (0x1U)
#define GPR3_RTU1XPAR_DIS_SHIFT (0U)
#define GPR3_RTU1XPAR_DIS_WIDTH (1U)
#define GPR3_RTU1XPAR_DIS(x) \
    (((uint32_t)(((uint32_t)(x)) << GPR3_RTU1XPAR_DIS_SHIFT)) & GPR3_RTU1XPAR_DIS_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group GPR3_Register_Masks */

/*!
 * @}
 */ /* end of group GPR3_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_GPR3_H_) */
