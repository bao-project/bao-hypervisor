/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2_MC_ME.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2_MC_ME
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
#if !defined(S32Z2_MC_ME_H_) /* Check if memory map has not been already included */
#define S32Z2_MC_ME_H_

#include "S32Z2_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MC_ME Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_ME_Peripheral_Access_Layer MC_ME Peripheral Access Layer
 * @{
 */

/** MC_ME - Register Layout Typedef */
typedef struct {
    __IO uint32_t CTL_KEY;     /**< Control Key Register, offset: 0x0 */
    __IO uint32_t MODE_CONF;   /**< Mode Configuration Register, offset: 0x4 */
    __IO uint32_t MODE_UPD;    /**< Mode Update Register, offset: 0x8 */
    uint8_t RESERVED_0[244];
    __IO uint32_t PRTN0_PCONF; /**< Partition 0 Process Configuration Register, offset: 0x100 */
    __IO uint32_t PRTN0_PUPD;  /**< Partition 0 Process Update Register, offset: 0x104 */
    __I uint32_t PRTN0_STAT;   /**< Partition 0 Status Register, offset: 0x108 */
    uint8_t RESERVED_1[52];
    __IO uint32_t PRTN0_CORE0_PCONF; /**< Partition 0 Core 0 Process Configuration Register, offset:
                                        0x140 */
    __IO uint32_t PRTN0_CORE0_PUPD;  /**< Partition 0 Core 0 Process Update Register, offset: 0x144
                                      */
    __I uint32_t PRTN0_CORE0_STAT;   /**< Partition 0 Core 0 Status Register, offset: 0x148 */
    __IO uint32_t PRTN0_CORE0_ADDR;  /**< Partition 0 Core 0 Address Register, offset: 0x14C */
    uint8_t RESERVED_2[16];
    __IO uint32_t PRTN0_CORE1_PCONF; /**< Partition 0 Core 1 Process Configuration Register, offset:
                                        0x160 */
    __IO uint32_t PRTN0_CORE1_PUPD;  /**< Partition 0 Core 1 Process Update Register, offset: 0x164
                                      */
    __I uint32_t PRTN0_CORE1_STAT;   /**< Partition 0 Core 1 Status Register, offset: 0x168 */
    __IO uint32_t PRTN0_CORE1_ADDR;  /**< Partition 0 Core 1 Address Register, offset: 0x16C */
    uint8_t RESERVED_3[16];
    __IO uint32_t PRTN0_CORE2_PCONF; /**< Partition 0 Core 2 Process Configuration Register, offset:
                                        0x180 */
    __IO uint32_t PRTN0_CORE2_PUPD;  /**< Partition 0 Core 2 Process Update Register, offset: 0x184
                                      */
    __I uint32_t PRTN0_CORE2_STAT;   /**< Partition 0 Core 2 Status Register, offset: 0x188 */
    __IO uint32_t PRTN0_CORE2_ADDR;  /**< Partition 0 Core 2 Address Register, offset: 0x18C */
    uint8_t RESERVED_4[16];
    __IO uint32_t PRTN0_CORE3_PCONF; /**< Partition 0 Core 3 Process Configuration Register, offset:
                                        0x1A0 */
    __IO uint32_t PRTN0_CORE3_PUPD;  /**< Partition 0 Core 3 Process Update Register, offset: 0x1A4
                                      */
    __I uint32_t PRTN0_CORE3_STAT;   /**< Partition 0 Core 3 Status Register, offset: 0x1A8 */
    __IO uint32_t PRTN0_CORE3_ADDR;  /**< Partition 0 Core 3 Address Register, offset: 0x1AC */
    uint8_t RESERVED_5[16];
    __IO uint32_t PRTN0_CORE4_PCONF; /**< Partition 0 Core 4 Process Configuration Register, offset:
                                        0x1C0 */
    __IO uint32_t PRTN0_CORE4_PUPD;  /**< Partition 0 Core 4 Process Update Register, offset: 0x1C4
                                      */
    __I uint32_t PRTN0_CORE4_STAT;   /**< Partition 0 Core 4 Status Register, offset: 0x1C8 */
    __IO uint32_t PRTN0_CORE4_ADDR;  /**< Partition 0 Core 4 Address Register, offset: 0x1CC */
    uint8_t RESERVED_6[16];
    __IO uint32_t PRTN0_CORE5_PCONF; /**< Partition 0 Core 5 Process Configuration Register, offset:
                                        0x1E0 */
    __IO uint32_t PRTN0_CORE5_PUPD;  /**< Partition 0 Core 5 Process Update Register, offset: 0x1E4
                                      */
    __I uint32_t PRTN0_CORE5_STAT;   /**< Partition 0 Core 5 Status Register, offset: 0x1E8 */
    __IO uint32_t PRTN0_CORE5_ADDR;  /**< Partition 0 Core 5 Address Register, offset: 0x1EC */
    uint8_t RESERVED_7[16];
    __IO uint32_t PRTN0_CORE6_PCONF; /**< Partition 0 Core 6 Process Configuration Register, offset:
                                        0x200 */
    __IO uint32_t PRTN0_CORE6_PUPD;  /**< Partition 0 Core 6 Process Update Register, offset: 0x204
                                      */
    __I uint32_t PRTN0_CORE6_STAT;   /**< Partition 0 Core 6 Status Register, offset: 0x208 */
    __IO uint32_t PRTN0_CORE6_ADDR;  /**< Partition 0 Core 6 Address Register, offset: 0x20C */
    uint8_t RESERVED_8[16];
    __IO uint32_t PRTN0_CORE7_PCONF; /**< Partition 0 Core 7 Process Configuration Register, offset:
                                        0x220 */
    __IO uint32_t PRTN0_CORE7_PUPD;  /**< Partition 0 Core 7 Process Update Register, offset: 0x224
                                      */
    __I uint32_t PRTN0_CORE7_STAT;   /**< Partition 0 Core 7 Status Register, offset: 0x228 */
    __IO uint32_t PRTN0_CORE7_ADDR;  /**< Partition 0 Core 7 Address Register, offset: 0x22C */
    uint8_t RESERVED_9[208];
    __IO uint32_t PRTN1_PCONF; /**< Partition 1 Process Configuration Register, offset: 0x300 */
    __IO uint32_t PRTN1_PUPD;  /**< Partition 1 Process Update Register, offset: 0x304 */
    __I uint32_t PRTN1_STAT;   /**< Partition 1 Status Register, offset: 0x308 */
    uint8_t RESERVED_10[52];
    __IO uint32_t PRTN1_CORE0_PCONF; /**< Partition 1 Core 0 Process Configuration Register, offset:
                                        0x340 */
    __IO uint32_t PRTN1_CORE0_PUPD;  /**< Partition 1 Core 0 Process Update Register, offset: 0x344
                                      */
    __I uint32_t PRTN1_CORE0_STAT;   /**< Partition 1 Core 0 Status Register, offset: 0x348 */
    __IO uint32_t PRTN1_CORE0_ADDR;  /**< Partition 1 Core 0 Address Register, offset: 0x34C */
    uint8_t RESERVED_11[16];
    __IO uint32_t PRTN1_CORE1_PCONF; /**< Partition 1 Core 1 Process Configuration Register, offset:
                                        0x360 */
    __IO uint32_t PRTN1_CORE1_PUPD;  /**< Partition 1 Core 1 Process Update Register, offset: 0x364
                                      */
    __I uint32_t PRTN1_CORE1_STAT;   /**< Partition 1 Core 1 Status Register, offset: 0x368 */
    __IO uint32_t PRTN1_CORE1_ADDR;  /**< Partition 1 Core 1 Address Register, offset: 0x36C */
    uint8_t RESERVED_12[16];
    __IO uint32_t PRTN1_CORE2_PCONF; /**< Partition 1 Core 2 Process Configuration Register, offset:
                                        0x380 */
    __IO uint32_t PRTN1_CORE2_PUPD;  /**< Partition 1 Core 2 Process Update Register, offset: 0x384
                                      */
    __I uint32_t PRTN1_CORE2_STAT;   /**< Partition 1 Core 2 Status Register, offset: 0x388 */
    __IO uint32_t PRTN1_CORE2_ADDR;  /**< Partition 1 Core 2 Address Register, offset: 0x38C */
    uint8_t RESERVED_13[16];
    __IO uint32_t PRTN1_CORE3_PCONF; /**< Partition 1 Core 3 Process Configuration Register, offset:
                                        0x3A0 */
    __IO uint32_t PRTN1_CORE3_PUPD;  /**< Partition 1 Core 3 Process Update Register, offset: 0x3A4
                                      */
    __I uint32_t PRTN1_CORE3_STAT;   /**< Partition 1 Core 3 Status Register, offset: 0x3A8 */
    __IO uint32_t PRTN1_CORE3_ADDR;  /**< Partition 1 Core 3 Address Register, offset: 0x3AC */
    uint8_t RESERVED_14[336];
    __IO uint32_t PRTN2_PCONF; /**< Partition 2 Process Configuration Register, offset: 0x500 */
    __IO uint32_t PRTN2_PUPD;  /**< Partition 2 Process Update Register, offset: 0x504 */
    __I uint32_t PRTN2_STAT;   /**< Partition 2 Status Register, offset: 0x508 */
    uint8_t RESERVED_15[52];
    __IO uint32_t PRTN2_CORE0_PCONF; /**< Partition 2 Core 0 Process Configuration Register, offset:
                                        0x540 */
    __IO uint32_t PRTN2_CORE0_PUPD;  /**< Partition 2 Core 0 Process Update Register, offset: 0x544
                                      */
    __I uint32_t PRTN2_CORE0_STAT;   /**< Partition 2 Core 0 Status Register, offset: 0x548 */
    __IO uint32_t PRTN2_CORE0_ADDR;  /**< Partition 2 Core 0 Address Register, offset: 0x54C */
    uint8_t RESERVED_16[16];
    __IO uint32_t PRTN2_CORE1_PCONF; /**< Partition 2 Core 1 Process Configuration Register, offset:
                                        0x560 */
    __IO uint32_t PRTN2_CORE1_PUPD;  /**< Partition 2 Core 1 Process Update Register, offset: 0x564
                                      */
    __I uint32_t PRTN2_CORE1_STAT;   /**< Partition 2 Core 1 Status Register, offset: 0x568 */
    __IO uint32_t PRTN2_CORE1_ADDR;  /**< Partition 2 Core 1 Address Register, offset: 0x56C */
    uint8_t RESERVED_17[16];
    __IO uint32_t PRTN2_CORE2_PCONF; /**< Partition 2 Core 2 Process Configuration Register, offset:
                                        0x580 */
    __IO uint32_t PRTN2_CORE2_PUPD;  /**< Partition 2 Core 2 Process Update Register, offset: 0x584
                                      */
    __I uint32_t PRTN2_CORE2_STAT;   /**< Partition 2 Core 2 Status Register, offset: 0x588 */
    __IO uint32_t PRTN2_CORE2_ADDR;  /**< Partition 2 Core 2 Address Register, offset: 0x58C */
    uint8_t RESERVED_18[16];
    __IO uint32_t PRTN2_CORE3_PCONF; /**< Partition 2 Core 3 Process Configuration Register, offset:
                                        0x5A0 */
    __IO uint32_t PRTN2_CORE3_PUPD;  /**< Partition 2 Core 3 Process Update Register, offset: 0x5A4
                                      */
    __I uint32_t PRTN2_CORE3_STAT;   /**< Partition 2 Core 3 Status Register, offset: 0x5A8 */
    __IO uint32_t PRTN2_CORE3_ADDR;  /**< Partition 2 Core 3 Address Register, offset: 0x5AC */
} MC_ME_Type, *MC_ME_MemMapPtr;

/** Number of instances of the MC_ME module. */
#define MC_ME_INSTANCE_COUNT    (1u)

/* MC_ME - Peripheral instance base addresses */
/** Peripheral MC_ME base address */
#define IP_MC_ME_BASE           (0x41900000u)
/** Peripheral MC_ME base pointer */
#define IP_MC_ME                ((MC_ME_Type*)IP_MC_ME_BASE)
/** Array initializer of MC_ME peripheral base addresses */
#define IP_MC_ME_BASE_ADDRS     { IP_MC_ME_BASE }
/** Array initializer of MC_ME peripheral base pointers */
#define IP_MC_ME_BASE_PTRS      { IP_MC_ME }

/* ----------------------------------------------------------------------------
   -- MC_ME Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_ME_Register_Masks MC_ME Register Masks
 * @{
 */

/*! @name CTL_KEY - Control Key Register */
/*! @{ */

#define MC_ME_CTL_KEY_KEY_MASK  (0xFFFFU)
#define MC_ME_CTL_KEY_KEY_SHIFT (0U)
#define MC_ME_CTL_KEY_KEY_WIDTH (16U)
#define MC_ME_CTL_KEY_KEY(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_CTL_KEY_KEY_SHIFT)) & MC_ME_CTL_KEY_KEY_MASK)
/*! @} */

/*! @name MODE_CONF - Mode Configuration Register */
/*! @{ */

#define MC_ME_MODE_CONF_DEST_RST_MASK  (0x1U)
#define MC_ME_MODE_CONF_DEST_RST_SHIFT (0U)
#define MC_ME_MODE_CONF_DEST_RST_WIDTH (1U)
#define MC_ME_MODE_CONF_DEST_RST(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_MODE_CONF_DEST_RST_SHIFT)) & \
        MC_ME_MODE_CONF_DEST_RST_MASK)

#define MC_ME_MODE_CONF_FUNC_RST_MASK  (0x2U)
#define MC_ME_MODE_CONF_FUNC_RST_SHIFT (1U)
#define MC_ME_MODE_CONF_FUNC_RST_WIDTH (1U)
#define MC_ME_MODE_CONF_FUNC_RST(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_MODE_CONF_FUNC_RST_SHIFT)) & \
        MC_ME_MODE_CONF_FUNC_RST_MASK)
/*! @} */

/*! @name MODE_UPD - Mode Update Register */
/*! @{ */

#define MC_ME_MODE_UPD_MODE_UPD_MASK  (0x1U)
#define MC_ME_MODE_UPD_MODE_UPD_SHIFT (0U)
#define MC_ME_MODE_UPD_MODE_UPD_WIDTH (1U)
#define MC_ME_MODE_UPD_MODE_UPD(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_MODE_UPD_MODE_UPD_SHIFT)) & MC_ME_MODE_UPD_MODE_UPD_MASK)
/*! @} */

/*! @name PRTN0_PCONF - Partition 0 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_PCONF_PCE_MASK  (0x1U)
#define MC_ME_PRTN0_PCONF_PCE_SHIFT (0U)
#define MC_ME_PRTN0_PCONF_PCE_WIDTH (1U)
#define MC_ME_PRTN0_PCONF_PCE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_PCONF_PCE_SHIFT)) & MC_ME_PRTN0_PCONF_PCE_MASK)
/*! @} */

/*! @name PRTN0_PUPD - Partition 0 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_PUPD_PCUD_MASK  (0x1U)
#define MC_ME_PRTN0_PUPD_PCUD_SHIFT (0U)
#define MC_ME_PRTN0_PUPD_PCUD_WIDTH (1U)
#define MC_ME_PRTN0_PUPD_PCUD(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_PUPD_PCUD_SHIFT)) & MC_ME_PRTN0_PUPD_PCUD_MASK)
/*! @} */

/*! @name PRTN0_STAT - Partition 0 Status Register */
/*! @{ */

#define MC_ME_PRTN0_STAT_PCS_MASK  (0x1U)
#define MC_ME_PRTN0_STAT_PCS_SHIFT (0U)
#define MC_ME_PRTN0_STAT_PCS_WIDTH (1U)
#define MC_ME_PRTN0_STAT_PCS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_STAT_PCS_SHIFT)) & MC_ME_PRTN0_STAT_PCS_MASK)
/*! @} */

/*! @name PRTN0_CORE0_PCONF - Partition 0 Core 0 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE0_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE0_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE0_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE0_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE0_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE0_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE0_PUPD - Partition 0 Core 0 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE0_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE0_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE0_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE0_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE0_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE0_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE0_STAT - Partition 0 Core 0 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE0_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE0_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE0_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE0_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE0_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE0_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE0_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE0_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE0_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE0_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE0_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE0_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE0_ADDR - Partition 0 Core 0 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE0_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE0_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE0_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE0_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE0_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE0_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN0_CORE1_PCONF - Partition 0 Core 1 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE1_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE1_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE1_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE1_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE1_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE1_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE1_PUPD - Partition 0 Core 1 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE1_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE1_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE1_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE1_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE1_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE1_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE1_STAT - Partition 0 Core 1 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE1_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE1_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE1_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE1_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE1_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE1_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE1_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE1_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE1_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE1_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE1_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE1_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE1_ADDR - Partition 0 Core 1 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE1_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE1_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE1_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE1_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE1_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE1_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN0_CORE2_PCONF - Partition 0 Core 2 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE2_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE2_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE2_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE2_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE2_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE2_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE2_PUPD - Partition 0 Core 2 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE2_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE2_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE2_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE2_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE2_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE2_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE2_STAT - Partition 0 Core 2 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE2_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE2_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE2_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE2_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE2_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE2_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE2_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE2_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE2_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE2_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE2_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE2_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE2_ADDR - Partition 0 Core 2 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE2_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE2_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE2_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE2_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE2_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE2_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN0_CORE3_PCONF - Partition 0 Core 3 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE3_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE3_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE3_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE3_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE3_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE3_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE3_PUPD - Partition 0 Core 3 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE3_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE3_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE3_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE3_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE3_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE3_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE3_STAT - Partition 0 Core 3 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE3_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE3_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE3_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE3_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE3_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE3_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE3_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE3_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE3_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE3_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE3_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE3_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE3_ADDR - Partition 0 Core 3 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE3_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE3_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE3_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE3_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE3_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE3_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN0_CORE4_PCONF - Partition 0 Core 4 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE4_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE4_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE4_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE4_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE4_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE4_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE4_PUPD - Partition 0 Core 4 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE4_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE4_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE4_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE4_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE4_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE4_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE4_STAT - Partition 0 Core 4 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE4_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE4_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE4_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE4_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE4_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE4_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE4_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE4_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE4_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE4_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE4_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE4_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE4_ADDR - Partition 0 Core 4 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE4_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE4_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE4_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE4_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE4_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE4_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN0_CORE5_PCONF - Partition 0 Core 5 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE5_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE5_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE5_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE5_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE5_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE5_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE5_PUPD - Partition 0 Core 5 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE5_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE5_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE5_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE5_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE5_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE5_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE5_STAT - Partition 0 Core 5 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE5_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE5_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE5_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE5_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE5_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE5_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE5_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE5_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE5_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE5_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE5_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE5_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE5_ADDR - Partition 0 Core 5 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE5_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE5_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE5_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE5_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE5_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE5_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN0_CORE6_PCONF - Partition 0 Core 6 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE6_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE6_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE6_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE6_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE6_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE6_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE6_PUPD - Partition 0 Core 6 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE6_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE6_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE6_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE6_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE6_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE6_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE6_STAT - Partition 0 Core 6 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE6_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE6_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE6_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE6_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE6_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE6_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE6_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE6_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE6_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE6_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE6_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE6_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE6_ADDR - Partition 0 Core 6 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE6_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE6_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE6_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE6_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE6_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE6_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN0_CORE7_PCONF - Partition 0 Core 7 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN0_CORE7_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN0_CORE7_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN0_CORE7_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN0_CORE7_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE7_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN0_CORE7_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN0_CORE7_PUPD - Partition 0 Core 7 Process Update Register */
/*! @{ */

#define MC_ME_PRTN0_CORE7_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN0_CORE7_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN0_CORE7_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN0_CORE7_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE7_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN0_CORE7_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN0_CORE7_STAT - Partition 0 Core 7 Status Register */
/*! @{ */

#define MC_ME_PRTN0_CORE7_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN0_CORE7_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN0_CORE7_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN0_CORE7_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE7_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN0_CORE7_STAT_CCS_MASK)

#define MC_ME_PRTN0_CORE7_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN0_CORE7_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN0_CORE7_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN0_CORE7_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE7_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN0_CORE7_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN0_CORE7_ADDR - Partition 0 Core 7 Address Register */
/*! @{ */

#define MC_ME_PRTN0_CORE7_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN0_CORE7_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN0_CORE7_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN0_CORE7_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN0_CORE7_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN0_CORE7_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN1_PCONF - Partition 1 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN1_PCONF_PCE_MASK  (0x1U)
#define MC_ME_PRTN1_PCONF_PCE_SHIFT (0U)
#define MC_ME_PRTN1_PCONF_PCE_WIDTH (1U)
#define MC_ME_PRTN1_PCONF_PCE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_PCONF_PCE_SHIFT)) & MC_ME_PRTN1_PCONF_PCE_MASK)

#define MC_ME_PRTN1_PCONF_OSSE_MASK  (0x4U)
#define MC_ME_PRTN1_PCONF_OSSE_SHIFT (2U)
#define MC_ME_PRTN1_PCONF_OSSE_WIDTH (1U)
#define MC_ME_PRTN1_PCONF_OSSE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_PCONF_OSSE_SHIFT)) & MC_ME_PRTN1_PCONF_OSSE_MASK)
/*! @} */

/*! @name PRTN1_PUPD - Partition 1 Process Update Register */
/*! @{ */

#define MC_ME_PRTN1_PUPD_PCUD_MASK  (0x1U)
#define MC_ME_PRTN1_PUPD_PCUD_SHIFT (0U)
#define MC_ME_PRTN1_PUPD_PCUD_WIDTH (1U)
#define MC_ME_PRTN1_PUPD_PCUD(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_PUPD_PCUD_SHIFT)) & MC_ME_PRTN1_PUPD_PCUD_MASK)

#define MC_ME_PRTN1_PUPD_OSSUD_MASK  (0x4U)
#define MC_ME_PRTN1_PUPD_OSSUD_SHIFT (2U)
#define MC_ME_PRTN1_PUPD_OSSUD_WIDTH (1U)
#define MC_ME_PRTN1_PUPD_OSSUD(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_PUPD_OSSUD_SHIFT)) & MC_ME_PRTN1_PUPD_OSSUD_MASK)
/*! @} */

/*! @name PRTN1_STAT - Partition 1 Status Register */
/*! @{ */

#define MC_ME_PRTN1_STAT_PCS_MASK  (0x1U)
#define MC_ME_PRTN1_STAT_PCS_SHIFT (0U)
#define MC_ME_PRTN1_STAT_PCS_WIDTH (1U)
#define MC_ME_PRTN1_STAT_PCS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_STAT_PCS_SHIFT)) & MC_ME_PRTN1_STAT_PCS_MASK)

#define MC_ME_PRTN1_STAT_OSSS_MASK  (0x4U)
#define MC_ME_PRTN1_STAT_OSSS_SHIFT (2U)
#define MC_ME_PRTN1_STAT_OSSS_WIDTH (1U)
#define MC_ME_PRTN1_STAT_OSSS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_STAT_OSSS_SHIFT)) & MC_ME_PRTN1_STAT_OSSS_MASK)
/*! @} */

/*! @name PRTN1_CORE0_PCONF - Partition 1 Core 0 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN1_CORE0_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN1_CORE0_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN1_CORE0_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN1_CORE0_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE0_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN1_CORE0_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN1_CORE0_PUPD - Partition 1 Core 0 Process Update Register */
/*! @{ */

#define MC_ME_PRTN1_CORE0_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN1_CORE0_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN1_CORE0_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN1_CORE0_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE0_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN1_CORE0_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN1_CORE0_STAT - Partition 1 Core 0 Status Register */
/*! @{ */

#define MC_ME_PRTN1_CORE0_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN1_CORE0_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN1_CORE0_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN1_CORE0_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE0_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN1_CORE0_STAT_CCS_MASK)

#define MC_ME_PRTN1_CORE0_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN1_CORE0_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN1_CORE0_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN1_CORE0_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE0_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN1_CORE0_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN1_CORE0_ADDR - Partition 1 Core 0 Address Register */
/*! @{ */

#define MC_ME_PRTN1_CORE0_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN1_CORE0_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN1_CORE0_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN1_CORE0_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE0_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN1_CORE0_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN1_CORE1_PCONF - Partition 1 Core 1 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN1_CORE1_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN1_CORE1_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN1_CORE1_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN1_CORE1_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE1_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN1_CORE1_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN1_CORE1_PUPD - Partition 1 Core 1 Process Update Register */
/*! @{ */

#define MC_ME_PRTN1_CORE1_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN1_CORE1_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN1_CORE1_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN1_CORE1_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE1_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN1_CORE1_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN1_CORE1_STAT - Partition 1 Core 1 Status Register */
/*! @{ */

#define MC_ME_PRTN1_CORE1_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN1_CORE1_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN1_CORE1_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN1_CORE1_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE1_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN1_CORE1_STAT_CCS_MASK)

#define MC_ME_PRTN1_CORE1_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN1_CORE1_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN1_CORE1_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN1_CORE1_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE1_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN1_CORE1_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN1_CORE1_ADDR - Partition 1 Core 1 Address Register */
/*! @{ */

#define MC_ME_PRTN1_CORE1_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN1_CORE1_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN1_CORE1_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN1_CORE1_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE1_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN1_CORE1_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN1_CORE2_PCONF - Partition 1 Core 2 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN1_CORE2_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN1_CORE2_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN1_CORE2_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN1_CORE2_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE2_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN1_CORE2_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN1_CORE2_PUPD - Partition 1 Core 2 Process Update Register */
/*! @{ */

#define MC_ME_PRTN1_CORE2_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN1_CORE2_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN1_CORE2_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN1_CORE2_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE2_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN1_CORE2_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN1_CORE2_STAT - Partition 1 Core 2 Status Register */
/*! @{ */

#define MC_ME_PRTN1_CORE2_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN1_CORE2_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN1_CORE2_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN1_CORE2_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE2_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN1_CORE2_STAT_CCS_MASK)

#define MC_ME_PRTN1_CORE2_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN1_CORE2_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN1_CORE2_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN1_CORE2_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE2_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN1_CORE2_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN1_CORE2_ADDR - Partition 1 Core 2 Address Register */
/*! @{ */

#define MC_ME_PRTN1_CORE2_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN1_CORE2_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN1_CORE2_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN1_CORE2_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE2_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN1_CORE2_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN1_CORE3_PCONF - Partition 1 Core 3 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN1_CORE3_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN1_CORE3_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN1_CORE3_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN1_CORE3_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE3_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN1_CORE3_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN1_CORE3_PUPD - Partition 1 Core 3 Process Update Register */
/*! @{ */

#define MC_ME_PRTN1_CORE3_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN1_CORE3_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN1_CORE3_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN1_CORE3_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE3_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN1_CORE3_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN1_CORE3_STAT - Partition 1 Core 3 Status Register */
/*! @{ */

#define MC_ME_PRTN1_CORE3_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN1_CORE3_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN1_CORE3_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN1_CORE3_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE3_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN1_CORE3_STAT_CCS_MASK)

#define MC_ME_PRTN1_CORE3_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN1_CORE3_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN1_CORE3_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN1_CORE3_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE3_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN1_CORE3_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN1_CORE3_ADDR - Partition 1 Core 3 Address Register */
/*! @{ */

#define MC_ME_PRTN1_CORE3_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN1_CORE3_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN1_CORE3_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN1_CORE3_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN1_CORE3_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN1_CORE3_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN2_PCONF - Partition 2 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN2_PCONF_PCE_MASK  (0x1U)
#define MC_ME_PRTN2_PCONF_PCE_SHIFT (0U)
#define MC_ME_PRTN2_PCONF_PCE_WIDTH (1U)
#define MC_ME_PRTN2_PCONF_PCE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_PCONF_PCE_SHIFT)) & MC_ME_PRTN2_PCONF_PCE_MASK)

#define MC_ME_PRTN2_PCONF_OSSE_MASK  (0x4U)
#define MC_ME_PRTN2_PCONF_OSSE_SHIFT (2U)
#define MC_ME_PRTN2_PCONF_OSSE_WIDTH (1U)
#define MC_ME_PRTN2_PCONF_OSSE(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_PCONF_OSSE_SHIFT)) & MC_ME_PRTN2_PCONF_OSSE_MASK)
/*! @} */

/*! @name PRTN2_PUPD - Partition 2 Process Update Register */
/*! @{ */

#define MC_ME_PRTN2_PUPD_PCUD_MASK  (0x1U)
#define MC_ME_PRTN2_PUPD_PCUD_SHIFT (0U)
#define MC_ME_PRTN2_PUPD_PCUD_WIDTH (1U)
#define MC_ME_PRTN2_PUPD_PCUD(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_PUPD_PCUD_SHIFT)) & MC_ME_PRTN2_PUPD_PCUD_MASK)

#define MC_ME_PRTN2_PUPD_OSSUD_MASK  (0x4U)
#define MC_ME_PRTN2_PUPD_OSSUD_SHIFT (2U)
#define MC_ME_PRTN2_PUPD_OSSUD_WIDTH (1U)
#define MC_ME_PRTN2_PUPD_OSSUD(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_PUPD_OSSUD_SHIFT)) & MC_ME_PRTN2_PUPD_OSSUD_MASK)
/*! @} */

/*! @name PRTN2_STAT - Partition 2 Status Register */
/*! @{ */

#define MC_ME_PRTN2_STAT_PCS_MASK  (0x1U)
#define MC_ME_PRTN2_STAT_PCS_SHIFT (0U)
#define MC_ME_PRTN2_STAT_PCS_WIDTH (1U)
#define MC_ME_PRTN2_STAT_PCS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_STAT_PCS_SHIFT)) & MC_ME_PRTN2_STAT_PCS_MASK)

#define MC_ME_PRTN2_STAT_OSSS_MASK  (0x4U)
#define MC_ME_PRTN2_STAT_OSSS_SHIFT (2U)
#define MC_ME_PRTN2_STAT_OSSS_WIDTH (1U)
#define MC_ME_PRTN2_STAT_OSSS(x) \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_STAT_OSSS_SHIFT)) & MC_ME_PRTN2_STAT_OSSS_MASK)
/*! @} */

/*! @name PRTN2_CORE0_PCONF - Partition 2 Core 0 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN2_CORE0_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN2_CORE0_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN2_CORE0_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN2_CORE0_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE0_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN2_CORE0_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN2_CORE0_PUPD - Partition 2 Core 0 Process Update Register */
/*! @{ */

#define MC_ME_PRTN2_CORE0_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN2_CORE0_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN2_CORE0_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN2_CORE0_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE0_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN2_CORE0_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN2_CORE0_STAT - Partition 2 Core 0 Status Register */
/*! @{ */

#define MC_ME_PRTN2_CORE0_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN2_CORE0_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN2_CORE0_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN2_CORE0_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE0_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN2_CORE0_STAT_CCS_MASK)

#define MC_ME_PRTN2_CORE0_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN2_CORE0_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN2_CORE0_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN2_CORE0_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE0_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN2_CORE0_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN2_CORE0_ADDR - Partition 2 Core 0 Address Register */
/*! @{ */

#define MC_ME_PRTN2_CORE0_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN2_CORE0_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN2_CORE0_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN2_CORE0_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE0_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN2_CORE0_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN2_CORE1_PCONF - Partition 2 Core 1 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN2_CORE1_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN2_CORE1_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN2_CORE1_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN2_CORE1_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE1_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN2_CORE1_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN2_CORE1_PUPD - Partition 2 Core 1 Process Update Register */
/*! @{ */

#define MC_ME_PRTN2_CORE1_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN2_CORE1_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN2_CORE1_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN2_CORE1_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE1_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN2_CORE1_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN2_CORE1_STAT - Partition 2 Core 1 Status Register */
/*! @{ */

#define MC_ME_PRTN2_CORE1_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN2_CORE1_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN2_CORE1_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN2_CORE1_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE1_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN2_CORE1_STAT_CCS_MASK)

#define MC_ME_PRTN2_CORE1_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN2_CORE1_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN2_CORE1_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN2_CORE1_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE1_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN2_CORE1_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN2_CORE1_ADDR - Partition 2 Core 1 Address Register */
/*! @{ */

#define MC_ME_PRTN2_CORE1_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN2_CORE1_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN2_CORE1_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN2_CORE1_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE1_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN2_CORE1_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN2_CORE2_PCONF - Partition 2 Core 2 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN2_CORE2_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN2_CORE2_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN2_CORE2_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN2_CORE2_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE2_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN2_CORE2_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN2_CORE2_PUPD - Partition 2 Core 2 Process Update Register */
/*! @{ */

#define MC_ME_PRTN2_CORE2_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN2_CORE2_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN2_CORE2_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN2_CORE2_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE2_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN2_CORE2_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN2_CORE2_STAT - Partition 2 Core 2 Status Register */
/*! @{ */

#define MC_ME_PRTN2_CORE2_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN2_CORE2_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN2_CORE2_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN2_CORE2_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE2_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN2_CORE2_STAT_CCS_MASK)

#define MC_ME_PRTN2_CORE2_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN2_CORE2_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN2_CORE2_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN2_CORE2_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE2_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN2_CORE2_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN2_CORE2_ADDR - Partition 2 Core 2 Address Register */
/*! @{ */

#define MC_ME_PRTN2_CORE2_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN2_CORE2_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN2_CORE2_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN2_CORE2_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE2_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN2_CORE2_ADDR_ADDR_MASK)
/*! @} */

/*! @name PRTN2_CORE3_PCONF - Partition 2 Core 3 Process Configuration Register */
/*! @{ */

#define MC_ME_PRTN2_CORE3_PCONF_CCE_MASK  (0x1U)
#define MC_ME_PRTN2_CORE3_PCONF_CCE_SHIFT (0U)
#define MC_ME_PRTN2_CORE3_PCONF_CCE_WIDTH (1U)
#define MC_ME_PRTN2_CORE3_PCONF_CCE(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE3_PCONF_CCE_SHIFT)) & \
        MC_ME_PRTN2_CORE3_PCONF_CCE_MASK)
/*! @} */

/*! @name PRTN2_CORE3_PUPD - Partition 2 Core 3 Process Update Register */
/*! @{ */

#define MC_ME_PRTN2_CORE3_PUPD_CCUPD_MASK  (0x1U)
#define MC_ME_PRTN2_CORE3_PUPD_CCUPD_SHIFT (0U)
#define MC_ME_PRTN2_CORE3_PUPD_CCUPD_WIDTH (1U)
#define MC_ME_PRTN2_CORE3_PUPD_CCUPD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE3_PUPD_CCUPD_SHIFT)) & \
        MC_ME_PRTN2_CORE3_PUPD_CCUPD_MASK)
/*! @} */

/*! @name PRTN2_CORE3_STAT - Partition 2 Core 3 Status Register */
/*! @{ */

#define MC_ME_PRTN2_CORE3_STAT_CCS_MASK  (0x1U)
#define MC_ME_PRTN2_CORE3_STAT_CCS_SHIFT (0U)
#define MC_ME_PRTN2_CORE3_STAT_CCS_WIDTH (1U)
#define MC_ME_PRTN2_CORE3_STAT_CCS(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE3_STAT_CCS_SHIFT)) & \
        MC_ME_PRTN2_CORE3_STAT_CCS_MASK)

#define MC_ME_PRTN2_CORE3_STAT_WFI_MASK  (0x80000000U)
#define MC_ME_PRTN2_CORE3_STAT_WFI_SHIFT (31U)
#define MC_ME_PRTN2_CORE3_STAT_WFI_WIDTH (1U)
#define MC_ME_PRTN2_CORE3_STAT_WFI(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE3_STAT_WFI_SHIFT)) & \
        MC_ME_PRTN2_CORE3_STAT_WFI_MASK)
/*! @} */

/*! @name PRTN2_CORE3_ADDR - Partition 2 Core 3 Address Register */
/*! @{ */

#define MC_ME_PRTN2_CORE3_ADDR_ADDR_MASK  (0xFFFFFFFCU)
#define MC_ME_PRTN2_CORE3_ADDR_ADDR_SHIFT (2U)
#define MC_ME_PRTN2_CORE3_ADDR_ADDR_WIDTH (30U)
#define MC_ME_PRTN2_CORE3_ADDR_ADDR(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << MC_ME_PRTN2_CORE3_ADDR_ADDR_SHIFT)) & \
        MC_ME_PRTN2_CORE3_ADDR_ADDR_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MC_ME_Register_Masks */

/*!
 * @}
 */ /* end of group MC_ME_Peripheral_Access_Layer */

#endif /* #if !defined(S32Z2_MC_ME_H_) */
