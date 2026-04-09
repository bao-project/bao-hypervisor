/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_SIUL2.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_SIUL2
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
#if !defined(S32Z2_SIUL2_H_) /* Check if memory map has not been already included */
#define S32Z2_SIUL2_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SIUL2 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIUL2_Peripheral_Access_Layer SIUL2 Peripheral Access Layer
 * @{
 */

/** SIUL2 - Size of Registers Arrays */
#define SIUL2_IFMCR_COUNT  20u
#define SIUL2_MSCR_COUNT   504u
#define SIUL2_IMCR_COUNT   496u
#define SIUL2_MPGPDO_COUNT 11u

/** SIUL2 - Register Layout Typedef */
typedef struct {
    uint8_t RESERVED_0[4];
    __I uint32_t MIDR1;   /**< SIUL2 MCU ID 1, offset: 0x4, available only on: SIUL2_4 (missing on
                             SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint32_t MIDR2;   /**< SIUL2 MCU ID 2, offset: 0x8, available only on: SIUL2_4 (missing on
                             SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    uint8_t RESERVED_1[4];
    __IO uint32_t DISR0;  /**< SIUL2 DMA/Interrupt Status Flag 0, offset: 0x10 */
    uint8_t RESERVED_2[4];
    __IO uint32_t DIRER0; /**< SIUL2 DMA/Interrupt Request Enable 0, offset: 0x18 */
    uint8_t RESERVED_3[4];
    __IO uint32_t DIRSR0; /**< SIUL2 DMA/Interrupt Request Select 0, offset: 0x20 */
    uint8_t RESERVED_4[4];
    __IO uint32_t IREER0; /**< SIUL2 Interrupt Rising-Edge Event Enable 0, offset: 0x28 */
    uint8_t RESERVED_5[4];
    __IO uint32_t IFEER0; /**< SIUL2 Interrupt Falling-Edge Event Enable 0, offset: 0x30 */
    uint8_t RESERVED_6[4];
    __IO uint32_t IFER0;  /**< SIUL2 Interrupt Filter Enable 0, offset: 0x38 */
    uint8_t RESERVED_7[4];
    __IO uint32_t IFMCR[SIUL2_IFMCR_COUNT]; /**< SIUL2 Interrupt Filter Maximum Counter, array
                                               offset: 0x40, array step: 0x4, irregular array, not
                                               all indices are valid */
    uint8_t RESERVED_8[48];
    __IO uint32_t IFCPR; /**< SIUL2 Interrupt Filter Clock Prescaler, offset: 0xC0 */
    uint8_t RESERVED_9[316];
    __I uint32_t MIDR3;  /**< SIUL2 MCU ID 3, offset: 0x200, available only on: SIUL2_4 (missing on
                            SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint32_t MIDR4;  /**< SIUL2 MCU ID 4, offset: 0x204, available only on: SIUL2_4 (missing on
                            SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    uint8_t RESERVED_10[56];
    __IO uint32_t MSCR[SIUL2_MSCR_COUNT]; /**< SIUL2 Multiplexed Signal Configuration Register,
                                             array offset: 0x240, array step: 0x4, irregular array,
                                             not all indices are valid */
    uint8_t RESERVED_11[32];
    __IO uint32_t IMCR[SIUL2_IMCR_COUNT]; /**< SIUL2 Input Multiplexed Signal Configuration, array
                                             offset: 0xA40, array step: 0x4, irregular array, not
                                             all indices are valid */
    uint8_t RESERVED_12[256];
    __IO uint8_t GPDO3;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1300, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO2;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1301, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO1;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1302, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO0;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1303, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO7;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1304, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO6;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1305, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO5;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1306, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO4;  /**< SIUL2 GPIO Pad Data Output, offset: 0x1307, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO11; /**< SIUL2 GPIO Pad Data Output, offset: 0x1308, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO10; /**< SIUL2 GPIO Pad Data Output, offset: 0x1309, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO9;  /**< SIUL2 GPIO Pad Data Output, offset: 0x130A, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO8;  /**< SIUL2 GPIO Pad Data Output, offset: 0x130B, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO15; /**< SIUL2 GPIO Pad Data Output, offset: 0x130C, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO14; /**< SIUL2 GPIO Pad Data Output, offset: 0x130D, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO13; /**< SIUL2 GPIO Pad Data Output, offset: 0x130E, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO12; /**< SIUL2 GPIO Pad Data Output, offset: 0x130F, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO19; /**< SIUL2 GPIO Pad Data Output, offset: 0x1310, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO18; /**< SIUL2 GPIO Pad Data Output, offset: 0x1311, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO17; /**< SIUL2 GPIO Pad Data Output, offset: 0x1312, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO16; /**< SIUL2 GPIO Pad Data Output, offset: 0x1313, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO23; /**< SIUL2 GPIO Pad Data Output, offset: 0x1314, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO22; /**< SIUL2 GPIO Pad Data Output, offset: 0x1315, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO21; /**< SIUL2 GPIO Pad Data Output, offset: 0x1316, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO20; /**< SIUL2 GPIO Pad Data Output, offset: 0x1317, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO27; /**< SIUL2 GPIO Pad Data Output, offset: 0x1318, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO26; /**< SIUL2 GPIO Pad Data Output, offset: 0x1319, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO25; /**< SIUL2 GPIO Pad Data Output, offset: 0x131A, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO24; /**< SIUL2 GPIO Pad Data Output, offset: 0x131B, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO31; /**< SIUL2 GPIO Pad Data Output, offset: 0x131C, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO30; /**< SIUL2 GPIO Pad Data Output, offset: 0x131D, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO29; /**< SIUL2 GPIO Pad Data Output, offset: 0x131E, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO28; /**< SIUL2 GPIO Pad Data Output, offset: 0x131F, available only on: SIUL2_0
                            (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO35; /**< SIUL2 GPIO Pad Data Output, offset: 0x1320, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO34; /**< SIUL2 GPIO Pad Data Output, offset: 0x1321, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO33; /**< SIUL2 GPIO Pad Data Output, offset: 0x1322, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO32; /**< SIUL2 GPIO Pad Data Output, offset: 0x1323, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO39; /**< SIUL2 GPIO Pad Data Output, offset: 0x1324, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO38; /**< SIUL2 GPIO Pad Data Output, offset: 0x1325, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO37; /**< SIUL2 GPIO Pad Data Output, offset: 0x1326, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO36; /**< SIUL2 GPIO Pad Data Output, offset: 0x1327, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO43; /**< SIUL2 GPIO Pad Data Output, offset: 0x1328, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO42; /**< SIUL2 GPIO Pad Data Output, offset: 0x1329, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO41; /**< SIUL2 GPIO Pad Data Output, offset: 0x132A, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO40; /**< SIUL2 GPIO Pad Data Output, offset: 0x132B, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO47; /**< SIUL2 GPIO Pad Data Output, offset: 0x132C, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO46; /**< SIUL2 GPIO Pad Data Output, offset: 0x132D, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO45; /**< SIUL2 GPIO Pad Data Output, offset: 0x132E, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO44; /**< SIUL2 GPIO Pad Data Output, offset: 0x132F, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO51; /**< SIUL2 GPIO Pad Data Output, offset: 0x1330, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO50; /**< SIUL2 GPIO Pad Data Output, offset: 0x1331, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO49; /**< SIUL2 GPIO Pad Data Output, offset: 0x1332, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO48; /**< SIUL2 GPIO Pad Data Output, offset: 0x1333, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO55; /**< SIUL2 GPIO Pad Data Output, offset: 0x1334, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO54; /**< SIUL2 GPIO Pad Data Output, offset: 0x1335, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO53; /**< SIUL2 GPIO Pad Data Output, offset: 0x1336, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO52; /**< SIUL2 GPIO Pad Data Output, offset: 0x1337, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO59; /**< SIUL2 GPIO Pad Data Output, offset: 0x1338, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO58; /**< SIUL2 GPIO Pad Data Output, offset: 0x1339, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO57; /**< SIUL2 GPIO Pad Data Output, offset: 0x133A, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO56; /**< SIUL2 GPIO Pad Data Output, offset: 0x133B, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO63; /**< SIUL2 GPIO Pad Data Output, offset: 0x133C, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO62; /**< SIUL2 GPIO Pad Data Output, offset: 0x133D, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO61; /**< SIUL2 GPIO Pad Data Output, offset: 0x133E, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO60; /**< SIUL2 GPIO Pad Data Output, offset: 0x133F, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO67; /**< SIUL2 GPIO Pad Data Output, offset: 0x1340, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO66; /**< SIUL2 GPIO Pad Data Output, offset: 0x1341, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO65; /**< SIUL2 GPIO Pad Data Output, offset: 0x1342, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO64; /**< SIUL2 GPIO Pad Data Output, offset: 0x1343, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO71; /**< SIUL2 GPIO Pad Data Output, offset: 0x1344, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO70; /**< SIUL2 GPIO Pad Data Output, offset: 0x1345, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO69; /**< SIUL2 GPIO Pad Data Output, offset: 0x1346, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO68; /**< SIUL2 GPIO Pad Data Output, offset: 0x1347, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO75; /**< SIUL2 GPIO Pad Data Output, offset: 0x1348, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO74; /**< SIUL2 GPIO Pad Data Output, offset: 0x1349, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO73; /**< SIUL2 GPIO Pad Data Output, offset: 0x134A, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO72; /**< SIUL2 GPIO Pad Data Output, offset: 0x134B, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO79; /**< SIUL2 GPIO Pad Data Output, offset: 0x134C, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO78; /**< SIUL2 GPIO Pad Data Output, offset: 0x134D, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO77; /**< SIUL2 GPIO Pad Data Output, offset: 0x134E, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO76; /**< SIUL2 GPIO Pad Data Output, offset: 0x134F, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO83; /**< SIUL2 GPIO Pad Data Output, offset: 0x1350, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO82; /**< SIUL2 GPIO Pad Data Output, offset: 0x1351, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO81; /**< SIUL2 GPIO Pad Data Output, offset: 0x1352, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO80; /**< SIUL2 GPIO Pad Data Output, offset: 0x1353, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO87; /**< SIUL2 GPIO Pad Data Output, offset: 0x1354, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO86; /**< SIUL2 GPIO Pad Data Output, offset: 0x1355, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO85; /**< SIUL2 GPIO Pad Data Output, offset: 0x1356, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO84; /**< SIUL2 GPIO Pad Data Output, offset: 0x1357, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO91; /**< SIUL2 GPIO Pad Data Output, offset: 0x1358, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO90; /**< SIUL2 GPIO Pad Data Output, offset: 0x1359, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO89; /**< SIUL2 GPIO Pad Data Output, offset: 0x135A, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO88; /**< SIUL2 GPIO Pad Data Output, offset: 0x135B, available only on: SIUL2_1
                            (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO95; /**< SIUL2 GPIO Pad Data Output, offset: 0x135C, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO94; /**< SIUL2 GPIO Pad Data Output, offset: 0x135D, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO93; /**< SIUL2 GPIO Pad Data Output, offset: 0x135E, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO92; /**< SIUL2 GPIO Pad Data Output, offset: 0x135F, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO99; /**< SIUL2 GPIO Pad Data Output, offset: 0x1360, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO98; /**< SIUL2 GPIO Pad Data Output, offset: 0x1361, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO97; /**< SIUL2 GPIO Pad Data Output, offset: 0x1362, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO96; /**< SIUL2 GPIO Pad Data Output, offset: 0x1363, available only on: SIUL2_4
                            (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO103; /**< SIUL2 GPIO Pad Data Output, offset: 0x1364, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO102; /**< SIUL2 GPIO Pad Data Output, offset: 0x1365, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO101; /**< SIUL2 GPIO Pad Data Output, offset: 0x1366, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO100; /**< SIUL2 GPIO Pad Data Output, offset: 0x1367, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO107; /**< SIUL2 GPIO Pad Data Output, offset: 0x1368, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO106; /**< SIUL2 GPIO Pad Data Output, offset: 0x1369, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO105; /**< SIUL2 GPIO Pad Data Output, offset: 0x136A, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO104; /**< SIUL2 GPIO Pad Data Output, offset: 0x136B, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO111; /**< SIUL2 GPIO Pad Data Output, offset: 0x136C, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO110; /**< SIUL2 GPIO Pad Data Output, offset: 0x136D, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO109; /**< SIUL2 GPIO Pad Data Output, offset: 0x136E, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO108; /**< SIUL2 GPIO Pad Data Output, offset: 0x136F, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO115; /**< SIUL2 GPIO Pad Data Output, offset: 0x1370, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO114; /**< SIUL2 GPIO Pad Data Output, offset: 0x1371, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO113; /**< SIUL2 GPIO Pad Data Output, offset: 0x1372, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO112; /**< SIUL2 GPIO Pad Data Output, offset: 0x1373, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO119; /**< SIUL2 GPIO Pad Data Output, offset: 0x1374, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO118; /**< SIUL2 GPIO Pad Data Output, offset: 0x1375, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO117; /**< SIUL2 GPIO Pad Data Output, offset: 0x1376, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO116; /**< SIUL2 GPIO Pad Data Output, offset: 0x1377, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO123; /**< SIUL2 GPIO Pad Data Output, offset: 0x1378, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO122; /**< SIUL2 GPIO Pad Data Output, offset: 0x1379, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO121; /**< SIUL2 GPIO Pad Data Output, offset: 0x137A, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO120; /**< SIUL2 GPIO Pad Data Output, offset: 0x137B, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO127; /**< SIUL2 GPIO Pad Data Output, offset: 0x137C, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO126; /**< SIUL2 GPIO Pad Data Output, offset: 0x137D, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO125; /**< SIUL2 GPIO Pad Data Output, offset: 0x137E, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO124; /**< SIUL2 GPIO Pad Data Output, offset: 0x137F, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO131; /**< SIUL2 GPIO Pad Data Output, offset: 0x1380, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO130; /**< SIUL2 GPIO Pad Data Output, offset: 0x1381, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO129; /**< SIUL2 GPIO Pad Data Output, offset: 0x1382, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO128; /**< SIUL2 GPIO Pad Data Output, offset: 0x1383, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO135; /**< SIUL2 GPIO Pad Data Output, offset: 0x1384, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO134; /**< SIUL2 GPIO Pad Data Output, offset: 0x1385, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO133; /**< SIUL2 GPIO Pad Data Output, offset: 0x1386, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO132; /**< SIUL2 GPIO Pad Data Output, offset: 0x1387, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO139; /**< SIUL2 GPIO Pad Data Output, offset: 0x1388, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO138; /**< SIUL2 GPIO Pad Data Output, offset: 0x1389, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO137; /**< SIUL2 GPIO Pad Data Output, offset: 0x138A, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO136; /**< SIUL2 GPIO Pad Data Output, offset: 0x138B, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO143; /**< SIUL2 GPIO Pad Data Output, offset: 0x138C, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO142; /**< SIUL2 GPIO Pad Data Output, offset: 0x138D, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO141; /**< SIUL2 GPIO Pad Data Output, offset: 0x138E, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO140; /**< SIUL2 GPIO Pad Data Output, offset: 0x138F, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO147; /**< SIUL2 GPIO Pad Data Output, offset: 0x1390, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO146; /**< SIUL2 GPIO Pad Data Output, offset: 0x1391, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO145; /**< SIUL2 GPIO Pad Data Output, offset: 0x1392, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO144; /**< SIUL2 GPIO Pad Data Output, offset: 0x1393, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint8_t GPDO151; /**< SIUL2 GPIO Pad Data Output, offset: 0x1394, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO150; /**< SIUL2 GPIO Pad Data Output, offset: 0x1395, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO149; /**< SIUL2 GPIO Pad Data Output, offset: 0x1396, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO148; /**< SIUL2 GPIO Pad Data Output, offset: 0x1397, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO155; /**< SIUL2 GPIO Pad Data Output, offset: 0x1398, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO154; /**< SIUL2 GPIO Pad Data Output, offset: 0x1399, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO153; /**< SIUL2 GPIO Pad Data Output, offset: 0x139A, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO152; /**< SIUL2 GPIO Pad Data Output, offset: 0x139B, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO159; /**< SIUL2 GPIO Pad Data Output, offset: 0x139C, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO158; /**< SIUL2 GPIO Pad Data Output, offset: 0x139D, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO157; /**< SIUL2 GPIO Pad Data Output, offset: 0x139E, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO156; /**< SIUL2 GPIO Pad Data Output, offset: 0x139F, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO163; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A0, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO162; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A1, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO161; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A2, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO160; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A3, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO167; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A4, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO166; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A5, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO165; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A6, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO164; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A7, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO171; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A8, available only on:
                             SIUL2_0 (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO170; /**< SIUL2 GPIO Pad Data Output, offset: 0x13A9, available only on:
                             SIUL2_0 (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO169; /**< SIUL2 GPIO Pad Data Output, offset: 0x13AA, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __IO uint8_t GPDO168; /**< SIUL2 GPIO Pad Data Output, offset: 0x13AB, available only on:
                             SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    uint8_t RESERVED_13[2];
    __IO uint8_t GPDO173; /**< SIUL2 GPIO Pad Data Output, offset: 0x13AE, available only on:
                             SIUL2_0 (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint8_t GPDO172; /**< SIUL2 GPIO Pad Data Output, offset: 0x13AF, available only on:
                             SIUL2_0 (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    uint8_t RESERVED_14[336];
    __I uint8_t GPDI3;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1500, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI2;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1501, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI1;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1502, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI0;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1503, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI7;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1504, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI6;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1505, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI5;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1506, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI4;    /**< SIUL2 GPIO Pad Data Input, offset: 0x1507, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI11;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1508, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI10;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1509, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI9;    /**< SIUL2 GPIO Pad Data Input, offset: 0x150A, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI8;    /**< SIUL2 GPIO Pad Data Input, offset: 0x150B, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI15;   /**< SIUL2 GPIO Pad Data Input, offset: 0x150C, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI14;   /**< SIUL2 GPIO Pad Data Input, offset: 0x150D, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI13;   /**< SIUL2 GPIO Pad Data Input, offset: 0x150E, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI12;   /**< SIUL2 GPIO Pad Data Input, offset: 0x150F, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI19;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1510, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI18;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1511, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI17;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1512, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI16;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1513, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI23;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1514, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI22;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1515, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI21;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1516, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI20;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1517, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI27;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1518, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI26;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1519, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI25;   /**< SIUL2 GPIO Pad Data Input, offset: 0x151A, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI24;   /**< SIUL2 GPIO Pad Data Input, offset: 0x151B, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI31;   /**< SIUL2 GPIO Pad Data Input, offset: 0x151C, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI30;   /**< SIUL2 GPIO Pad Data Input, offset: 0x151D, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI29;   /**< SIUL2 GPIO Pad Data Input, offset: 0x151E, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI28;   /**< SIUL2 GPIO Pad Data Input, offset: 0x151F, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI35;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1520, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI34;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1521, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI33;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1522, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI32;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1523, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI39;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1524, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI38;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1525, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI37;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1526, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI36;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1527, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI43;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1528, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI42;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1529, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI41;   /**< SIUL2 GPIO Pad Data Input, offset: 0x152A, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI40;   /**< SIUL2 GPIO Pad Data Input, offset: 0x152B, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI47;   /**< SIUL2 GPIO Pad Data Input, offset: 0x152C, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI46;   /**< SIUL2 GPIO Pad Data Input, offset: 0x152D, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI45;   /**< SIUL2 GPIO Pad Data Input, offset: 0x152E, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI44;   /**< SIUL2 GPIO Pad Data Input, offset: 0x152F, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI51;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1530, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI50;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1531, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI49;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1532, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI48;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1533, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI55;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1534, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI54;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1535, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI53;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1536, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI52;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1537, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI59;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1538, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI58;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1539, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI57;   /**< SIUL2 GPIO Pad Data Input, offset: 0x153A, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI56;   /**< SIUL2 GPIO Pad Data Input, offset: 0x153B, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI63;   /**< SIUL2 GPIO Pad Data Input, offset: 0x153C, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI62;   /**< SIUL2 GPIO Pad Data Input, offset: 0x153D, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI61;   /**< SIUL2 GPIO Pad Data Input, offset: 0x153E, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI60;   /**< SIUL2 GPIO Pad Data Input, offset: 0x153F, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI67;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1540, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI66;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1541, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI65;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1542, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI64;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1543, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI71;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1544, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI70;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1545, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI69;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1546, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI68;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1547, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI75;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1548, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI74;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1549, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI73;   /**< SIUL2 GPIO Pad Data Input, offset: 0x154A, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI72;   /**< SIUL2 GPIO Pad Data Input, offset: 0x154B, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI79;   /**< SIUL2 GPIO Pad Data Input, offset: 0x154C, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI78;   /**< SIUL2 GPIO Pad Data Input, offset: 0x154D, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI77;   /**< SIUL2 GPIO Pad Data Input, offset: 0x154E, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI76;   /**< SIUL2 GPIO Pad Data Input, offset: 0x154F, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI83;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1550, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI82;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1551, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI81;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1552, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI80;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1553, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI87;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1554, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI86;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1555, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI85;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1556, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI84;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1557, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI91;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1558, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI90;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1559, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI89;   /**< SIUL2 GPIO Pad Data Input, offset: 0x155A, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI88;   /**< SIUL2 GPIO Pad Data Input, offset: 0x155B, available only on: SIUL2_1
                             (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI95;   /**< SIUL2 GPIO Pad Data Input, offset: 0x155C, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI94;   /**< SIUL2 GPIO Pad Data Input, offset: 0x155D, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI93;   /**< SIUL2 GPIO Pad Data Input, offset: 0x155E, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI92;   /**< SIUL2 GPIO Pad Data Input, offset: 0x155F, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI99;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1560, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI98;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1561, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI97;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1562, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI96;   /**< SIUL2 GPIO Pad Data Input, offset: 0x1563, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI103;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1564, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI102;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1565, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI101;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1566, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI100;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1567, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI107;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1568, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI106;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1569, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI105;  /**< SIUL2 GPIO Pad Data Input, offset: 0x156A, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI104;  /**< SIUL2 GPIO Pad Data Input, offset: 0x156B, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI111;  /**< SIUL2 GPIO Pad Data Input, offset: 0x156C, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI110;  /**< SIUL2 GPIO Pad Data Input, offset: 0x156D, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI109;  /**< SIUL2 GPIO Pad Data Input, offset: 0x156E, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI108;  /**< SIUL2 GPIO Pad Data Input, offset: 0x156F, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI115;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1570, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI114;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1571, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI113;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1572, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI112;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1573, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI119;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1574, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI118;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1575, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI117;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1576, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI116;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1577, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI123;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1578, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI122;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1579, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI121;  /**< SIUL2 GPIO Pad Data Input, offset: 0x157A, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI120;  /**< SIUL2 GPIO Pad Data Input, offset: 0x157B, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI127;  /**< SIUL2 GPIO Pad Data Input, offset: 0x157C, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI126;  /**< SIUL2 GPIO Pad Data Input, offset: 0x157D, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI125;  /**< SIUL2 GPIO Pad Data Input, offset: 0x157E, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI124;  /**< SIUL2 GPIO Pad Data Input, offset: 0x157F, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI131;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1580, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI130;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1581, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI129;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1582, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI128;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1583, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI135;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1584, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI134;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1585, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI133;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1586, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI132;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1587, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI139;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1588, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI138;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1589, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI137;  /**< SIUL2 GPIO Pad Data Input, offset: 0x158A, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI136;  /**< SIUL2 GPIO Pad Data Input, offset: 0x158B, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI143;  /**< SIUL2 GPIO Pad Data Input, offset: 0x158C, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI142;  /**< SIUL2 GPIO Pad Data Input, offset: 0x158D, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI141;  /**< SIUL2 GPIO Pad Data Input, offset: 0x158E, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI140;  /**< SIUL2 GPIO Pad Data Input, offset: 0x158F, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI147;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1590, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI146;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1591, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI145;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1592, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI144;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1593, available only on: SIUL2_4
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint8_t GPDI151;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1594, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI150;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1595, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI149;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1596, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI148;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1597, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI155;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1598, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI154;  /**< SIUL2 GPIO Pad Data Input, offset: 0x1599, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI153;  /**< SIUL2 GPIO Pad Data Input, offset: 0x159A, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI152;  /**< SIUL2 GPIO Pad Data Input, offset: 0x159B, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI159;  /**< SIUL2 GPIO Pad Data Input, offset: 0x159C, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI158;  /**< SIUL2 GPIO Pad Data Input, offset: 0x159D, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI157;  /**< SIUL2 GPIO Pad Data Input, offset: 0x159E, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI156;  /**< SIUL2 GPIO Pad Data Input, offset: 0x159F, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI163;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A0, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI162;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A1, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI161;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A2, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI160;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A3, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI167;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A4, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI166;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A5, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI165;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A6, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI164;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A7, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI171;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A8, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI170;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15A9, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI169;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15AA, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    __I uint8_t GPDI168;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15AB, available only on: SIUL2_5
                             (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_4) */
    uint8_t RESERVED_15[2];
    __I uint8_t GPDI173;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15AE, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint8_t GPDI172;  /**< SIUL2 GPIO Pad Data Input, offset: 0x15AF, available only on: SIUL2_0
                             (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    uint8_t RESERVED_16[336];
    __IO uint16_t PGPDO1; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1700, available only on:
                             SIUL2_0, SIUL2_1 (missing on SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint16_t PGPDO0; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1702, available only on:
                             SIUL2_0 (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint16_t PGPDO3; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1704, available only on:
                             SIUL2_1 (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint16_t PGPDO2; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1706, available only on:
                             SIUL2_1 (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint16_t PGPDO5; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1708, available only on:
                             SIUL2_1, SIUL2_4 (missing on SIUL2_0, SIUL2_3, SIUL2_5) */
    __IO uint16_t PGPDO4; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x170A, available only on:
                             SIUL2_1 (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __IO uint16_t PGPDO7; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x170C, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint16_t PGPDO6; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x170E, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __IO uint16_t PGPDO9; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1710, available only on:
                             SIUL2_4, SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3) */
    __IO uint16_t PGPDO8; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1712, available only on:
                             SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    uint8_t RESERVED_17[2];
    __IO uint16_t PGPDO10; /**< SIUL2 Parallel GPIO Pad Data Out, offset: 0x1716, available only on:
                              SIUL2_0, SIUL2_5 (missing on SIUL2_1, SIUL2_3, SIUL2_4) */
    uint8_t RESERVED_18[40];
    __I uint16_t PGPDI1;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1740, available only on:
                              SIUL2_0, SIUL2_1 (missing on SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint16_t PGPDI0;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1742, available only on:
                              SIUL2_0 (missing on SIUL2_1, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint16_t PGPDI3;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1744, available only on:
                              SIUL2_1 (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint16_t PGPDI2;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1746, available only on:
                              SIUL2_1 (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint16_t PGPDI5;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1748, available only on:
                              SIUL2_1, SIUL2_4 (missing on SIUL2_0, SIUL2_3, SIUL2_5) */
    __I uint16_t PGPDI4;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x174A, available only on:
                              SIUL2_1 (missing on SIUL2_0, SIUL2_3, SIUL2_4, SIUL2_5) */
    __I uint16_t PGPDI7;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x174C, available only on:
                              SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint16_t PGPDI6;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x174E, available only on:
                              SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    __I uint16_t PGPDI9;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1750, available only on:
                              SIUL2_4, SIUL2_5 (missing on SIUL2_0, SIUL2_1, SIUL2_3) */
    __I uint16_t PGPDI8;   /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1752, available only on:
                              SIUL2_4 (missing on SIUL2_0, SIUL2_1, SIUL2_3, SIUL2_5) */
    uint8_t RESERVED_19[2];
    __I uint16_t PGPDI10;  /**< SIUL2 Parallel GPIO Pad Data In, offset: 0x1756, available only on:
                              SIUL2_0, SIUL2_5 (missing on SIUL2_1, SIUL2_3, SIUL2_4) */
    uint8_t RESERVED_20[40];
    __O uint32_t MPGPDO[SIUL2_MPGPDO_COUNT]; /**< SIUL2 Masked Parallel GPIO Pad Data Out, array
                                                offset: 0x1780, array step: 0x4, irregular array,
                                                not all indices are valid */
} SIUL2_Type, *SIUL2_MemMapPtr;

/** Number of instances of the SIUL2 module. */
#define SIUL2_INSTANCE_COUNT (5u)

/* SIUL2 - Peripheral instance base addresses */
/** Peripheral SIUL2_0 base address */
#define IP_SIUL2_0_BASE      (0x40520000u)
/** Peripheral SIUL2_0 base pointer */
#define IP_SIUL2_0           ((SIUL2_Type*)IP_SIUL2_0_BASE)
/** Peripheral SIUL2_1 base address */
#define IP_SIUL2_1_BASE      (0x40D20000u)
/** Peripheral SIUL2_1 base pointer */
#define IP_SIUL2_1           ((SIUL2_Type*)IP_SIUL2_1_BASE)
/** Peripheral SIUL2_3 base address */
#define IP_SIUL2_3_BASE      (0x41D20000u)
/** Peripheral SIUL2_3 base pointer */
#define IP_SIUL2_3           ((SIUL2_Type*)IP_SIUL2_3_BASE)
/** Peripheral SIUL2_4 base address */
#define IP_SIUL2_4_BASE      (0x42520000u)
/** Peripheral SIUL2_4 base pointer */
#define IP_SIUL2_4           ((SIUL2_Type*)IP_SIUL2_4_BASE)
/** Peripheral SIUL2_5 base address */
#define IP_SIUL2_5_BASE      (0x42D20000u)
/** Peripheral SIUL2_5 base pointer */
#define IP_SIUL2_5           ((SIUL2_Type*)IP_SIUL2_5_BASE)
/** Array initializer of SIUL2 peripheral base addresses */
#define IP_SIUL2_BASE_ADDRS \
    { IP_SIUL2_0_BASE, IP_SIUL2_1_BASE, IP_SIUL2_3_BASE, IP_SIUL2_4_BASE, IP_SIUL2_5_BASE }
/** Array initializer of SIUL2 peripheral base pointers */
#define IP_SIUL2_BASE_PTRS           { IP_SIUL2_0, IP_SIUL2_1, IP_SIUL2_3, IP_SIUL2_4, IP_SIUL2_5 }

/* ----------------------------------------------------------------------------
   -- SIUL2 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIUL2_Register_Masks SIUL2 Register Masks
 * @{
 */

/*! @name MIDR1 - SIUL2 MCU ID 1 */
/*! @{ */

#define SIUL2_MIDR1_MINOR_MASK_MASK  (0xFU)
#define SIUL2_MIDR1_MINOR_MASK_SHIFT (0U)
#define SIUL2_MIDR1_MINOR_MASK_WIDTH (4U)
#define SIUL2_MIDR1_MINOR_MASK(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_MINOR_MASK_SHIFT)) & SIUL2_MIDR1_MINOR_MASK_MASK)

#define SIUL2_MIDR1_MAJOR_MASK_MASK  (0xF0U)
#define SIUL2_MIDR1_MAJOR_MASK_SHIFT (4U)
#define SIUL2_MIDR1_MAJOR_MASK_WIDTH (4U)
#define SIUL2_MIDR1_MAJOR_MASK(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_MAJOR_MASK_SHIFT)) & SIUL2_MIDR1_MAJOR_MASK_MASK)

#define SIUL2_MIDR1_PART_NO_MASK  (0x3FF0000U)
#define SIUL2_MIDR1_PART_NO_SHIFT (16U)
#define SIUL2_MIDR1_PART_NO_WIDTH (10U)
#define SIUL2_MIDR1_PART_NO(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_PART_NO_SHIFT)) & SIUL2_MIDR1_PART_NO_MASK)

#define SIUL2_MIDR1_PRODUCT_LINE_LETTER_MASK  (0xFC000000U)
#define SIUL2_MIDR1_PRODUCT_LINE_LETTER_SHIFT (26U)
#define SIUL2_MIDR1_PRODUCT_LINE_LETTER_WIDTH (6U)
#define SIUL2_MIDR1_PRODUCT_LINE_LETTER(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR1_PRODUCT_LINE_LETTER_SHIFT)) & \
        SIUL2_MIDR1_PRODUCT_LINE_LETTER_MASK)
/*! @} */

/*! @name MIDR2 - SIUL2 MCU ID 2 */
/*! @{ */

#define SIUL2_MIDR2_FLASH_SIZE_CODE_MASK  (0xFFU)
#define SIUL2_MIDR2_FLASH_SIZE_CODE_SHIFT (0U)
#define SIUL2_MIDR2_FLASH_SIZE_CODE_WIDTH (8U)
#define SIUL2_MIDR2_FLASH_SIZE_CODE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_SIZE_CODE_SHIFT)) & \
        SIUL2_MIDR2_FLASH_SIZE_CODE_MASK)

#define SIUL2_MIDR2_FLASH_SIZE_DATA_MASK  (0xF00U)
#define SIUL2_MIDR2_FLASH_SIZE_DATA_SHIFT (8U)
#define SIUL2_MIDR2_FLASH_SIZE_DATA_WIDTH (4U)
#define SIUL2_MIDR2_FLASH_SIZE_DATA(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_SIZE_DATA_SHIFT)) & \
        SIUL2_MIDR2_FLASH_SIZE_DATA_MASK)

#define SIUL2_MIDR2_FLASH_DATA_MASK  (0x3000U)
#define SIUL2_MIDR2_FLASH_DATA_SHIFT (12U)
#define SIUL2_MIDR2_FLASH_DATA_WIDTH (2U)
#define SIUL2_MIDR2_FLASH_DATA(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_DATA_SHIFT)) & SIUL2_MIDR2_FLASH_DATA_MASK)

#define SIUL2_MIDR2_FLASH_CODE_MASK  (0xC000U)
#define SIUL2_MIDR2_FLASH_CODE_SHIFT (14U)
#define SIUL2_MIDR2_FLASH_CODE_WIDTH (2U)
#define SIUL2_MIDR2_FLASH_CODE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FLASH_CODE_SHIFT)) & SIUL2_MIDR2_FLASH_CODE_MASK)

#define SIUL2_MIDR2_FREQUENCY_MASK  (0xF0000U)
#define SIUL2_MIDR2_FREQUENCY_SHIFT (16U)
#define SIUL2_MIDR2_FREQUENCY_WIDTH (4U)
#define SIUL2_MIDR2_FREQUENCY(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_FREQUENCY_SHIFT)) & SIUL2_MIDR2_FREQUENCY_MASK)

#define SIUL2_MIDR2_PACKAGE_MASK  (0x3F00000U)
#define SIUL2_MIDR2_PACKAGE_SHIFT (20U)
#define SIUL2_MIDR2_PACKAGE_WIDTH (6U)
#define SIUL2_MIDR2_PACKAGE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_PACKAGE_SHIFT)) & SIUL2_MIDR2_PACKAGE_MASK)

#define SIUL2_MIDR2_TEMPERATURE_MASK  (0x1C000000U)
#define SIUL2_MIDR2_TEMPERATURE_SHIFT (26U)
#define SIUL2_MIDR2_TEMPERATURE_WIDTH (3U)
#define SIUL2_MIDR2_TEMPERATURE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_TEMPERATURE_SHIFT)) & SIUL2_MIDR2_TEMPERATURE_MASK)

#define SIUL2_MIDR2_TECHNOLOGY_MASK  (0xE0000000U)
#define SIUL2_MIDR2_TECHNOLOGY_SHIFT (29U)
#define SIUL2_MIDR2_TECHNOLOGY_WIDTH (3U)
#define SIUL2_MIDR2_TECHNOLOGY(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR2_TECHNOLOGY_SHIFT)) & SIUL2_MIDR2_TECHNOLOGY_MASK)
/*! @} */

/*! @name DISR0 - SIUL2 DMA/Interrupt Status Flag 0 */
/*! @{ */

#define SIUL2_DISR0_EIF0_MASK  (0x1U)
#define SIUL2_DISR0_EIF0_SHIFT (0U)
#define SIUL2_DISR0_EIF0_WIDTH (1U)
#define SIUL2_DISR0_EIF0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF0_SHIFT)) & SIUL2_DISR0_EIF0_MASK)

#define SIUL2_DISR0_EIF1_MASK  (0x2U)
#define SIUL2_DISR0_EIF1_SHIFT (1U)
#define SIUL2_DISR0_EIF1_WIDTH (1U)
#define SIUL2_DISR0_EIF1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF1_SHIFT)) & SIUL2_DISR0_EIF1_MASK)

#define SIUL2_DISR0_EIF2_MASK  (0x4U)
#define SIUL2_DISR0_EIF2_SHIFT (2U)
#define SIUL2_DISR0_EIF2_WIDTH (1U)
#define SIUL2_DISR0_EIF2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF2_SHIFT)) & SIUL2_DISR0_EIF2_MASK)

#define SIUL2_DISR0_EIF3_MASK  (0x8U)
#define SIUL2_DISR0_EIF3_SHIFT (3U)
#define SIUL2_DISR0_EIF3_WIDTH (1U)
#define SIUL2_DISR0_EIF3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF3_SHIFT)) & SIUL2_DISR0_EIF3_MASK)

#define SIUL2_DISR0_EIF4_MASK  (0x10U)
#define SIUL2_DISR0_EIF4_SHIFT (4U)
#define SIUL2_DISR0_EIF4_WIDTH (1U)
#define SIUL2_DISR0_EIF4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF4_SHIFT)) & SIUL2_DISR0_EIF4_MASK)

#define SIUL2_DISR0_EIF5_MASK  (0x20U)
#define SIUL2_DISR0_EIF5_SHIFT (5U)
#define SIUL2_DISR0_EIF5_WIDTH (1U)
#define SIUL2_DISR0_EIF5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF5_SHIFT)) & SIUL2_DISR0_EIF5_MASK)

#define SIUL2_DISR0_EIF6_MASK  (0x40U)
#define SIUL2_DISR0_EIF6_SHIFT (6U)
#define SIUL2_DISR0_EIF6_WIDTH (1U)
#define SIUL2_DISR0_EIF6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF6_SHIFT)) & SIUL2_DISR0_EIF6_MASK)

#define SIUL2_DISR0_EIF7_MASK  (0x80U)
#define SIUL2_DISR0_EIF7_SHIFT (7U)
#define SIUL2_DISR0_EIF7_WIDTH (1U)
#define SIUL2_DISR0_EIF7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF7_SHIFT)) & SIUL2_DISR0_EIF7_MASK)

#define SIUL2_DISR0_EIF8_MASK  (0x100U)
#define SIUL2_DISR0_EIF8_SHIFT (8U)
#define SIUL2_DISR0_EIF8_WIDTH (1U)
#define SIUL2_DISR0_EIF8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF8_SHIFT)) & SIUL2_DISR0_EIF8_MASK)

#define SIUL2_DISR0_EIF9_MASK  (0x200U)
#define SIUL2_DISR0_EIF9_SHIFT (9U)
#define SIUL2_DISR0_EIF9_WIDTH (1U)
#define SIUL2_DISR0_EIF9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF9_SHIFT)) & SIUL2_DISR0_EIF9_MASK)

#define SIUL2_DISR0_EIF10_MASK  (0x400U)
#define SIUL2_DISR0_EIF10_SHIFT (10U)
#define SIUL2_DISR0_EIF10_WIDTH (1U)
#define SIUL2_DISR0_EIF10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF10_SHIFT)) & SIUL2_DISR0_EIF10_MASK)

#define SIUL2_DISR0_EIF11_MASK  (0x800U)
#define SIUL2_DISR0_EIF11_SHIFT (11U)
#define SIUL2_DISR0_EIF11_WIDTH (1U)
#define SIUL2_DISR0_EIF11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF11_SHIFT)) & SIUL2_DISR0_EIF11_MASK)

#define SIUL2_DISR0_EIF12_MASK  (0x1000U)
#define SIUL2_DISR0_EIF12_SHIFT (12U)
#define SIUL2_DISR0_EIF12_WIDTH (1U)
#define SIUL2_DISR0_EIF12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF12_SHIFT)) & SIUL2_DISR0_EIF12_MASK)

#define SIUL2_DISR0_EIF13_MASK  (0x2000U)
#define SIUL2_DISR0_EIF13_SHIFT (13U)
#define SIUL2_DISR0_EIF13_WIDTH (1U)
#define SIUL2_DISR0_EIF13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF13_SHIFT)) & SIUL2_DISR0_EIF13_MASK)

#define SIUL2_DISR0_EIF14_MASK  (0x4000U)
#define SIUL2_DISR0_EIF14_SHIFT (14U)
#define SIUL2_DISR0_EIF14_WIDTH (1U)
#define SIUL2_DISR0_EIF14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF14_SHIFT)) & SIUL2_DISR0_EIF14_MASK)

#define SIUL2_DISR0_EIF15_MASK  (0x8000U)
#define SIUL2_DISR0_EIF15_SHIFT (15U)
#define SIUL2_DISR0_EIF15_WIDTH (1U)
#define SIUL2_DISR0_EIF15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF15_SHIFT)) & SIUL2_DISR0_EIF15_MASK)

#define SIUL2_DISR0_EIF16_MASK  (0x10000U)
#define SIUL2_DISR0_EIF16_SHIFT (16U)
#define SIUL2_DISR0_EIF16_WIDTH (1U)
#define SIUL2_DISR0_EIF16(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF16_SHIFT)) & SIUL2_DISR0_EIF16_MASK)

#define SIUL2_DISR0_EIF17_MASK  (0x20000U)
#define SIUL2_DISR0_EIF17_SHIFT (17U)
#define SIUL2_DISR0_EIF17_WIDTH (1U)
#define SIUL2_DISR0_EIF17(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF17_SHIFT)) & SIUL2_DISR0_EIF17_MASK)

#define SIUL2_DISR0_EIF18_MASK  (0x40000U)
#define SIUL2_DISR0_EIF18_SHIFT (18U)
#define SIUL2_DISR0_EIF18_WIDTH (1U)
#define SIUL2_DISR0_EIF18(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF18_SHIFT)) & SIUL2_DISR0_EIF18_MASK)

#define SIUL2_DISR0_EIF19_MASK  (0x80000U)
#define SIUL2_DISR0_EIF19_SHIFT (19U)
#define SIUL2_DISR0_EIF19_WIDTH (1U)
#define SIUL2_DISR0_EIF19(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DISR0_EIF19_SHIFT)) & SIUL2_DISR0_EIF19_MASK)
/*! @} */

/*! @name DIRER0 - SIUL2 DMA/Interrupt Request Enable 0 */
/*! @{ */

#define SIUL2_DIRER0_EIRE0_MASK  (0x1U)
#define SIUL2_DIRER0_EIRE0_SHIFT (0U)
#define SIUL2_DIRER0_EIRE0_WIDTH (1U)
#define SIUL2_DIRER0_EIRE0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE0_SHIFT)) & SIUL2_DIRER0_EIRE0_MASK)

#define SIUL2_DIRER0_EIRE1_MASK  (0x2U)
#define SIUL2_DIRER0_EIRE1_SHIFT (1U)
#define SIUL2_DIRER0_EIRE1_WIDTH (1U)
#define SIUL2_DIRER0_EIRE1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE1_SHIFT)) & SIUL2_DIRER0_EIRE1_MASK)

#define SIUL2_DIRER0_EIRE2_MASK  (0x4U)
#define SIUL2_DIRER0_EIRE2_SHIFT (2U)
#define SIUL2_DIRER0_EIRE2_WIDTH (1U)
#define SIUL2_DIRER0_EIRE2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE2_SHIFT)) & SIUL2_DIRER0_EIRE2_MASK)

#define SIUL2_DIRER0_EIRE3_MASK  (0x8U)
#define SIUL2_DIRER0_EIRE3_SHIFT (3U)
#define SIUL2_DIRER0_EIRE3_WIDTH (1U)
#define SIUL2_DIRER0_EIRE3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE3_SHIFT)) & SIUL2_DIRER0_EIRE3_MASK)

#define SIUL2_DIRER0_EIRE4_MASK  (0x10U)
#define SIUL2_DIRER0_EIRE4_SHIFT (4U)
#define SIUL2_DIRER0_EIRE4_WIDTH (1U)
#define SIUL2_DIRER0_EIRE4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE4_SHIFT)) & SIUL2_DIRER0_EIRE4_MASK)

#define SIUL2_DIRER0_EIRE5_MASK  (0x20U)
#define SIUL2_DIRER0_EIRE5_SHIFT (5U)
#define SIUL2_DIRER0_EIRE5_WIDTH (1U)
#define SIUL2_DIRER0_EIRE5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE5_SHIFT)) & SIUL2_DIRER0_EIRE5_MASK)

#define SIUL2_DIRER0_EIRE6_MASK  (0x40U)
#define SIUL2_DIRER0_EIRE6_SHIFT (6U)
#define SIUL2_DIRER0_EIRE6_WIDTH (1U)
#define SIUL2_DIRER0_EIRE6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE6_SHIFT)) & SIUL2_DIRER0_EIRE6_MASK)

#define SIUL2_DIRER0_EIRE7_MASK  (0x80U)
#define SIUL2_DIRER0_EIRE7_SHIFT (7U)
#define SIUL2_DIRER0_EIRE7_WIDTH (1U)
#define SIUL2_DIRER0_EIRE7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE7_SHIFT)) & SIUL2_DIRER0_EIRE7_MASK)

#define SIUL2_DIRER0_EIRE8_MASK  (0x100U)
#define SIUL2_DIRER0_EIRE8_SHIFT (8U)
#define SIUL2_DIRER0_EIRE8_WIDTH (1U)
#define SIUL2_DIRER0_EIRE8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE8_SHIFT)) & SIUL2_DIRER0_EIRE8_MASK)

#define SIUL2_DIRER0_EIRE9_MASK  (0x200U)
#define SIUL2_DIRER0_EIRE9_SHIFT (9U)
#define SIUL2_DIRER0_EIRE9_WIDTH (1U)
#define SIUL2_DIRER0_EIRE9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE9_SHIFT)) & SIUL2_DIRER0_EIRE9_MASK)

#define SIUL2_DIRER0_EIRE10_MASK  (0x400U)
#define SIUL2_DIRER0_EIRE10_SHIFT (10U)
#define SIUL2_DIRER0_EIRE10_WIDTH (1U)
#define SIUL2_DIRER0_EIRE10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE10_SHIFT)) & SIUL2_DIRER0_EIRE10_MASK)

#define SIUL2_DIRER0_EIRE11_MASK  (0x800U)
#define SIUL2_DIRER0_EIRE11_SHIFT (11U)
#define SIUL2_DIRER0_EIRE11_WIDTH (1U)
#define SIUL2_DIRER0_EIRE11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE11_SHIFT)) & SIUL2_DIRER0_EIRE11_MASK)

#define SIUL2_DIRER0_EIRE12_MASK  (0x1000U)
#define SIUL2_DIRER0_EIRE12_SHIFT (12U)
#define SIUL2_DIRER0_EIRE12_WIDTH (1U)
#define SIUL2_DIRER0_EIRE12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE12_SHIFT)) & SIUL2_DIRER0_EIRE12_MASK)

#define SIUL2_DIRER0_EIRE13_MASK  (0x2000U)
#define SIUL2_DIRER0_EIRE13_SHIFT (13U)
#define SIUL2_DIRER0_EIRE13_WIDTH (1U)
#define SIUL2_DIRER0_EIRE13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE13_SHIFT)) & SIUL2_DIRER0_EIRE13_MASK)

#define SIUL2_DIRER0_EIRE14_MASK  (0x4000U)
#define SIUL2_DIRER0_EIRE14_SHIFT (14U)
#define SIUL2_DIRER0_EIRE14_WIDTH (1U)
#define SIUL2_DIRER0_EIRE14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE14_SHIFT)) & SIUL2_DIRER0_EIRE14_MASK)

#define SIUL2_DIRER0_EIRE15_MASK  (0x8000U)
#define SIUL2_DIRER0_EIRE15_SHIFT (15U)
#define SIUL2_DIRER0_EIRE15_WIDTH (1U)
#define SIUL2_DIRER0_EIRE15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE15_SHIFT)) & SIUL2_DIRER0_EIRE15_MASK)

#define SIUL2_DIRER0_EIRE16_MASK  (0x10000U)
#define SIUL2_DIRER0_EIRE16_SHIFT (16U)
#define SIUL2_DIRER0_EIRE16_WIDTH (1U)
#define SIUL2_DIRER0_EIRE16(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE16_SHIFT)) & SIUL2_DIRER0_EIRE16_MASK)

#define SIUL2_DIRER0_EIRE17_MASK  (0x20000U)
#define SIUL2_DIRER0_EIRE17_SHIFT (17U)
#define SIUL2_DIRER0_EIRE17_WIDTH (1U)
#define SIUL2_DIRER0_EIRE17(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE17_SHIFT)) & SIUL2_DIRER0_EIRE17_MASK)

#define SIUL2_DIRER0_EIRE18_MASK  (0x40000U)
#define SIUL2_DIRER0_EIRE18_SHIFT (18U)
#define SIUL2_DIRER0_EIRE18_WIDTH (1U)
#define SIUL2_DIRER0_EIRE18(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE18_SHIFT)) & SIUL2_DIRER0_EIRE18_MASK)

#define SIUL2_DIRER0_EIRE19_MASK  (0x80000U)
#define SIUL2_DIRER0_EIRE19_SHIFT (19U)
#define SIUL2_DIRER0_EIRE19_WIDTH (1U)
#define SIUL2_DIRER0_EIRE19(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRER0_EIRE19_SHIFT)) & SIUL2_DIRER0_EIRE19_MASK)
/*! @} */

/*! @name DIRSR0 - SIUL2 DMA/Interrupt Request Select 0 */
/*! @{ */

#define SIUL2_DIRSR0_DIRSR0_MASK  (0x1U)
#define SIUL2_DIRSR0_DIRSR0_SHIFT (0U)
#define SIUL2_DIRSR0_DIRSR0_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR0_SHIFT)) & SIUL2_DIRSR0_DIRSR0_MASK)

#define SIUL2_DIRSR0_DIRSR1_MASK  (0x2U)
#define SIUL2_DIRSR0_DIRSR1_SHIFT (1U)
#define SIUL2_DIRSR0_DIRSR1_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR1_SHIFT)) & SIUL2_DIRSR0_DIRSR1_MASK)

#define SIUL2_DIRSR0_DIRSR2_MASK  (0x4U)
#define SIUL2_DIRSR0_DIRSR2_SHIFT (2U)
#define SIUL2_DIRSR0_DIRSR2_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR2_SHIFT)) & SIUL2_DIRSR0_DIRSR2_MASK)

#define SIUL2_DIRSR0_DIRSR3_MASK  (0x8U)
#define SIUL2_DIRSR0_DIRSR3_SHIFT (3U)
#define SIUL2_DIRSR0_DIRSR3_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR3_SHIFT)) & SIUL2_DIRSR0_DIRSR3_MASK)

#define SIUL2_DIRSR0_DIRSR4_MASK  (0x10U)
#define SIUL2_DIRSR0_DIRSR4_SHIFT (4U)
#define SIUL2_DIRSR0_DIRSR4_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR4_SHIFT)) & SIUL2_DIRSR0_DIRSR4_MASK)

#define SIUL2_DIRSR0_DIRSR5_MASK  (0x20U)
#define SIUL2_DIRSR0_DIRSR5_SHIFT (5U)
#define SIUL2_DIRSR0_DIRSR5_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR5_SHIFT)) & SIUL2_DIRSR0_DIRSR5_MASK)

#define SIUL2_DIRSR0_DIRSR6_MASK  (0x40U)
#define SIUL2_DIRSR0_DIRSR6_SHIFT (6U)
#define SIUL2_DIRSR0_DIRSR6_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR6_SHIFT)) & SIUL2_DIRSR0_DIRSR6_MASK)

#define SIUL2_DIRSR0_DIRSR7_MASK  (0x80U)
#define SIUL2_DIRSR0_DIRSR7_SHIFT (7U)
#define SIUL2_DIRSR0_DIRSR7_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR7_SHIFT)) & SIUL2_DIRSR0_DIRSR7_MASK)

#define SIUL2_DIRSR0_DIRSR8_MASK  (0x100U)
#define SIUL2_DIRSR0_DIRSR8_SHIFT (8U)
#define SIUL2_DIRSR0_DIRSR8_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR8_SHIFT)) & SIUL2_DIRSR0_DIRSR8_MASK)

#define SIUL2_DIRSR0_DIRSR9_MASK  (0x200U)
#define SIUL2_DIRSR0_DIRSR9_SHIFT (9U)
#define SIUL2_DIRSR0_DIRSR9_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR9_SHIFT)) & SIUL2_DIRSR0_DIRSR9_MASK)

#define SIUL2_DIRSR0_DIRSR10_MASK  (0x400U)
#define SIUL2_DIRSR0_DIRSR10_SHIFT (10U)
#define SIUL2_DIRSR0_DIRSR10_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR10_SHIFT)) & SIUL2_DIRSR0_DIRSR10_MASK)

#define SIUL2_DIRSR0_DIRSR11_MASK  (0x800U)
#define SIUL2_DIRSR0_DIRSR11_SHIFT (11U)
#define SIUL2_DIRSR0_DIRSR11_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR11_SHIFT)) & SIUL2_DIRSR0_DIRSR11_MASK)

#define SIUL2_DIRSR0_DIRSR12_MASK  (0x1000U)
#define SIUL2_DIRSR0_DIRSR12_SHIFT (12U)
#define SIUL2_DIRSR0_DIRSR12_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR12_SHIFT)) & SIUL2_DIRSR0_DIRSR12_MASK)

#define SIUL2_DIRSR0_DIRSR13_MASK  (0x2000U)
#define SIUL2_DIRSR0_DIRSR13_SHIFT (13U)
#define SIUL2_DIRSR0_DIRSR13_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR13_SHIFT)) & SIUL2_DIRSR0_DIRSR13_MASK)

#define SIUL2_DIRSR0_DIRSR14_MASK  (0x4000U)
#define SIUL2_DIRSR0_DIRSR14_SHIFT (14U)
#define SIUL2_DIRSR0_DIRSR14_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR14_SHIFT)) & SIUL2_DIRSR0_DIRSR14_MASK)

#define SIUL2_DIRSR0_DIRSR15_MASK  (0x8000U)
#define SIUL2_DIRSR0_DIRSR15_SHIFT (15U)
#define SIUL2_DIRSR0_DIRSR15_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR15_SHIFT)) & SIUL2_DIRSR0_DIRSR15_MASK)

#define SIUL2_DIRSR0_DIRSR16_MASK  (0x10000U)
#define SIUL2_DIRSR0_DIRSR16_SHIFT (16U)
#define SIUL2_DIRSR0_DIRSR16_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR16(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR16_SHIFT)) & SIUL2_DIRSR0_DIRSR16_MASK)

#define SIUL2_DIRSR0_DIRSR17_MASK  (0x20000U)
#define SIUL2_DIRSR0_DIRSR17_SHIFT (17U)
#define SIUL2_DIRSR0_DIRSR17_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR17(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR17_SHIFT)) & SIUL2_DIRSR0_DIRSR17_MASK)

#define SIUL2_DIRSR0_DIRSR18_MASK  (0x40000U)
#define SIUL2_DIRSR0_DIRSR18_SHIFT (18U)
#define SIUL2_DIRSR0_DIRSR18_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR18(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR18_SHIFT)) & SIUL2_DIRSR0_DIRSR18_MASK)

#define SIUL2_DIRSR0_DIRSR19_MASK  (0x80000U)
#define SIUL2_DIRSR0_DIRSR19_SHIFT (19U)
#define SIUL2_DIRSR0_DIRSR19_WIDTH (1U)
#define SIUL2_DIRSR0_DIRSR19(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_DIRSR0_DIRSR19_SHIFT)) & SIUL2_DIRSR0_DIRSR19_MASK)
/*! @} */

/*! @name IREER0 - SIUL2 Interrupt Rising-Edge Event Enable 0 */
/*! @{ */

#define SIUL2_IREER0_IREE0_MASK  (0x1U)
#define SIUL2_IREER0_IREE0_SHIFT (0U)
#define SIUL2_IREER0_IREE0_WIDTH (1U)
#define SIUL2_IREER0_IREE0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE0_SHIFT)) & SIUL2_IREER0_IREE0_MASK)

#define SIUL2_IREER0_IREE1_MASK  (0x2U)
#define SIUL2_IREER0_IREE1_SHIFT (1U)
#define SIUL2_IREER0_IREE1_WIDTH (1U)
#define SIUL2_IREER0_IREE1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE1_SHIFT)) & SIUL2_IREER0_IREE1_MASK)

#define SIUL2_IREER0_IREE2_MASK  (0x4U)
#define SIUL2_IREER0_IREE2_SHIFT (2U)
#define SIUL2_IREER0_IREE2_WIDTH (1U)
#define SIUL2_IREER0_IREE2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE2_SHIFT)) & SIUL2_IREER0_IREE2_MASK)

#define SIUL2_IREER0_IREE3_MASK  (0x8U)
#define SIUL2_IREER0_IREE3_SHIFT (3U)
#define SIUL2_IREER0_IREE3_WIDTH (1U)
#define SIUL2_IREER0_IREE3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE3_SHIFT)) & SIUL2_IREER0_IREE3_MASK)

#define SIUL2_IREER0_IREE4_MASK  (0x10U)
#define SIUL2_IREER0_IREE4_SHIFT (4U)
#define SIUL2_IREER0_IREE4_WIDTH (1U)
#define SIUL2_IREER0_IREE4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE4_SHIFT)) & SIUL2_IREER0_IREE4_MASK)

#define SIUL2_IREER0_IREE5_MASK  (0x20U)
#define SIUL2_IREER0_IREE5_SHIFT (5U)
#define SIUL2_IREER0_IREE5_WIDTH (1U)
#define SIUL2_IREER0_IREE5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE5_SHIFT)) & SIUL2_IREER0_IREE5_MASK)

#define SIUL2_IREER0_IREE6_MASK  (0x40U)
#define SIUL2_IREER0_IREE6_SHIFT (6U)
#define SIUL2_IREER0_IREE6_WIDTH (1U)
#define SIUL2_IREER0_IREE6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE6_SHIFT)) & SIUL2_IREER0_IREE6_MASK)

#define SIUL2_IREER0_IREE7_MASK  (0x80U)
#define SIUL2_IREER0_IREE7_SHIFT (7U)
#define SIUL2_IREER0_IREE7_WIDTH (1U)
#define SIUL2_IREER0_IREE7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE7_SHIFT)) & SIUL2_IREER0_IREE7_MASK)

#define SIUL2_IREER0_IREE8_MASK  (0x100U)
#define SIUL2_IREER0_IREE8_SHIFT (8U)
#define SIUL2_IREER0_IREE8_WIDTH (1U)
#define SIUL2_IREER0_IREE8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE8_SHIFT)) & SIUL2_IREER0_IREE8_MASK)

#define SIUL2_IREER0_IREE9_MASK  (0x200U)
#define SIUL2_IREER0_IREE9_SHIFT (9U)
#define SIUL2_IREER0_IREE9_WIDTH (1U)
#define SIUL2_IREER0_IREE9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE9_SHIFT)) & SIUL2_IREER0_IREE9_MASK)

#define SIUL2_IREER0_IREE10_MASK  (0x400U)
#define SIUL2_IREER0_IREE10_SHIFT (10U)
#define SIUL2_IREER0_IREE10_WIDTH (1U)
#define SIUL2_IREER0_IREE10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE10_SHIFT)) & SIUL2_IREER0_IREE10_MASK)

#define SIUL2_IREER0_IREE11_MASK  (0x800U)
#define SIUL2_IREER0_IREE11_SHIFT (11U)
#define SIUL2_IREER0_IREE11_WIDTH (1U)
#define SIUL2_IREER0_IREE11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE11_SHIFT)) & SIUL2_IREER0_IREE11_MASK)

#define SIUL2_IREER0_IREE12_MASK  (0x1000U)
#define SIUL2_IREER0_IREE12_SHIFT (12U)
#define SIUL2_IREER0_IREE12_WIDTH (1U)
#define SIUL2_IREER0_IREE12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE12_SHIFT)) & SIUL2_IREER0_IREE12_MASK)

#define SIUL2_IREER0_IREE13_MASK  (0x2000U)
#define SIUL2_IREER0_IREE13_SHIFT (13U)
#define SIUL2_IREER0_IREE13_WIDTH (1U)
#define SIUL2_IREER0_IREE13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE13_SHIFT)) & SIUL2_IREER0_IREE13_MASK)

#define SIUL2_IREER0_IREE14_MASK  (0x4000U)
#define SIUL2_IREER0_IREE14_SHIFT (14U)
#define SIUL2_IREER0_IREE14_WIDTH (1U)
#define SIUL2_IREER0_IREE14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE14_SHIFT)) & SIUL2_IREER0_IREE14_MASK)

#define SIUL2_IREER0_IREE15_MASK  (0x8000U)
#define SIUL2_IREER0_IREE15_SHIFT (15U)
#define SIUL2_IREER0_IREE15_WIDTH (1U)
#define SIUL2_IREER0_IREE15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE15_SHIFT)) & SIUL2_IREER0_IREE15_MASK)

#define SIUL2_IREER0_IREE16_MASK  (0x10000U)
#define SIUL2_IREER0_IREE16_SHIFT (16U)
#define SIUL2_IREER0_IREE16_WIDTH (1U)
#define SIUL2_IREER0_IREE16(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE16_SHIFT)) & SIUL2_IREER0_IREE16_MASK)

#define SIUL2_IREER0_IREE17_MASK  (0x20000U)
#define SIUL2_IREER0_IREE17_SHIFT (17U)
#define SIUL2_IREER0_IREE17_WIDTH (1U)
#define SIUL2_IREER0_IREE17(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE17_SHIFT)) & SIUL2_IREER0_IREE17_MASK)

#define SIUL2_IREER0_IREE18_MASK  (0x40000U)
#define SIUL2_IREER0_IREE18_SHIFT (18U)
#define SIUL2_IREER0_IREE18_WIDTH (1U)
#define SIUL2_IREER0_IREE18(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE18_SHIFT)) & SIUL2_IREER0_IREE18_MASK)

#define SIUL2_IREER0_IREE19_MASK  (0x80000U)
#define SIUL2_IREER0_IREE19_SHIFT (19U)
#define SIUL2_IREER0_IREE19_WIDTH (1U)
#define SIUL2_IREER0_IREE19(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IREER0_IREE19_SHIFT)) & SIUL2_IREER0_IREE19_MASK)
/*! @} */

/*! @name IFEER0 - SIUL2 Interrupt Falling-Edge Event Enable 0 */
/*! @{ */

#define SIUL2_IFEER0_IFEE0_MASK  (0x1U)
#define SIUL2_IFEER0_IFEE0_SHIFT (0U)
#define SIUL2_IFEER0_IFEE0_WIDTH (1U)
#define SIUL2_IFEER0_IFEE0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE0_SHIFT)) & SIUL2_IFEER0_IFEE0_MASK)

#define SIUL2_IFEER0_IFEE1_MASK  (0x2U)
#define SIUL2_IFEER0_IFEE1_SHIFT (1U)
#define SIUL2_IFEER0_IFEE1_WIDTH (1U)
#define SIUL2_IFEER0_IFEE1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE1_SHIFT)) & SIUL2_IFEER0_IFEE1_MASK)

#define SIUL2_IFEER0_IFEE2_MASK  (0x4U)
#define SIUL2_IFEER0_IFEE2_SHIFT (2U)
#define SIUL2_IFEER0_IFEE2_WIDTH (1U)
#define SIUL2_IFEER0_IFEE2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE2_SHIFT)) & SIUL2_IFEER0_IFEE2_MASK)

#define SIUL2_IFEER0_IFEE3_MASK  (0x8U)
#define SIUL2_IFEER0_IFEE3_SHIFT (3U)
#define SIUL2_IFEER0_IFEE3_WIDTH (1U)
#define SIUL2_IFEER0_IFEE3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE3_SHIFT)) & SIUL2_IFEER0_IFEE3_MASK)

#define SIUL2_IFEER0_IFEE4_MASK  (0x10U)
#define SIUL2_IFEER0_IFEE4_SHIFT (4U)
#define SIUL2_IFEER0_IFEE4_WIDTH (1U)
#define SIUL2_IFEER0_IFEE4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE4_SHIFT)) & SIUL2_IFEER0_IFEE4_MASK)

#define SIUL2_IFEER0_IFEE5_MASK  (0x20U)
#define SIUL2_IFEER0_IFEE5_SHIFT (5U)
#define SIUL2_IFEER0_IFEE5_WIDTH (1U)
#define SIUL2_IFEER0_IFEE5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE5_SHIFT)) & SIUL2_IFEER0_IFEE5_MASK)

#define SIUL2_IFEER0_IFEE6_MASK  (0x40U)
#define SIUL2_IFEER0_IFEE6_SHIFT (6U)
#define SIUL2_IFEER0_IFEE6_WIDTH (1U)
#define SIUL2_IFEER0_IFEE6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE6_SHIFT)) & SIUL2_IFEER0_IFEE6_MASK)

#define SIUL2_IFEER0_IFEE7_MASK  (0x80U)
#define SIUL2_IFEER0_IFEE7_SHIFT (7U)
#define SIUL2_IFEER0_IFEE7_WIDTH (1U)
#define SIUL2_IFEER0_IFEE7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE7_SHIFT)) & SIUL2_IFEER0_IFEE7_MASK)

#define SIUL2_IFEER0_IFEE8_MASK  (0x100U)
#define SIUL2_IFEER0_IFEE8_SHIFT (8U)
#define SIUL2_IFEER0_IFEE8_WIDTH (1U)
#define SIUL2_IFEER0_IFEE8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE8_SHIFT)) & SIUL2_IFEER0_IFEE8_MASK)

#define SIUL2_IFEER0_IFEE9_MASK  (0x200U)
#define SIUL2_IFEER0_IFEE9_SHIFT (9U)
#define SIUL2_IFEER0_IFEE9_WIDTH (1U)
#define SIUL2_IFEER0_IFEE9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE9_SHIFT)) & SIUL2_IFEER0_IFEE9_MASK)

#define SIUL2_IFEER0_IFEE10_MASK  (0x400U)
#define SIUL2_IFEER0_IFEE10_SHIFT (10U)
#define SIUL2_IFEER0_IFEE10_WIDTH (1U)
#define SIUL2_IFEER0_IFEE10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE10_SHIFT)) & SIUL2_IFEER0_IFEE10_MASK)

#define SIUL2_IFEER0_IFEE11_MASK  (0x800U)
#define SIUL2_IFEER0_IFEE11_SHIFT (11U)
#define SIUL2_IFEER0_IFEE11_WIDTH (1U)
#define SIUL2_IFEER0_IFEE11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE11_SHIFT)) & SIUL2_IFEER0_IFEE11_MASK)

#define SIUL2_IFEER0_IFEE12_MASK  (0x1000U)
#define SIUL2_IFEER0_IFEE12_SHIFT (12U)
#define SIUL2_IFEER0_IFEE12_WIDTH (1U)
#define SIUL2_IFEER0_IFEE12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE12_SHIFT)) & SIUL2_IFEER0_IFEE12_MASK)

#define SIUL2_IFEER0_IFEE13_MASK  (0x2000U)
#define SIUL2_IFEER0_IFEE13_SHIFT (13U)
#define SIUL2_IFEER0_IFEE13_WIDTH (1U)
#define SIUL2_IFEER0_IFEE13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE13_SHIFT)) & SIUL2_IFEER0_IFEE13_MASK)

#define SIUL2_IFEER0_IFEE14_MASK  (0x4000U)
#define SIUL2_IFEER0_IFEE14_SHIFT (14U)
#define SIUL2_IFEER0_IFEE14_WIDTH (1U)
#define SIUL2_IFEER0_IFEE14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE14_SHIFT)) & SIUL2_IFEER0_IFEE14_MASK)

#define SIUL2_IFEER0_IFEE15_MASK  (0x8000U)
#define SIUL2_IFEER0_IFEE15_SHIFT (15U)
#define SIUL2_IFEER0_IFEE15_WIDTH (1U)
#define SIUL2_IFEER0_IFEE15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE15_SHIFT)) & SIUL2_IFEER0_IFEE15_MASK)

#define SIUL2_IFEER0_IFEE16_MASK  (0x10000U)
#define SIUL2_IFEER0_IFEE16_SHIFT (16U)
#define SIUL2_IFEER0_IFEE16_WIDTH (1U)
#define SIUL2_IFEER0_IFEE16(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE16_SHIFT)) & SIUL2_IFEER0_IFEE16_MASK)

#define SIUL2_IFEER0_IFEE17_MASK  (0x20000U)
#define SIUL2_IFEER0_IFEE17_SHIFT (17U)
#define SIUL2_IFEER0_IFEE17_WIDTH (1U)
#define SIUL2_IFEER0_IFEE17(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE17_SHIFT)) & SIUL2_IFEER0_IFEE17_MASK)

#define SIUL2_IFEER0_IFEE18_MASK  (0x40000U)
#define SIUL2_IFEER0_IFEE18_SHIFT (18U)
#define SIUL2_IFEER0_IFEE18_WIDTH (1U)
#define SIUL2_IFEER0_IFEE18(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE18_SHIFT)) & SIUL2_IFEER0_IFEE18_MASK)

#define SIUL2_IFEER0_IFEE19_MASK  (0x80000U)
#define SIUL2_IFEER0_IFEE19_SHIFT (19U)
#define SIUL2_IFEER0_IFEE19_WIDTH (1U)
#define SIUL2_IFEER0_IFEE19(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFEER0_IFEE19_SHIFT)) & SIUL2_IFEER0_IFEE19_MASK)
/*! @} */

/*! @name IFER0 - SIUL2 Interrupt Filter Enable 0 */
/*! @{ */

#define SIUL2_IFER0_IFE0_MASK  (0x1U)
#define SIUL2_IFER0_IFE0_SHIFT (0U)
#define SIUL2_IFER0_IFE0_WIDTH (1U)
#define SIUL2_IFER0_IFE0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE0_SHIFT)) & SIUL2_IFER0_IFE0_MASK)

#define SIUL2_IFER0_IFE1_MASK  (0x2U)
#define SIUL2_IFER0_IFE1_SHIFT (1U)
#define SIUL2_IFER0_IFE1_WIDTH (1U)
#define SIUL2_IFER0_IFE1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE1_SHIFT)) & SIUL2_IFER0_IFE1_MASK)

#define SIUL2_IFER0_IFE2_MASK  (0x4U)
#define SIUL2_IFER0_IFE2_SHIFT (2U)
#define SIUL2_IFER0_IFE2_WIDTH (1U)
#define SIUL2_IFER0_IFE2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE2_SHIFT)) & SIUL2_IFER0_IFE2_MASK)

#define SIUL2_IFER0_IFE3_MASK  (0x8U)
#define SIUL2_IFER0_IFE3_SHIFT (3U)
#define SIUL2_IFER0_IFE3_WIDTH (1U)
#define SIUL2_IFER0_IFE3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE3_SHIFT)) & SIUL2_IFER0_IFE3_MASK)

#define SIUL2_IFER0_IFE4_MASK  (0x10U)
#define SIUL2_IFER0_IFE4_SHIFT (4U)
#define SIUL2_IFER0_IFE4_WIDTH (1U)
#define SIUL2_IFER0_IFE4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE4_SHIFT)) & SIUL2_IFER0_IFE4_MASK)

#define SIUL2_IFER0_IFE5_MASK  (0x20U)
#define SIUL2_IFER0_IFE5_SHIFT (5U)
#define SIUL2_IFER0_IFE5_WIDTH (1U)
#define SIUL2_IFER0_IFE5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE5_SHIFT)) & SIUL2_IFER0_IFE5_MASK)

#define SIUL2_IFER0_IFE6_MASK  (0x40U)
#define SIUL2_IFER0_IFE6_SHIFT (6U)
#define SIUL2_IFER0_IFE6_WIDTH (1U)
#define SIUL2_IFER0_IFE6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE6_SHIFT)) & SIUL2_IFER0_IFE6_MASK)

#define SIUL2_IFER0_IFE7_MASK  (0x80U)
#define SIUL2_IFER0_IFE7_SHIFT (7U)
#define SIUL2_IFER0_IFE7_WIDTH (1U)
#define SIUL2_IFER0_IFE7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE7_SHIFT)) & SIUL2_IFER0_IFE7_MASK)

#define SIUL2_IFER0_IFE8_MASK  (0x100U)
#define SIUL2_IFER0_IFE8_SHIFT (8U)
#define SIUL2_IFER0_IFE8_WIDTH (1U)
#define SIUL2_IFER0_IFE8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE8_SHIFT)) & SIUL2_IFER0_IFE8_MASK)

#define SIUL2_IFER0_IFE9_MASK  (0x200U)
#define SIUL2_IFER0_IFE9_SHIFT (9U)
#define SIUL2_IFER0_IFE9_WIDTH (1U)
#define SIUL2_IFER0_IFE9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE9_SHIFT)) & SIUL2_IFER0_IFE9_MASK)

#define SIUL2_IFER0_IFE10_MASK  (0x400U)
#define SIUL2_IFER0_IFE10_SHIFT (10U)
#define SIUL2_IFER0_IFE10_WIDTH (1U)
#define SIUL2_IFER0_IFE10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE10_SHIFT)) & SIUL2_IFER0_IFE10_MASK)

#define SIUL2_IFER0_IFE11_MASK  (0x800U)
#define SIUL2_IFER0_IFE11_SHIFT (11U)
#define SIUL2_IFER0_IFE11_WIDTH (1U)
#define SIUL2_IFER0_IFE11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE11_SHIFT)) & SIUL2_IFER0_IFE11_MASK)

#define SIUL2_IFER0_IFE12_MASK  (0x1000U)
#define SIUL2_IFER0_IFE12_SHIFT (12U)
#define SIUL2_IFER0_IFE12_WIDTH (1U)
#define SIUL2_IFER0_IFE12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE12_SHIFT)) & SIUL2_IFER0_IFE12_MASK)

#define SIUL2_IFER0_IFE13_MASK  (0x2000U)
#define SIUL2_IFER0_IFE13_SHIFT (13U)
#define SIUL2_IFER0_IFE13_WIDTH (1U)
#define SIUL2_IFER0_IFE13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE13_SHIFT)) & SIUL2_IFER0_IFE13_MASK)

#define SIUL2_IFER0_IFE14_MASK  (0x4000U)
#define SIUL2_IFER0_IFE14_SHIFT (14U)
#define SIUL2_IFER0_IFE14_WIDTH (1U)
#define SIUL2_IFER0_IFE14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE14_SHIFT)) & SIUL2_IFER0_IFE14_MASK)

#define SIUL2_IFER0_IFE15_MASK  (0x8000U)
#define SIUL2_IFER0_IFE15_SHIFT (15U)
#define SIUL2_IFER0_IFE15_WIDTH (1U)
#define SIUL2_IFER0_IFE15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE15_SHIFT)) & SIUL2_IFER0_IFE15_MASK)

#define SIUL2_IFER0_IFE16_MASK  (0x10000U)
#define SIUL2_IFER0_IFE16_SHIFT (16U)
#define SIUL2_IFER0_IFE16_WIDTH (1U)
#define SIUL2_IFER0_IFE16(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE16_SHIFT)) & SIUL2_IFER0_IFE16_MASK)

#define SIUL2_IFER0_IFE17_MASK  (0x20000U)
#define SIUL2_IFER0_IFE17_SHIFT (17U)
#define SIUL2_IFER0_IFE17_WIDTH (1U)
#define SIUL2_IFER0_IFE17(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE17_SHIFT)) & SIUL2_IFER0_IFE17_MASK)

#define SIUL2_IFER0_IFE18_MASK  (0x40000U)
#define SIUL2_IFER0_IFE18_SHIFT (18U)
#define SIUL2_IFER0_IFE18_WIDTH (1U)
#define SIUL2_IFER0_IFE18(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE18_SHIFT)) & SIUL2_IFER0_IFE18_MASK)

#define SIUL2_IFER0_IFE19_MASK  (0x80000U)
#define SIUL2_IFER0_IFE19_SHIFT (19U)
#define SIUL2_IFER0_IFE19_WIDTH (1U)
#define SIUL2_IFER0_IFE19(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFER0_IFE19_SHIFT)) & SIUL2_IFER0_IFE19_MASK)
/*! @} */

/*! @name IFMCR - SIUL2 Interrupt Filter Maximum Counter */
/*! @{ */

#define SIUL2_IFMCR_MAXCNT_MASK  (0xFU)
#define SIUL2_IFMCR_MAXCNT_SHIFT (0U)
#define SIUL2_IFMCR_MAXCNT_WIDTH (4U)
#define SIUL2_IFMCR_MAXCNT(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFMCR_MAXCNT_SHIFT)) & SIUL2_IFMCR_MAXCNT_MASK)
/*! @} */

/*! @name IFCPR - SIUL2 Interrupt Filter Clock Prescaler */
/*! @{ */

#define SIUL2_IFCPR_IFCP_MASK  (0xFU)
#define SIUL2_IFCPR_IFCP_SHIFT (0U)
#define SIUL2_IFCPR_IFCP_WIDTH (4U)
#define SIUL2_IFCPR_IFCP(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IFCPR_IFCP_SHIFT)) & SIUL2_IFCPR_IFCP_MASK)
/*! @} */

/*! @name MIDR3 - SIUL2 MCU ID 3 */
/*! @{ */

#define SIUL2_MIDR3_SYSTEM_RAM_SIZE_MASK  (0x3FU)
#define SIUL2_MIDR3_SYSTEM_RAM_SIZE_SHIFT (0U)
#define SIUL2_MIDR3_SYSTEM_RAM_SIZE_WIDTH (6U)
#define SIUL2_MIDR3_SYSTEM_RAM_SIZE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_SYSTEM_RAM_SIZE_SHIFT)) & \
        SIUL2_MIDR3_SYSTEM_RAM_SIZE_MASK)

#define SIUL2_MIDR3_PART_NO_LETTER_MASK  (0xFC00U)
#define SIUL2_MIDR3_PART_NO_LETTER_SHIFT (10U)
#define SIUL2_MIDR3_PART_NO_LETTER_WIDTH (6U)
#define SIUL2_MIDR3_PART_NO_LETTER(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_PART_NO_LETTER_SHIFT)) & \
        SIUL2_MIDR3_PART_NO_LETTER_MASK)

#define SIUL2_MIDR3_PRODUCT_FAMILY_NO_MASK  (0x3FF0000U)
#define SIUL2_MIDR3_PRODUCT_FAMILY_NO_SHIFT (16U)
#define SIUL2_MIDR3_PRODUCT_FAMILY_NO_WIDTH (10U)
#define SIUL2_MIDR3_PRODUCT_FAMILY_NO(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_PRODUCT_FAMILY_NO_SHIFT)) & \
        SIUL2_MIDR3_PRODUCT_FAMILY_NO_MASK)

#define SIUL2_MIDR3_PRODUCT_FAMILY_LETTER_MASK  (0xFC000000U)
#define SIUL2_MIDR3_PRODUCT_FAMILY_LETTER_SHIFT (26U)
#define SIUL2_MIDR3_PRODUCT_FAMILY_LETTER_WIDTH (6U)
#define SIUL2_MIDR3_PRODUCT_FAMILY_LETTER(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR3_PRODUCT_FAMILY_LETTER_SHIFT)) & \
        SIUL2_MIDR3_PRODUCT_FAMILY_LETTER_MASK)
/*! @} */

/*! @name MIDR4 - SIUL2 MCU ID 4 */
/*! @{ */

#define SIUL2_MIDR4_AE0_MASK  (0x1U)
#define SIUL2_MIDR4_AE0_SHIFT (0U)
#define SIUL2_MIDR4_AE0_WIDTH (1U)
#define SIUL2_MIDR4_AE0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_AE0_SHIFT)) & SIUL2_MIDR4_AE0_MASK)

#define SIUL2_MIDR4_AE_RC_MASK  (0x2U)
#define SIUL2_MIDR4_AE_RC_SHIFT (1U)
#define SIUL2_MIDR4_AE_RC_WIDTH (1U)
#define SIUL2_MIDR4_AE_RC(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_AE_RC_SHIFT)) & SIUL2_MIDR4_AE_RC_MASK)

#define SIUL2_MIDR4_DIP_MASK  (0x4U)
#define SIUL2_MIDR4_DIP_SHIFT (2U)
#define SIUL2_MIDR4_DIP_WIDTH (1U)
#define SIUL2_MIDR4_DIP(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_DIP_SHIFT)) & SIUL2_MIDR4_DIP_MASK)

#define SIUL2_MIDR4_GTM_MASK  (0x200U)
#define SIUL2_MIDR4_GTM_SHIFT (9U)
#define SIUL2_MIDR4_GTM_WIDTH (1U)
#define SIUL2_MIDR4_GTM(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_GTM_SHIFT)) & SIUL2_MIDR4_GTM_MASK)

#define SIUL2_MIDR4_CANXL_FUNC_MASK  (0x400U)
#define SIUL2_MIDR4_CANXL_FUNC_SHIFT (10U)
#define SIUL2_MIDR4_CANXL_FUNC_WIDTH (1U)
#define SIUL2_MIDR4_CANXL_FUNC(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_CANXL_FUNC_SHIFT)) & SIUL2_MIDR4_CANXL_FUNC_MASK)

#define SIUL2_MIDR4_CANXL_INST_MASK  (0x800U)
#define SIUL2_MIDR4_CANXL_INST_SHIFT (11U)
#define SIUL2_MIDR4_CANXL_INST_WIDTH (1U)
#define SIUL2_MIDR4_CANXL_INST(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_CANXL_INST_SHIFT)) & SIUL2_MIDR4_CANXL_INST_MASK)

#define SIUL2_MIDR4_MCP_MASK  (0x1000U)
#define SIUL2_MIDR4_MCP_SHIFT (12U)
#define SIUL2_MIDR4_MCP_WIDTH (1U)
#define SIUL2_MIDR4_MCP(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_MCP_SHIFT)) & SIUL2_MIDR4_MCP_MASK)

#define SIUL2_MIDR4_HPBF_MASK  (0x2000U)
#define SIUL2_MIDR4_HPBF_SHIFT (13U)
#define SIUL2_MIDR4_HPBF_WIDTH (1U)
#define SIUL2_MIDR4_HPBF(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_HPBF_SHIFT)) & SIUL2_MIDR4_HPBF_MASK)

#define SIUL2_MIDR4_OTA_MASK  (0x4000U)
#define SIUL2_MIDR4_OTA_SHIFT (14U)
#define SIUL2_MIDR4_OTA_WIDTH (1U)
#define SIUL2_MIDR4_OTA(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_OTA_SHIFT)) & SIUL2_MIDR4_OTA_MASK)

#define SIUL2_MIDR4_SERDES_MASK  (0x8000U)
#define SIUL2_MIDR4_SERDES_SHIFT (15U)
#define SIUL2_MIDR4_SERDES_WIDTH (1U)
#define SIUL2_MIDR4_SERDES(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_SERDES_SHIFT)) & SIUL2_MIDR4_SERDES_MASK)

#define SIUL2_MIDR4_COMPUTE_DIE_PART_NUMBER_MASK  (0x3FF0000U)
#define SIUL2_MIDR4_COMPUTE_DIE_PART_NUMBER_SHIFT (16U)
#define SIUL2_MIDR4_COMPUTE_DIE_PART_NUMBER_WIDTH (10U)
#define SIUL2_MIDR4_COMPUTE_DIE_PART_NUMBER(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_COMPUTE_DIE_PART_NUMBER_SHIFT)) & \
        SIUL2_MIDR4_COMPUTE_DIE_PART_NUMBER_MASK)

#define SIUL2_MIDR4_FLASH_CONFIG_MASK  (0x30000000U)
#define SIUL2_MIDR4_FLASH_CONFIG_SHIFT (28U)
#define SIUL2_MIDR4_FLASH_CONFIG_WIDTH (2U)
#define SIUL2_MIDR4_FLASH_CONFIG(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_FLASH_CONFIG_SHIFT)) & \
        SIUL2_MIDR4_FLASH_CONFIG_MASK)

#define SIUL2_MIDR4_FLASH_VENDOR_MASK  (0xC0000000U)
#define SIUL2_MIDR4_FLASH_VENDOR_SHIFT (30U)
#define SIUL2_MIDR4_FLASH_VENDOR_WIDTH (2U)
#define SIUL2_MIDR4_FLASH_VENDOR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MIDR4_FLASH_VENDOR_SHIFT)) & \
        SIUL2_MIDR4_FLASH_VENDOR_MASK)
/*! @} */

/*! @name MSCR - SIUL2 Multiplexed Signal Configuration Register */
/*! @{ */

#define SIUL2_MSCR_SSS_MASK  (0x7U)
#define SIUL2_MSCR_SSS_SHIFT (0U)
#define SIUL2_MSCR_SSS_WIDTH (3U)
#define SIUL2_MSCR_SSS(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SSS_SHIFT)) & SIUL2_MSCR_SSS_MASK)

#define SIUL2_MSCR_SMC_MASK  (0xF0U)
#define SIUL2_MSCR_SMC_SHIFT (4U)
#define SIUL2_MSCR_SMC_WIDTH (4U)
#define SIUL2_MSCR_SMC(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SMC_SHIFT)) & SIUL2_MSCR_SMC_MASK)

#define SIUL2_MSCR_TRC_MASK  (0x100U)
#define SIUL2_MSCR_TRC_SHIFT (8U)
#define SIUL2_MSCR_TRC_WIDTH (1U)
#define SIUL2_MSCR_TRC(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_TRC_SHIFT)) & SIUL2_MSCR_TRC_MASK)

#define SIUL2_MSCR_RCVR_MASK  (0x400U)
#define SIUL2_MSCR_RCVR_SHIFT (10U)
#define SIUL2_MSCR_RCVR_WIDTH (1U)
#define SIUL2_MSCR_RCVR(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_RCVR_SHIFT)) & SIUL2_MSCR_RCVR_MASK)

#define SIUL2_MSCR_CREF_MASK  (0x800U)
#define SIUL2_MSCR_CREF_SHIFT (11U)
#define SIUL2_MSCR_CREF_WIDTH (1U)
#define SIUL2_MSCR_CREF(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_CREF_SHIFT)) & SIUL2_MSCR_CREF_MASK)

#define SIUL2_MSCR_PUS_MASK  (0x1000U)
#define SIUL2_MSCR_PUS_SHIFT (12U)
#define SIUL2_MSCR_PUS_WIDTH (1U)
#define SIUL2_MSCR_PUS(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_PUS_SHIFT)) & SIUL2_MSCR_PUS_MASK)

#define SIUL2_MSCR_PUE_MASK  (0x2000U)
#define SIUL2_MSCR_PUE_SHIFT (13U)
#define SIUL2_MSCR_PUE_WIDTH (1U)
#define SIUL2_MSCR_PUE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_PUE_SHIFT)) & SIUL2_MSCR_PUE_MASK)

#define SIUL2_MSCR_SRE_MASK  (0x1C000U)
#define SIUL2_MSCR_SRE_SHIFT (14U)
#define SIUL2_MSCR_SRE_WIDTH (3U)
#define SIUL2_MSCR_SRE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_SRE_SHIFT)) & SIUL2_MSCR_SRE_MASK)

#define SIUL2_MSCR_RXCB_MASK  (0x20000U)
#define SIUL2_MSCR_RXCB_SHIFT (17U)
#define SIUL2_MSCR_RXCB_WIDTH (1U)
#define SIUL2_MSCR_RXCB(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_RXCB_SHIFT)) & SIUL2_MSCR_RXCB_MASK)

#define SIUL2_MSCR_IBE_MASK  (0x80000U)
#define SIUL2_MSCR_IBE_SHIFT (19U)
#define SIUL2_MSCR_IBE_WIDTH (1U)
#define SIUL2_MSCR_IBE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_IBE_SHIFT)) & SIUL2_MSCR_IBE_MASK)

#define SIUL2_MSCR_ODE_MASK  (0x100000U)
#define SIUL2_MSCR_ODE_SHIFT (20U)
#define SIUL2_MSCR_ODE_WIDTH (1U)
#define SIUL2_MSCR_ODE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_ODE_SHIFT)) & SIUL2_MSCR_ODE_MASK)

#define SIUL2_MSCR_OBE_MASK  (0x200000U)
#define SIUL2_MSCR_OBE_SHIFT (21U)
#define SIUL2_MSCR_OBE_WIDTH (1U)
#define SIUL2_MSCR_OBE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MSCR_OBE_SHIFT)) & SIUL2_MSCR_OBE_MASK)
/*! @} */

/*! @name IMCR - SIUL2 Input Multiplexed Signal Configuration */
/*! @{ */

#define SIUL2_IMCR_SSS_MASK  (0x7U)
#define SIUL2_IMCR_SSS_SHIFT (0U)
#define SIUL2_IMCR_SSS_WIDTH (3U)
#define SIUL2_IMCR_SSS(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_IMCR_SSS_SHIFT)) & SIUL2_IMCR_SSS_MASK)
/*! @} */

/*! @name GPDO3 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO3_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO3_PDO_n_SHIFT (0U)
#define SIUL2_GPDO3_PDO_n_WIDTH (1U)
#define SIUL2_GPDO3_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO3_PDO_n_SHIFT)) & SIUL2_GPDO3_PDO_n_MASK)
/*! @} */

/*! @name GPDO2 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO2_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO2_PDO_n_SHIFT (0U)
#define SIUL2_GPDO2_PDO_n_WIDTH (1U)
#define SIUL2_GPDO2_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO2_PDO_n_SHIFT)) & SIUL2_GPDO2_PDO_n_MASK)
/*! @} */

/*! @name GPDO1 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO1_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO1_PDO_n_SHIFT (0U)
#define SIUL2_GPDO1_PDO_n_WIDTH (1U)
#define SIUL2_GPDO1_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO1_PDO_n_SHIFT)) & SIUL2_GPDO1_PDO_n_MASK)
/*! @} */

/*! @name GPDO0 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO0_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO0_PDO_n_SHIFT (0U)
#define SIUL2_GPDO0_PDO_n_WIDTH (1U)
#define SIUL2_GPDO0_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO0_PDO_n_SHIFT)) & SIUL2_GPDO0_PDO_n_MASK)
/*! @} */

/*! @name GPDO7 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO7_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO7_PDO_n_SHIFT (0U)
#define SIUL2_GPDO7_PDO_n_WIDTH (1U)
#define SIUL2_GPDO7_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO7_PDO_n_SHIFT)) & SIUL2_GPDO7_PDO_n_MASK)
/*! @} */

/*! @name GPDO6 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO6_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO6_PDO_n_SHIFT (0U)
#define SIUL2_GPDO6_PDO_n_WIDTH (1U)
#define SIUL2_GPDO6_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO6_PDO_n_SHIFT)) & SIUL2_GPDO6_PDO_n_MASK)
/*! @} */

/*! @name GPDO5 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO5_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO5_PDO_n_SHIFT (0U)
#define SIUL2_GPDO5_PDO_n_WIDTH (1U)
#define SIUL2_GPDO5_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO5_PDO_n_SHIFT)) & SIUL2_GPDO5_PDO_n_MASK)
/*! @} */

/*! @name GPDO4 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO4_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO4_PDO_n_SHIFT (0U)
#define SIUL2_GPDO4_PDO_n_WIDTH (1U)
#define SIUL2_GPDO4_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO4_PDO_n_SHIFT)) & SIUL2_GPDO4_PDO_n_MASK)
/*! @} */

/*! @name GPDO11 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO11_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO11_PDO_n_SHIFT (0U)
#define SIUL2_GPDO11_PDO_n_WIDTH (1U)
#define SIUL2_GPDO11_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO11_PDO_n_SHIFT)) & SIUL2_GPDO11_PDO_n_MASK)
/*! @} */

/*! @name GPDO10 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO10_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO10_PDO_n_SHIFT (0U)
#define SIUL2_GPDO10_PDO_n_WIDTH (1U)
#define SIUL2_GPDO10_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO10_PDO_n_SHIFT)) & SIUL2_GPDO10_PDO_n_MASK)
/*! @} */

/*! @name GPDO9 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO9_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO9_PDO_n_SHIFT (0U)
#define SIUL2_GPDO9_PDO_n_WIDTH (1U)
#define SIUL2_GPDO9_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO9_PDO_n_SHIFT)) & SIUL2_GPDO9_PDO_n_MASK)
/*! @} */

/*! @name GPDO8 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO8_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO8_PDO_n_SHIFT (0U)
#define SIUL2_GPDO8_PDO_n_WIDTH (1U)
#define SIUL2_GPDO8_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO8_PDO_n_SHIFT)) & SIUL2_GPDO8_PDO_n_MASK)
/*! @} */

/*! @name GPDO15 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO15_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO15_PDO_n_SHIFT (0U)
#define SIUL2_GPDO15_PDO_n_WIDTH (1U)
#define SIUL2_GPDO15_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO15_PDO_n_SHIFT)) & SIUL2_GPDO15_PDO_n_MASK)
/*! @} */

/*! @name GPDO14 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO14_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO14_PDO_n_SHIFT (0U)
#define SIUL2_GPDO14_PDO_n_WIDTH (1U)
#define SIUL2_GPDO14_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO14_PDO_n_SHIFT)) & SIUL2_GPDO14_PDO_n_MASK)
/*! @} */

/*! @name GPDO13 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO13_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO13_PDO_n_SHIFT (0U)
#define SIUL2_GPDO13_PDO_n_WIDTH (1U)
#define SIUL2_GPDO13_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO13_PDO_n_SHIFT)) & SIUL2_GPDO13_PDO_n_MASK)
/*! @} */

/*! @name GPDO12 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO12_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO12_PDO_n_SHIFT (0U)
#define SIUL2_GPDO12_PDO_n_WIDTH (1U)
#define SIUL2_GPDO12_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO12_PDO_n_SHIFT)) & SIUL2_GPDO12_PDO_n_MASK)
/*! @} */

/*! @name GPDO19 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO19_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO19_PDO_n_SHIFT (0U)
#define SIUL2_GPDO19_PDO_n_WIDTH (1U)
#define SIUL2_GPDO19_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO19_PDO_n_SHIFT)) & SIUL2_GPDO19_PDO_n_MASK)
/*! @} */

/*! @name GPDO18 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO18_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO18_PDO_n_SHIFT (0U)
#define SIUL2_GPDO18_PDO_n_WIDTH (1U)
#define SIUL2_GPDO18_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO18_PDO_n_SHIFT)) & SIUL2_GPDO18_PDO_n_MASK)
/*! @} */

/*! @name GPDO17 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO17_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO17_PDO_n_SHIFT (0U)
#define SIUL2_GPDO17_PDO_n_WIDTH (1U)
#define SIUL2_GPDO17_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO17_PDO_n_SHIFT)) & SIUL2_GPDO17_PDO_n_MASK)
/*! @} */

/*! @name GPDO16 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO16_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO16_PDO_n_SHIFT (0U)
#define SIUL2_GPDO16_PDO_n_WIDTH (1U)
#define SIUL2_GPDO16_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO16_PDO_n_SHIFT)) & SIUL2_GPDO16_PDO_n_MASK)
/*! @} */

/*! @name GPDO23 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO23_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO23_PDO_n_SHIFT (0U)
#define SIUL2_GPDO23_PDO_n_WIDTH (1U)
#define SIUL2_GPDO23_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO23_PDO_n_SHIFT)) & SIUL2_GPDO23_PDO_n_MASK)
/*! @} */

/*! @name GPDO22 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO22_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO22_PDO_n_SHIFT (0U)
#define SIUL2_GPDO22_PDO_n_WIDTH (1U)
#define SIUL2_GPDO22_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO22_PDO_n_SHIFT)) & SIUL2_GPDO22_PDO_n_MASK)
/*! @} */

/*! @name GPDO21 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO21_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO21_PDO_n_SHIFT (0U)
#define SIUL2_GPDO21_PDO_n_WIDTH (1U)
#define SIUL2_GPDO21_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO21_PDO_n_SHIFT)) & SIUL2_GPDO21_PDO_n_MASK)
/*! @} */

/*! @name GPDO20 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO20_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO20_PDO_n_SHIFT (0U)
#define SIUL2_GPDO20_PDO_n_WIDTH (1U)
#define SIUL2_GPDO20_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO20_PDO_n_SHIFT)) & SIUL2_GPDO20_PDO_n_MASK)
/*! @} */

/*! @name GPDO27 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO27_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO27_PDO_n_SHIFT (0U)
#define SIUL2_GPDO27_PDO_n_WIDTH (1U)
#define SIUL2_GPDO27_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO27_PDO_n_SHIFT)) & SIUL2_GPDO27_PDO_n_MASK)
/*! @} */

/*! @name GPDO26 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO26_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO26_PDO_n_SHIFT (0U)
#define SIUL2_GPDO26_PDO_n_WIDTH (1U)
#define SIUL2_GPDO26_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO26_PDO_n_SHIFT)) & SIUL2_GPDO26_PDO_n_MASK)
/*! @} */

/*! @name GPDO25 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO25_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO25_PDO_n_SHIFT (0U)
#define SIUL2_GPDO25_PDO_n_WIDTH (1U)
#define SIUL2_GPDO25_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO25_PDO_n_SHIFT)) & SIUL2_GPDO25_PDO_n_MASK)
/*! @} */

/*! @name GPDO24 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO24_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO24_PDO_n_SHIFT (0U)
#define SIUL2_GPDO24_PDO_n_WIDTH (1U)
#define SIUL2_GPDO24_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO24_PDO_n_SHIFT)) & SIUL2_GPDO24_PDO_n_MASK)
/*! @} */

/*! @name GPDO31 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO31_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO31_PDO_n_SHIFT (0U)
#define SIUL2_GPDO31_PDO_n_WIDTH (1U)
#define SIUL2_GPDO31_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO31_PDO_n_SHIFT)) & SIUL2_GPDO31_PDO_n_MASK)
/*! @} */

/*! @name GPDO30 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO30_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO30_PDO_n_SHIFT (0U)
#define SIUL2_GPDO30_PDO_n_WIDTH (1U)
#define SIUL2_GPDO30_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO30_PDO_n_SHIFT)) & SIUL2_GPDO30_PDO_n_MASK)
/*! @} */

/*! @name GPDO29 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO29_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO29_PDO_n_SHIFT (0U)
#define SIUL2_GPDO29_PDO_n_WIDTH (1U)
#define SIUL2_GPDO29_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO29_PDO_n_SHIFT)) & SIUL2_GPDO29_PDO_n_MASK)
/*! @} */

/*! @name GPDO28 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO28_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO28_PDO_n_SHIFT (0U)
#define SIUL2_GPDO28_PDO_n_WIDTH (1U)
#define SIUL2_GPDO28_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO28_PDO_n_SHIFT)) & SIUL2_GPDO28_PDO_n_MASK)
/*! @} */

/*! @name GPDO35 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO35_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO35_PDO_n_SHIFT (0U)
#define SIUL2_GPDO35_PDO_n_WIDTH (1U)
#define SIUL2_GPDO35_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO35_PDO_n_SHIFT)) & SIUL2_GPDO35_PDO_n_MASK)
/*! @} */

/*! @name GPDO34 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO34_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO34_PDO_n_SHIFT (0U)
#define SIUL2_GPDO34_PDO_n_WIDTH (1U)
#define SIUL2_GPDO34_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO34_PDO_n_SHIFT)) & SIUL2_GPDO34_PDO_n_MASK)
/*! @} */

/*! @name GPDO33 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO33_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO33_PDO_n_SHIFT (0U)
#define SIUL2_GPDO33_PDO_n_WIDTH (1U)
#define SIUL2_GPDO33_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO33_PDO_n_SHIFT)) & SIUL2_GPDO33_PDO_n_MASK)
/*! @} */

/*! @name GPDO32 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO32_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO32_PDO_n_SHIFT (0U)
#define SIUL2_GPDO32_PDO_n_WIDTH (1U)
#define SIUL2_GPDO32_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO32_PDO_n_SHIFT)) & SIUL2_GPDO32_PDO_n_MASK)
/*! @} */

/*! @name GPDO39 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO39_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO39_PDO_n_SHIFT (0U)
#define SIUL2_GPDO39_PDO_n_WIDTH (1U)
#define SIUL2_GPDO39_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO39_PDO_n_SHIFT)) & SIUL2_GPDO39_PDO_n_MASK)
/*! @} */

/*! @name GPDO38 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO38_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO38_PDO_n_SHIFT (0U)
#define SIUL2_GPDO38_PDO_n_WIDTH (1U)
#define SIUL2_GPDO38_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO38_PDO_n_SHIFT)) & SIUL2_GPDO38_PDO_n_MASK)
/*! @} */

/*! @name GPDO37 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO37_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO37_PDO_n_SHIFT (0U)
#define SIUL2_GPDO37_PDO_n_WIDTH (1U)
#define SIUL2_GPDO37_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO37_PDO_n_SHIFT)) & SIUL2_GPDO37_PDO_n_MASK)
/*! @} */

/*! @name GPDO36 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO36_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO36_PDO_n_SHIFT (0U)
#define SIUL2_GPDO36_PDO_n_WIDTH (1U)
#define SIUL2_GPDO36_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO36_PDO_n_SHIFT)) & SIUL2_GPDO36_PDO_n_MASK)
/*! @} */

/*! @name GPDO43 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO43_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO43_PDO_n_SHIFT (0U)
#define SIUL2_GPDO43_PDO_n_WIDTH (1U)
#define SIUL2_GPDO43_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO43_PDO_n_SHIFT)) & SIUL2_GPDO43_PDO_n_MASK)
/*! @} */

/*! @name GPDO42 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO42_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO42_PDO_n_SHIFT (0U)
#define SIUL2_GPDO42_PDO_n_WIDTH (1U)
#define SIUL2_GPDO42_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO42_PDO_n_SHIFT)) & SIUL2_GPDO42_PDO_n_MASK)
/*! @} */

/*! @name GPDO41 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO41_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO41_PDO_n_SHIFT (0U)
#define SIUL2_GPDO41_PDO_n_WIDTH (1U)
#define SIUL2_GPDO41_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO41_PDO_n_SHIFT)) & SIUL2_GPDO41_PDO_n_MASK)
/*! @} */

/*! @name GPDO40 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO40_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO40_PDO_n_SHIFT (0U)
#define SIUL2_GPDO40_PDO_n_WIDTH (1U)
#define SIUL2_GPDO40_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO40_PDO_n_SHIFT)) & SIUL2_GPDO40_PDO_n_MASK)
/*! @} */

/*! @name GPDO47 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO47_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO47_PDO_n_SHIFT (0U)
#define SIUL2_GPDO47_PDO_n_WIDTH (1U)
#define SIUL2_GPDO47_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO47_PDO_n_SHIFT)) & SIUL2_GPDO47_PDO_n_MASK)
/*! @} */

/*! @name GPDO46 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO46_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO46_PDO_n_SHIFT (0U)
#define SIUL2_GPDO46_PDO_n_WIDTH (1U)
#define SIUL2_GPDO46_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO46_PDO_n_SHIFT)) & SIUL2_GPDO46_PDO_n_MASK)
/*! @} */

/*! @name GPDO45 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO45_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO45_PDO_n_SHIFT (0U)
#define SIUL2_GPDO45_PDO_n_WIDTH (1U)
#define SIUL2_GPDO45_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO45_PDO_n_SHIFT)) & SIUL2_GPDO45_PDO_n_MASK)
/*! @} */

/*! @name GPDO44 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO44_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO44_PDO_n_SHIFT (0U)
#define SIUL2_GPDO44_PDO_n_WIDTH (1U)
#define SIUL2_GPDO44_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO44_PDO_n_SHIFT)) & SIUL2_GPDO44_PDO_n_MASK)
/*! @} */

/*! @name GPDO51 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO51_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO51_PDO_n_SHIFT (0U)
#define SIUL2_GPDO51_PDO_n_WIDTH (1U)
#define SIUL2_GPDO51_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO51_PDO_n_SHIFT)) & SIUL2_GPDO51_PDO_n_MASK)
/*! @} */

/*! @name GPDO50 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO50_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO50_PDO_n_SHIFT (0U)
#define SIUL2_GPDO50_PDO_n_WIDTH (1U)
#define SIUL2_GPDO50_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO50_PDO_n_SHIFT)) & SIUL2_GPDO50_PDO_n_MASK)
/*! @} */

/*! @name GPDO49 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO49_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO49_PDO_n_SHIFT (0U)
#define SIUL2_GPDO49_PDO_n_WIDTH (1U)
#define SIUL2_GPDO49_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO49_PDO_n_SHIFT)) & SIUL2_GPDO49_PDO_n_MASK)
/*! @} */

/*! @name GPDO48 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO48_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO48_PDO_n_SHIFT (0U)
#define SIUL2_GPDO48_PDO_n_WIDTH (1U)
#define SIUL2_GPDO48_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO48_PDO_n_SHIFT)) & SIUL2_GPDO48_PDO_n_MASK)
/*! @} */

/*! @name GPDO55 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO55_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO55_PDO_n_SHIFT (0U)
#define SIUL2_GPDO55_PDO_n_WIDTH (1U)
#define SIUL2_GPDO55_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO55_PDO_n_SHIFT)) & SIUL2_GPDO55_PDO_n_MASK)
/*! @} */

/*! @name GPDO54 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO54_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO54_PDO_n_SHIFT (0U)
#define SIUL2_GPDO54_PDO_n_WIDTH (1U)
#define SIUL2_GPDO54_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO54_PDO_n_SHIFT)) & SIUL2_GPDO54_PDO_n_MASK)
/*! @} */

/*! @name GPDO53 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO53_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO53_PDO_n_SHIFT (0U)
#define SIUL2_GPDO53_PDO_n_WIDTH (1U)
#define SIUL2_GPDO53_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO53_PDO_n_SHIFT)) & SIUL2_GPDO53_PDO_n_MASK)
/*! @} */

/*! @name GPDO52 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO52_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO52_PDO_n_SHIFT (0U)
#define SIUL2_GPDO52_PDO_n_WIDTH (1U)
#define SIUL2_GPDO52_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO52_PDO_n_SHIFT)) & SIUL2_GPDO52_PDO_n_MASK)
/*! @} */

/*! @name GPDO59 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO59_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO59_PDO_n_SHIFT (0U)
#define SIUL2_GPDO59_PDO_n_WIDTH (1U)
#define SIUL2_GPDO59_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO59_PDO_n_SHIFT)) & SIUL2_GPDO59_PDO_n_MASK)
/*! @} */

/*! @name GPDO58 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO58_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO58_PDO_n_SHIFT (0U)
#define SIUL2_GPDO58_PDO_n_WIDTH (1U)
#define SIUL2_GPDO58_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO58_PDO_n_SHIFT)) & SIUL2_GPDO58_PDO_n_MASK)
/*! @} */

/*! @name GPDO57 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO57_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO57_PDO_n_SHIFT (0U)
#define SIUL2_GPDO57_PDO_n_WIDTH (1U)
#define SIUL2_GPDO57_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO57_PDO_n_SHIFT)) & SIUL2_GPDO57_PDO_n_MASK)
/*! @} */

/*! @name GPDO56 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO56_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO56_PDO_n_SHIFT (0U)
#define SIUL2_GPDO56_PDO_n_WIDTH (1U)
#define SIUL2_GPDO56_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO56_PDO_n_SHIFT)) & SIUL2_GPDO56_PDO_n_MASK)
/*! @} */

/*! @name GPDO63 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO63_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO63_PDO_n_SHIFT (0U)
#define SIUL2_GPDO63_PDO_n_WIDTH (1U)
#define SIUL2_GPDO63_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO63_PDO_n_SHIFT)) & SIUL2_GPDO63_PDO_n_MASK)
/*! @} */

/*! @name GPDO62 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO62_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO62_PDO_n_SHIFT (0U)
#define SIUL2_GPDO62_PDO_n_WIDTH (1U)
#define SIUL2_GPDO62_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO62_PDO_n_SHIFT)) & SIUL2_GPDO62_PDO_n_MASK)
/*! @} */

/*! @name GPDO61 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO61_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO61_PDO_n_SHIFT (0U)
#define SIUL2_GPDO61_PDO_n_WIDTH (1U)
#define SIUL2_GPDO61_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO61_PDO_n_SHIFT)) & SIUL2_GPDO61_PDO_n_MASK)
/*! @} */

/*! @name GPDO60 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO60_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO60_PDO_n_SHIFT (0U)
#define SIUL2_GPDO60_PDO_n_WIDTH (1U)
#define SIUL2_GPDO60_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO60_PDO_n_SHIFT)) & SIUL2_GPDO60_PDO_n_MASK)
/*! @} */

/*! @name GPDO67 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO67_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO67_PDO_n_SHIFT (0U)
#define SIUL2_GPDO67_PDO_n_WIDTH (1U)
#define SIUL2_GPDO67_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO67_PDO_n_SHIFT)) & SIUL2_GPDO67_PDO_n_MASK)
/*! @} */

/*! @name GPDO66 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO66_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO66_PDO_n_SHIFT (0U)
#define SIUL2_GPDO66_PDO_n_WIDTH (1U)
#define SIUL2_GPDO66_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO66_PDO_n_SHIFT)) & SIUL2_GPDO66_PDO_n_MASK)
/*! @} */

/*! @name GPDO65 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO65_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO65_PDO_n_SHIFT (0U)
#define SIUL2_GPDO65_PDO_n_WIDTH (1U)
#define SIUL2_GPDO65_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO65_PDO_n_SHIFT)) & SIUL2_GPDO65_PDO_n_MASK)
/*! @} */

/*! @name GPDO64 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO64_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO64_PDO_n_SHIFT (0U)
#define SIUL2_GPDO64_PDO_n_WIDTH (1U)
#define SIUL2_GPDO64_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO64_PDO_n_SHIFT)) & SIUL2_GPDO64_PDO_n_MASK)
/*! @} */

/*! @name GPDO71 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO71_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO71_PDO_n_SHIFT (0U)
#define SIUL2_GPDO71_PDO_n_WIDTH (1U)
#define SIUL2_GPDO71_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO71_PDO_n_SHIFT)) & SIUL2_GPDO71_PDO_n_MASK)
/*! @} */

/*! @name GPDO70 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO70_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO70_PDO_n_SHIFT (0U)
#define SIUL2_GPDO70_PDO_n_WIDTH (1U)
#define SIUL2_GPDO70_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO70_PDO_n_SHIFT)) & SIUL2_GPDO70_PDO_n_MASK)
/*! @} */

/*! @name GPDO69 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO69_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO69_PDO_n_SHIFT (0U)
#define SIUL2_GPDO69_PDO_n_WIDTH (1U)
#define SIUL2_GPDO69_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO69_PDO_n_SHIFT)) & SIUL2_GPDO69_PDO_n_MASK)
/*! @} */

/*! @name GPDO68 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO68_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO68_PDO_n_SHIFT (0U)
#define SIUL2_GPDO68_PDO_n_WIDTH (1U)
#define SIUL2_GPDO68_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO68_PDO_n_SHIFT)) & SIUL2_GPDO68_PDO_n_MASK)
/*! @} */

/*! @name GPDO75 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO75_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO75_PDO_n_SHIFT (0U)
#define SIUL2_GPDO75_PDO_n_WIDTH (1U)
#define SIUL2_GPDO75_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO75_PDO_n_SHIFT)) & SIUL2_GPDO75_PDO_n_MASK)
/*! @} */

/*! @name GPDO74 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO74_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO74_PDO_n_SHIFT (0U)
#define SIUL2_GPDO74_PDO_n_WIDTH (1U)
#define SIUL2_GPDO74_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO74_PDO_n_SHIFT)) & SIUL2_GPDO74_PDO_n_MASK)
/*! @} */

/*! @name GPDO73 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO73_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO73_PDO_n_SHIFT (0U)
#define SIUL2_GPDO73_PDO_n_WIDTH (1U)
#define SIUL2_GPDO73_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO73_PDO_n_SHIFT)) & SIUL2_GPDO73_PDO_n_MASK)
/*! @} */

/*! @name GPDO72 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO72_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO72_PDO_n_SHIFT (0U)
#define SIUL2_GPDO72_PDO_n_WIDTH (1U)
#define SIUL2_GPDO72_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO72_PDO_n_SHIFT)) & SIUL2_GPDO72_PDO_n_MASK)
/*! @} */

/*! @name GPDO79 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO79_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO79_PDO_n_SHIFT (0U)
#define SIUL2_GPDO79_PDO_n_WIDTH (1U)
#define SIUL2_GPDO79_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO79_PDO_n_SHIFT)) & SIUL2_GPDO79_PDO_n_MASK)
/*! @} */

/*! @name GPDO78 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO78_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO78_PDO_n_SHIFT (0U)
#define SIUL2_GPDO78_PDO_n_WIDTH (1U)
#define SIUL2_GPDO78_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO78_PDO_n_SHIFT)) & SIUL2_GPDO78_PDO_n_MASK)
/*! @} */

/*! @name GPDO77 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO77_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO77_PDO_n_SHIFT (0U)
#define SIUL2_GPDO77_PDO_n_WIDTH (1U)
#define SIUL2_GPDO77_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO77_PDO_n_SHIFT)) & SIUL2_GPDO77_PDO_n_MASK)
/*! @} */

/*! @name GPDO76 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO76_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO76_PDO_n_SHIFT (0U)
#define SIUL2_GPDO76_PDO_n_WIDTH (1U)
#define SIUL2_GPDO76_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO76_PDO_n_SHIFT)) & SIUL2_GPDO76_PDO_n_MASK)
/*! @} */

/*! @name GPDO83 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO83_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO83_PDO_n_SHIFT (0U)
#define SIUL2_GPDO83_PDO_n_WIDTH (1U)
#define SIUL2_GPDO83_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO83_PDO_n_SHIFT)) & SIUL2_GPDO83_PDO_n_MASK)
/*! @} */

/*! @name GPDO82 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO82_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO82_PDO_n_SHIFT (0U)
#define SIUL2_GPDO82_PDO_n_WIDTH (1U)
#define SIUL2_GPDO82_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO82_PDO_n_SHIFT)) & SIUL2_GPDO82_PDO_n_MASK)
/*! @} */

/*! @name GPDO81 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO81_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO81_PDO_n_SHIFT (0U)
#define SIUL2_GPDO81_PDO_n_WIDTH (1U)
#define SIUL2_GPDO81_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO81_PDO_n_SHIFT)) & SIUL2_GPDO81_PDO_n_MASK)
/*! @} */

/*! @name GPDO80 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO80_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO80_PDO_n_SHIFT (0U)
#define SIUL2_GPDO80_PDO_n_WIDTH (1U)
#define SIUL2_GPDO80_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO80_PDO_n_SHIFT)) & SIUL2_GPDO80_PDO_n_MASK)
/*! @} */

/*! @name GPDO87 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO87_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO87_PDO_n_SHIFT (0U)
#define SIUL2_GPDO87_PDO_n_WIDTH (1U)
#define SIUL2_GPDO87_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO87_PDO_n_SHIFT)) & SIUL2_GPDO87_PDO_n_MASK)
/*! @} */

/*! @name GPDO86 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO86_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO86_PDO_n_SHIFT (0U)
#define SIUL2_GPDO86_PDO_n_WIDTH (1U)
#define SIUL2_GPDO86_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO86_PDO_n_SHIFT)) & SIUL2_GPDO86_PDO_n_MASK)
/*! @} */

/*! @name GPDO85 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO85_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO85_PDO_n_SHIFT (0U)
#define SIUL2_GPDO85_PDO_n_WIDTH (1U)
#define SIUL2_GPDO85_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO85_PDO_n_SHIFT)) & SIUL2_GPDO85_PDO_n_MASK)
/*! @} */

/*! @name GPDO84 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO84_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO84_PDO_n_SHIFT (0U)
#define SIUL2_GPDO84_PDO_n_WIDTH (1U)
#define SIUL2_GPDO84_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO84_PDO_n_SHIFT)) & SIUL2_GPDO84_PDO_n_MASK)
/*! @} */

/*! @name GPDO91 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO91_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO91_PDO_n_SHIFT (0U)
#define SIUL2_GPDO91_PDO_n_WIDTH (1U)
#define SIUL2_GPDO91_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO91_PDO_n_SHIFT)) & SIUL2_GPDO91_PDO_n_MASK)
/*! @} */

/*! @name GPDO90 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO90_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO90_PDO_n_SHIFT (0U)
#define SIUL2_GPDO90_PDO_n_WIDTH (1U)
#define SIUL2_GPDO90_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO90_PDO_n_SHIFT)) & SIUL2_GPDO90_PDO_n_MASK)
/*! @} */

/*! @name GPDO89 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO89_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO89_PDO_n_SHIFT (0U)
#define SIUL2_GPDO89_PDO_n_WIDTH (1U)
#define SIUL2_GPDO89_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO89_PDO_n_SHIFT)) & SIUL2_GPDO89_PDO_n_MASK)
/*! @} */

/*! @name GPDO88 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO88_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO88_PDO_n_SHIFT (0U)
#define SIUL2_GPDO88_PDO_n_WIDTH (1U)
#define SIUL2_GPDO88_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO88_PDO_n_SHIFT)) & SIUL2_GPDO88_PDO_n_MASK)
/*! @} */

/*! @name GPDO95 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO95_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO95_PDO_n_SHIFT (0U)
#define SIUL2_GPDO95_PDO_n_WIDTH (1U)
#define SIUL2_GPDO95_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO95_PDO_n_SHIFT)) & SIUL2_GPDO95_PDO_n_MASK)
/*! @} */

/*! @name GPDO94 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO94_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO94_PDO_n_SHIFT (0U)
#define SIUL2_GPDO94_PDO_n_WIDTH (1U)
#define SIUL2_GPDO94_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO94_PDO_n_SHIFT)) & SIUL2_GPDO94_PDO_n_MASK)
/*! @} */

/*! @name GPDO93 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO93_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO93_PDO_n_SHIFT (0U)
#define SIUL2_GPDO93_PDO_n_WIDTH (1U)
#define SIUL2_GPDO93_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO93_PDO_n_SHIFT)) & SIUL2_GPDO93_PDO_n_MASK)
/*! @} */

/*! @name GPDO92 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO92_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO92_PDO_n_SHIFT (0U)
#define SIUL2_GPDO92_PDO_n_WIDTH (1U)
#define SIUL2_GPDO92_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO92_PDO_n_SHIFT)) & SIUL2_GPDO92_PDO_n_MASK)
/*! @} */

/*! @name GPDO99 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO99_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO99_PDO_n_SHIFT (0U)
#define SIUL2_GPDO99_PDO_n_WIDTH (1U)
#define SIUL2_GPDO99_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO99_PDO_n_SHIFT)) & SIUL2_GPDO99_PDO_n_MASK)
/*! @} */

/*! @name GPDO98 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO98_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO98_PDO_n_SHIFT (0U)
#define SIUL2_GPDO98_PDO_n_WIDTH (1U)
#define SIUL2_GPDO98_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO98_PDO_n_SHIFT)) & SIUL2_GPDO98_PDO_n_MASK)
/*! @} */

/*! @name GPDO97 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO97_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO97_PDO_n_SHIFT (0U)
#define SIUL2_GPDO97_PDO_n_WIDTH (1U)
#define SIUL2_GPDO97_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO97_PDO_n_SHIFT)) & SIUL2_GPDO97_PDO_n_MASK)
/*! @} */

/*! @name GPDO96 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO96_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO96_PDO_n_SHIFT (0U)
#define SIUL2_GPDO96_PDO_n_WIDTH (1U)
#define SIUL2_GPDO96_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO96_PDO_n_SHIFT)) & SIUL2_GPDO96_PDO_n_MASK)
/*! @} */

/*! @name GPDO103 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO103_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO103_PDO_n_SHIFT (0U)
#define SIUL2_GPDO103_PDO_n_WIDTH (1U)
#define SIUL2_GPDO103_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO103_PDO_n_SHIFT)) & SIUL2_GPDO103_PDO_n_MASK)
/*! @} */

/*! @name GPDO102 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO102_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO102_PDO_n_SHIFT (0U)
#define SIUL2_GPDO102_PDO_n_WIDTH (1U)
#define SIUL2_GPDO102_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO102_PDO_n_SHIFT)) & SIUL2_GPDO102_PDO_n_MASK)
/*! @} */

/*! @name GPDO101 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO101_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO101_PDO_n_SHIFT (0U)
#define SIUL2_GPDO101_PDO_n_WIDTH (1U)
#define SIUL2_GPDO101_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO101_PDO_n_SHIFT)) & SIUL2_GPDO101_PDO_n_MASK)
/*! @} */

/*! @name GPDO100 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO100_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO100_PDO_n_SHIFT (0U)
#define SIUL2_GPDO100_PDO_n_WIDTH (1U)
#define SIUL2_GPDO100_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO100_PDO_n_SHIFT)) & SIUL2_GPDO100_PDO_n_MASK)
/*! @} */

/*! @name GPDO107 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO107_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO107_PDO_n_SHIFT (0U)
#define SIUL2_GPDO107_PDO_n_WIDTH (1U)
#define SIUL2_GPDO107_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO107_PDO_n_SHIFT)) & SIUL2_GPDO107_PDO_n_MASK)
/*! @} */

/*! @name GPDO106 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO106_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO106_PDO_n_SHIFT (0U)
#define SIUL2_GPDO106_PDO_n_WIDTH (1U)
#define SIUL2_GPDO106_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO106_PDO_n_SHIFT)) & SIUL2_GPDO106_PDO_n_MASK)
/*! @} */

/*! @name GPDO105 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO105_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO105_PDO_n_SHIFT (0U)
#define SIUL2_GPDO105_PDO_n_WIDTH (1U)
#define SIUL2_GPDO105_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO105_PDO_n_SHIFT)) & SIUL2_GPDO105_PDO_n_MASK)
/*! @} */

/*! @name GPDO104 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO104_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO104_PDO_n_SHIFT (0U)
#define SIUL2_GPDO104_PDO_n_WIDTH (1U)
#define SIUL2_GPDO104_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO104_PDO_n_SHIFT)) & SIUL2_GPDO104_PDO_n_MASK)
/*! @} */

/*! @name GPDO111 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO111_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO111_PDO_n_SHIFT (0U)
#define SIUL2_GPDO111_PDO_n_WIDTH (1U)
#define SIUL2_GPDO111_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO111_PDO_n_SHIFT)) & SIUL2_GPDO111_PDO_n_MASK)
/*! @} */

/*! @name GPDO110 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO110_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO110_PDO_n_SHIFT (0U)
#define SIUL2_GPDO110_PDO_n_WIDTH (1U)
#define SIUL2_GPDO110_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO110_PDO_n_SHIFT)) & SIUL2_GPDO110_PDO_n_MASK)
/*! @} */

/*! @name GPDO109 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO109_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO109_PDO_n_SHIFT (0U)
#define SIUL2_GPDO109_PDO_n_WIDTH (1U)
#define SIUL2_GPDO109_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO109_PDO_n_SHIFT)) & SIUL2_GPDO109_PDO_n_MASK)
/*! @} */

/*! @name GPDO108 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO108_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO108_PDO_n_SHIFT (0U)
#define SIUL2_GPDO108_PDO_n_WIDTH (1U)
#define SIUL2_GPDO108_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO108_PDO_n_SHIFT)) & SIUL2_GPDO108_PDO_n_MASK)
/*! @} */

/*! @name GPDO115 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO115_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO115_PDO_n_SHIFT (0U)
#define SIUL2_GPDO115_PDO_n_WIDTH (1U)
#define SIUL2_GPDO115_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO115_PDO_n_SHIFT)) & SIUL2_GPDO115_PDO_n_MASK)
/*! @} */

/*! @name GPDO114 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO114_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO114_PDO_n_SHIFT (0U)
#define SIUL2_GPDO114_PDO_n_WIDTH (1U)
#define SIUL2_GPDO114_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO114_PDO_n_SHIFT)) & SIUL2_GPDO114_PDO_n_MASK)
/*! @} */

/*! @name GPDO113 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO113_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO113_PDO_n_SHIFT (0U)
#define SIUL2_GPDO113_PDO_n_WIDTH (1U)
#define SIUL2_GPDO113_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO113_PDO_n_SHIFT)) & SIUL2_GPDO113_PDO_n_MASK)
/*! @} */

/*! @name GPDO112 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO112_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO112_PDO_n_SHIFT (0U)
#define SIUL2_GPDO112_PDO_n_WIDTH (1U)
#define SIUL2_GPDO112_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO112_PDO_n_SHIFT)) & SIUL2_GPDO112_PDO_n_MASK)
/*! @} */

/*! @name GPDO119 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO119_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO119_PDO_n_SHIFT (0U)
#define SIUL2_GPDO119_PDO_n_WIDTH (1U)
#define SIUL2_GPDO119_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO119_PDO_n_SHIFT)) & SIUL2_GPDO119_PDO_n_MASK)
/*! @} */

/*! @name GPDO118 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO118_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO118_PDO_n_SHIFT (0U)
#define SIUL2_GPDO118_PDO_n_WIDTH (1U)
#define SIUL2_GPDO118_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO118_PDO_n_SHIFT)) & SIUL2_GPDO118_PDO_n_MASK)
/*! @} */

/*! @name GPDO117 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO117_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO117_PDO_n_SHIFT (0U)
#define SIUL2_GPDO117_PDO_n_WIDTH (1U)
#define SIUL2_GPDO117_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO117_PDO_n_SHIFT)) & SIUL2_GPDO117_PDO_n_MASK)
/*! @} */

/*! @name GPDO116 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO116_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO116_PDO_n_SHIFT (0U)
#define SIUL2_GPDO116_PDO_n_WIDTH (1U)
#define SIUL2_GPDO116_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO116_PDO_n_SHIFT)) & SIUL2_GPDO116_PDO_n_MASK)
/*! @} */

/*! @name GPDO123 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO123_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO123_PDO_n_SHIFT (0U)
#define SIUL2_GPDO123_PDO_n_WIDTH (1U)
#define SIUL2_GPDO123_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO123_PDO_n_SHIFT)) & SIUL2_GPDO123_PDO_n_MASK)
/*! @} */

/*! @name GPDO122 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO122_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO122_PDO_n_SHIFT (0U)
#define SIUL2_GPDO122_PDO_n_WIDTH (1U)
#define SIUL2_GPDO122_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO122_PDO_n_SHIFT)) & SIUL2_GPDO122_PDO_n_MASK)
/*! @} */

/*! @name GPDO121 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO121_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO121_PDO_n_SHIFT (0U)
#define SIUL2_GPDO121_PDO_n_WIDTH (1U)
#define SIUL2_GPDO121_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO121_PDO_n_SHIFT)) & SIUL2_GPDO121_PDO_n_MASK)
/*! @} */

/*! @name GPDO120 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO120_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO120_PDO_n_SHIFT (0U)
#define SIUL2_GPDO120_PDO_n_WIDTH (1U)
#define SIUL2_GPDO120_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO120_PDO_n_SHIFT)) & SIUL2_GPDO120_PDO_n_MASK)
/*! @} */

/*! @name GPDO127 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO127_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO127_PDO_n_SHIFT (0U)
#define SIUL2_GPDO127_PDO_n_WIDTH (1U)
#define SIUL2_GPDO127_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO127_PDO_n_SHIFT)) & SIUL2_GPDO127_PDO_n_MASK)
/*! @} */

/*! @name GPDO126 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO126_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO126_PDO_n_SHIFT (0U)
#define SIUL2_GPDO126_PDO_n_WIDTH (1U)
#define SIUL2_GPDO126_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO126_PDO_n_SHIFT)) & SIUL2_GPDO126_PDO_n_MASK)
/*! @} */

/*! @name GPDO125 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO125_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO125_PDO_n_SHIFT (0U)
#define SIUL2_GPDO125_PDO_n_WIDTH (1U)
#define SIUL2_GPDO125_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO125_PDO_n_SHIFT)) & SIUL2_GPDO125_PDO_n_MASK)
/*! @} */

/*! @name GPDO124 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO124_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO124_PDO_n_SHIFT (0U)
#define SIUL2_GPDO124_PDO_n_WIDTH (1U)
#define SIUL2_GPDO124_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO124_PDO_n_SHIFT)) & SIUL2_GPDO124_PDO_n_MASK)
/*! @} */

/*! @name GPDO131 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO131_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO131_PDO_n_SHIFT (0U)
#define SIUL2_GPDO131_PDO_n_WIDTH (1U)
#define SIUL2_GPDO131_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO131_PDO_n_SHIFT)) & SIUL2_GPDO131_PDO_n_MASK)
/*! @} */

/*! @name GPDO130 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO130_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO130_PDO_n_SHIFT (0U)
#define SIUL2_GPDO130_PDO_n_WIDTH (1U)
#define SIUL2_GPDO130_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO130_PDO_n_SHIFT)) & SIUL2_GPDO130_PDO_n_MASK)
/*! @} */

/*! @name GPDO129 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO129_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO129_PDO_n_SHIFT (0U)
#define SIUL2_GPDO129_PDO_n_WIDTH (1U)
#define SIUL2_GPDO129_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO129_PDO_n_SHIFT)) & SIUL2_GPDO129_PDO_n_MASK)
/*! @} */

/*! @name GPDO128 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO128_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO128_PDO_n_SHIFT (0U)
#define SIUL2_GPDO128_PDO_n_WIDTH (1U)
#define SIUL2_GPDO128_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO128_PDO_n_SHIFT)) & SIUL2_GPDO128_PDO_n_MASK)
/*! @} */

/*! @name GPDO135 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO135_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO135_PDO_n_SHIFT (0U)
#define SIUL2_GPDO135_PDO_n_WIDTH (1U)
#define SIUL2_GPDO135_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO135_PDO_n_SHIFT)) & SIUL2_GPDO135_PDO_n_MASK)
/*! @} */

/*! @name GPDO134 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO134_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO134_PDO_n_SHIFT (0U)
#define SIUL2_GPDO134_PDO_n_WIDTH (1U)
#define SIUL2_GPDO134_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO134_PDO_n_SHIFT)) & SIUL2_GPDO134_PDO_n_MASK)
/*! @} */

/*! @name GPDO133 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO133_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO133_PDO_n_SHIFT (0U)
#define SIUL2_GPDO133_PDO_n_WIDTH (1U)
#define SIUL2_GPDO133_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO133_PDO_n_SHIFT)) & SIUL2_GPDO133_PDO_n_MASK)
/*! @} */

/*! @name GPDO132 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO132_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO132_PDO_n_SHIFT (0U)
#define SIUL2_GPDO132_PDO_n_WIDTH (1U)
#define SIUL2_GPDO132_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO132_PDO_n_SHIFT)) & SIUL2_GPDO132_PDO_n_MASK)
/*! @} */

/*! @name GPDO139 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO139_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO139_PDO_n_SHIFT (0U)
#define SIUL2_GPDO139_PDO_n_WIDTH (1U)
#define SIUL2_GPDO139_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO139_PDO_n_SHIFT)) & SIUL2_GPDO139_PDO_n_MASK)
/*! @} */

/*! @name GPDO138 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO138_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO138_PDO_n_SHIFT (0U)
#define SIUL2_GPDO138_PDO_n_WIDTH (1U)
#define SIUL2_GPDO138_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO138_PDO_n_SHIFT)) & SIUL2_GPDO138_PDO_n_MASK)
/*! @} */

/*! @name GPDO137 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO137_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO137_PDO_n_SHIFT (0U)
#define SIUL2_GPDO137_PDO_n_WIDTH (1U)
#define SIUL2_GPDO137_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO137_PDO_n_SHIFT)) & SIUL2_GPDO137_PDO_n_MASK)
/*! @} */

/*! @name GPDO136 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO136_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO136_PDO_n_SHIFT (0U)
#define SIUL2_GPDO136_PDO_n_WIDTH (1U)
#define SIUL2_GPDO136_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO136_PDO_n_SHIFT)) & SIUL2_GPDO136_PDO_n_MASK)
/*! @} */

/*! @name GPDO143 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO143_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO143_PDO_n_SHIFT (0U)
#define SIUL2_GPDO143_PDO_n_WIDTH (1U)
#define SIUL2_GPDO143_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO143_PDO_n_SHIFT)) & SIUL2_GPDO143_PDO_n_MASK)
/*! @} */

/*! @name GPDO142 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO142_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO142_PDO_n_SHIFT (0U)
#define SIUL2_GPDO142_PDO_n_WIDTH (1U)
#define SIUL2_GPDO142_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO142_PDO_n_SHIFT)) & SIUL2_GPDO142_PDO_n_MASK)
/*! @} */

/*! @name GPDO141 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO141_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO141_PDO_n_SHIFT (0U)
#define SIUL2_GPDO141_PDO_n_WIDTH (1U)
#define SIUL2_GPDO141_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO141_PDO_n_SHIFT)) & SIUL2_GPDO141_PDO_n_MASK)
/*! @} */

/*! @name GPDO140 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO140_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO140_PDO_n_SHIFT (0U)
#define SIUL2_GPDO140_PDO_n_WIDTH (1U)
#define SIUL2_GPDO140_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO140_PDO_n_SHIFT)) & SIUL2_GPDO140_PDO_n_MASK)
/*! @} */

/*! @name GPDO147 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO147_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO147_PDO_n_SHIFT (0U)
#define SIUL2_GPDO147_PDO_n_WIDTH (1U)
#define SIUL2_GPDO147_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO147_PDO_n_SHIFT)) & SIUL2_GPDO147_PDO_n_MASK)
/*! @} */

/*! @name GPDO146 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO146_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO146_PDO_n_SHIFT (0U)
#define SIUL2_GPDO146_PDO_n_WIDTH (1U)
#define SIUL2_GPDO146_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO146_PDO_n_SHIFT)) & SIUL2_GPDO146_PDO_n_MASK)
/*! @} */

/*! @name GPDO145 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO145_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO145_PDO_n_SHIFT (0U)
#define SIUL2_GPDO145_PDO_n_WIDTH (1U)
#define SIUL2_GPDO145_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO145_PDO_n_SHIFT)) & SIUL2_GPDO145_PDO_n_MASK)
/*! @} */

/*! @name GPDO144 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO144_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO144_PDO_n_SHIFT (0U)
#define SIUL2_GPDO144_PDO_n_WIDTH (1U)
#define SIUL2_GPDO144_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO144_PDO_n_SHIFT)) & SIUL2_GPDO144_PDO_n_MASK)
/*! @} */

/*! @name GPDO151 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO151_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO151_PDO_n_SHIFT (0U)
#define SIUL2_GPDO151_PDO_n_WIDTH (1U)
#define SIUL2_GPDO151_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO151_PDO_n_SHIFT)) & SIUL2_GPDO151_PDO_n_MASK)
/*! @} */

/*! @name GPDO150 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO150_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO150_PDO_n_SHIFT (0U)
#define SIUL2_GPDO150_PDO_n_WIDTH (1U)
#define SIUL2_GPDO150_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO150_PDO_n_SHIFT)) & SIUL2_GPDO150_PDO_n_MASK)
/*! @} */

/*! @name GPDO149 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO149_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO149_PDO_n_SHIFT (0U)
#define SIUL2_GPDO149_PDO_n_WIDTH (1U)
#define SIUL2_GPDO149_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO149_PDO_n_SHIFT)) & SIUL2_GPDO149_PDO_n_MASK)
/*! @} */

/*! @name GPDO148 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO148_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO148_PDO_n_SHIFT (0U)
#define SIUL2_GPDO148_PDO_n_WIDTH (1U)
#define SIUL2_GPDO148_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO148_PDO_n_SHIFT)) & SIUL2_GPDO148_PDO_n_MASK)
/*! @} */

/*! @name GPDO155 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO155_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO155_PDO_n_SHIFT (0U)
#define SIUL2_GPDO155_PDO_n_WIDTH (1U)
#define SIUL2_GPDO155_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO155_PDO_n_SHIFT)) & SIUL2_GPDO155_PDO_n_MASK)
/*! @} */

/*! @name GPDO154 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO154_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO154_PDO_n_SHIFT (0U)
#define SIUL2_GPDO154_PDO_n_WIDTH (1U)
#define SIUL2_GPDO154_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO154_PDO_n_SHIFT)) & SIUL2_GPDO154_PDO_n_MASK)
/*! @} */

/*! @name GPDO153 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO153_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO153_PDO_n_SHIFT (0U)
#define SIUL2_GPDO153_PDO_n_WIDTH (1U)
#define SIUL2_GPDO153_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO153_PDO_n_SHIFT)) & SIUL2_GPDO153_PDO_n_MASK)
/*! @} */

/*! @name GPDO152 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO152_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO152_PDO_n_SHIFT (0U)
#define SIUL2_GPDO152_PDO_n_WIDTH (1U)
#define SIUL2_GPDO152_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO152_PDO_n_SHIFT)) & SIUL2_GPDO152_PDO_n_MASK)
/*! @} */

/*! @name GPDO159 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO159_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO159_PDO_n_SHIFT (0U)
#define SIUL2_GPDO159_PDO_n_WIDTH (1U)
#define SIUL2_GPDO159_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO159_PDO_n_SHIFT)) & SIUL2_GPDO159_PDO_n_MASK)
/*! @} */

/*! @name GPDO158 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO158_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO158_PDO_n_SHIFT (0U)
#define SIUL2_GPDO158_PDO_n_WIDTH (1U)
#define SIUL2_GPDO158_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO158_PDO_n_SHIFT)) & SIUL2_GPDO158_PDO_n_MASK)
/*! @} */

/*! @name GPDO157 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO157_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO157_PDO_n_SHIFT (0U)
#define SIUL2_GPDO157_PDO_n_WIDTH (1U)
#define SIUL2_GPDO157_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO157_PDO_n_SHIFT)) & SIUL2_GPDO157_PDO_n_MASK)
/*! @} */

/*! @name GPDO156 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO156_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO156_PDO_n_SHIFT (0U)
#define SIUL2_GPDO156_PDO_n_WIDTH (1U)
#define SIUL2_GPDO156_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO156_PDO_n_SHIFT)) & SIUL2_GPDO156_PDO_n_MASK)
/*! @} */

/*! @name GPDO163 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO163_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO163_PDO_n_SHIFT (0U)
#define SIUL2_GPDO163_PDO_n_WIDTH (1U)
#define SIUL2_GPDO163_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO163_PDO_n_SHIFT)) & SIUL2_GPDO163_PDO_n_MASK)
/*! @} */

/*! @name GPDO162 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO162_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO162_PDO_n_SHIFT (0U)
#define SIUL2_GPDO162_PDO_n_WIDTH (1U)
#define SIUL2_GPDO162_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO162_PDO_n_SHIFT)) & SIUL2_GPDO162_PDO_n_MASK)
/*! @} */

/*! @name GPDO161 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO161_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO161_PDO_n_SHIFT (0U)
#define SIUL2_GPDO161_PDO_n_WIDTH (1U)
#define SIUL2_GPDO161_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO161_PDO_n_SHIFT)) & SIUL2_GPDO161_PDO_n_MASK)
/*! @} */

/*! @name GPDO160 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO160_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO160_PDO_n_SHIFT (0U)
#define SIUL2_GPDO160_PDO_n_WIDTH (1U)
#define SIUL2_GPDO160_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO160_PDO_n_SHIFT)) & SIUL2_GPDO160_PDO_n_MASK)
/*! @} */

/*! @name GPDO167 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO167_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO167_PDO_n_SHIFT (0U)
#define SIUL2_GPDO167_PDO_n_WIDTH (1U)
#define SIUL2_GPDO167_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO167_PDO_n_SHIFT)) & SIUL2_GPDO167_PDO_n_MASK)
/*! @} */

/*! @name GPDO166 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO166_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO166_PDO_n_SHIFT (0U)
#define SIUL2_GPDO166_PDO_n_WIDTH (1U)
#define SIUL2_GPDO166_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO166_PDO_n_SHIFT)) & SIUL2_GPDO166_PDO_n_MASK)
/*! @} */

/*! @name GPDO165 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO165_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO165_PDO_n_SHIFT (0U)
#define SIUL2_GPDO165_PDO_n_WIDTH (1U)
#define SIUL2_GPDO165_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO165_PDO_n_SHIFT)) & SIUL2_GPDO165_PDO_n_MASK)
/*! @} */

/*! @name GPDO164 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO164_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO164_PDO_n_SHIFT (0U)
#define SIUL2_GPDO164_PDO_n_WIDTH (1U)
#define SIUL2_GPDO164_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO164_PDO_n_SHIFT)) & SIUL2_GPDO164_PDO_n_MASK)
/*! @} */

/*! @name GPDO171 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO171_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO171_PDO_n_SHIFT (0U)
#define SIUL2_GPDO171_PDO_n_WIDTH (1U)
#define SIUL2_GPDO171_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO171_PDO_n_SHIFT)) & SIUL2_GPDO171_PDO_n_MASK)
/*! @} */

/*! @name GPDO170 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO170_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO170_PDO_n_SHIFT (0U)
#define SIUL2_GPDO170_PDO_n_WIDTH (1U)
#define SIUL2_GPDO170_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO170_PDO_n_SHIFT)) & SIUL2_GPDO170_PDO_n_MASK)
/*! @} */

/*! @name GPDO169 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO169_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO169_PDO_n_SHIFT (0U)
#define SIUL2_GPDO169_PDO_n_WIDTH (1U)
#define SIUL2_GPDO169_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO169_PDO_n_SHIFT)) & SIUL2_GPDO169_PDO_n_MASK)
/*! @} */

/*! @name GPDO168 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO168_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO168_PDO_n_SHIFT (0U)
#define SIUL2_GPDO168_PDO_n_WIDTH (1U)
#define SIUL2_GPDO168_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO168_PDO_n_SHIFT)) & SIUL2_GPDO168_PDO_n_MASK)
/*! @} */

/*! @name GPDO173 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO173_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO173_PDO_n_SHIFT (0U)
#define SIUL2_GPDO173_PDO_n_WIDTH (1U)
#define SIUL2_GPDO173_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO173_PDO_n_SHIFT)) & SIUL2_GPDO173_PDO_n_MASK)
/*! @} */

/*! @name GPDO172 - SIUL2 GPIO Pad Data Output */
/*! @{ */

#define SIUL2_GPDO172_PDO_n_MASK  (0x1U)
#define SIUL2_GPDO172_PDO_n_SHIFT (0U)
#define SIUL2_GPDO172_PDO_n_WIDTH (1U)
#define SIUL2_GPDO172_PDO_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDO172_PDO_n_SHIFT)) & SIUL2_GPDO172_PDO_n_MASK)
/*! @} */

/*! @name GPDI3 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI3_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI3_PDI_n_SHIFT (0U)
#define SIUL2_GPDI3_PDI_n_WIDTH (1U)
#define SIUL2_GPDI3_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI3_PDI_n_SHIFT)) & SIUL2_GPDI3_PDI_n_MASK)
/*! @} */

/*! @name GPDI2 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI2_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI2_PDI_n_SHIFT (0U)
#define SIUL2_GPDI2_PDI_n_WIDTH (1U)
#define SIUL2_GPDI2_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI2_PDI_n_SHIFT)) & SIUL2_GPDI2_PDI_n_MASK)
/*! @} */

/*! @name GPDI1 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI1_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI1_PDI_n_SHIFT (0U)
#define SIUL2_GPDI1_PDI_n_WIDTH (1U)
#define SIUL2_GPDI1_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI1_PDI_n_SHIFT)) & SIUL2_GPDI1_PDI_n_MASK)
/*! @} */

/*! @name GPDI0 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI0_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI0_PDI_n_SHIFT (0U)
#define SIUL2_GPDI0_PDI_n_WIDTH (1U)
#define SIUL2_GPDI0_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI0_PDI_n_SHIFT)) & SIUL2_GPDI0_PDI_n_MASK)
/*! @} */

/*! @name GPDI7 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI7_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI7_PDI_n_SHIFT (0U)
#define SIUL2_GPDI7_PDI_n_WIDTH (1U)
#define SIUL2_GPDI7_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI7_PDI_n_SHIFT)) & SIUL2_GPDI7_PDI_n_MASK)
/*! @} */

/*! @name GPDI6 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI6_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI6_PDI_n_SHIFT (0U)
#define SIUL2_GPDI6_PDI_n_WIDTH (1U)
#define SIUL2_GPDI6_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI6_PDI_n_SHIFT)) & SIUL2_GPDI6_PDI_n_MASK)
/*! @} */

/*! @name GPDI5 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI5_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI5_PDI_n_SHIFT (0U)
#define SIUL2_GPDI5_PDI_n_WIDTH (1U)
#define SIUL2_GPDI5_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI5_PDI_n_SHIFT)) & SIUL2_GPDI5_PDI_n_MASK)
/*! @} */

/*! @name GPDI4 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI4_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI4_PDI_n_SHIFT (0U)
#define SIUL2_GPDI4_PDI_n_WIDTH (1U)
#define SIUL2_GPDI4_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI4_PDI_n_SHIFT)) & SIUL2_GPDI4_PDI_n_MASK)
/*! @} */

/*! @name GPDI11 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI11_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI11_PDI_n_SHIFT (0U)
#define SIUL2_GPDI11_PDI_n_WIDTH (1U)
#define SIUL2_GPDI11_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI11_PDI_n_SHIFT)) & SIUL2_GPDI11_PDI_n_MASK)
/*! @} */

/*! @name GPDI10 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI10_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI10_PDI_n_SHIFT (0U)
#define SIUL2_GPDI10_PDI_n_WIDTH (1U)
#define SIUL2_GPDI10_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI10_PDI_n_SHIFT)) & SIUL2_GPDI10_PDI_n_MASK)
/*! @} */

/*! @name GPDI9 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI9_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI9_PDI_n_SHIFT (0U)
#define SIUL2_GPDI9_PDI_n_WIDTH (1U)
#define SIUL2_GPDI9_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI9_PDI_n_SHIFT)) & SIUL2_GPDI9_PDI_n_MASK)
/*! @} */

/*! @name GPDI8 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI8_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI8_PDI_n_SHIFT (0U)
#define SIUL2_GPDI8_PDI_n_WIDTH (1U)
#define SIUL2_GPDI8_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI8_PDI_n_SHIFT)) & SIUL2_GPDI8_PDI_n_MASK)
/*! @} */

/*! @name GPDI15 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI15_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI15_PDI_n_SHIFT (0U)
#define SIUL2_GPDI15_PDI_n_WIDTH (1U)
#define SIUL2_GPDI15_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI15_PDI_n_SHIFT)) & SIUL2_GPDI15_PDI_n_MASK)
/*! @} */

/*! @name GPDI14 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI14_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI14_PDI_n_SHIFT (0U)
#define SIUL2_GPDI14_PDI_n_WIDTH (1U)
#define SIUL2_GPDI14_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI14_PDI_n_SHIFT)) & SIUL2_GPDI14_PDI_n_MASK)
/*! @} */

/*! @name GPDI13 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI13_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI13_PDI_n_SHIFT (0U)
#define SIUL2_GPDI13_PDI_n_WIDTH (1U)
#define SIUL2_GPDI13_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI13_PDI_n_SHIFT)) & SIUL2_GPDI13_PDI_n_MASK)
/*! @} */

/*! @name GPDI12 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI12_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI12_PDI_n_SHIFT (0U)
#define SIUL2_GPDI12_PDI_n_WIDTH (1U)
#define SIUL2_GPDI12_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI12_PDI_n_SHIFT)) & SIUL2_GPDI12_PDI_n_MASK)
/*! @} */

/*! @name GPDI19 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI19_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI19_PDI_n_SHIFT (0U)
#define SIUL2_GPDI19_PDI_n_WIDTH (1U)
#define SIUL2_GPDI19_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI19_PDI_n_SHIFT)) & SIUL2_GPDI19_PDI_n_MASK)
/*! @} */

/*! @name GPDI18 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI18_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI18_PDI_n_SHIFT (0U)
#define SIUL2_GPDI18_PDI_n_WIDTH (1U)
#define SIUL2_GPDI18_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI18_PDI_n_SHIFT)) & SIUL2_GPDI18_PDI_n_MASK)
/*! @} */

/*! @name GPDI17 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI17_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI17_PDI_n_SHIFT (0U)
#define SIUL2_GPDI17_PDI_n_WIDTH (1U)
#define SIUL2_GPDI17_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI17_PDI_n_SHIFT)) & SIUL2_GPDI17_PDI_n_MASK)
/*! @} */

/*! @name GPDI16 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI16_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI16_PDI_n_SHIFT (0U)
#define SIUL2_GPDI16_PDI_n_WIDTH (1U)
#define SIUL2_GPDI16_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI16_PDI_n_SHIFT)) & SIUL2_GPDI16_PDI_n_MASK)
/*! @} */

/*! @name GPDI23 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI23_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI23_PDI_n_SHIFT (0U)
#define SIUL2_GPDI23_PDI_n_WIDTH (1U)
#define SIUL2_GPDI23_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI23_PDI_n_SHIFT)) & SIUL2_GPDI23_PDI_n_MASK)
/*! @} */

/*! @name GPDI22 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI22_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI22_PDI_n_SHIFT (0U)
#define SIUL2_GPDI22_PDI_n_WIDTH (1U)
#define SIUL2_GPDI22_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI22_PDI_n_SHIFT)) & SIUL2_GPDI22_PDI_n_MASK)
/*! @} */

/*! @name GPDI21 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI21_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI21_PDI_n_SHIFT (0U)
#define SIUL2_GPDI21_PDI_n_WIDTH (1U)
#define SIUL2_GPDI21_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI21_PDI_n_SHIFT)) & SIUL2_GPDI21_PDI_n_MASK)
/*! @} */

/*! @name GPDI20 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI20_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI20_PDI_n_SHIFT (0U)
#define SIUL2_GPDI20_PDI_n_WIDTH (1U)
#define SIUL2_GPDI20_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI20_PDI_n_SHIFT)) & SIUL2_GPDI20_PDI_n_MASK)
/*! @} */

/*! @name GPDI27 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI27_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI27_PDI_n_SHIFT (0U)
#define SIUL2_GPDI27_PDI_n_WIDTH (1U)
#define SIUL2_GPDI27_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI27_PDI_n_SHIFT)) & SIUL2_GPDI27_PDI_n_MASK)
/*! @} */

/*! @name GPDI26 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI26_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI26_PDI_n_SHIFT (0U)
#define SIUL2_GPDI26_PDI_n_WIDTH (1U)
#define SIUL2_GPDI26_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI26_PDI_n_SHIFT)) & SIUL2_GPDI26_PDI_n_MASK)
/*! @} */

/*! @name GPDI25 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI25_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI25_PDI_n_SHIFT (0U)
#define SIUL2_GPDI25_PDI_n_WIDTH (1U)
#define SIUL2_GPDI25_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI25_PDI_n_SHIFT)) & SIUL2_GPDI25_PDI_n_MASK)
/*! @} */

/*! @name GPDI24 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI24_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI24_PDI_n_SHIFT (0U)
#define SIUL2_GPDI24_PDI_n_WIDTH (1U)
#define SIUL2_GPDI24_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI24_PDI_n_SHIFT)) & SIUL2_GPDI24_PDI_n_MASK)
/*! @} */

/*! @name GPDI31 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI31_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI31_PDI_n_SHIFT (0U)
#define SIUL2_GPDI31_PDI_n_WIDTH (1U)
#define SIUL2_GPDI31_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI31_PDI_n_SHIFT)) & SIUL2_GPDI31_PDI_n_MASK)
/*! @} */

/*! @name GPDI30 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI30_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI30_PDI_n_SHIFT (0U)
#define SIUL2_GPDI30_PDI_n_WIDTH (1U)
#define SIUL2_GPDI30_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI30_PDI_n_SHIFT)) & SIUL2_GPDI30_PDI_n_MASK)
/*! @} */

/*! @name GPDI29 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI29_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI29_PDI_n_SHIFT (0U)
#define SIUL2_GPDI29_PDI_n_WIDTH (1U)
#define SIUL2_GPDI29_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI29_PDI_n_SHIFT)) & SIUL2_GPDI29_PDI_n_MASK)
/*! @} */

/*! @name GPDI28 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI28_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI28_PDI_n_SHIFT (0U)
#define SIUL2_GPDI28_PDI_n_WIDTH (1U)
#define SIUL2_GPDI28_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI28_PDI_n_SHIFT)) & SIUL2_GPDI28_PDI_n_MASK)
/*! @} */

/*! @name GPDI35 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI35_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI35_PDI_n_SHIFT (0U)
#define SIUL2_GPDI35_PDI_n_WIDTH (1U)
#define SIUL2_GPDI35_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI35_PDI_n_SHIFT)) & SIUL2_GPDI35_PDI_n_MASK)
/*! @} */

/*! @name GPDI34 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI34_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI34_PDI_n_SHIFT (0U)
#define SIUL2_GPDI34_PDI_n_WIDTH (1U)
#define SIUL2_GPDI34_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI34_PDI_n_SHIFT)) & SIUL2_GPDI34_PDI_n_MASK)
/*! @} */

/*! @name GPDI33 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI33_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI33_PDI_n_SHIFT (0U)
#define SIUL2_GPDI33_PDI_n_WIDTH (1U)
#define SIUL2_GPDI33_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI33_PDI_n_SHIFT)) & SIUL2_GPDI33_PDI_n_MASK)
/*! @} */

/*! @name GPDI32 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI32_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI32_PDI_n_SHIFT (0U)
#define SIUL2_GPDI32_PDI_n_WIDTH (1U)
#define SIUL2_GPDI32_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI32_PDI_n_SHIFT)) & SIUL2_GPDI32_PDI_n_MASK)
/*! @} */

/*! @name GPDI39 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI39_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI39_PDI_n_SHIFT (0U)
#define SIUL2_GPDI39_PDI_n_WIDTH (1U)
#define SIUL2_GPDI39_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI39_PDI_n_SHIFT)) & SIUL2_GPDI39_PDI_n_MASK)
/*! @} */

/*! @name GPDI38 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI38_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI38_PDI_n_SHIFT (0U)
#define SIUL2_GPDI38_PDI_n_WIDTH (1U)
#define SIUL2_GPDI38_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI38_PDI_n_SHIFT)) & SIUL2_GPDI38_PDI_n_MASK)
/*! @} */

/*! @name GPDI37 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI37_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI37_PDI_n_SHIFT (0U)
#define SIUL2_GPDI37_PDI_n_WIDTH (1U)
#define SIUL2_GPDI37_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI37_PDI_n_SHIFT)) & SIUL2_GPDI37_PDI_n_MASK)
/*! @} */

/*! @name GPDI36 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI36_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI36_PDI_n_SHIFT (0U)
#define SIUL2_GPDI36_PDI_n_WIDTH (1U)
#define SIUL2_GPDI36_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI36_PDI_n_SHIFT)) & SIUL2_GPDI36_PDI_n_MASK)
/*! @} */

/*! @name GPDI43 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI43_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI43_PDI_n_SHIFT (0U)
#define SIUL2_GPDI43_PDI_n_WIDTH (1U)
#define SIUL2_GPDI43_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI43_PDI_n_SHIFT)) & SIUL2_GPDI43_PDI_n_MASK)
/*! @} */

/*! @name GPDI42 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI42_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI42_PDI_n_SHIFT (0U)
#define SIUL2_GPDI42_PDI_n_WIDTH (1U)
#define SIUL2_GPDI42_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI42_PDI_n_SHIFT)) & SIUL2_GPDI42_PDI_n_MASK)
/*! @} */

/*! @name GPDI41 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI41_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI41_PDI_n_SHIFT (0U)
#define SIUL2_GPDI41_PDI_n_WIDTH (1U)
#define SIUL2_GPDI41_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI41_PDI_n_SHIFT)) & SIUL2_GPDI41_PDI_n_MASK)
/*! @} */

/*! @name GPDI40 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI40_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI40_PDI_n_SHIFT (0U)
#define SIUL2_GPDI40_PDI_n_WIDTH (1U)
#define SIUL2_GPDI40_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI40_PDI_n_SHIFT)) & SIUL2_GPDI40_PDI_n_MASK)
/*! @} */

/*! @name GPDI47 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI47_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI47_PDI_n_SHIFT (0U)
#define SIUL2_GPDI47_PDI_n_WIDTH (1U)
#define SIUL2_GPDI47_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI47_PDI_n_SHIFT)) & SIUL2_GPDI47_PDI_n_MASK)
/*! @} */

/*! @name GPDI46 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI46_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI46_PDI_n_SHIFT (0U)
#define SIUL2_GPDI46_PDI_n_WIDTH (1U)
#define SIUL2_GPDI46_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI46_PDI_n_SHIFT)) & SIUL2_GPDI46_PDI_n_MASK)
/*! @} */

/*! @name GPDI45 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI45_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI45_PDI_n_SHIFT (0U)
#define SIUL2_GPDI45_PDI_n_WIDTH (1U)
#define SIUL2_GPDI45_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI45_PDI_n_SHIFT)) & SIUL2_GPDI45_PDI_n_MASK)
/*! @} */

/*! @name GPDI44 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI44_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI44_PDI_n_SHIFT (0U)
#define SIUL2_GPDI44_PDI_n_WIDTH (1U)
#define SIUL2_GPDI44_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI44_PDI_n_SHIFT)) & SIUL2_GPDI44_PDI_n_MASK)
/*! @} */

/*! @name GPDI51 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI51_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI51_PDI_n_SHIFT (0U)
#define SIUL2_GPDI51_PDI_n_WIDTH (1U)
#define SIUL2_GPDI51_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI51_PDI_n_SHIFT)) & SIUL2_GPDI51_PDI_n_MASK)
/*! @} */

/*! @name GPDI50 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI50_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI50_PDI_n_SHIFT (0U)
#define SIUL2_GPDI50_PDI_n_WIDTH (1U)
#define SIUL2_GPDI50_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI50_PDI_n_SHIFT)) & SIUL2_GPDI50_PDI_n_MASK)
/*! @} */

/*! @name GPDI49 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI49_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI49_PDI_n_SHIFT (0U)
#define SIUL2_GPDI49_PDI_n_WIDTH (1U)
#define SIUL2_GPDI49_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI49_PDI_n_SHIFT)) & SIUL2_GPDI49_PDI_n_MASK)
/*! @} */

/*! @name GPDI48 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI48_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI48_PDI_n_SHIFT (0U)
#define SIUL2_GPDI48_PDI_n_WIDTH (1U)
#define SIUL2_GPDI48_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI48_PDI_n_SHIFT)) & SIUL2_GPDI48_PDI_n_MASK)
/*! @} */

/*! @name GPDI55 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI55_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI55_PDI_n_SHIFT (0U)
#define SIUL2_GPDI55_PDI_n_WIDTH (1U)
#define SIUL2_GPDI55_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI55_PDI_n_SHIFT)) & SIUL2_GPDI55_PDI_n_MASK)
/*! @} */

/*! @name GPDI54 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI54_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI54_PDI_n_SHIFT (0U)
#define SIUL2_GPDI54_PDI_n_WIDTH (1U)
#define SIUL2_GPDI54_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI54_PDI_n_SHIFT)) & SIUL2_GPDI54_PDI_n_MASK)
/*! @} */

/*! @name GPDI53 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI53_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI53_PDI_n_SHIFT (0U)
#define SIUL2_GPDI53_PDI_n_WIDTH (1U)
#define SIUL2_GPDI53_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI53_PDI_n_SHIFT)) & SIUL2_GPDI53_PDI_n_MASK)
/*! @} */

/*! @name GPDI52 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI52_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI52_PDI_n_SHIFT (0U)
#define SIUL2_GPDI52_PDI_n_WIDTH (1U)
#define SIUL2_GPDI52_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI52_PDI_n_SHIFT)) & SIUL2_GPDI52_PDI_n_MASK)
/*! @} */

/*! @name GPDI59 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI59_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI59_PDI_n_SHIFT (0U)
#define SIUL2_GPDI59_PDI_n_WIDTH (1U)
#define SIUL2_GPDI59_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI59_PDI_n_SHIFT)) & SIUL2_GPDI59_PDI_n_MASK)
/*! @} */

/*! @name GPDI58 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI58_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI58_PDI_n_SHIFT (0U)
#define SIUL2_GPDI58_PDI_n_WIDTH (1U)
#define SIUL2_GPDI58_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI58_PDI_n_SHIFT)) & SIUL2_GPDI58_PDI_n_MASK)
/*! @} */

/*! @name GPDI57 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI57_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI57_PDI_n_SHIFT (0U)
#define SIUL2_GPDI57_PDI_n_WIDTH (1U)
#define SIUL2_GPDI57_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI57_PDI_n_SHIFT)) & SIUL2_GPDI57_PDI_n_MASK)
/*! @} */

/*! @name GPDI56 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI56_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI56_PDI_n_SHIFT (0U)
#define SIUL2_GPDI56_PDI_n_WIDTH (1U)
#define SIUL2_GPDI56_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI56_PDI_n_SHIFT)) & SIUL2_GPDI56_PDI_n_MASK)
/*! @} */

/*! @name GPDI63 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI63_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI63_PDI_n_SHIFT (0U)
#define SIUL2_GPDI63_PDI_n_WIDTH (1U)
#define SIUL2_GPDI63_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI63_PDI_n_SHIFT)) & SIUL2_GPDI63_PDI_n_MASK)
/*! @} */

/*! @name GPDI62 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI62_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI62_PDI_n_SHIFT (0U)
#define SIUL2_GPDI62_PDI_n_WIDTH (1U)
#define SIUL2_GPDI62_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI62_PDI_n_SHIFT)) & SIUL2_GPDI62_PDI_n_MASK)
/*! @} */

/*! @name GPDI61 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI61_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI61_PDI_n_SHIFT (0U)
#define SIUL2_GPDI61_PDI_n_WIDTH (1U)
#define SIUL2_GPDI61_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI61_PDI_n_SHIFT)) & SIUL2_GPDI61_PDI_n_MASK)
/*! @} */

/*! @name GPDI60 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI60_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI60_PDI_n_SHIFT (0U)
#define SIUL2_GPDI60_PDI_n_WIDTH (1U)
#define SIUL2_GPDI60_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI60_PDI_n_SHIFT)) & SIUL2_GPDI60_PDI_n_MASK)
/*! @} */

/*! @name GPDI67 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI67_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI67_PDI_n_SHIFT (0U)
#define SIUL2_GPDI67_PDI_n_WIDTH (1U)
#define SIUL2_GPDI67_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI67_PDI_n_SHIFT)) & SIUL2_GPDI67_PDI_n_MASK)
/*! @} */

/*! @name GPDI66 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI66_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI66_PDI_n_SHIFT (0U)
#define SIUL2_GPDI66_PDI_n_WIDTH (1U)
#define SIUL2_GPDI66_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI66_PDI_n_SHIFT)) & SIUL2_GPDI66_PDI_n_MASK)
/*! @} */

/*! @name GPDI65 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI65_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI65_PDI_n_SHIFT (0U)
#define SIUL2_GPDI65_PDI_n_WIDTH (1U)
#define SIUL2_GPDI65_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI65_PDI_n_SHIFT)) & SIUL2_GPDI65_PDI_n_MASK)
/*! @} */

/*! @name GPDI64 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI64_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI64_PDI_n_SHIFT (0U)
#define SIUL2_GPDI64_PDI_n_WIDTH (1U)
#define SIUL2_GPDI64_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI64_PDI_n_SHIFT)) & SIUL2_GPDI64_PDI_n_MASK)
/*! @} */

/*! @name GPDI71 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI71_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI71_PDI_n_SHIFT (0U)
#define SIUL2_GPDI71_PDI_n_WIDTH (1U)
#define SIUL2_GPDI71_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI71_PDI_n_SHIFT)) & SIUL2_GPDI71_PDI_n_MASK)
/*! @} */

/*! @name GPDI70 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI70_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI70_PDI_n_SHIFT (0U)
#define SIUL2_GPDI70_PDI_n_WIDTH (1U)
#define SIUL2_GPDI70_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI70_PDI_n_SHIFT)) & SIUL2_GPDI70_PDI_n_MASK)
/*! @} */

/*! @name GPDI69 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI69_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI69_PDI_n_SHIFT (0U)
#define SIUL2_GPDI69_PDI_n_WIDTH (1U)
#define SIUL2_GPDI69_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI69_PDI_n_SHIFT)) & SIUL2_GPDI69_PDI_n_MASK)
/*! @} */

/*! @name GPDI68 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI68_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI68_PDI_n_SHIFT (0U)
#define SIUL2_GPDI68_PDI_n_WIDTH (1U)
#define SIUL2_GPDI68_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI68_PDI_n_SHIFT)) & SIUL2_GPDI68_PDI_n_MASK)
/*! @} */

/*! @name GPDI75 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI75_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI75_PDI_n_SHIFT (0U)
#define SIUL2_GPDI75_PDI_n_WIDTH (1U)
#define SIUL2_GPDI75_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI75_PDI_n_SHIFT)) & SIUL2_GPDI75_PDI_n_MASK)
/*! @} */

/*! @name GPDI74 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI74_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI74_PDI_n_SHIFT (0U)
#define SIUL2_GPDI74_PDI_n_WIDTH (1U)
#define SIUL2_GPDI74_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI74_PDI_n_SHIFT)) & SIUL2_GPDI74_PDI_n_MASK)
/*! @} */

/*! @name GPDI73 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI73_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI73_PDI_n_SHIFT (0U)
#define SIUL2_GPDI73_PDI_n_WIDTH (1U)
#define SIUL2_GPDI73_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI73_PDI_n_SHIFT)) & SIUL2_GPDI73_PDI_n_MASK)
/*! @} */

/*! @name GPDI72 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI72_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI72_PDI_n_SHIFT (0U)
#define SIUL2_GPDI72_PDI_n_WIDTH (1U)
#define SIUL2_GPDI72_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI72_PDI_n_SHIFT)) & SIUL2_GPDI72_PDI_n_MASK)
/*! @} */

/*! @name GPDI79 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI79_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI79_PDI_n_SHIFT (0U)
#define SIUL2_GPDI79_PDI_n_WIDTH (1U)
#define SIUL2_GPDI79_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI79_PDI_n_SHIFT)) & SIUL2_GPDI79_PDI_n_MASK)
/*! @} */

/*! @name GPDI78 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI78_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI78_PDI_n_SHIFT (0U)
#define SIUL2_GPDI78_PDI_n_WIDTH (1U)
#define SIUL2_GPDI78_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI78_PDI_n_SHIFT)) & SIUL2_GPDI78_PDI_n_MASK)
/*! @} */

/*! @name GPDI77 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI77_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI77_PDI_n_SHIFT (0U)
#define SIUL2_GPDI77_PDI_n_WIDTH (1U)
#define SIUL2_GPDI77_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI77_PDI_n_SHIFT)) & SIUL2_GPDI77_PDI_n_MASK)
/*! @} */

/*! @name GPDI76 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI76_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI76_PDI_n_SHIFT (0U)
#define SIUL2_GPDI76_PDI_n_WIDTH (1U)
#define SIUL2_GPDI76_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI76_PDI_n_SHIFT)) & SIUL2_GPDI76_PDI_n_MASK)
/*! @} */

/*! @name GPDI83 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI83_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI83_PDI_n_SHIFT (0U)
#define SIUL2_GPDI83_PDI_n_WIDTH (1U)
#define SIUL2_GPDI83_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI83_PDI_n_SHIFT)) & SIUL2_GPDI83_PDI_n_MASK)
/*! @} */

/*! @name GPDI82 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI82_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI82_PDI_n_SHIFT (0U)
#define SIUL2_GPDI82_PDI_n_WIDTH (1U)
#define SIUL2_GPDI82_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI82_PDI_n_SHIFT)) & SIUL2_GPDI82_PDI_n_MASK)
/*! @} */

/*! @name GPDI81 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI81_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI81_PDI_n_SHIFT (0U)
#define SIUL2_GPDI81_PDI_n_WIDTH (1U)
#define SIUL2_GPDI81_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI81_PDI_n_SHIFT)) & SIUL2_GPDI81_PDI_n_MASK)
/*! @} */

/*! @name GPDI80 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI80_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI80_PDI_n_SHIFT (0U)
#define SIUL2_GPDI80_PDI_n_WIDTH (1U)
#define SIUL2_GPDI80_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI80_PDI_n_SHIFT)) & SIUL2_GPDI80_PDI_n_MASK)
/*! @} */

/*! @name GPDI87 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI87_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI87_PDI_n_SHIFT (0U)
#define SIUL2_GPDI87_PDI_n_WIDTH (1U)
#define SIUL2_GPDI87_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI87_PDI_n_SHIFT)) & SIUL2_GPDI87_PDI_n_MASK)
/*! @} */

/*! @name GPDI86 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI86_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI86_PDI_n_SHIFT (0U)
#define SIUL2_GPDI86_PDI_n_WIDTH (1U)
#define SIUL2_GPDI86_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI86_PDI_n_SHIFT)) & SIUL2_GPDI86_PDI_n_MASK)
/*! @} */

/*! @name GPDI85 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI85_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI85_PDI_n_SHIFT (0U)
#define SIUL2_GPDI85_PDI_n_WIDTH (1U)
#define SIUL2_GPDI85_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI85_PDI_n_SHIFT)) & SIUL2_GPDI85_PDI_n_MASK)
/*! @} */

/*! @name GPDI84 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI84_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI84_PDI_n_SHIFT (0U)
#define SIUL2_GPDI84_PDI_n_WIDTH (1U)
#define SIUL2_GPDI84_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI84_PDI_n_SHIFT)) & SIUL2_GPDI84_PDI_n_MASK)
/*! @} */

/*! @name GPDI91 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI91_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI91_PDI_n_SHIFT (0U)
#define SIUL2_GPDI91_PDI_n_WIDTH (1U)
#define SIUL2_GPDI91_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI91_PDI_n_SHIFT)) & SIUL2_GPDI91_PDI_n_MASK)
/*! @} */

/*! @name GPDI90 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI90_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI90_PDI_n_SHIFT (0U)
#define SIUL2_GPDI90_PDI_n_WIDTH (1U)
#define SIUL2_GPDI90_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI90_PDI_n_SHIFT)) & SIUL2_GPDI90_PDI_n_MASK)
/*! @} */

/*! @name GPDI89 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI89_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI89_PDI_n_SHIFT (0U)
#define SIUL2_GPDI89_PDI_n_WIDTH (1U)
#define SIUL2_GPDI89_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI89_PDI_n_SHIFT)) & SIUL2_GPDI89_PDI_n_MASK)
/*! @} */

/*! @name GPDI88 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI88_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI88_PDI_n_SHIFT (0U)
#define SIUL2_GPDI88_PDI_n_WIDTH (1U)
#define SIUL2_GPDI88_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI88_PDI_n_SHIFT)) & SIUL2_GPDI88_PDI_n_MASK)
/*! @} */

/*! @name GPDI95 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI95_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI95_PDI_n_SHIFT (0U)
#define SIUL2_GPDI95_PDI_n_WIDTH (1U)
#define SIUL2_GPDI95_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI95_PDI_n_SHIFT)) & SIUL2_GPDI95_PDI_n_MASK)
/*! @} */

/*! @name GPDI94 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI94_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI94_PDI_n_SHIFT (0U)
#define SIUL2_GPDI94_PDI_n_WIDTH (1U)
#define SIUL2_GPDI94_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI94_PDI_n_SHIFT)) & SIUL2_GPDI94_PDI_n_MASK)
/*! @} */

/*! @name GPDI93 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI93_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI93_PDI_n_SHIFT (0U)
#define SIUL2_GPDI93_PDI_n_WIDTH (1U)
#define SIUL2_GPDI93_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI93_PDI_n_SHIFT)) & SIUL2_GPDI93_PDI_n_MASK)
/*! @} */

/*! @name GPDI92 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI92_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI92_PDI_n_SHIFT (0U)
#define SIUL2_GPDI92_PDI_n_WIDTH (1U)
#define SIUL2_GPDI92_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI92_PDI_n_SHIFT)) & SIUL2_GPDI92_PDI_n_MASK)
/*! @} */

/*! @name GPDI99 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI99_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI99_PDI_n_SHIFT (0U)
#define SIUL2_GPDI99_PDI_n_WIDTH (1U)
#define SIUL2_GPDI99_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI99_PDI_n_SHIFT)) & SIUL2_GPDI99_PDI_n_MASK)
/*! @} */

/*! @name GPDI98 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI98_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI98_PDI_n_SHIFT (0U)
#define SIUL2_GPDI98_PDI_n_WIDTH (1U)
#define SIUL2_GPDI98_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI98_PDI_n_SHIFT)) & SIUL2_GPDI98_PDI_n_MASK)
/*! @} */

/*! @name GPDI97 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI97_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI97_PDI_n_SHIFT (0U)
#define SIUL2_GPDI97_PDI_n_WIDTH (1U)
#define SIUL2_GPDI97_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI97_PDI_n_SHIFT)) & SIUL2_GPDI97_PDI_n_MASK)
/*! @} */

/*! @name GPDI96 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI96_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI96_PDI_n_SHIFT (0U)
#define SIUL2_GPDI96_PDI_n_WIDTH (1U)
#define SIUL2_GPDI96_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI96_PDI_n_SHIFT)) & SIUL2_GPDI96_PDI_n_MASK)
/*! @} */

/*! @name GPDI103 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI103_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI103_PDI_n_SHIFT (0U)
#define SIUL2_GPDI103_PDI_n_WIDTH (1U)
#define SIUL2_GPDI103_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI103_PDI_n_SHIFT)) & SIUL2_GPDI103_PDI_n_MASK)
/*! @} */

/*! @name GPDI102 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI102_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI102_PDI_n_SHIFT (0U)
#define SIUL2_GPDI102_PDI_n_WIDTH (1U)
#define SIUL2_GPDI102_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI102_PDI_n_SHIFT)) & SIUL2_GPDI102_PDI_n_MASK)
/*! @} */

/*! @name GPDI101 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI101_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI101_PDI_n_SHIFT (0U)
#define SIUL2_GPDI101_PDI_n_WIDTH (1U)
#define SIUL2_GPDI101_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI101_PDI_n_SHIFT)) & SIUL2_GPDI101_PDI_n_MASK)
/*! @} */

/*! @name GPDI100 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI100_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI100_PDI_n_SHIFT (0U)
#define SIUL2_GPDI100_PDI_n_WIDTH (1U)
#define SIUL2_GPDI100_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI100_PDI_n_SHIFT)) & SIUL2_GPDI100_PDI_n_MASK)
/*! @} */

/*! @name GPDI107 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI107_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI107_PDI_n_SHIFT (0U)
#define SIUL2_GPDI107_PDI_n_WIDTH (1U)
#define SIUL2_GPDI107_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI107_PDI_n_SHIFT)) & SIUL2_GPDI107_PDI_n_MASK)
/*! @} */

/*! @name GPDI106 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI106_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI106_PDI_n_SHIFT (0U)
#define SIUL2_GPDI106_PDI_n_WIDTH (1U)
#define SIUL2_GPDI106_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI106_PDI_n_SHIFT)) & SIUL2_GPDI106_PDI_n_MASK)
/*! @} */

/*! @name GPDI105 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI105_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI105_PDI_n_SHIFT (0U)
#define SIUL2_GPDI105_PDI_n_WIDTH (1U)
#define SIUL2_GPDI105_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI105_PDI_n_SHIFT)) & SIUL2_GPDI105_PDI_n_MASK)
/*! @} */

/*! @name GPDI104 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI104_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI104_PDI_n_SHIFT (0U)
#define SIUL2_GPDI104_PDI_n_WIDTH (1U)
#define SIUL2_GPDI104_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI104_PDI_n_SHIFT)) & SIUL2_GPDI104_PDI_n_MASK)
/*! @} */

/*! @name GPDI111 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI111_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI111_PDI_n_SHIFT (0U)
#define SIUL2_GPDI111_PDI_n_WIDTH (1U)
#define SIUL2_GPDI111_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI111_PDI_n_SHIFT)) & SIUL2_GPDI111_PDI_n_MASK)
/*! @} */

/*! @name GPDI110 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI110_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI110_PDI_n_SHIFT (0U)
#define SIUL2_GPDI110_PDI_n_WIDTH (1U)
#define SIUL2_GPDI110_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI110_PDI_n_SHIFT)) & SIUL2_GPDI110_PDI_n_MASK)
/*! @} */

/*! @name GPDI109 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI109_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI109_PDI_n_SHIFT (0U)
#define SIUL2_GPDI109_PDI_n_WIDTH (1U)
#define SIUL2_GPDI109_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI109_PDI_n_SHIFT)) & SIUL2_GPDI109_PDI_n_MASK)
/*! @} */

/*! @name GPDI108 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI108_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI108_PDI_n_SHIFT (0U)
#define SIUL2_GPDI108_PDI_n_WIDTH (1U)
#define SIUL2_GPDI108_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI108_PDI_n_SHIFT)) & SIUL2_GPDI108_PDI_n_MASK)
/*! @} */

/*! @name GPDI115 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI115_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI115_PDI_n_SHIFT (0U)
#define SIUL2_GPDI115_PDI_n_WIDTH (1U)
#define SIUL2_GPDI115_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI115_PDI_n_SHIFT)) & SIUL2_GPDI115_PDI_n_MASK)
/*! @} */

/*! @name GPDI114 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI114_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI114_PDI_n_SHIFT (0U)
#define SIUL2_GPDI114_PDI_n_WIDTH (1U)
#define SIUL2_GPDI114_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI114_PDI_n_SHIFT)) & SIUL2_GPDI114_PDI_n_MASK)
/*! @} */

/*! @name GPDI113 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI113_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI113_PDI_n_SHIFT (0U)
#define SIUL2_GPDI113_PDI_n_WIDTH (1U)
#define SIUL2_GPDI113_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI113_PDI_n_SHIFT)) & SIUL2_GPDI113_PDI_n_MASK)
/*! @} */

/*! @name GPDI112 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI112_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI112_PDI_n_SHIFT (0U)
#define SIUL2_GPDI112_PDI_n_WIDTH (1U)
#define SIUL2_GPDI112_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI112_PDI_n_SHIFT)) & SIUL2_GPDI112_PDI_n_MASK)
/*! @} */

/*! @name GPDI119 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI119_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI119_PDI_n_SHIFT (0U)
#define SIUL2_GPDI119_PDI_n_WIDTH (1U)
#define SIUL2_GPDI119_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI119_PDI_n_SHIFT)) & SIUL2_GPDI119_PDI_n_MASK)
/*! @} */

/*! @name GPDI118 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI118_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI118_PDI_n_SHIFT (0U)
#define SIUL2_GPDI118_PDI_n_WIDTH (1U)
#define SIUL2_GPDI118_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI118_PDI_n_SHIFT)) & SIUL2_GPDI118_PDI_n_MASK)
/*! @} */

/*! @name GPDI117 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI117_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI117_PDI_n_SHIFT (0U)
#define SIUL2_GPDI117_PDI_n_WIDTH (1U)
#define SIUL2_GPDI117_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI117_PDI_n_SHIFT)) & SIUL2_GPDI117_PDI_n_MASK)
/*! @} */

/*! @name GPDI116 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI116_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI116_PDI_n_SHIFT (0U)
#define SIUL2_GPDI116_PDI_n_WIDTH (1U)
#define SIUL2_GPDI116_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI116_PDI_n_SHIFT)) & SIUL2_GPDI116_PDI_n_MASK)
/*! @} */

/*! @name GPDI123 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI123_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI123_PDI_n_SHIFT (0U)
#define SIUL2_GPDI123_PDI_n_WIDTH (1U)
#define SIUL2_GPDI123_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI123_PDI_n_SHIFT)) & SIUL2_GPDI123_PDI_n_MASK)
/*! @} */

/*! @name GPDI122 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI122_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI122_PDI_n_SHIFT (0U)
#define SIUL2_GPDI122_PDI_n_WIDTH (1U)
#define SIUL2_GPDI122_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI122_PDI_n_SHIFT)) & SIUL2_GPDI122_PDI_n_MASK)
/*! @} */

/*! @name GPDI121 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI121_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI121_PDI_n_SHIFT (0U)
#define SIUL2_GPDI121_PDI_n_WIDTH (1U)
#define SIUL2_GPDI121_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI121_PDI_n_SHIFT)) & SIUL2_GPDI121_PDI_n_MASK)
/*! @} */

/*! @name GPDI120 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI120_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI120_PDI_n_SHIFT (0U)
#define SIUL2_GPDI120_PDI_n_WIDTH (1U)
#define SIUL2_GPDI120_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI120_PDI_n_SHIFT)) & SIUL2_GPDI120_PDI_n_MASK)
/*! @} */

/*! @name GPDI127 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI127_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI127_PDI_n_SHIFT (0U)
#define SIUL2_GPDI127_PDI_n_WIDTH (1U)
#define SIUL2_GPDI127_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI127_PDI_n_SHIFT)) & SIUL2_GPDI127_PDI_n_MASK)
/*! @} */

/*! @name GPDI126 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI126_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI126_PDI_n_SHIFT (0U)
#define SIUL2_GPDI126_PDI_n_WIDTH (1U)
#define SIUL2_GPDI126_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI126_PDI_n_SHIFT)) & SIUL2_GPDI126_PDI_n_MASK)
/*! @} */

/*! @name GPDI125 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI125_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI125_PDI_n_SHIFT (0U)
#define SIUL2_GPDI125_PDI_n_WIDTH (1U)
#define SIUL2_GPDI125_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI125_PDI_n_SHIFT)) & SIUL2_GPDI125_PDI_n_MASK)
/*! @} */

/*! @name GPDI124 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI124_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI124_PDI_n_SHIFT (0U)
#define SIUL2_GPDI124_PDI_n_WIDTH (1U)
#define SIUL2_GPDI124_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI124_PDI_n_SHIFT)) & SIUL2_GPDI124_PDI_n_MASK)
/*! @} */

/*! @name GPDI131 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI131_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI131_PDI_n_SHIFT (0U)
#define SIUL2_GPDI131_PDI_n_WIDTH (1U)
#define SIUL2_GPDI131_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI131_PDI_n_SHIFT)) & SIUL2_GPDI131_PDI_n_MASK)
/*! @} */

/*! @name GPDI130 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI130_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI130_PDI_n_SHIFT (0U)
#define SIUL2_GPDI130_PDI_n_WIDTH (1U)
#define SIUL2_GPDI130_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI130_PDI_n_SHIFT)) & SIUL2_GPDI130_PDI_n_MASK)
/*! @} */

/*! @name GPDI129 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI129_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI129_PDI_n_SHIFT (0U)
#define SIUL2_GPDI129_PDI_n_WIDTH (1U)
#define SIUL2_GPDI129_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI129_PDI_n_SHIFT)) & SIUL2_GPDI129_PDI_n_MASK)
/*! @} */

/*! @name GPDI128 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI128_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI128_PDI_n_SHIFT (0U)
#define SIUL2_GPDI128_PDI_n_WIDTH (1U)
#define SIUL2_GPDI128_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI128_PDI_n_SHIFT)) & SIUL2_GPDI128_PDI_n_MASK)
/*! @} */

/*! @name GPDI135 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI135_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI135_PDI_n_SHIFT (0U)
#define SIUL2_GPDI135_PDI_n_WIDTH (1U)
#define SIUL2_GPDI135_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI135_PDI_n_SHIFT)) & SIUL2_GPDI135_PDI_n_MASK)
/*! @} */

/*! @name GPDI134 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI134_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI134_PDI_n_SHIFT (0U)
#define SIUL2_GPDI134_PDI_n_WIDTH (1U)
#define SIUL2_GPDI134_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI134_PDI_n_SHIFT)) & SIUL2_GPDI134_PDI_n_MASK)
/*! @} */

/*! @name GPDI133 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI133_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI133_PDI_n_SHIFT (0U)
#define SIUL2_GPDI133_PDI_n_WIDTH (1U)
#define SIUL2_GPDI133_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI133_PDI_n_SHIFT)) & SIUL2_GPDI133_PDI_n_MASK)
/*! @} */

/*! @name GPDI132 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI132_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI132_PDI_n_SHIFT (0U)
#define SIUL2_GPDI132_PDI_n_WIDTH (1U)
#define SIUL2_GPDI132_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI132_PDI_n_SHIFT)) & SIUL2_GPDI132_PDI_n_MASK)
/*! @} */

/*! @name GPDI139 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI139_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI139_PDI_n_SHIFT (0U)
#define SIUL2_GPDI139_PDI_n_WIDTH (1U)
#define SIUL2_GPDI139_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI139_PDI_n_SHIFT)) & SIUL2_GPDI139_PDI_n_MASK)
/*! @} */

/*! @name GPDI138 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI138_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI138_PDI_n_SHIFT (0U)
#define SIUL2_GPDI138_PDI_n_WIDTH (1U)
#define SIUL2_GPDI138_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI138_PDI_n_SHIFT)) & SIUL2_GPDI138_PDI_n_MASK)
/*! @} */

/*! @name GPDI137 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI137_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI137_PDI_n_SHIFT (0U)
#define SIUL2_GPDI137_PDI_n_WIDTH (1U)
#define SIUL2_GPDI137_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI137_PDI_n_SHIFT)) & SIUL2_GPDI137_PDI_n_MASK)
/*! @} */

/*! @name GPDI136 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI136_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI136_PDI_n_SHIFT (0U)
#define SIUL2_GPDI136_PDI_n_WIDTH (1U)
#define SIUL2_GPDI136_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI136_PDI_n_SHIFT)) & SIUL2_GPDI136_PDI_n_MASK)
/*! @} */

/*! @name GPDI143 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI143_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI143_PDI_n_SHIFT (0U)
#define SIUL2_GPDI143_PDI_n_WIDTH (1U)
#define SIUL2_GPDI143_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI143_PDI_n_SHIFT)) & SIUL2_GPDI143_PDI_n_MASK)
/*! @} */

/*! @name GPDI142 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI142_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI142_PDI_n_SHIFT (0U)
#define SIUL2_GPDI142_PDI_n_WIDTH (1U)
#define SIUL2_GPDI142_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI142_PDI_n_SHIFT)) & SIUL2_GPDI142_PDI_n_MASK)
/*! @} */

/*! @name GPDI141 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI141_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI141_PDI_n_SHIFT (0U)
#define SIUL2_GPDI141_PDI_n_WIDTH (1U)
#define SIUL2_GPDI141_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI141_PDI_n_SHIFT)) & SIUL2_GPDI141_PDI_n_MASK)
/*! @} */

/*! @name GPDI140 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI140_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI140_PDI_n_SHIFT (0U)
#define SIUL2_GPDI140_PDI_n_WIDTH (1U)
#define SIUL2_GPDI140_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI140_PDI_n_SHIFT)) & SIUL2_GPDI140_PDI_n_MASK)
/*! @} */

/*! @name GPDI147 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI147_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI147_PDI_n_SHIFT (0U)
#define SIUL2_GPDI147_PDI_n_WIDTH (1U)
#define SIUL2_GPDI147_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI147_PDI_n_SHIFT)) & SIUL2_GPDI147_PDI_n_MASK)
/*! @} */

/*! @name GPDI146 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI146_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI146_PDI_n_SHIFT (0U)
#define SIUL2_GPDI146_PDI_n_WIDTH (1U)
#define SIUL2_GPDI146_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI146_PDI_n_SHIFT)) & SIUL2_GPDI146_PDI_n_MASK)
/*! @} */

/*! @name GPDI145 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI145_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI145_PDI_n_SHIFT (0U)
#define SIUL2_GPDI145_PDI_n_WIDTH (1U)
#define SIUL2_GPDI145_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI145_PDI_n_SHIFT)) & SIUL2_GPDI145_PDI_n_MASK)
/*! @} */

/*! @name GPDI144 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI144_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI144_PDI_n_SHIFT (0U)
#define SIUL2_GPDI144_PDI_n_WIDTH (1U)
#define SIUL2_GPDI144_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI144_PDI_n_SHIFT)) & SIUL2_GPDI144_PDI_n_MASK)
/*! @} */

/*! @name GPDI151 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI151_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI151_PDI_n_SHIFT (0U)
#define SIUL2_GPDI151_PDI_n_WIDTH (1U)
#define SIUL2_GPDI151_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI151_PDI_n_SHIFT)) & SIUL2_GPDI151_PDI_n_MASK)
/*! @} */

/*! @name GPDI150 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI150_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI150_PDI_n_SHIFT (0U)
#define SIUL2_GPDI150_PDI_n_WIDTH (1U)
#define SIUL2_GPDI150_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI150_PDI_n_SHIFT)) & SIUL2_GPDI150_PDI_n_MASK)
/*! @} */

/*! @name GPDI149 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI149_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI149_PDI_n_SHIFT (0U)
#define SIUL2_GPDI149_PDI_n_WIDTH (1U)
#define SIUL2_GPDI149_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI149_PDI_n_SHIFT)) & SIUL2_GPDI149_PDI_n_MASK)
/*! @} */

/*! @name GPDI148 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI148_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI148_PDI_n_SHIFT (0U)
#define SIUL2_GPDI148_PDI_n_WIDTH (1U)
#define SIUL2_GPDI148_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI148_PDI_n_SHIFT)) & SIUL2_GPDI148_PDI_n_MASK)
/*! @} */

/*! @name GPDI155 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI155_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI155_PDI_n_SHIFT (0U)
#define SIUL2_GPDI155_PDI_n_WIDTH (1U)
#define SIUL2_GPDI155_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI155_PDI_n_SHIFT)) & SIUL2_GPDI155_PDI_n_MASK)
/*! @} */

/*! @name GPDI154 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI154_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI154_PDI_n_SHIFT (0U)
#define SIUL2_GPDI154_PDI_n_WIDTH (1U)
#define SIUL2_GPDI154_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI154_PDI_n_SHIFT)) & SIUL2_GPDI154_PDI_n_MASK)
/*! @} */

/*! @name GPDI153 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI153_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI153_PDI_n_SHIFT (0U)
#define SIUL2_GPDI153_PDI_n_WIDTH (1U)
#define SIUL2_GPDI153_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI153_PDI_n_SHIFT)) & SIUL2_GPDI153_PDI_n_MASK)
/*! @} */

/*! @name GPDI152 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI152_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI152_PDI_n_SHIFT (0U)
#define SIUL2_GPDI152_PDI_n_WIDTH (1U)
#define SIUL2_GPDI152_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI152_PDI_n_SHIFT)) & SIUL2_GPDI152_PDI_n_MASK)
/*! @} */

/*! @name GPDI159 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI159_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI159_PDI_n_SHIFT (0U)
#define SIUL2_GPDI159_PDI_n_WIDTH (1U)
#define SIUL2_GPDI159_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI159_PDI_n_SHIFT)) & SIUL2_GPDI159_PDI_n_MASK)
/*! @} */

/*! @name GPDI158 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI158_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI158_PDI_n_SHIFT (0U)
#define SIUL2_GPDI158_PDI_n_WIDTH (1U)
#define SIUL2_GPDI158_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI158_PDI_n_SHIFT)) & SIUL2_GPDI158_PDI_n_MASK)
/*! @} */

/*! @name GPDI157 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI157_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI157_PDI_n_SHIFT (0U)
#define SIUL2_GPDI157_PDI_n_WIDTH (1U)
#define SIUL2_GPDI157_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI157_PDI_n_SHIFT)) & SIUL2_GPDI157_PDI_n_MASK)
/*! @} */

/*! @name GPDI156 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI156_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI156_PDI_n_SHIFT (0U)
#define SIUL2_GPDI156_PDI_n_WIDTH (1U)
#define SIUL2_GPDI156_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI156_PDI_n_SHIFT)) & SIUL2_GPDI156_PDI_n_MASK)
/*! @} */

/*! @name GPDI163 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI163_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI163_PDI_n_SHIFT (0U)
#define SIUL2_GPDI163_PDI_n_WIDTH (1U)
#define SIUL2_GPDI163_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI163_PDI_n_SHIFT)) & SIUL2_GPDI163_PDI_n_MASK)
/*! @} */

/*! @name GPDI162 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI162_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI162_PDI_n_SHIFT (0U)
#define SIUL2_GPDI162_PDI_n_WIDTH (1U)
#define SIUL2_GPDI162_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI162_PDI_n_SHIFT)) & SIUL2_GPDI162_PDI_n_MASK)
/*! @} */

/*! @name GPDI161 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI161_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI161_PDI_n_SHIFT (0U)
#define SIUL2_GPDI161_PDI_n_WIDTH (1U)
#define SIUL2_GPDI161_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI161_PDI_n_SHIFT)) & SIUL2_GPDI161_PDI_n_MASK)
/*! @} */

/*! @name GPDI160 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI160_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI160_PDI_n_SHIFT (0U)
#define SIUL2_GPDI160_PDI_n_WIDTH (1U)
#define SIUL2_GPDI160_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI160_PDI_n_SHIFT)) & SIUL2_GPDI160_PDI_n_MASK)
/*! @} */

/*! @name GPDI167 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI167_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI167_PDI_n_SHIFT (0U)
#define SIUL2_GPDI167_PDI_n_WIDTH (1U)
#define SIUL2_GPDI167_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI167_PDI_n_SHIFT)) & SIUL2_GPDI167_PDI_n_MASK)
/*! @} */

/*! @name GPDI166 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI166_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI166_PDI_n_SHIFT (0U)
#define SIUL2_GPDI166_PDI_n_WIDTH (1U)
#define SIUL2_GPDI166_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI166_PDI_n_SHIFT)) & SIUL2_GPDI166_PDI_n_MASK)
/*! @} */

/*! @name GPDI165 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI165_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI165_PDI_n_SHIFT (0U)
#define SIUL2_GPDI165_PDI_n_WIDTH (1U)
#define SIUL2_GPDI165_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI165_PDI_n_SHIFT)) & SIUL2_GPDI165_PDI_n_MASK)
/*! @} */

/*! @name GPDI164 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI164_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI164_PDI_n_SHIFT (0U)
#define SIUL2_GPDI164_PDI_n_WIDTH (1U)
#define SIUL2_GPDI164_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI164_PDI_n_SHIFT)) & SIUL2_GPDI164_PDI_n_MASK)
/*! @} */

/*! @name GPDI171 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI171_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI171_PDI_n_SHIFT (0U)
#define SIUL2_GPDI171_PDI_n_WIDTH (1U)
#define SIUL2_GPDI171_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI171_PDI_n_SHIFT)) & SIUL2_GPDI171_PDI_n_MASK)
/*! @} */

/*! @name GPDI170 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI170_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI170_PDI_n_SHIFT (0U)
#define SIUL2_GPDI170_PDI_n_WIDTH (1U)
#define SIUL2_GPDI170_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI170_PDI_n_SHIFT)) & SIUL2_GPDI170_PDI_n_MASK)
/*! @} */

/*! @name GPDI169 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI169_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI169_PDI_n_SHIFT (0U)
#define SIUL2_GPDI169_PDI_n_WIDTH (1U)
#define SIUL2_GPDI169_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI169_PDI_n_SHIFT)) & SIUL2_GPDI169_PDI_n_MASK)
/*! @} */

/*! @name GPDI168 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI168_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI168_PDI_n_SHIFT (0U)
#define SIUL2_GPDI168_PDI_n_WIDTH (1U)
#define SIUL2_GPDI168_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI168_PDI_n_SHIFT)) & SIUL2_GPDI168_PDI_n_MASK)
/*! @} */

/*! @name GPDI173 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI173_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI173_PDI_n_SHIFT (0U)
#define SIUL2_GPDI173_PDI_n_WIDTH (1U)
#define SIUL2_GPDI173_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI173_PDI_n_SHIFT)) & SIUL2_GPDI173_PDI_n_MASK)
/*! @} */

/*! @name GPDI172 - SIUL2 GPIO Pad Data Input */
/*! @{ */

#define SIUL2_GPDI172_PDI_n_MASK  (0x1U)
#define SIUL2_GPDI172_PDI_n_SHIFT (0U)
#define SIUL2_GPDI172_PDI_n_WIDTH (1U)
#define SIUL2_GPDI172_PDI_n(x) \
    (((uint8_t)(((uint8_t)(x)) << SIUL2_GPDI172_PDI_n_SHIFT)) & SIUL2_GPDI172_PDI_n_MASK)
/*! @} */

/*! @name PGPDO1 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO1_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO1_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO1_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO0_SHIFT)) & SIUL2_PGPDO1_PPDO0_MASK)

#define SIUL2_PGPDO1_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO1_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO1_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO1_SHIFT)) & SIUL2_PGPDO1_PPDO1_MASK)

#define SIUL2_PGPDO1_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO1_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO1_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO2_SHIFT)) & SIUL2_PGPDO1_PPDO2_MASK)

#define SIUL2_PGPDO1_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO1_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO1_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO3_SHIFT)) & SIUL2_PGPDO1_PPDO3_MASK)

#define SIUL2_PGPDO1_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO1_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO1_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO4_SHIFT)) & SIUL2_PGPDO1_PPDO4_MASK)

#define SIUL2_PGPDO1_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO1_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO1_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO5_SHIFT)) & SIUL2_PGPDO1_PPDO5_MASK)

#define SIUL2_PGPDO1_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO1_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO1_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO6_SHIFT)) & SIUL2_PGPDO1_PPDO6_MASK)

#define SIUL2_PGPDO1_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO1_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO1_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO7_SHIFT)) & SIUL2_PGPDO1_PPDO7_MASK)

#define SIUL2_PGPDO1_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO1_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO1_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO8_SHIFT)) & SIUL2_PGPDO1_PPDO8_MASK)

#define SIUL2_PGPDO1_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO1_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO1_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO9_SHIFT)) & SIUL2_PGPDO1_PPDO9_MASK)

#define SIUL2_PGPDO1_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO1_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO1_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO10_SHIFT)) & SIUL2_PGPDO1_PPDO10_MASK)

#define SIUL2_PGPDO1_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO1_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO1_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO11_SHIFT)) & SIUL2_PGPDO1_PPDO11_MASK)

#define SIUL2_PGPDO1_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO1_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO1_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO12_SHIFT)) & SIUL2_PGPDO1_PPDO12_MASK)

#define SIUL2_PGPDO1_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO1_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO1_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO13_SHIFT)) & SIUL2_PGPDO1_PPDO13_MASK)

#define SIUL2_PGPDO1_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO1_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO1_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO14_SHIFT)) & SIUL2_PGPDO1_PPDO14_MASK)

#define SIUL2_PGPDO1_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO1_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO1_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO1_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO1_PPDO15_SHIFT)) & SIUL2_PGPDO1_PPDO15_MASK)
/*! @} */

/*! @name PGPDO0 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO0_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO0_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO0_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO0_SHIFT)) & SIUL2_PGPDO0_PPDO0_MASK)

#define SIUL2_PGPDO0_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO0_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO0_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO1_SHIFT)) & SIUL2_PGPDO0_PPDO1_MASK)

#define SIUL2_PGPDO0_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO0_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO0_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO2_SHIFT)) & SIUL2_PGPDO0_PPDO2_MASK)

#define SIUL2_PGPDO0_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO0_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO0_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO3_SHIFT)) & SIUL2_PGPDO0_PPDO3_MASK)

#define SIUL2_PGPDO0_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO0_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO0_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO4_SHIFT)) & SIUL2_PGPDO0_PPDO4_MASK)

#define SIUL2_PGPDO0_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO0_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO0_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO5_SHIFT)) & SIUL2_PGPDO0_PPDO5_MASK)

#define SIUL2_PGPDO0_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO0_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO0_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO6_SHIFT)) & SIUL2_PGPDO0_PPDO6_MASK)

#define SIUL2_PGPDO0_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO0_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO0_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO7_SHIFT)) & SIUL2_PGPDO0_PPDO7_MASK)

#define SIUL2_PGPDO0_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO0_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO0_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO8_SHIFT)) & SIUL2_PGPDO0_PPDO8_MASK)

#define SIUL2_PGPDO0_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO0_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO0_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO9_SHIFT)) & SIUL2_PGPDO0_PPDO9_MASK)

#define SIUL2_PGPDO0_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO0_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO0_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO10_SHIFT)) & SIUL2_PGPDO0_PPDO10_MASK)

#define SIUL2_PGPDO0_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO0_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO0_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO11_SHIFT)) & SIUL2_PGPDO0_PPDO11_MASK)

#define SIUL2_PGPDO0_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO0_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO0_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO12_SHIFT)) & SIUL2_PGPDO0_PPDO12_MASK)

#define SIUL2_PGPDO0_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO0_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO0_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO13_SHIFT)) & SIUL2_PGPDO0_PPDO13_MASK)

#define SIUL2_PGPDO0_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO0_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO0_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO14_SHIFT)) & SIUL2_PGPDO0_PPDO14_MASK)

#define SIUL2_PGPDO0_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO0_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO0_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO0_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO0_PPDO15_SHIFT)) & SIUL2_PGPDO0_PPDO15_MASK)
/*! @} */

/*! @name PGPDO3 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO3_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO3_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO3_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO0_SHIFT)) & SIUL2_PGPDO3_PPDO0_MASK)

#define SIUL2_PGPDO3_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO3_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO3_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO1_SHIFT)) & SIUL2_PGPDO3_PPDO1_MASK)

#define SIUL2_PGPDO3_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO3_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO3_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO2_SHIFT)) & SIUL2_PGPDO3_PPDO2_MASK)

#define SIUL2_PGPDO3_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO3_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO3_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO3_SHIFT)) & SIUL2_PGPDO3_PPDO3_MASK)

#define SIUL2_PGPDO3_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO3_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO3_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO4_SHIFT)) & SIUL2_PGPDO3_PPDO4_MASK)

#define SIUL2_PGPDO3_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO3_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO3_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO5_SHIFT)) & SIUL2_PGPDO3_PPDO5_MASK)

#define SIUL2_PGPDO3_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO3_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO3_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO6_SHIFT)) & SIUL2_PGPDO3_PPDO6_MASK)

#define SIUL2_PGPDO3_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO3_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO3_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO7_SHIFT)) & SIUL2_PGPDO3_PPDO7_MASK)

#define SIUL2_PGPDO3_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO3_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO3_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO8_SHIFT)) & SIUL2_PGPDO3_PPDO8_MASK)

#define SIUL2_PGPDO3_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO3_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO3_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO9_SHIFT)) & SIUL2_PGPDO3_PPDO9_MASK)

#define SIUL2_PGPDO3_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO3_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO3_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO10_SHIFT)) & SIUL2_PGPDO3_PPDO10_MASK)

#define SIUL2_PGPDO3_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO3_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO3_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO11_SHIFT)) & SIUL2_PGPDO3_PPDO11_MASK)

#define SIUL2_PGPDO3_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO3_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO3_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO12_SHIFT)) & SIUL2_PGPDO3_PPDO12_MASK)

#define SIUL2_PGPDO3_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO3_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO3_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO13_SHIFT)) & SIUL2_PGPDO3_PPDO13_MASK)

#define SIUL2_PGPDO3_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO3_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO3_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO14_SHIFT)) & SIUL2_PGPDO3_PPDO14_MASK)

#define SIUL2_PGPDO3_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO3_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO3_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO3_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO3_PPDO15_SHIFT)) & SIUL2_PGPDO3_PPDO15_MASK)
/*! @} */

/*! @name PGPDO2 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO2_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO2_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO2_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO0_SHIFT)) & SIUL2_PGPDO2_PPDO0_MASK)

#define SIUL2_PGPDO2_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO2_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO2_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO1_SHIFT)) & SIUL2_PGPDO2_PPDO1_MASK)

#define SIUL2_PGPDO2_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO2_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO2_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO2_SHIFT)) & SIUL2_PGPDO2_PPDO2_MASK)

#define SIUL2_PGPDO2_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO2_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO2_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO3_SHIFT)) & SIUL2_PGPDO2_PPDO3_MASK)

#define SIUL2_PGPDO2_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO2_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO2_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO4_SHIFT)) & SIUL2_PGPDO2_PPDO4_MASK)

#define SIUL2_PGPDO2_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO2_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO2_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO5_SHIFT)) & SIUL2_PGPDO2_PPDO5_MASK)

#define SIUL2_PGPDO2_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO2_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO2_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO6_SHIFT)) & SIUL2_PGPDO2_PPDO6_MASK)

#define SIUL2_PGPDO2_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO2_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO2_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO7_SHIFT)) & SIUL2_PGPDO2_PPDO7_MASK)

#define SIUL2_PGPDO2_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO2_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO2_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO8_SHIFT)) & SIUL2_PGPDO2_PPDO8_MASK)

#define SIUL2_PGPDO2_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO2_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO2_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO9_SHIFT)) & SIUL2_PGPDO2_PPDO9_MASK)

#define SIUL2_PGPDO2_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO2_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO2_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO10_SHIFT)) & SIUL2_PGPDO2_PPDO10_MASK)

#define SIUL2_PGPDO2_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO2_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO2_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO11_SHIFT)) & SIUL2_PGPDO2_PPDO11_MASK)

#define SIUL2_PGPDO2_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO2_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO2_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO12_SHIFT)) & SIUL2_PGPDO2_PPDO12_MASK)

#define SIUL2_PGPDO2_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO2_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO2_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO13_SHIFT)) & SIUL2_PGPDO2_PPDO13_MASK)

#define SIUL2_PGPDO2_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO2_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO2_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO14_SHIFT)) & SIUL2_PGPDO2_PPDO14_MASK)

#define SIUL2_PGPDO2_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO2_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO2_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO2_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO2_PPDO15_SHIFT)) & SIUL2_PGPDO2_PPDO15_MASK)
/*! @} */

/*! @name PGPDO5 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO5_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO5_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO5_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO0_SHIFT)) & SIUL2_PGPDO5_PPDO0_MASK)

#define SIUL2_PGPDO5_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO5_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO5_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO1_SHIFT)) & SIUL2_PGPDO5_PPDO1_MASK)

#define SIUL2_PGPDO5_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO5_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO5_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO2_SHIFT)) & SIUL2_PGPDO5_PPDO2_MASK)

#define SIUL2_PGPDO5_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO5_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO5_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO3_SHIFT)) & SIUL2_PGPDO5_PPDO3_MASK)

#define SIUL2_PGPDO5_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO5_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO5_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO4_SHIFT)) & SIUL2_PGPDO5_PPDO4_MASK)

#define SIUL2_PGPDO5_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO5_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO5_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO5_SHIFT)) & SIUL2_PGPDO5_PPDO5_MASK)

#define SIUL2_PGPDO5_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO5_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO5_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO6_SHIFT)) & SIUL2_PGPDO5_PPDO6_MASK)

#define SIUL2_PGPDO5_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO5_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO5_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO7_SHIFT)) & SIUL2_PGPDO5_PPDO7_MASK)

#define SIUL2_PGPDO5_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO5_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO5_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO8_SHIFT)) & SIUL2_PGPDO5_PPDO8_MASK)

#define SIUL2_PGPDO5_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO5_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO5_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO9_SHIFT)) & SIUL2_PGPDO5_PPDO9_MASK)

#define SIUL2_PGPDO5_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO5_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO5_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO10_SHIFT)) & SIUL2_PGPDO5_PPDO10_MASK)

#define SIUL2_PGPDO5_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO5_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO5_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO11_SHIFT)) & SIUL2_PGPDO5_PPDO11_MASK)

#define SIUL2_PGPDO5_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO5_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO5_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO12_SHIFT)) & SIUL2_PGPDO5_PPDO12_MASK)

#define SIUL2_PGPDO5_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO5_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO5_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO13_SHIFT)) & SIUL2_PGPDO5_PPDO13_MASK)

#define SIUL2_PGPDO5_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO5_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO5_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO14_SHIFT)) & SIUL2_PGPDO5_PPDO14_MASK)

#define SIUL2_PGPDO5_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO5_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO5_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO5_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO5_PPDO15_SHIFT)) & SIUL2_PGPDO5_PPDO15_MASK)
/*! @} */

/*! @name PGPDO4 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO4_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO4_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO4_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO0_SHIFT)) & SIUL2_PGPDO4_PPDO0_MASK)

#define SIUL2_PGPDO4_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO4_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO4_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO1_SHIFT)) & SIUL2_PGPDO4_PPDO1_MASK)

#define SIUL2_PGPDO4_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO4_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO4_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO2_SHIFT)) & SIUL2_PGPDO4_PPDO2_MASK)

#define SIUL2_PGPDO4_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO4_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO4_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO3_SHIFT)) & SIUL2_PGPDO4_PPDO3_MASK)

#define SIUL2_PGPDO4_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO4_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO4_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO4_SHIFT)) & SIUL2_PGPDO4_PPDO4_MASK)

#define SIUL2_PGPDO4_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO4_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO4_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO5_SHIFT)) & SIUL2_PGPDO4_PPDO5_MASK)

#define SIUL2_PGPDO4_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO4_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO4_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO6_SHIFT)) & SIUL2_PGPDO4_PPDO6_MASK)

#define SIUL2_PGPDO4_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO4_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO4_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO7_SHIFT)) & SIUL2_PGPDO4_PPDO7_MASK)

#define SIUL2_PGPDO4_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO4_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO4_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO8_SHIFT)) & SIUL2_PGPDO4_PPDO8_MASK)

#define SIUL2_PGPDO4_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO4_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO4_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO9_SHIFT)) & SIUL2_PGPDO4_PPDO9_MASK)

#define SIUL2_PGPDO4_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO4_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO4_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO10_SHIFT)) & SIUL2_PGPDO4_PPDO10_MASK)

#define SIUL2_PGPDO4_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO4_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO4_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO11_SHIFT)) & SIUL2_PGPDO4_PPDO11_MASK)

#define SIUL2_PGPDO4_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO4_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO4_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO12_SHIFT)) & SIUL2_PGPDO4_PPDO12_MASK)

#define SIUL2_PGPDO4_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO4_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO4_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO13_SHIFT)) & SIUL2_PGPDO4_PPDO13_MASK)

#define SIUL2_PGPDO4_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO4_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO4_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO14_SHIFT)) & SIUL2_PGPDO4_PPDO14_MASK)

#define SIUL2_PGPDO4_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO4_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO4_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO4_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO4_PPDO15_SHIFT)) & SIUL2_PGPDO4_PPDO15_MASK)
/*! @} */

/*! @name PGPDO7 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO7_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO7_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO7_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO0_SHIFT)) & SIUL2_PGPDO7_PPDO0_MASK)

#define SIUL2_PGPDO7_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO7_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO7_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO1_SHIFT)) & SIUL2_PGPDO7_PPDO1_MASK)

#define SIUL2_PGPDO7_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO7_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO7_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO2_SHIFT)) & SIUL2_PGPDO7_PPDO2_MASK)

#define SIUL2_PGPDO7_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO7_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO7_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO3_SHIFT)) & SIUL2_PGPDO7_PPDO3_MASK)

#define SIUL2_PGPDO7_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO7_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO7_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO4_SHIFT)) & SIUL2_PGPDO7_PPDO4_MASK)

#define SIUL2_PGPDO7_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO7_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO7_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO5_SHIFT)) & SIUL2_PGPDO7_PPDO5_MASK)

#define SIUL2_PGPDO7_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO7_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO7_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO6_SHIFT)) & SIUL2_PGPDO7_PPDO6_MASK)

#define SIUL2_PGPDO7_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO7_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO7_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO7_SHIFT)) & SIUL2_PGPDO7_PPDO7_MASK)

#define SIUL2_PGPDO7_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO7_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO7_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO8_SHIFT)) & SIUL2_PGPDO7_PPDO8_MASK)

#define SIUL2_PGPDO7_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO7_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO7_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO9_SHIFT)) & SIUL2_PGPDO7_PPDO9_MASK)

#define SIUL2_PGPDO7_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO7_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO7_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO10_SHIFT)) & SIUL2_PGPDO7_PPDO10_MASK)

#define SIUL2_PGPDO7_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO7_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO7_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO11_SHIFT)) & SIUL2_PGPDO7_PPDO11_MASK)

#define SIUL2_PGPDO7_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO7_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO7_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO12_SHIFT)) & SIUL2_PGPDO7_PPDO12_MASK)

#define SIUL2_PGPDO7_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO7_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO7_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO13_SHIFT)) & SIUL2_PGPDO7_PPDO13_MASK)

#define SIUL2_PGPDO7_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO7_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO7_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO14_SHIFT)) & SIUL2_PGPDO7_PPDO14_MASK)

#define SIUL2_PGPDO7_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO7_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO7_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO7_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO7_PPDO15_SHIFT)) & SIUL2_PGPDO7_PPDO15_MASK)
/*! @} */

/*! @name PGPDO6 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO6_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO6_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO6_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO0_SHIFT)) & SIUL2_PGPDO6_PPDO0_MASK)

#define SIUL2_PGPDO6_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO6_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO6_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO1_SHIFT)) & SIUL2_PGPDO6_PPDO1_MASK)

#define SIUL2_PGPDO6_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO6_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO6_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO2_SHIFT)) & SIUL2_PGPDO6_PPDO2_MASK)

#define SIUL2_PGPDO6_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO6_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO6_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO3_SHIFT)) & SIUL2_PGPDO6_PPDO3_MASK)

#define SIUL2_PGPDO6_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO6_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO6_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO4_SHIFT)) & SIUL2_PGPDO6_PPDO4_MASK)

#define SIUL2_PGPDO6_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO6_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO6_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO5_SHIFT)) & SIUL2_PGPDO6_PPDO5_MASK)

#define SIUL2_PGPDO6_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO6_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO6_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO6_SHIFT)) & SIUL2_PGPDO6_PPDO6_MASK)

#define SIUL2_PGPDO6_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO6_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO6_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO7_SHIFT)) & SIUL2_PGPDO6_PPDO7_MASK)

#define SIUL2_PGPDO6_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO6_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO6_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO8_SHIFT)) & SIUL2_PGPDO6_PPDO8_MASK)

#define SIUL2_PGPDO6_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO6_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO6_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO9_SHIFT)) & SIUL2_PGPDO6_PPDO9_MASK)

#define SIUL2_PGPDO6_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO6_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO6_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO10_SHIFT)) & SIUL2_PGPDO6_PPDO10_MASK)

#define SIUL2_PGPDO6_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO6_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO6_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO11_SHIFT)) & SIUL2_PGPDO6_PPDO11_MASK)

#define SIUL2_PGPDO6_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO6_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO6_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO12_SHIFT)) & SIUL2_PGPDO6_PPDO12_MASK)

#define SIUL2_PGPDO6_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO6_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO6_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO13_SHIFT)) & SIUL2_PGPDO6_PPDO13_MASK)

#define SIUL2_PGPDO6_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO6_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO6_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO14_SHIFT)) & SIUL2_PGPDO6_PPDO14_MASK)

#define SIUL2_PGPDO6_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO6_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO6_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO6_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO6_PPDO15_SHIFT)) & SIUL2_PGPDO6_PPDO15_MASK)
/*! @} */

/*! @name PGPDO9 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO9_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO9_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO9_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO0_SHIFT)) & SIUL2_PGPDO9_PPDO0_MASK)

#define SIUL2_PGPDO9_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO9_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO9_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO1_SHIFT)) & SIUL2_PGPDO9_PPDO1_MASK)

#define SIUL2_PGPDO9_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO9_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO9_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO2_SHIFT)) & SIUL2_PGPDO9_PPDO2_MASK)

#define SIUL2_PGPDO9_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO9_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO9_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO3_SHIFT)) & SIUL2_PGPDO9_PPDO3_MASK)

#define SIUL2_PGPDO9_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO9_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO9_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO4_SHIFT)) & SIUL2_PGPDO9_PPDO4_MASK)

#define SIUL2_PGPDO9_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO9_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO9_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO5_SHIFT)) & SIUL2_PGPDO9_PPDO5_MASK)

#define SIUL2_PGPDO9_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO9_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO9_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO6_SHIFT)) & SIUL2_PGPDO9_PPDO6_MASK)

#define SIUL2_PGPDO9_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO9_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO9_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO7_SHIFT)) & SIUL2_PGPDO9_PPDO7_MASK)

#define SIUL2_PGPDO9_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO9_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO9_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO8_SHIFT)) & SIUL2_PGPDO9_PPDO8_MASK)

#define SIUL2_PGPDO9_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO9_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO9_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO9_SHIFT)) & SIUL2_PGPDO9_PPDO9_MASK)

#define SIUL2_PGPDO9_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO9_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO9_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO10_SHIFT)) & SIUL2_PGPDO9_PPDO10_MASK)

#define SIUL2_PGPDO9_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO9_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO9_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO11_SHIFT)) & SIUL2_PGPDO9_PPDO11_MASK)

#define SIUL2_PGPDO9_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO9_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO9_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO12_SHIFT)) & SIUL2_PGPDO9_PPDO12_MASK)

#define SIUL2_PGPDO9_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO9_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO9_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO13_SHIFT)) & SIUL2_PGPDO9_PPDO13_MASK)

#define SIUL2_PGPDO9_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO9_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO9_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO14_SHIFT)) & SIUL2_PGPDO9_PPDO14_MASK)

#define SIUL2_PGPDO9_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO9_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO9_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO9_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO9_PPDO15_SHIFT)) & SIUL2_PGPDO9_PPDO15_MASK)
/*! @} */

/*! @name PGPDO8 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO8_PPDO0_MASK  (0x1U)
#define SIUL2_PGPDO8_PPDO0_SHIFT (0U)
#define SIUL2_PGPDO8_PPDO0_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO0_SHIFT)) & SIUL2_PGPDO8_PPDO0_MASK)

#define SIUL2_PGPDO8_PPDO1_MASK  (0x2U)
#define SIUL2_PGPDO8_PPDO1_SHIFT (1U)
#define SIUL2_PGPDO8_PPDO1_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO1_SHIFT)) & SIUL2_PGPDO8_PPDO1_MASK)

#define SIUL2_PGPDO8_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO8_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO8_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO2_SHIFT)) & SIUL2_PGPDO8_PPDO2_MASK)

#define SIUL2_PGPDO8_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO8_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO8_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO3_SHIFT)) & SIUL2_PGPDO8_PPDO3_MASK)

#define SIUL2_PGPDO8_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO8_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO8_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO4_SHIFT)) & SIUL2_PGPDO8_PPDO4_MASK)

#define SIUL2_PGPDO8_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO8_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO8_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO5_SHIFT)) & SIUL2_PGPDO8_PPDO5_MASK)

#define SIUL2_PGPDO8_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO8_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO8_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO6_SHIFT)) & SIUL2_PGPDO8_PPDO6_MASK)

#define SIUL2_PGPDO8_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO8_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO8_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO7_SHIFT)) & SIUL2_PGPDO8_PPDO7_MASK)

#define SIUL2_PGPDO8_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO8_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO8_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO8_SHIFT)) & SIUL2_PGPDO8_PPDO8_MASK)

#define SIUL2_PGPDO8_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO8_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO8_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO9_SHIFT)) & SIUL2_PGPDO8_PPDO9_MASK)

#define SIUL2_PGPDO8_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO8_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO8_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO10_SHIFT)) & SIUL2_PGPDO8_PPDO10_MASK)

#define SIUL2_PGPDO8_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO8_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO8_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO11_SHIFT)) & SIUL2_PGPDO8_PPDO11_MASK)

#define SIUL2_PGPDO8_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO8_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO8_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO12_SHIFT)) & SIUL2_PGPDO8_PPDO12_MASK)

#define SIUL2_PGPDO8_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO8_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO8_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO13_SHIFT)) & SIUL2_PGPDO8_PPDO13_MASK)

#define SIUL2_PGPDO8_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO8_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO8_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO14_SHIFT)) & SIUL2_PGPDO8_PPDO14_MASK)

#define SIUL2_PGPDO8_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO8_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO8_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO8_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO8_PPDO15_SHIFT)) & SIUL2_PGPDO8_PPDO15_MASK)
/*! @} */

/*! @name PGPDO10 - SIUL2 Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_PGPDO10_PPDO2_MASK  (0x4U)
#define SIUL2_PGPDO10_PPDO2_SHIFT (2U)
#define SIUL2_PGPDO10_PPDO2_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO2_SHIFT)) & SIUL2_PGPDO10_PPDO2_MASK)

#define SIUL2_PGPDO10_PPDO3_MASK  (0x8U)
#define SIUL2_PGPDO10_PPDO3_SHIFT (3U)
#define SIUL2_PGPDO10_PPDO3_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO3_SHIFT)) & SIUL2_PGPDO10_PPDO3_MASK)

#define SIUL2_PGPDO10_PPDO4_MASK  (0x10U)
#define SIUL2_PGPDO10_PPDO4_SHIFT (4U)
#define SIUL2_PGPDO10_PPDO4_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO4_SHIFT)) & SIUL2_PGPDO10_PPDO4_MASK)

#define SIUL2_PGPDO10_PPDO5_MASK  (0x20U)
#define SIUL2_PGPDO10_PPDO5_SHIFT (5U)
#define SIUL2_PGPDO10_PPDO5_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO5_SHIFT)) & SIUL2_PGPDO10_PPDO5_MASK)

#define SIUL2_PGPDO10_PPDO6_MASK  (0x40U)
#define SIUL2_PGPDO10_PPDO6_SHIFT (6U)
#define SIUL2_PGPDO10_PPDO6_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO6_SHIFT)) & SIUL2_PGPDO10_PPDO6_MASK)

#define SIUL2_PGPDO10_PPDO7_MASK  (0x80U)
#define SIUL2_PGPDO10_PPDO7_SHIFT (7U)
#define SIUL2_PGPDO10_PPDO7_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO7_SHIFT)) & SIUL2_PGPDO10_PPDO7_MASK)

#define SIUL2_PGPDO10_PPDO8_MASK  (0x100U)
#define SIUL2_PGPDO10_PPDO8_SHIFT (8U)
#define SIUL2_PGPDO10_PPDO8_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO8_SHIFT)) & SIUL2_PGPDO10_PPDO8_MASK)

#define SIUL2_PGPDO10_PPDO9_MASK  (0x200U)
#define SIUL2_PGPDO10_PPDO9_SHIFT (9U)
#define SIUL2_PGPDO10_PPDO9_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO9_SHIFT)) & SIUL2_PGPDO10_PPDO9_MASK)

#define SIUL2_PGPDO10_PPDO10_MASK  (0x400U)
#define SIUL2_PGPDO10_PPDO10_SHIFT (10U)
#define SIUL2_PGPDO10_PPDO10_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO10_SHIFT)) & SIUL2_PGPDO10_PPDO10_MASK)

#define SIUL2_PGPDO10_PPDO11_MASK  (0x800U)
#define SIUL2_PGPDO10_PPDO11_SHIFT (11U)
#define SIUL2_PGPDO10_PPDO11_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO11_SHIFT)) & SIUL2_PGPDO10_PPDO11_MASK)

#define SIUL2_PGPDO10_PPDO12_MASK  (0x1000U)
#define SIUL2_PGPDO10_PPDO12_SHIFT (12U)
#define SIUL2_PGPDO10_PPDO12_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO12_SHIFT)) & SIUL2_PGPDO10_PPDO12_MASK)

#define SIUL2_PGPDO10_PPDO13_MASK  (0x2000U)
#define SIUL2_PGPDO10_PPDO13_SHIFT (13U)
#define SIUL2_PGPDO10_PPDO13_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO13_SHIFT)) & SIUL2_PGPDO10_PPDO13_MASK)

#define SIUL2_PGPDO10_PPDO14_MASK  (0x4000U)
#define SIUL2_PGPDO10_PPDO14_SHIFT (14U)
#define SIUL2_PGPDO10_PPDO14_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO14_SHIFT)) & SIUL2_PGPDO10_PPDO14_MASK)

#define SIUL2_PGPDO10_PPDO15_MASK  (0x8000U)
#define SIUL2_PGPDO10_PPDO15_SHIFT (15U)
#define SIUL2_PGPDO10_PPDO15_WIDTH (1U)
#define SIUL2_PGPDO10_PPDO15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDO10_PPDO15_SHIFT)) & SIUL2_PGPDO10_PPDO15_MASK)
/*! @} */

/*! @name PGPDI1 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI1_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI1_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI1_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI0_SHIFT)) & SIUL2_PGPDI1_PPDI0_MASK)

#define SIUL2_PGPDI1_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI1_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI1_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI1_SHIFT)) & SIUL2_PGPDI1_PPDI1_MASK)

#define SIUL2_PGPDI1_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI1_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI1_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI2_SHIFT)) & SIUL2_PGPDI1_PPDI2_MASK)

#define SIUL2_PGPDI1_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI1_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI1_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI3_SHIFT)) & SIUL2_PGPDI1_PPDI3_MASK)

#define SIUL2_PGPDI1_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI1_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI1_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI4_SHIFT)) & SIUL2_PGPDI1_PPDI4_MASK)

#define SIUL2_PGPDI1_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI1_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI1_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI5_SHIFT)) & SIUL2_PGPDI1_PPDI5_MASK)

#define SIUL2_PGPDI1_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI1_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI1_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI6_SHIFT)) & SIUL2_PGPDI1_PPDI6_MASK)

#define SIUL2_PGPDI1_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI1_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI1_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI7_SHIFT)) & SIUL2_PGPDI1_PPDI7_MASK)

#define SIUL2_PGPDI1_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI1_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI1_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI8_SHIFT)) & SIUL2_PGPDI1_PPDI8_MASK)

#define SIUL2_PGPDI1_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI1_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI1_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI9_SHIFT)) & SIUL2_PGPDI1_PPDI9_MASK)

#define SIUL2_PGPDI1_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI1_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI1_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI10_SHIFT)) & SIUL2_PGPDI1_PPDI10_MASK)

#define SIUL2_PGPDI1_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI1_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI1_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI11_SHIFT)) & SIUL2_PGPDI1_PPDI11_MASK)

#define SIUL2_PGPDI1_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI1_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI1_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI12_SHIFT)) & SIUL2_PGPDI1_PPDI12_MASK)

#define SIUL2_PGPDI1_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI1_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI1_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI13_SHIFT)) & SIUL2_PGPDI1_PPDI13_MASK)

#define SIUL2_PGPDI1_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI1_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI1_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI14_SHIFT)) & SIUL2_PGPDI1_PPDI14_MASK)

#define SIUL2_PGPDI1_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI1_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI1_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI1_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI1_PPDI15_SHIFT)) & SIUL2_PGPDI1_PPDI15_MASK)
/*! @} */

/*! @name PGPDI0 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI0_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI0_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI0_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI0_SHIFT)) & SIUL2_PGPDI0_PPDI0_MASK)

#define SIUL2_PGPDI0_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI0_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI0_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI1_SHIFT)) & SIUL2_PGPDI0_PPDI1_MASK)

#define SIUL2_PGPDI0_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI0_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI0_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI2_SHIFT)) & SIUL2_PGPDI0_PPDI2_MASK)

#define SIUL2_PGPDI0_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI0_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI0_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI3_SHIFT)) & SIUL2_PGPDI0_PPDI3_MASK)

#define SIUL2_PGPDI0_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI0_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI0_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI4_SHIFT)) & SIUL2_PGPDI0_PPDI4_MASK)

#define SIUL2_PGPDI0_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI0_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI0_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI5_SHIFT)) & SIUL2_PGPDI0_PPDI5_MASK)

#define SIUL2_PGPDI0_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI0_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI0_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI6_SHIFT)) & SIUL2_PGPDI0_PPDI6_MASK)

#define SIUL2_PGPDI0_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI0_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI0_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI7_SHIFT)) & SIUL2_PGPDI0_PPDI7_MASK)

#define SIUL2_PGPDI0_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI0_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI0_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI8_SHIFT)) & SIUL2_PGPDI0_PPDI8_MASK)

#define SIUL2_PGPDI0_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI0_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI0_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI9_SHIFT)) & SIUL2_PGPDI0_PPDI9_MASK)

#define SIUL2_PGPDI0_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI0_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI0_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI10_SHIFT)) & SIUL2_PGPDI0_PPDI10_MASK)

#define SIUL2_PGPDI0_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI0_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI0_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI11_SHIFT)) & SIUL2_PGPDI0_PPDI11_MASK)

#define SIUL2_PGPDI0_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI0_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI0_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI12_SHIFT)) & SIUL2_PGPDI0_PPDI12_MASK)

#define SIUL2_PGPDI0_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI0_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI0_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI13_SHIFT)) & SIUL2_PGPDI0_PPDI13_MASK)

#define SIUL2_PGPDI0_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI0_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI0_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI14_SHIFT)) & SIUL2_PGPDI0_PPDI14_MASK)

#define SIUL2_PGPDI0_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI0_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI0_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI0_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI0_PPDI15_SHIFT)) & SIUL2_PGPDI0_PPDI15_MASK)
/*! @} */

/*! @name PGPDI3 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI3_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI3_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI3_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI0_SHIFT)) & SIUL2_PGPDI3_PPDI0_MASK)

#define SIUL2_PGPDI3_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI3_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI3_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI1_SHIFT)) & SIUL2_PGPDI3_PPDI1_MASK)

#define SIUL2_PGPDI3_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI3_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI3_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI2_SHIFT)) & SIUL2_PGPDI3_PPDI2_MASK)

#define SIUL2_PGPDI3_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI3_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI3_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI3_SHIFT)) & SIUL2_PGPDI3_PPDI3_MASK)

#define SIUL2_PGPDI3_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI3_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI3_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI4_SHIFT)) & SIUL2_PGPDI3_PPDI4_MASK)

#define SIUL2_PGPDI3_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI3_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI3_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI5_SHIFT)) & SIUL2_PGPDI3_PPDI5_MASK)

#define SIUL2_PGPDI3_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI3_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI3_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI6_SHIFT)) & SIUL2_PGPDI3_PPDI6_MASK)

#define SIUL2_PGPDI3_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI3_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI3_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI7_SHIFT)) & SIUL2_PGPDI3_PPDI7_MASK)

#define SIUL2_PGPDI3_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI3_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI3_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI8_SHIFT)) & SIUL2_PGPDI3_PPDI8_MASK)

#define SIUL2_PGPDI3_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI3_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI3_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI9_SHIFT)) & SIUL2_PGPDI3_PPDI9_MASK)

#define SIUL2_PGPDI3_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI3_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI3_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI10_SHIFT)) & SIUL2_PGPDI3_PPDI10_MASK)

#define SIUL2_PGPDI3_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI3_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI3_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI11_SHIFT)) & SIUL2_PGPDI3_PPDI11_MASK)

#define SIUL2_PGPDI3_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI3_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI3_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI12_SHIFT)) & SIUL2_PGPDI3_PPDI12_MASK)

#define SIUL2_PGPDI3_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI3_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI3_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI13_SHIFT)) & SIUL2_PGPDI3_PPDI13_MASK)

#define SIUL2_PGPDI3_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI3_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI3_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI14_SHIFT)) & SIUL2_PGPDI3_PPDI14_MASK)

#define SIUL2_PGPDI3_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI3_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI3_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI3_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI3_PPDI15_SHIFT)) & SIUL2_PGPDI3_PPDI15_MASK)
/*! @} */

/*! @name PGPDI2 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI2_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI2_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI2_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI0_SHIFT)) & SIUL2_PGPDI2_PPDI0_MASK)

#define SIUL2_PGPDI2_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI2_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI2_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI1_SHIFT)) & SIUL2_PGPDI2_PPDI1_MASK)

#define SIUL2_PGPDI2_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI2_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI2_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI2_SHIFT)) & SIUL2_PGPDI2_PPDI2_MASK)

#define SIUL2_PGPDI2_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI2_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI2_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI3_SHIFT)) & SIUL2_PGPDI2_PPDI3_MASK)

#define SIUL2_PGPDI2_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI2_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI2_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI4_SHIFT)) & SIUL2_PGPDI2_PPDI4_MASK)

#define SIUL2_PGPDI2_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI2_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI2_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI5_SHIFT)) & SIUL2_PGPDI2_PPDI5_MASK)

#define SIUL2_PGPDI2_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI2_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI2_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI6_SHIFT)) & SIUL2_PGPDI2_PPDI6_MASK)

#define SIUL2_PGPDI2_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI2_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI2_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI7_SHIFT)) & SIUL2_PGPDI2_PPDI7_MASK)

#define SIUL2_PGPDI2_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI2_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI2_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI8_SHIFT)) & SIUL2_PGPDI2_PPDI8_MASK)

#define SIUL2_PGPDI2_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI2_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI2_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI9_SHIFT)) & SIUL2_PGPDI2_PPDI9_MASK)

#define SIUL2_PGPDI2_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI2_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI2_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI10_SHIFT)) & SIUL2_PGPDI2_PPDI10_MASK)

#define SIUL2_PGPDI2_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI2_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI2_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI11_SHIFT)) & SIUL2_PGPDI2_PPDI11_MASK)

#define SIUL2_PGPDI2_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI2_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI2_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI12_SHIFT)) & SIUL2_PGPDI2_PPDI12_MASK)

#define SIUL2_PGPDI2_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI2_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI2_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI13_SHIFT)) & SIUL2_PGPDI2_PPDI13_MASK)

#define SIUL2_PGPDI2_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI2_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI2_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI14_SHIFT)) & SIUL2_PGPDI2_PPDI14_MASK)

#define SIUL2_PGPDI2_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI2_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI2_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI2_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI2_PPDI15_SHIFT)) & SIUL2_PGPDI2_PPDI15_MASK)
/*! @} */

/*! @name PGPDI5 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI5_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI5_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI5_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI0_SHIFT)) & SIUL2_PGPDI5_PPDI0_MASK)

#define SIUL2_PGPDI5_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI5_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI5_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI1_SHIFT)) & SIUL2_PGPDI5_PPDI1_MASK)

#define SIUL2_PGPDI5_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI5_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI5_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI2_SHIFT)) & SIUL2_PGPDI5_PPDI2_MASK)

#define SIUL2_PGPDI5_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI5_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI5_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI3_SHIFT)) & SIUL2_PGPDI5_PPDI3_MASK)

#define SIUL2_PGPDI5_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI5_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI5_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI4_SHIFT)) & SIUL2_PGPDI5_PPDI4_MASK)

#define SIUL2_PGPDI5_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI5_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI5_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI5_SHIFT)) & SIUL2_PGPDI5_PPDI5_MASK)

#define SIUL2_PGPDI5_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI5_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI5_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI6_SHIFT)) & SIUL2_PGPDI5_PPDI6_MASK)

#define SIUL2_PGPDI5_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI5_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI5_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI7_SHIFT)) & SIUL2_PGPDI5_PPDI7_MASK)

#define SIUL2_PGPDI5_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI5_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI5_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI8_SHIFT)) & SIUL2_PGPDI5_PPDI8_MASK)

#define SIUL2_PGPDI5_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI5_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI5_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI9_SHIFT)) & SIUL2_PGPDI5_PPDI9_MASK)

#define SIUL2_PGPDI5_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI5_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI5_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI10_SHIFT)) & SIUL2_PGPDI5_PPDI10_MASK)

#define SIUL2_PGPDI5_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI5_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI5_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI11_SHIFT)) & SIUL2_PGPDI5_PPDI11_MASK)

#define SIUL2_PGPDI5_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI5_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI5_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI12_SHIFT)) & SIUL2_PGPDI5_PPDI12_MASK)

#define SIUL2_PGPDI5_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI5_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI5_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI13_SHIFT)) & SIUL2_PGPDI5_PPDI13_MASK)

#define SIUL2_PGPDI5_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI5_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI5_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI14_SHIFT)) & SIUL2_PGPDI5_PPDI14_MASK)

#define SIUL2_PGPDI5_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI5_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI5_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI5_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI5_PPDI15_SHIFT)) & SIUL2_PGPDI5_PPDI15_MASK)
/*! @} */

/*! @name PGPDI4 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI4_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI4_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI4_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI0_SHIFT)) & SIUL2_PGPDI4_PPDI0_MASK)

#define SIUL2_PGPDI4_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI4_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI4_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI1_SHIFT)) & SIUL2_PGPDI4_PPDI1_MASK)

#define SIUL2_PGPDI4_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI4_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI4_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI2_SHIFT)) & SIUL2_PGPDI4_PPDI2_MASK)

#define SIUL2_PGPDI4_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI4_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI4_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI3_SHIFT)) & SIUL2_PGPDI4_PPDI3_MASK)

#define SIUL2_PGPDI4_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI4_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI4_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI4_SHIFT)) & SIUL2_PGPDI4_PPDI4_MASK)

#define SIUL2_PGPDI4_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI4_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI4_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI5_SHIFT)) & SIUL2_PGPDI4_PPDI5_MASK)

#define SIUL2_PGPDI4_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI4_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI4_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI6_SHIFT)) & SIUL2_PGPDI4_PPDI6_MASK)

#define SIUL2_PGPDI4_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI4_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI4_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI7_SHIFT)) & SIUL2_PGPDI4_PPDI7_MASK)

#define SIUL2_PGPDI4_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI4_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI4_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI8_SHIFT)) & SIUL2_PGPDI4_PPDI8_MASK)

#define SIUL2_PGPDI4_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI4_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI4_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI9_SHIFT)) & SIUL2_PGPDI4_PPDI9_MASK)

#define SIUL2_PGPDI4_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI4_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI4_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI10_SHIFT)) & SIUL2_PGPDI4_PPDI10_MASK)

#define SIUL2_PGPDI4_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI4_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI4_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI11_SHIFT)) & SIUL2_PGPDI4_PPDI11_MASK)

#define SIUL2_PGPDI4_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI4_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI4_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI12_SHIFT)) & SIUL2_PGPDI4_PPDI12_MASK)

#define SIUL2_PGPDI4_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI4_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI4_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI13_SHIFT)) & SIUL2_PGPDI4_PPDI13_MASK)

#define SIUL2_PGPDI4_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI4_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI4_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI14_SHIFT)) & SIUL2_PGPDI4_PPDI14_MASK)

#define SIUL2_PGPDI4_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI4_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI4_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI4_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI4_PPDI15_SHIFT)) & SIUL2_PGPDI4_PPDI15_MASK)
/*! @} */

/*! @name PGPDI7 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI7_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI7_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI7_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI0_SHIFT)) & SIUL2_PGPDI7_PPDI0_MASK)

#define SIUL2_PGPDI7_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI7_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI7_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI1_SHIFT)) & SIUL2_PGPDI7_PPDI1_MASK)

#define SIUL2_PGPDI7_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI7_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI7_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI2_SHIFT)) & SIUL2_PGPDI7_PPDI2_MASK)

#define SIUL2_PGPDI7_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI7_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI7_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI3_SHIFT)) & SIUL2_PGPDI7_PPDI3_MASK)

#define SIUL2_PGPDI7_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI7_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI7_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI4_SHIFT)) & SIUL2_PGPDI7_PPDI4_MASK)

#define SIUL2_PGPDI7_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI7_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI7_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI5_SHIFT)) & SIUL2_PGPDI7_PPDI5_MASK)

#define SIUL2_PGPDI7_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI7_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI7_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI6_SHIFT)) & SIUL2_PGPDI7_PPDI6_MASK)

#define SIUL2_PGPDI7_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI7_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI7_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI7_SHIFT)) & SIUL2_PGPDI7_PPDI7_MASK)

#define SIUL2_PGPDI7_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI7_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI7_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI8_SHIFT)) & SIUL2_PGPDI7_PPDI8_MASK)

#define SIUL2_PGPDI7_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI7_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI7_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI9_SHIFT)) & SIUL2_PGPDI7_PPDI9_MASK)

#define SIUL2_PGPDI7_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI7_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI7_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI10_SHIFT)) & SIUL2_PGPDI7_PPDI10_MASK)

#define SIUL2_PGPDI7_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI7_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI7_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI11_SHIFT)) & SIUL2_PGPDI7_PPDI11_MASK)

#define SIUL2_PGPDI7_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI7_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI7_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI12_SHIFT)) & SIUL2_PGPDI7_PPDI12_MASK)

#define SIUL2_PGPDI7_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI7_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI7_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI13_SHIFT)) & SIUL2_PGPDI7_PPDI13_MASK)

#define SIUL2_PGPDI7_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI7_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI7_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI14_SHIFT)) & SIUL2_PGPDI7_PPDI14_MASK)

#define SIUL2_PGPDI7_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI7_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI7_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI7_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI7_PPDI15_SHIFT)) & SIUL2_PGPDI7_PPDI15_MASK)
/*! @} */

/*! @name PGPDI6 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI6_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI6_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI6_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI0_SHIFT)) & SIUL2_PGPDI6_PPDI0_MASK)

#define SIUL2_PGPDI6_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI6_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI6_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI1_SHIFT)) & SIUL2_PGPDI6_PPDI1_MASK)

#define SIUL2_PGPDI6_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI6_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI6_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI2_SHIFT)) & SIUL2_PGPDI6_PPDI2_MASK)

#define SIUL2_PGPDI6_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI6_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI6_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI3_SHIFT)) & SIUL2_PGPDI6_PPDI3_MASK)

#define SIUL2_PGPDI6_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI6_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI6_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI4_SHIFT)) & SIUL2_PGPDI6_PPDI4_MASK)

#define SIUL2_PGPDI6_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI6_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI6_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI5_SHIFT)) & SIUL2_PGPDI6_PPDI5_MASK)

#define SIUL2_PGPDI6_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI6_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI6_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI6_SHIFT)) & SIUL2_PGPDI6_PPDI6_MASK)

#define SIUL2_PGPDI6_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI6_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI6_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI7_SHIFT)) & SIUL2_PGPDI6_PPDI7_MASK)

#define SIUL2_PGPDI6_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI6_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI6_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI8_SHIFT)) & SIUL2_PGPDI6_PPDI8_MASK)

#define SIUL2_PGPDI6_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI6_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI6_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI9_SHIFT)) & SIUL2_PGPDI6_PPDI9_MASK)

#define SIUL2_PGPDI6_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI6_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI6_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI10_SHIFT)) & SIUL2_PGPDI6_PPDI10_MASK)

#define SIUL2_PGPDI6_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI6_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI6_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI11_SHIFT)) & SIUL2_PGPDI6_PPDI11_MASK)

#define SIUL2_PGPDI6_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI6_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI6_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI12_SHIFT)) & SIUL2_PGPDI6_PPDI12_MASK)

#define SIUL2_PGPDI6_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI6_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI6_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI13_SHIFT)) & SIUL2_PGPDI6_PPDI13_MASK)

#define SIUL2_PGPDI6_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI6_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI6_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI14_SHIFT)) & SIUL2_PGPDI6_PPDI14_MASK)

#define SIUL2_PGPDI6_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI6_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI6_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI6_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI6_PPDI15_SHIFT)) & SIUL2_PGPDI6_PPDI15_MASK)
/*! @} */

/*! @name PGPDI9 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI9_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI9_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI9_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI0_SHIFT)) & SIUL2_PGPDI9_PPDI0_MASK)

#define SIUL2_PGPDI9_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI9_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI9_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI1_SHIFT)) & SIUL2_PGPDI9_PPDI1_MASK)

#define SIUL2_PGPDI9_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI9_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI9_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI2_SHIFT)) & SIUL2_PGPDI9_PPDI2_MASK)

#define SIUL2_PGPDI9_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI9_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI9_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI3_SHIFT)) & SIUL2_PGPDI9_PPDI3_MASK)

#define SIUL2_PGPDI9_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI9_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI9_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI4_SHIFT)) & SIUL2_PGPDI9_PPDI4_MASK)

#define SIUL2_PGPDI9_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI9_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI9_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI5_SHIFT)) & SIUL2_PGPDI9_PPDI5_MASK)

#define SIUL2_PGPDI9_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI9_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI9_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI6_SHIFT)) & SIUL2_PGPDI9_PPDI6_MASK)

#define SIUL2_PGPDI9_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI9_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI9_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI7_SHIFT)) & SIUL2_PGPDI9_PPDI7_MASK)

#define SIUL2_PGPDI9_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI9_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI9_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI8_SHIFT)) & SIUL2_PGPDI9_PPDI8_MASK)

#define SIUL2_PGPDI9_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI9_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI9_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI9_SHIFT)) & SIUL2_PGPDI9_PPDI9_MASK)

#define SIUL2_PGPDI9_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI9_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI9_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI10_SHIFT)) & SIUL2_PGPDI9_PPDI10_MASK)

#define SIUL2_PGPDI9_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI9_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI9_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI11_SHIFT)) & SIUL2_PGPDI9_PPDI11_MASK)

#define SIUL2_PGPDI9_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI9_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI9_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI12_SHIFT)) & SIUL2_PGPDI9_PPDI12_MASK)

#define SIUL2_PGPDI9_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI9_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI9_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI13_SHIFT)) & SIUL2_PGPDI9_PPDI13_MASK)

#define SIUL2_PGPDI9_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI9_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI9_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI14_SHIFT)) & SIUL2_PGPDI9_PPDI14_MASK)

#define SIUL2_PGPDI9_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI9_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI9_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI9_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI9_PPDI15_SHIFT)) & SIUL2_PGPDI9_PPDI15_MASK)
/*! @} */

/*! @name PGPDI8 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI8_PPDI0_MASK  (0x1U)
#define SIUL2_PGPDI8_PPDI0_SHIFT (0U)
#define SIUL2_PGPDI8_PPDI0_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI0(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI0_SHIFT)) & SIUL2_PGPDI8_PPDI0_MASK)

#define SIUL2_PGPDI8_PPDI1_MASK  (0x2U)
#define SIUL2_PGPDI8_PPDI1_SHIFT (1U)
#define SIUL2_PGPDI8_PPDI1_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI1(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI1_SHIFT)) & SIUL2_PGPDI8_PPDI1_MASK)

#define SIUL2_PGPDI8_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI8_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI8_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI2_SHIFT)) & SIUL2_PGPDI8_PPDI2_MASK)

#define SIUL2_PGPDI8_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI8_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI8_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI3_SHIFT)) & SIUL2_PGPDI8_PPDI3_MASK)

#define SIUL2_PGPDI8_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI8_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI8_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI4_SHIFT)) & SIUL2_PGPDI8_PPDI4_MASK)

#define SIUL2_PGPDI8_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI8_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI8_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI5_SHIFT)) & SIUL2_PGPDI8_PPDI5_MASK)

#define SIUL2_PGPDI8_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI8_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI8_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI6_SHIFT)) & SIUL2_PGPDI8_PPDI6_MASK)

#define SIUL2_PGPDI8_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI8_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI8_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI7_SHIFT)) & SIUL2_PGPDI8_PPDI7_MASK)

#define SIUL2_PGPDI8_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI8_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI8_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI8_SHIFT)) & SIUL2_PGPDI8_PPDI8_MASK)

#define SIUL2_PGPDI8_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI8_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI8_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI9_SHIFT)) & SIUL2_PGPDI8_PPDI9_MASK)

#define SIUL2_PGPDI8_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI8_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI8_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI10_SHIFT)) & SIUL2_PGPDI8_PPDI10_MASK)

#define SIUL2_PGPDI8_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI8_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI8_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI11_SHIFT)) & SIUL2_PGPDI8_PPDI11_MASK)

#define SIUL2_PGPDI8_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI8_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI8_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI12_SHIFT)) & SIUL2_PGPDI8_PPDI12_MASK)

#define SIUL2_PGPDI8_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI8_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI8_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI13_SHIFT)) & SIUL2_PGPDI8_PPDI13_MASK)

#define SIUL2_PGPDI8_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI8_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI8_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI14_SHIFT)) & SIUL2_PGPDI8_PPDI14_MASK)

#define SIUL2_PGPDI8_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI8_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI8_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI8_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI8_PPDI15_SHIFT)) & SIUL2_PGPDI8_PPDI15_MASK)
/*! @} */

/*! @name PGPDI10 - SIUL2 Parallel GPIO Pad Data In */
/*! @{ */

#define SIUL2_PGPDI10_PPDI2_MASK  (0x4U)
#define SIUL2_PGPDI10_PPDI2_SHIFT (2U)
#define SIUL2_PGPDI10_PPDI2_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI2(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI2_SHIFT)) & SIUL2_PGPDI10_PPDI2_MASK)

#define SIUL2_PGPDI10_PPDI3_MASK  (0x8U)
#define SIUL2_PGPDI10_PPDI3_SHIFT (3U)
#define SIUL2_PGPDI10_PPDI3_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI3(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI3_SHIFT)) & SIUL2_PGPDI10_PPDI3_MASK)

#define SIUL2_PGPDI10_PPDI4_MASK  (0x10U)
#define SIUL2_PGPDI10_PPDI4_SHIFT (4U)
#define SIUL2_PGPDI10_PPDI4_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI4(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI4_SHIFT)) & SIUL2_PGPDI10_PPDI4_MASK)

#define SIUL2_PGPDI10_PPDI5_MASK  (0x20U)
#define SIUL2_PGPDI10_PPDI5_SHIFT (5U)
#define SIUL2_PGPDI10_PPDI5_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI5(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI5_SHIFT)) & SIUL2_PGPDI10_PPDI5_MASK)

#define SIUL2_PGPDI10_PPDI6_MASK  (0x40U)
#define SIUL2_PGPDI10_PPDI6_SHIFT (6U)
#define SIUL2_PGPDI10_PPDI6_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI6(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI6_SHIFT)) & SIUL2_PGPDI10_PPDI6_MASK)

#define SIUL2_PGPDI10_PPDI7_MASK  (0x80U)
#define SIUL2_PGPDI10_PPDI7_SHIFT (7U)
#define SIUL2_PGPDI10_PPDI7_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI7(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI7_SHIFT)) & SIUL2_PGPDI10_PPDI7_MASK)

#define SIUL2_PGPDI10_PPDI8_MASK  (0x100U)
#define SIUL2_PGPDI10_PPDI8_SHIFT (8U)
#define SIUL2_PGPDI10_PPDI8_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI8(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI8_SHIFT)) & SIUL2_PGPDI10_PPDI8_MASK)

#define SIUL2_PGPDI10_PPDI9_MASK  (0x200U)
#define SIUL2_PGPDI10_PPDI9_SHIFT (9U)
#define SIUL2_PGPDI10_PPDI9_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI9(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI9_SHIFT)) & SIUL2_PGPDI10_PPDI9_MASK)

#define SIUL2_PGPDI10_PPDI10_MASK  (0x400U)
#define SIUL2_PGPDI10_PPDI10_SHIFT (10U)
#define SIUL2_PGPDI10_PPDI10_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI10(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI10_SHIFT)) & SIUL2_PGPDI10_PPDI10_MASK)

#define SIUL2_PGPDI10_PPDI11_MASK  (0x800U)
#define SIUL2_PGPDI10_PPDI11_SHIFT (11U)
#define SIUL2_PGPDI10_PPDI11_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI11(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI11_SHIFT)) & SIUL2_PGPDI10_PPDI11_MASK)

#define SIUL2_PGPDI10_PPDI12_MASK  (0x1000U)
#define SIUL2_PGPDI10_PPDI12_SHIFT (12U)
#define SIUL2_PGPDI10_PPDI12_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI12(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI12_SHIFT)) & SIUL2_PGPDI10_PPDI12_MASK)

#define SIUL2_PGPDI10_PPDI13_MASK  (0x2000U)
#define SIUL2_PGPDI10_PPDI13_SHIFT (13U)
#define SIUL2_PGPDI10_PPDI13_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI13(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI13_SHIFT)) & SIUL2_PGPDI10_PPDI13_MASK)

#define SIUL2_PGPDI10_PPDI14_MASK  (0x4000U)
#define SIUL2_PGPDI10_PPDI14_SHIFT (14U)
#define SIUL2_PGPDI10_PPDI14_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI14(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI14_SHIFT)) & SIUL2_PGPDI10_PPDI14_MASK)

#define SIUL2_PGPDI10_PPDI15_MASK  (0x8000U)
#define SIUL2_PGPDI10_PPDI15_SHIFT (15U)
#define SIUL2_PGPDI10_PPDI15_WIDTH (1U)
#define SIUL2_PGPDI10_PPDI15(x) \
    (((uint16_t)(((uint16_t)(x)) << SIUL2_PGPDI10_PPDI15_SHIFT)) & SIUL2_PGPDI10_PPDI15_MASK)
/*! @} */

/*! @name MPGPDO - SIUL2 Masked Parallel GPIO Pad Data Out */
/*! @{ */

#define SIUL2_MPGPDO_MPPDO0_MASK  (0x1U)
#define SIUL2_MPGPDO_MPPDO0_SHIFT (0U)
#define SIUL2_MPGPDO_MPPDO0_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO0_SHIFT)) & SIUL2_MPGPDO_MPPDO0_MASK)

#define SIUL2_MPGPDO_MPPDO1_MASK  (0x2U)
#define SIUL2_MPGPDO_MPPDO1_SHIFT (1U)
#define SIUL2_MPGPDO_MPPDO1_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO1_SHIFT)) & SIUL2_MPGPDO_MPPDO1_MASK)

#define SIUL2_MPGPDO_MPPDO2_MASK  (0x4U)
#define SIUL2_MPGPDO_MPPDO2_SHIFT (2U)
#define SIUL2_MPGPDO_MPPDO2_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO2_SHIFT)) & SIUL2_MPGPDO_MPPDO2_MASK)

#define SIUL2_MPGPDO_MPPDO3_MASK  (0x8U)
#define SIUL2_MPGPDO_MPPDO3_SHIFT (3U)
#define SIUL2_MPGPDO_MPPDO3_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO3_SHIFT)) & SIUL2_MPGPDO_MPPDO3_MASK)

#define SIUL2_MPGPDO_MPPDO4_MASK  (0x10U)
#define SIUL2_MPGPDO_MPPDO4_SHIFT (4U)
#define SIUL2_MPGPDO_MPPDO4_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO4_SHIFT)) & SIUL2_MPGPDO_MPPDO4_MASK)

#define SIUL2_MPGPDO_MPPDO5_MASK  (0x20U)
#define SIUL2_MPGPDO_MPPDO5_SHIFT (5U)
#define SIUL2_MPGPDO_MPPDO5_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO5_SHIFT)) & SIUL2_MPGPDO_MPPDO5_MASK)

#define SIUL2_MPGPDO_MPPDO6_MASK  (0x40U)
#define SIUL2_MPGPDO_MPPDO6_SHIFT (6U)
#define SIUL2_MPGPDO_MPPDO6_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO6_SHIFT)) & SIUL2_MPGPDO_MPPDO6_MASK)

#define SIUL2_MPGPDO_MPPDO7_MASK  (0x80U)
#define SIUL2_MPGPDO_MPPDO7_SHIFT (7U)
#define SIUL2_MPGPDO_MPPDO7_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO7_SHIFT)) & SIUL2_MPGPDO_MPPDO7_MASK)

#define SIUL2_MPGPDO_MPPDO8_MASK  (0x100U)
#define SIUL2_MPGPDO_MPPDO8_SHIFT (8U)
#define SIUL2_MPGPDO_MPPDO8_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO8_SHIFT)) & SIUL2_MPGPDO_MPPDO8_MASK)

#define SIUL2_MPGPDO_MPPDO9_MASK  (0x200U)
#define SIUL2_MPGPDO_MPPDO9_SHIFT (9U)
#define SIUL2_MPGPDO_MPPDO9_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO9_SHIFT)) & SIUL2_MPGPDO_MPPDO9_MASK)

#define SIUL2_MPGPDO_MPPDO10_MASK  (0x400U)
#define SIUL2_MPGPDO_MPPDO10_SHIFT (10U)
#define SIUL2_MPGPDO_MPPDO10_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO10_SHIFT)) & SIUL2_MPGPDO_MPPDO10_MASK)

#define SIUL2_MPGPDO_MPPDO11_MASK  (0x800U)
#define SIUL2_MPGPDO_MPPDO11_SHIFT (11U)
#define SIUL2_MPGPDO_MPPDO11_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO11_SHIFT)) & SIUL2_MPGPDO_MPPDO11_MASK)

#define SIUL2_MPGPDO_MPPDO12_MASK  (0x1000U)
#define SIUL2_MPGPDO_MPPDO12_SHIFT (12U)
#define SIUL2_MPGPDO_MPPDO12_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO12_SHIFT)) & SIUL2_MPGPDO_MPPDO12_MASK)

#define SIUL2_MPGPDO_MPPDO13_MASK  (0x2000U)
#define SIUL2_MPGPDO_MPPDO13_SHIFT (13U)
#define SIUL2_MPGPDO_MPPDO13_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO13_SHIFT)) & SIUL2_MPGPDO_MPPDO13_MASK)

#define SIUL2_MPGPDO_MPPDO14_MASK  (0x4000U)
#define SIUL2_MPGPDO_MPPDO14_SHIFT (14U)
#define SIUL2_MPGPDO_MPPDO14_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO14_SHIFT)) & SIUL2_MPGPDO_MPPDO14_MASK)

#define SIUL2_MPGPDO_MPPDO15_MASK  (0x8000U)
#define SIUL2_MPGPDO_MPPDO15_SHIFT (15U)
#define SIUL2_MPGPDO_MPPDO15_WIDTH (1U)
#define SIUL2_MPGPDO_MPPDO15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MPPDO15_SHIFT)) & SIUL2_MPGPDO_MPPDO15_MASK)

#define SIUL2_MPGPDO_MASK0_MASK  (0x10000U)
#define SIUL2_MPGPDO_MASK0_SHIFT (16U)
#define SIUL2_MPGPDO_MASK0_WIDTH (1U)
#define SIUL2_MPGPDO_MASK0(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK0_SHIFT)) & SIUL2_MPGPDO_MASK0_MASK)

#define SIUL2_MPGPDO_MASK1_MASK  (0x20000U)
#define SIUL2_MPGPDO_MASK1_SHIFT (17U)
#define SIUL2_MPGPDO_MASK1_WIDTH (1U)
#define SIUL2_MPGPDO_MASK1(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK1_SHIFT)) & SIUL2_MPGPDO_MASK1_MASK)

#define SIUL2_MPGPDO_MASK2_MASK  (0x40000U)
#define SIUL2_MPGPDO_MASK2_SHIFT (18U)
#define SIUL2_MPGPDO_MASK2_WIDTH (1U)
#define SIUL2_MPGPDO_MASK2(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK2_SHIFT)) & SIUL2_MPGPDO_MASK2_MASK)

#define SIUL2_MPGPDO_MASK3_MASK  (0x80000U)
#define SIUL2_MPGPDO_MASK3_SHIFT (19U)
#define SIUL2_MPGPDO_MASK3_WIDTH (1U)
#define SIUL2_MPGPDO_MASK3(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK3_SHIFT)) & SIUL2_MPGPDO_MASK3_MASK)

#define SIUL2_MPGPDO_MASK4_MASK  (0x100000U)
#define SIUL2_MPGPDO_MASK4_SHIFT (20U)
#define SIUL2_MPGPDO_MASK4_WIDTH (1U)
#define SIUL2_MPGPDO_MASK4(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK4_SHIFT)) & SIUL2_MPGPDO_MASK4_MASK)

#define SIUL2_MPGPDO_MASK5_MASK  (0x200000U)
#define SIUL2_MPGPDO_MASK5_SHIFT (21U)
#define SIUL2_MPGPDO_MASK5_WIDTH (1U)
#define SIUL2_MPGPDO_MASK5(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK5_SHIFT)) & SIUL2_MPGPDO_MASK5_MASK)

#define SIUL2_MPGPDO_MASK6_MASK  (0x400000U)
#define SIUL2_MPGPDO_MASK6_SHIFT (22U)
#define SIUL2_MPGPDO_MASK6_WIDTH (1U)
#define SIUL2_MPGPDO_MASK6(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK6_SHIFT)) & SIUL2_MPGPDO_MASK6_MASK)

#define SIUL2_MPGPDO_MASK7_MASK  (0x800000U)
#define SIUL2_MPGPDO_MASK7_SHIFT (23U)
#define SIUL2_MPGPDO_MASK7_WIDTH (1U)
#define SIUL2_MPGPDO_MASK7(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK7_SHIFT)) & SIUL2_MPGPDO_MASK7_MASK)

#define SIUL2_MPGPDO_MASK8_MASK  (0x1000000U)
#define SIUL2_MPGPDO_MASK8_SHIFT (24U)
#define SIUL2_MPGPDO_MASK8_WIDTH (1U)
#define SIUL2_MPGPDO_MASK8(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK8_SHIFT)) & SIUL2_MPGPDO_MASK8_MASK)

#define SIUL2_MPGPDO_MASK9_MASK  (0x2000000U)
#define SIUL2_MPGPDO_MASK9_SHIFT (25U)
#define SIUL2_MPGPDO_MASK9_WIDTH (1U)
#define SIUL2_MPGPDO_MASK9(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK9_SHIFT)) & SIUL2_MPGPDO_MASK9_MASK)

#define SIUL2_MPGPDO_MASK10_MASK  (0x4000000U)
#define SIUL2_MPGPDO_MASK10_SHIFT (26U)
#define SIUL2_MPGPDO_MASK10_WIDTH (1U)
#define SIUL2_MPGPDO_MASK10(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK10_SHIFT)) & SIUL2_MPGPDO_MASK10_MASK)

#define SIUL2_MPGPDO_MASK11_MASK  (0x8000000U)
#define SIUL2_MPGPDO_MASK11_SHIFT (27U)
#define SIUL2_MPGPDO_MASK11_WIDTH (1U)
#define SIUL2_MPGPDO_MASK11(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK11_SHIFT)) & SIUL2_MPGPDO_MASK11_MASK)

#define SIUL2_MPGPDO_MASK12_MASK  (0x10000000U)
#define SIUL2_MPGPDO_MASK12_SHIFT (28U)
#define SIUL2_MPGPDO_MASK12_WIDTH (1U)
#define SIUL2_MPGPDO_MASK12(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK12_SHIFT)) & SIUL2_MPGPDO_MASK12_MASK)

#define SIUL2_MPGPDO_MASK13_MASK  (0x20000000U)
#define SIUL2_MPGPDO_MASK13_SHIFT (29U)
#define SIUL2_MPGPDO_MASK13_WIDTH (1U)
#define SIUL2_MPGPDO_MASK13(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK13_SHIFT)) & SIUL2_MPGPDO_MASK13_MASK)

#define SIUL2_MPGPDO_MASK14_MASK  (0x40000000U)
#define SIUL2_MPGPDO_MASK14_SHIFT (30U)
#define SIUL2_MPGPDO_MASK14_WIDTH (1U)
#define SIUL2_MPGPDO_MASK14(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK14_SHIFT)) & SIUL2_MPGPDO_MASK14_MASK)

#define SIUL2_MPGPDO_MASK15_MASK  (0x80000000U)
#define SIUL2_MPGPDO_MASK15_SHIFT (31U)
#define SIUL2_MPGPDO_MASK15_WIDTH (1U)
#define SIUL2_MPGPDO_MASK15(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_MPGPDO_MASK15_SHIFT)) & SIUL2_MPGPDO_MASK15_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SIUL2_Register_Masks */

/*!
 * @}
 */ /* end of group SIUL2_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_SIUL2_H_) */
