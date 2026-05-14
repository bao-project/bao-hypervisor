/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_MC_CGM.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_MC_CGM
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
#if !defined(S32Z2_MC_CGM_H_) /* Check if memory map has not been already included */
#define S32Z2_MC_CGM_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MC_CGM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_CGM_Peripheral_Access_Layer MC_CGM Peripheral Access Layer
 * @{
 */

/** MC_CGM - Register Layout Typedef */
typedef struct {
    __IO uint32_t PCFS_SDUR;   /**< PCFS Step Duration, offset: 0x0 */
    uint8_t RESERVED_0[132];
    __IO uint32_t PCFS_DIVC12; /**< PCFS Divider Change 12 Register, offset: 0x88, available only
                                  on: MC_CGM_0, MC_CGM_1, MC_CGM_3 (missing on MC_CGM_2, MC_CGM_4,
                                  MC_CGM_5, MC_CGM_6) */
    __IO uint32_t PCFS_DIVE12; /**< PCFS Divider End 12 Register, offset: 0x8C, available only on:
                                  MC_CGM_0, MC_CGM_1, MC_CGM_3 (missing on MC_CGM_2, MC_CGM_4,
                                  MC_CGM_5, MC_CGM_6) */
    __IO uint32_t PCFS_DIVS12; /**< PCFS Divider Start 12 Register, offset: 0x90, available only on:
                                  MC_CGM_0, MC_CGM_1, MC_CGM_3 (missing on MC_CGM_2, MC_CGM_4,
                                  MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_1[24];
    __IO uint32_t PCFS_DIVC15; /**< PCFS Divider Change 15 Register, offset: 0xAC, available only
                                  on: MC_CGM_2, MC_CGM_4, MC_CGM_5 (missing on MC_CGM_0, MC_CGM_1,
                                  MC_CGM_3, MC_CGM_6) */
    __IO uint32_t PCFS_DIVE15; /**< PCFS Divider End 15 Register, offset: 0xB0, available only on:
                                  MC_CGM_2, MC_CGM_4, MC_CGM_5 (missing on MC_CGM_0, MC_CGM_1,
                                  MC_CGM_3, MC_CGM_6) */
    __IO uint32_t PCFS_DIVS15; /**< PCFS Divider Start 15 Register, offset: 0xB4, available only on:
                                  MC_CGM_2, MC_CGM_4, MC_CGM_5 (missing on MC_CGM_0, MC_CGM_1,
                                  MC_CGM_3, MC_CGM_6) */
    uint8_t RESERVED_2[288];
    __IO uint32_t PCFS_DIVC40; /**< PCFS Divider Change 40 Register, offset: 0x1D8, available only
                                  on: MC_CGM_6 (missing on MC_CGM_0, MC_CGM_1, MC_CGM_2, MC_CGM_3,
                                  MC_CGM_4, MC_CGM_5) */
    __IO uint32_t PCFS_DIVE40; /**< PCFS Divider End 40 Register, offset: 0x1DC, available only on:
                                  MC_CGM_6 (missing on MC_CGM_0, MC_CGM_1, MC_CGM_2, MC_CGM_3,
                                  MC_CGM_4, MC_CGM_5) */
    __IO uint32_t PCFS_DIVS40; /**< PCFS Divider Start 40 Register, offset: 0x1E0, available only
                                  on: MC_CGM_6 (missing on MC_CGM_0, MC_CGM_1, MC_CGM_2, MC_CGM_3,
                                  MC_CGM_4, MC_CGM_5) */
    uint8_t RESERVED_3[284];
    __IO uint32_t MUX_0_CSC;   /**< Clock Mux 0 Select Control Register, offset: 0x300 */
    __I uint32_t MUX_0_CSS;    /**< Clock Mux 0 Select Status Register, offset: 0x304 */
    __IO uint32_t MUX_0_DC_0;  /**< Clock Mux 0 Divider 0 Control Register, offset: 0x308, available
                                  only on: MC_CGM_5, MC_CGM_6 (missing on MC_CGM_0, MC_CGM_1,
                                  MC_CGM_2, MC_CGM_3, MC_CGM_4) */
    __IO uint32_t MUX_0_DC_1;  /**< Clock Mux 0 Divider 1 Control Register, offset: 0x30C, available
                                  only on: MC_CGM_6 (missing on MC_CGM_0, MC_CGM_1, MC_CGM_2,
                                  MC_CGM_3, MC_CGM_4, MC_CGM_5) */
    uint8_t RESERVED_4[44];
    __I uint32_t MUX_0_DIV_UPD_STAT; /**< Clock Mux 0 Divider Update Status Register, offset: 0x33C,
                                        available only on: MC_CGM_5, MC_CGM_6 (missing on MC_CGM_0,
                                        MC_CGM_1, MC_CGM_2, MC_CGM_3, MC_CGM_4) */
    __IO uint32_t MUX_1_CSC;         /**< Clock Mux 1 Select Control Register, offset: 0x340 */
    __I uint32_t MUX_1_CSS;          /**< Clock Mux 1 Select Status Register, offset: 0x344 */
    __IO uint32_t MUX_1_DC_0;        /**< Clock Mux 1 Divider 0 Control Register, offset: 0x348 */
    __IO uint32_t MUX_1_DC_1; /**< Clock Mux 1 Divider 1 Control Register, offset: 0x34C, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_5[44];
    __I uint32_t MUX_1_DIV_UPD_STAT; /**< Clock Mux 1 Divider Update Status Register, offset: 0x37C
                                      */
    __IO uint32_t MUX_2_CSC; /**< Clock Mux 2 Select Control Register, offset: 0x380, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5
                                (missing on MC_CGM_6) */
    __I uint32_t MUX_2_CSS;  /**< Clock Mux 2 Select Status Register, offset: 0x384, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5
                                (missing on MC_CGM_6) */
    __IO uint32_t MUX_2_DC_0; /**< Clock Mux 2 Divider 0 Control Register, offset: 0x388, available
                                 only on: MC_CGM_0, MC_CGM_3, MC_CGM_4, MC_CGM_5 (missing on
                                 MC_CGM_1, MC_CGM_2, MC_CGM_6) */
    __IO uint32_t MUX_2_DC_1; /**< Clock Mux 2 Divider 1 Control Register, offset: 0x38C, available
                                 only on: MC_CGM_0, MC_CGM_3, MC_CGM_4 (missing on MC_CGM_1,
                                 MC_CGM_2, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_2_DC_2; /**< Clock Mux 2 Divider 2 Control Register, offset: 0x390, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_2_DC_3; /**< Clock Mux 2 Divider 3 Control Register, offset: 0x394, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_2_DC_4; /**< Clock Mux 2 Divider 4 Control Register, offset: 0x398, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_2_DC_5; /**< Clock Mux 2 Divider 5 Control Register, offset: 0x39C, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_6[28];
    __I uint32_t MUX_2_DIV_UPD_STAT; /**< Clock Mux 2 Divider Update Status Register, offset: 0x3BC,
                                        available only on: MC_CGM_0, MC_CGM_3, MC_CGM_4, MC_CGM_5
                                        (missing on MC_CGM_1, MC_CGM_2, MC_CGM_6) */
    __IO uint32_t MUX_3_CSC; /**< Clock Mux 3 Select Control Register, offset: 0x3C0, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5
                                (missing on MC_CGM_6) */
    __I uint32_t MUX_3_CSS;  /**< Clock Mux 3 Select Status Register, offset: 0x3C4, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5
                                (missing on MC_CGM_6) */
    __IO uint32_t MUX_3_DC_0; /**< Clock Mux 3 Divider 0 Control Register, offset: 0x3C8, available
                                 only on: MC_CGM_0, MC_CGM_3, MC_CGM_4 (missing on MC_CGM_1,
                                 MC_CGM_2, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_3_DC_1; /**< Clock Mux 3 Divider 1 Control Register, offset: 0x3CC, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_3_DC_2; /**< Clock Mux 3 Divider 2 Control Register, offset: 0x3D0, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_3_DC_3; /**< Clock Mux 3 Divider 3 Control Register, offset: 0x3D4, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_3_DC_4; /**< Clock Mux 3 Divider 4 Control Register, offset: 0x3D8, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_3_DC_5; /**< Clock Mux 3 Divider 5 Control Register, offset: 0x3DC, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_3_DC_6; /**< Clock Mux 3 Divider 6 Control Register, offset: 0x3E0, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_3_DC_7; /**< Clock Mux 3 Divider 7 Control Register, offset: 0x3E4, available
                                 only on: MC_CGM_0, MC_CGM_4 (missing on MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_7[20];
    __I uint32_t MUX_3_DIV_UPD_STAT; /**< Clock Mux 3 Divider Update Status Register, offset: 0x3FC,
                                        available only on: MC_CGM_0, MC_CGM_3, MC_CGM_4 (missing on
                                        MC_CGM_1, MC_CGM_2, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_4_CSC; /**< Clock Mux 4 Select Control Register, offset: 0x400, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_3, MC_CGM_4, MC_CGM_5 (missing on
                                MC_CGM_2, MC_CGM_6) */
    __I uint32_t MUX_4_CSS;  /**< Clock Mux 4 Select Status Register, offset: 0x404, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_3, MC_CGM_4, MC_CGM_5 (missing on
                                MC_CGM_2, MC_CGM_6) */
    __IO uint32_t MUX_4_DC_0; /**< Clock Mux 4 Divider 0 Control Register, offset: 0x408, available
                                 only on: MC_CGM_0, MC_CGM_1, MC_CGM_3, MC_CGM_5 (missing on
                                 MC_CGM_2, MC_CGM_4, MC_CGM_6) */
    uint8_t RESERVED_8[48];
    __I uint32_t MUX_4_DIV_UPD_STAT; /**< Clock Mux 4 Divider Update Status Register, offset: 0x43C,
                                        available only on: MC_CGM_0, MC_CGM_1, MC_CGM_3, MC_CGM_5
                                        (missing on MC_CGM_2, MC_CGM_4, MC_CGM_6) */
    __IO uint32_t MUX_5_CSC; /**< Clock Mux 5 Select Control Register, offset: 0x440, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4, MC_CGM_5 (missing on MC_CGM_2,
                                MC_CGM_3, MC_CGM_6) */
    __I uint32_t MUX_5_CSS;  /**< Clock Mux 5 Select Status Register, offset: 0x444, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4, MC_CGM_5 (missing on MC_CGM_2,
                                MC_CGM_3, MC_CGM_6) */
    __IO uint32_t MUX_5_DC_0; /**< Clock Mux 5 Divider 0 Control Register, offset: 0x448, available
                                 only on: MC_CGM_1, MC_CGM_5 (missing on MC_CGM_0, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_4, MC_CGM_6) */
    __IO uint32_t MUX_5_DC_1; /**< Clock Mux 5 Divider 1 Control Register, offset: 0x44C, available
                                 only on: MC_CGM_5 (missing on MC_CGM_0, MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_4, MC_CGM_6) */
    __IO uint32_t MUX_5_DC_2; /**< Clock Mux 5 Divider 2 Control Register, offset: 0x450, available
                                 only on: MC_CGM_5 (missing on MC_CGM_0, MC_CGM_1, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_4, MC_CGM_6) */
    uint8_t RESERVED_9[40];
    __I uint32_t MUX_5_DIV_UPD_STAT; /**< Clock Mux 5 Divider Update Status Register, offset: 0x47C,
                                        available only on: MC_CGM_1, MC_CGM_5 (missing on MC_CGM_0,
                                        MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_6) */
    __IO uint32_t MUX_6_CSC; /**< Clock Mux 6 Select Control Register, offset: 0x480, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_6_CSS;  /**< Clock Mux 6 Select Status Register, offset: 0x484, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_6_DC_0; /**< Clock Mux 6 Divider 0 Control Register, offset: 0x488, available
                                 only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_6_DC_1; /**< Clock Mux 6 Divider 1 Control Register, offset: 0x48C, available
                                 only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_10[44];
    __I uint32_t MUX_6_DIV_UPD_STAT; /**< Clock Mux 6 Divider Update Status Register, offset: 0x4BC,
                                        available only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on
                                        MC_CGM_2, MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_7_CSC; /**< Clock Mux 7 Select Control Register, offset: 0x4C0, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_7_CSS;  /**< Clock Mux 7 Select Status Register, offset: 0x4C4, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_7_DC_0; /**< Clock Mux 7 Divider 0 Control Register, offset: 0x4C8, available
                                 only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_7_DC_1; /**< Clock Mux 7 Divider 1 Control Register, offset: 0x4CC, available
                                 only on: MC_CGM_0, MC_CGM_1 (missing on MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_7_DC_2; /**< Clock Mux 7 Divider 2 Control Register, offset: 0x4D0, available
                                 only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_11[32];
    __IO uint32_t MUX_7_DIV_TRIG_CTRL; /**< Clock Mux 7 Divider Trigger Control Register, offset:
                                          0x4F4, available only on: MC_CGM_0 (missing on MC_CGM_1,
                                          MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __O uint32_t MUX_7_DIV_TRIG; /**< Clock Mux 7 Divider Trigger Register, offset: 0x4F8, available
                                    only on: MC_CGM_0 (missing on MC_CGM_1, MC_CGM_2, MC_CGM_3,
                                    MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_7_DIV_UPD_STAT; /**< Clock Mux 7 Divider Update Status Register, offset: 0x4FC,
                                        available only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on
                                        MC_CGM_2, MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_8_CSC; /**< Clock Mux 8 Select Control Register, offset: 0x500, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_8_CSS;  /**< Clock Mux 8 Select Status Register, offset: 0x504, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_8_DC_0; /**< Clock Mux 8 Divider 0 Control Register, offset: 0x508, available
                                 only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_8_DC_1; /**< Clock Mux 8 Divider 1 Control Register, offset: 0x50C, available
                                 only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_12[44];
    __I uint32_t MUX_8_DIV_UPD_STAT; /**< Clock Mux 8 Divider Update Status Register, offset: 0x53C,
                                        available only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on
                                        MC_CGM_2, MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_9_CSC; /**< Clock Mux 9 Select Control Register, offset: 0x540, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_9_CSS;  /**< Clock Mux 9 Select Status Register, offset: 0x544, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_9_DC_0; /**< Clock Mux 9 Divider 0 Control Register, offset: 0x548, available
                                 only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_9_DC_1; /**< Clock Mux 9 Divider 1 Control Register, offset: 0x54C, available
                                 only on: MC_CGM_1, MC_CGM_4 (missing on MC_CGM_0, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_9_DC_2; /**< Clock Mux 9 Divider 2 Control Register, offset: 0x550, available
                                 only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_13[40];
    __I uint32_t MUX_9_DIV_UPD_STAT; /**< Clock Mux 9 Divider Update Status Register, offset: 0x57C,
                                        available only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on
                                        MC_CGM_2, MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_10_CSC; /**< Clock Mux 10 Select Control Register, offset: 0x580, available
                                 only on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_10_CSS; /**< Clock Mux 10 Select Status Register, offset: 0x584, available only
                                on: MC_CGM_0, MC_CGM_1, MC_CGM_4 (missing on MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_10_DC_0;        /**< Clock Mux 10 Divider 0 Control Register, offset: 0x588,
                                         available only on: MC_CGM_0, MC_CGM_1 (missing on MC_CGM_2,
                                         MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_14[48];
    __I uint32_t MUX_10_DIV_UPD_STAT; /**< Clock Mux 10 Divider Update Status Register, offset:
                                         0x5BC, available only on: MC_CGM_0, MC_CGM_1 (missing on
                                         MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_11_CSC; /**< Clock Mux 11 Select Control Register, offset: 0x5C0, available
                                 only on: MC_CGM_1, MC_CGM_4 (missing on MC_CGM_0, MC_CGM_2,
                                 MC_CGM_3, MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_11_CSS; /**< Clock Mux 11 Select Status Register, offset: 0x5C4, available only
                                on: MC_CGM_1, MC_CGM_4 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_11_DC_0;        /**< Clock Mux 11 Divider 0 Control Register, offset: 0x5C8,
                                         available only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2,
                                         MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_15[48];
    __I uint32_t MUX_11_DIV_UPD_STAT; /**< Clock Mux 11 Divider Update Status Register, offset:
                                         0x5FC, available only on: MC_CGM_1 (missing on MC_CGM_0,
                                         MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_12_CSC; /**< Clock Mux 12 Select Control Register, offset: 0x600, available
                                 only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_12_CSS; /**< Clock Mux 12 Select Status Register, offset: 0x604, available only
                                on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3, MC_CGM_4,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_12_DC_0;        /**< Clock Mux 12 Divider 0 Control Register, offset: 0x608,
                                         available only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2,
                                         MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_16[48];
    __I uint32_t MUX_12_DIV_UPD_STAT; /**< Clock Mux 12 Divider Update Status Register, offset:
                                         0x63C, available only on: MC_CGM_1 (missing on MC_CGM_0,
                                         MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_13_CSC; /**< Clock Mux 13 Select Control Register, offset: 0x640, available
                                 only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_13_CSS; /**< Clock Mux 13 Select Status Register, offset: 0x644, available only
                                on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3, MC_CGM_4,
                                MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_17[56];
    __IO uint32_t MUX_14_CSC; /**< Clock Mux 14 Select Control Register, offset: 0x680, available
                                 only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3,
                                 MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    __I uint32_t MUX_14_CSS; /**< Clock Mux 14 Select Status Register, offset: 0x684, available only
                                on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2, MC_CGM_3, MC_CGM_4,
                                MC_CGM_5, MC_CGM_6) */
    __IO uint32_t MUX_14_DC_0;        /**< Clock Mux 14 Divider 0 Control Register, offset: 0x688,
                                         available only on: MC_CGM_1 (missing on MC_CGM_0, MC_CGM_2,
                                         MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
    uint8_t RESERVED_18[48];
    __I uint32_t MUX_14_DIV_UPD_STAT; /**< Clock Mux 14 Divider Update Status Register, offset:
                                         0x6BC, available only on: MC_CGM_1 (missing on MC_CGM_0,
                                         MC_CGM_2, MC_CGM_3, MC_CGM_4, MC_CGM_5, MC_CGM_6) */
} MC_CGM_Type, *MC_CGM_MemMapPtr;

/** Number of instances of the MC_CGM module. */
#define MC_CGM_INSTANCE_COUNT (7u)

/* MC_CGM - Peripheral instance base addresses */
/** Peripheral MC_CGM_0 base address */
#define IP_MC_CGM_0_BASE      (0x40030000u)
/** Peripheral MC_CGM_0 base pointer */
#define IP_MC_CGM_0           ((MC_CGM_Type*)IP_MC_CGM_0_BASE)
/** Peripheral MC_CGM_1 base address */
#define IP_MC_CGM_1_BASE      (0x40830000u)
/** Peripheral MC_CGM_1 base pointer */
#define IP_MC_CGM_1           ((MC_CGM_Type*)IP_MC_CGM_1_BASE)
/** Peripheral MC_CGM_2 base address */
#define IP_MC_CGM_2_BASE      (0x41030000u)
/** Peripheral MC_CGM_2 base pointer */
#define IP_MC_CGM_2           ((MC_CGM_Type*)IP_MC_CGM_2_BASE)
/** Peripheral MC_CGM_3 base address */
#define IP_MC_CGM_3_BASE      (0x41830000u)
/** Peripheral MC_CGM_3 base pointer */
#define IP_MC_CGM_3           ((MC_CGM_Type*)IP_MC_CGM_3_BASE)
/** Peripheral MC_CGM_4 base address */
#define IP_MC_CGM_4_BASE      (0x42030000u)
/** Peripheral MC_CGM_4 base pointer */
#define IP_MC_CGM_4           ((MC_CGM_Type*)IP_MC_CGM_4_BASE)
/** Peripheral MC_CGM_5 base address */
#define IP_MC_CGM_5_BASE      (0x42830000u)
/** Peripheral MC_CGM_5 base pointer */
#define IP_MC_CGM_5           ((MC_CGM_Type*)IP_MC_CGM_5_BASE)
/** Peripheral MC_CGM_6 base address */
#define IP_MC_CGM_6_BASE      (0x44030000u)
/** Peripheral MC_CGM_6 base pointer */
#define IP_MC_CGM_6           ((MC_CGM_Type*)IP_MC_CGM_6_BASE)
/** Array initializer of MC_CGM peripheral base addresses */
#define IP_MC_CGM_BASE_ADDRS                                                                    \
    { IP_MC_CGM_0_BASE, IP_MC_CGM_1_BASE, IP_MC_CGM_2_BASE, IP_MC_CGM_3_BASE, IP_MC_CGM_4_BASE, \
        IP_MC_CGM_5_BASE, IP_MC_CGM_6_BASE }
/** Array initializer of MC_CGM peripheral base pointers */
#define IP_MC_CGM_BASE_PTRS \
    { IP_MC_CGM_0, IP_MC_CGM_1, IP_MC_CGM_2, IP_MC_CGM_3, IP_MC_CGM_4, IP_MC_CGM_5, IP_MC_CGM_6 }

/* ----------------------------------------------------------------------------
   -- MC_CGM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_CGM_Register_Masks MC_CGM Register Masks
 * @{
 */

/*! @name PCFS_SDUR - PCFS Step Duration */
/*! @{ */

#define MC_CGM_PCFS_SDUR_SDUR_MASK  (0xFFFFU)
#define MC_CGM_PCFS_SDUR_SDUR_SHIFT (0U)
#define MC_CGM_PCFS_SDUR_SDUR_WIDTH (16U)
#define MC_CGM_PCFS_SDUR_SDUR(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_SDUR_SDUR_SHIFT)) & MC_CGM_PCFS_SDUR_SDUR_MASK)
/*! @} */

/*! @name PCFS_DIVC12 - PCFS Divider Change 12 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVC12_RATE_MASK  (0xFFU)
#define MC_CGM_PCFS_DIVC12_RATE_SHIFT (0U)
#define MC_CGM_PCFS_DIVC12_RATE_WIDTH (8U)
#define MC_CGM_PCFS_DIVC12_RATE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC12_RATE_SHIFT)) & MC_CGM_PCFS_DIVC12_RATE_MASK)

#define MC_CGM_PCFS_DIVC12_INIT_MASK  (0xFFFF0000U)
#define MC_CGM_PCFS_DIVC12_INIT_SHIFT (16U)
#define MC_CGM_PCFS_DIVC12_INIT_WIDTH (16U)
#define MC_CGM_PCFS_DIVC12_INIT(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC12_INIT_SHIFT)) & MC_CGM_PCFS_DIVC12_INIT_MASK)
/*! @} */

/*! @name PCFS_DIVE12 - PCFS Divider End 12 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVE12_DIVE_MASK  (0xFFFFFU)
#define MC_CGM_PCFS_DIVE12_DIVE_SHIFT (0U)
#define MC_CGM_PCFS_DIVE12_DIVE_WIDTH (20U)
#define MC_CGM_PCFS_DIVE12_DIVE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVE12_DIVE_SHIFT)) & MC_CGM_PCFS_DIVE12_DIVE_MASK)
/*! @} */

/*! @name PCFS_DIVS12 - PCFS Divider Start 12 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVS12_DIVS_MASK  (0xFFFFFU)
#define MC_CGM_PCFS_DIVS12_DIVS_SHIFT (0U)
#define MC_CGM_PCFS_DIVS12_DIVS_WIDTH (20U)
#define MC_CGM_PCFS_DIVS12_DIVS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVS12_DIVS_SHIFT)) & MC_CGM_PCFS_DIVS12_DIVS_MASK)
/*! @} */

/*! @name PCFS_DIVC15 - PCFS Divider Change 15 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVC15_RATE_MASK  (0xFFU)
#define MC_CGM_PCFS_DIVC15_RATE_SHIFT (0U)
#define MC_CGM_PCFS_DIVC15_RATE_WIDTH (8U)
#define MC_CGM_PCFS_DIVC15_RATE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC15_RATE_SHIFT)) & MC_CGM_PCFS_DIVC15_RATE_MASK)

#define MC_CGM_PCFS_DIVC15_INIT_MASK  (0xFFFF0000U)
#define MC_CGM_PCFS_DIVC15_INIT_SHIFT (16U)
#define MC_CGM_PCFS_DIVC15_INIT_WIDTH (16U)
#define MC_CGM_PCFS_DIVC15_INIT(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC15_INIT_SHIFT)) & MC_CGM_PCFS_DIVC15_INIT_MASK)
/*! @} */

/*! @name PCFS_DIVE15 - PCFS Divider End 15 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVE15_DIVE_MASK  (0xFFFFFU)
#define MC_CGM_PCFS_DIVE15_DIVE_SHIFT (0U)
#define MC_CGM_PCFS_DIVE15_DIVE_WIDTH (20U)
#define MC_CGM_PCFS_DIVE15_DIVE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVE15_DIVE_SHIFT)) & MC_CGM_PCFS_DIVE15_DIVE_MASK)
/*! @} */

/*! @name PCFS_DIVS15 - PCFS Divider Start 15 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVS15_DIVS_MASK  (0xFFFFFU)
#define MC_CGM_PCFS_DIVS15_DIVS_SHIFT (0U)
#define MC_CGM_PCFS_DIVS15_DIVS_WIDTH (20U)
#define MC_CGM_PCFS_DIVS15_DIVS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVS15_DIVS_SHIFT)) & MC_CGM_PCFS_DIVS15_DIVS_MASK)
/*! @} */

/*! @name PCFS_DIVC40 - PCFS Divider Change 40 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVC40_RATE_MASK  (0xFFU)
#define MC_CGM_PCFS_DIVC40_RATE_SHIFT (0U)
#define MC_CGM_PCFS_DIVC40_RATE_WIDTH (8U)
#define MC_CGM_PCFS_DIVC40_RATE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC40_RATE_SHIFT)) & MC_CGM_PCFS_DIVC40_RATE_MASK)

#define MC_CGM_PCFS_DIVC40_INIT_MASK  (0xFFFF0000U)
#define MC_CGM_PCFS_DIVC40_INIT_SHIFT (16U)
#define MC_CGM_PCFS_DIVC40_INIT_WIDTH (16U)
#define MC_CGM_PCFS_DIVC40_INIT(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC40_INIT_SHIFT)) & MC_CGM_PCFS_DIVC40_INIT_MASK)
/*! @} */

/*! @name PCFS_DIVE40 - PCFS Divider End 40 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVE40_DIVE_MASK  (0xFFFFFU)
#define MC_CGM_PCFS_DIVE40_DIVE_SHIFT (0U)
#define MC_CGM_PCFS_DIVE40_DIVE_WIDTH (20U)
#define MC_CGM_PCFS_DIVE40_DIVE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVE40_DIVE_SHIFT)) & MC_CGM_PCFS_DIVE40_DIVE_MASK)
/*! @} */

/*! @name PCFS_DIVS40 - PCFS Divider Start 40 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVS40_DIVS_MASK  (0xFFFFFU)
#define MC_CGM_PCFS_DIVS40_DIVS_SHIFT (0U)
#define MC_CGM_PCFS_DIVS40_DIVS_WIDTH (20U)
#define MC_CGM_PCFS_DIVS40_DIVS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVS40_DIVS_SHIFT)) & MC_CGM_PCFS_DIVS40_DIVS_MASK)
/*! @} */

/*! @name MUX_0_CSC - Clock Mux 0 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_0_CSC_RAMPUP_MASK  (0x1U)
#define MC_CGM_MUX_0_CSC_RAMPUP_SHIFT (0U)
#define MC_CGM_MUX_0_CSC_RAMPUP_WIDTH (1U)
#define MC_CGM_MUX_0_CSC_RAMPUP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_RAMPUP_SHIFT)) & MC_CGM_MUX_0_CSC_RAMPUP_MASK)

#define MC_CGM_MUX_0_CSC_RAMPDOWN_MASK  (0x2U)
#define MC_CGM_MUX_0_CSC_RAMPDOWN_SHIFT (1U)
#define MC_CGM_MUX_0_CSC_RAMPDOWN_WIDTH (1U)
#define MC_CGM_MUX_0_CSC_RAMPDOWN(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_RAMPDOWN_SHIFT)) & \
        MC_CGM_MUX_0_CSC_RAMPDOWN_MASK)

#define MC_CGM_MUX_0_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_0_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_0_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_0_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_0_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_0_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_0_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_0_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_0_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_0_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_0_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (4, 6), \
                     largest definition used */
#define MC_CGM_MUX_0_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_0_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_0_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_0_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (4, 6), largest definition used */
/*! @} */

/*! @name MUX_0_CSS - Clock Mux 0 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_0_CSS_RAMPUP_MASK  (0x1U)
#define MC_CGM_MUX_0_CSS_RAMPUP_SHIFT (0U)
#define MC_CGM_MUX_0_CSS_RAMPUP_WIDTH (1U)
#define MC_CGM_MUX_0_CSS_RAMPUP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_RAMPUP_SHIFT)) & MC_CGM_MUX_0_CSS_RAMPUP_MASK)

#define MC_CGM_MUX_0_CSS_RAMPDOWN_MASK  (0x2U)
#define MC_CGM_MUX_0_CSS_RAMPDOWN_SHIFT (1U)
#define MC_CGM_MUX_0_CSS_RAMPDOWN_WIDTH (1U)
#define MC_CGM_MUX_0_CSS_RAMPDOWN(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_RAMPDOWN_SHIFT)) & \
        MC_CGM_MUX_0_CSS_RAMPDOWN_MASK)

#define MC_CGM_MUX_0_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_0_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_0_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_0_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_0_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_0_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_0_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_0_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_0_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_0_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_0_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_0_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_0_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_0_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SWIP_SHIFT)) & MC_CGM_MUX_0_CSS_SWIP_MASK)

#define MC_CGM_MUX_0_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_0_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_0_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_0_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_0_CSS_SWTRG_MASK)

#define MC_CGM_MUX_0_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (4, 6), \
                     largest definition used */
#define MC_CGM_MUX_0_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_0_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_0_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_0_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (4, 6), largest definition used */
/*! @} */

/*! @name MUX_0_DC_0 - Clock Mux 0 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_0_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_0_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_0_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_0_DIV_SHIFT)) & MC_CGM_MUX_0_DC_0_DIV_MASK)

#define MC_CGM_MUX_0_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_0_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_0_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_0_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_0_DE_SHIFT)) & MC_CGM_MUX_0_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_0_DC_1 - Clock Mux 0 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_0_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_0_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_0_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_1_DIV_SHIFT)) & MC_CGM_MUX_0_DC_1_DIV_MASK)

#define MC_CGM_MUX_0_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_0_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_0_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_0_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_1_DE_SHIFT)) & MC_CGM_MUX_0_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_0_DIV_UPD_STAT - Clock Mux 0 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_1_CSC - Clock Mux 1 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_1_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_1_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_1_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_1_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_1_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_1_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_1_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_1_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_1_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_1_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_1_CSC_SELCTL_MASK  (0xF000000U)
#define MC_CGM_MUX_1_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_1_CSC_SELCTL_WIDTH (4U)
#define MC_CGM_MUX_1_CSC_SELCTL(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_1_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_1_CSS - Clock Mux 1 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_1_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_1_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_1_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_1_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_1_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_1_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_1_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_1_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_1_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_1_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_1_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_1_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_1_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_1_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SWIP_SHIFT)) & MC_CGM_MUX_1_CSS_SWIP_MASK)

#define MC_CGM_MUX_1_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_1_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_1_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_1_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_1_CSS_SWTRG_MASK)

#define MC_CGM_MUX_1_CSS_SELSTAT_MASK  (0xF000000U)
#define MC_CGM_MUX_1_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_1_CSS_SELSTAT_WIDTH (4U)
#define MC_CGM_MUX_1_CSS_SELSTAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)) & \
        MC_CGM_MUX_1_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_1_DC_0 - Clock Mux 1 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_1_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_1_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_1_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_1_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DC_0_DIV_SHIFT)) & MC_CGM_MUX_1_DC_0_DIV_MASK)

#define MC_CGM_MUX_1_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_1_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_1_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_1_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DC_0_DE_SHIFT)) & MC_CGM_MUX_1_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_1_DC_1 - Clock Mux 1 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_1_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_1_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_1_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_1_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DC_1_DIV_SHIFT)) & MC_CGM_MUX_1_DC_1_DIV_MASK)

#define MC_CGM_MUX_1_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_1_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_1_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_1_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DC_1_DE_SHIFT)) & MC_CGM_MUX_1_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_1_DIV_UPD_STAT - Clock Mux 1 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_2_CSC - Clock Mux 2 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_2_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_2_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_2_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_2_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_2_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_2_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_2_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_2_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_2_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_2_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_2_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_2_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_2_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_2_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_2_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_2_CSS - Clock Mux 2 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_2_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_2_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_2_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_2_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_2_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_2_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_2_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_2_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_2_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_2_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_2_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_2_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_2_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_2_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SWIP_SHIFT)) & MC_CGM_MUX_2_CSS_SWIP_MASK)

#define MC_CGM_MUX_2_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_2_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_2_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_2_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_2_CSS_SWTRG_MASK)

#define MC_CGM_MUX_2_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_2_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_2_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_2_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_2_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_2_DC_0 - Clock Mux 2 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_2_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_2_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_2_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_2_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_0_DIV_SHIFT)) & MC_CGM_MUX_2_DC_0_DIV_MASK)

#define MC_CGM_MUX_2_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_2_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_2_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_2_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_0_DE_SHIFT)) & MC_CGM_MUX_2_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_2_DC_1 - Clock Mux 2 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_2_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_2_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_2_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_2_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_1_DIV_SHIFT)) & MC_CGM_MUX_2_DC_1_DIV_MASK)

#define MC_CGM_MUX_2_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_2_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_2_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_2_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_1_DE_SHIFT)) & MC_CGM_MUX_2_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_2_DC_2 - Clock Mux 2 Divider 2 Control Register */
/*! @{ */

#define MC_CGM_MUX_2_DC_2_DIV_FMT_MASK  (0x3U)
#define MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT (0U)
#define MC_CGM_MUX_2_DC_2_DIV_FMT_WIDTH (2U)
#define MC_CGM_MUX_2_DC_2_DIV_FMT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT)) & \
        MC_CGM_MUX_2_DC_2_DIV_FMT_MASK)

#define MC_CGM_MUX_2_DC_2_DIV_MASK  (0x1FFF0000U)
#define MC_CGM_MUX_2_DC_2_DIV_SHIFT (16U)
#define MC_CGM_MUX_2_DC_2_DIV_WIDTH (13U)
#define MC_CGM_MUX_2_DC_2_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_2_DIV_SHIFT)) & MC_CGM_MUX_2_DC_2_DIV_MASK)

#define MC_CGM_MUX_2_DC_2_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_2_DC_2_DE_SHIFT (31U)
#define MC_CGM_MUX_2_DC_2_DE_WIDTH (1U)
#define MC_CGM_MUX_2_DC_2_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_2_DE_SHIFT)) & MC_CGM_MUX_2_DC_2_DE_MASK)
/*! @} */

/*! @name MUX_2_DC_3 - Clock Mux 2 Divider 3 Control Register */
/*! @{ */

#define MC_CGM_MUX_2_DC_3_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_2_DC_3_DIV_SHIFT (16U)
#define MC_CGM_MUX_2_DC_3_DIV_WIDTH (8U)
#define MC_CGM_MUX_2_DC_3_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_3_DIV_SHIFT)) & MC_CGM_MUX_2_DC_3_DIV_MASK)

#define MC_CGM_MUX_2_DC_3_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_2_DC_3_DE_SHIFT (31U)
#define MC_CGM_MUX_2_DC_3_DE_WIDTH (1U)
#define MC_CGM_MUX_2_DC_3_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_3_DE_SHIFT)) & MC_CGM_MUX_2_DC_3_DE_MASK)
/*! @} */

/*! @name MUX_2_DC_4 - Clock Mux 2 Divider 4 Control Register */
/*! @{ */

#define MC_CGM_MUX_2_DC_4_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_2_DC_4_DIV_SHIFT (16U)
#define MC_CGM_MUX_2_DC_4_DIV_WIDTH (8U)
#define MC_CGM_MUX_2_DC_4_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_4_DIV_SHIFT)) & MC_CGM_MUX_2_DC_4_DIV_MASK)

#define MC_CGM_MUX_2_DC_4_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_2_DC_4_DE_SHIFT (31U)
#define MC_CGM_MUX_2_DC_4_DE_WIDTH (1U)
#define MC_CGM_MUX_2_DC_4_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_4_DE_SHIFT)) & MC_CGM_MUX_2_DC_4_DE_MASK)
/*! @} */

/*! @name MUX_2_DC_5 - Clock Mux 2 Divider 5 Control Register */
/*! @{ */

#define MC_CGM_MUX_2_DC_5_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_2_DC_5_DIV_SHIFT (16U)
#define MC_CGM_MUX_2_DC_5_DIV_WIDTH (8U)
#define MC_CGM_MUX_2_DC_5_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_5_DIV_SHIFT)) & MC_CGM_MUX_2_DC_5_DIV_MASK)

#define MC_CGM_MUX_2_DC_5_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_2_DC_5_DE_SHIFT (31U)
#define MC_CGM_MUX_2_DC_5_DE_WIDTH (1U)
#define MC_CGM_MUX_2_DC_5_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_5_DE_SHIFT)) & MC_CGM_MUX_2_DC_5_DE_MASK)
/*! @} */

/*! @name MUX_2_DIV_UPD_STAT - Clock Mux 2 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_3_CSC - Clock Mux 3 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_3_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_3_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_3_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_3_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_3_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_3_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_3_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_3_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_3_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_3_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_3_CSC_SELCTL_MASK                                                           \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (4, 5, 6), \
                     largest definition used */
#define MC_CGM_MUX_3_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_3_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_3_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_3_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (4, 5, 6), largest definition used */
/*! @} */

/*! @name MUX_3_CSS - Clock Mux 3 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_3_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_3_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_3_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_3_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_3_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_3_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_3_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_3_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_3_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_3_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_3_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_3_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_3_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_3_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SWIP_SHIFT)) & MC_CGM_MUX_3_CSS_SWIP_MASK)

#define MC_CGM_MUX_3_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_3_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_3_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_3_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_3_CSS_SWTRG_MASK)

#define MC_CGM_MUX_3_CSS_SELSTAT_MASK                                                          \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (4, 5, 6), \
                     largest definition used */
#define MC_CGM_MUX_3_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_3_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_3_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_3_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (4, 5, 6), largest definition used */
/*! @} */

/*! @name MUX_3_DC_0 - Clock Mux 3 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_0_DIV_MASK                                                          \
    (0x3FF0000U) /* Merged from fields with different position or width, of widths (8, 10), \
                    largest definition used */
#define MC_CGM_MUX_3_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_0_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_0_DIV(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_0_DIV_SHIFT)) &                            \
        MC_CGM_MUX_3_DC_0_DIV_MASK) /* Merged from fields with different position or width, of \
                                       widths (8, 10), largest definition used */

#define MC_CGM_MUX_3_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_0_DE_SHIFT)) & MC_CGM_MUX_3_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_3_DC_1 - Clock Mux 3 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_1_DIV_MASK  (0x3FF0000U)
#define MC_CGM_MUX_3_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_1_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_1_DIV_SHIFT)) & MC_CGM_MUX_3_DC_1_DIV_MASK)

#define MC_CGM_MUX_3_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_1_DE_SHIFT)) & MC_CGM_MUX_3_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_3_DC_2 - Clock Mux 3 Divider 2 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_2_DIV_MASK  (0x3FF0000U)
#define MC_CGM_MUX_3_DC_2_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_2_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_2_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_2_DIV_SHIFT)) & MC_CGM_MUX_3_DC_2_DIV_MASK)

#define MC_CGM_MUX_3_DC_2_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_2_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_2_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_2_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_2_DE_SHIFT)) & MC_CGM_MUX_3_DC_2_DE_MASK)
/*! @} */

/*! @name MUX_3_DC_3 - Clock Mux 3 Divider 3 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_3_DIV_MASK  (0x3FF0000U)
#define MC_CGM_MUX_3_DC_3_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_3_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_3_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_3_DIV_SHIFT)) & MC_CGM_MUX_3_DC_3_DIV_MASK)

#define MC_CGM_MUX_3_DC_3_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_3_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_3_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_3_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_3_DE_SHIFT)) & MC_CGM_MUX_3_DC_3_DE_MASK)
/*! @} */

/*! @name MUX_3_DC_4 - Clock Mux 3 Divider 4 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_4_DIV_MASK  (0x3FF0000U)
#define MC_CGM_MUX_3_DC_4_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_4_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_4_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_4_DIV_SHIFT)) & MC_CGM_MUX_3_DC_4_DIV_MASK)

#define MC_CGM_MUX_3_DC_4_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_4_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_4_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_4_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_4_DE_SHIFT)) & MC_CGM_MUX_3_DC_4_DE_MASK)
/*! @} */

/*! @name MUX_3_DC_5 - Clock Mux 3 Divider 5 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_5_DIV_MASK  (0x3FF0000U)
#define MC_CGM_MUX_3_DC_5_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_5_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_5_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_5_DIV_SHIFT)) & MC_CGM_MUX_3_DC_5_DIV_MASK)

#define MC_CGM_MUX_3_DC_5_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_5_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_5_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_5_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_5_DE_SHIFT)) & MC_CGM_MUX_3_DC_5_DE_MASK)
/*! @} */

/*! @name MUX_3_DC_6 - Clock Mux 3 Divider 6 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_6_DIV_MASK  (0x3FF0000U)
#define MC_CGM_MUX_3_DC_6_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_6_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_6_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_6_DIV_SHIFT)) & MC_CGM_MUX_3_DC_6_DIV_MASK)

#define MC_CGM_MUX_3_DC_6_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_6_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_6_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_6_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_6_DE_SHIFT)) & MC_CGM_MUX_3_DC_6_DE_MASK)
/*! @} */

/*! @name MUX_3_DC_7 - Clock Mux 3 Divider 7 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_7_DIV_MASK  (0x3FF0000U)
#define MC_CGM_MUX_3_DC_7_DIV_SHIFT (16U)
#define MC_CGM_MUX_3_DC_7_DIV_WIDTH (10U)
#define MC_CGM_MUX_3_DC_7_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_7_DIV_SHIFT)) & MC_CGM_MUX_3_DC_7_DIV_MASK)

#define MC_CGM_MUX_3_DC_7_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_3_DC_7_DE_SHIFT (31U)
#define MC_CGM_MUX_3_DC_7_DE_WIDTH (1U)
#define MC_CGM_MUX_3_DC_7_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_7_DE_SHIFT)) & MC_CGM_MUX_3_DC_7_DE_MASK)
/*! @} */

/*! @name MUX_3_DIV_UPD_STAT - Clock Mux 3 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_4_CSC - Clock Mux 4 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_4_CSC_CG_MASK  (0x4U)
#define MC_CGM_MUX_4_CSC_CG_SHIFT (2U)
#define MC_CGM_MUX_4_CSC_CG_WIDTH (1U)
#define MC_CGM_MUX_4_CSC_CG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_CG_SHIFT)) & MC_CGM_MUX_4_CSC_CG_MASK)

#define MC_CGM_MUX_4_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_4_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_4_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_4_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_4_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_4_CSC_FCG_MASK  (0x8U)
#define MC_CGM_MUX_4_CSC_FCG_SHIFT (3U)
#define MC_CGM_MUX_4_CSC_FCG_WIDTH (1U)
#define MC_CGM_MUX_4_CSC_FCG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_FCG_SHIFT)) & MC_CGM_MUX_4_CSC_FCG_MASK)

#define MC_CGM_MUX_4_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_4_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_4_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_4_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_4_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_4_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_4_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_4_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_4_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_4_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_4_CSS - Clock Mux 4 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_4_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_4_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_4_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_4_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_4_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_4_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_4_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_4_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_4_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_4_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_4_CSS_GRIP_MASK  (0x10000U)
#define MC_CGM_MUX_4_CSS_GRIP_SHIFT (16U)
#define MC_CGM_MUX_4_CSS_GRIP_WIDTH (1U)
#define MC_CGM_MUX_4_CSS_GRIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_GRIP_SHIFT)) & MC_CGM_MUX_4_CSS_GRIP_MASK)

#define MC_CGM_MUX_4_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_4_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_4_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_4_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SWIP_SHIFT)) & MC_CGM_MUX_4_CSS_SWIP_MASK)

#define MC_CGM_MUX_4_CSS_CS_MASK  (0x20000U)
#define MC_CGM_MUX_4_CSS_CS_SHIFT (17U)
#define MC_CGM_MUX_4_CSS_CS_WIDTH (1U)
#define MC_CGM_MUX_4_CSS_CS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_CS_SHIFT)) & MC_CGM_MUX_4_CSS_CS_MASK)

#define MC_CGM_MUX_4_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_4_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_4_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_4_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_4_CSS_SWTRG_MASK)

#define MC_CGM_MUX_4_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_4_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_4_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_4_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_4_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_4_DC_0 - Clock Mux 4 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_4_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_4_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_4_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_4_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_DC_0_DIV_SHIFT)) & MC_CGM_MUX_4_DC_0_DIV_MASK)

#define MC_CGM_MUX_4_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_4_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_4_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_4_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_DC_0_DE_SHIFT)) & MC_CGM_MUX_4_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_4_DIV_UPD_STAT - Clock Mux 4 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_5_CSC - Clock Mux 5 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_5_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_5_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_5_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_5_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_5_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_5_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_5_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_5_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_5_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_5_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_5_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_5_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_5_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_5_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_5_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_5_CSS - Clock Mux 5 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_5_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_5_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_5_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_5_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_5_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_5_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_5_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_5_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_5_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_5_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_5_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_5_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_5_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_5_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_SWIP_SHIFT)) & MC_CGM_MUX_5_CSS_SWIP_MASK)

#define MC_CGM_MUX_5_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_5_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_5_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_5_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_5_CSS_SWTRG_MASK)

#define MC_CGM_MUX_5_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_5_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_5_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_5_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_5_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_5_DC_0 - Clock Mux 5 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_5_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_5_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_5_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_5_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_0_DIV_SHIFT)) & MC_CGM_MUX_5_DC_0_DIV_MASK)

#define MC_CGM_MUX_5_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_5_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_5_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_5_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_0_DE_SHIFT)) & MC_CGM_MUX_5_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_5_DC_1 - Clock Mux 5 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_5_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_5_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_5_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_5_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_1_DIV_SHIFT)) & MC_CGM_MUX_5_DC_1_DIV_MASK)

#define MC_CGM_MUX_5_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_5_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_5_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_5_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_1_DE_SHIFT)) & MC_CGM_MUX_5_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_5_DC_2 - Clock Mux 5 Divider 2 Control Register */
/*! @{ */

#define MC_CGM_MUX_5_DC_2_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_5_DC_2_DIV_SHIFT (16U)
#define MC_CGM_MUX_5_DC_2_DIV_WIDTH (8U)
#define MC_CGM_MUX_5_DC_2_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_2_DIV_SHIFT)) & MC_CGM_MUX_5_DC_2_DIV_MASK)

#define MC_CGM_MUX_5_DC_2_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_5_DC_2_DE_SHIFT (31U)
#define MC_CGM_MUX_5_DC_2_DE_WIDTH (1U)
#define MC_CGM_MUX_5_DC_2_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_2_DE_SHIFT)) & MC_CGM_MUX_5_DC_2_DE_MASK)
/*! @} */

/*! @name MUX_5_DIV_UPD_STAT - Clock Mux 5 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_6_CSC - Clock Mux 6 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_6_CSC_CG_MASK  (0x4U)
#define MC_CGM_MUX_6_CSC_CG_SHIFT (2U)
#define MC_CGM_MUX_6_CSC_CG_WIDTH (1U)
#define MC_CGM_MUX_6_CSC_CG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_CG_SHIFT)) & MC_CGM_MUX_6_CSC_CG_MASK)

#define MC_CGM_MUX_6_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_6_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_6_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_6_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_6_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_6_CSC_FCG_MASK  (0x8U)
#define MC_CGM_MUX_6_CSC_FCG_SHIFT (3U)
#define MC_CGM_MUX_6_CSC_FCG_WIDTH (1U)
#define MC_CGM_MUX_6_CSC_FCG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_FCG_SHIFT)) & MC_CGM_MUX_6_CSC_FCG_MASK)

#define MC_CGM_MUX_6_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_6_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_6_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_6_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_6_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_6_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_6_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_6_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_6_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_6_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_6_CSS - Clock Mux 6 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_6_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_6_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_6_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_6_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_6_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_6_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_6_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_6_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_6_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_6_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_6_CSS_GRIP_MASK  (0x10000U)
#define MC_CGM_MUX_6_CSS_GRIP_SHIFT (16U)
#define MC_CGM_MUX_6_CSS_GRIP_WIDTH (1U)
#define MC_CGM_MUX_6_CSS_GRIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_GRIP_SHIFT)) & MC_CGM_MUX_6_CSS_GRIP_MASK)

#define MC_CGM_MUX_6_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_6_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_6_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_6_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_SWIP_SHIFT)) & MC_CGM_MUX_6_CSS_SWIP_MASK)

#define MC_CGM_MUX_6_CSS_CS_MASK  (0x20000U)
#define MC_CGM_MUX_6_CSS_CS_SHIFT (17U)
#define MC_CGM_MUX_6_CSS_CS_WIDTH (1U)
#define MC_CGM_MUX_6_CSS_CS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_CS_SHIFT)) & MC_CGM_MUX_6_CSS_CS_MASK)

#define MC_CGM_MUX_6_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_6_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_6_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_6_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_6_CSS_SWTRG_MASK)

#define MC_CGM_MUX_6_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_6_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_6_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_6_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_6_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_6_DC_0 - Clock Mux 6 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_6_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_6_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_6_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_6_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DC_0_DIV_SHIFT)) & MC_CGM_MUX_6_DC_0_DIV_MASK)

#define MC_CGM_MUX_6_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_6_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_6_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_6_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DC_0_DE_SHIFT)) & MC_CGM_MUX_6_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_6_DC_1 - Clock Mux 6 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_6_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_6_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_6_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_6_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DC_1_DIV_SHIFT)) & MC_CGM_MUX_6_DC_1_DIV_MASK)

#define MC_CGM_MUX_6_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_6_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_6_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_6_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DC_1_DE_SHIFT)) & MC_CGM_MUX_6_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_6_DIV_UPD_STAT - Clock Mux 6 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_7_CSC - Clock Mux 7 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_7_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_7_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_7_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_7_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_7_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_7_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_7_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_7_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_7_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_7_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_7_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_7_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_7_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_7_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_7_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_7_CSS - Clock Mux 7 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_7_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_7_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_7_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_7_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_7_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_7_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_7_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_7_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_7_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_7_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_7_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_7_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_7_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_7_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SWIP_SHIFT)) & MC_CGM_MUX_7_CSS_SWIP_MASK)

#define MC_CGM_MUX_7_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_7_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_7_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_7_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_7_CSS_SWTRG_MASK)

#define MC_CGM_MUX_7_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_7_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_7_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_7_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_7_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_7_DC_0 - Clock Mux 7 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_7_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_7_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_7_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_7_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_0_DIV_SHIFT)) & MC_CGM_MUX_7_DC_0_DIV_MASK)

#define MC_CGM_MUX_7_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_7_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_7_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_7_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_0_DE_SHIFT)) & MC_CGM_MUX_7_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_7_DC_1 - Clock Mux 7 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_7_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_7_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_7_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_7_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_1_DIV_SHIFT)) & MC_CGM_MUX_7_DC_1_DIV_MASK)

#define MC_CGM_MUX_7_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_7_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_7_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_7_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_1_DE_SHIFT)) & MC_CGM_MUX_7_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_7_DC_2 - Clock Mux 7 Divider 2 Control Register */
/*! @{ */

#define MC_CGM_MUX_7_DC_2_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_7_DC_2_DIV_SHIFT (16U)
#define MC_CGM_MUX_7_DC_2_DIV_WIDTH (8U)
#define MC_CGM_MUX_7_DC_2_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_2_DIV_SHIFT)) & MC_CGM_MUX_7_DC_2_DIV_MASK)

#define MC_CGM_MUX_7_DC_2_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_7_DC_2_DE_SHIFT (31U)
#define MC_CGM_MUX_7_DC_2_DE_WIDTH (1U)
#define MC_CGM_MUX_7_DC_2_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_2_DE_SHIFT)) & MC_CGM_MUX_7_DC_2_DE_MASK)
/*! @} */

/*! @name MUX_7_DIV_TRIG_CTRL - Clock Mux 7 Divider Trigger Control Register */
/*! @{ */

#define MC_CGM_MUX_7_DIV_TRIG_CTRL_TCTL_MASK  (0x1U)
#define MC_CGM_MUX_7_DIV_TRIG_CTRL_TCTL_SHIFT (0U)
#define MC_CGM_MUX_7_DIV_TRIG_CTRL_TCTL_WIDTH (1U)
#define MC_CGM_MUX_7_DIV_TRIG_CTRL_TCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DIV_TRIG_CTRL_TCTL_SHIFT)) & \
        MC_CGM_MUX_7_DIV_TRIG_CTRL_TCTL_MASK)

#define MC_CGM_MUX_7_DIV_TRIG_CTRL_HHEN_MASK  (0x80000000U)
#define MC_CGM_MUX_7_DIV_TRIG_CTRL_HHEN_SHIFT (31U)
#define MC_CGM_MUX_7_DIV_TRIG_CTRL_HHEN_WIDTH (1U)
#define MC_CGM_MUX_7_DIV_TRIG_CTRL_HHEN(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DIV_TRIG_CTRL_HHEN_SHIFT)) & \
        MC_CGM_MUX_7_DIV_TRIG_CTRL_HHEN_MASK)
/*! @} */

/*! @name MUX_7_DIV_TRIG - Clock Mux 7 Divider Trigger Register */
/*! @{ */

#define MC_CGM_MUX_7_DIV_TRIG_TRIGGER_MASK  (0xFFFFFFFFU)
#define MC_CGM_MUX_7_DIV_TRIG_TRIGGER_SHIFT (0U)
#define MC_CGM_MUX_7_DIV_TRIG_TRIGGER_WIDTH (32U)
#define MC_CGM_MUX_7_DIV_TRIG_TRIGGER(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DIV_TRIG_TRIGGER_SHIFT)) & \
        MC_CGM_MUX_7_DIV_TRIG_TRIGGER_MASK)
/*! @} */

/*! @name MUX_7_DIV_UPD_STAT - Clock Mux 7 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_8_CSC - Clock Mux 8 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_8_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_8_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_8_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_8_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_8_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_8_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_8_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_8_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_8_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_8_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_8_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_8_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_8_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_8_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_8_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_8_CSS - Clock Mux 8 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_8_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_8_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_8_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_8_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_8_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_8_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_8_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_8_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_8_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_8_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_8_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_8_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_8_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_8_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SWIP_SHIFT)) & MC_CGM_MUX_8_CSS_SWIP_MASK)

#define MC_CGM_MUX_8_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_8_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_8_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_8_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_8_CSS_SWTRG_MASK)

#define MC_CGM_MUX_8_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_8_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_8_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_8_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_8_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_8_DC_0 - Clock Mux 8 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_8_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_8_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_8_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_8_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DC_0_DIV_SHIFT)) & MC_CGM_MUX_8_DC_0_DIV_MASK)

#define MC_CGM_MUX_8_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_8_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_8_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_8_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DC_0_DE_SHIFT)) & MC_CGM_MUX_8_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_8_DC_1 - Clock Mux 8 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_8_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_8_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_8_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_8_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DC_1_DIV_SHIFT)) & MC_CGM_MUX_8_DC_1_DIV_MASK)

#define MC_CGM_MUX_8_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_8_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_8_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_8_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DC_1_DE_SHIFT)) & MC_CGM_MUX_8_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_8_DIV_UPD_STAT - Clock Mux 8 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_9_CSC - Clock Mux 9 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_9_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_9_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_9_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_9_CSC_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_9_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_9_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_9_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_9_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_9_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_9_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_9_CSC_SELCTL_MASK                                                        \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_9_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_9_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_9_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_9_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                         widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_9_CSS - Clock Mux 9 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_9_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_9_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_9_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_9_CSS_CLK_SW(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_9_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_9_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_9_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_9_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_9_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_9_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_9_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_9_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_9_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_9_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SWIP_SHIFT)) & MC_CGM_MUX_9_CSS_SWIP_MASK)

#define MC_CGM_MUX_9_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_9_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_9_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_9_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_9_CSS_SWTRG_MASK)

#define MC_CGM_MUX_9_CSS_SELSTAT_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_9_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_9_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_9_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_9_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_9_DC_0 - Clock Mux 9 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_9_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_9_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_9_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_9_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_0_DIV_SHIFT)) & MC_CGM_MUX_9_DC_0_DIV_MASK)

#define MC_CGM_MUX_9_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_9_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_9_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_9_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_0_DE_SHIFT)) & MC_CGM_MUX_9_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_9_DC_1 - Clock Mux 9 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_9_DC_1_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_9_DC_1_DIV_SHIFT (16U)
#define MC_CGM_MUX_9_DC_1_DIV_WIDTH (8U)
#define MC_CGM_MUX_9_DC_1_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_1_DIV_SHIFT)) & MC_CGM_MUX_9_DC_1_DIV_MASK)

#define MC_CGM_MUX_9_DC_1_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_9_DC_1_DE_SHIFT (31U)
#define MC_CGM_MUX_9_DC_1_DE_WIDTH (1U)
#define MC_CGM_MUX_9_DC_1_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_1_DE_SHIFT)) & MC_CGM_MUX_9_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_9_DC_2 - Clock Mux 9 Divider 2 Control Register */
/*! @{ */

#define MC_CGM_MUX_9_DC_2_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_9_DC_2_DIV_SHIFT (16U)
#define MC_CGM_MUX_9_DC_2_DIV_WIDTH (8U)
#define MC_CGM_MUX_9_DC_2_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_2_DIV_SHIFT)) & MC_CGM_MUX_9_DC_2_DIV_MASK)

#define MC_CGM_MUX_9_DC_2_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_9_DC_2_DE_SHIFT (31U)
#define MC_CGM_MUX_9_DC_2_DE_WIDTH (1U)
#define MC_CGM_MUX_9_DC_2_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_2_DE_SHIFT)) & MC_CGM_MUX_9_DC_2_DE_MASK)
/*! @} */

/*! @name MUX_9_DIV_UPD_STAT - Clock Mux 9 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_10_CSC - Clock Mux 10 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_10_CSC_CG_MASK  (0x4U)
#define MC_CGM_MUX_10_CSC_CG_SHIFT (2U)
#define MC_CGM_MUX_10_CSC_CG_WIDTH (1U)
#define MC_CGM_MUX_10_CSC_CG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_CG_SHIFT)) & MC_CGM_MUX_10_CSC_CG_MASK)

#define MC_CGM_MUX_10_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_10_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_10_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_10_CSC_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_10_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_10_CSC_FCG_MASK  (0x8U)
#define MC_CGM_MUX_10_CSC_FCG_SHIFT (3U)
#define MC_CGM_MUX_10_CSC_FCG_WIDTH (1U)
#define MC_CGM_MUX_10_CSC_FCG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_FCG_SHIFT)) & MC_CGM_MUX_10_CSC_FCG_MASK)

#define MC_CGM_MUX_10_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_10_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_10_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_10_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_10_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_10_CSC_SELCTL_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_10_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_10_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_10_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_10_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_10_CSS - Clock Mux 10 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_10_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_10_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_10_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_10_CSS_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_10_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_10_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_10_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_10_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_10_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_10_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_10_CSS_GRIP_MASK  (0x10000U)
#define MC_CGM_MUX_10_CSS_GRIP_SHIFT (16U)
#define MC_CGM_MUX_10_CSS_GRIP_WIDTH (1U)
#define MC_CGM_MUX_10_CSS_GRIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_GRIP_SHIFT)) & MC_CGM_MUX_10_CSS_GRIP_MASK)

#define MC_CGM_MUX_10_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_10_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_10_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_10_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SWIP_SHIFT)) & MC_CGM_MUX_10_CSS_SWIP_MASK)

#define MC_CGM_MUX_10_CSS_CS_MASK  (0x20000U)
#define MC_CGM_MUX_10_CSS_CS_SHIFT (17U)
#define MC_CGM_MUX_10_CSS_CS_WIDTH (1U)
#define MC_CGM_MUX_10_CSS_CS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_CS_SHIFT)) & MC_CGM_MUX_10_CSS_CS_MASK)

#define MC_CGM_MUX_10_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_10_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_10_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_10_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_10_CSS_SWTRG_MASK)

#define MC_CGM_MUX_10_CSS_SELSTAT_MASK                                                      \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_10_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_10_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_10_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_10_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                           widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_10_DC_0 - Clock Mux 10 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_10_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_10_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_10_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_10_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_DC_0_DIV_SHIFT)) & MC_CGM_MUX_10_DC_0_DIV_MASK)

#define MC_CGM_MUX_10_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_10_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_10_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_10_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_DC_0_DE_SHIFT)) & MC_CGM_MUX_10_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_10_DIV_UPD_STAT - Clock Mux 10 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_11_CSC - Clock Mux 11 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_11_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_11_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_11_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_11_CSC_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSC_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_11_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_11_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_11_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_11_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_11_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_11_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_11_CSC_SELCTL_MASK                                                       \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_11_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_11_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_11_CSC_SELCTL(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSC_SELCTL_SHIFT)) &                            \
        MC_CGM_MUX_11_CSC_SELCTL_MASK) /* Merged from fields with different position or width, of \
                                          widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_11_CSS - Clock Mux 11 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_11_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_11_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_11_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_11_CSS_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_11_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_11_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_11_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_11_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_11_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_11_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_11_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_11_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_11_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_11_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_SWIP_SHIFT)) & MC_CGM_MUX_11_CSS_SWIP_MASK)

#define MC_CGM_MUX_11_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_11_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_11_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_11_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_11_CSS_SWTRG_MASK)

#define MC_CGM_MUX_11_CSS_SELSTAT_MASK                                                      \
    (0x3F000000U) /* Merged from fields with different position or width, of widths (5, 6), \
                     largest definition used */
#define MC_CGM_MUX_11_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_11_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_11_CSS_SELSTAT(x)                                                               \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_SELSTAT_SHIFT)) &                            \
        MC_CGM_MUX_11_CSS_SELSTAT_MASK) /* Merged from fields with different position or width, of \
                                           widths (5, 6), largest definition used */
/*! @} */

/*! @name MUX_11_DC_0 - Clock Mux 11 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_11_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_11_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_11_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_11_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_DC_0_DIV_SHIFT)) & MC_CGM_MUX_11_DC_0_DIV_MASK)

#define MC_CGM_MUX_11_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_11_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_11_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_11_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_DC_0_DE_SHIFT)) & MC_CGM_MUX_11_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_11_DIV_UPD_STAT - Clock Mux 11 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_12_CSC - Clock Mux 12 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_12_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_12_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_12_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_12_CSC_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSC_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_12_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_12_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_12_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_12_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_12_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_12_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_12_CSC_SELCTL_MASK  (0x3F000000U)
#define MC_CGM_MUX_12_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_12_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_12_CSC_SELCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSC_SELCTL_SHIFT)) & \
        MC_CGM_MUX_12_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_12_CSS - Clock Mux 12 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_12_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_12_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_12_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_12_CSS_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSS_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_12_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_12_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_12_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_12_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_12_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_12_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_12_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_12_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_12_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_12_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSS_SWIP_SHIFT)) & MC_CGM_MUX_12_CSS_SWIP_MASK)

#define MC_CGM_MUX_12_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_12_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_12_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_12_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_12_CSS_SWTRG_MASK)

#define MC_CGM_MUX_12_CSS_SELSTAT_MASK  (0x3F000000U)
#define MC_CGM_MUX_12_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_12_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_12_CSS_SELSTAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_CSS_SELSTAT_SHIFT)) & \
        MC_CGM_MUX_12_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_12_DC_0 - Clock Mux 12 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_12_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_12_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_12_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_12_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_DC_0_DIV_SHIFT)) & MC_CGM_MUX_12_DC_0_DIV_MASK)

#define MC_CGM_MUX_12_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_12_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_12_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_12_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_DC_0_DE_SHIFT)) & MC_CGM_MUX_12_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_12_DIV_UPD_STAT - Clock Mux 12 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_12_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_12_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_12_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_12_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_12_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_12_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_13_CSC - Clock Mux 13 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_13_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_13_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_13_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_13_CSC_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSC_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_13_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_13_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_13_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_13_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_13_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_13_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_13_CSC_SELCTL_MASK  (0x3F000000U)
#define MC_CGM_MUX_13_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_13_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_13_CSC_SELCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSC_SELCTL_SHIFT)) & \
        MC_CGM_MUX_13_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_13_CSS - Clock Mux 13 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_13_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_13_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_13_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_13_CSS_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSS_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_13_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_13_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_13_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_13_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_13_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_13_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_13_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_13_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_13_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_13_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSS_SWIP_SHIFT)) & MC_CGM_MUX_13_CSS_SWIP_MASK)

#define MC_CGM_MUX_13_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_13_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_13_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_13_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_13_CSS_SWTRG_MASK)

#define MC_CGM_MUX_13_CSS_SELSTAT_MASK  (0x3F000000U)
#define MC_CGM_MUX_13_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_13_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_13_CSS_SELSTAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_13_CSS_SELSTAT_SHIFT)) & \
        MC_CGM_MUX_13_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_14_CSC - Clock Mux 14 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_14_CSC_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_14_CSC_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_14_CSC_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_14_CSC_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSC_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_14_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_14_CSC_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_14_CSC_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_14_CSC_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_14_CSC_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSC_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_14_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_14_CSC_SELCTL_MASK  (0x3F000000U)
#define MC_CGM_MUX_14_CSC_SELCTL_SHIFT (24U)
#define MC_CGM_MUX_14_CSC_SELCTL_WIDTH (6U)
#define MC_CGM_MUX_14_CSC_SELCTL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSC_SELCTL_SHIFT)) & \
        MC_CGM_MUX_14_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_14_CSS - Clock Mux 14 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_14_CSS_CLK_SW_MASK  (0x4U)
#define MC_CGM_MUX_14_CSS_CLK_SW_SHIFT (2U)
#define MC_CGM_MUX_14_CSS_CLK_SW_WIDTH (1U)
#define MC_CGM_MUX_14_CSS_CLK_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSS_CLK_SW_SHIFT)) & \
        MC_CGM_MUX_14_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_14_CSS_SAFE_SW_MASK  (0x8U)
#define MC_CGM_MUX_14_CSS_SAFE_SW_SHIFT (3U)
#define MC_CGM_MUX_14_CSS_SAFE_SW_WIDTH (1U)
#define MC_CGM_MUX_14_CSS_SAFE_SW(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSS_SAFE_SW_SHIFT)) & \
        MC_CGM_MUX_14_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_14_CSS_SWIP_MASK  (0x10000U)
#define MC_CGM_MUX_14_CSS_SWIP_SHIFT (16U)
#define MC_CGM_MUX_14_CSS_SWIP_WIDTH (1U)
#define MC_CGM_MUX_14_CSS_SWIP(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSS_SWIP_SHIFT)) & MC_CGM_MUX_14_CSS_SWIP_MASK)

#define MC_CGM_MUX_14_CSS_SWTRG_MASK  (0xE0000U)
#define MC_CGM_MUX_14_CSS_SWTRG_SHIFT (17U)
#define MC_CGM_MUX_14_CSS_SWTRG_WIDTH (3U)
#define MC_CGM_MUX_14_CSS_SWTRG(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_14_CSS_SWTRG_MASK)

#define MC_CGM_MUX_14_CSS_SELSTAT_MASK  (0x3F000000U)
#define MC_CGM_MUX_14_CSS_SELSTAT_SHIFT (24U)
#define MC_CGM_MUX_14_CSS_SELSTAT_WIDTH (6U)
#define MC_CGM_MUX_14_CSS_SELSTAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_CSS_SELSTAT_SHIFT)) & \
        MC_CGM_MUX_14_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_14_DC_0 - Clock Mux 14 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_14_DC_0_DIV_MASK  (0xFF0000U)
#define MC_CGM_MUX_14_DC_0_DIV_SHIFT (16U)
#define MC_CGM_MUX_14_DC_0_DIV_WIDTH (8U)
#define MC_CGM_MUX_14_DC_0_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_DC_0_DIV_SHIFT)) & MC_CGM_MUX_14_DC_0_DIV_MASK)

#define MC_CGM_MUX_14_DC_0_DE_MASK  (0x80000000U)
#define MC_CGM_MUX_14_DC_0_DE_SHIFT (31U)
#define MC_CGM_MUX_14_DC_0_DE_WIDTH (1U)
#define MC_CGM_MUX_14_DC_0_DE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_DC_0_DE_SHIFT)) & MC_CGM_MUX_14_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_14_DIV_UPD_STAT - Clock Mux 14 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_14_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_14_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_14_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_14_DIV_UPD_STAT_DIV_STAT(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_14_DIV_UPD_STAT_DIV_STAT_SHIFT)) & \
        MC_CGM_MUX_14_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MC_CGM_Register_Masks */

/*!
 * @}
 */ /* end of group MC_CGM_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_MC_CGM_H_) */
