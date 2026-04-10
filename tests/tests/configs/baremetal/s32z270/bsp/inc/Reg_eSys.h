/*
 * Copyright 2021-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REG_ESYS_H
#define REG_ESYS_H

/**
 *   @file
 *
 *   @addtogroup BASENXP_COMPONENT
 *   @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define REG_ESYS_VENDOR_ID                   43
#define REG_ESYS_MODULE_ID                   0
#define REG_ESYS_AR_RELEASE_MAJOR_VERSION    4
#define REG_ESYS_AR_RELEASE_MINOR_VERSION    7
#define REG_ESYS_AR_RELEASE_REVISION_VERSION 0
#define REG_ESYS_SW_MAJOR_VERSION            2
#define REG_ESYS_SW_MINOR_VERSION            0
#define REG_ESYS_SW_PATCH_VERSION            1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                   REGISTER PROTECTION (REG_PROT)
==================================================================================================*/
/**
 * @brief Macros defined for the IPVs that are protected.
 */
#define MCAL_SAR_ADC_AE_REG_PROT_AVAILABLE   (STD_ON)
#define MCAL_FLEXPWM_AE_REG_PROT_AVAILABLE   (STD_ON)
#define MCAL_ETIMER_AE_REG_PROT_AVAILABLE    (STD_ON)
#define MCAL_CTU_AE_REG_PROT_AVAILABLE       (STD_ON)
#define MCAL_DMAMUX_AE_REG_PROT_AVAILABLE    (STD_ON)
#define MCAL_PIT_AE_REG_PROT_AVAILABLE       (STD_ON)
#define MCAL_PFLASH_AE_REG_PROT_AVAILABLE    (STD_ON)
#define MCAL_C55FP_AE_REG_PROT_AVAILABLE     (STD_ON)
#define MCAL_CMU_AE_REG_PROT_AVAILABLE       (STD_ON)
#define MCAL_SIUL2_AE_REG_PROT_AVAILABLE     (STD_ON)
#define MCAL_PMC_AE_REG_PROT_AVAILABLE       (STD_ON)
#define MCAL_DIPORTSD_AE_REG_PROT_AVAILABLE  (STD_ON)
#define MCAL_EDMA_AE_REG_PROT_AVAILABLE      (STD_ON)

/**
 * @brief Macros defined for the protection size
 */
#define SAR_ADC_AE_PROT_MEM_U32              ((uint32)0x00000001UL)
#define FLEXPWM_AE_PROT_MEM_U32              ((uint32)0x00000001UL)
#define ETIMER_AE_PROT_MEM_U32               ((uint32)0x00000001UL)
#define CTU_AE_PROT_MEM_U32                  ((uint32)0x00000001UL)
#define DMAMUX_AE_PROT_MEM_U32               ((uint32)0x00000001UL)
#define PIT_AE_PROT_MEM_U32                  ((uint32)0x00000001UL)
#define PFLASH_AE_PROT_MEM_U32               ((uint32)0x00000001UL)
#define C55FP_AE_PROT_MEM_U32                ((uint32)0x00000001UL)
#define CMU_AE_PROT_MEM_U32                  ((uint32)0x00000001UL)
#define SIUL2_AE_PROT_MEM_U32                ((uint32)0x00000001UL)
#define PMC_AE_PROT_MEM_U32                  ((uint32)0x00000001UL)
#define DIPORTSD_AE_PROT_MEM_U32             ((uint32)0x00000001UL)
#define EDMA_AE_PROT_MEM_U32                 ((uint32)0x00000001UL)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* REG_ESYS_H */
